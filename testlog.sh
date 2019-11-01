#!/bin/bash

TESTFILE=test.out

pushd bin > /dev/null

echo "Running test: output to doc/current.txt"
./$TESTFILE > ../doc/current.txt

if [ ! -z "$(which valgrind)" ]; then
echo "Running valgrind: output to doc/valgrind.txt"
valgrind --log-fd=1 --leak-check=full ./$TESTFILE > ../doc/valgrind.txt
else
echo "Command not found: valgrind"
fi

popd > /dev/null

echo "Done."

