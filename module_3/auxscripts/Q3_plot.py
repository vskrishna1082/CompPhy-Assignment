#! /usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("data/Q3_M_T-4.9_init_1.dat")
data2 = np.loadtxt("data/Q3_M_T-4.9_init_rand.dat")
x = np.linspace(0,len(data), len(data)).astype(int)

plt.plot(x, data, label="Init: 1")
plt.plot(x, data2, label="Init: random")
plt.xlabel("Iterations")
plt.ylabel("Magnetization per spin")
plt.title("Magnetization per Spin : k$_B$T = 4.9")
ax = plt.gca()
ax.set_ylim([-1, 1])
plt.legend()
plt.savefig("figures/Q3_Magnetization.png")
