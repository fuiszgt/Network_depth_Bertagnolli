import numpy as np

#input
inputFilePath = '../Data/'
inputFileName = 'Zachary_2D_coordinates.txt'
embedded = np.loadtxt(inputFilePath + inputFileName)

#PTD
cov = np.cov(embedded)
