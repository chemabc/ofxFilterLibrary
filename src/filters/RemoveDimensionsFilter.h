//
//  RemoveDimensionsFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#ifndef __filterSandbox__RemoveDimensionsFilter__
#define __filterSandbox__RemoveDimensionsFilter__

#include "AbstractFilter.h"

#define REMOVEFILTER_MIN_DIM 0
#define REMOVEFILTER_MAX_DIM 1920 //Pixels

class RemoveDimensionsFilter : public AbstractFilter {
public:
	RemoveDimensionsFilter(float width, float height);
	virtual ~RemoveDimensionsFilter();

    virtual void    onKeyPressed(int key);
    virtual void    onMousePressed(int button);

    virtual string  getInstructions() { return "NO KEY CONTROL " ; }
     virtual void updateParameters();

    #ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);

    virtual string getTotalHelpString();

	#endif

protected:
    virtual string  _getVertSrc();
    virtual string  _getFragSrc();
    int _i_xMin, _i_xMax, _i_yMin, _i_yMax;


};

#endif /* defined(__filterSandbox__RemoveDimensionsFilter__) */
