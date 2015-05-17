#!/usr/bin/python

from __future__ import print_function
import os
import sys
import ast
import json
import argparse

def prettify_gyp(fin, fout, indent):
    gyp_dict = ast.literal_eval(fin.read())
    json_str = json.dumps(gyp_dict,
                          sort_keys = True,
                          indent = indent,
                          separators = (',', ': '))
    print(json_str, file = fout)

def main(argv):
    parser = argparse.ArgumentParser(description = "Prettify GYP files.")
    parser.add_argument("dir",
                        help = "the root directory containing GYP files")
    parser.add_argument("--exclude",
                        nargs = "*",
                        help = "exclude GYP files inside these directories")
    parser.add_argument("--indent",
                        type = int,
                        default = 4,
                        choices = xrange(1, 9),
                        help = "the JSON indent size")

    args = parser.parse_args()

    for root, dirs, files in os.walk(args.dir):
        for file in files:
            if file.endswith((".gyp", ".gypi")):
                if not any([root.startswith(exclude) for exclude in args.exclude or []]):
                    path = os.path.join(root, file)
                    temp = path + ".tmp"
                    with open(temp, "w") as fout:
                        with open(path, "r") as fin:
                            prettify_gyp(fin,
                                         fout,
                                         args.indent)
                    os.rename(temp, path)

if __name__ == "__main__":
    sys.exit(main(sys.argv))
