// Author : Shahil Sabbag
// Date : 25th August 19
/*********START**********/

// header guard
#ifndef _LOGS_H_
#define _LOGS_H_

// C++ header Files
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Socket header files
#ifdef WIN32
// for Windows
#include <windows.h>
#include <process.h>
#else
// for POSIX
#include <errno.h>
#include <pthread.h>
#endif //end of IF for socket file header's IF

namespace FlexibleLog{
    //Recomemded direct interface for Logging
    // v= verbosity of the called log_level
    // s= data to be logged, can be in string,stream or char array
    // l= log_level i.e FATAL, ERROR, WARN etc.,
    // b= boolean value, true or false
    
    #define FATAL(v,s)  Logger:: getInstance()->FATAL(v,s)
    #define FATAL(s)    Logger:: getInstance()->FATAL(s)

    #define ERROR(v,s)  Logger:: getInstance()->ERROR(v,s)
    #define ERROR(s)    Logger:: getInstance()->ERROR(s)

    #define ALWAYS(v,s) Logger:: getInstance()->ALWAYS(v,s)
    #define ALWAYS(s)   Logger:: getInstance()->ALWAYS(s)

    #define ALARM(v,s)  Logger:: getInstance()->ALARM(v,s)
    #define ALARM(s)    Logger:: getInstance()->ALARM(s)

    #define WARN(v,s)   Logger:: getInstance()->WARN(v,s)
    #define WARN(s)     Logger:: getInstance()->WARN(s)

    #define INFO(v,s)   Logger:: getInstance()->INFO(v,s)
    #define INFO(s)     Logger:: getInstance()->INFO(s)

    #define DEBUG(v,s)  Logger:: getInstance()->DEBUG(v,s)
    #define DEBUG(s)    Logger:: getInstance()->DEBUG(s)

    #define LOG(l,b,s)  Logger:: getInstance()->LOG(v,s)
    #define LOG(s)      Logger:: getInstance()->LOG(s)

    // enum for LOG_LEVEL
    typedef enum LOG_LEVEL{
        L_NOLOG,
        L_DEBUG,
        L_INFO,
        L_WARN,
        L_ALARM,
        L_ALWAYS,
        L_ERROR,
        L_FATAL,
        NUM_OF_LOG_LEVEL
    }LogLevel;

    //enum for LOG_VERBOSITY
    typedef enum LOG_VERBOSITY{
        V_NONE,
        V_PRIMARY,
        V_SECONDRY,
        V_GOSSIP,
        NUM_OF_VERBOSITY_LEVEL
    }LogVerbosity;

    //enum for LOG_TYPE
    typedef enum{
        T_NOWHERE,
        T_CONSOLE,
        T_FILE
    }LogType;
    class Logger{
    public:
        static Logger* getInstance() throw();
        //Interface for FATAL Log

    };
}
