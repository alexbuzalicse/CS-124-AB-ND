"""
Script to find the theoretical root at which it becomes computationally
less intensive to use naive matrix multiplication over Strassen's
algorithm.

Authors: Noah Dohrmann and Alex Buzali
"""

import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import root_scalar

def naive_cost(n :int) -> int:
    """ cost for all adds and mults in a naive mat mul """
    return 2 * n ** 3 - n ** 2

def analytic_strassen(n : int) -> float:
    """ the analytic cost expression for the number of flops """
    return 7 * n **(np.log2(7)) - 6 * n ** 2
    #return 7 **(np.log(2 * n) / np.log(2)) - 6 * n ** 2

def analytic_difference(n : int) -> float:
    """ difference in the cost of strassen and naive, analytically """
    return analytic_strassen(n) - naive_cost(n)

def root_finder() -> float:
    """ find the root of the cost difference """
    return root_scalar(analytic_difference, method='bisect', bracket= [400, 800])

def strassen_cost(n : int) -> int:
    """ calculates the total FLOP cost for doing strassen's all the way down """
    if (n == 1):
        return 1
    if (n % 2 != 0):
        # introduce padding
        n += 1
    return 7 * strassen_cost(n // 2) + 2 * n ** 2

def cost_comparison() -> None:
    """ plot the cost comparison for using Strassen's vs naive """
    ns = np.arange(1, 1024)

    naive_costs = []
    strassen_costs = []

    for n in ns:
        naive_costs.append(naive_cost(n))
        strassen_costs.append(strassen_cost(n))

    fig, ax = plt.subplots()

    ax.plot(naive_costs, label="naive")
    ax.plot(strassen_costs, label="strassen")
    ax.legend()

    plt.show()

def analytic_cost_comparison():
    """ compare the analytic costs """

    ns = np.arange(1, 1024)
    strassen = np.array([analytic_strassen(n) for n in ns])
    naive = np.array([naive_cost(n) for n in ns])

    diffs = naive - strassen

    fig, ax = plt.subplots()

    #ax.plot(strassen, label = "strassen")
    #ax.plot(naive, label = "naive")

    ax.plot(diffs)

    ax.legend()
    plt.show()

def main() -> None:
    #cost_comparison()
    #analytic_cost_comparison()
    print(f"The root is {root_finder()}") # gives about 650

if __name__ == "__main__":
    main()
