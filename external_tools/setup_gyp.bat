@ECHO OFF
SET PATH=%PATH%;%APPDATA%\..\Local\GitHub\PortableGit_c2ba306e536fdf878271f7fe636a147ff37326ad\bin

ECHO Checkout GYP...
git clone https://chromium.googlesource.com/external/gyp gyp
