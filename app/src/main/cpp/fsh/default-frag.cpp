#include "../../include/JniBase.h"

//
// Created by Administrator on 2018/6/27.
//
static const char DEFAULT_FRAG_SHADER[] = JNI_VALUE(
    precision highp float;
    uniform sampler2D sampler;
        varying vec2 aVaryingCoordinate;
    varying vec4 coordColor;


    void main(){
        gl_FragColor = texture2D(sampler, aVaryingCoordinate.xy);
    }
);
