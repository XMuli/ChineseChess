#ifndef MYLOG_H
#define MYLOG_H

#include <string>
#include <iostream>
#include <QVector>
#include <ChessStep.h>

using namespace std;
static int i = 0;

class myLog {
public:
    static void print(std::string s){
        std::cout<< s<< " " << i++ << endl;
    }

};
#endif // MYLOG_H
