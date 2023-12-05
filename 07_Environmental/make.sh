#!/bin/bash

aclocal
autoheader
autoconf
automake
./configure
make

make check
