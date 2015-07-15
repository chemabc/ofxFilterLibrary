//
//  RemoveDimensionsFilter.cpp
//  filterSandbox
//
//  Created by Chema Blanco 2014/07/11
//  Based on Matthew Fargo on 2014/06/23.

//
//

#include "RemoveDimensionsFilter.h"


RemoveDimensionsFilter::RemoveDimensionsFilter(float width, float height) : AbstractFilter() {
    _name = "RemoveDimensions";
    _i_xMin = 0;
    _i_xMax = width;
    _i_yMin = 0;
    _i_yMax = height;


    _addParameter(new ParameterI("i_xMin", _i_xMin));
    _addParameter(new ParameterI("i_xMax", _i_xMax));
    _addParameter(new ParameterI("i_yMin", _i_yMin));
    _addParameter(new ParameterI("i_yMax", _i_yMax));
    _setupShader();

    ofLogVerbose("[RemoveDimensionsFilter:: constructor] end");
}
RemoveDimensionsFilter::~RemoveDimensionsFilter() {}


void RemoveDimensionsFilter::onKeyPressed(int key) {
//    if (key==OF_KEY_LEFT) _threshold--;
//    else if (key==OF_KEY_RIGHT) _threshold++;
    updateParameters();

}
void RemoveDimensionsFilter::onMousePressed(int button){
    updateParameters();
}

string RemoveDimensionsFilter::_getVertSrc() {
    return AbstractFilter::_getVertSrc();
}

string RemoveDimensionsFilter::_getFragSrc() {
    return GLSL_STRING(120,
         uniform sampler2D inputImageTexture;
         uniform int i_xMin;
         uniform int i_xMax;
         uniform int i_yMin;
         uniform int i_yMax;
        const vec3 W = vec3(0.2125, 0.7154, 0.0721);
    void main(){
            //Change into grayscale
            vec2 textureCoordinate = gl_TexCoord[0].xy;

            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            vec3 screenCoord = gl_FragCoord.xyz;
            vec4 finalColor = textureColor;

            if(screenCoord.x < i_xMin ||
               screenCoord.x > i_xMax ||
               screenCoord.y < i_yMin ||
               screenCoord.y > i_yMax
               )
            {
                finalColor.r = 1.0;
                finalColor.g = 1.0;
                finalColor.b = 1.0;
                finalColor.a = 0.0;
           }



            gl_FragColor = finalColor;


    }
    );
}

void RemoveDimensionsFilter::updateParameters(){
    if (_i_xMin<REMOVEFILTER_MIN_DIM) _i_xMin = REMOVEFILTER_MIN_DIM;
    if (_i_xMin>REMOVEFILTER_MAX_DIM) _i_xMin = REMOVEFILTER_MAX_DIM;

    if (_i_xMax<REMOVEFILTER_MIN_DIM) _i_xMax = REMOVEFILTER_MIN_DIM;
    if (_i_xMax>REMOVEFILTER_MAX_DIM) _i_xMax = REMOVEFILTER_MAX_DIM;

    if (_i_yMin<REMOVEFILTER_MIN_DIM) _i_yMin = REMOVEFILTER_MIN_DIM;
    if (_i_yMin>REMOVEFILTER_MAX_DIM) _i_yMin = REMOVEFILTER_MAX_DIM;

    if (_i_yMax<REMOVEFILTER_MIN_DIM) _i_yMax = REMOVEFILTER_MIN_DIM;
    if (_i_yMax>REMOVEFILTER_MAX_DIM) _i_yMax = REMOVEFILTER_MAX_DIM;

    updateParameter("i_xMin", _i_xMin);
    updateParameter("i_xMax", _i_xMax);
    updateParameter("i_yMin", _i_yMin);
    updateParameter("i_yMax", _i_yMax);

}
#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/

string RemoveDimensionsFilter::getTotalHelpString() {
   string sComplete= _name + ": " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    sComplete += " _i_xMin: " + ofToString(_i_xMin) + "; ";
    sComplete += " _i_xMax: " + ofToString(_i_xMax) + "; ";
    sComplete += " _i_yMin: " + ofToString(_i_yMin) + "; ";
    sComplete += " _i_yMax: " + ofToString(_i_yMax) + "; ";

    return sComplete;
}
void RemoveDimensionsFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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

        ptr_gui->addSlider("_i_xMin"+ofToString(i_ID), _i_xMin, REMOVEFILTER_MIN_DIM, REMOVEFILTER_MAX_DIM);
        ptr_gui->addSlider("_i_xMax"+ofToString(i_ID), _i_xMax, REMOVEFILTER_MIN_DIM, REMOVEFILTER_MAX_DIM);
        ptr_gui->addSlider("_i_yMin"+ofToString(i_ID), _i_yMin, REMOVEFILTER_MIN_DIM, REMOVEFILTER_MAX_DIM);
        ptr_gui->addSlider("_i_yMax"+ofToString(i_ID), _i_yMax, REMOVEFILTER_MIN_DIM, REMOVEFILTER_MAX_DIM);



        if(bLoadSettings){
            ptr_gui->loadFromXML();
            updateParameters();
        }
    }

}
#endif
