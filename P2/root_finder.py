"""
script to find the root of the cutoff equation
"""

import numpy as np
from scipy.optimize import root
import matplotlib.pyplot as plt

def N_set_maker(n : int, n0: int) -> list:
    """ n and n0 should be powers of 2 """
    N = []
    i = 1
    while (n >= 2 * n0):
        N.append([n, i])
        n //= 2
        i += 1
    return N

def strassen_cost(n : int, n0 : int) -> int:
    """
    Returns how expensive Strassen's is for a given n and n0
    """
    N_set = N_set_maker(n, n0)

    cost = (7 ** (len(N_set) + 1) ) * n0

    for N in N_set:
        cost += 7**N[1] * N[0]**2

    return cost

def naive_cost(n : int) -> int:
    """ naive cost of mat mul """
    return n ** 3

def main():
    MAX_POW = 10
    powers = [1 + a for a in np.arange(MAX_POW)]
    trial_ns = [2 ** p for p in powers]

    sign = None

    data = []

    for i, trial_n in enumerate(trial_ns):
        n0s = [2 ** k for k in np.arange(i)]

        loc_data = []
        for n0 in n0s:
            delta = strassen_cost(trial_n, n0) - naive_cost(trial_n)
            loc_data.append(delta)

        data.append(loc_data)

    print(len(data[0]))
    plot(data)

def plot(data : list) -> None:
    """
    plots data collected
    """

    fig, ax = plt.subplots()

    for dat in data:
        if len(dat) == 0:
            continue
        dat = np.array(dat)
        #dat /= np.abs(dat).max()
        ax.plot(dat)

    plt.show()

if __name__ == "__main__":
    main()
