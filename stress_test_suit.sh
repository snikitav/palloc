#!/bin/bash

mkdir -p build
cd build

for I in `seq 1 256`
do
    for J in `seq 1 256`
    do
        echo "BLOCK_SIZE=$I POOL_SIZE=$J"
       (cmake .. -DBLOCK_SIZE=$I -DPOOL_SIZE=$J -DCMAKE_BUILD_TYPE=Debug && make) &>/dev/null
       ./out/test/palloc_test
       echo ""
    done;
done;
