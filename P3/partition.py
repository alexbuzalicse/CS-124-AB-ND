import sys
import numpy as np
import standardAlgorithms
import prepartitionAlgorithms

def main():

    flag = int(sys.argv[1])
    algorithm = int(sys.argv[2])
    inputFileName = sys.argv[3]

    maxIterations = 1000
    file = open(inputFileName, "r")
    content = file.read()
    A = np.array(content.split('\n'),dtype = int)

    match algorithm:
        case 0:
            print(standardAlgorithms.karmarkarKarp(A))
        case 1:
            print(standardAlgorithms.repeatedRandom(A,maxIterations))
        case 2:
            print(standardAlgorithms.hillClimbing(A,maxIterations))
        case 3:
            print(standardAlgorithms.simulatedAnnealing(A,maxIterations))
        case 11:
            print(prepartitionAlgorithms.repeatedRandom(A,maxIterations))
        case 12:
            print(prepartitionAlgorithms.hillClimbing(A,maxIterations))
        case 13:
            print(prepartitionAlgorithms.simulatedAnnealing(A,maxIterations))

if __name__ == "__main__":
    main()