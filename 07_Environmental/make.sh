#!/bin/bash

aclocal
autoheader
autoreconf -fisv
automake --add-missing
./configure --disable-dependency-tracking --enable-readline
make
