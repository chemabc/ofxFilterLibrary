//
//  ToonFilter.cpp
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#include "ToonFilter.h"

ToonFilter::ToonFilter(float width, float height, float threshold, float quantizationLevels) : AbstractFilter(width, height) {
    _name = "Toon";
    _threshold = threshold;
    _quantizationLevels = quantizationLevels;
    _addParameter(new ParameterF("texelWidth", 1.f/getWidth()));
    _addParameter(new ParameterF("texelHeight", 1.f/getHeight()));
    _addParameter(new ParameterF("threshold", _threshold));
    _addParameter(new ParameterF("quantizationLevels", _quantizationLevels));
    _setupShader();
}
ToonFilter::~ToonFilter() {}

void ToonFilter::onKeyPressed(int key) {
//    if (key==OF_KEY_UP) _quantizationLevels ++;
//    else if (key==OF_KEY_DOWN) _quantizationLevels--;
//    else if (key==OF_KEY_LEFT) _threshold-=0.1f;
//    else if (key==OF_KEY_RIGHT) _threshold+=0.1f;
    updateParameters();
}
void ToonFilter::onMousePressed(int button){
    updateParameters();
}


string ToonFilter::_getFragSrc() {
    return GLSL_STRING(120,
        varying vec2 leftTextureCoordinate;
        varying vec2 rightTextureCoordinate;

        varying vec2 topTextureCoordinate;
        varying vec2 topLeftTextureCoordinate;
        varying vec2 topRightTextureCoordinate;

        varying vec2 bottomTextureCoordinate;
        varying vec2 bottomLeftTextureCoordinate;
        varying vec2 bottomRightTextureCoordinate;

        uniform sampler2D inputImageTexture;

        uniform float intensity;
        uniform float threshold;
        uniform float quantizationLevels;

        const vec3 W = vec3(0.2125, 0.7154, 0.0721);

        void main() {
            vec2 textureCoordinate = gl_TexCoord[0].xy;
            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

            float bottomLeftIntensity = texture2D(inputImageTexture, bottomLeftTextureCoordinate).r;
            float topRightIntensity = texture2D(inputImageTexture, topRightTextureCoordinate).r;
            float topLeftIntensity = texture2D(inputImageTexture, topLeftTextureCoordinate).r;
            float bottomRightIntensity = texture2D(inputImageTexture, bottomRightTextureCoordinate).r;
            float leftIntensity = texture2D(inputImageTexture, leftTextureCoordinate).r;
            float rightIntensity = texture2D(inputImageTexture, rightTextureCoordinate).r;
            float bottomIntensity = texture2D(inputImageTexture, bottomTextureCoordinate).r;
            float topIntensity = texture2D(inputImageTexture, topTextureCoordinate).r;
            float h = -topLeftIntensity - 2.0 * topIntensity - topRightIntensity + bottomLeftIntensity + 2.0 * bottomIntensity + bottomRightIntensity;
            float v = -bottomLeftIntensity - 2.0 * leftIntensity - topLeftIntensity + bottomRightIntensity + 2.0 * rightIntensity + topRightIntensity;

            float mag = length(vec2(h, v));

            vec3 posterizedImageColor = floor((textureColor.rgb * quantizationLevels) + 0.5) / quantizationLevels;

            float thresholdTest = 1.0 - step(threshold, mag);

            gl_FragColor = vec4(posterizedImageColor * thresholdTest, textureColor.a);
        }
    );
}
string ToonFilter::_getVertSrc() {
    return GLSL_STRING(120,
        uniform float texelWidth;
        uniform float texelHeight;

        varying vec2 leftTextureCoordinate;
        varying vec2 rightTextureCoordinate;

        varying vec2 topTextureCoordinate;
        varying vec2 topLeftTextureCoordinate;
        varying vec2 topRightTextureCoordinate;

        varying vec2 bottomTextureCoordinate;
        varying vec2 bottomLeftTextureCoordinate;
        varying vec2 bottomRightTextureCoordinate;

        void main() {
            gl_TexCoord[0] = gl_MultiTexCoord0;
            gl_Position = ftransform();

            vec2 widthStep = vec2(texelWidth, 0.0);
            vec2 heightStep = vec2(0.0, texelHeight);
            vec2 widthHeightStep = vec2(texelWidth, texelHeight);
            vec2 widthNegativeHeightStep = vec2(texelWidth, -texelHeight);

            //textureCoordinate = inputTextureCoordinate.xy;
            vec2 textureCoordinate = vec2(gl_MultiTexCoord0);
            leftTextureCoordinate = textureCoordinate - widthStep;
            rightTextureCoordinate = textureCoordinate + widthStep;

            topTextureCoordinate = textureCoordinate - heightStep;
            topLeftTextureCoordinate = textureCoordinate - widthHeightStep;
            topRightTextureCoordinate = textureCoordinate + widthNegativeHeightStep;

            bottomTextureCoordinate = textureCoordinate + heightStep;
            bottomLeftTextureCoordinate = textureCoordinate - widthNegativeHeightStep;
            bottomRightTextureCoordinate = textureCoordinate + widthHeightStep;
        }
    );
}

void ToonFilter::updateParameters(){
    if (_quantizationLevels<0) _quantizationLevels = 0;
  if (_threshold<0) _threshold = 0;
  updateParameter("quantizationLevels", _quantizationLevels);
  updateParameter("threshold", _threshold);
}

#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
string ToonFilter::getTotalHelpString() {
    string sComplete= _name + ": " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    sComplete += " _threshold: " + ofToString(_threshold) + "; " ;
    sComplete += " _quantizationLevels: " + ofToString(_quantizationLevels) + "; " ;
    return sComplete;
}
void ToonFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
        ptr_gui->addSlider("_threshold_"+ofToString(i_ID), _threshold, 0, 4.0);
        ptr_gui->addSlider("_quantizationLevels_"+ofToString(i_ID), _quantizationLevels, 0, 50.0);


        if(bLoadSettings) {
            ptr_gui->loadFromXML();
            updateParameters();
        }
    }

}
#endif
