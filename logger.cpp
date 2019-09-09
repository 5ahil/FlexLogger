// Author : Shahil Sabbag
// Date : 26th August 19
/*********START**********/

// C++ header Files
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>

// Actual header file to be Recomemded
#include "logger.h"

using namespace std;
using namespace FlexibleLog;

Logger* Logger::m_Instance = NULL;
//ostringstream* Logger::sl=new ostringstream();
// file name for Logging
const string logFileName = "main.log";

//Logger constructor
Logger::Logger(){
    m_File.open(logFileName.c_str(),ios::out|ios::app);
    sl=new ostringstream();
    m_minLogLevel = L_INFO;
    m_LogType = T_FILE;
    //Initialize mutex
#ifdef WIN32
    InitializeCriticalSection(&m_Mutex);
#else
    int err=0;
    err = pthread_mutexattr_settype(&m_Attr,PTHREAD_MUTEX_ERRORCHECK_NP);
    if (err!=0){
        printf("Failed to set mutex attribute\n");
        exit(0);
    }
    err = pthread_mutex_init(&m_Mutex,&m_Attr);
    if (err!=0){
        printf("Failed to Initialize mutex\n");
        exit(0);
    }
#endif  // End of mutex Initialization
}

//Logger destructor
Logger::~Logger(){
    m_File.close();
    //destroy Mutex
#ifdef WIN32
    DeleteCriticalSection(&m_Mutex);
#else
    pthread_mutexattr_destroy(&m_Attr);
    pthread_mutex_destroy(&m_Mutex);
#endif // End of mutex destruction
}
Logger* Logger::getInstance() throw ()
{
   if (m_Instance == NULL)
   {
      m_Instance = new Logger();
   }

   return m_Instance;
}
ostringstream& Logger::sref(){

    return *sl;
}
//Logger lock
void Logger::lock(){
#ifdef WIN32
    EnterCriticalSection(&m_Mutex);
#else
    pthread_mutex_lock(&m_Mutex);
#endif
}

//logger unlock
void Logger::unlock(){
#ifdef WIN32
    LeaveCriticalSection(&m_Mutex);
#else
    pthread_mutex_unlock(&m_Mutex);
#endif
}

// log into Files
void Logger::logIntoFile(std::string& data){
    lock();
    m_File<<data<<endl;
    unlock();
}

void Logger::logOnConsole(std::string& data){
    cout<<data<<endl;
}
/*ostringstream& Logger::log(string a,int b){
    LogMess d(a,b);
    for(;d.iterate();d.next())return d.sref();
    cout<<"here\n";
    //d.load();
    return d.sref();
}
// FATAL
/*void Logger::fatal(const char*text,int verbosity,int l)throw(){
    string data;
    cout<<"1.veb"<<l<<endl;
    data.append("[FATAL]:");
    //data.append(atoi(__LINE__));
    data.append(text);
    logOnConsole(data);
}
void Logger::fatal(std::string&str,int verbosity,int l)throw(){
    cout<<"2.veb"<<l<<endl;
    fatal(str.data(),verbosity);
}
void Logger::fatal(std::ostringstream&stream,int verbosity,int l)throw(){
string str = stream.str();
cout<<"3.veb"<<l<<endl;
    fatal(str.data(),verbosity);
}*/
