import matplotlib.pyplot as plt
import numpy as np

#input
inputFilePath = '../Data/Zachary_2D_coordinates.txt'
embedding_coordinates = np.loadtxt(inputFilePath)
n = len(embedding_coordinates)
labels = range(1, n+1)

#print('plotting')
#plotting
x = embedding_coordinates[:,0]
y = embedding_coordinates[:,1]

plt.scatter(x, y)
for i, label in enumerate(labels):
	plt.annotate(label, (x[i], y[i]))
plt.show()
