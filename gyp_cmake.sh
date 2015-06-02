#!/bin/sh

export PYTHONPATH=./external_tools/gyp/pylib:$PYTHONPATH
python gen_proj.py --ignore-environment --format=cmake --generator-output=build/cmake -G output_dir=.