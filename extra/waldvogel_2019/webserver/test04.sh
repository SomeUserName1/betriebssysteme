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
fallocate -l 1G $WEBROOT/large_file
cp netzwerk.jpg $WEBROOT/
touch -d "11 Jan 2019 02:03:04 GMT" $WEBROOT/netzwerk.jpg
echo $TESTSTR > $WEBROOT/$TESTNAME
echo File 2 > $WEBROOT/dir2/file_2
echo "<h1>Welcome $TESTSTR</h1><p>Here is no content</p>" > $WEBROOT/dir1/index.html
echo "<h1>Network</h1><img alt='network image' src='netzwerk.jpg' />" > $WEBROOT/network.html
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


echo
echo Test limits
t "$(curl $FLAGS -X "GET" -w "%{http_code};%{size_download}\n" -o /dev/null $HOST/netzwerk.jpg)" "200;44667" "Server handles small files"
t "$(curl $FLAGS -X "GET" -w "%{http_code};%{size_download}\n" -o /dev/null $HOST/large_file)" "200;1073741824" "Server handles large files"
key=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 1025 | head -n 1)
value=$(cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 1025 | head -n 1)
t "$(curl -sb -X GET -H "$key: $value" $HOST/header/$key)" "$value" "Server allows for arbitrary length header fields"
t "$(curl -s -X GET -H "00:00" -H "01:01" -H "02:02" -H "03:03" -H "04:04" -H "05:05" -H "06:06" -H "07:07" -H "08:08" -H "09:09" -H "10:10" -H "11:11" -H "12:12" -H "13:13" -H "14:14" -H "15:15" -H "16:16" -H "17:17" -H "18:18" -H "19:19" -H "20:20" -H "21:21" -H "22:22" -H "23:23" -H "24:24" -H "25:25" -H "26:26" -H "27:27" -H "28:28" -H "29:29" -H "30:30" -H "31:31" -H "32:32" -H "33:33" -H "34:34" -H "35:35" $HOST/keys | wc -l)" "39" "Server allows for unlimited header fields"


if [ $NUMBER_OF_FAILED_TESTS -gt 0 ]; then
  echo
  echo $NUMBER_OF_FAILED_TESTS tests are failing!
  exit 1
fi
