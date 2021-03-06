//
//  DissolveBlendFilter.h
//  ofxFilterLibraryExample
//
//  Created by Matthew Fargo on 2014/06/30.
//
//

#ifndef __ofxFilterLibraryExample__DissolveBlendFilter__
#define __ofxFilterLibraryExample__DissolveBlendFilter__

#include "AbstractTwoInputFilter.h"

class DissolveBlendFilter : public AbstractTwoInputFilter {
public:
	DissolveBlendFilter(float width, float height, float mix=0.5f);
	virtual ~DissolveBlendFilter();

    virtual void    onKeyPressed(int key);
    virtual void    onMousePressed(int button);

    float           getMix() { return _mix;  }
    void            setMix(float mix);
    virtual void updateParameters();
#ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
virtual string getTotalHelpString();
	#endif
protected:
    virtual string  _getFragSrc();

    float           _mix;

};

#endif /* defined(__ofxFilterLibraryExample__DissolveBlendFilter__) */
