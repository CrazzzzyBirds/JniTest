package com.heima.jnitest

class JniUtils private constructor(){
    // 1. 基础数据类型
    external fun putBasic(int: Int): Int
    // 2. 数组类型
    external fun putArray(intArray: IntArray): IntArray
    // 3. string和数组
    external fun putString(string: String, a: Array<String>): String
    // 4.  类的实例
    external  fun putObj(person: Person)
    // 5.  C层直接新建
    external  fun newObj()

    companion object {
        var instance: JniUtils? = null	//Kotlin中public可以隐藏
            get() {
                if (field == null) {
                    field = JniUtils()
                }
                return field
            }
        init {
            System.loadLibrary("native-lib")
        }
    }
}