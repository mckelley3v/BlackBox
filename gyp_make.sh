#!/bin/sh

export PYTHONPATH=./external_tools/gyp/pylib:$PYTHONPATH
python gen_proj.py --ignore-environment --format=make --generator-output=build/make -G output_dir=.