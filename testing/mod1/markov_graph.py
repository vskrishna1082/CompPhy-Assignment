#! /usr/bin/env python3
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import math

Xdata = np.arange(4,500,2);
Ydata = pd.read_csv("endpoint_probability.dat");
X2data = np.arange(4,1000,2);
Y2data = pd.read_csv("endpoint_probability_2.dat");
plt.scatter(Xdata,Ydata)
plt.scatter(X2data,Y2data)
plt.show()
