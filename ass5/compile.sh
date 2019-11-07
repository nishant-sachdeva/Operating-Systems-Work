#! /bin/bash

cp -r my_repo/* final_repo

cd final_repo 

make

make qemu-nox
