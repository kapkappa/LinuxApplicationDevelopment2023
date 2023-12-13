#!/bin/bash

touch NEWS README AUTHORS ChangeLog
autoreconf -fisv
./configure
make
