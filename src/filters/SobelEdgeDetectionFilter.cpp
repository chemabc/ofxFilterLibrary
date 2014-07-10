//
//  SobelEdgeDetectionFilter.cpp
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#include "SobelEdgeDetectionFilter.h"

SobelEdgeDetectionFilter::SobelEdgeDetectionFilter(float width, float height, float edgeStrength) : AbstractFilter(width, height) {
    _name = "Sobel Edge";
    _threshold = 0.0;
    _edgeStrength = edgeStrength;
    _addParameter(new ParameterF("edgeStrength", 1.f));
    _addParameter(new ParameterF("threshold", _threshold));
    _addParameter(new ParameterF("texelWidth", 1.f/getWidth()));
    _addParameter(new ParameterF("texelHeight", 1.f/getHeight()));
    _setupShader();
}
SobelEdgeDetectionFilter::~SobelEdgeDetectionFilter() {}

void SobelEdgeDetectionFilter::onKeyPressed(int key) {
    if (key==OF_KEY_LEFT) _edgeStrength-=0.1f;
    else if (key==OF_KEY_RIGHT) _edgeStrength+=0.1f;
    if (key==OF_KEY_DOWN) _threshold-=0.1f;
    else if (key==OF_KEY_UP) _threshold+=0.1f;
    if (_edgeStrength<0) _edgeStrength=0;
    if (_threshold<0) _threshold=0;
    updateParameter("edgeStrength", _edgeStrength);
    updateParameter("threshold", _threshold);
}
void SobelEdgeDetectionFilter::onMousePressed(int button){
    if (_edgeStrength<0) _edgeStrength=0;
    if (_threshold<0) _threshold=0;
    updateParameter("edgeStrength", _edgeStrength);
    updateParameter("threshold", _threshold);
}

string SobelEdgeDetectionFilter::_getFragSrc() {
    return GLSL_STRING(120,
        varying vec2 textureCoordinate;
        varying vec2 leftTextureCoordinate;
        varying vec2 rightTextureCoordinate;

        varying vec2 topTextureCoordinate;
        varying vec2 topLeftTextureCoordinate;
        varying vec2 topRightTextureCoordinate;

        varying vec2 bottomTextureCoordinate;
        varying vec2 bottomLeftTextureCoordinate;
        varying vec2 bottomRightTextureCoordinate;

        uniform sampler2D inputImageTexture;
        uniform float edgeStrength;
        uniform float threshold;

        void main() {
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

            float mag = length(vec2(h, v)) * edgeStrength;
            if(threshold != 0.0){
                if(mag > threshold){
                    mag = 1.0;
                }else mag = 0.0;
            }

            gl_FragColor = vec4(vec3(mag), 1.0);
        }
    );
}

string SobelEdgeDetectionFilter::_getVertSrc() {
    return GLSL_STRING(120,
         uniform float texelWidth;
         uniform float texelHeight;

         varying vec2 textureCoordinate;
         varying vec2 leftTextureCoordinate;
         varying vec2 rightTextureCoordinate;

         varying vec2 topTextureCoordinate;
         varying vec2 topLeftTextureCoordinate;
         varying vec2 topRightTextureCoordinate;

         varying vec2 bottomTextureCoordinate;
         varying vec2 bottomLeftTextureCoordinate;
         varying vec2 bottomRightTextureCoordinate;

         void main() {
             //gl_Position = position;
             gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

             vec2 widthStep = vec2(texelWidth, 0.0);
             vec2 heightStep = vec2(0.0, texelHeight);
             vec2 widthHeightStep = vec2(texelWidth, texelHeight);
             vec2 widthNegativeHeightStep = vec2(texelWidth, -texelHeight);

             //textureCoordinate = inputTextureCoordinate.xy;
             textureCoordinate = vec2(gl_MultiTexCoord0);
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
#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/

string SobelEdgeDetectionFilter::getTotalHelpString() {
    string sComplete= "Sobel: " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    sComplete += " _edgeStrength: " + ofToString(_edgeStrength) + "; " ;
    sComplete += " _threshold: " + ofToString(_threshold) + "; " ;

    return sComplete;
}
void SobelEdgeDetectionFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
        ptr_gui->addSlider("_edgeStrength", _edgeStrength, 0, 5.0);
        ptr_gui->addSlider("_threshold", _threshold, 0.0, 1.0);


        if(bLoadSettings) ptr_gui->loadFromXML();
    }

}
#endif
