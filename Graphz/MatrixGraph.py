import sys
from PointVertex import PointVertexMatrix, euclidianDistance
INFINITE = sys.maxsize

class MatrixGraph:
    vertices = dict()
    edges = list() #Inicializar com matrix
    verticesIndex = dict()
    numberOfVertices = 0

    def addVertex(self, vertex):
        if isinstance(vertex, PointVertexMatrix) and vertex not in self.vertices:
            self.vertices[vertex.getName()] = vertex

            for line in self.edges:
                line.append(0)

            self.edges.append([0] * (len(self.edges)+1) )

            self.verticesIndex[vertex.getName()] = len(self.verticesIndex)
            self.numberOfVertices += 1
    
    def addEdge(self, initialVertex, destinationVertex):
        #if both vertices are instances of Vertex
        if isinstance(initialVertex, PointVertexMatrix) and isinstance(destinationVertex, PointVertexMatrix):
            weight = euclidianDistance(initialVertex, destinationVertex)
            #if both vertices are in the graph
            if initialVertex.getName() in self.vertices and destinationVertex.getName() in self.vertices:
                initialIndex = self.verticesIndex[initialVertex.getName()]
                destinationIndex = self.verticesIndex[destinationVertex.getName()]

                self.edges[initialIndex][destinationIndex] = weight
    
    def existEdge(self, initialVertex, destinationVertex):
        #if both vertices are instances of Vertex
        if isinstance(initialVertex, PointVertexMatrix) and isinstance(destinationVertex, PointVertexMatrix):
            #if both vertices are in the graph
            if initialVertex.getName() in self.vertices and destinationVertex.getName() in self.vertices:

                initialIndex = self.verticesIndex[initialVertex.getName()]
                destinationIndex = self.verticesIndex[destinationVertex.getName()]

                if self.edges[initialIndex][destinationIndex] != 0:
                    return True
        
        return False

    def getEdge(self, initialVertex, destinationVertex):
        if self.existEdge(initialVertex, destinationVertex):

            initialIndex = self.verticesIndex[initialVertex.getName()]
            destinationIndex = self.verticesIndex[destinationVertex.getName()]
            return self.edges[initialIndex][destinationIndex]
        else:
            return 0
    
    def toString(self):
        toReturn = "["

        for currentVertex in self.verticesIndex.items():
            for adjacentV in self.verticesIndex.items(): 
                if self.edges[currentVertex[1]][adjacentV[1]] != 0:#.items() returns a tuple (key, value)
                    toReturn += "\n("+ currentVertex[0]+")=>(" + adjacentV[0] +"); "
        toReturn += "]\n"
        return toReturn

    def FloydMarshall(self):

        distanceMatrix = list()

        #Initializes the distanceMatrix with max
        for i in range(self.numberOfVertices):
            distanceMatrix.append([INFINITE] * self.numberOfVertices)

        for i in range(self.numberOfVertices):
            distanceMatrix[i][i] = 0

            for j in range(self.numberOfVertices):
                if(self.edges[i][j] != 0):
                    distanceMatrix[i][j] = self.edges[i][j]
                
        for k in range(self.numberOfVertices):
            for i in range(self.numberOfVertices):
                for j in range(self.numberOfVertices):
                    if((distanceMatrix[i][k] + distanceMatrix[k][j]) < (distanceMatrix[i][j])):
                        distanceMatrix[i][j] = (distanceMatrix[i][k] + distanceMatrix[k][j])
        return distanceMatrix

    def getExcentricityList(self):
        distanceMatrix = self.FloydMarshall()
        excentricityList = ([-1] * self.numberOfVertices)
        for i in range(self.numberOfVertices):
            #print(list(self.vertices.keys()).index(i))
            for j in range(self.numberOfVertices):

                # if distanceMatrix[j][i] == sys.maxsize:#se o vertex que chega em i é infinito
                #     if excentricityList[i] == -1:
                #         excentricityList[i] = distanceMatrix[j][i]

                # elif excentricityList == sys.maxsize:
                #     if distanceMatrix[j][i] != 0:
                #         excentricityList[i] = min(excentricityList[i], distanceMatrix[j][i])#Max cost of i

                # else: excentricityList[i] = max(excentricityList[i], distanceMatrix[j][i])   
                if(distanceMatrix[j][i] != INFINITE):
                    excentricityList[i] = max(distanceMatrix[j][i], excentricityList[i])   
                
        return excentricityList

    def centralVertex(self, excentricityList):
        smaller = sys.maxsize
        currentSmaller = None
        for vertex in self.verticesIndex.items():#(name, index)
            if excentricityList[vertex[1]] != 0 and excentricityList[vertex[1]] < smaller:
                currentSmaller = vertex
                smaller = excentricityList[vertex[1]]
        if currentSmaller != None:
            return self.vertices[currentSmaller[0]]

    def peripheralVertex(self, excentricityList):
        bigger = -1
        currentBigger = None
        for vertex in self.verticesIndex.items():
            if excentricityList[vertex[1]] > bigger:
                currentBigger = vertex
                bigger = excentricityList[vertex[1]]
        if currentBigger != None:
            return self.vertices[currentBigger[0]]
    
    def getFarthestVertex(self, originVertex):
        if isinstance(originVertex, PointVertexMatrix):
            distanceMatrix = self.FloydMarshall()
            greatestDistance = 0
            farthest = None
            index = self.verticesIndex[originVertex.getName()]
            for vertex in self.verticesIndex.items():
                currentDistance = distanceMatrix[index][vertex[1]]

                #if currentDistance != sys.maxsize:
                if currentDistance > greatestDistance:
                    #print("cur "+  str(currentDistance))
                    farthest = vertex
                    greatestDistance = currentDistance
            
            if farthest != None: 
                farthest = self.vertices[farthest[0]]
                return farthest
        return originVertex
            