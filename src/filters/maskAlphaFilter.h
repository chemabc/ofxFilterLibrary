//
//  maskAlphaFilter.h
//  ofxFilterLibraryExample
//
//  Created by Matthew Fargo on 2014/06/27.
//
//

#ifndef __ofxFilterLibraryExample__maskAlphaFilter__
#define __ofxFilterLibraryExample__maskAlphaFilter__

#include "AbstractFilter.h"


class maskAlphaFilter : public AbstractFilter {
public:
	maskAlphaFilter();
	virtual ~maskAlphaFilter();

	#ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
	#endif

private:
    virtual string  _getFragSrc();
};

#endif /* defined(__ofxFilterLibraryExample__maskAlphaFilter__) */
