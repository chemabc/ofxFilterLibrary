//
//  ThresholdAndToneFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#ifndef __filterSandbox__ThresholdAndToneFilter__
#define __filterSandbox__ThresholdAndToneFilter__

#include "AbstractFilter.h"

class ThresholdAndToneFilter : public AbstractFilter {
public:
	ThresholdAndToneFilter(float width, float height);
	virtual ~ThresholdAndToneFilter();

    virtual void    onKeyPressed(int key);
    virtual void    onMousePressed(int button);

    virtual string  getInstructions() { return "No keys allowed. Only GUI control" ; }
    virtual void updateParameters();

    void setColor0(ofFloatColor col0){color0 = col0; updateParameters();}
    void setColor1(ofFloatColor col1){color1 = col1; updateParameters();}

#ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
    virtual string getTotalHelpString();
	#endif

protected:
    virtual string  _getVertSrc();
    virtual string  _getFragSrc();


    ofFloatColor color0, color1;
    float _threshold;//1, _threshold2;
    float _thresholdTransparency;
    int _sharpCol0, _sharpCol1;





};

#endif /* defined(__filterSandbox__ThresholdAndToneFilter__) */
