# Robo ML
Machine Learning Infrastructure for Robotics. This is a thread-safe, header-only
library for deep learning in robotics. The interface is based off of Gym and 
TF-Agents.

# Features
- Thread-safe and 10x speed up over std multi-threading libraries with [safe pointers](https://github.com/AlexeyAB/object_threadsafe)
- Can handle upwards of 64 parallel threads without any significant overhead
- Support for 
  - CXX 11 - Latest
  - MacOS Latest
  - Ubuntu 16.04 - Latest
  - CMake 3.14 - Latest
  - arm64 and x86_64 architectures
- CI on all supported platforms with [gtest](https://google.github.io/googletest/quickstart-cmake.html)