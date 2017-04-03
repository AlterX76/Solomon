
#ifndef SYNCRONIZEDEFINITION_H

    #define SYNCRONIZEDEFINITION_H

    #if defined (WIN32)
        #include <WinSock2.h>
        #include <thread>

        typedef void                            siginfo_t; // dummy value
        typedef std::thread *                   pthread_t;
        typedef CONDITION_VARIABLE              pthread_cond_t;
        typedef CRITICAL_SECTION                pthread_mutex_t;
    #else
        #include <pthread.h>
    #endif

#endif // SYNCRONIZEDEFINITION_H
