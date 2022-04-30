#! /bin/bash
EXE='ChineseChess'  # 我的程序名
PWD=`pwd`           # 打包的路径
files=`ldd $EXE | awk '{ if(match($3,"^/"))printf("%s "),$3 }'`
cp $files $PWD

