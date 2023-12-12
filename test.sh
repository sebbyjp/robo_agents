#!/bin/sh
Help()
{
    # Display Help
    echo "Run tests with CMAKE."
    echo
    echo "Syntax: sh test.sh [-c|n]"
    echo "options:"
    echo "h     Print this Help."
    echo "c     CXX Standard to use. (11, 14, 17, 20)"
    echo
}

CXX_STANDARD=17
while getopts ":hc:" option; do
   case $option in
      h) # display Help
         Help
         exit;;
      c) # CXX_STANDARD
         CXX_STANDARD=$OPTARG;;
     \?) # Invalid option
         echo "Error: Invalid option"
         exit;;
   esac
done


cmake -S. -Bbuild -DBUILD_TESTS=ON -DCMAKE_CXX_STANDARD=$CXX_STANDARD
cmake --build build
cd build && ctest
cd .. && rm -rf build
