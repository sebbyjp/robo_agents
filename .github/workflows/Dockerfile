# Container image that runs your code
ARG OS=ubuntu
ARG OS_VERSION=latest
ARG CPU_ARCH=amd64
ARG BASE_IMAGE=${CPU_ARCH}/${OS}:${OS_VERSION}
FROM ${BASE_IMAGE}

ARG PACKAGE_NAME=robo_agents
ARG PYTHON_VERSION=python3.8
ARG CXX_COMPILER=g++
ARG C_COMPILER=gcc
ARG CMAKE_VERSION=3.14
ARG CXX_STANDARD=17
ARG CPU_ARCH=x86_64

ENV PACKAGE_NAME=${PACKAGE_NAME}
ENV PYTHON_VERSION=${PYTHON_VERSION}
ENV CXX_COMPILER=${CXX_COMPILER}
ENV C_COMPILER=${C_COMPILER}
ENV CMAKE_VERSION=${CMAKE_VERSION}
ENV CXX_STANDARD=${CXX_STANDARD}
ENV CPU_ARCH=${CPU_ARCH}

# TODO(speralta): Read in args from github actions.
# Copies your code file from your action repository to the filesystem path `/` of the container
RUN mkdir -p  /${PACKAGE_NAME}
COPY . /${PACKAGE_NAME}/.
COPY .github/workflows/build_and_test.sh /${PACKAGE_NAME}/.
RUN apt-get update && apt-get -y upgrade  && apt-get install sudo
RUN sudo chmod +rwx  /${PACKAGE_NAME}/build_and_test.sh 


# Code file to execute when the docker container starts up (`entrypoint.sh`)
# ENTRYPOINT ["/build_and_test.sh"]
