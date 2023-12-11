# Container image that runs your code
FROM ubuntu:20.04

# Copies your code file from your action repository to the filesystem path `/` of the container
COPY ../.. /.
COPY ./build_and_test.sh /.

RUN apt-get update && apt-get install -y \
    && apt-get install sudo

# Code file to execute when the docker container starts up (`entrypoint.sh`)
# ENTRYPOINT ["/build_and_test.sh"]
