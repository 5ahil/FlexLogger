#include <iostream>
#include <sstream>
#include "logger.h"

using namespace std;

int main(){
    //Logger* pLogger = NULL; // Create the object pointer for Logger Class
    //pLogger = Logger::getInstance();
    LOG("great",4)<<" hi";
    LOG("wow",4)<<" heyyy";
    Logger::getInstance()->pr();
    //FATAL("greater");
    //FATAL("great",3);
}
