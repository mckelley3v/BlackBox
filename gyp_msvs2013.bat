@ECHO OFF

SET PATH=%PATH%;C:\Python27

python gen_proj.py --ignore-environment --format=msvs -G msvs_version=2013 --generator-output=build/msvs2013