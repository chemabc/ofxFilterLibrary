//
//  GaussianBlurFilter.cpp
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#include "GaussianBlurFilter.h"


GaussianBlurFilter::GaussianBlurFilter(float width, float height, float blurSize, float bloom) :Abstract3x3PingPongFilter(width, height, ofVec2f(1, 1)) {
    _name = "Gaussian Blur";
    _blurSize = blurSize;
    _bloom = bloom;
    _addParameter(new ParameterF("blurSize", blurSize));
    _addParameter(new ParameterF("bloom", bloom));
    _setupShader();
}
GaussianBlurFilter::~GaussianBlurFilter() {}


void GaussianBlurFilter::onKeyPressed(int key) {
    if (key==OF_KEY_LEFT) _blurSize--;
    else if (key==OF_KEY_RIGHT) _blurSize++;
    else if (key==OF_KEY_UP) _bloom += 0.1;
    else if (key==OF_KEY_DOWN) _bloom -= 0.1;
    if (_blurSize<0) _blurSize = 0;
    if (_bloom<0) _bloom = 0;
    updateParameter("blurSize", _blurSize);
    updateParameter("bloom", _bloom);
}
void GaussianBlurFilter::onMousePressed(int button){
    if (_blurSize<0) _blurSize = 0;
    if (_bloom<0) _bloom = 0;
    updateParameter("blurSize", _blurSize);
    updateParameter("bloom", _bloom);
}

string GaussianBlurFilter::_getVertSrc() {
    return AbstractFilter::_getVertSrc();
}

string GaussianBlurFilter::_getFragSrc() {
    return GLSL_STRING(120,
        uniform sampler2D texture0;
        uniform float blurSize;
        uniform float bloom;
        uniform float texelWidthOffset;
        uniform float texelHeightOffset;

        void main() {
        float v;
        float pi = 3.141592653589793;
        float radius = blurSize;
        if ( radius < 0 ) radius = 0;
        int steps = int(min(radius * 0.7, sqrt(radius) * pi));
        float r = radius / steps;
        float t = bloom / (steps * 2 + 1);
        float x = gl_TexCoord[0].x;
        float y = gl_TexCoord[0].y;
        vec4 sum = texture2D(texture0, vec2(x, y)) * t;
        int i;
        for(i = 1; i <= steps; i++){
            v = (cos(i / (steps + 1) / pi) + 1) * 0.5;
            sum += texture2D(texture0, vec2(x + i * texelWidthOffset * r, y + i * texelHeightOffset * r)) * v * t;
            sum += texture2D(texture0, vec2(x - i * texelWidthOffset * r, y - i * texelHeightOffset * r)) * v * t;
        }

        gl_FragColor = sum;

    }
    );
}
#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
string GaussianBlurFilter::getTotalHelpString() {
    string sComplete= "Gaussian: " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    sComplete += " _blurSize: " + ofToString(_blurSize) + "; ";
    sComplete += " _bloom: " + ofToString(_bloom) + "; ";
    return sComplete;
}
void GaussianBlurFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
        ptr_gui->addSlider("_blurSize"+ofToString(i_ID), _blurSize, 0, 100.0);
        ptr_gui->addSlider("_bloom"+ofToString(i_ID), _bloom, 0, 100.0);

        if(bLoadSettings) ptr_gui->loadFromXML();
    }

}
#endif
