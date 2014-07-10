//
//  FilterChain.h
//  GlassTextureTest
//
//  Created by Matthew Fargo on 2014/06/27.
//
//

#ifndef __GlassTextureTest__FilterChain__
#define __GlassTextureTest__FilterChain__

#include "AbstractPingPongRenderer.h"
#include "AbstractFilter.h"

class FilterChain : public AbstractFilter, public AbstractPingPongRenderer {
public:
	FilterChain(float width, float height, string name="Chain");
	virtual ~FilterChain();

    virtual void    begin();
    virtual void    end();

    void            addFilter(AbstractFilter * filter) { _filters.push_back(filter); }


     #ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
    virtual void    onKeyPressed(int key);
    virtual void    onMousePressed(int button);
    virtual string getTotalHelpString();

    #endif

protected:

    vector<AbstractFilter *>    _filters;
    int i_shitToDebug;
};

#endif /* defined(__GlassTextureTest__FilterChain__) */
