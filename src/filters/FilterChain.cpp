//
//  FilterChain.cpp
//  GlassTextureTest
//
//  Created by Matthew Fargo on 2014/06/27.
//
//

#include "FilterChain.h"

FilterChain::FilterChain(float width, float height, string name) : AbstractFilter(width, height),AbstractPingPongRenderer(width, height) {
    _name = name;
    i_shitToDebug = 0;
        // don't set up shader, cuz there ain't neccesarily one
}
FilterChain::~FilterChain() {}


void FilterChain::begin() {
    if (_filters.size()<1) return;
    #ifdef _APPGC_OFXSIMPLEGUITOO
//    cout << "[FilterChain::end] Ping begin index 0 ("<< _filters[0]->isActive()<<"): " <<i_shitToDebug << endl;
    #endif
    _ping.begin();
    ofClear(0, 0, 0, 0);
    _filters[0]->begin();


}

void FilterChain::end() {
    _filters[0]->end();
    _ping.end();
    #ifdef _APPGC_OFXSIMPLEGUITOO
//    cout << "[FilterChain::end] Ping end index 0 ("<< _filters[0]->isActive()<<"): " <<i_shitToDebug << endl;
    #endif



    int filterIndex = 1;
    while (filterIndex<_filters.size()) {
        if (filterIndex%2==1) _pong.begin(); //Si el índice es par
        else _ping.begin(); //Si es impar
        ofClear(0, 0, 0, 0);

        _filters[filterIndex]->begin();
        if (filterIndex%2==1) _ping.draw(0,0);
        else _pong.draw(0,0);
        _filters[filterIndex]->end();

        if (filterIndex%2==1) _pong.end();
        else _ping.end();
        filterIndex++;
    }
    if (filterIndex%2==1) _ping.draw(0,0);
    else _pong.draw(0,0);


    i_shitToDebug++;

}

#ifdef _APPGC_OFXSIMPLEGUITOO
string FilterChain::getTotalHelpString() {
    string sComplete= "Chain " + this->getName() +"("+ofToString(_filters.size())+")" +"\n";
    for(int i= 0; i < _filters.size(); i++){
        sComplete += "      - Filter (" + ofToString(i) + "/" + ofToString( _filters.size()-1)+") " + _filters[i]->getTotalHelpString() + "\n";
    }

    return sComplete;
}
void FilterChain::onKeyPressed(int key) {
    for(int i= 0; i < _filters.size(); i++){
        _filters[i]->onKeyPressed(key);
    }
}
void FilterChain::onMousePressed(int button){
     for(int i= 0; i < _filters.size(); i++){
        _filters[i]->onMousePressed(button);
    }
}

/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
void FilterChain::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
    ptr_gui = gui;
    s_userGuiPage=_name+"_"+ofToString(i_ID);
    if(ptr_gui!=0){
        if(userGuiPage == ""){

            if(bUsePageNameAsATitle){
                //ptr_gui->addTitle(s_userGuiPage, true);
                ptr_gui->addTitle(s_userGuiPage);
            }
            else{
                ptr_gui->addPage(s_userGuiPage);
            }
        }else{
            if(bUsePageNameAsATitle){
                //ptr_gui->addTitle(userGuiPage, true);
                ptr_gui->addTitle(userGuiPage);
            }
            else{
                ptr_gui->setPage(userGuiPage);
                //ptr_gui->addTitle(s_userGuiPage, true);
                ptr_gui->addTitle(s_userGuiPage);
            }
        }

        if(bLoadSettings) ptr_gui->loadFromXML();
    }
}
#endif
