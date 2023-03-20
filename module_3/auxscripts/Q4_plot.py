#! /usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt("data/Q4_E_T-3.9_init_1.dat")
data2 = np.loadtxt("data/Q4_E_T-3.9_init_rand.dat")
x = np.linspace(0,len(data), len(data)).astype(int)

plt.plot(x, data, label="Init: 1")
plt.plot(x, data2, label="Init: random")
plt.xlabel("Iterations")
plt.ylabel("Energy per spin")
plt.title("Energy per Spin : k$_B$T = 3.9")
ax = plt.gca()
ax.set_ylim([-3, 0])
plt.legend()
plt.savefig("figures/Q4_Energy.png")
