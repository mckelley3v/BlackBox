@ECHO OFF

CALL ../../%~nx0 experiment.gyp

IF ERRORLEVEL 1 (
	PAUSE
)