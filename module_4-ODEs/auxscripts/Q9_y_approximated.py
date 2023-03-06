#! /usr/bin/env python3
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# data = pd.read_csv("data/Q9_y_best.dat", header=None)
y = np.loadtxt("data/Q9_y_best.dat", delimiter="\n", dtype=float)
x = np.linspace(0,1,len(y))
data = {"x":x, "y":y}
data = pd.DataFrame(data)
print(data)
df2 = data.query('x == 0.80')['y']
print(df2)
plt.plot(x,2*x)
plt.scatter(x,y, marker='.', s=2, c='red')
plt.savefig("figures/Q9.png")
