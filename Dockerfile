FROM marketplace.gcr.io/google/bazel:latest AS build-env
RUN apt-get update && apt-get install --no-install-recommends -y bison flex
RUN mkdir /work
WORKDIR /work
COPY CROSSTOOL WORKSPACE BUILD formatsql.cc formatsql.h main.go /work/
RUN bazel build \
  --incompatible_disable_deprecated_attr_params=false \
  --incompatible_string_join_requires_strings=false \
  --incompatible_new_actions_api=false \
  --incompatible_require_ctx_in_configure_features=false \
  --incompatible_depset_is_not_iterable=false \
  --incompatible_no_support_tools_in_action_inputs=false \
  --host_force_python=PY2 \
  ...

FROM gcr.io/distroless/cc
# FROM marketplace.gcr.io/google/ubuntu1604:latest
COPY --from=build-env /work/bazel-bin/linux_amd64_stripped/zetasql-server ./
ENTRYPOINT ["./zetasql-server"]
