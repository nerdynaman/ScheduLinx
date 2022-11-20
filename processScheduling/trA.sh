#! /bin/bash
cd linux-5.19.9.1
cp ../config .config
make
make modules
make modules_install
make bzImage
