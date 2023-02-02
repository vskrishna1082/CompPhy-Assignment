#! /usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import expon

data1 = np.loadtxt('gaussian_rv_1.dat', unpack=True)
mu1, std1 = norm.fit(data1)
mean, var, skew, kurt = expon.stats(moments='mvsk')
print("Standard Deviation =",std2)
