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
#include <unistd.h>

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
using namespace std;
namespace FlexibleLog{

    // enum for LOG_LEVEL
    typedef enum LOG_LEVEL{
        ENABLE_ALL_LOG,
        L_DEBUG,
        L_INFO,
        L_WARN,
        L_ALARM,
        L_ALWAYS,
        L_ERROR,
        L_FATAL,
        DISABLE_ALL_LOG
    }LogLevel;

    //enum for LOG_VERBOSITY
    typedef enum LOG_VERBOSITY{
        DISABLE_ALL_VERBOSITY,
        V_PRIMARY,
        V_SECONDRY,
        V_GOSSIP,
        ENABLE_ALL_VERBOSITY
    }LogVerbosity;

    //enum for LOG_TYPE
    typedef enum LOG_TYPE{
        T_JSON,
        T_CONSOLE,
        T_FILE
    }LogType;

    class MessageBody;
    class Logger{
    public:
        static Logger* getInstance() throw();
        LogVerbosity getVerbosityOfLevel(LogLevel level_){return levelVerbosityMap[level_];}
        LogLevel getMinLogLevel(){return m_minLogLevel;}
        ostringstream&sref();
        void srefClear();
        bool isFileEnabled(){return printFile_;}
        bool isFuncEnabled(){return printFunc_;}
        bool isTimeEnabled(){return printTime_;}
        string getCurrentTime();
        LogType getLogType(){return m_LogType;};
        void logIntoFile(std::string data);

    protected:
        Logger();
        ~Logger();
        void lock();
        void unlock();

    private:
        void logOnConsole(std::string& data);
        Logger(const Logger&obj);
        void operator=(const Logger&obj);
        static Logger* m_Instance;
        ofstream  m_File;
        ostringstream *sl;
        bool printFile_;
        bool printFunc_;
        bool printTime_;
        LogVerbosity levelVerbosityMap [DISABLE_ALL_LOG];
        LogLevel m_minLogLevel;
        LogType m_LogType;


        #ifdef WIN32
        CRITICAL_SECTION m_Mutex;
        #else
        pthread_mutexattr_t m_Attr;
        pthread_mutex_t m_Mutex;
        #endif
    };
    class MessageBody{
    public:

        // MessageBody class have all necessary members to create complete log string.
        // Constructor of the class can be created providing atmost four arguments in macro LOG()
        // Those arguments are should always be in order from LogLevel->LogVerbosity->boolean-condition->string-data
        // So, we can have 16 permutations of such constructors.

        //0000
        MessageBody(const char* file, int line, const char* func,bool loop);

        //0001
        MessageBody(const char* file, int line, const char* func,bool loop,const char* msg);

        //0010
        MessageBody(const char* file, int line, const char* func,bool loop,bool condition);

        //0100
        MessageBody(const char* file, int line, const char* func,bool loop,char verbosity);

        //1000
        MessageBody(const char* file, int line, const char* func,bool loop,int level);

        //0011
        MessageBody(const char* file, int line, const char* func,bool loop,bool condition,const char* msg);

        //0101
        MessageBody(const char* file, int line, const char* func,bool loop,char verbosity,const char* msg);

        //1001
        MessageBody(const char* file, int line, const char* func,bool loop,int level,const char* msg);

        //0110
        MessageBody(const char* file, int line, const char* func,bool loop,char verbosity,bool condition);

        //1010
        MessageBody(const char* file, int line, const char* func,bool loop,int level,bool condition);

        //1100
        MessageBody(const char* file, int line, const char* func,bool loop,int level,char verbosity);

        //0111
        MessageBody(const char* file, int line, const char* func,bool loop,char verbosity,bool condition,const char* msg);

        //1011
        MessageBody(const char* file, int line, const char* func,bool loop,int level,bool condition,const char* msg);

        //1101
        MessageBody(const char* file, int line, const char* func,bool loop,int level,char verbosity,const char* msg);

        //1110
        MessageBody(const char* file, int line, const char* func,bool loop,int level,char verbosity,bool condition);

        //1111
        MessageBody(const char* file, int line, const char* func,bool loop,int level,char verbosity,bool condition,const char* msg);


        string getLevel(LogLevel level_){
            switch (level_) {
                case 0 : return "NOLOG";
                case 1 : return "DEBUG";
                case 2 : return "INFO";
                case 3 : return "WARN";
                case 4 : return "ALARM";
                case 5 : return "ALWAYS";
                case 6 : return "ERROR";
                case 7 : return "FATAL";
                default: return "###";
            }
        }
        string getVerbosity(LogVerbosity verbosity_){
            switch (verbosity_) {
                case 0: return "0";
                case 1: return "P";
                case 2: return "S";
                case 3: return "G";
                default: return "#";
            }
        }
        bool isLoopTrue();
        void logNow(ostringstream &st);

    private:
        const char* msg_;
        bool condition_;
        bool loop_;
        const char *file_;
        const char *func_;
        const int line_;
        LogLevel level_;
        LogVerbosity verbosity_;
    };
} //End of Namespace
typedef FlexibleLog::Logger Logger;
typedef FlexibleLog::MessageBody MessageBody;
#define LOG(a...)  for(MessageBody i(__FILE__,__LINE__,__func__,true,##a);i.isLoopTrue();i.logNow(Logger::getInstance()->sref()))Logger::getInstance()->sref()
#define FATAL(a,b)  LOG(a,b)
#endif // End of LOGS_H_
