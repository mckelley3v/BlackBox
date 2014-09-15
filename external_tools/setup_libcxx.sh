#!/bin/sh

echo Checkout libc++abi...
svn co http://llvm.org/svn/llvm-project/libcxxabi/trunk libcxxabi 

echo Checkout libc++...
svn co http://llvm.org/svn/llvm-project/libcxx/trunk libcxx


export PATH=$PATH:/usr/local/bin

echo Build libc++abi...
cd libcxxabi
export LIBCXXABIDIR=$PWD
cd lib
./buildit
sudo cp libc++abi.so.1.0 /usr/lib/libc++abi.so.1.0
sudo link /usr/lib/libc++abi.so.1.0 /usr/lib/libc++abi.so.1
sudo link /usr/lib/libc++abi.so.1 /usr/lib/libc++abi.so
cd ../..

echo Build libc++...
cd libcxx
export LIBCXXDIR=$PWD
mkdir build
cd build
#CC=clang CXX=clang++ cmake -G "Unix Makefiles" -DLIBCXX_CXX_ABI=libsupc++ -DLIBCXX_LIBSUPCXX_INCLUDE_PATHS="/usr/include/c++/4.8/;/usr/include/c++/4.8/i586-suse-linux/" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr $LIBCXXDIR
echo CC=clang CXX=clang++ cmake -G "Unix Makefiles" -DLIBCXX_CXX_ABI=libcxxabi -DLIBCXX_LIBCXXABI_INCLUDE_PATHS=$LIBCXXABIDIR/include -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr $LIBCXXDIR
CC=clang CXX=clang++ cmake -G "Unix Makefiles" -DLIBCXX_CXX_ABI=libcxxabi -DLIBCXX_LIBCXXABI_INCLUDE_PATHS=$LIBCXXABIDIR/include -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr $LIBCXXDIR
sudo make install
cd ../..
