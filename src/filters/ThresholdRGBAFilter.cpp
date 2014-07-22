//
//  ThresholdRGBAFilter.cpp
//  filterSandbox
//
//  Created by Chema Blanco 2014/07/11
//  Based on Matthew Fargo on 2014/06/23.
//
//

#include "ThresholdRGBAFilter.h"


ThresholdRGBAFilter::ThresholdRGBAFilter(float width, float height, float threshold) : AbstractFilter() {
    _name = "ThresholdRGBA";
    _thresholdR = threshold;
    _thresholdG = threshold;
    _thresholdB = threshold;
    _thresholdA = threshold;
    _sharp = 0;
    _invert = 0;
    _addParameter(new ParameterF("thresholdR", _thresholdR));
    _addParameter(new ParameterF("thresholdG", _thresholdG));
    _addParameter(new ParameterF("thresholdB", _thresholdB));
    _addParameter(new ParameterF("thresholdA", _thresholdA));
    _addParameter(new ParameterI("sharp", _sharp));
    _addParameter(new ParameterI("invert", _invert));
    _setupShader();
}
ThresholdRGBAFilter::~ThresholdRGBAFilter() {}


void ThresholdRGBAFilter::onKeyPressed(int key) {
    updateParameters();
}
void ThresholdRGBAFilter::onMousePressed(int button){
    updateParameters();
}

string ThresholdRGBAFilter::_getVertSrc() {
    return AbstractFilter::_getVertSrc();
}

string ThresholdRGBAFilter::_getFragSrc() {
    return GLSL_STRING(120,
         uniform sampler2D inputImageTexture;
         uniform float thresholdR;
         uniform float thresholdG;
         uniform float thresholdB;
         uniform float thresholdA;
         uniform int sharp;
         uniform int invert;

    void main(){
            //Change into grayscale
            vec2 textureCoordinate = gl_TexCoord[0].xy;
            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            vec4 finalColor;

            if(sharp==0){
                if(textureColor.r >= thresholdR) finalColor.r = textureColor.r; else finalColor.r=0.0;
                if(textureColor.g >= thresholdG) finalColor.g = textureColor.g; else finalColor.g=0.0;
                if(textureColor.b >= thresholdB) finalColor.b = textureColor.b; else finalColor.b=0.0;
                if(textureColor.a >= thresholdA) finalColor.a = textureColor.a; else finalColor.a=0.0;
            }else{
                if(textureColor.r >= thresholdR) finalColor.r = 1.0; else finalColor.r=0.0;
                if(textureColor.g >= thresholdG) finalColor.g = 1.0; else finalColor.g=0.0;
                if(textureColor.b >= thresholdB) finalColor.b = 1.0; else finalColor.b=0.0;
                if(textureColor.a >= thresholdA) finalColor.a = 1.0; else finalColor.a=0.0;
            }


            if(invert==1) {
                finalColor.r = 1.0 - finalColor.r;
                finalColor.g = 1.0 - finalColor.g;
                finalColor.b = 1.0 - finalColor.b;
                //finalColor.a = 1.0 - finalColor.a;
            }

            gl_FragColor = finalColor;

    }
    );
}

void ThresholdRGBAFilter::updateParameters(){
    if (_thresholdR<0) _thresholdR = 0;
    if (_thresholdR>1) _thresholdR = 1;
    if (_thresholdG<0) _thresholdG = 0;
    if (_thresholdG>1) _thresholdG = 1;
    if (_thresholdB<0) _thresholdB = 0;
    if (_thresholdB>1) _thresholdB = 1;
    if (_thresholdA<0) _thresholdA = 0;
    if (_thresholdA>1) _thresholdA = 1;
    if (_sharp<0) _sharp = 0;
    if (_sharp>1) _sharp = 1;
    if (_invert<0) _invert = 0;
    if (_invert>1) _invert = 1;
    updateParameter("thresholdR", _thresholdR);
    updateParameter("thresholdG", _thresholdG);
    updateParameter("thresholdB", _thresholdB);
    updateParameter("thresholdA", _thresholdA);
    updateParameter("sharp", _sharp);
    updateParameter("invert", _invert);
}
#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
string ThresholdRGBAFilter::getTotalHelpString() {
    string sComplete= _name + ": " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    sComplete += " _sharp: " + ofToString(_sharp) + "; ";
    sComplete += " _invert: " + ofToString(_invert) + "; ";
    sComplete += " _thresholdR: " + ofToString(_thresholdR) + "; ";
    sComplete += " _thresholdG: " + ofToString(_thresholdG) + "; ";
    sComplete += " _thresholdB: " + ofToString(_thresholdB) + "; ";
    sComplete += " _thresholdA: " + ofToString(_thresholdA) + "; ";
    return sComplete;
}
void ThresholdRGBAFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
        ptr_gui->addSlider("_sharp"+ofToString(i_ID), _sharp, 0, 1);
        ptr_gui->addSlider("_invert"+ofToString(i_ID), _invert, 0, 1);
        ptr_gui->addSlider("_thresholdR"+ofToString(i_ID), _thresholdR, 0.0, 1.0);
        ptr_gui->addSlider("_thresholdG"+ofToString(i_ID), _thresholdG, 0.0, 1.0);
        ptr_gui->addSlider("_thresholdB"+ofToString(i_ID), _thresholdB, 0.0, 1.0);
        ptr_gui->addSlider("_thresholdA"+ofToString(i_ID), _thresholdA, 0.0, 1.0);


        if(bLoadSettings){
            ptr_gui->loadFromXML();
            updateParameters();
        }
    }

}
#endif
