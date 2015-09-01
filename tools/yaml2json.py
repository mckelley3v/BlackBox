#!/usr/bin/python

from __future__ import print_function
import yaml
import json
import argparse
import sys

from collections import OrderedDict

def yaml_load(yaml_file, Loader = yaml.Loader):
    class OrderedLoader(Loader):
        pass

    def construct_mapping(loader, node):
        loader.flatten_mapping(node)
        return OrderedDict(loader.construct_pairs(node))

    OrderedLoader.add_constructor(yaml.resolver.BaseResolver.DEFAULT_MAPPING_TAG, construct_mapping)
    return yaml.load(yaml_file, OrderedLoader)

def yaml2json(yaml_file, json_file, indent):
    yaml_dict = yaml_load(yaml_file)
    json.dump(yaml_dict, json_file, separators = (',', ': '), indent = indent)
    json_file.write('\n')

def main(argv):
    parser = argparse.ArgumentParser(description = "Convert YAML to JSON")
    parser.add_argument("--yaml_file",
                        "-i",
                        type = argparse.FileType("r"),
                        default = sys.stdin,
                        help = "YAML input file")
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
              args.indent)

if __name__ == '__main__':
    sys.exit(main(sys.argv))
