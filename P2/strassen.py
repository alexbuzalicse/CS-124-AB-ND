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
    # size of matrix
    n = int(sys.argv[1])

    # determine padded matrix size, k
    k = get_k(n)

    # what kind of calc to run - get guidance on cmd args
    type = sys.argv[2]

    # cutoff point of strassen's algorithm
    n_0 = 100 # get a real value here later, also will test multiple vals

    # make matrices to be of a size 2^k for some k
    if (type == "binary"):
        A = binary_matrix_maker(n, k)
        B = binary_matrix_maker(n, k)
    else:
        # TODO: add other init types!
        A = binary_matrix_maker(n, k)
        B = binary_matrix_maker(n, k)

    # determine true value of C = A B, and the time it takes
    t0 = time.perf_counter()
    C_true =  A @ B
    t1 = time.perf_counter()

    time_baseline = t1 - t0

    # determine strassen's output
    t0 = time.perf_counter()
    C_strassen = strassen_multiply(A, B, n_0)
    t1 = time.perf_counter()

    time_strassen = t1 - t0


if __name__ == "__main__":
    main()