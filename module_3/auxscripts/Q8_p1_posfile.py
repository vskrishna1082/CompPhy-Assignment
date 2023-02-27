#! /usr/bin/env python3
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

data = pd.read_csv("data/Q8_particle_1_pos.dat", header=None)
t = np.linspace(0,40,len(data[1]))
plt.plot(t,data[0])
plt.plot(t,data[25])
plt.show()
