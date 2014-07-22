//
//  LowPassFilter.h
//  ofxFilterLibraryExample
//
//  Created by Matthew Fargo on 2014/06/30.
//
//

#ifndef __ofxFilterLibraryExample__LowPassFilter__
#define __ofxFilterLibraryExample__LowPassFilter__

#include "DissolveBlendFilter.h"

class LowPassFilter : public DissolveBlendFilter {
public:
	LowPassFilter(float width, float height, float mix=1.0);
	virtual ~LowPassFilter();

    virtual void    begin();
    virtual void    end();


    ofTexture &     getTextureReference() { return _buffer.getTextureReference(); }

    #ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);

    string getTotalHelpString();
	#endif

private:

    ofFbo           _buffer;    // buffer result and read back in
};

#endif /* defined(__ofxFilterLibraryExample__LowPassFilter__) */
