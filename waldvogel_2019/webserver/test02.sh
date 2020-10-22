#!/bin/bash

HOST=$1

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

FLAGS="-s -o /dev/null" #add -v to show some debug information

if [ -z "$1" ]; then
    echo "No host provided. This script has to been used like this: ./httpCompliantTest.sh localhost:8080"
    exit 1
fi

TESTSTR=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1)
TESTNAME=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1)
WEBROOT=/tmp/www

# Setup
rm -rf $WEBROOT
mkdir -p $WEBROOT/dir1
mkdir $WEBROOT/dir2
cp netzwerk.jpg $WEBROOT/
touch -d "11 Jan 2019 02:03:04 GMT" $WEBROOT/netzwerk.jpg
echo $TESTSTR > $WEBROOT/$TESTNAME
echo File 2 > $WEBROOT/dir2/file_2
echo "<!DOCTYPE html><html><h1>Welcome $TESTSTR</h1><p>Here is no content</p></html>" > $WEBROOT/dir1/index.html
echo "<!DOCTYPE html><html><h1>Network</h1><img alt='network image' src='netzwerk.jpg' /></html>" > $WEBROOT/network.html
echo forbidden > $WEBROOT/../forbidden

NUMBER_OF_FAILED_TESTS=0

t () {
  local RETURN=`tr -d "\r\n" <<< "$1"`
  local EXPECTED=$2
  local DESC=$3

  if [ "$RETURN" = "$EXPECTED" ]; then
    echo -e "\t${GREEN}✔ $DESC${NC}"
  else
    echo -e "\t${RED}✘ $DESC${NC}"
    NUMBER_OF_FAILED_TESTS=$(($NUMBER_OF_FAILED_TESTS+1))
  fi
}

echo Test directory traversal
t "$(curl $FLAGS -X GET -w "%{http_code}\n" $HOST/)" "200" "Server responds with status code 200 for root dir"
t "$(curl -s -X GET $HOST | grep -iq "$TESTNAME"; echo $?)" "0" "Directory listing is showing $TESTNAME"
t "$(curl -s -X GET $HOST | grep -iq "dir2"; echo $?)" "0" "Directory listing is showing dir2"
t "$(curl -s -X GET $HOST/dir1/ | grep -iq "Welcome $TESTSTR"; echo $?)" "0" "Server returns index.html instead of directory listing"
t "$(curl -s -X GET $HOST/dir2/ | grep -iq "file_2"; echo $?)" "0" "Directory listing for subdirectory is working"
t "$(curl $FLAGS -X GET -w "%{http_code}\n" $HOST/dir2/../)" "200" "Relative path are working"
t "$(curl --path-as-is $FLAGS -X GET -w "%{http_code}\n" $HOST/dir2/../../forbidden)" "404" "Server prevents file access outside of his webroot"

echo
echo Test file access
t "$(curl $FLAGS -X "GET" -w "%{http_code};%{size_download}\n" -o /dev/null $HOST/netzwerk.jpg)" "200;44667" "Server handles small files"
t "$(curl $FLAGS -X GET -w "%{http_code}\n" $HOST/foobar)" "404" "Server responds with status code 404 for an unknown path"

echo
echo Test headers
t "$(curl -s -I -X GET $HOST/network.html | grep -iq "Content-Type: text/html"; echo $?)" "0" "Server responds with correct content type for html file"
t "$(curl -s -I -X GET $HOST/netzwerk.jpg | grep -iq "Content-Type: image/jpeg"; echo $?)" "0" "Server responds with correct content type for jpeg file"
t "$(curl -s -I -X GET $HOST/$TESTNAME | grep -iq "Content-Type: application/octet-stream"; echo $?)" "0" "Server responds with correct content type for unknown file type"
t "$(curl -s -I -X GET $HOST/netzwerk.jpg | grep -iq "Last-Modified: Fri, 11 Jan 2019 02:03:04 GMT"; echo $?)" "0" "Server responds with correct last modified"
t "$(curl -s -I -X GET $HOST/netzwerk.jpg | grep -iq "Content-Length: 44667"; echo $?)" "0" "Server responds with correct content length"

echo
echo Test cache
t "$(curl $FLAGS -X GET -w "%{http_code}\n" $HOST/netzwerk.jpg)" "200" "Server responds with file if no If-Modified-Since header is present"
t "$(curl $FLAGS -X GET -w "%{http_code}\n" -H "If-Modified-Since: Thu, 10 Jan 2019 00:00:00 GMT" $HOST/netzwerk.jpg)" "200" "Server responds with file because there is a new version"
t "$(curl $FLAGS -X GET -w "%{http_code}\n" -H "If-Modified-Since: Fri, 11 Jan 2019 10:00:00 GMT" $HOST/netzwerk.jpg)" "304" "Server responds with not modified"

if [ $NUMBER_OF_FAILED_TESTS -gt 0 ]; then
  echo
  echo $NUMBER_OF_FAILED_TESTS tests are failing!
  exit 1
fi
