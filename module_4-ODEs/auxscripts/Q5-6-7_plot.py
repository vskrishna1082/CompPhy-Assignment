#! /usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data5 = pd.read_csv("data/Q5.dat", header=None);
data6 = pd.read_csv("data/Q6.dat", header=None);
data7 = pd.read_csv("data/Q7.dat", header=None);
x5 = data5[0]
v5 = data5[1]
x6 = data6[0]
v6 = data6[1]
x7 = data7[0]
v7 = data7[1]
t = np.linspace(0,50,len(x5))
xth = 0.1*np.sin(t)
plt.plot(t,x5, label="Estimated Position ($v_0=1.9$)")
plt.plot(t,x6, label="Estimated Position ($v_0=1.99$)")
plt.plot(t,x7, label="Estimated Position ($v_0=2.001$)")
plt.legend()
plt.xlabel("time (t)")
plt.ylabel("position (x)")
plt.savefig("figures/Q5-6-7.png")
