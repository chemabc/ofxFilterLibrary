//
//  PosterizeFilter.cpp
//  filterSandbox
//
//  Created by Chema Blanco 2014/07/11
//  Based on Matthew Fargo on 2014/06/23.
//
//

#include "PosterizeFilter.h"


PosterizeFilter::PosterizeFilter(float width, float height, float gamma, float numColors) :AbstractFilter() {
    _name = "Posterize";
    _gamma = gamma;
    _numColors = numColors;
    _addParameter(new ParameterF("gamma", _gamma));
    _addParameter(new ParameterF("numColors", _numColors));
    _setupShader();
}
PosterizeFilter::~PosterizeFilter() {}


void PosterizeFilter::onKeyPressed(int key) {
//    if (key==OF_KEY_LEFT) _gamma--;
//    else if (key==OF_KEY_RIGHT) _gamma++;
//    else if (key==OF_KEY_UP) _numColors += 0.1;
//    else if (key==OF_KEY_DOWN) _numColors -= 0.1;
    updateParameters();
}
void PosterizeFilter::onMousePressed(int button){
  updateParameters();
}

string PosterizeFilter::_getVertSrc() {
    return AbstractFilter::_getVertSrc();
}

string PosterizeFilter::_getFragSrc() {
    return GLSL_STRING(120,
        uniform sampler2D inputImageTexture;
        uniform float gamma;
        uniform float numColors;

        void main() {
            vec2 textureCoordinate = gl_TexCoord[0].xy;
            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            vec3 c = textureColor.rgb;
            c = pow(c, vec3(gamma, gamma, gamma));
            c = c * numColors;
            c = floor(c);
            c = c/numColors;
            c = pow(c, vec3(1.0/gamma));
            gl_FragColor = vec4(c, 1.0);

    }
    );
}

void PosterizeFilter::updateParameters(){
      if (_gamma<0) _gamma = 0;
    if (_numColors<0) _numColors = 0;
    updateParameter("gamma", _gamma);
    updateParameter("numColors", _numColors);
}
#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
string PosterizeFilter::getTotalHelpString() {
    string sComplete= _name + ": " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    sComplete += " _gamma: " + ofToString(_gamma) + "; ";
    sComplete += " _numColors: " + ofToString(_numColors) + "; ";
    return sComplete;
}
void PosterizeFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
        ptr_gui->addSlider("_gamma"+ofToString(i_ID), _gamma, 0, 5.0);
        ptr_gui->addSlider("_numColors"+ofToString(i_ID), _numColors, 1.0, 50.0);

        if(bLoadSettings) {
            ptr_gui->loadFromXML();
            updateParameters();
        }
    }

}
#endif
