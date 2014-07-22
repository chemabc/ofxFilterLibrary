//
//  LowPassFilter.cpp
//  ofxFilterLibraryExample
//
//  Created by Matthew Fargo on 2014/06/30.
//
//

#include "LowPassFilter.h"

LowPassFilter::LowPassFilter(float width, float height, float mix) : DissolveBlendFilter(width, height, mix) {
    _name = "Low Pass";
    _buffer.allocate(getWidth(), getHeight());
    setSecondTexture(_buffer.getTextureReference());
}
LowPassFilter::~LowPassFilter() {}

void LowPassFilter::begin() {
    #ifdef _APPGC_OFXSIMPLEGUITOO
    if(_b_activeFilter){
    #endif
    ofSetColor(255);
    _buffer.begin();
    DissolveBlendFilter::begin();
    #ifdef _APPGC_OFXSIMPLEGUITOO
    }
    #endif
}

void LowPassFilter::end() {
    #ifdef _APPGC_OFXSIMPLEGUITOO
    if(_b_activeFilter){
    #endif
    DissolveBlendFilter::end();
    _buffer.end();
    ofSetColor(255);
    _buffer.draw(0, 0);
    #ifdef _APPGC_OFXSIMPLEGUITOO
    }
    #endif
}

#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
string LowPassFilter::getTotalHelpString() {
    string sComplete= _name + ": " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    return sComplete;
}
void LowPassFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
    DissolveBlendFilter::setupGui(gui,userGuiPage, bUsePageNameAsATitle, bLoadSettings);
//    ptr_gui = gui;
//    s_userGuiPage=_name+"_"+ofToString(i_ID);
//    if(ptr_gui!=0){
//        if(userGuiPage == ""){
//
//            if(bUsePageNameAsATitle){
//                ptr_gui->addTitle(s_userGuiPage);
//            }
//            else{
//                ptr_gui->addPage(s_userGuiPage);
//            }
//        }else{
//            if(bUsePageNameAsATitle){
//                ptr_gui->addTitle(userGuiPage);
//            }
//            else{
//                ptr_gui->setPage(userGuiPage);
//                ptr_gui->addTitle(s_userGuiPage);
//            }
//        }
//        ptr_gui->addToggle("_b_activeFilter_"+ofToString(i_ID), _b_activeFilter);
//        if(bLoadSettings) ptr_gui->loadFromXML();
//    }

}


#endif
