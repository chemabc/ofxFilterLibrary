//
//  DissolveBlendFilter.cpp
//  ofxFilterLibraryExample
//
//  Created by Matthew Fargo on 2014/06/30.
//
//

#include "DissolveBlendFilter.h"

DissolveBlendFilter::DissolveBlendFilter(float width, float height, float mix) : AbstractTwoInputFilter(width, height) {
    _name = "Dissolve Blend";
    _addParameter(new ParameterF("mixturePercent", mix));
    setMix(mix);
    _setupShader();
}
DissolveBlendFilter::~DissolveBlendFilter() {}



string DissolveBlendFilter::_getFragSrc() {
    return GLSL_STRING(120,
        varying vec2 textureCoordinate;
        uniform sampler2D inputImageTexture;
        uniform sampler2D inputImageTexture2;
        uniform float mixturePercent;

        void main()
        {

            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            vec4 textureColor2 = texture2D(inputImageTexture2, textureCoordinate);

            vec4 color;
            if (textureCoordinate.x > 0.5) color = textureColor;
            else color = textureColor2;
            //gl_FragColor = color;
            gl_FragColor = mix(textureColor, textureColor2, mixturePercent);
        }
    );
}

void   DissolveBlendFilter::onKeyPressed(int key){
    updateParameter("mixturePercent", _mix);
}
void   DissolveBlendFilter::onMousePressed(int button){
    updateParameter("mixturePercent", _mix);
}

void DissolveBlendFilter::setMix(float mix)  {
    _mix = mix;
    updateParameter("mixturePercent", mix);
}

#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
string DissolveBlendFilter::getTotalHelpString() {
    string sComplete= "Dissolve: " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    sComplete += " _mix: " + ofToString(_mix) + "; ";

    return sComplete;
}
void DissolveBlendFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
        ptr_gui->addSlider("_mix"+ofToString(i_ID), _mix, 0, 255.0);


        if(bLoadSettings) ptr_gui->loadFromXML();
    }

}
#endif
