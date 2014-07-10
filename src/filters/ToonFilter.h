//
//  ToonFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#ifndef __filterSandbox__ToonFilter__
#define __filterSandbox__ToonFilter__

#include "AbstractFilter.h"

class ToonFilter : public AbstractFilter {
public:
	ToonFilter(float width, float height, float threshold=0.2, float quantizationLevels=12.f);
	virtual ~ToonFilter();

    virtual void    onKeyPressed(int key);
    virtual void    onMousePressed(int button);
    virtual string  getInstructions() {
        return "Left and Right change threshold: " + ofToString(_threshold) + "\nUp and Down change quantization: " + ofToString(_quantizationLevels);
    }
      #ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
virtual string getTotalHelpString();
	#endif
protected:
    virtual string  _getVertSrc();
    virtual string  _getFragSrc();
    float           _threshold;
    float           _quantizationLevels;
};

#endif /* defined(__filterSandbox__ToonFilter__) */
