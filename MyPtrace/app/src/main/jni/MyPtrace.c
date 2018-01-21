#include "MyPtrace.h"

JNIEXPORT jint JNICALL Java_zieln_com_myptrace_MainActivity_MyPtrace  (JNIEnv *env, jobject obj)
  {
    child = fork();
    if(child < 0){
        return errno;
    }
    if(child == 0){
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        kill(getpid(), SIGSTOP);
        sleep(5);
        _exit(1);

    }
    else{

        int status;
        while(1){
            if(wait(&status) < 0)
                break;

            if (WIFEXITED(status) || WIFSIGNALED(status) )
                break;

            long sc_number, sc_retcode;
            #if defined( __x86_64__) || defined(__i386__)
            sc_number = ptrace(PTRACE_PEEKUSER, child, SC_NUMBER, NULL);
            if(sc_number != -1)
                __android_log_print(ANDROID_LOG_INFO, LOG_TAG, "syscall = %ld", sc_number);
            #endif

             ptrace(PTRACE_SYSCALL, child, NULL, NULL);

        }


        return 0;
    }

  }

  JNIEXPORT jint JNICALL Java_zieln_com_myptrace_MainActivity_getChildPid (JNIEnv *env, jobject obj)
  {
        return child;
  }
