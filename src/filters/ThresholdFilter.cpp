//
//  ThresholdFilter.cpp
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#include "ThresholdFilter.h"


ThresholdFilter::ThresholdFilter(float width, float height, float threshold) : AbstractFilter() {
    _name = "Threshold";
    _threshold = threshold;
//    _sharp = false;
    _addParameter(new ParameterF("threshold", _threshold));
   // _addParameter(new ParameterF("sharp", _sharp));
    _setupShader();
}
ThresholdFilter::~ThresholdFilter() {}


void ThresholdFilter::onKeyPressed(int key) {
    if (key==OF_KEY_LEFT) _threshold--;
    else if (key==OF_KEY_RIGHT) _threshold++;

    if (_threshold<0) _threshold = 0;
    updateParameter("threshold", _threshold);
//    updateParameter("sharp", _sharp);

}
void ThresholdFilter::onMousePressed(int button){
    if (_threshold<0) _threshold = 0;
    updateParameter("threshold", _threshold);
//    updateParameter("sharp", _sharp);
}

string ThresholdFilter::_getVertSrc() {
    return AbstractFilter::_getVertSrc();
}

string ThresholdFilter::_getFragSrc() {
    return GLSL_STRING(120,
        uniform sampler2D inputImageTexture;
         uniform float threshold;
         uniform bool sharp;
        const vec3 W = vec3(0.2125, 0.7154, 0.0721);
    void main(){
            //Change into grayscale
            vec2 textureCoordinate = gl_TexCoord[0].xy;

            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            float luminance = dot(textureColor.rgb, W);


            if(luminance >= threshold){
                luminance = 1.0;
            } else luminance = 0.0;

            gl_FragColor = vec4(vec3(luminance), textureColor.a);


    }
    );
}
#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
string ThresholdFilter::getTotalHelpString() {
    string sComplete= "Gaussian: " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
//    sComplete += " _sharp: " + ofToString(_sharp) + "; ";
    sComplete += " _threshold: " + ofToString(_threshold) + "; ";
    return sComplete;
}
void ThresholdFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
//        ptr_gui->addToggle("_sharp"+ofToString(i_ID), _sharp);
        ptr_gui->addSlider("_threshold"+ofToString(i_ID), _threshold, 0.0, 1.0);


        if(bLoadSettings) ptr_gui->loadFromXML();
    }

}
#endif
