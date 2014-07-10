//
//  TileShiftFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#ifndef __filterSandbox__TileShiftFilter__
#define __filterSandbox__TileShiftFilter__

#include "GaussianBlurFilter.h"

class TiltShiftFilter : public AbstractFilter {
public:
	TiltShiftFilter(ofTexture & texture, float focusPercent = 0.4, float falloff=0.2f);
	virtual ~TiltShiftFilter();

    virtual void    begin();
    virtual void    onKeyPressed(int key);
     virtual void    onMousePressed(int button);

    virtual void    describeParameters();
    GaussianBlurFilter *getGaussianBlurFilter() { return _gaussianBlurFilter; }
    virtual string  getInstructions() { return "Up and Down change vertical focus"; }


#ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
virtual string getTotalHelpString();
	#endif

protected:
    virtual string      _getFragSrc();

private:
    float               _focusPercent;

    GaussianBlurFilter *_gaussianBlurFilter;
    ofTexture           _texture;

};

#endif /* defined(__filterSandbox__TileShiftFilter__) */
