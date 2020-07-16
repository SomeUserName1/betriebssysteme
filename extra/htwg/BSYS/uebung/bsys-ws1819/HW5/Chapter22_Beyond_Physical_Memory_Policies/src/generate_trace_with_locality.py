#!/usr/bin/python

import sys;
import math;
from random import seed;
from random import randint;
from random import random;

def standard_normal_distribution(x):
    return 1 / math.sqrt(2 * math.pi) * math.exp(-1 / 2 * math.pow(x, 2));

def standard_normal_distribution_2(x, u, o):
    return 1 / math.sqrt(2 * math.pi * o) * math.exp(-math.pow(x - u, 2) / (2 * o))

if len(sys.argv) < 3:
    print("Usage: ./generate_trace_with_locality <lenOfTrace> <randSeed>");
    exit();

elif len(sys.argv) > 3:
    print("Usage: ./generate_trace_with_locality <lenOfTrace> <randSeed>");
    exit();

lenOfTrace = int(sys.argv[1]);
randSeed = int(sys.argv[2]);

seed(randSeed);

for i in range(0, lenOfTrace):
    x = random();
    y = randint(10, 25);
    
    if i < lenOfTrace - 1:
        sys.stdout.write(str(int(round(standard_normal_distribution(x) * y))) + ',');
    else:
        sys.stdout.write(str(int(round(standard_normal_distribution(x) * y))));

sys.stdout.write('\n');
