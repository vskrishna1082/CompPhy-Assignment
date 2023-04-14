#! /usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
plt.rcParams.update({'font.size': 12})

KE = np.loadtxt('data/Q3_KE.dat')
PE = np.loadtxt('data/Q3_PE.dat')
KE2 = np.loadtxt('data/Q2_KE.dat')
PE2 = np.loadtxt('data/Q2_PE.dat')
iter = range(len(KE))
n = 2197
plt.plot(iter, KE, label='Kinetic Energy (with Thermostat)')
plt.plot(iter, PE, label='Potential Energy (with Thermostat)')
plt.plot(iter, KE2, label='Kinetic Energy')
plt.plot(iter, PE2, label='Potential Energy')
plt.plot(iter, KE + PE, label='Total Energy (with Thermostat)')
plt.plot(iter, KE2 + PE2, label='Total Energy')
plt.legend();
plt.xlabel('Iterations')
plt.ylabel('Energy (sim units)')
plt.tight_layout()
plt.show()
# plt.savefig('figures/Q3_Energy.png')
