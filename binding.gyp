{
    "targets": [
        {
            "target_name": "numnjs",
            "sources": [
                "src/shared/errors.cpp",
                "src/shared/handlers.cpp",
                "src/shared/inputs.cpp",
                "src/shared/njsarrays.cpp",
                "src/shared/returns.cpp",
                "src/shared/tools.cpp",
                "src/trigonometric.cpp",
                "src/hyperbolic.cpp",
                "src/rounding.cpp",
                "src/sums.cpp",
                "src/exp_logs.cpp",
                "src/arithmetic.cpp",
                "src/miscellaneous.cpp",
                "src/matrix.cpp",
                "src/statistics.cpp",
                "src/numnjs.cpp"
            ],
            "cflags": [
                "-std=c++11",
                "-fopenmp",
                "-pthread",
                "-Wno-deprecated"
            ],
        }
    ]
}
