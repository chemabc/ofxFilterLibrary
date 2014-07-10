//
//  ThresholdFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#ifndef __filterSandbox__ThresholdFilter__
#define __filterSandbox__ThresholdFilter__

#include "AbstractFilter.h"

class ThresholdFilter : public AbstractFilter {
public:
	ThresholdFilter(float width, float height,
                 float threshold = 0.0);
	virtual ~ThresholdFilter();

    virtual void    onKeyPressed(int key);
    virtual void    onMousePressed(int button);

    virtual string  getInstructions() { return "Left and Right change threshold size: " + ofToString(_threshold); }

#ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
virtual string getTotalHelpString();
	#endif

protected:
    virtual string  _getVertSrc();
    virtual string  _getFragSrc();
    float           _threshold;
//    bool            _sharp;


};

#endif /* defined(__filterSandbox__ThresholdFilter__) */
