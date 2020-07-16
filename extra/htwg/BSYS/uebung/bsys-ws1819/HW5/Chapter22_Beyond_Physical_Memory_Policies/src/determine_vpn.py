#!/usr/bin/python

import sys;
import binascii;

file = open("transformed_valgrind_out.txt", "r");

hex_data = file.read().splitlines();
MAX_LEN = 21287;
for i in range(0, MAX_LEN):
    bin_data = str(bin(int(hex_data[i], 16))[2:]);
    vpn_as_dez = int(bin_data[:-12], 2);

    if i < MAX_LEN - 1:
        sys.stdout.write(str(vpn_as_dez) + ',');
    else:
        sys.stdout.write(str(vpn_as_dez));

sys.stdout.write('\n');
