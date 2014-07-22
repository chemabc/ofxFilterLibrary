//
//  PosterizeFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#ifndef __filterSandbox__PosterizeFilter__
#define __filterSandbox__PosterizeFilter__

#include "AbstractFilter.h"

class PosterizeFilter : public AbstractFilter {
public:
	PosterizeFilter(float width, float height, float gamma=0.6f, float numColors=8.f);
	virtual ~PosterizeFilter();

    virtual void    onKeyPressed(int key);
    virtual void    onMousePressed(int button);

    virtual string  getInstructions() { return "Left and Right change gamma: " + ofToString(_gamma) + "\nUp and Down change num colors: " + ofToString(_numColors); }
    virtual void updateParameters();

#ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
virtual string getTotalHelpString();
	#endif

protected:
    virtual string  _getVertSrc();
    virtual string  _getFragSrc();
    float           _gamma;
    float           _numColors;

};

#endif /* defined(__filterSandbox__PosterizeFilter__) */
