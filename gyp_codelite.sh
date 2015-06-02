#!/bin/sh

export PYTHONPATH=./external_tools/gyp/pylib:$PYTHONPATH
python gen_proj.py --ignore-environment --format=codelite.py --generator-output=build/codelite -G product_dir=build/bin -G intermediate_dir=build/temp