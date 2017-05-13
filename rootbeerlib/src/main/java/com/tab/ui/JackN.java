package com.tab.ui;

/**
 * Created by mat on 19/06/15.
 */
public class JackN {

    /**
     * Loads the C/C++ libraries statically
     */
    static {
        System.loadLibrary("android-logger");
    }

    // named deceivingly to avoid reverse engineers attention
    // tricky to handle in pro-guard since its a native implementation and
    // no automated method is found to handle it

    public native int checkForR(Object[] pathArray); // check for root
    public native int setLogDebugMessages(boolean logDebugMessages);
    // check for build tags
    public native int checkBuildT();

}
