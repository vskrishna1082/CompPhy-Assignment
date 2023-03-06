#! /usr/bin/env python3
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

data = pd.read_csv("data/Q8_particle_1_pos.dat", header=None)
t = np.linspace(0,40,len(data[1]))
plt.plot(t,data[0],label="Particle 1")
plt.plot(t,data[1],label="Particle 26")
plt.xlabel("time (t)")
plt.ylabel("Position (y)")
plt.title("Time Evolution of particle position")
plt.legend()
plt.savefig("figures/Q8_p1_26_y_vs_t.png")
