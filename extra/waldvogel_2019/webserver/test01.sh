#!/bin/bash

HOST=$1
NCHOST=${HOST//:/ }

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

FLAGS="-s -o /dev/null" #add -v to show some debug information

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

echo Test valid requests
t "$(curl $FLAGS -X GET -w "%{http_code}\n" $HOST)" "200" "Server respondss with status code 200 for /"
t "$(curl $FLAGS -X GET -w "%{http_code}\n" $HOST/index.html)" "200" "Server responds with status code 200 for /index.html"
t "$(curl $FLAGS -X GET -w "%{http_code}\n" $HOST/foobar)" "404" "Server responds with status code 404 for an unknown path"
redirecttest=$(curl $FLAGS -X GET -w "%{http_code};%{redirect_url}" $HOST/index.php)
t "$redirecttest" "301;http://$HOST/index.html" "Server redirects requests from /index.php to /index.html"

echo
echo Test invalid requests
t "$(curl $FLAGS -X "GET ME" -w "%{http_code}\n" $HOST)" "400" "Server rejects request with invalid method"
t "$(curl $FLAGS -X "GETME" -w "%{http_code}\n" $HOST)" "501" "Server handles unknown method"
t "$(curl $FLAGS -X GET -w "%{http_code}\n" -H "host:" $HOST)" "400" "Server rejects requests without host header"

echo
echo Test headers
t "$(curl -s -I -X GET $HOST | grep -iq "date:"; echo $?)" "0" "Server responds with date header"
t "$(curl -s -I -X GET $HOST | grep -iq "server:"; echo $?)" "0" "Server responds with server header"

echo
echo Test header field parsing
tstarts "$(printf "GET / HTTP/1.1\r\nHost: localhost\r\nBADHEADER\r\n\r\n" | nc $NCHOST)" "HTTP/1.1 400" "Server rejects request with invalid header"
key=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1)
value=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1)
t "$(curl -sb -X GET -H "$key: $value" $HOST/header/$key)" "$value" "Server outputs requested header field"
t "$(curl $FLAGS -X GET -w "%{http_code}\n" -H "$key: $value" $HOST/header/$value)" "404" "Server responds with Not Found if header key is not present"
t "$(curl -s -X GET -H "$key: $value" $HOST/keys | grep "$key")" "$key" "Server responds with header keys"
t "$(curl -s -X GET -H "$key: $value" $HOST/values | grep "$value")" "$value" "Server responds with header values"

if [ $NUMBER_OF_FAILED_TESTS -gt 0 ]; then
  echo
  echo $NUMBER_OF_FAILED_TESTS tests are failing!
  exit 1
fi
