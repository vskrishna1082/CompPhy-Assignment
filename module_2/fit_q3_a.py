#! /usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import expon

data1 = np.loadtxt('exp_rand_nos.dat', unpack=True)
mean, var, skew, kurt = expon.stats(moments='mvsk')
x = np.arange(0,len(data1))
plt.plot(x,data1)
plt.show()
