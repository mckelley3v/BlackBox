#!/usr/bin/python

from __future__ import print_function
import subprocess
import argparse
import sys
import os

Apis = \
[
#    "gl_1_0",
#    "gl_1_1",
#    "gl_1_2",
#    "gl_1_3",
#    "gl_1_4",
#    "gl_1_5",
#    "gl_2_0",
#    "gl_2_1",
#    "gl_3_0",
#    "gl_3_1",
#    "gl_3_2",
    "gl_3_3",
#    "gl_3_0_core",
#    "gl_3_1_core",
#    "gl_3_2_core",
#    "gl_3_3_core",
#    "gl_4_0",
#    "gl_4_1",
#    "gl_4_2",
#    "gl_4_3",
#    "gl_4_4",
#    "gl_4_5",
#    "gl_4_0",
#    "gl_4_1",
#    "gl_4_2",
#    "gl_4_3",
#    "gl_4_4",
#    "gl_4_5",
#    "gl_4_0_core",
#    "gl_4_1_core",
#    "gl_4_2_core",
#    "gl_4_3_core",
#    "gl_4_4_core",
#    "gl_4_5_core",
#    "gles_1_0",
#    "gles_2_0",
#    "gles_3_0",
#    "gles_3_1",
]

LanguageDicts = \
[
#    {
#        "name": "C89",
#        "suffix": "_c89.h",
#    },
    {
        "name": "C99",
        "suffix": "_c99.h",
    },
#    {
#        "name": "C++98",
#        "suffix": "_cpp98.hpp",
#    },
#    {
#        "name": "C++11",
#        "suffix": "_cpp11.hpp",
#    },
]

def TestMain(args):
    if not os.path.exists(args.output_dir):
        os.makedirs(args.output_dir)

    for language_dict in LanguageDicts:
        for api in Apis:
            GLapi_args = \
            [
                "python",
                "GLapi.py",
                "--api %s" % api,
                "--language %s" % language_dict["name"],
                "--output %s" % os.path.join(args.output_dir, "%s%s" % (api, language_dict["suffix"])),
                args.input,
            ]

            GLapi_cmd = " ".join(GLapi_args)
            subprocess.call(GLapi_cmd)

    return 0

def main(argv):
    parser = argparse.ArgumentParser(description = "Test Generate OpenGL API")
    parser.add_argument("--output_dir",
                        "-o",
                        metavar = "PATH",
                        help = "Write output to PATH")
    parser.add_argument("input",
                        help = "Path to GL registry xml")

    args = parser.parse_args(argv[1:])

    return TestMain(args)

if __name__ == '__main__':
    sys.exit(main(sys.argv))
