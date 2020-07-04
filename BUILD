load("@rules_cc//cc:defs.bzl", "cc_library")
load("@io_bazel_rules_go//go:def.bzl", "go_binary")

go_binary(
    name = "zetasql-server",
    srcs = ["main.go"],
    cdeps = [
        ":formatsql",
    ],
    cgo = True,
    pure = "off",
)

cc_library(
    name = "formatsql",
    srcs = [
        "formatsql.cc",
        "formatsql.h",
        "sql_formatter.cc",
        "sql_formatter.h",
        "unparser.cc",
        "unparser.h",
    ],
    deps = [
        "@com_google_zetasql//zetasql/public:sql_formatter",
    ],
)
