#include <jni.h>
#include "zieln_com_myptrace_MainActivity.h"
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "defs.h"
#include <android/log.h>

#if  defined(__x86_64__)
	#include <sys/reg.h>
	#include <sys/user.h>
#else
	#include <sys/user.h>
	#include <asm/ptrace.h>
#endif


#ifdef __x86_64__
#define SC_NUMBER  (8 * ORIG_RAX)
#define SC_RETCODE (8 * RAX)
#else
#define SC_NUMBER  (4 * ORIG_EAX)
#define SC_RETCODE (4 * EAX)
#endif


#define LOG_TAG "MYLOG"

pid_t child;
