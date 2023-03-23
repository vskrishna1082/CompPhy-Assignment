#! /usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

data7 = np.loadtxt("data/Q7-8-9-Mag_Avg_l_7.dat")
data8 = np.loadtxt("data/Q7-8-9-Mag_Avg_l_8.dat")
data9 = np.loadtxt("data/Q7-8-9-Mag_Avg_l_9.dat")

Exp7_M2 = data7[:,1]
Exp7_M4 = data7[:,2]
Exp8_M2 = data8[:,1]
Exp8_M4 = data8[:,2]
Exp9_M2 = data9[:,1]
Exp9_M4 = data9[:,2]
T = np.linspace(3.8,4.7,np.size(Exp7_M2))

U7 = Exp7_M4/(3*Exp7_M2)
U8 = Exp8_M4/(3*Exp8_M2)
U9 = Exp9_M4/(3*Exp9_M2)

plt.plot(T, U7, '--o', label="7")
plt.plot(T, U8, '--o', label="8")
plt.plot(T, U9, '--o', label="9")
plt.legend()
plt.show()
