//
//  GrayscaleFilter.h
//  ofxFilterLibraryExample
//
//  Created by Matthew Fargo on 2014/06/27.
//
//

#ifndef __ofxFilterLibraryExample__GrayscaleFilter__
#define __ofxFilterLibraryExample__GrayscaleFilter__

#include "AbstractFilter.h"


class GrayscaleFilter : public AbstractFilter {
public:
	GrayscaleFilter();
	virtual ~GrayscaleFilter();

	#ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);

    string getTotalHelpString();
	#endif

private:
    virtual string  _getFragSrc();
};

#endif /* defined(__ofxFilterLibraryExample__GrayscaleFilter__) */
