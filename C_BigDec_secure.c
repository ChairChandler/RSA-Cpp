#include "C_BigDec_secure.h"
#include <windows.h>
#include <pthread.h>
#include <stdio.h>

#define DIV 1048576

static void* C_BigDec_secureThread(void *arg)
{
	MEMORYSTATUSEX statex;
	
	do
	{
        GlobalMemoryStatusEx(&statex);

        statex.dwLength=sizeof(statex);

        GlobalMemoryStatusEx(&statex);

    }while(statex.ullAvailPhys/DIV/1000 > 1);
	
    fprintf(stderr,"\n[C_BigDec_secureThread] Memory overflow protection.");
    exit(EXIT_FAILURE);
}

int C_BigDec_secure(void)
{
    static int secure= -1;
    static pthread_t secureThread;

    if(secure)
	{
        secure= 0;
        pthread_create(&secureThread, NULL, C_BigDec_secureThread, NULL);
		return 1;
	}
	else
	{
        secure= -1;
        pthread_kill(secureThread, SIGINT);
		return 0;
	}	
}
