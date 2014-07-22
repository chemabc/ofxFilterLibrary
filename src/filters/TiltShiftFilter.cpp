//
//  TiltShiftFilter.cpp
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#include "TiltShiftFilter.h"


TiltShiftFilter::TiltShiftFilter(ofTexture & texture, float focusPercent, float falloff) : AbstractFilter(texture.getWidth(), texture.getHeight()) {
    _name = "Tilt Shift";
    _texture = texture;
    _focusPercent=ofClamp(focusPercent, 0, 1);
    _gaussianBlurFilter = new GaussianBlurFilter(getWidth(), getHeight());
    _addParameter(new ParameterF("topFocusLevel", focusPercent));
    _addParameter(new ParameterF("bottomFocusLevel", 1.f - focusPercent));
    _addParameter(new ParameterF("focusFallOffRate", falloff));
    _addParameter(new ParameterT("inputImageTexture", _texture, 1));
    _addParameter(new ParameterT("inputImageTexture2", _gaussianBlurFilter->getTextureReference(), 2));
    _setupShader();
}
TiltShiftFilter::~TiltShiftFilter() {}

string TiltShiftFilter::_getFragSrc() {
    return GLSL_STRING(120,
        uniform sampler2D inputImageTexture;
        uniform sampler2D inputImageTexture2;

        uniform float topFocusLevel;
        uniform float bottomFocusLevel;
        uniform float focusFallOffRate;

        void main() {
            vec2 uv = gl_TexCoord[0].xy;
            vec4 sharpImageColor = texture2D(inputImageTexture, uv);
            vec4 blurredImageColor = texture2D(inputImageTexture2, uv);

            float blurIntensity = 1.0 - smoothstep(topFocusLevel - focusFallOffRate, topFocusLevel, uv.y);
            blurIntensity += smoothstep(bottomFocusLevel, bottomFocusLevel + focusFallOffRate, uv.y);

            gl_FragColor = mix(sharpImageColor, blurredImageColor, blurIntensity);
        }
    );
}

void TiltShiftFilter::onKeyPressed(int key) {
    if (key==OF_KEY_UP)
        _focusPercent = ofClamp(_focusPercent-0.01, 0, 1);
    else if (key==OF_KEY_DOWN)
        _focusPercent = ofClamp(_focusPercent+0.01, 0, 1);
    updateParameter("topFocusLevel", _focusPercent);
    updateParameter("bottomFocusLevel", 1.f - _focusPercent);
}
void TiltShiftFilter::onMousePressed(int button) {
    updateParameter("topFocusLevel", _focusPercent);
    updateParameter("bottomFocusLevel", 1.f - _focusPercent);
}
void TiltShiftFilter::begin() {
    _gaussianBlurFilter->begin();
    _texture.draw(0, 0);
    _gaussianBlurFilter->end();
    AbstractFilter::begin();
}


void TiltShiftFilter::describeParameters() {
    AbstractFilter::describeParameters();
    _gaussianBlurFilter->describeParameters();
}
#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
string TiltShiftFilter::getTotalHelpString() {
    string sComplete= _name + ": " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    sComplete += " _focusPercent: " + ofToString(_focusPercent) + "; ";
    return sComplete;
}
void TiltShiftFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
     ptr_gui = gui;
    s_userGuiPage=_name+"_"+ofToString(i_ID);
    if(ptr_gui!=0){
        if(userGuiPage == ""){

            if(bUsePageNameAsATitle){
                ptr_gui->addTitle(s_userGuiPage);
            }
            else{
                ptr_gui->addPage(s_userGuiPage);
            }
        }else{
            if(bUsePageNameAsATitle){
                ptr_gui->addTitle(userGuiPage);
            }
            else{
                ptr_gui->setPage(userGuiPage);
                ptr_gui->addTitle(s_userGuiPage);
            }
        }
        ptr_gui->addToggle("_b_activeFilter_"+ofToString(i_ID), _b_activeFilter);
        ptr_gui->addSlider("_focusPercent"+ofToString(i_ID), _focusPercent, 0, 10.0);


        if(bLoadSettings) ptr_gui->loadFromXML();
    }

}
#endif
