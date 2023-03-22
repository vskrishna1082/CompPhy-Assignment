#! /usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

data1 = np.loadtxt("data/Q5_E_T-4.05_init_1.dat")
data2 = np.loadtxt("data/Q5_E_T-4.05_init_rand.dat")
data3 = np.loadtxt("data/Q5_M_T-4.05_init_1.dat")
data4 = np.loadtxt("data/Q5_M_T-4.05_init_rand.dat")
data5 = np.loadtxt("data/Q5_E_T-4.05_init_m1.dat")
data6 = np.loadtxt("data/Q5_M_T-4.05_init_m1.dat")
x = np.linspace(0,len(data1), len(data1)).astype(int)

plt.plot(x, data1, label="Init: +1")
plt.plot(x, data5, label="Init: -1")
plt.plot(x, data2, label="Init: random")
plt.xlabel("Iterations")
plt.ylabel("Energy per spin")
plt.title("Energy per Spin : k$_B$T = 4.05")
ax = plt.gca()
ax.set_ylim([-3, 0])
plt.legend()
plt.savefig("figures/Q5_Energy.png")

plt.clf()

plt.plot(x, data3, label="Init: +1")
plt.plot(x, data6, label="Init: -1")
plt.plot(x, data4, label="Init: random")
plt.xlabel("Iterations")
plt.ylabel("Magnetization per spin")
plt.title("Magnetization per Spin : k$_B$T = 4.05")
ax = plt.gca()
ax.set_ylim([-1, 1])
plt.legend()
plt.savefig("figures/Q5_Magnetization.png")
