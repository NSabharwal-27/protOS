#!/bin/bash

set -e

export PREFIX="$HOME/opt/cross"
export TARGET=aarch64-none-elf
export PATH="$PREFIX/bin:$PATH"

echo $PREFIX $TARGET $PATH

MAKEFLAGS=-j4

mkdir -p "$PREFIX"
mkdir -p src build/binutils build/gcc build/gdb
cd src

wget https://ftp.gnu.org/gnu/binutils/binutils-2.47.tar.gz
wget https://ftp.gnu.org/gnu/gcc/gcc-15.2.0/gcc-15.2.0.tar.gz
wget https://ftp.gnu.org/gnu/gdb/gdb-18.1.tar.gz

tar -xf binutils-2.47.tar.gz
tar -xf gcc-15.2.0.tar.gz
tar -xf gdb-18.1.tar.gz

cd ../build/binutils
../../src/binutils-2.47/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror --enable-default-execstack=no

make
make install

cd ../gcc
../../src/gcc-15.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --disable-hosted-libstdcxx --with-gmp="/opt/homebrew/Cellar/gmp/6.3.0" --with-mpfr="/opt/homebrew/Cellar/mpfr/4.2.2" --with-mpc="/opt/homebrew/Cellar/libmpc/1.4.1"

make all-gcc
make all-target-libgcc
make all-target-libstdc++-v3
make install-gcc
make install-target-libgcc
make install-target-libstdc++-v3

pwd
cd ../gdb
../../src/gdb-18.1/configure --target=$TARGET --prefix="$PREFIX" --with-mpfr="/opt/homebrew/Cellar/mpfr/4.2.2" --with-gmp="/opt/homebrew/Cellar/gmp/6.3.0" --disable-werror

make all-gdb
make install-gdb
