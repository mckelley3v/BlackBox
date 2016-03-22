@ECHO OFF

SET THIS_DIR=%~dp0
SET GYPPATH=%THIS_DIR%external_tools\gyp
SET PYTHONPATH=%GYPPATH%\pylib;%PYTHONPATH%

CALL %GYPPATH%\gyp.bat --ignore-environment --format=msvs -G msvs_version=2013 --generator-output=build/msvs2013 --include=%THIS_DIR%msvs.gypi --include=%THIS_DIR%include.gypi --depth=%CD% %*