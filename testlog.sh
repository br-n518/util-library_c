#!/bin/bash

pushd bin

./test.out > ../doc/current.txt

if [ ! -z "$(which valgrind)" ]; then
valgrind --log-fd=1 ./test.out > ../doc/valgrind.txt
fi

popd

