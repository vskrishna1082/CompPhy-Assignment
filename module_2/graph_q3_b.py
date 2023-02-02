#! /usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

X = pd.read_csv("gaussian_rv_1.dat")
Y = pd.read_csv("gaussian_rv_2.dat")
plt.scatter(X,Y,s=1, marker='.')
plt.show()
