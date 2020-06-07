#include <jni.h>
#include <string>
#include "android_log.h"

jint putBasic(JNIEnv *jniEnv, jobject obj, jint j_int) {
    // LOGD("jni input : %d", j_int);
    int result = 0;//int类型可以作为jint类型直接返回
    return result;
}

/*
 * Class:     com_heima_jnitest_JniUtils
 * Method:    putArray
 * Signature: ([I)[I
 */
jintArray putArray(JNIEnv *jniEnv, jobject jObj, jintArray jArray) {
    /*第一部分：读取数组*/
    //1.获取数组长度 GetArrayLength（java中Int数组）
    int arraySize = jniEnv->GetArrayLength(jArray);
    // 2.java中数组 → C语言数组  GetIntArrayElements（java中Int数组，是否copy）
    int *cIntArray = jniEnv->GetIntArrayElements(jArray, NULL);
    LOGD("input array");
    for (int i = 0; i < arraySize; ++i) {
        LOGD("%d", cIntArray[i]);
        *(cIntArray + i) += 10; //将数组中的每个元素加10
    }

    /*第二部分：返回数组*/

    /* 1. new一个 jintArray
     * NewIntArray（数组长度）
     */
    jintArray returnArray = jniEnv->NewIntArray(arraySize);

    /* 2. 把上面修改过的cIntArray赋值到新建的returnArray中去
     *  SetIntArrayRegion（jintArray，起始位置，长度，c中已经准备好的数组int *cIntArray）
     */
    jniEnv->SetIntArrayRegion(returnArray, 0, arraySize, cIntArray);


    /* 既然开辟了空间，一定要去释放
     *  关于第三个参数：mode：
     *  0 → 刷新Java数组并释放C数组
     *  1 → 只刷新Java数组，不释放C数组
     *  2 → 只释放
     * */
    jniEnv->ReleaseIntArrayElements(jArray, cIntArray, 0);

    return returnArray;
}


/*
* Class:     com_heima_jnitest_JniUtils
        * Method:    putString
        * Signature: (Ljava/lang/String;[Ljava/lang/String;)Ljava/lang/String;
*/
jstring putString(JNIEnv *env, jobject obj, jstring jstring1, jobjectArray jobjectArray1) {
    /* 一. string相关 */
    LOGD("jstring: %s", jstring1)//这样直接打印jstring是打印不出来东西的,需要转换
    // jstring → const char 才能打印出来内容
    const char *str = env->GetStringUTFChars(jstring1, NULL);
    LOGD("const char:%s", str)

    /* 二. string数组相关 简单说就是类型转换 → 遍历数组 → 转换string */
    // 1.获取数组长度
    jsize size = env->GetArrayLength(jobjectArray1);
    LOGD("java input ")
    for (int i = 0; i < size; i++) {
        // 2. 遍历并强转为其中的每个jstring
        jstring obj = (jstring) env->GetObjectArrayElement(jobjectArray1, i);
        // 3.得到字符串
        //std:: string str = (std::string)env->GetStringUTFChars(obj,NULL); //Android的log无法打印std:: string？？？我懵逼了
        const char *str = env->GetStringUTFChars(obj, NULL);
        LOGD("const char:%s", str)
        // 4.必须记得释放！！！
        env->ReleaseStringUTFChars(obj, str);
    }
    return env->NewStringUTF("C层数据");
}

/*
 * Class:     com_heima_jnitest_JniUtils
 * Method:    putObj
 * Signature: (Lcom/heima/jnitest/Person;)V
 */
void putObj(JNIEnv *env, jobject thiz, jobject person) {
    // 1.找到jclass
    jclass personJClass = env->GetObjectClass(person);

    // 2.寻找想要调用的方法ID
    const char *sig = "(Ljava/lang/String;)V"; // 方法签名
    //todo 第一个坑：GetMethodID第三个参数直接写入字符串，有时候报错，我编了俩遍，clean多次才成功运行
    jmethodID setName = env->GetMethodID(personJClass, "setName", sig);
    //jmethodID setName = env->GetMethodID(personJClass, "setName", "(Ljava/lang/String;)V");//有时报错！！！
    const char *sig2 = "()Ljava/lang/String;"; // 方法签名
    jmethodID getName = env->GetMethodID(personJClass, "getName", sig2);

    // 3.调用
    jstring value = env->NewStringUTF("JNI");
    // todo  第二个坑：CallVoidMethod传入上面获得的personJClass会调用失败（不报错） 传入函数入口的jobject=person调用成功
    //env->CallVoidMethod(personJClass, setName, value);
    env->CallVoidMethod(person, setName, value);
    //返回类型jobject 需要转换类型
    jstring getNameResult = static_cast<jstring>(env->CallObjectMethod(person, getName));
    //转为const char*方可打印
    const char *getNameString = env->GetStringUTFChars(getNameResult, NULL);
    LOGE("Java getName = %s", getNameString)

    //4.用完一定释放啊baby！！！！！！
    env->ReleaseStringUTFChars(getNameResult, getNameString);
}


void newObj(JNIEnv *env, jobject obj) {
    // 1.包名+类名路径找到类
    const char * personPath = "com/heima/jnitest/Person";
    jclass  personClass = env->FindClass(personPath);

    // 2.jclass → （实例化jobject对象
    /*
     * 创建方法的俩种方式
     * NewObject：  初始化成员变量，调用指定的构造方法
     * AllocObject：不初始成员变量，也不调用构造方法
     * */
    jobject personObj = env->AllocObject(personClass);
    // 3.调用方法签名 一定要匹配。PS：不匹配也没关系，因为编译器会报错提示；当时输入第二个参数时候其实第三个参数也会自己跳出来。
    const char *sig = "(Ljava/lang/String;)V";
    jmethodID setName = env->GetMethodID(personClass, "setName", sig);
    sig="(I)V";
    jmethodID setId = env->GetMethodID(personClass, "setId", sig);
    sig="()V";
    jmethodID printVar= env->GetMethodID(personClass, "printVar", sig);
    // 4.实例化对象 → 调用方法
    env->CallVoidMethod(personObj, setName,  env->NewStringUTF("CPP"));
    env->CallVoidMethod(personObj, setId, 666);
    //调用类中打印方法，看是否生效
    env->CallVoidMethod(personObj, printVar);

    // 5. 老规矩，释放。C没有GC，在C里new了就要手动释放。
    /*
     * 释放的俩种方式：
     * DeleteLocalRef 释放局部变量
     * DeleteGlobalRef 释放全局变量 → JNI函数创建（NewGlobalRef）
     * */
    env->DeleteLocalRef(personClass);
    env->DeleteLocalRef(personObj);
}

/*
 * typedef struct {
    const char* name; //函数名字
    const char* signature; //函数符号
    void*       fnPtr; //函数指针
    } JNINativeMethod;
 */
static const JNINativeMethod jniNativeMethod[] = {
        {"putBasic",  "(I)I",                                                      (void *) (putBasic)},
        {"putArray",  "([I)[I",                                                    (void *) (putArray)},
        {"putString", "(Ljava/lang/String;[Ljava/lang/String;)Ljava/lang/String;", (void *) (putString)},
        {"putObj",    "(Lcom/heima/jnitest/Person;)V",                             (void *) (putObj)},
        {"newObj",    "()V",                             (void *) (newObj)}
};
/*
 * Class:     com_heima_jnitest_JniUtils
 * Method:    putObj
 * Signature: (Lcom/heima/jnitest/Person;)V
 */

/**
 * 1.设置jvm全局变量，多线程需要用到
 * 2.nullptr: C++11后，要取代NULL，作用是可以给初始化的指针赋值
 */
JavaVM *jvm = nullptr;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *javaVm, void *pVoid) {
    jvm = javaVm;
    // 1.通过JavaVM 创建全新的JNIEnv
    JNIEnv *jniEnv = nullptr;
    // 2.判断创建是否成功
    jint result = javaVm->GetEnv(reinterpret_cast<void **>(&jniEnv),
                                 JNI_VERSION_1_6); // 参数2：是JNI的版本 NDK 1.6   JavaJni 1.8
    if (result != JNI_OK) {
        return -1;
    }
    // 3.找到需要动态动态注册的Jni类
    jclass jniClass = jniEnv->FindClass("com/heima/jnitest/JniUtils");
    //动态注册   待注册class 方法集合 方法数量
    jniEnv->RegisterNatives(jniClass, jniNativeMethod,
                            sizeof(jniNativeMethod) / sizeof(JNINativeMethod));
    return JNI_VERSION_1_6;
}