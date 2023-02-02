#! /usr/bin/env python3

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data=pd.read_csv('q_2_c_auto_correlation.dat', header=None)
x = np.arange(0,len(data))
plt.title('Auto-Correlation Function')
plt.xlabel('Lag')
plt.ylabel('Correlation')
plt.plot(x,data)
plt.savefig('plots/q2_c_auto_correlation.png')
plt.show()
