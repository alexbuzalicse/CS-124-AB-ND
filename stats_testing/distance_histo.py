"""
tester script to plot out a histogram of the different edge distances
"""

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

N = int(2e5)
dims = [0, 2, 3, 4]

def gen_dists(dim):
    dists = np.zeros(N)
    low = dim * (0,)
    high = dim * (1,)
    if dim == 0:
        for i in range(N):
            dists[i] = np.random.uniform()
    else:
        for i in range(N):
            v1 = np.random.uniform(low, high)
            v2 = np.random.uniform(low, high)
            dists[i] = np.linalg.norm(v1 - v2)

    return dists
    

def main():
    dists = []
    for dim in dims:
        dists.append(gen_dists(dim))

    fig, ax = plt.subplots(2,2,figsize=(8,8))

    coord = 0
    for i in range(2):
        for j in range(2):
            ax[i][j].hist(dists[coord],bins=50)
            ax[i][j].set_title(f"{dims[coord]}")
            perc = np.percentile(dists[coord], 1)
            ax[i][j].plot([perc, perc],[0,N/20],"k--")
            coord += 1

    plt.show()

if __name__ == "__main__":
    main()
