//
//  KuwaharaFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#ifndef __filterSandbox__KuwaharaFilter__
#define __filterSandbox__KuwaharaFilter__

#include "AbstractFilter.h"

class KuwaharaFilter : public AbstractFilter {
public:
	KuwaharaFilter(int radius=7);

	virtual ~KuwaharaFilter();

    virtual void    onKeyPressed(int key);
    virtual void    onMousePressed(int button);
    virtual string  getInstructions() { return "Up and Down change radius ("+ofToString(_radius)+")"; }
virtual void updateParameters();
    #ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
virtual string getTotalHelpString();
	#endif

protected:
    virtual string  _getFragSrc();
    int             _radius;
};


#endif /* defined(__filterSandbox__KuwaharaFilter__) */
