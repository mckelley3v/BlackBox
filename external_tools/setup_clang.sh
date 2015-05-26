#!/bin/sh

echo Checkout LLVM...
svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm

echo Checkout Clang...
cd llvm/tools
svn co http://llvm.org/svn/llvm-project/cfe/trunk clang
cd ../..

echo Checkout extra Clang Tools...
cd llvm/tools/clang/tools
svn co http://llvm.org/svn/llvm-project/clang-tools-extra/trunk extra
cd ../../../..

echo Checkout Compiler-RT...
cd llvm/projects
svn co http://llvm.org/svn/llvm-project/compiler-rt/trunk compiler-rt
cd ../..

echo Build LLVM and Clang...
cd llvm
mkdir build
cd build
cmake -G "Unix Makefiles" ../llvm
make
sudo make install
cd ../..
