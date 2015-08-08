@ECHO OFF

SET PATH=%PATH%;C:\Python27
SET PYTHONPATH=%PYTHONPATH%;%~dp0external_tools\gyp\pylib

python gen_proj.py --ignore-environment --format=msvs -G msvs_version=2015 --generator-output=build/msvs2015 --include=msvs.gypi