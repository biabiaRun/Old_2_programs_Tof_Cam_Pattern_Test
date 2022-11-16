#!/bin/bash
# this file is to delete the build folder and compile pattern-testing

echo "----- MAKE SURE YOU ARE AT BELOW DIRECTORY $(pwd) "
sleep 2
echo
 
rm -rf build
echo "----- build folder is deleted -----"
sleep 1
echo
echo "----- start to run build.sh -----"
sleep 1
echo

./build.sh

echo 
echo 
scp build/bin/pattern-testing root@10.100.32.150:/usr/bin
#scp build/bin/libplatform.so.0.0.1 root@10.100.32.150:/usr/lib

