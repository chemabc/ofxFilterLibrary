//
//  HSVControlFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#ifndef __filterSandbox__HSVControlFilter__
#define __filterSandbox__HSVControlFilter__

#include "AbstractFilter.h"

class HSVControlFilter : public AbstractFilter {
public:
	HSVControlFilter(float width, float height);
	virtual ~HSVControlFilter();

    virtual void    onKeyPressed(int key);
    virtual void    onMousePressed(int button);

    virtual string  getInstructions() { return "No keys allowed. Only GUI control." ; }

    virtual void updateParameters();

#ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
virtual string getTotalHelpString();
	#endif

protected:
    virtual string  _getVertSrc();
    virtual string  _getFragSrc();
    float           _hue;
    float           _saturation;
    float           _brightness;

};

#endif /* defined(__filterSandbox__HSVControlFilter__) */
