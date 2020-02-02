
#ifndef __JNILIBOPUS_H__
#define __JNILIBOPUS_H__

#include <stdio.h>
#include <jni.h>
#include <vector>
#include <mutex>

#include "opus.h"

#ifdef __cplusplus
extern "C"
{
#endif

    JNIEXPORT jint JNICALL
    Java_com_test_JniOpus_encoder_1initialize(JNIEnv *env, jobject jobj,
                                                                jint sampleRateHz, jint channel, jint bitrate);

    JNIEXPORT jint JNICALL
    Java_com_test_JniOpus_encode(JNIEnv *env, jobject jobj,
                                                   jint enc, jbyteArray _input, jint inputOffset, jint inputLength,
                                                   jbyteArray _output, jint outputOffset, jint outputLength);

    JNIEXPORT void JNICALL
    Java_com_test_JniOpus_encoder_1uninitialize(JNIEnv *env, jobject jobj,
                                                                  jint enc);

    JNIEXPORT jint JNICALL
    Java_com_test_JniOpus_decoder_1initialize(JNIEnv *env, jobject jobj,
                                                                jint sampleRateHz, jint channel);

    JNIEXPORT jint JNICALL
    Java_com_test_JniOpus_decode(JNIEnv *env, jobject jobj,
                                                   jint dec, jbyteArray _input, jint inputOffset, jint inputLength,
                                                   jbyteArray _output, jint outputOffset, jint outputLength);

    JNIEXPORT void JNICALL
    Java_com_test_JniOpus_decoder_1uninitialize(JNIEnv *env, jobject jobj,
                                                                  jint dec);

#ifdef __cplusplus
}
#endif

#endif /* __JNILIBOPUS_H__ */
