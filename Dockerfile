FROM ubuntu:bionic
RUN apt-get update && apt-get install -y bison flex git pkg-config zip g++ zlib1g-dev unzip python wget default-jdk libfl-dev
RUN wget https://github.com/bazelbuild/bazel/releases/download/0.24.1/bazel-0.24.1-installer-linux-x86_64.sh && bash bazel-0.24.1-installer-linux-x86_64.sh
# RUN git clone https://github.com/google/zetasql.git
RUN mkdir /work
WORKDIR /work
COPY main.cc /work/main.cc
COPY WORKSPACE BUILD /work/
RUN bazel build ...
