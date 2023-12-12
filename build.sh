#!/bin/sh
set -e # Exit with nonzero exit code if anything fails.
Help()
{
    # Display Help
    echo "Build package with CMAKE."
    echo
    echo "Syntax: sh build.sh [-c|n]"
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

mkdir -p build 
cd build
cmake .. -DCMAKE_CXX_STANDARD=17
cd ..
cmake --build build 
