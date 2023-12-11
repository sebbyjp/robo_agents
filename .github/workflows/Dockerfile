# Container image that runs your code
FROM ubuntu:20.04

# Copies your code file from your action repository to the filesystem path `/` of the container
COPY . /.
COPY .github/workflows/build_and_test.sh /.

# Code file to execute when the docker container starts up (`entrypoint.sh`)
ENTRYPOINT ["/build_and_test.sh"]