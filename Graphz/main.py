from PointVertex import PointVertexMatrix
from MatrixGraph import MatrixGraph


numberOfVertices = int(input())
graph = MatrixGraph()

for i in range(numberOfVertices):
    coordinates = input()
    coordinates = coordinates.split(',')

    vertex = PointVertexMatrix(int(coordinates[0]), int(coordinates[1]))

    graph.addVertex(vertex)

numberOfEdges = int(input())

for i in range(numberOfEdges):
    edgeDescription = input().split(':')
    initialVertex = edgeDescription[0].split(',')
    destinationVertex = edgeDescription[1].split(',')

    initialVertex = PointVertexMatrix(int(initialVertex[0]), int(initialVertex[1]))
    destinationVertex = PointVertexMatrix(int(destinationVertex[0]), int(destinationVertex[1]))

    graph.addEdge(initialVertex, destinationVertex)

excentricityList = graph.getExcentricityList()
centralVertex = graph.centralVertex(excentricityList)
peripheralVertex = graph.peripheralVertex(excentricityList)

# print(list(graph.vertices.keys())[0])
#print(graph.edges)
print(centralVertex.getName())
print(peripheralVertex.getName())
print(graph.getFarthestVertex(peripheralVertex).getName())
# print(graph.verticesIndex[peripheralVertex.getName()])
