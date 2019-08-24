load("@io_bazel_rules_go//go:def.bzl", "go_binary", "go_library", "go_test")
go_binary(name = "zetasql-server", srcs = ["main.go", "formatsql.cc", "formatsql.h"], pure = "off", cgo = True, cxxopts = ['-std=c++14'], cdeps = [
		"@com_google_zetasql//zetasql/public:sql_formatter",
		])

