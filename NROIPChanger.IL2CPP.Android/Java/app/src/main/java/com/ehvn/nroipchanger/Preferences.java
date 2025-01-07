package com.ehvn.nroipchanger;

import android.annotation.TargetApi;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.Build;

import java.util.LinkedHashSet;
import java.util.Set;

public class Preferences {
    private static SharedPreferences sharedPreferences;
    private static Preferences prefsInstance;
    public static Context context;
    public static boolean loadPref, isExpanded;

    private static final String LENGTH = "_length";
    private static final String DEFAULT_STRING_VALUE = "";
    private static final int DEFAULT_INT_VALUE = 0; //-1
    private static final double DEFAULT_DOUBLE_VALUE = 0d; //-1d
    private static final float DEFAULT_FLOAT_VALUE = 0f; //-1f
    private static final long DEFAULT_LONG_VALUE = 0L; //-1L
    private static final boolean DEFAULT_BOOLEAN_VALUE = false;

    public static native void Changes(Context context, int featNum, String featName, int value, long Lvalue, boolean isOn, String inputText);

    public static void changeFeatureInt(String featureID, int featureNum, int value) {
        Preferences.with(context).writeInt(featureNum, value);
        Changes(context, featureNum, featureID, value, 0, false, null);
    }

    public static void changeFeatureLong(String featureID, int featureNum, long Lvalue) {
        Preferences.with(context).writeLong(String.valueOf(featureNum), Lvalue);
        Changes(context, featureNum, featureID, 0, Lvalue, false, null);
    }

    public static void changeFeatureString(String featureID, int featureNum, String inputString) {
        Preferences.with(context).writeString(featureNum, inputString);
        Changes(context, featureNum, featureID, 0, 0, false, inputString);
    }

    public static void changeFeatureBool(String featureID, int featureNum, boolean bool) {
        Preferences.with(context).writeBoolean(featureNum, bool);
        Changes(context, featureNum, featureID, 0, 0, bool, null);
    }

    public static int readFeatureInt(int featureNum) {
        return Preferences.with(context).readInt(featureNum);
    }

    public static long readFeatureLong(int featureNum) {
        return Preferences.with(context).readLong(String.valueOf(featureNum));
    }

    public static String readFeatureString(int featureNum) {
        return Preferences.with(context).readString(featureNum);
    }

    public static boolean readFeatureBool(int featureNum) {
        return Preferences.with(context).readBoolean(featureNum);
    }

    public static int loadPrefInt(String featureID, int featureNum) {
        if (loadPref) {
            int value = readFeatureInt(featureNum);
            Changes(context, featureNum, featureID, value , 0, false, null);
            return value;
        }
        return 0;
    }

    public static long loadPrefLong(String featureID, int featureNum) {
        if (loadPref) {
            long Lvalue = readFeatureLong(featureNum);
            Changes(context, featureNum, featureID, 0, Lvalue, false, null);
            return Lvalue;
        }
        return 0;
    }

    public static boolean loadPrefBool(String featureID, int featureNum, boolean bDef) {
        boolean bool = readFeatureBool(featureNum);
        if (featureNum == -1) {
            loadPref = bool;
        }
        if (featureNum == -3) {
            isExpanded = bool;
        }
        if (loadPref || featureNum < 0) {
            bDef = bool;
        }

        Changes(context, featureNum, featureID, 0,0, bDef, null);
        return bDef;
    }

    public static String loadPrefString(String featureID, int featureNum) {
        if (loadPref || featureNum <= 0) {
            String text = readFeatureString(featureNum);
            Changes(context, featureNum, featureID, 0,0, false, text);
            return text;
        }
        return "";
    }

    private Preferences(Context context) {
        sharedPreferences = context.getApplicationContext().getSharedPreferences(
                context.getPackageName() + "_preferences",
                Context.MODE_PRIVATE
        );
    }

    private Preferences(Context context, String preferencesName) {
        sharedPreferences = context.getApplicationContext().getSharedPreferences(
                preferencesName,
                Context.MODE_PRIVATE
        );
    }

    /**
     * @param context
     * @return Returns a 'Preferences' instance
     */
    public static Preferences with(Context context) {
        if (prefsInstance == null) {
            prefsInstance = new Preferences(context);
        }
        return prefsInstance;
    }

    /**
     * @param context
     * @param forceInstantiation
     * @return Returns a 'Preferences' instance
     */
    public static Preferences with(Context context, boolean forceInstantiation) {
        if (forceInstantiation) {
            prefsInstance = new Preferences(context);
        }
        return prefsInstance;
    }

    /**
     * @param context
     * @param preferencesName
     * @return Returns a 'Preferences' instance
     */
    public static Preferences with(Context context, String preferencesName) {
        if (prefsInstance == null) {
            prefsInstance = new Preferences(context, preferencesName);
        }
        return prefsInstance;
    }

    /**
     * @param context
     * @param preferencesName
     * @param forceInstantiation
     * @return Returns a 'Preferences' instance
     */
    public static Preferences with(Context context, String preferencesName, boolean forceInstantiation) {
        if (forceInstantiation) {
            prefsInstance = new Preferences(context, preferencesName);
        }
        return prefsInstance;
    }

    // String related methods

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public String readString(String what) {
        return sharedPreferences.getString(what, DEFAULT_STRING_VALUE);
    }

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public String readString(int what) {
        try {
            return sharedPreferences.getString(String.valueOf(what), DEFAULT_STRING_VALUE);
        } catch (java.lang.ClassCastException ex) {
            return "";
        }
    }

    /**
     * @param what
     * @param defaultString
     * @return Returns the stored value of 'what'
     */
    public String readString(String what, String defaultString) {
        return sharedPreferences.getString(what, defaultString);
    }

    /**
     * @param where
     * @param what
     */
    public void writeString(String where, String what) {
        sharedPreferences.edit().putString(where, what).apply();
    }

    /**
     * @param where
     * @param what
     */
    public void writeString(int where, String what) {
        sharedPreferences.edit().putString(String.valueOf(where), what).apply();
    }

    // int related methods

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public int readInt(String what) {
        return sharedPreferences.getInt(what, DEFAULT_INT_VALUE);
    }

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public int readInt(int what) {
        try {
            return sharedPreferences.getInt(String.valueOf(what), DEFAULT_INT_VALUE);
        } catch (java.lang.ClassCastException ex) {
            return 0;
        }
    }

    /**
     * @param what
     * @param defaultInt
     * @return Returns the stored value of 'what'
     */
    public int readInt(String what, int defaultInt) {
        return sharedPreferences.getInt(what, defaultInt);
    }

    /**
     * @param where
     * @param what
     */
    public void writeInt(String where, int what) {
        sharedPreferences.edit().putInt(where, what).apply();
    }

    /**
     * @param where
     * @param what
     */
    public void writeInt(int where, int what) {
        sharedPreferences.edit().putInt(String.valueOf(where), what).apply();
    }

    // double related methods

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public double readDouble(String what) {
        if (!contains(what))
            return DEFAULT_DOUBLE_VALUE;
        return Double.longBitsToDouble(readLong(what));
    }

    /**
     * @param what
     * @param defaultDouble
     * @return Returns the stored value of 'what'
     */
    public double readDouble(String what, double defaultDouble) {
        if (!contains(what))
            return defaultDouble;
        return Double.longBitsToDouble(readLong(what));
    }

    /**
     * @param where
     * @param what
     */
    public void writeDouble(String where, double what) {
        writeLong(where, Double.doubleToRawLongBits(what));
    }

    // float related methods

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public float readFloat(String what) {
        return sharedPreferences.getFloat(what, DEFAULT_FLOAT_VALUE);
    }

    /**
     * @param what
     * @param defaultFloat
     * @return Returns the stored value of 'what'
     */
    public float readFloat(String what, float defaultFloat) {
        return sharedPreferences.getFloat(what, defaultFloat);
    }

    /**
     * @param where
     * @param what
     */
    public void writeFloat(String where, float what) {
        sharedPreferences.edit().putFloat(where, what).apply();
    }

    // long related methods

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public long readLong(String what) {
        return sharedPreferences.getLong(what, DEFAULT_LONG_VALUE);
    }

    /**
     * @param what
     * @param defaultLong
     * @return Returns the stored value of 'what'
     */
    public long readLong(String what, long defaultLong) {
        return sharedPreferences.getLong(what, defaultLong);
    }

    /**
     * @param where
     * @param what
     */
    public void writeLong(String where, long what) {
        sharedPreferences.edit().putLong(where, what).apply();
    }

    // boolean related methods

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public boolean readBoolean(String what) {
        return sharedPreferences.getBoolean(what, DEFAULT_BOOLEAN_VALUE);
    }

    /**
     * @param what
     * @return Returns the stored value of 'what'
     */
    public boolean readBoolean(int what) {
        return sharedPreferences.getBoolean(String.valueOf(what), DEFAULT_BOOLEAN_VALUE);
    }

    /**
     * @param what
     * @param defaultBoolean
     * @return Returns the stored value of 'what'
     */
    public boolean readBoolean(String what, boolean defaultBoolean) {
        /*if (defaultBoolean == true && !sharedPreferences.contains(what))
            writeBoolean(what, true);*/
        return sharedPreferences.getBoolean(what, defaultBoolean);
    }

    /**
     * @param what
     * @param defaultBoolean
     * @return Returns the stored value of 'what'
     */
    public boolean readBoolean(int what, boolean defaultBoolean) {
        /*if (defaultBoolean == true && !sharedPreferences.contains(String.valueOf(what)))
            writeBoolean(what, true);*/
        try {
            return sharedPreferences.getBoolean(String.valueOf(what), defaultBoolean);
        } catch (java.lang.ClassCastException ex) {
            return defaultBoolean;
        }
    }

    /**
     * @param where
     * @param what
     */
    public void writeBoolean(String where, boolean what) {
        sharedPreferences.edit().putBoolean(where, what).apply();
    }

    /**
     * @param where
     * @param what
     */
    public void writeBoolean(int where, boolean what) {
        sharedPreferences.edit().putBoolean(String.valueOf(where), what).apply();
    }

    /**
     * @param key
     * @return Returns if that key exists
     */
    public boolean contains(final String key) {
        return sharedPreferences.contains(key);
    }

    /**
     * Clear all the preferences
     */
    public void clear() {
        sharedPreferences.edit().clear().apply();
    }
}