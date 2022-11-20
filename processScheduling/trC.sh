#! /bin/bash
cd linux-5.19.9.3
cp ../config .config
make
make modules
make modules_install
make bzImage
