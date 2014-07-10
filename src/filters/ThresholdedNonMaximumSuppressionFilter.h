//
//  ThresholdedNonMaximumSuppressionFilter.h
//  ofxFilterLibraryExample
//
//  Created by Matthew Fargo on 2014/06/27.
//
//

#ifndef __ofxFilterLibraryExample__ThresholdedNonMaximumSuppressionFilter__
#define __ofxFilterLibraryExample__ThresholdedNonMaximumSuppressionFilter__

#include "Abstract3x3TextureSamplingFilter.h"

class ThresholdedNonMaximumSuppressionFilter : public Abstract3x3TextureSamplingFilter {
public:
	ThresholdedNonMaximumSuppressionFilter(float width, float height, bool usesPackedColorSpace=false, float texelSpacing=1.f);
	virtual ~ThresholdedNonMaximumSuppressionFilter();
//	 virtual void    onMousePressed(int button);

    #ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
virtual string getTotalHelpString();
	#endif

protected:
    virtual string  _getFragSrc();

private:
    bool        _usesPackedColorSpace;

};

#endif /* defined(__ofxFilterLibraryExample__ThresholdedNonMaximumSuppressionFilter__) */
