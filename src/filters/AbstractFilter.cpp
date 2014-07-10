//
//  AbstractFilter.cpp
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#include "AbstractFilter.h"

#ifdef _APPGC_OFXSIMPLEGUITOO
int AbstractFilter::i_count_instances = 0;
#endif

AbstractFilter::AbstractFilter(float width, float height) {
    setWidth(width);
    setHeight(height);
    #ifdef _APPGC_OFXSIMPLEGUITOO
    i_ID = i_count_instances;
    i_count_instances++;
    _b_activeFilter = true;
    #endif
}


AbstractFilter::~AbstractFilter() {}

void AbstractFilter::_setupShader() {
    if (_shader.isLoaded()) _shader.unload();
    _shader.setupShaderFromSource(GL_VERTEX_SHADER, _getVertSrc());
    _shader.setupShaderFromSource(GL_FRAGMENT_SHADER, _getFragSrc());
    _shader.linkProgram();
}

void AbstractFilter::begin() {
    #ifdef _APPGC_OFXSIMPLEGUITOO
    if(_b_activeFilter){
    #endif
        _shader.begin();
    #ifdef _APPGC_OFXSIMPLEGUITOO
    }
    #endif
        _updateParameters(&_shader);

}

void AbstractFilter::end() {
    #ifdef _APPGC_OFXSIMPLEGUITOO
    if(_b_activeFilter){
    #endif
        _shader.end();
    #ifdef _APPGC_OFXSIMPLEGUITOO
    }
    #endif
}


string AbstractFilter::_getFragSrc() {
    return GLSL_STRING(120,
        uniform sampler2D inputImageTexture;

        void main() {
            vec2 uv = gl_TexCoord[0].xy;
            gl_FragColor = texture2D(inputImageTexture, uv );
        }
    );
}

string AbstractFilter::_getVertSrc() {
    return GLSL_STRING(120,
       void main() {
           gl_TexCoord[0] = gl_MultiTexCoord0;
           gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
           //gl_Position = ftransform();  // not using this cuz we might blend later
       }
    );
}


#ifdef _APPGC_OFXSIMPLEGUITOO
//void AbstractFilter::updateParameters(){
//
//}
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
void AbstractFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
        ptr_gui->addToggle("_b_activeFilter", _b_activeFilter);
        if(bLoadSettings) ptr_gui->loadFromXML();
    }
}
#endif
