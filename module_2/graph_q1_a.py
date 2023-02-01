#! /usr/bin/env python3
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import linregress

Xdata = pd.read_csv("q1_a_x.dat")
Ydata = pd.read_csv("q1_a_y.dat")
Xdata = np.transpose(Xdata)
Ydata = np.transpose(Ydata)
slope,intercept,r_value,p_value,std_err = linregress(Xdata,Ydata)

print("Slope: ", slope)
plt.scatter(Xdata,Ydata, marker='.', s=2)
plt.show()
