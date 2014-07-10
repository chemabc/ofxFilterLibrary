//
//  LookupFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#ifndef __filterSandbox__LookupFilter__
#define __filterSandbox__LookupFilter__

#include "AbstractFilter.h"

class LookupFilter : public AbstractFilter {
public:
	LookupFilter(float width, float height, string lookupImageUrl);
	virtual ~LookupFilter();

     #ifdef _APPGC_OFXSIMPLEGUITOO
     virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
     virtual string getTotalHelpString();
     #endif
protected:
    ofTexture       _lookupTexture;
    virtual string  _getFragSrc();
};

#endif /* defined(__filterSandbox__LookupFilter__) */
