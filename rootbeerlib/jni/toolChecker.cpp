/****************************************************************************
 * File:   toolChecker.cpp
 * Author: Matthew Rollings
 * Date:   19/06/2015
 *
 * Description : Root checking JNI NDK code
 *
 ****************************************************************************/

/****************************************************************************
 *>>>>>>>>>>>>>>>>>>>>>>>>> System Includes <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*
 ****************************************************************************/

// Android headers
#include <jni.h>
#include <android/log.h>

// String / file headers
#include <string.h>
#include <stdio.h>
#include <sys/system_properties.h>

/****************************************************************************
 *>>>>>>>>>>>>>>>>>>>>>>>>>> User Includes <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*
 ****************************************************************************/
#include "toolChecker.h"

/****************************************************************************
 *>>>>>>>>>>>>>>>>>>>>>>>>>> Constant Macros <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*
 ****************************************************************************/

// LOGCAT
#define  LOG_TAG    "JackN"
#define  LOGD(...)  if (DEBUG) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__);
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__);

/* Set to 1 to enable debug log traces. */
static int DEBUG = 1;

/*****************************************************************************
 * Description: Sets if we should log debug messages
 *
 * Parameters: env - Java environment pointer
 *      thiz - javaobject
 * 	bool - true to log debug messages
 *
 *****************************************************************************/
void Java_com_tab_ui_JackN_setLogDebugMessages( JNIEnv* env, jobject thiz, jboolean debug)
{
  if (debug){
    DEBUG = 1;
  }
  else{
    DEBUG = 0;
  }
}


/*****************************************************************************
 * Description: Checks if a file exists
 *
 * Parameters: fname - filename to check
 *
 * Return value: 0 - non-existant / not visible, 1 - exists
 *
 *****************************************************************************/
int exists(const char *fname)
{
    FILE *file;
    if (file = fopen(fname, "r"))
    {
      // LOGD("LOOKING FOR BINARY: %s PRESENT!!!",fname);
        fclose(file);
        return 1;
    }
      // LOGD("LOOKING FOR BINARY: %s Absent :(",fname);
    return 0;
}


int Java_com_tab_ui_JackN_checkBuildT(JNIEnv* env, jobject thiz) {

    int len;
    char build_tags[PROP_VALUE_MAX]; // PROP_VALUE_MAX from <sys/system_properties.h>.
    int result = 0;
//    #define ANDROID_OS_BUILD_TAGS                "ro.build.tags"                     // Comma-separated tags describing the build, like "unsigned,debug".

    len = __system_property_get("ro.build.tags", build_tags); // On return, len will equal (int)strlen(model_id).
    if(len > 0 && strstr(build_tags,"test-keys") != NULL){
        result = 1;
    }

    return result;

}


/*****************************************************************************
 * Description: Checks for root binaries
 *
 * Parameters: env - Java environment pointer
 *      thiz - javaobject
 *
 * Return value: int number of su binaries found
 *
 *****************************************************************************/
int Java_com_tab_ui_JackN_checkForR( JNIEnv* env, jobject thiz, jobjectArray pathsArray )
{

    int binariesFound = 0;

    int stringCount = (env)->GetArrayLength(pathsArray);

    for (int i=0; i<stringCount; i++) {
        jstring string = (jstring) (env)->GetObjectArrayElement(pathsArray, i);
        const char *pathString = (env)->GetStringUTFChars(string, 0);

	binariesFound+=exists(pathString);

	(env)->ReleaseStringUTFChars(string, pathString);
    }

    return binariesFound>0;
}


