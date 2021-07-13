from typing import List
import math

class PointVertex:
    coordinates = ()
    edges = list()

    def __init__(self, xCoord, yCoord):
        self.coordinates = (xCoord,yCoord)

    def getX(self):
        return self.coordinates[0]

    def getY(self):
        return self.coordinates[1]

    def getName(self):
        return str(self.getX()) +','+ str(self.getY())
    
    def addEdge(self,xCoord, yCoord):
        if(self.edges == None): self.edges = list()

        thisPoint = PointVertex(self.getX(), self.getY())
        adjacentPoint = PointVertex(xCoord, yCoord)

        distance = euclidianDistance(thisPoint, adjacentPoint)
        self.edges.append((distance, adjacentPoint))
        self.edges.sort()
    
    def toString(self):
        print(self.coordinates)
        print(self)
        if(self.edges != None):
            for i in self.edges:
                print('\t=>' + str(i[1].coordinates) + " Distance: " + str(i[0]))

    def verifyEdge(self, xCoord, yCoord):
        for edge in self.edges:
            if(edge[1].getX() == xCoord and edge[1].getY() == yCoord):
                return edge[0];
        return False;

def euclidianDistance(pointOne, pointTwo):
    return math.sqrt((pow(pointOne.getX()-pointTwo.getX(), 2)) + pow(pointOne.getY()-pointTwo.getY(), 2))



class PointVertexMatrix:

    def __init__(self, xValue, yValue):
        self.coordinates = (xValue, yValue)

    def getX(self):
        return self.coordinates[0]

    def getY(self):
        return self.coordinates[1]
    
    def getName(self):
        return str(self.getX()) +','+ str(self.getY())
    