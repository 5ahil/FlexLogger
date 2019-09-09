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
using namespace std;
namespace FlexibleLog{
    //Recomemded direct interface for Logging
    // v= verbosity of the called log_level
    // s= data to be logged, can be in string,stream or char array
    // l= log_level i.e FATAL, ERROR, WARN etc.,
    // b= boolean value, true or false


    //#define FATAL_1(s)    Logger:: getInstance()->fatal(s)
/*
    #define ERROR(s,v)  Logger:: getInstance()->error(s,v)
    #define ERROR(s)    Logger:: getInstance()->error(s)

    #define ALWAYS(s,v) Logger:: getInstance()->always(s,v)
    #define ALWAYS(s)   Logger:: getInstance()->always(s)

    #define ALARM(s,v)  Logger:: getInstance()->alarm(s,v)
    #define ALARM(s)    Logger:: getInstance()->alarm(s)

    #define WARN(s,v)   Logger:: getInstance()->warn(s,v)
    #define WARN(s)     Logger:: getInstance()->warn(s)

    #define INFO(s,v)   Logger:: getInstance()->info(s,v)
    #define INFO(s)     Logger:: getInstance()->info(s)

    #define DEBUG(s,v)  Logger:: getInstance()->debug(s,v)
    #define DEBUG(s)    Logger:: getInstance()->debug(s)

    #define LOG(l,b,s)  Logger:: getInstance()->log(s,v)
    #define LOG(s)      Logger:: getInstance()->log(s)
*/
    //update functions goes here

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
    class LogMess;
    class Logger{
    public:
        static Logger* getInstance() throw();
        //Interface for FATAL Log
        //ostringstream& log(string a,int b);
        ostringstream&sref();
        void pr(){
            cout<<(sl)->str();
        }
        void fatal(const char*text,int vebosity,int l)throw();
        void fatal(std::string&str,int vebosity,int l)throw();
        void fatal(std::ostringstream&str,int vebosity,int l)throw();
/*
        //Interface for ERROR Log
        void error(std::string&str,int vebosity=V_PRIMARY)throw();
        void error(std::ostringstream&str,int vebosity=V_PRIMARY)throw();
        void error(const char*text,int vebosity=V_PRIMARY)throw();

        //Interface for ALWAYS Log
        void always(const char*text,int vebosity=V_PRIMARY)throw();
        void always(std::string&str,int vebosity=V_PRIMARY)throw();
        void always(std::ostringstream&str,int vebosity=V_PRIMARY)throw();

        //Interface for ALARM Log
        void alarm(const char*text,int vebosity=V_PRIMARY)throw();
        void alarm(std::string&str,int vebosity=V_PRIMARY)throw();
        void alarm(std::ostringstream&str,int vebosity=V_PRIMARY)throw();

        //Interface for WARN Log
        void warn(const char*text,int vebosity=V_PRIMARY)throw();
        void warn(std::string&str,int vebosity=V_PRIMARY)throw();
        void warn(std::ostringstream&str,int vebosity=V_PRIMARY)throw();

        //Interface for INFO Log
        void info(const char*text,int vebosity=V_PRIMARY)throw();
        void info(std::string&str,int vebosity=V_PRIMARY)throw();
        void info(std::ostringstream&str,int vebosity=V_PRIMARY)throw();

        //Interface for DEBUG Log
        void debug(const char*text,int vebosity=V_PRIMARY)throw();
        void debug(std::string&str,int vebosity=V_PRIMARY)throw();
        void debug(std::ostringstream&str,int vebosity=V_PRIMARY)throw();
*/

    protected:
        Logger();
        ~Logger();
        void lock();
        void unlock();
    private:
        void logIntoFile(std::string& data);
        void logOnConsole(std::string& data);
        Logger(const Logger&obj);
        void operator=(const Logger&obj);
        static Logger* m_Instance;
        std::ofstream  m_File;
        std::ostringstream *sl;
        //static LogVerbosity[NUM_OF_LOG_LEVEL]levelVerbosityMap={V_PRIMARY};
        //LogMess msg;
        LogLevel m_minLogLevel;
        LogType m_LogType;


#ifdef WIN32
        CRITICAL_SECTION m_Mutex;
#else
        pthread_mutexattr_t m_Attr;
        pthread_mutex_t m_Mutex;
#endif
    };
    class LogMess{
    public:

        std::string msg;
        bool iterate_;
        LogMess(string a,int b):msg(a),iterate_(true){
            //st = new ostringstream();
            //iterate_= true;
            cout<<"constrc\n";
            //*st<<a;
        }
        iterate(){
            return iterate_;
        }
        void next(ostringstream &st){
            iterate_ = false;

            msg+=st.str();
            cout<<msg<<" done \n";
        }

    };
}   typedef FlexibleLog::Logger Logger;   //End of Namespace
#define LOG(a,b)  for(FlexibleLog::LogMess d(a,b);d.iterate();d.next(Logger::getInstance()->sref())) cout<<""
#define FATAL(a,b)  LOG(a,b)
#endif // End of LOGS_H_
