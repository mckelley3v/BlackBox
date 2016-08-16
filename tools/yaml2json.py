#!/usr/bin/python

from __future__ import print_function
import re
import yaml
import json
import argparse
import sys
import os
import traceback

from collections import OrderedDict

def filter_dict(old_dict, regex):
    if isinstance(old_dict, OrderedDict):
        return OrderedDict([(k, filter_dict(v, regex)) for k, v in old_dict.iteritems() if regex.match(k)])

    return old_dict

class YamlLoader(yaml.Loader):
    def __init__(self, *args, **kwargs):
        super(YamlLoader, self).__init__(*args, **kwargs)
        self.add_constructor(yaml.resolver.BaseResolver.DEFAULT_MAPPING_TAG, YamlLoader.construct_dict)
        self.add_constructor("!include-file", YamlLoader.construct_include)
        if "root" in kwargs:
            self.root = kwargs["root"]
        elif isinstance(self.stream, file):
            self.root = os.path.dirname(self.stream.name)
        else:
            self.root = os.path.curdir

    def construct_dict(self, node):
        self.flatten_mapping(node)
        return OrderedDict(self.construct_pairs(node))

    def construct_include(self, node):
        root = self.root
        file_path = os.path.join(self.root, self.construct_scalar(node))
        self.root = os.path.dirname(file_path)
        data = None
        with open(file_path, "r") as fin:
            data = self.load(fin)
        self.root = root

        return data

def yaml2json(yaml_file, json_file, filter, indent):
    yaml_dict = yaml.load(yaml_file, YamlLoader)
    if filter:
        yaml_dict = filter_dict(yaml_dict, filter)

    json.dump(yaml_dict, json_file, separators = (",", ": "), indent = indent)
    json_file.write("\n")

def regex_type(arg):
    try:
        return re.compile(arg)
    except:
        traceback.print_exc()
        raise argparse.ArgumentTypeError("Invalid regex")

def main(argv):
    parser = argparse.ArgumentParser(description = "Convert YAML to JSON")
    parser.add_argument("--yaml_file",
                        "-i",
                        type = argparse.FileType("r"),
                        default = sys.stdin,
                        help = "YAML input file")
    parser.add_argument("--filter",
                        "-f",
                        type = regex_type,
                        default = None)
    parser.add_argument("--json_file",
                        "-o",
                        type = argparse.FileType("w"),
                        default = sys.stdout,
                        help = "JSON output file")
    parser.add_argument("--indent",
                        default = 4,
                        help = "Number of spaces to indent")

    args = parser.parse_args(argv[1:])

    yaml2json(args.yaml_file,
              args.json_file,
              args.filter,
              args.indent)

if __name__ == "__main__":
    sys.exit(main(sys.argv))
