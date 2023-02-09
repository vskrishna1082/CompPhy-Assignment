#! /usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm

data1 = np.loadtxt('Importanc_Sampling_MC.dat', unpack=True)
mu1, std1 = norm.fit(data1)
print("Integral =", mu1)
print("Standard Deviation =",std1)
