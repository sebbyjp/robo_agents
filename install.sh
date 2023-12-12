#!/bin/sh
Help()
{
    # Display Help
    echo "Install package globally."
    echo
    echo "Syntax: sh install.sh [-c|n]"
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


sh build.sh -c $CXX_STANDARD
cd build && make install
cd .. && rm -rf build
