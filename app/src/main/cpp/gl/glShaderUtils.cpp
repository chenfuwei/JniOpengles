//
// Created by Administrator on 2018/6/27.
//
#include "../../include/glBase.h"
#include "../../include/jnibase.h"
#include <stdlib.h>

static int createShader(int type, const char shader[]) {
    GLuint value = glCreateShader(type);
    if (!value) {
        JNI_LOGI("glCreateShader failure type =  %d, value = %d", type, value);
        return 0;
    }
    glShaderSource(value, 1, &shader, NULL);
    JNI_LOGI("glCreateShader value = %d,  type = %d", value, type);
    glCompileShader(value);
    JNI_LOGI("glCreateShader 1 value = %d, type = %d", value, type);

    GLint infoLenght;
    glGetShaderiv(value, GL_INFO_LOG_LENGTH, &infoLenght);
    JNI_LOGI("createShader GL_INFO_LOG_LENGTH = %d ", infoLenght);
    char *buf = (char *) malloc(infoLenght + 1);
    if (infoLenght) {
        glGetShaderInfoLog(value, infoLenght, NULL, buf);
        JNI_LOGI("shaderinfo log shader = %d buf = %s", value, buf);
    }

    return value;
}

static int createProgram(const char v[], const char f[])
{
    JNI_LOGI("createProgram v = %s, f = %s", v, f);
    int vetexShader = createShader(GL_VERTEX_SHADER, v);
    if(!vetexShader)
    {
        JNI_LOGI("createProgram GL_VERTEX_SHADER vetexShader = %d", vetexShader);
        return 0;
    }

    int fragShader = createShader(GL_FRAGMENT_SHADER, f);
    if(!fragShader)
    {
        JNI_LOGI("createShader GL_FRAG_SHADER fragShader = %d", fragShader);
        return 0;
    }

    int program = glCreateProgram();
    glAttachShader(program, vetexShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    return program;
}

static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    JNI_LOGI("GL %s = %s\n", name, v);
}

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
                                                    = glGetError()) {
        JNI_LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

