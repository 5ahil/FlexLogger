#include <iostream>
#include <sstream>
#include "logger.h"

using namespace std;

int main(){
    //Logger* pLogger = NULL; // Create the object pointer for Logger Class
    //pLogger = Logger::getInstance();
    LOG();
    LOG()<<" hi";
    LOG("wow")<<" Shahil";
    LOG(true)<<" Shahil";
    LOG('1')<<" Shahil";
    LOG(2)<<" Shahil";
    LOG(true,"wow")<<" Shahil";
    LOG('2',"dd")<<" Shahil";
    LOG(7,"sds")<<" Shahil";
    LOG('3',true)<<" Shahil";
    LOG(5,true)<<" Shahil";
    LOG(6,'2')<<" Shahil";
    LOG('2',true,"sqsq")<<" Shahil";
    LOG(1,true,"sqsq")<<" Shahil";
    LOG(3,'3',"sqsq")<<" Shahil";
    LOG(4,'2',true)<<" Shahil";
    LOG(6,'1',true,"wwwe")<<" Shahil";


    //Logger::getInstance()->pr();
    //FATAL("greater");
    //FATAL("great",3);
}
