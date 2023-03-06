#! /usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data1 = pd.read_csv("data/Q1.dat", header=None);
data2 = pd.read_csv("data/Q2.dat", header=None);
data3 = pd.read_csv("data/Q3.dat", header=None);
data4 = pd.read_csv("data/Q4.dat", header=None);
x1 = data1[0]
x2 = data2[0]
x3 = data3[0]
x4 = data4[0]
t = np.linspace(0,50,len(x5))
plt.plot(t, tan(t), label="tan(x)")
plt.scatter(t,x1, label="Euler Method", marker='.')
plt.scatter(t,x2, label="Modified Euler Method", marker='.')
plt.scatter(t,x3, label="Improved Euler Method", marker='.')
plt.scatter(t,x4, label="Runge Kutta Method", marker='.')
plt.legend()
plt.xlabel("time (t)")
plt.ylabel("position (x)")
plt.savefig("figures/Q5-6-7.png")
