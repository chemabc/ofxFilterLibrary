//
//  SobelEdgeDetectionFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#ifndef __filterSandbox__SobelEdgeDetectionFilter__
#define __filterSandbox__SobelEdgeDetectionFilter__

#include "AbstractFilter.h"

class SobelEdgeDetectionFilter : public AbstractFilter {
public:
	SobelEdgeDetectionFilter(float width, float height, float edgeStrength=1.f);
	virtual ~SobelEdgeDetectionFilter();

    virtual void    onKeyPressed(int key);
    virtual void    onMousePressed(int button);
    virtual string  getInstructions() { return "Left and Right change edge strength: " + ofToString(_edgeStrength); }

    #ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
virtual string getTotalHelpString();
	#endif


protected:
    virtual string  _getFragSrc();
    virtual string  _getVertSrc();

    float           _edgeStrength;
    float           _threshold;
};

#endif /* defined(__filterSandbox__SobelEdgeDetectionFilter__) */
