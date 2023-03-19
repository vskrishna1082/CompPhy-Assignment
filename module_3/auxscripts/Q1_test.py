#! /usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

data1 = np.loadtxt("data/Q1_rand_E.dat")
data2 = np.loadtxt("data/Q1_rand_E2.dat")
x = np.linspace(0,1000000, 1000000).astype(int)
data1 = data1.transpose()
data1 = np.sort(data1)
data2 = np.sort(data2)
print(data1)
print(x)

plt.scatter(data1,x)
plt.show()
plt.scatter(data2,x)
plt.show()
