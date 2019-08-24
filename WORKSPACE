load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
   name = "rules_foreign_cc",
   strip_prefix = "rules_foreign_cc-e3f4b5e0bc9dac9cf036616c13de25e6cd5051a2",
   urls = [
      "https://github.com/bazelbuild/rules_foreign_cc/archive/e3f4b5e0bc9dac9cf036616c13de25e6cd5051a2.tar.gz",
   ],
   sha256 = "136470a38dcd00c7890230402b43004dc947bf1e3dd0289dd1bd2bfb1e0a3484"
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
   name = "com_google_zetasql",
   strip_prefix = "zetasql-2019.07.1",
   urls = [
      "https://github.com/google/zetasql/archive/2019.07.1.tar.gz",
   ],
   sha256 = "88871fe511cce67e86321f9eb69cd8f81218a9415f41dff36b066a23b483bf06"
)

load("@com_google_zetasql//:zetasql_deps.bzl", "zetasql_deps")
zetasql_deps()

http_archive(
    name = "io_bazel_rules_go",
    urls = ["https://github.com/bazelbuild/rules_go/releases/download/0.18.3/rules_go-0.18.3.tar.gz"],
    sha256 = "86ae934bd4c43b99893fc64be9d9fc684b81461581df7ea8fc291c816f5ee8c5",
)
load("@io_bazel_rules_go//go:deps.bzl", "go_rules_dependencies", "go_register_toolchains")
go_rules_dependencies()
go_register_toolchains()
