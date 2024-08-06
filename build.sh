#!/bin/bash

gcc -o MALLOCFREE.o MAIN.c mallocfree.c

if [ $? -ne 0 ]; then
    echo "Build Error"
    exit 1
fi
./MALLOCFREE.o