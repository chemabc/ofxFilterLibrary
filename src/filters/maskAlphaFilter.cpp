//
//  maskAlphaFilter.cpp
//  ofxFilterLibraryExample
//
//  Created by Matthew Fargo on 2014/06/27.
//
//

#include "maskAlphaFilter.h"

maskAlphaFilter::maskAlphaFilter() : AbstractFilter() {
    _name = "maskAlpha";
    _setupShader();
}

maskAlphaFilter::~maskAlphaFilter() {}


string maskAlphaFilter::_getFragSrc() {
    return GLSL_STRING(120,
//        "#extension GL_ARB_texture_rectangle : enable
//        #extension GL_EXT_gpu-shader4 : enable"
        uniform sampler2D inputImageTexture;
       // uniform sampler2D inputImageTexture1; //mask con alpha

        void main() {
            vec2 textureCoordinate = gl_TexCoord[0].xy;
         //   vec2 textureCoordinate2 = gl_TexCoord[1].xy;
            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
           // vec4 textureColor2 = texture2D(inputImageTexture1, textureCoordinate2);
//            vec4 finalColor;
//            finalColor.rgb = textureColor.rgb;
////           finalColor.r = 1.0;
////            finalColor.g = 0.0;
////            finalColor.b = 0.0;
////
//            finalColor.a = 1.0;
            if(textureColor.a <=0.0){
                textureColor.r =1.0;
                textureColor.a =1.0;
            }
            gl_FragColor =textureColor;
        }
    );
}


#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
//void maskAlphaFilter::updateParameters(){
//
//}
void maskAlphaFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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

        if(bLoadSettings) ptr_gui->loadFromXML();
    }

}


#endif
