package com.heima.jnitest

import android.util.Log


class Person{
    private val tag = Person::class.java.name
    var name:String = "init"
    var id:Int = 0

    constructor(name: String, id: Int) {
        this.name = name
        this.id = id
    }

    fun printVar() {
        Log.d(tag, "name:$name,id:$id")
    }
}