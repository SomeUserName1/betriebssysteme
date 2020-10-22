#!/usr/bin/python

import matplotlib.pyplot as plt
import numpy as np

x, y, z = np.loadtxt("data.txt", usecols=(0, 1, 2), unpack=True)

# create an index for each tick position
xi = [i for i in range(0, len(x))]

plt.title('Memory access bandwidth')
plt.xlabel('Memory in kB')
plt.ylabel('bandwidth (MB/s)')

plt.xticks(xi, x.astype(int))

plt.plot(xi, y, marker='o', color='b', label="first loop")
plt.plot(xi, z, marker='o', color='r', label="remaining loops")
plt.legend()

plt.savefig('mem-plot.png')
print("saved plot in file: mem-plot.png")
