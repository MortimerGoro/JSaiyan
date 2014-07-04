/* 
 * JSaiyan is licensed under MIT licensed. See LICENSE.md file for more information.
 * Copyright (c) 2014 MortimerGoro
*/

#include <jni.h>
#include <android/log.h>
#include <cstdlib>

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "JSaiyan",__VA_ARGS__)

extern "C"
{   
    jint JNI_OnLoad(JavaVM* vm, void* reserved)
    {
        JNIEnv* env;
        if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
            return -1;
        }
        return JNI_VERSION_1_6;
    } 

    jobject Java_com_jsaiyan_Unsafe_allocateObject(JNIEnv * env, jobject thiz, jclass clazz) 
    {
        return env->AllocObject(clazz);
    }

    void Java_com_jsaiyan_Unsafe_nativeCallSuper(JNIEnv * env, jobject thiz, jobject instance, jclass clazz, jstring methodName, jstring signature, jobjectArray params) 
    {

        const char * strMethod = env->GetStringUTFChars(methodName, JNI_FALSE);
        const char * strSignature = env->GetStringUTFChars(signature, JNI_FALSE);

        jmethodID methodID = env->GetMethodID(clazz, strMethod, strSignature);

        int count = env->GetArrayLength(params);

        if (count == 0) {
             env->CallNonvirtualVoidMethod(instance, clazz, methodID);
             return;
        }
        else {
            jvalue values[count];
            for (int i=0; i<count; i++) {
                jvalue val;
                val.l = env->GetObjectArrayElement(params, i);
                values[i] = val;
            }
            env->CallNonvirtualVoidMethodA(instance, clazz, methodID, values);
        }

        env->ReleaseStringUTFChars(methodName, strMethod);
        env->ReleaseStringUTFChars(signature, strSignature);
    } 

    void Java_com_jsaiyan_Unsafe_throwException(JNIEnv * env, jobject thiz, jthrowable exception) 
    {
        env->Throw(exception);
    }

    jlong Java_com_jsaiyan_Unsafe_malloc(JNIEnv * env, jobject thiz, jlong size) {
        return reinterpret_cast<jlong>(malloc(size));
    } 

    void Java_com_jsaiyan_Unsafe_free(JNIEnv * env, jobject thiz, jlong address) {
        return free(reinterpret_cast<void*>(address));
    } 

    void Java_com_jsaiyan_Unsafe_memcpy(JNIEnv * env, jobject thiz, jlong dest, jlong source, jlong size) {
        memcpy(reinterpret_cast<void*>(dest), reinterpret_cast<void*>(source), size);
    } 

    long Java_com_jsaiyan_Unsafe_getAddress(JNIEnv * env, jobject thiz, jlong address) {
        //TODO 64 bit support
        void * pointer = reinterpret_cast<void*>(address);
        int data;
        memcpy(&data, pointer, sizeof(data));
        return data;
    } 

    void Java_com_jsaiyan_Unsafe_putAddress(JNIEnv * env, jobject thiz, jlong address, jlong value) {
        //TODO 64 bit support
        void * pointer = reinterpret_cast<void*>(address);
        int data = value;
        memcpy(pointer, &data, sizeof(data));
    } 
}