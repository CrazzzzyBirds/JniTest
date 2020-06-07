package com.heima.jnitest

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

/*        var int = JniUtils.instance!!.putBasic(1)
        //Log.d("HM",int.toString())
        sample_text.text = int.toString()*/

        /*    var inputIntArray:IntArray=intArrayOf(0,1,2);
            var returnArray=JniUtils.instance!!.putArray(inputIntArray)
            Log.d("HM", "return array")
            for (element in returnArray){
                Log.d("HM", element.toString())
            }*/


//        var returnString = JniUtils.instance!!.putString("java", arrayOf("a", "b", "c"))
//        Log.d("HM", returnString)

//        JniUtils.instance!!.putObj(Person("java",0))
        JniUtils.instance!!.newObj()
    }


}
