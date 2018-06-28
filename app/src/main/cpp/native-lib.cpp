#include <jni.h>
#include <string>
#include <android/bitmap.h>
#include "../include/JniBase.h"
#include "./gl/glShaderUtils.cpp"
#include "./fsh/default-frag.cpp"
#include "./vsh/default-vertex.cpp"

static const GLfloat VERTEX[] = {
        0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f};

static const GLfloat COLOR[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
    };

static const GLfloat TEXTURE[] = {
        0.5f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f
};
int aPosition;
int aColor;
int aCoordiante;
int nTexture;
static int program = 0;

void initValue(JNIEnv *env, jobject bitmap)
{
    aPosition = glGetAttribLocation(program, "aPosition");
    aColor = glGetAttribLocation(program, "aColor");
    aCoordiante = glGetAttribLocation(program, "aCoordinate");
    JNI_LOGI("initValue aPosition = %d, aColor = %d aCoordiante = %d", aPosition, aColor, aCoordiante);

    AndroidBitmapInfo bitmapInfo;
    AndroidBitmap_getInfo(env, bitmap, &bitmapInfo);

    void * data;
    AndroidBitmap_lockPixels(env, bitmap, &data);

    GLuint textures[] = {0};
    glGenTextures(1, textures);
    nTexture = textures[0];

    glBindTexture(GL_TEXTURE_2D, nTexture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmapInfo.width, bitmapInfo.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    AndroidBitmap_unlockPixels(env, bitmap);
}

extern "C" JNIEXPORT jstring
JNICALL
Java_com_jni_opengles_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT void
JNICALL
Java_com_jni_opengles_MainActivity_onSurfaceCreated(JNIEnv *env, jobject object, jobject bitmap)
{
    JNI_LOGI("onSurfaceCreated");
    program = createProgram(DEFAULT_VERTEX_SHADER, DEFAULT_FRAG_SHADER);
    JNI_LOGI("onSurfaceCreated program = %d", program);
    initValue(env, bitmap);
}

extern "C" JNIEXPORT void
JNICALL
Java_com_jni_opengles_MainActivity_onSurfaceChanged(JNIEnv *env, jobject object,jint width, jint height)
{
    JNI_LOGI("Java_com_jni_opengles_MainActivity_onSurfaceChanged width = %d, height = %d", width, height);
    glViewport(0,0,width,height);
}

extern "C" JNIEXPORT void
JNICALL
Java_com_jni_opengles_MainActivity_onDrawFrame(JNIEnv *env, jobject object)
{
    glUseProgram(program);
    checkGlError("glUserProgram");

    glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnableVertexAttribArray(aPosition);
   // glEnableVertexAttribArray(aColor);
    glEnableVertexAttribArray(aCoordiante);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, nTexture);
    glVertexAttribPointer(aPosition, 3, GL_FLOAT, GL_FALSE, 0, VERTEX);
    checkGlError("glVertexAttribPointer aPosition");

//    glVertexAttribPointer(aColor, 4, GL_FLOAT, GL_FALSE, 0, COLOR);
//    checkGlError("glVertexAttribPointer aColor");


    glVertexAttribPointer(aCoordiante, 2, GL_FLOAT, GL_FALSE, 0, TEXTURE);
    checkGlError("glVertexAttribPointer aCoordinate");



    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");

    glDisableVertexAttribArray(aPosition);
   // glDisableVertexAttribArray(aColor);
    glDisableVertexAttribArray(aCoordiante);
}


