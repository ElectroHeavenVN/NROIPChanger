package com.ehvn.nroipchanger;

import android.app.Activity;
import android.content.Context;
import android.widget.Toast;

public class Main {

    public static Context mainActivity = null;

    //Load lib
    static {
        // When you change the lib name, change also on Android.mk file
        // Both must have same name
        System.loadLibrary("NROIPChanger");
    }

    private static native void CheckOverlayPermission(Context context);

    private static native void Init(Context context);

//    public static void StartWithoutPermission(Context context) {
//        CrashHandler.init(context, true);
//        if (context instanceof Activity) {
//            //Check if context is an Activity.
//            Menu menu = new Menu(context);
//            menu.SetWindowManagerActivity();
//            menu.ShowMenu();
//        } else {
//            Toast.makeText(context, "Failed to launch the mod menu\n", Toast.LENGTH_LONG).show();
//        }
//    }

    public static void Start(Context context) {
        mainActivity = context;
        CrashHandler.init(context, false);
        CheckOverlayPermission(context);
        Init(context);  //Init after the user grants the permission
    }
}
