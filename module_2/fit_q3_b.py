#! /usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm

data1 = np.loadtxt('gaussian_rv_1.dat', unpack=True)
data2 = np.loadtxt('gaussian_rv_1.dat', unpack=True)
mu1, std1 = norm.fit(data1)
mu2, std2 = norm.fit(data2)
print("Standard Deviation =",std1)
print("Standard Deviation =",std2)
