#! /usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

data7_E = np.loadtxt("data/Q7-8-9-Energy_Avg_l_7.dat")
data7_M = np.loadtxt("data/Q7-8-9-Mag_Avg_l_7.dat")
data7_modM = np.loadtxt("data/Q7-8-9-Mag_Mod_Avg_l_7.dat")
data8_E = np.loadtxt("data/Q7-8-9-Energy_Avg_l_8.dat")
data8_M = np.loadtxt("data/Q7-8-9-Mag_Avg_l_8.dat")
data8_modM = np.loadtxt("data/Q7-8-9-Mag_Mod_Avg_l_8.dat")
data9_E = np.loadtxt("data/Q7-8-9-Energy_Avg_l_9.dat")
data9_M = np.loadtxt("data/Q7-8-9-Mag_Avg_l_9.dat")
data9_modM = np.loadtxt("data/Q7-8-9-Mag_Mod_Avg_l_9.dat")

Exp7_E = data7_E[:,0]
Exp7_E2 = data7_E[:,1]
Exp7_M = data7_M[:,0]
Exp7_M2 = data7_M[:,1]
Exp7_modM = data7_modM[:,0]
Exp7_modM2 = data7_modM[:,1]
Exp8_E = data8_E[:,0]
Exp8_E2 = data8_E[:,1]
Exp8_M = data8_M[:,0]
Exp8_M2 = data8_M[:,1]
Exp8_modM = data8_modM[:,0]
Exp8_modM2 = data8_modM[:,1]
Exp9_E = data9_E[:,0]
Exp9_E2 = data9_E[:,1]
Exp9_M = data9_M[:,0]
Exp9_M2 = data9_M[:,1]
Exp9_modM = data9_modM[:,0]
Exp9_modM2 = data9_modM[:,1]

T = np.linspace(3.8,4.7,np.size(Exp7_E))

chi7 = ((7**3)**2*Exp7_modM2 - (7**3)**2*Exp7_modM**2)/T
chi8 = ((8**3)**2*Exp8_modM2 - (8**3)**2*Exp8_modM**2)/T
chi9 = ((9**3)**2*Exp9_modM2 - (9**3)**2*Exp9_modM**2)/T

cv7 = ((7*7*7)**2)*(Exp7_E2 - Exp7_E*Exp7_E)/(T*T)
cv8 = ((8*8*8)**2)*(Exp8_E2 - Exp8_E*Exp8_E)/(T*T)
cv9 = ((9*9*9)**2)*(Exp9_E2 - Exp9_E*Exp9_E)/(T*T)
print(chi7[-11])
print(chi8[-11])
print(chi9[-11])

print()
print(cv8.max())
print(cv9.max())

print()
print(Exp7_M[0])

plt.plot(T, chi7, '.-', label="L = 7")
plt.plot(T, chi8, '.-', label="L = 8")
plt.plot(T, chi9, '.-', label="L = 9")
plt.xlabel("Temperature")
plt.ylabel("$\chi$")
plt.legend()
plt.title("$\chi$ vs T for different box sizes")
plt.savefig("figures/Q7_chi_T.png")
plt.clf()

plt.plot(T, cv7, '.-', label="L = 7")
plt.plot(T, cv8, '.-', label="L = 8")
plt.plot(T, cv9, '.-', label="L = 9")
plt.xlabel("Temperature")
plt.ylabel("$C_v$")
plt.legend()
plt.title("$C_v$ vs T for different box sizes")
plt.savefig("figures/Q7_cv_T.png")
plt.clf()

plt.plot(T, Exp7_M,'.--', label="(Mag) L = 7")
plt.plot(T, Exp8_M,'.--', label="(Mag) L = 8")
plt.plot(T, Exp9_M,'.--', label="(Mag) L = 9")
plt.plot(T, Exp7_modM,'.--', label="(abs Mag) L = 7")
plt.plot(T, Exp8_modM,'.--', label="(abs Mag) L = 8")
plt.plot(T, Exp9_modM,'.--', label="(abs Mag) L = 9")
plt.xlabel("Temperature")
plt.ylabel("M/N")
plt.legend()
plt.title("Magnetization per Spin vs T")
plt.savefig("figures/Q7-M.png")
plt.clf()

plt.plot(T, Exp7_E,'.-', label="L = 7")
plt.plot(T, Exp8_E,'.-', label="L = 8")
plt.plot(T, Exp9_E,'.-', label="L = 9")
plt.xlabel("Temperature")
plt.ylabel("E/N")
plt.legend()
plt.title("Energy per Spin vs T")
plt.savefig("figures/Q7-E.png")
