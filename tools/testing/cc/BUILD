package(default_visibility = ["//tools/build_defs:internal_pkg"])

licenses(["notice"])  # Apache 2.0

cc_library(
    name = "cli_util",
    srcs = ["cli_util.cc"],
    hdrs = ["cli_util.h"],
    visibility = ["//tools/testing:__subpackages__"],
    deps = [
        "//cc",
        "//cc:binary_keyset_reader",
        "//cc:cleartext_keyset_handle",
        "//cc:config",
        "//cc/config:tink_config",
        "//cc/util:status",
    ],
)

cc_binary(
    name = "aead_cli_cc",
    srcs = ["aead_cli.cc"],
    visibility = ["//tools/testing:__subpackages__"],
    deps = [
        ":cli_util",
        "//cc",
    ],
)

cc_binary(
    name = "hybrid_encrypt_cli_cc",
    srcs = ["hybrid_encrypt_cli.cc"],
    visibility = ["//tools/testing:__subpackages__"],
    deps = [
        ":cli_util",
        "//cc",
    ],
)

cc_binary(
    name = "hybrid_decrypt_cli_cc",
    srcs = ["hybrid_decrypt_cli.cc"],
    visibility = ["//tools/testing:__subpackages__"],
    deps = [
        ":cli_util",
        "//cc",
    ],
)
