//
//  ThresholdRGBAFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#ifndef __filterSandbox__ThresholdRGBAFilter__
#define __filterSandbox__ThresholdRGBAFilter__

#include "AbstractFilter.h"

class ThresholdRGBAFilter : public AbstractFilter {
public:
	ThresholdRGBAFilter(float width, float height,
                 float threshold = 0.0);
	virtual ~ThresholdRGBAFilter();

    virtual void    onKeyPressed(int key);
    virtual void    onMousePressed(int button);

    virtual string  getInstructions() { return "No keys allowed. Use only GUI for thresholdRGBA. "; }
    virtual void updateParameters();

#ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
virtual string getTotalHelpString();
	#endif

protected:
    virtual string  _getVertSrc();
    virtual string  _getFragSrc();

    int            _sharp;
    int            _invert;
    float           _thresholdR;
    float           _thresholdG;
    float           _thresholdB;
    float           _thresholdA;


};

#endif /* defined(__filterSandbox__ThresholdRGBAFilter__) */
