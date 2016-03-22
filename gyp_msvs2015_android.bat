@ECHO OFF

SET THIS_DIR=%~dp0
SET GYPPATH=%THIS_DIR%external_tools\gyp
SET PYTHONPATH=%GYPPATH%\pylib;%PYTHONPATH%

CALL %GYPPATH%\gyp.bat --ignore-environment --format=%THIS_DIR%msvs_android.py -G msvs_version=2015 --generator-output=build/msvs2015_android --include=%THIS_DIR%msvs_android.gypi --include=%THIS_DIR%include.gypi --depth=%CD% %*