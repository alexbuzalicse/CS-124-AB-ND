"""
Main file for the Strassen's algo code, CS 124.

Authors: Noah Dohrmann and Alex Buzali
Due: 27 March 2024
"""

import numpy as np
from numpy import linalg
import sys
import os
import time
from math import comb
import matplotlib.pyplot as plt

def binary_matrix_maker(n : int, k : int) -> np.ndarray:
    """ make a binary matrix for input size n, real size of matrix k """
    mat_k = np.zeros(shape=(k,k))
    mat_n = np.random.randint(2, size=(n,n))

    # embed mat_n into mat_k
    mat_k[:n,:n] = mat_n

    return mat_k

def get_k(n : int) -> int:
    """ return the padded size k from an input size n """
    return 2 ** np.ceil(np.log2(n))

def strassen_multiply(U : np.ndarray, V : np.ndarray, n_0 : int) -> np.ndarray:
    """
    Takes in two numpy arrays A and B, and a cutoff point n_0. Performs Strassen's
    algorithm for matrix multiplication until the size of the recursive matrices is n_0.
    At this point, conventional matrix multiplication is used. Returns the computed product
    C = A @ B
    """

    n = U.shape[0]

    # Cutoff point
    if n <= n_0:
        return U@V

    # Pad arrays if necessary
    if n % 2 == 1:

        X = np.zeros((n+1,n+1))
        X[:n,:n] = U

        Y = np.zeros((n+1,n+1))
        Y[:n,:n] = V

        nPrime = n+1

    else:
        X = U
        Y = V
        nPrime = n

    A = X[:nPrime//2,:nPrime//2]
    B = X[:nPrime//2,nPrime//2:]
    C = X[nPrime//2:,:nPrime//2]
    D = X[nPrime//2:,nPrime//2:]

    E = Y[:nPrime//2,:nPrime//2]
    F = Y[:nPrime//2,nPrime//2:]
    G = Y[nPrime//2:,:nPrime//2]
    H = Y[nPrime//2:,nPrime//2:]

    P1 = strassen_multiply(A,F-H,n_0)
    P2 = strassen_multiply(A+B,H,n_0)
    P3 = strassen_multiply(C+D,E,n_0)
    P4 = strassen_multiply(D,G-E,n_0)
    P5 = strassen_multiply(A+D,E+H,n_0)
    P6 = strassen_multiply(B-D,G+H,n_0)
    P7 = strassen_multiply(C-A,E+F,n_0)

    Z1 = -P2 + P4 + P5 + P6
    Z2 = P1 + P2
    Z3 = P3 + P4
    Z4 = P1 - P3 + P5 +P7

    Z = np.block([[Z1,Z2],[Z3,Z4]])

    return Z[:n,:n]

def main():

    # Command line arguments
    flag = int(sys.argv[1])
    n = int(sys.argv[2])
    inputFileName = sys.argv[3]

    # Parse input file
    file = open(inputFileName, "r")
    content = file.read()
    A = np.reshape(content.split('\n')[:n**2],(n,n)).astype('int')
    B = np.reshape(content.split('\n')[n**2:-1],(n,n)).astype('int')


    # cutoff point of strassen's algorithm
    n_0 = 64 # get a real value here later, also will test multiple vals

    # determine strassen's output
    C = strassen_multiply(A, B, n_0)
    for i in range(n):
        print(C[i,i])
    print()

def triangle_finder(p : float, N : int) -> float:
    """
    Given a probability p, create an adjaceny matrix representation of a graph
    G, which has probability p of including each edge. N x N matrix.
    """
    # choose n0 (change this later)
    n0 = 64

    # get the expected number of triangles
    t_expected = comb(N, 3) * p ** 3

    # create the A matrix probabilities
    A = np.random.rand(N, N)

    # assign edges
    for i in range(N):
        for j in range(N):
            A[i][j] = 1 if A[i][j] < p else 0

    # perform Strassen's algorithm to get A^3
    A_copy = A.copy()
    A = strassen_multiply(A, A, n0)
    A = strassen_multiply(A, A_copy, n0)

    # get number of calculated triangles
    t_calc = A.trace() / 6.0

    return t_calc

def expected_triangles(p : float, N : int) -> float:
    """
    returns the number of expected triangles for probability p
    for each edge and size N matrix.
    """
    return comb(N, 3) * p ** 3

def triangle_results() -> None:
    """ plots the results of expected vs. calculated number of triangles """
    ps = np.array([0.01, 0.02, 0.03, 0.04, 0.05])
    N = 1024

    t_expected = np.array([expected_triangles(p, N) for p in ps])
    t_calc = np.array([triangle_finder(p, N) for p in ps])

    fig, ax = plt.subplots()

    ALPHA = 1

    for i in range(len(ps)):
        ax.semilogy(ps[i], t_expected[i], "kx", alpha = ALPHA)
        ax.semilogy(ps[i], t_calc[i], "bx", alpha = ALPHA)

    ax.semilogy(ps[-1], t_expected[-1], "kx", label= "expected", alpha = ALPHA)
    ax.semilogy(ps[-1], t_calc[-1], "bx", label = "calculated", alpha = ALPHA)
    plt.grid()

    ax.set_xlabel("Probability of Edge Inclusion", fontsize=16)
    ax.set_ylabel("Number of Triangles", fontsize=16)
    ax.set_title("Expected v. Calculated Triangles", fontsize=16)
    ax.legend(fontsize=13)
    plt.show()

    plt.savefig("./triangles.png", bbox_inches='tight', dpi=200)

if __name__ == "__main__":
    main()
    #triangle_results()
