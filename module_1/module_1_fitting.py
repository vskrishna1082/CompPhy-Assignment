#! /usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm

data = np.loadtxt('random_numbers_sums.dat', unpack=True)
mu, std = norm.fit(data)
fig,axs = plt.subplots(ncols=2,nrows=2, layout="constrained")
axs[0,0].hist(data, bins=int((data[-1]-data[0])/2), density=True, alpha=0.6, color='xkcd:violet')
xmin, xmax = axs[0,0].get_xlim()
x = np.linspace(xmin, xmax, 100)
p = norm.pdf(x, mu, std)
axs[0,0].plot(x, p, 'k', linewidth=2)
title = "Sum of random nos:SD= %.2f" % (std)
axs[0,0].title.set_text(title)

data = np.loadtxt('random_walk_sums_10E5x10E5.dat', unpack=True)
mu, std = norm.fit(data)
axs[1,1].hist(data, bins=int((data[-1]-data[0])/4), density=True, alpha=0.6, color='xkcd:violet')
xmin, xmax = axs[1,1].get_xlim()
x = np.linspace(xmin, xmax, 100)
p = norm.pdf(x, mu, std)
axs[1,1].plot(x, p, 'k', linewidth=2)
title = "10k x 10k samples:SD= %.2f" % (std)
axs[1,1].title.set_text(title)

data = np.loadtxt('random_walk_sums.dat', unpack=True)
mu, std = norm.fit(data)
axs[0,1].hist(data, bins=int((data[-1]-data[0])/4), density=True, alpha=0.6, color='xkcd:violet')
xmin, xmax = axs[0,1].get_xlim()
x = np.linspace(xmin, xmax, 100)
p = norm.pdf(x, mu, std)
axs[0,1].plot(x, p, 'k', linewidth=2)
axs[0,1].set_xlim(axs[1,1].get_xlim())
title = "1k x 1k samples:SD= %.2f" % (std)
axs[0,1].title.set_text(title)

data = np.loadtxt('random_walk_sums_10E5x10E4.dat', unpack=True)
mu, std = norm.fit(data)
axs[1,0].hist(data, bins=int((data[-1]-data[0])/2), density=True, alpha=0.6, color='xkcd:violet')
xmin, xmax = axs[1,0].get_xlim()
x = np.linspace(xmin, xmax, 100)
p = norm.pdf(x, mu, std)
axs[1,0].plot(x, p, 'k', linewidth=2)
axs[1,0].set_xlim(axs[1,1].get_xlim())
title = "1k x 10k samples:SD= %.2f" % (std)
axs[1,0].title.set_text(title)

axs[1,1].set_ylim(axs[0,1].get_ylim())

axs[0,0].set_xlabel("Sum")
axs[0,0].set_ylabel("Probability Density")
axs[1,0].set_xlabel("Sum")
axs[1,0].set_ylabel("Probability Density")
axs[0,1].set_xlabel("Sum")
axs[0,1].set_ylabel("Probability Density")
axs[1,1].set_xlabel("Sum")
axs[1,1].set_ylabel("Probability Density")
plt.show()