//
//  BilateralFilter.cpp
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/24.
//
//

#include "BilateralFilter.h"

BilateralFilter::BilateralFilter(float width, float height, float blurOffset, float normalization) : Abstract3x3PingPongFilter(width, height, ofVec2f(blurOffset, blurOffset)) {
    _name = "Bilateral";
    _normalization = normalization;
    _addParameter(new ParameterF("distanceNormalizationFactor", normalization));
    _setupShader();
}
BilateralFilter::~BilateralFilter() {}


void BilateralFilter::onKeyPressed(int key) {
//    float blurOffset = _texelSpacing.x;
//    if (key==OF_KEY_DOWN) blurOffset -= 0.5f;
//    else if (key==OF_KEY_UP) blurOffset += 0.5f;
//    else if (key==OF_KEY_LEFT) _normalization -=0.5;
//    else if (key==OF_KEY_RIGHT) _normalization += 0.5;
    updateParameters();
}
void BilateralFilter::onMousePressed(int button){
    updateParameters();

}
string BilateralFilter::_getFragSrc() {
    return GLSL_STRING(120,
        uniform sampler2D inputImageTexture;

        const int GAUSSIAN_SAMPLES = 9;

        varying vec2 textureCoordinate;
        varying vec2 blurCoordinates[GAUSSIAN_SAMPLES];

        uniform float distanceNormalizationFactor;

        void main()
        {
            vec4 centralColor;
            float gaussianWeightTotal;
            vec4 sum;
            vec4 sampleColor;
            float distanceFromCentralColor;
            float gaussianWeight;

            centralColor = texture2D(inputImageTexture, blurCoordinates[4]);
            gaussianWeightTotal = 0.18;
            sum = centralColor * 0.18;

            sampleColor = texture2D(inputImageTexture, blurCoordinates[0]);
            distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
            gaussianWeight = 0.05 * (1.0 - distanceFromCentralColor);
            gaussianWeightTotal += gaussianWeight;
            sum += sampleColor * gaussianWeight;

            sampleColor = texture2D(inputImageTexture, blurCoordinates[1]);
            distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
            gaussianWeight = 0.09 * (1.0 - distanceFromCentralColor);
            gaussianWeightTotal += gaussianWeight;
            sum += sampleColor * gaussianWeight;

            sampleColor = texture2D(inputImageTexture, blurCoordinates[2]);
            distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
            gaussianWeight = 0.12 * (1.0 - distanceFromCentralColor);
            gaussianWeightTotal += gaussianWeight;
            sum += sampleColor * gaussianWeight;

            sampleColor = texture2D(inputImageTexture, blurCoordinates[3]);
            distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
            gaussianWeight = 0.15 * (1.0 - distanceFromCentralColor);
            gaussianWeightTotal += gaussianWeight;
            sum += sampleColor * gaussianWeight;

            sampleColor = texture2D(inputImageTexture, blurCoordinates[5]);
            distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
            gaussianWeight = 0.15 * (1.0 - distanceFromCentralColor);
            gaussianWeightTotal += gaussianWeight;
            sum += sampleColor * gaussianWeight;

            sampleColor = texture2D(inputImageTexture, blurCoordinates[6]);
            distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
            gaussianWeight = 0.12 * (1.0 - distanceFromCentralColor);
            gaussianWeightTotal += gaussianWeight;
            sum += sampleColor * gaussianWeight;

            sampleColor = texture2D(inputImageTexture, blurCoordinates[7]);
            distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
            gaussianWeight = 0.09 * (1.0 - distanceFromCentralColor);
            gaussianWeightTotal += gaussianWeight;
            sum += sampleColor * gaussianWeight;

            sampleColor = texture2D(inputImageTexture, blurCoordinates[8]);
            distanceFromCentralColor = min(distance(centralColor, sampleColor) * distanceNormalizationFactor, 1.0);
            gaussianWeight = 0.05 * (1.0 - distanceFromCentralColor);
            gaussianWeightTotal += gaussianWeight;
            sum += sampleColor * gaussianWeight;

            gl_FragColor = sum / gaussianWeightTotal;
        }
    );
}
string BilateralFilter::_getVertSrc() {
    return GLSL_STRING(120,
        const int GAUSSIAN_SAMPLES = 9;

        uniform float texelWidthOffset;
        uniform float texelHeightOffset;

        varying vec2 textureCoordinate;
        varying vec2 blurCoordinates[GAUSSIAN_SAMPLES];

        void main() {
            textureCoordinate = vec2(gl_MultiTexCoord0);
            gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

            // Calculate the positions for the blur
            int multiplier = 0;
            vec2 blurStep;
            vec2 singleStepOffset = vec2(texelWidthOffset, texelHeightOffset);

            for (int i = 0; i < GAUSSIAN_SAMPLES; i++) {
                multiplier = (i - ((GAUSSIAN_SAMPLES - 1) / 2));
                blurStep = float(multiplier) * singleStepOffset;
                blurCoordinates[i] = textureCoordinate + blurStep;
            }
        }
    );
}
void BilateralFilter::updateParameters(){
    if (_blurOffset<0) _blurOffset = 0;
    if (_normalization<0) _normalization = 0;
    updateParameter("distanceNormalizationFactor", _normalization);
    _texelSpacing = ofVec2f(_blurOffset, _blurOffset);
}
#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/

string BilateralFilter::getTotalHelpString() {
    string sComplete= _name + ": " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    sComplete += " _blurOffset: " + ofToString(_texelSpacing.x) + "; " ;
    sComplete += " _normalization: " + ofToString(_normalization) + "; " ;
    return sComplete;
}
void BilateralFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
        ptr_gui->addSlider("_blurOffset", _blurOffset, 0, 20.0);
        ptr_gui->addSlider("_normalization", _normalization, 0.0, 20.0);

        if(bLoadSettings) {
                ptr_gui->loadFromXML();
                updateParameters();
        }
    }

}
#endif


