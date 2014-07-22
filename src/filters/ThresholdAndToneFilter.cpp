//
//  ThresholdAndToneFilter.cpp
//  filterSandbox
//
//  Created by Chema Blanco 2014/07/11
//  Based on Matthew Fargo on 2014/06/23.
//

#include "ThresholdAndToneFilter.h"


ThresholdAndToneFilter::ThresholdAndToneFilter(float width, float height) : AbstractFilter() {
    _name = "ThresholdAndTone";

    _addParameter(new ParameterF("threshold", _threshold));
//    _addParameter(new ParameterF("threshold1", _threshold1));
//     _addParameter(new ParameterF("threshold2", _threshold2));
//    _addParameter(new ParameterF("thresholdTransparency", _thresholdTransparency));

    _addParameter(new ParameterI("sharpCol0", _sharpCol0));
    _addParameter(new ParameterI("sharpCol1", _sharpCol1));

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
ThresholdAndToneFilter::~ThresholdAndToneFilter() {}


void ThresholdAndToneFilter::onKeyPressed(int key) {
    updateParameters();
}
void ThresholdAndToneFilter::onMousePressed(int button){
   updateParameters();
}

string ThresholdAndToneFilter::_getVertSrc() {
    return AbstractFilter::_getVertSrc();
}

string ThresholdAndToneFilter::_getFragSrc() {
    return GLSL_STRING(120,
        uniform sampler2D inputImageTexture;

        uniform float threshold;
//        uniform float threshold1;
//        uniform float threshold2;
//        uniform float thresholdTransparency;
        uniform int sharpCol0;
        uniform int sharpCol1;

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

            if(luminance >= threshold){
                if(sharpCol0==1){
                    colorFinal.r = color_0_R;
                    colorFinal.g = color_0_G;
                    colorFinal.b = color_0_B;
                    //colorFinal.a = color_0_A;
                }

                else{
                    colorFinal.r = luminance * color_0_R;
                    colorFinal.g = luminance * color_0_G;
                    colorFinal.b = luminance * color_0_B;
                    //colorFinal.a = luminance * color_0_A;
                }

//                colorFinal.r = luminance * color_0_R + (1.0-luminance) * color_1_R;
//                colorFinal.g = luminance * color_0_G + (1.0-luminance) * color_1_G;
//                colorFinal.b = luminance * color_0_B + (1.0-luminance) * color_1_B;
//                colorFinal.a = luminance * color_0_A + (1.0-luminance) * color_1_A;


            }else {
                if(sharpCol1==1){
                    colorFinal.r = color_1_R;
                    colorFinal.g = color_1_G;
                    colorFinal.b = color_1_B;
                }
                else{
                    colorFinal.r = luminance * color_0_R + (1.0-luminance) * color_1_R;
                    colorFinal.g = luminance * color_0_G + (1.0-luminance) * color_1_G;
                    colorFinal.b = luminance * color_0_B + (1.0-luminance) * color_1_B;
//                  colorFinal.r = luminance * color_1_R;
//                  colorFinal.g = luminance * color_1_G;
//                  colorFinal.b = luminance * color_1_B;
                }


//                colorFinal.r = luminance * color_0_R + (1.0-luminance) * color_1_R;
//                colorFinal.g = luminance * color_0_G + (1.0-luminance) * color_1_G;
//                colorFinal.b = luminance * color_0_B + (1.0-luminance) * color_1_B;
//                colorFinal.a = luminance * color_0_A + (1.0-luminance) * color_1_A;
            }
//            if(textureColor.a < thresholdTransparency){
//                colorFinal.r = 0.0;
//                colorFinal.g = 1.0;
//                colorFinal.b = 0.0;
//                colorFinal.a = 1.0;
//            }
            colorFinal.a = 1.0;


            gl_FragColor = colorFinal;

    }
    );
}
void ThresholdAndToneFilter::updateParameters(){

    updateParameter("threshold", _threshold);
//    updateParameter("threshold1", _threshold1);
    //updateParameter("threshold2", _threshold2);
//    updateParameter("thresholdTransparency", _thresholdTransparency);

    updateParameter("sharpCol0", _sharpCol0);
    updateParameter("sharpCol1", _sharpCol1);

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
string ThresholdAndToneFilter::getTotalHelpString() {
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
void ThresholdAndToneFilter::setupGui(ofxSimpleGuiToo *gui, string userGuiPage, bool bUsePageNameAsATitle, bool bLoadSettings){
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
        ptr_gui->addSlider("_threshold"+ofToString(i_ID), _threshold, 0.0, 1.0);
//        ptr_gui->addSlider("_thresholdTransparency"+ofToString(i_ID), _thresholdTransparency, 0.0, 1.0);

        ptr_gui->addSlider("_sharpCol0"+ofToString(i_ID), _sharpCol0, 0, 1);
        ptr_gui->addSlider("_sharpCol1"+ofToString(i_ID), _sharpCol1, 0, 1);

        ptr_gui->addColorPicker("_color_0_"+ofToString(i_ID), color0);
        ptr_gui->addColorPicker("_color_1_"+ofToString(i_ID), color1);

        if(bLoadSettings){
                ptr_gui->loadFromXML();
                updateParameters();
        }
    }

}
#endif
