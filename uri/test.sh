#!/bin/bash

PATH=$1
BIN_PATH=$PATH./.bin/exe 

INPUT_PATH=$PATH/data/input
RUN_OUT_PATH=$PATH./.bin/out
EXPECTED_OUT_PATH=$PATH/data/output

$BIN_PATH < $INPUT_PATH > $RUN_OUT_PATH 

RUN_OUT=$(/bin/cat $RUN_OUT_PATH)
EXPECTED_OUT=$(/bin/cat $EXPECTED_OUT_PATH)

if [[ "$RUN_OUT" != "$EXPECTED_OUT" ]]; then
  echo "$1 Busted..."
  if [[ $1 == '-v' ]]; then
    /bin/cat out
  else
    /bin/vimdiff "$RUN_OUT_PATH" "$EXPECTED_OUT_PATH"
  fi
  exit 1
else
  echo "OK!"
fi
