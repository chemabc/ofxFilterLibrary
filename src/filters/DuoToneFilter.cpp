//
//  DuoToneFilter.cpp
//  filterSandbox
//
//  Created by Chema Blanco 2014/07/11
//  Based on Matthew Fargo on 2014/06/23.
//

#include "DuoToneFilter.h"


DuoToneFilter::DuoToneFilter(float width, float height) : AbstractFilter() {
    _name = "DueTone";

    _addParameter(new ParameterF("color_0_R", color0.r));
    _addParameter(new ParameterF("color_0_G", color0.g));
    _addParameter(new ParameterF("color_0_B", color0.b));
    _addParameter(new ParameterF("color_0_A", color0.a));

    _addParameter(new ParameterF("color_1_R", color1.r));
    _addParameter(new ParameterF("color_1_G", color1.g));
    _addParameter(new ParameterF("color_1_B", color1.b));
    _addParameter(new ParameterF("color_1_A", color1.a));


   // _addParameter(new ParameterF("sharp", _sharp));
    _setupShader();
}
DuoToneFilter::~DuoToneFilter() {}


void DuoToneFilter::onKeyPressed(int key) {
    updateParameters();
}
void DuoToneFilter::onMousePressed(int button){
   updateParameters();
}

string DuoToneFilter::_getVertSrc() {
    return AbstractFilter::_getVertSrc();
}

string DuoToneFilter::_getFragSrc() {
    return GLSL_STRING(120,
        uniform sampler2D inputImageTexture;

        uniform float color_0_R;
        uniform float color_0_G;
        uniform float color_0_B;
        uniform float color_0_A;

        uniform float color_1_R;
        uniform float color_1_G;
        uniform float color_1_B;
        uniform float color_1_A;

        const vec3 W = vec3(0.2125, 0.7154, 0.0721);
    void main(){
            //Grayscale for threshold
            vec2 textureCoordinate = gl_TexCoord[0].xy;
            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            float luminance = dot(textureColor.rgb, W);

            vec4 colorFinal;
            colorFinal.r = luminance * color_0_R + (1.0-luminance) * color_1_R;
            colorFinal.g = luminance * color_0_G + (1.0-luminance) * color_1_G;
            colorFinal.b = luminance * color_0_B + (1.0-luminance) * color_1_B;
            colorFinal.a = luminance * color_0_A + (1.0-luminance) * color_1_A;

            gl_FragColor = colorFinal;

    }
    );
}
void DuoToneFilter::updateParameters(){
    updateParameter("color_0_R", color0.r);
    updateParameter("color_0_G", color0.g);
    updateParameter("color_0_B", color0.b);
    updateParameter("color_0_A", color0.a);

    updateParameter("color_1_R", color1.r);
    updateParameter("color_1_G", color1.g);
    updateParameter("color_1_B", color1.b);
    updateParameter("color_1_A", color1.a);
}
#ifdef _APPGC_OFXSIMPLEGUITOO
/****************************************************
        ofxSimpleGuiToo GUI
****************************************************/
string DuoToneFilter::getTotalHelpString() {
    string sComplete= _name + ": " + s_userGuiPage + " ";
    sComplete += " color0.r: " + ofToString(color0.r) + "; " ;
    sComplete += " color0.g: " + ofToString(color0.g) + "; " ;
    sComplete += " color0.b: " + ofToString(color0.b) + "; " ;
    sComplete += " color0.a: " + ofToString(color0.a) + "; " ;

    sComplete += " color1.r: " + ofToString(color1.r) + "; " ;
    sComplete += " color1.g: " + ofToString(color1.g) + "; " ;
    sComplete += " color1.b: " + ofToString(color1.b) + "; " ;
    sComplete += " color1.a: " + ofToString(color1.a) + "; " ;

    return sComplete;
}
void DuoToneFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
        ptr_gui->addColorPicker("_color_0_"+ofToString(i_ID), color0);
        ptr_gui->addColorPicker("_color_1_"+ofToString(i_ID), color1);

        if(bLoadSettings){
                ptr_gui->loadFromXML();
                updateParameters();
        }
    }

}
#endif
