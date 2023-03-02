#! /usr/bin/env python3
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn

data = pd.read_table("data/Q2_temps_best.dat", delimiter=" ", header=None, skipinitialspace=True)
data = data[::-1]
seaborn.heatmap(data, cmap="coolwarm")
plt.xlabel("x")
plt.ylabel("y")
plt.title("Temperature (K) on a 34x34 lattice\nNewmann Boundary Conditions")
plt.savefig("figures/Q2-heatmap.png")
