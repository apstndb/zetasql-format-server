load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
git_repository(name = "com_google_zetasql", remote = "https://github.com/apstndb/zetasql.git", commit = "a7485ba1e180b2c1330dc57c2d061faffea6b984")

load("@com_google_zetasql//:zetasql_deps.bzl", "zetasql_deps")
zetasql_deps()
load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()
load("@io_grpc_grpc_java//:repositories.bzl", "grpc_java_repositories")
grpc_java_repositories()
