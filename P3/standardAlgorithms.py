import numpy as np

def residue(A, S):
    return np.abs(A@S)

def T(iteration):
    return (10**10) * (0.8**np.floor(iteration/300))

def randomNeighbor(S, n):

    sPrime = np.copy(S)
    i,j = np.random.choice(range(n),2,False)
    sPrime[i] *= -1
    sPrime[j] = np.random.choice([sPrime[j], -sPrime[j]])
    return sPrime

def karmarkarKarp(A):

    Acopy = np.copy(A)

    for iteration in range(len(A)):
        i = np.argpartition(Acopy,-2)[-2:]
        Acopy[i[1]] = Acopy[i[1]] - Acopy[i[0]]
        Acopy[i[0]] = 0

    return np.partition(Acopy,-1)[-1]

def repeatedRandom(A, maxIterations):

    n = len(A)
    S = np.random.choice([-1,1],n)

    for iteration in range(maxIterations):
        sPrime = np.random.choice([-1,1],n)
        if residue(A,sPrime) < residue(A,S):
            S = sPrime

        if residue(A,sPrime) == 0: return 0

    return residue(A,S)

def hillClimbing(A, maxIterations):

    n = len(A)
    S = np.random.choice([-1,1],n)

    for iteration in range(maxIterations):

        sPrime = randomNeighbor(S,n)

        if residue(A,sPrime) < residue(A,S):
            S = sPrime

        if residue(A,sPrime) == 0: return 0

    return residue(A,S)

def simulatedAnnealing(A, maxIterations):

    n = len(A)
    S = np.random.choice([-1,1],n)
    sPrimePrime = np.copy(S)

    for iteration in range(maxIterations):

        sPrime = randomNeighbor(S,n)
        resS = residue(A,S)
        resSPrime = residue(A, sPrime)

        if resSPrime < resS:
            S = sPrime

        else:
            prob = np.exp(-(resSPrime-resS)/T(iteration))
            choice = np.random.choice([0,1],p=[prob,1-prob])
            if choice == 0: S = sPrime

        if resS < residue(A,sPrimePrime):
            sPrimePrime = S
        if resS == 0: return 0

    return residue(A,sPrimePrime)
