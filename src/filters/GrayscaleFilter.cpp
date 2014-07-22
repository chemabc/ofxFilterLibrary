//
//  GrayscaleFilter.cpp
//  ofxFilterLibraryExample
//
//  Created by Matthew Fargo on 2014/06/27.
//
//

#include "GrayscaleFilter.h"

GrayscaleFilter::GrayscaleFilter() : AbstractFilter() {
    _name = "Grayscale";
    _setupShader();
}

GrayscaleFilter::~GrayscaleFilter() {}


string GrayscaleFilter::_getFragSrc() {
    return GLSL_STRING(120,
        uniform sampler2D inputImageTexture;

        const vec3 W = vec3(0.2125, 0.7154, 0.0721);

        void main() {
            vec2 textureCoordinate = gl_TexCoord[0].xy;

            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            float luminance = dot(textureColor.rgb, W);

            gl_FragColor = vec4(vec3(luminance), textureColor.a);
        }
    );
}


#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
string GrayscaleFilter::getTotalHelpString() {
    string sComplete= _name + ": " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    return sComplete;
}
void GrayscaleFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
        if(bLoadSettings) ptr_gui->loadFromXML();
    }

}


#endif
