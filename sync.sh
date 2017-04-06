#!/bin/bash
CMD="./build.sh"
FILE="."
LASTPID="-1"
LAST="---------"
while true; do
  sleep 1
  NEW=`find ./COSC363A1/ -type f -exec md5sum {} \; | sort -k 2 | md5sum`
  if [ "$NEW" != "$LAST" ]; then
    if [ $LASTPID != "-1" ]; then
        kill -KILL $LASTPID
    fi
    echo "building..."
    $CMD
    cd ./Bin
    ./project &
    LASTPID=$!
    cd ..
    LAST="$NEW"
  fi
done
