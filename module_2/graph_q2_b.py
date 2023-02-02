#! /usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

Rand_Nos = pd.read_csv("uniform_rand_0_1.dat")
x = np.arange(1,len(Rand_Nos)+1)

plt.title('Scatter Plot showing 2000 random samples')
plt.xlim(0,2000)
plt.ylim(0,1)
plt.scatter(x[:2000],Rand_Nos[:2000],s=1, marker='.')
plt.savefig('plots/random_scatter_q2_a.png',format='png')
plt.show()
