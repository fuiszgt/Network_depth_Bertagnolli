import numpy as np
from numpy import array, asarray, inf, zeros, minimum, diagonal, newaxis
print("Implementing new network centrality measure based on statistical data depth")
print("Export distance")


def check_and_convert_adjacency_matrix(adjacency_matrix):
	mat = asarray(adjacency_matrix)

	(nrows, ncols) = mat.shape
	assert nrows == ncols
	n = nrows

	assert (diagonal(mat) == 0.0).all()

	return (mat, n)


def floyd_warshall_fastest(adjacency_matrix):
	'''floyd_warshall_fastest(adjacency_matrix) -> shortest_path_distance_matrix
	Input
		An NxN NumPy array describing the directed distances between N nodes.
		adjacency_matrix[i,j] = distance to travel directly from node i to node j (without passing through other nodes)
		Notes:
		* If there is no edge connecting i->j then adjacency_matrix[i,j] should be equal to numpy.inf.
		* The diagonal of adjacency_matrix should be zero.
	Output
		An NxN NumPy array such that result[i,j] is the shortest distance to travel between node i and node j. If no such path exists then result[i,j] == numpy.inf
	'''
	(mat, n) = check_and_convert_adjacency_matrix(adjacency_matrix)

	for k in range(n):
		mat = minimum(mat, mat[newaxis,k,:] + mat[:,k,newaxis])
	return mat

#Input

#filename = read()
inputFilePath = '../Data/'
inputFileName = 'biogrid-heat-shock15-yeast-PPI-a-vg.net'
input = open(inputFilePath + inputFileName)

input.readline()
labels = [];
for line in input:
	if '*Edges' in line:
		break
	else:
		labels.append(line.split()[1])
	

n = len(labels)

adj_matrix = np.full((n,n),np.inf)
adjacency = [[]]*(n)
weights = [[]]*(n)

for i in range(n):
	adj_matrix[i][i] = 0.0
	
for line in input:
	parsed = line.split()
	a = int(parsed[0]) - 1
	b = int(parsed[1]) - 1
	w = float(parsed[2])
	adjacency[a].append(b)
	adjacency[b].append(a)
	weights[a].append(w)
	weights[b].append(w)
	adj_matrix[a][b] = w
	adj_matrix[b][a] = w
input.close()

#Computing distance (It takes approximately 20 mins to compute)
	#Floyd-Warshall
	
distance_mat = floyd_warshall_fastest(adj_matrix)
print(distance_mat)

#Saving it to a txt 
np.savetxt('Distance matrix of Zachary.txt', distance_mat)

