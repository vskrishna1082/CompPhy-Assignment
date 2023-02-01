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
slope_trunc='%3f'%(slope)

print("Slope: ", slope)
plt.title('log-log plot between bins and errors')
plt.xlabel('Number of bins')
plt.ylabel('Error in estimation')
plt.xlim(0,7)
plt.ylim(-7,0)
plt.axline((0,intercept), slope=slope, lw=1, c='black', label=f'Fit Line: Slope={slope_trunc}')
plt.scatter(Xdata,Ydata,marker='.', s=20, c='red', label='log(Error)')
plt.legend()
plt.savefig('plots/log_log_q1_a.png',format='png') 
plt.show()
