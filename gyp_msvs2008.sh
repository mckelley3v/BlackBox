#!/bin/sh

export PYTHONPATH=./external_tools/gyp/pylib:$PYTHONPATH
python gen_proj.py --ignore-environment --format=msvs -G msvs_version=2008 --generator-output=build/msvs2008 -G output_dir=.