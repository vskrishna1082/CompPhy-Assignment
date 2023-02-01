#! /usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

Rand_Nos = pd.read_csv("uniform_rand_0_1.dat")
x = np.arange(1,len(Rand_Nos)+1)


plt.plot(x,Rand_Nos, 'bo', ms=1)
plt.show()
