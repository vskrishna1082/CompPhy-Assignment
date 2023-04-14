#! /usr/bin/env python3

import numpy as np
import matplotlib.pyplot as plt
plt.rcParams.update({'font.size': 12})

KE = np.loadtxt('data/Q2_KE.dat')
PE = np.loadtxt('data/Q2_PE.dat')
MV = np.loadtxt('data/Q2_Momentum.dat')
iter = range(len(KE))

plt.plot(iter, KE, label='Kinetic Energy')
plt.plot(iter, PE, label='Potential Energy')
plt.plot(iter, KE + PE, label='Total Energy')
plt.legend();
plt.xlabel('Iterations')
plt.ylabel('Energy per particle (sim units)')
plt.tight_layout()
plt.show()
# plt.savefig('figures/Q2_Energy.png')
# plt.clf()
plt.plot(iter, MV[:,0], label='$p_x$')
plt.plot(iter, MV[:,1], label='$p_y$')
plt.plot(iter, MV[:,2], label='$p_z$')
plt.legend();
plt.xlabel('Iterations')
plt.ylabel('Momentum per particle')
plt.ylim(-1,1)
plt.tight_layout()
# plt.savefig('figures/Q2_Momentum.png')
plt.show()
