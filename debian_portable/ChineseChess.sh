#!/bin/sh  
appname=`basename $0 | sed s,\.sh$,,`  #获取\和.sh之间的字符串

dirname=`dirname $0`  
tmp="${dirname#?}"  

#绝对路径
if [ "${dirname%$tmp}" != "/" ]; then  
dirname=$PWD/$dirname  
fi  

LD_LIBRARY_PATH=$dirname  
export LD_LIBRARY_PATH  
$dirname/$appname "$@"  #"$@" 脚本参数

