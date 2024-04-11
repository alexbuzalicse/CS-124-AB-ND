import numpy as np

def getAPrime(A,P):

    n = len(A)
    aPrime = np.zeros(n)
    for i in range(n):
        aPrime[P[i]] += A[i]

    return aPrime

def residue(A, P):
    aPrime = getAPrime(A,P)
    return karmarkarKarp(aPrime,P)

def randomNeighbor(P, n):

    pPrime = np.copy(P)

    i,j = np.random.choice(range(n),2)
    while pPrime[i]== j:
        i,j = np.random.choice(range(n),2)

    pPrime[i] = j
    return pPrime

def T(iteration):
    return (10**10) * (0.8**np.floor(iteration/300))

def karmarkarKarp(A,P):

    aPrime = getAPrime(A,P)

    for iteration in range(len(aPrime)):
        i = np.argpartition(aPrime,-2)[-2:]
        aPrime[i[1]] = aPrime[i[1]] - aPrime[i[0]]
        aPrime[i[0]] = 0

    return int(np.partition(aPrime,-1)[-1])

def repeatedRandom(A, maxIterations):

    n = len(A)
    P = np.random.randint(0,n-1,n)

    for iteration in range(maxIterations):

        pPrime = np.random.randint(0,n-1,n)
        if residue(A,pPrime) < residue(A,P):
            P = pPrime

        if residue(A,pPrime) == 0: return 0

    return residue(A, P)

def hillClimbing(A, maxIterations):

    n = len(A)
    P = np.random.randint(0,n-1,n)

    for iteration in range(maxIterations):

        pPrime = randomNeighbor(P,n)
        if residue(A,pPrime) < residue(A,P):
            P = pPrime

        if residue(A,pPrime) == 0: return 0

    return residue(A,P)

def simulatedAnnealing(A, maxIterations):

    n = len(A)
    P = np.random.randint(0,n-1,n)
    pPrimePrime = np.copy(P)

    for iteration in range(maxIterations):

        pPrime = randomNeighbor(P,n)
        resP = residue(A,P)
        resPPrime = residue(A,pPrime)

        if resPPrime < resP:
            P = pPrime
        else:
            prob = np.exp(-(resPPrime-resP)/T(iteration))
            choice = np.random.choice([0,1],p=[prob,1-prob])
            if choice == 0: P = pPrime

        if resP < residue(A,pPrimePrime):
            pPrimePrime = P

        if resP == 0: return 0

    return residue(A,pPrimePrime)