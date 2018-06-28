//
// Created by Administrator on 2018/6/27.
//

#include "../../include/JniBase.h"

static const char DEFAULT_VERTEX_SHADER[] = JNI_VALUE(
    precision highp float;
    attribute vec3 aPosition;
    attribute vec4 aColor;
    attribute vec2 aCoordinate;
    varying vec4 coordColor;
        varying vec2 aVaryingCoordinate;

    void main()
    {
        gl_Position = vec4(aPosition, 1.0);
        coordColor = aColor;
        aVaryingCoordinate = aCoordinate;
    }
);