/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_heima_jnitest_JniUtils */

#ifndef _Included_com_heima_jnitest_JniUtils
#define _Included_com_heima_jnitest_JniUtils
#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_heima_jnitest_JniUtils
 * Method:    setName
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_heima_jnitest_JniUtils_setName
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_heima_jnitest_JniUtils
 * Method:    getName
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_heima_jnitest_JniUtils_getName
  (JNIEnv *, jobject);

/*
 * Class:     com_heima_jnitest_JniUtils
 * Method:    putBasic
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_heima_jnitest_JniUtils_putBasic
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_heima_jnitest_JniUtils
 * Method:    putArray
 * Signature: ([I)[I
 */
JNIEXPORT jintArray JNICALL Java_com_heima_jnitest_JniUtils_putArray
  (JNIEnv *, jobject, jintArray);

/*
 * Class:     com_heima_jnitest_JniUtils
 * Method:    putString
 * Signature: (Ljava/lang/String;[Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_heima_jnitest_JniUtils_putString
  (JNIEnv *, jobject, jstring, jobjectArray);

/*
 * Class:     com_heima_jnitest_JniUtils
 * Method:    putObj
 * Signature: (Lcom/heima/jnitest/Person;)V
 */
JNIEXPORT void JNICALL Java_com_heima_jnitest_JniUtils_putObj
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
