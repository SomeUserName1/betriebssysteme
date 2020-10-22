#!/usr/bin/python

import sys;
from random import seed;
from random import randrange;
from random import randint;

if len(sys.argv) < 4:
    print("Usage: ./generate_random_trace <lenOfRandTrace> <maxPageNum> <randSeed>");
    exit();

elif len(sys.argv) > 4:
    print("Usage: ./generate_random_trace <lenOfRandTrace> <maxPageNum> <randSeed>");
    exit();

lenOfRandTrace = int(sys.argv[1]);
maxPageNum = int(sys.argv[2]);
randSeed = int(sys.argv[3]);

seed(randSeed);

for i in range(0, lenOfRandTrace):
    if i < lenOfRandTrace - 1:
        sys.stdout.write(str(randint(0, maxPageNum + 1)) + ',');
    else:
        sys.stdout.write(str(randint(0, maxPageNum + 1)));

sys.stdout.write('\n');
