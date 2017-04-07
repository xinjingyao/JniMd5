#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#include <malloc.h>
#include <ctype.h>
#include "com_example_yao_jnimd5_Md5Utils.h"
#include "md5.h"

char *join3(char *, char *);
char *toUpperCase(char *);
char *md5Encrypt(char *, unsigned char*);
char *jstringTostring(JNIEnv *, jstring);

#define MD5_KEY  "123"


JNIEXPORT jstring JNICALL Java_com_example_yao_jnimd5_Md5Utils_getRandomNum
  (JNIEnv *env, jclass clazz, jstring jstr, jboolean jbool){


//    把java字符串转换为c语言的
    char *beforeStr = (char *) (*env)->GetStringUTFChars(env, jstr, 0);
//    char *key = MD5_KEY;
//    char *str = join3(szText, key);
//    char *str = szText;

    MD5_CTX context = {0};
    MD5Init(&context);
    MD5Update(&context, beforeStr, strlen(beforeStr));
    unsigned char dest[16] = {0};
    MD5Final(dest, &context);

    int i = 0;
    char szMd5[32] = {0};
    for (i = 0; i < 16; i++) {
        sprintf(szMd5, "%s%02x", szMd5, dest[i]);
    }
    unsigned char b = jbool;
    // 释放引用
    (*env)->ReleaseStringUTFChars(env, jstr, beforeStr);
    return b == 1 ? (*env)->NewStringUTF(env, toUpperCase(szMd5)):(*env)->NewStringUTF(env, szMd5);
  }



// java的string转换成c的string（ GetStringUTFChars(env, jstr, 0)也可以）
char* jstringTostring(JNIEnv* env, jstring jstr)
{
    char* rtn = NULL;
    jclass clsstring = (*env)->FindClass(env, "java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env, "utf-8");
    jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)(*env)->CallObjectMethod(env, jstr, mid, strencode);
    jsize alen = (*env)->GetArrayLength(env, barr);
    jbyte* ba = (*env)->GetByteArrayElements(env, barr, JNI_FALSE);
    if (alen > 0)
    {
        rtn = (char*)malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env, barr, ba, 0);
    return rtn;
}

    // md5加密方法，但是报错
  char *md5Encrypt(char *beforeStr, unsigned char *b) {
      MD5_CTX context = {0};
      MD5Init(&context);
      MD5Update(&context, beforeStr, strlen(beforeStr));
      unsigned char dest[16] = {0};
      MD5Final(dest, &context);
      // 释放引用
//      (*env)->ReleaseStringUTFChars(env, jstr, str);
      int i = 0;
      char resultMd5[32] = {0};
      for (i = 0; i < 16; i++) {
          sprintf(resultMd5, "%s%02x", resultMd5, dest[i]);
      }
      return b==1 ? toUpperCase(resultMd5) : resultMd5;
  }

   // 两个字符串相加
  char *join3(char *s1, char *s2) {
      char *result = malloc(strlen(s1) + strlen(s2) + 1);//+1 for the zero-terminator
      //in real code you would check for errors in malloc here
      if (result == NULL) exit(1);

      strcpy(result, s1);
      strcat(result, s2);

      return result;
  }
  // 小写字母转成大写
  char *toUpperCase(char *s) {
        int i;

        for(i=0;s[i]!='\0';i++)
            if(s[i]<= 'z' && s[i]>='a')//是小写字符
                s[i]-= 'a'-'A';//转成大写
        return s;
  }

