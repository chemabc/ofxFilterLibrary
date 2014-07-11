//
//  DuoToneFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#ifndef __filterSandbox__DuoToneFilter__
#define __filterSandbox__DuoToneFilter__

#include "AbstractFilter.h"

class DuoToneFilter : public AbstractFilter {
public:
	DuoToneFilter(float width, float height);
	virtual ~DuoToneFilter();

    virtual void    onKeyPressed(int key);
    virtual void    onMousePressed(int button);

    virtual string  getInstructions() { return "No keys allowed. Only GUI control" ; }
    virtual void updateParameters();

#ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
virtual string getTotalHelpString();
	#endif

protected:
    virtual string  _getVertSrc();
    virtual string  _getFragSrc();


    ofFloatColor color0, color1;





};

#endif /* defined(__filterSandbox__DuoToneFilter__) */
