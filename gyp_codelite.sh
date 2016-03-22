#!/bin/sh

this_dir=$(dirname "$0")
gyp_path=$this_dir/external_tools/gyp
export PYTHONPATH=$gyp_path/pylib:$PYTHONPATH

$gyp_path/gyp  --ignore-environment --format=$this_dir/codelite.py --generator-output=build/codelite -G product_dir=build/bin -G intermediate_dir=build/temp --include=$this_dir/codelite.gypi --include=$this_dir/include.gypi --depth=$PWD "$@"