#ifndef MYLOG_H
#define MYLOG_H
#include <string>
#include <iostream>
using namespace std;
namespace myLog {
    static int i = 0;
    void print(std::string s){
        std::cout<< s << i++ << endl;
    }
}
#endif // MYLOG_H
