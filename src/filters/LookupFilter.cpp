//
//  LookupFilter.cpp
//  filterSandbox
//
//  Created by Matthew Fargo on 2014/06/23.
//
//

#include "LookupFilter.h"

LookupFilter::LookupFilter(float width, float height, string lookupImageUrl) : AbstractFilter(width, height) {
    _name = "Lookup";
    ofLoadImage(_lookupTexture, lookupImageUrl);
    _addParameter(new ParameterT("inputImageTexture2", _lookupTexture, 2));
    _setupShader();
}
LookupFilter::~LookupFilter() {}

string LookupFilter::_getFragSrc() {
    return GLSL_STRING(120,
        uniform sampler2D inputImageTexture;
        uniform sampler2D inputImageTexture2; // lookup texture

        void main() {
            vec2 uv = gl_TexCoord[0].xy;
            vec4 textureColor = texture2D(inputImageTexture, uv);

            float blueColor = textureColor.b * 63.0;

            vec2 quad1;
            quad1.y = floor(floor(blueColor) / 8.0);
            quad1.x = floor(blueColor) - (quad1.y * 8.0);

            vec2 quad2;
            quad2.y = floor(ceil(blueColor) / 8.0);
            quad2.x = ceil(blueColor) - (quad2.y * 8.0);

            vec2 texPos1;
            texPos1.x = (quad1.x * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.r);
            texPos1.y = (quad1.y * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.g);

            vec2 texPos2;
            texPos2.x = (quad2.x * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.r);
            texPos2.y = (quad2.y * 0.125) + 0.5/512.0 + ((0.125 - 1.0/512.0) * textureColor.g);

            vec4 newColor1 = texture2D(inputImageTexture2, texPos1);
            vec4 newColor2 = texture2D(inputImageTexture2, texPos2);

            vec4 newColor = mix(newColor1, newColor2, fract(blueColor));
            gl_FragColor = vec4(newColor.rgb, textureColor.w);
        }
    );
}

#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/

string LookupFilter::getTotalHelpString() {
    string sComplete= "LookUp: inputImageTexture2 " + s_userGuiPage + " ";
    sComplete += " _Active: " + ofToString(_b_activeFilter) + "; " ;
    return sComplete;
}
void LookupFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
     ptr_gui = gui;
    s_userGuiPage=_name+"_"+ofToString(i_ID);
    if(ptr_gui!=0){
        if(userGuiPage == ""){

            if(bUsePageNameAsATitle){
                ptr_gui->addTitle(s_userGuiPage);
            }
            else{
                ptr_gui->addPage(s_userGuiPage);
            }
        }else{
            if(bUsePageNameAsATitle){
                ptr_gui->addTitle(userGuiPage);
            }
            else{
                ptr_gui->setPage(userGuiPage);
                ptr_gui->addTitle(s_userGuiPage);
            }
        }
        ptr_gui->addToggle("_b_activeFilter_"+ofToString(i_ID), _b_activeFilter);

        if(bLoadSettings) ptr_gui->loadFromXML();
    }

}
#endif


