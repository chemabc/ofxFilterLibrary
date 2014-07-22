//
//  ErosionFilter.cpp
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/25.
//
//

#include "ErosionFilter.h"

ErosionFilter::ErosionFilter(float width, float height, int erosionRadius) : Abstract3x3PingPongFilter(width, height, ofVec2f(erosionRadius, erosionRadius)) {
    _setupShader();
     _name = "Erosion";
}
ErosionFilter::~ErosionFilter() {}



void ErosionFilter::onKeyPressed(int key) {
    int erosion = getErosionRadius();
    if (key==OF_KEY_DOWN) erosion--;
    else if (key==OF_KEY_UP) erosion++;
    if (erosion<1) erosion = 1;
    if (erosion>4) erosion = 4;
    setErosionRadius(erosion);
    f_erosionRadius = erosion;
}
void ErosionFilter::onMousePressed(int button){
    setErosionRadius(f_erosionRadius);

}

void ErosionFilter::setErosionRadius(int erosionRadius) {
    _texelSpacing.x = erosionRadius;
    _texelSpacing.y = erosionRadius;
}

string ErosionFilter::_getFragSrc() {
    return _getFragSrcForRadius(_texelSpacing.x);
}

string ErosionFilter::_getVertSrc() {
    return _getVertSrcForRadius(_texelSpacing.x);
}

string ErosionFilter::_getVertSrcForRadius(int radius) {
    switch (radius) {
        case 1:
            return GLSL_STRING(120,

                               uniform float texelWidthOffset;
                               uniform float texelHeightOffset;

                               varying vec2 centerTextureCoordinate;
                               varying vec2 oneStepPositiveTextureCoordinate;
                               varying vec2 oneStepNegativeTextureCoordinate;

                               void main()
                               {
                                   gl_TexCoord[0] = gl_MultiTexCoord0;
                                   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

                                   vec2 offset = vec2(texelWidthOffset, texelHeightOffset);

                                   centerTextureCoordinate = gl_TexCoord[0].xy;
                                   oneStepNegativeTextureCoordinate = centerTextureCoordinate - offset;
                                   oneStepPositiveTextureCoordinate = centerTextureCoordinate + offset;
                               }
                               );
            break;
        case 2:
            return GLSL_STRING(120,
                               uniform float texelWidthOffset;
                               uniform float texelHeightOffset;

                               varying vec2 centerTextureCoordinate;
                               varying vec2 oneStepPositiveTextureCoordinate;
                               varying vec2 oneStepNegativeTextureCoordinate;
                               varying vec2 twoStepsPositiveTextureCoordinate;
                               varying vec2 twoStepsNegativeTextureCoordinate;

                               void main()
                               {
                                   gl_TexCoord[0] = gl_MultiTexCoord0;
                                   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

                                   vec2 offset = vec2(texelWidthOffset, texelHeightOffset);

                                   centerTextureCoordinate = gl_TexCoord[0].xy;
                                   oneStepNegativeTextureCoordinate = centerTextureCoordinate - offset;
                                   oneStepPositiveTextureCoordinate = centerTextureCoordinate + offset;
                                   twoStepsNegativeTextureCoordinate = centerTextureCoordinate - (offset * 2.0);
                                   twoStepsPositiveTextureCoordinate = centerTextureCoordinate + (offset * 2.0);
                               }
                               );
            break;
        case 3:
            return GLSL_STRING(120,

                               uniform float texelWidthOffset;
                               uniform float texelHeightOffset;

                               varying vec2 centerTextureCoordinate;
                               varying vec2 oneStepPositiveTextureCoordinate;
                               varying vec2 oneStepNegativeTextureCoordinate;
                               varying vec2 twoStepsPositiveTextureCoordinate;
                               varying vec2 twoStepsNegativeTextureCoordinate;
                               varying vec2 threeStepsPositiveTextureCoordinate;
                               varying vec2 threeStepsNegativeTextureCoordinate;

                               void main()
                               {
                                   gl_TexCoord[0] = gl_MultiTexCoord0;
                                   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

                                   vec2 offset = vec2(texelWidthOffset, texelHeightOffset);

                                   centerTextureCoordinate = gl_TexCoord[0].xy;
                                   oneStepNegativeTextureCoordinate = centerTextureCoordinate - offset;
                                   oneStepPositiveTextureCoordinate = centerTextureCoordinate + offset;
                                   twoStepsNegativeTextureCoordinate = centerTextureCoordinate - (offset * 2.0);
                                   twoStepsPositiveTextureCoordinate = centerTextureCoordinate + (offset * 2.0);
                                   threeStepsNegativeTextureCoordinate = centerTextureCoordinate - (offset * 3.0);
                                   threeStepsPositiveTextureCoordinate = centerTextureCoordinate + (offset * 3.0);
                               }
                               );
            break;
        default:
            return GLSL_STRING(120,
                               attribute vec4 position;
                               attribute vec2 inputTextureCoordinate;

                               uniform float texelWidthOffset;
                               uniform float texelHeightOffset;

                               varying vec2 centerTextureCoordinate;
                               varying vec2 oneStepPositiveTextureCoordinate;
                               varying vec2 oneStepNegativeTextureCoordinate;
                               varying vec2 twoStepsPositiveTextureCoordinate;
                               varying vec2 twoStepsNegativeTextureCoordinate;
                               varying vec2 threeStepsPositiveTextureCoordinate;
                               varying vec2 threeStepsNegativeTextureCoordinate;
                               varying vec2 fourStepsPositiveTextureCoordinate;
                               varying vec2 fourStepsNegativeTextureCoordinate;

                               void main() {
                                   gl_TexCoord[0] = gl_MultiTexCoord0;
                                   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

                                   vec2 offset = vec2(texelWidthOffset, texelHeightOffset);

                                   centerTextureCoordinate = gl_TexCoord[0].xy;
                                   oneStepNegativeTextureCoordinate = centerTextureCoordinate - offset;
                                   oneStepPositiveTextureCoordinate = centerTextureCoordinate + offset;
                                   twoStepsNegativeTextureCoordinate = centerTextureCoordinate - (offset * 2.0);
                                   twoStepsPositiveTextureCoordinate = centerTextureCoordinate + (offset * 2.0);
                                   threeStepsNegativeTextureCoordinate = centerTextureCoordinate - (offset * 3.0);
                                   threeStepsPositiveTextureCoordinate = centerTextureCoordinate + (offset * 3.0);
                                   fourStepsNegativeTextureCoordinate = centerTextureCoordinate - (offset * 4.0);
                                   fourStepsPositiveTextureCoordinate = centerTextureCoordinate + (offset * 4.0);
                               }
                               );
            break;


    }
}

string ErosionFilter::_getFragSrcForRadius(int radius) {
    switch (radius) {
        case 1:
        return GLSL_STRING(120,
                           varying vec2 centerTextureCoordinate;
                           varying vec2 oneStepPositiveTextureCoordinate;
                           varying vec2 oneStepNegativeTextureCoordinate;

                           uniform sampler2D inputImageTexture;

                           void main()
                           {
                               float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
                               float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
                               float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;

                               float minValue = min(centerIntensity, oneStepPositiveIntensity);
                               minValue = min(minValue, oneStepNegativeIntensity);

                               gl_FragColor = vec4(vec3(minValue), 1.0);
                           }
                           );
            break;
        case 2:
            return GLSL_STRING(120,
                               varying vec2 centerTextureCoordinate;
                               varying vec2 oneStepPositiveTextureCoordinate;
                               varying vec2 oneStepNegativeTextureCoordinate;
                               varying vec2 twoStepsPositiveTextureCoordinate;
                               varying vec2 twoStepsNegativeTextureCoordinate;

                               uniform sampler2D inputImageTexture;

                               void main()
                               {
                                   float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
                                   float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
                                   float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;
                                   float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;
                                   float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;

                                   float minValue = min(centerIntensity, oneStepPositiveIntensity);
                                   minValue = min(minValue, oneStepNegativeIntensity);
                                   minValue = min(minValue, twoStepsPositiveIntensity);
                                   minValue = min(minValue, twoStepsNegativeIntensity);

                                   gl_FragColor = vec4(vec3(minValue), 1.0);
                               }
                               );
        case 3:
            return GLSL_STRING(120,
                               varying vec2 centerTextureCoordinate;
                               varying vec2 oneStepPositiveTextureCoordinate;
                               varying vec2 oneStepNegativeTextureCoordinate;
                               varying vec2 twoStepsPositiveTextureCoordinate;
                               varying vec2 twoStepsNegativeTextureCoordinate;
                               varying vec2 threeStepsPositiveTextureCoordinate;
                               varying vec2 threeStepsNegativeTextureCoordinate;

                               uniform sampler2D inputImageTexture;

                               void main()
                               {
                                   float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
                                   float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
                                   float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;
                                   float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;
                                   float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;
                                   float threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate).r;
                                   float threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate).r;

                                   float minValue = min(centerIntensity, oneStepPositiveIntensity);
                                   minValue = min(minValue, oneStepNegativeIntensity);
                                   minValue = min(minValue, twoStepsPositiveIntensity);
                                   minValue = min(minValue, twoStepsNegativeIntensity);
                                   minValue = min(minValue, threeStepsPositiveIntensity);
                                   minValue = min(minValue, threeStepsNegativeIntensity);

                                   gl_FragColor = vec4(vec3(minValue), 1.0);
                               }
                               );
            break;
        default:
            return GLSL_STRING(120,
                               varying vec2 centerTextureCoordinate;
                               varying vec2 oneStepPositiveTextureCoordinate;
                               varying vec2 oneStepNegativeTextureCoordinate;
                               varying vec2 twoStepsPositiveTextureCoordinate;
                               varying vec2 twoStepsNegativeTextureCoordinate;
                               varying vec2 threeStepsPositiveTextureCoordinate;
                               varying vec2 threeStepsNegativeTextureCoordinate;
                               varying vec2 fourStepsPositiveTextureCoordinate;
                               varying vec2 fourStepsNegativeTextureCoordinate;

                               uniform sampler2D inputImageTexture;

                               void main()
                               {
                                   float centerIntensity = texture2D(inputImageTexture, centerTextureCoordinate).r;
                                   float oneStepPositiveIntensity = texture2D(inputImageTexture, oneStepPositiveTextureCoordinate).r;
                                   float oneStepNegativeIntensity = texture2D(inputImageTexture, oneStepNegativeTextureCoordinate).r;
                                   float twoStepsPositiveIntensity = texture2D(inputImageTexture, twoStepsPositiveTextureCoordinate).r;
                                   float twoStepsNegativeIntensity = texture2D(inputImageTexture, twoStepsNegativeTextureCoordinate).r;
                                   float threeStepsPositiveIntensity = texture2D(inputImageTexture, threeStepsPositiveTextureCoordinate).r;
                                   float threeStepsNegativeIntensity = texture2D(inputImageTexture, threeStepsNegativeTextureCoordinate).r;
                                   float fourStepsPositiveIntensity = texture2D(inputImageTexture, fourStepsPositiveTextureCoordinate).r;
                                   float fourStepsNegativeIntensity = texture2D(inputImageTexture, fourStepsNegativeTextureCoordinate).r;

                                   float minValue = min(centerIntensity, oneStepPositiveIntensity);
                                   minValue = min(minValue, oneStepNegativeIntensity);
                                   minValue = min(minValue, twoStepsPositiveIntensity);
                                   minValue = min(minValue, twoStepsNegativeIntensity);
                                   minValue = min(minValue, threeStepsPositiveIntensity);
                                   minValue = min(minValue, threeStepsNegativeIntensity);
                                   minValue = min(minValue, fourStepsPositiveIntensity);
                                   minValue = min(minValue, fourStepsNegativeIntensity);

                                   gl_FragColor = vec4(vec3(minValue), 1.0);
                               }
                               );
            break;
    }
}
#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
string ErosionFilter::getTotalHelpString() {
    string sComplete= _name + ": " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    sComplete += " f_erosionRadius: " + ofToString(f_erosionRadius) + "; ";
    return sComplete;
}
void ErosionFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
        ptr_gui->addSlider("f_erosionRadius"+ofToString(i_ID), f_erosionRadius, 0, 100.0);


        if(bLoadSettings) ptr_gui->loadFromXML();
    }

}
#endif
