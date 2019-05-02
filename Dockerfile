FROM marketplace.gcr.io/google/bazel:latest AS build-env
RUN apt-get update && apt-get install --no-install-recommends -y bison flex
RUN mkdir /work
WORKDIR /work
COPY CROSSTOOL WORKSPACE BUILD formatsql.cc formatsql.h main.go /work/
RUN bazel build ...

FROM gcr.io/distroless/cc
# FROM marketplace.gcr.io/google/ubuntu1604:latest
COPY --from=build-env /work/bazel-bin/linux_amd64_stripped/zetasql-server ./
ENTRYPOINT ["./zetasql-server"]
