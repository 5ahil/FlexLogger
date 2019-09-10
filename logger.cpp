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
//ostringstream* Logger::sl=new ostringstream();
// file name for Logging
const string logFileName = "main.log";

//Logger constructor
Logger::Logger(){
    m_File.open(logFileName.c_str(),ios::out|ios::app);
    sl=new ostringstream();
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
bool MessageBody::isLoopTrue(){
    return loop_;
}
void MessageBody::logNow(ostringstream &st){
    loop_ = false;

    if(!condition_)return; //need srefClear
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
    cout<<fullMessage.str()<<"\n";
    Logger::getInstance()->srefClear();
}
