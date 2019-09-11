// Author : Shahil Sabbag
// Date : 26th August 19
/*********START**********/

// C++ header Files
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <unistd.h>

// Actual header file to be Recomemded
#include "logger.h"

using namespace std;
using namespace FlexibleLog;

Logger* Logger::m_Instance = NULL;
// file name for Logging
const string logFileName = "main.log";

//Logger constructor
Logger::Logger(){
    m_File.open(logFileName.c_str(),ios::out|ios::app);
    sl=new ostringstream();
    for(int i=0;i<DISABLE_ALL_LOG;i++) levelVerbosityMap[i]=V_PRIMARY;
    printFile_=true;
    printFunc_=true;
    printTime_=true;
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
void Logger::logIntoFile(std::string data){
    lock();
    m_File<<data<<endl;
    unlock();
}

void Logger::logOnConsole(std::string& data){
    cout<<data<<endl;
}
string Logger::getCurrentTime()
{
   string currTime;
   //Current date/time based on current time
   time_t now = time(0);
   // Convert current time to string
   currTime.assign(ctime(&now));

   // Last charactor of currentTime is "\n", so remove it
   string currentTime = currTime.substr(0, currTime.size()-1);
   return currentTime;
}


//0000
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop):msg_(""),condition_(true),file_(file),line_(line),func_(func),loop_(loop),level_(L_INFO),verbosity_(V_PRIMARY){
   //cout<<"0\n";
}
//0001
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,const char* msg):msg_(msg),condition_(true),file_(file),line_(line),func_(func),loop_(loop),level_(L_INFO),verbosity_(V_PRIMARY){
   //cout<<"inside\n";
   //cout<<msg_<<" "<<msg<<endl;
}
//0010

MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,bool condition):msg_(""),condition_(condition),file_(file),line_(line),func_(func),loop_(loop),level_(L_INFO),verbosity_(V_PRIMARY){
   //loop_=true;cout<<"2\n";
}
//0100
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,char verbosity):msg_(""),condition_(true),file_(file),line_(line),func_(func),loop_(loop),level_(L_INFO),verbosity_(static_cast<LogVerbosity>((int)verbosity-'0')){
   //loop_=true;cout<<"3\n";
}
//1000
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,int level):msg_(""),condition_(true),file_(file),line_(line),func_(func),loop_(loop),level_(static_cast<LogLevel>(level)),verbosity_(V_PRIMARY){
   //loop_=true;cout<<"4\n";
}
//0011
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,bool condition,const char* msg):msg_(msg),condition_(condition),file_(file),line_(line),func_(func),loop_(loop),level_(L_INFO),verbosity_(V_PRIMARY){
   //loop_=true;cout<<"5\n";
}
//0101
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,char verbosity,const char* msg):msg_(msg),condition_(true),file_(file),line_(line),func_(func),loop_(loop),level_(L_INFO),verbosity_(static_cast<LogVerbosity>((int)verbosity-'0')){
   //loop_=true;cout<<"6\n";
}
//1001
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,int level,const char* msg):msg_(msg),condition_(true),file_(file),line_(line),func_(func),loop_(loop),level_(static_cast<LogLevel>(level)),verbosity_(V_PRIMARY){
   //cout<<"7\n";
}
//0110
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,char verbosity,bool condition):msg_(""),condition_(condition),file_(file),line_(line),func_(func),loop_(loop),level_(L_INFO),verbosity_(static_cast<LogVerbosity>((int)verbosity-'0')){
   //cout<<"8\n";
}
//1010
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,int level,bool condition):msg_(""),condition_(condition),file_(file),line_(line),func_(func),loop_(loop),level_(static_cast<LogLevel>(level)),verbosity_(V_PRIMARY){
   //cout<<"09\n";
}
//1100
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,int level,char verbosity):msg_(""),condition_(true),file_(file),line_(line),func_(func),loop_(loop),level_(static_cast<LogLevel>(level)),verbosity_(static_cast<LogVerbosity>((int)verbosity-'0')){
   //cout<<"10\n";
}
//0111
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,char verbosity,bool condition,const char* msg):msg_(msg),condition_(condition),file_(file),line_(line),func_(func),loop_(loop),level_(L_INFO),verbosity_(static_cast<LogVerbosity>((int)verbosity-'0')){
   //cout<<"110\n";
}
//1011
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,int level,bool condition,const char* msg):msg_(msg),condition_(condition),file_(file),line_(line),func_(func),loop_(loop),level_(static_cast<LogLevel>(level)),verbosity_(V_PRIMARY){
    //cout<<"012\n";
}
//1101
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,int level,char verbosity,const char* msg):msg_(msg),condition_(true),file_(file),line_(line),func_(func),loop_(loop),level_(static_cast<LogLevel>(level)),verbosity_(static_cast<LogVerbosity>((int)verbosity-'0')){
   //cout<<"13\n";
}
//1110
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,int level,char verbosity,bool condition):msg_(""),condition_(condition),file_(file),line_(line),func_(func),loop_(loop),level_(static_cast<LogLevel>(level)),verbosity_(static_cast<LogVerbosity>((int)verbosity-'0')){
   //cout<<"140\n";
}
//1111
MessageBody::MessageBody(const char* file, int line, const char* func,bool loop,int level,char verbosity,bool condition,const char* msg):msg_(msg),condition_(condition),file_(file),line_(line),func_(func),loop_(loop),level_(static_cast<LogLevel>(level)),verbosity_(static_cast<LogVerbosity>((int)verbosity-'0')){
   //cout<<"015\n";
}
void Logger::srefClear(){
    sl->str("");
}

bool MessageBody::isLoopTrue(){
    return loop_;
}
void MessageBody::logNow(ostringstream &st){
    loop_ = false;

    if(!condition_){Logger::getInstance()->srefClear();return;} //need srefClear
    if(level_ < L_DEBUG || level_>=DISABLE_ALL_LOG){Logger::getInstance()->srefClear();return;}
    if(verbosity_ <= DISABLE_ALL_VERBOSITY || verbosity_ > V_GOSSIP){Logger::getInstance()->srefClear();return;}
    if(Logger::getInstance()->getMinLogLevel()>level_){Logger::getInstance()->srefClear();return;}
    if(Logger::getInstance()->getVerbosityOfLevel(level_)<verbosity_){Logger::getInstance()->srefClear();return;}


    stringstream fullMessage;
    if(Logger::getInstance()->isTimeEnabled())
    fullMessage<<"["<<Logger::getInstance()->getCurrentTime()<<"] ";
    if(Logger::getInstance()->isFuncEnabled())
    fullMessage<<"["<<string(func_)<<"] ";
    if(Logger::getInstance()->isFileEnabled()){
        fullMessage<<"["<<string(file_);
        fullMessage<<":"<<line_<<"] ";
    }


    #ifdef WIN32
    fullMessage<<"["<<GetCurrentProcessId();
    #else
    fullMessage<<"["<<getpid();
    #endif
    fullMessage<<"] ";
    //msg_+=st.str();
    fullMessage<<getLevel(level_)<<"("<<getVerbosity(verbosity_)<<") [";
    fullMessage<<msg_<<" ";
    fullMessage<<st.str();
    fullMessage<<"]";

    Logger::getInstance()->srefClear();
    LogType logType_ = Logger::getInstance()->getLogType();
    if(logType_ == T_JSON){
        cout<<"Under Process. Will be done soon. Sorry as of now. \nBye!";
    }
    else if(logType_ == T_CONSOLE){
        cout<<fullMessage.str()<<"\n";
    }
    else{
        Logger::getInstance()->logIntoFile(fullMessage.str());
    }
}
