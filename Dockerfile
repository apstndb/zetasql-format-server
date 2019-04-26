FROM ubuntu:bionic AS build-env
RUN apt-get update && apt-get install -y bison flex git pkg-config zip g++ zlib1g-dev unzip python wget default-jdk libfl-dev
RUN wget https://github.com/bazelbuild/bazel/releases/download/0.24.1/bazel-0.24.1-installer-linux-x86_64.sh && bash bazel-0.24.1-installer-linux-x86_64.sh
# RUN git clone https://github.com/google/zetasql.git
RUN mkdir /work
WORKDIR /work
COPY CROSSTOOL WORKSPACE BUILD /work/
RUN bazel build '@com_google_zetasql//zetasql/parser:parser'
COPY formatsql.cc formatsql.h main.go /work/
RUN bazel build ...
ENTRYPOINT ["/workbazel-bin/linux_amd64_stripped/zetasql-server"]

FROM ubuntu:bionic
COPY --from=build-env /work/bazel-bin/linux_amd64_stripped/zetasql-server ./
ENTRYPOINT ["./zetasql-server"]
