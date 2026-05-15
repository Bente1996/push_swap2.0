#!/usr/bin/env bash

NUMBERS=$(shuf -i 1-100)
./push_swap $NUMBERS | tee operations | ./checker_linux $NUMBERS >outfile
cat outfile
wc -l operations
