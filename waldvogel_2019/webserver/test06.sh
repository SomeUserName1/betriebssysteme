#!/bin/bash

export LC_NUMERIC="en_US.UTF-8"

HOST=$1

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

FLAGS="-s -o /dev/null" #add -v to show some debug information

if [ -z "$1" ]; then
    echo "No host provided. This script has to been used like this: ./httpCompliantTest.sh localhost:8080"
    exit 1
fi

WEBROOT=/tmp/www

# Setup
rm -rf $WEBROOT
mkdir -p $WEBROOT/
for i in {0..19}; do
  echo File $i > $WEBROOT/file-$i.html
done

NUMBER_OF_FAILED_TESTS=0

t () {
  local RETURN=`tr -d "\r\n" <<< "$1"`
  local EXPECTED=$2
  local DESC=$3
  local CMP=${4-eq}

  if [ "$CMP" = "eq" ] && [ "$RETURN" = "$EXPECTED" ]; then
    echo -e "\t${GREEN}✔ $DESC${NC}"
  elif [ "$CMP" = "lt" ] && [ $(bc <<< "$RETURN < $EXPECTED") = 1 ]; then
    echo -e "\t${GREEN}✔ $DESC${NC}"
  elif [ "$CMP" = "gt" ] && [ $(bc <<< "$RETURN > $EXPECTED") = 1 ]; then
    echo -e "\t${GREEN}✔ $DESC${NC}"
  else
    echo -e "\t${RED}✘ $DESC${NC}"
    echo -e "\t\tExpected value ($CMP): $EXPECTED\n\t\tActual value: $RETURN"
    NUMBER_OF_FAILED_TESTS=$(($NUMBER_OF_FAILED_TESTS+1))
  fi
}

echo Please be patient. These tests can take some time.
echo

echo Test cache
DELAY=1
SLEEP_TIME=$(curl $FLAGS -X GET $HOST/file-0.html -w "%{time_total}")
MAX_WAIT=$(bc <<< "$SLEEP_TIME + $DELAY")
t "$MAX_WAIT" "3" "Request to uncached file is delayed by more than 3 seconds (REQUIREMENT, doesn't award any points)" "gt"
t "$(curl $FLAGS -X GET $HOST/file-0.html -w "%{time_total}")" "3" "File was cached" "lt"

NUMBER_OF_CACHED_FILES=0
echo -e "\tMake 10 request, so that those files get cached\c"
for i in {1..10}; do
  WAIT_UNCACHED=$(curl $FLAGS -X GET $HOST/file-$i.html -w "%{time_total}")
  echo -e ".\c"
  if [ $(bc <<< "$WAIT_UNCACHED > 3") = 1 ]; then
    NUMBER_OF_CACHED_FILES=$(($NUMBER_OF_CACHED_FILES+1))
  fi
done
echo

for i in {1..10}; do
  WAIT_CACHED=$(curl $FLAGS -X GET $HOST/file-$i.html -w "%{time_total}")
  if [ $(bc <<< "$WAIT_CACHED < 3") = 1 ]; then
    NUMBER_OF_CACHED_FILES=$(($NUMBER_OF_CACHED_FILES-1))
  fi
done
t "$NUMBER_OF_CACHED_FILES" "0" "10 files were cached"

curl $FLAGS -X GET $HOST/file-1.html
curl $FLAGS -X GET $HOST/file-2.html
curl $FLAGS -X GET $HOST/file-11.html
t "$(curl $FLAGS -X GET $HOST/file-3.html -w "%{time_total}")" "3" "The LRU cache entry in the queue was deleted" "gt"

echo
echo Test threads
curl $FLAGS -X GET $HOST/file-19.html -w "%{time_total}\n" > total.log &
sleep $DELAY # We need to sleep, so that the above fork is scheduled
t "$(curl $FLAGS -X GET $HOST/file-18.html -w "%{time_total}\n")" "$MAX_WAIT" "Handle two requests simultanously" "lt"

curl $FLAGS -X GET $HOST/file-17.html -w "%{time_total}\n" > /dev/null &
curl $FLAGS -X GET $HOST/file-16.html -w "%{time_total}\n" > /dev/null &
curl $FLAGS -X GET $HOST/file-15.html -w "%{time_total}\n" > /dev/null &
sleep $DELAY
t "$(curl $FLAGS -X GET $HOST/file-14.html -w "%{time_total}\n")" "$MAX_WAIT" "Handle four requests simultanously" "lt"


echo
echo Test thread limits
./server -tl 3 8085 &
testpid=$!
curl $FLAGS -X GET localhost:8085/file-1.html &
curl $FLAGS -X GET localhost:8085/file-2.html &
curl $FLAGS -X GET localhost:8085/file-3.html &
curl $FLAGS -X GET localhost:8085/file-4.html &
curl $FLAGS -X GET localhost:8085/file-5.html &
t "$(ps huH -p $testpid | wc -l)" "4" "Server limits number of threads"
kill $testpid

echo
echo Test threadpool
./server -tp 200 8090 &
testpid=$!
t "$(ps huH -p $testpid | wc -l)" "201" "Server creates 200 threads at startup"
curl $FLAGS -X GET localhost:8090/file-1.html -w "%{time_total}\n" > /dev/null &
t "$(ps huH -p $testpid | wc -l)" "201" "Server doesn't create additional threads"
kill $testpid

if [ $NUMBER_OF_FAILED_TESTS -gt 0 ]; then
  echo
  echo $NUMBER_OF_FAILED_TESTS tests are failing!
  exit 1
fi
