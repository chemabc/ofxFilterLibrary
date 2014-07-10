//
//  BilateralFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/24.
//
//

#ifndef __filterSandbox__BilateralFilter__
#define __filterSandbox__BilateralFilter__

#include "Abstract3x3PingPongFilter.h"

class BilateralFilter : public Abstract3x3PingPongFilter {
public:
	BilateralFilter(float width, float height, float blurOffset=4.f, float normalization=6.f);
	virtual ~BilateralFilter();

    virtual void    onKeyPressed(int key);
    virtual void    onMousePressed(int button);
    virtual string  getInstructions() { return "Up and Down change blur offset: " + ofToString(_texelSpacing.x) + "\nLeft and Right to change normalization: " + ofToString(_normalization); }


    float           getBlurOffset() { return _texelSpacing.x; }
    void            setBlurOffset(float blurOffset) { _texelSpacing = ofVec2f(blurOffset, blurOffset); }

     #ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
virtual string getTotalHelpString();
	#endif

protected:
    virtual string  _getFragSrc();
    virtual string  _getVertSrc();

    float           _normalization;
    float _blurOffset; //chema

};

#endif /* defined(__filterSandbox__BilateralFilter__) */
