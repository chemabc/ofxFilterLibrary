//
//  HSVControlFilter.cpp
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#include "HSVControlFilter.h"


HSVControlFilter::HSVControlFilter(float width, float height) : AbstractFilter() {
    _name = "HSV Control";
    _hue = 0.0;
    _saturation = 0.0;
    _brightness = 0.0;
    _addParameter(new ParameterF("hue", _hue));
    _addParameter(new ParameterF("saturation", _saturation));
    _addParameter(new ParameterF("brightness", _brightness));

    _setupShader();
}
HSVControlFilter::~HSVControlFilter() {}


void HSVControlFilter::onKeyPressed(int key) {
    updateParameters();

}
void HSVControlFilter::onMousePressed(int button){
  updateParameters();
}

string HSVControlFilter::_getVertSrc() {
    return AbstractFilter::_getVertSrc();
}

string HSVControlFilter::_getFragSrc() {
    return GLSL_STRING(120,
        uniform sampler2D inputImageTexture;
        uniform float hue;
        uniform float saturation;
        uniform float brightness;
        const vec3 W = vec3(0.2125, 0.7154, 0.0721);

    vec3 rgb2hsv(vec3 c){
        vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
        vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));
        vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));

        float d = q.x - min(q.w, q.y);
        float e = 1.0e-10;
        return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
    }

    vec3 hsv2rgb(vec3 c){
        vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
        vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
        return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
    }

    void main(){
            //Change into grayscale
            vec2 textureCoordinate = gl_TexCoord[0].xy;
            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            vec3 hsv = rgb2hsv(vec3(textureColor.r,textureColor.g, textureColor.b) );
            vec3 finalColorHSV;
            finalColorHSV.r = hsv.r * hue;
            finalColorHSV.g = hsv.g * saturation;
            finalColorHSV.b = hsv.b * brightness;

            vec3 finalColorRGB = hsv2rgb(finalColorHSV);

            gl_FragColor = vec4(finalColorRGB.r, finalColorRGB.g, finalColorRGB.b, textureColor.a);

    }
    );
}

void HSVControlFilter::updateParameters(){
    updateParameter("hue", _hue);
    updateParameter("saturation", _saturation);
    updateParameter("brightness", _brightness);
}
#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
string HSVControlFilter::getTotalHelpString() {
    string sComplete= "HSV_Control: " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    sComplete += " _hue: " + ofToString(_hue) + "; ";
    sComplete += " _saturation: " + ofToString(_saturation) + "; ";
    sComplete += " _brightness: " + ofToString(_brightness) + "; ";
    return sComplete;
}
void HSVControlFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
        ptr_gui->addSlider("_hue_"+ofToString(i_ID), _hue, 0.0, 2.0);
        ptr_gui->addSlider("_saturation"+ofToString(i_ID), _saturation, 0.0, 2.0);
        ptr_gui->addSlider("_brightness"+ofToString(i_ID), _brightness, 0.0, 2.0);


        if(bLoadSettings){
            ptr_gui->loadFromXML();
            updateParameters();
        }
    }

}
#endif
