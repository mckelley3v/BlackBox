#!/bin/sh

python gen_proj.py --ignore-environment --format=msvs -G msvs_version=2013 --generator-output=build/msvs2013 -G output_dir=.