import matplotlib.pyplot as plt
import numpy as np

x, y = np.loadtxt("tlb_cost_data.txt", usecols=(0, 1), unpack=True)

# create an index for each tick position
xi = [i for i in range(0, len(x))]

plt.title('TLB Size Measurement')
plt.xlabel('Number Of Pages')
plt.ylabel('Time Per Access (ns)')

plt.xticks(xi, x.astype(int))

plt.plot(xi, y, marker='o', color='b')

plt.savefig('tlb_size_measurement.png')
print("saved plot in file: tlb_size_measurement.png")
