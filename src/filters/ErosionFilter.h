//
//  ErosionFilter.h
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/25.
//
//

#ifndef __filterSandbox__ErosionFilter__
#define __filterSandbox__ErosionFilter__

#include "Abstract3x3PingPongFilter.h"

class ErosionFilter : public Abstract3x3PingPongFilter {
public:
	ErosionFilter(float width, float height, int erosionRadius=2);
	virtual ~ErosionFilter();

    virtual void    onKeyPressed(int key);
     virtual void    onMousePressed(int button);

    virtual string  getInstructions() { return "Up and Down change erosion radius: " + ofToString(getErosionRadius()); }


    int             getErosionRadius() { return _texelSpacing.x; }
    void            setErosionRadius(int erosionRadius);
    #ifdef _APPGC_OFXSIMPLEGUITOO
    virtual void setupGui(ofxSimpleGuiToo *gui, string userGuiPage = "", bool bUsePageNameAsATitle = false, bool bLoadSettings=true);
//    virtual void updateParameters();
virtual string getTotalHelpString();
	#endif
protected:
    virtual string  _getFragSrc();
    virtual string  _getVertSrc();

private:
    string          _getFragSrcForRadius(int radius);
    string          _getVertSrcForRadius(int radius);

    float f_erosionRadius;
};

#endif /* defined(__filterSandbox__ErosionFilter__) */
