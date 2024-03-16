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
    return np.ceil(np.log2(n))

def strassen_multiply(A : np.ndarray, B : np.ndarray, n_0 : int) -> np.ndarray:
    """
    Takes in two numpy arrays A and B, and a cutoff point n_0. Performs Strassen's
    algorithm for matrix multiplication until the size of the recurive matrices is n_0.
    At this point, conventional matrix multiplication is used. Returns the computed product
    C = A @ B
    """
    C = np.zeros(shape=A.shape)

    # TODO - implement Strassen's with cutoff point n_0

    return C

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
