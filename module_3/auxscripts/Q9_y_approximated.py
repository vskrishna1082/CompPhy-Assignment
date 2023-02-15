#! /usr/bin/env python3
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

data = pd.read_csv("data/Q9_y_best.dat", header=None)
x = np.linspace(0,1,len(data))
plt.plot(x,2*x)
plt.plot(x,data)
plt.show()
