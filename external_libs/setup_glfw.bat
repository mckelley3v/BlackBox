@ECHO OFF
SET PATH=%PATH%;%APPDATA%\..\Local\GitHub\PortableGit_c2ba306e536fdf878271f7fe636a147ff37326ad\bin

ECHO Checkout GLFW 3.1...
git clone --branch 3.1 https://github.com/glfw/glfw.git glfw
