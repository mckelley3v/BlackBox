#!/usr/bin/python

from __future__ import print_function
import sys
import json
import demjson
import argparse

def prettify_json(fin, fout, indent):
    json_dict = demjson.decode(fin.read())
    json_str = json.dumps(json_dict,
                          sort_keys = True,
                          indent = indent,
                          separators = (',', ': '))
    print(json_str, file = fout)

def main(argv):
    parser = argparse.ArgumentParser(description = "Prettify JSON file.")
    parser.add_argument("input",
                        type = argparse.FileType("r"),
                        default = sys.stdin,
                        help = "the JSON file to make pretty")
    parser.add_argument("--output",
                        dest = "output",
                        type = argparse.FileType("w"),
                        default = sys.stdout,
                        help = "the new and prettier JSON file")
    parser.add_argument("--indent",
                        type = int,
                        default = 4,
                        choices = xrange(1, 9),
                        help = "the JSON indent size")

    args = parser.parse_args()

    prettify_json(args.input,
                  args.output,
                  args.indent)

if __name__ == "__main__":
    sys.exit(main(sys.argv))
