#! /usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("data/Q3_M_T-4.9_init_1.dat")
x = np.linspace(0,len(data), len(data)).astype(int)

plt.plot(x, data)
plt.xlabel("Iterations")
plt.ylabel("Magnetization per spin")
ax = plt.gca()
ax.set_ylim([-1, 1])
plt.show()
