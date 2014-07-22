//
//  VignetteFilter.cpp
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#include "VignetteFilter.h"

VignetteFilter::VignetteFilter() : AbstractFilter(0, 0) {
    _name = "Vignette";
    _addParameter(new Parameter2f("vignetteCenter", ofVec2f(0.5, 0.5) ));
    _addParameter(new Parameter3f("vignetteColor", ofVec3f(0, 0, 0)));
    _addParameter(new ParameterF("vignetteStart", 0.3));
    _addParameter(new ParameterF("vignetteEnd", 0.75));
    _setupShader();
}
VignetteFilter::~VignetteFilter() {}



string VignetteFilter::_getFragSrc() {
    return GLSL_STRING(120,
        uniform sampler2D inputImageTexture;

        uniform vec2 vignetteCenter;
        uniform vec3 vignetteColor;
        uniform float vignetteStart;
        uniform float vignetteEnd;

        void main() {
            vec2 uv = gl_TexCoord[0].xy;
            vec4 sourceImageColor = texture2D(inputImageTexture, uv);
            float d = distance(uv, vec2(vignetteCenter.x, vignetteCenter.y));
            float percent = smoothstep(vignetteStart, vignetteEnd, d);
            gl_FragColor = vec4(mix(sourceImageColor.rgb, vignetteColor, percent), sourceImageColor.a);
        }
    );
}

#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/

string VignetteFilter::getTotalHelpString() {
    string sComplete= _name + ": " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    //sComplete += " _radius: " + ofToString(_radius);
    return sComplete;
}
void VignetteFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
