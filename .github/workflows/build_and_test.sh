#!/bin/sh

Help() {
    # Display Help
    echo "Build and test script for robo_agents"
    echo
    echo "Syntax: sh build_and_test.sh [options]"
    echo "options:"
    echo "--python     Python version to use."
    echo "--cmake-version     CMake version to use."
    echo "-i    Install system dependencies."
    echo "--cpu-arc    CPU Architecture to use. (x86_64, aarch64)"
    echo "--os     OS to use. (linux, macos)"
    echo "--cxx-std   CXX Standard to use. (11, 14, 17, 20)"
    echo "-h     Print this Help."
}

INSTALL_SYSTEM_REQUIREMENTS=false
CMAKE_MAJOR_VERSION=3.27
PYTHON_VERSION=3.10
CPU_ARCH=aarch64
OS=linux
CXX_STANDARD=20
# TODO(speralta): Add short flags
#TODO(speralta): Add support for macos
while [ $# -gt 0 ]; do
  case "$1" in
    -h|--help)
      Help
      exit 0
      ;;
    -i |--install-system-requirements=*)
      INSTALL_SYSTEM_REQUIREMENTS=true
      ;;
    --cmake-version=*)
        CMAKE_MAJOR_VERSION="${1#*=}"
        ;;
    --python=*)
        PYTHON_VERSION="${1#*=}"
        ;;
    --cpu-arch=*)
        CPU_ARCH="${1#*=}"
        ;;
    --cxx-std=*)
        CXX_STANDARD="${1#*=}"
        ;;
    --os=*)
        OS="${1#*=}"
        ;;
    *)

      printf "Error: Invalid argument: $1 \n"
      printf "Use -h or --help for more information.\n"
      exit 1
  esac
  shift
done

sudo apt-get update && sudo apt-get -y upgrade
sudo chmod +rwx  /usr/local/

# NOTE Linux must be lowercase for 3.20 and above and uppercase before.
# if (( $(echo "$CMAKE_MAJOR_VERSION > 3.20" |bc -l) )) &&  "$OS" == "linux"; then
#     $OS = "Linux"
# fi
# if ["$CMAKE_MAJOR_VERSION" -gt 3.19] && ["$OS" == "Linux"]; then
#     $OS = "linux"
# fi
# if "arm" in $CPU_ARCH; then
#     $CPU_ARCH = "aarch64"
# fi

echo "CPU_ARCH: $CPU_ARCH"
echo "OS: $OS"
echo "CMAKE_MAJOR_VERSION: $CMAKE_MAJOR_VERSION"

sudo rm -rf build
DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends tzdata
CMAKE_SRC="https://cmake.org/files/v$CMAKE_MAJOR_VERSION/cmake-$CMAKE_MAJOR_VERSION.0-$OS-$CPU_ARCH.sh"
if $INSTALL_SYSTEM_REQUIREMENTS; then
    sudo apt install -y "python$PYTHON_VERSION"
    sudo apt install -y python3-pip
    python3 -m pip install --upgrade pip
    sudo apt install -y git
    sudo apt install -y curl
    echo "Installing CMake from $CMAKE_SRC"
    sudo curl -o cmake_install.sh "$CMAKE_SRC"
    sudo sh cmake_install.sh --skip-license --prefix=/usr/local -y
    # sudo ln -s /opt/cmake/bin/cmake /usr/local/bin/cmake # For cmake 3.28.
fi

sudo sh ./install.sh -c $CXX_STANDARD
sudo sh ./test.sh -c $CXX_STANDARD
