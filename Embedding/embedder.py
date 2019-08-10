import numpy as np
from sklearn.manifold import MDS


#input
inputFilePath = '../Data/'
inputFileName = 'Distance matrix of BHS15PPI.txt'
distance_mat = np.loadtxt(inputFilePath + inputFileName)

embedder = MDS(n_components=2, dissimilarity = 'precomputed')
embedding_coordinates = embedder.fit_transform(distance_mat)
np.savetxt('../Data/BHS15PPI_2D_coordinates.txt',embedding_coordinates)
