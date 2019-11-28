#ifndef GLOBALSFUN_H
#define GLOBALSFUN_H

#ifdef _WIN32
    #include <winsock2.h>
    #include <windows.h>
    #include <WS2tcpip.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif

#include <string>
#include <iostream>
#include "threadpull.h"

using namespace std;

extern ThreadPull* threadPulls; //Переменная хранящая в себе пул всех потоков

template<typename _Fn, typename... _Args>
bool add_threadOnPull(string nameThread,_Fn&& __fn,_Args&&... __args)
{
        //cout << "  = " << sizeof ... (__args)<<endl;

        if(threadPulls->chakeNameThread(nameThread))
        {
            cout <<"Error: This name  '" << nameThread<<"' is already there"<<endl;
            return false;
        }

        auto stopSignal = new promise<bool>;
        auto stopped = new future<void>;
        *stopped = async(launch::async, __fn,__args...,stopSignal->get_future());
        threadPulls->push_back(nameThread,stopSignal,stopped);

        return true;
}

/////////////////////////////////////////////////////////////

typedef signed char qint8;         /* 8 bit signed */
typedef unsigned char quint8;      /* 8 bit unsigned */
typedef short qint16;              /* 16 bit signed */
typedef unsigned short quint16;    /* 16 bit unsigned */
typedef int qint32;                /* 32 bit signed */
typedef unsigned int quint32;      /* 32 bit unsigned */

typedef unsigned int UINT_PTR,*PUINT_PTR;
#if 1
typedef UINT_PTR	SOCKET;
#else
typedef INT_PTR		SOCKET;
#endif

#define INVALID_SOCKET	(SOCKET)(~0)
#define SOCKET_ERROR	(-1)

typedef struct sockaddr		SOCKADDR;
typedef struct sockaddr_in	SOCKADDR_IN;

#endif // GLOBALSFUN_H
