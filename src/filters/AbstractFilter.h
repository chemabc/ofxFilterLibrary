//
//  AbstractFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#ifndef __filterSandbox__AbstractFilter__
#define __filterSandbox__AbstractFilter__

#define GLSL_STRING(version, shader)  "#version " #version "\n" #shader

#include "ParametricObject.h"

#include "defines_main.h"
#ifdef _APPGC_OFXSIMPLEGUITOO
    #include "ofxSimpleGuiToo.h"
#endif


class AbstractFilter : public ParametricObject {
public:

	AbstractFilter(float width=0, float height=0);
	virtual ~AbstractFilter();

    virtual void    begin();
    virtual void    end();

    virtual void    onKeyPressed(int key) {}  // abstract
    virtual void    onMousePressed(int button) {}  // abstract

    float           getWidth() { return _width; }
    float           getHeight() { return _height; }
    virtual void    setWidth(float width) { _width = width; }
    virtual void    setHeight(float height) { _height = height; }
    virtual string  getInstructions() { return ""; }
    ofShader &      getShader() { return _shader; }
    virtual void updateParameters(){};

    #ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
    virtual string getTotalHelpString() {return "";};
    bool isActive(){return _b_activeFilter;};
    void setActive(bool b){_b_activeFilter=b;};

    #endif

protected:
    static int i_count_instances;
    virtual void    _setupShader();
    virtual string  _getFragSrc();  // override these
    virtual string  _getVertSrc();  // with yr shader src


    ofShader        _shader;
    #ifdef _APPGC_OFXSIMPLEGUITOO
    int i_ID;
    ofxSimpleGuiToo *ptr_gui;
    string s_userGuiPage;
     bool            _b_activeFilter;
    #endif

private:
    float           _width;
    float           _height;



};

#endif /* defined(__filterSandbox__AbstractFilter__) */
