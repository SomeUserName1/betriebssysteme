#!/bin/bash

HOST=$1
NCHOST=${HOST//:/ }

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

FLAGS="-s -o /dev/null" #add to show some debug information

if [ -z "$1" ]; then
    echo "No host provided. This script has to been used like this: ./httpCompliantTest.sh localhost:8080"
    exit 1
fi

NUMBER_OF_FAILED_TESTS=0

t () {
  local RETURN=$1
  local EXPECTED=$2
  local DESC=$3

  if [ "$RETURN" == "$EXPECTED" ]; then
    echo -e "\t${GREEN}✔ $DESC${NC}"
  else
    echo -e "\t${RED}✘ $DESC${NC}"
    echo "Got answer:"
    echo "$RETURN"
    echo "Expected answer was:"
    echo "$EXPECTED"
    NUMBER_OF_FAILED_TESTS=$(($NUMBER_OF_FAILED_TESTS+1))
  fi
}

tstarts () {
  local RETURN=$1
  local EXPECTED=$2
  local DESC=$3

  if [[ "$RETURN" == "$EXPECTED"* ]]; then
    echo -e "\t${GREEN}✔ $DESC${NC}"
  else
    echo -e "\t${RED}✘ $DESC${NC}"
    echo "Got answer:"
    echo "$RETURN"
    echo "Expected answer was:"
    echo "$EXPECTED"
    NUMBER_OF_FAILED_TESTS=$(($NUMBER_OF_FAILED_TESTS+1))
  fi
}

tnot () {
  local RETURN=$1
  local EXPECTED=$2
  local DESC=$3

  if [ "$RETURN" != "$EXPECTED" ]; then
    echo -e "\t${GREEN}✔ $DESC${NC}"
  else
    echo -e "\t${RED}✘ $DESC${NC}"
    echo "Got wrong answer:"
    echo "$RETURN"
    NUMBER_OF_FAILED_TESTS=$(($NUMBER_OF_FAILED_TESTS+1))
  fi
}

./server 80 &
testpid=$!

echo
echo Privileges
tnot "$(ps -q $testpid -o uid:1= )" "0" "Server drops privileges"

echo
echo Stability
threads=$(ps huH -p $testpid | wc -l)
tstarts "$(echo -e "GET / HTTP/1.1\r\nHost:localhost\r\n\r\n" | nc -q 8 -i 2 $NCHOST )" "HTTP/1.1 200" "Server can handle delays"
echo -e "GET / HTTP/1.1\r\nHost:localhost\r\n" | nc -q 8 $NCHOST &
echo -e "GET / HTTP/1.1Host:localhost" | nc -q 8 $NCHOST &
echo -e "GET / HTTP/1.1\r\n\r\nHost:localhost\r\n" | nc -q 8 $NCHOST &
echo -e "GET /// HTTP/1.1\r\nHost:localhost\r\n\r\n" | nc -q 8 $NCHOST &
echo -e "GET / HTTP/1.1\r\nHost:localhost\r\n\r\n" | nc -q 8 $NCHOST &
echo -e "GET / HTTP/1.1\r\nHost: \r\nlocalhost\r\n\r\n" | nc -q 8 $NCHOST &
echo -e "GET / HTTP/1.1\r\nHost:\r\nlocalhost\r\n\r\n" | nc -q 8 $NCHOST &
echo -e "GET / HTTP/1.1\r\nHo\r\nst:localhost\r\n\r\n" | nc -q 8 $NCHOST &
echo -e "GET / HTTP/1.1\rHost:localhost\r\n\r\n" | nc -q 8 $NCHOST &
echo -e "GET / HTTP/1.1\rHost:localhost\n\r" | nc -q 8 $NCHOST &
echo -e "GET / HTTP/1.1\r\nHost:localhost\n\r\n" | nc -q 8 $NCHOST &
echo -e "GET /\r HTTP/1.1\r\nHost:localhost\r\n\r\n" | nc -q 8 $NCHOST &
echo -e "GET /\r\n HTTP/1.1\r\nHost:localhost\r\n\r\n" | nc -q 8 $NCHOST &
echo -e "GET / HTTP/1.1\r\nHost:localhost\r\n\r\n" | nc -q 8 -i 20 $NCHOST &
sleep 25
t "$(ps huH -p $testpid | wc -l)" "$threads" "Server finishes all connections"

kill $testpid


if [ $NUMBER_OF_FAILED_TESTS -gt 0 ]; then
  echo
  echo $NUMBER_OF_FAILED_TESTS tests are failing!
  exit 1
fi

