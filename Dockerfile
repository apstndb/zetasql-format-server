FROM ubuntu:focal AS build-env
RUN apt-get update && apt-get install -y --no-install-recommends curl ca-certificates gnupg
RUN curl https://bazel.build/bazel-release.pub.gpg | apt-key add -
RUN echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list
RUN apt-get update && apt-get install --no-install-recommends -y make g++ bazel git python3

RUN update-alternatives --install /usr/bin/python python /usr/bin/python3 100

WORKDIR /work

# cache build
COPY .bazelrc CROSSTOOL WORKSPACE /work/
COPY bazel/* /work/bazel/
RUN bazel build '@com_google_zetasql//zetasql/public:sql_formatter'

COPY BUILD *.cc *.h main.go /work/
RUN bazel build ...

FROM gcr.io/distroless/cc
COPY --from=build-env /work/bazel-bin/linux_amd64_stripped/zetasql-server ./
ENTRYPOINT ["./zetasql-server"]
