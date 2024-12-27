package com.ehvn.nroipchanger;

import android.app.Activity;
import android.os.Build;
import android.widget.Toast;

public final class Utils {
    public static void ShowToastOnUIThread(final String message, final int duration) {
        if (Main.mainActivity == null)
            return;
        Activity activity = (Activity)Main.mainActivity;
        activity.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                Toast.makeText(activity, message, duration).show();
            }
        });
    }

    public static String GetCurrentLanguage() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N)
            return Main.mainActivity.getResources().getConfiguration().getLocales().get(0).getLanguage();
        else
            return Main.mainActivity.getResources().getConfiguration().locale.getLanguage();
    }
}
