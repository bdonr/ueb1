#include "wuerfel.h"
#include <iostream>

Wuerfel::Wuerfel(int id,glm::vec3 colors):id(id),type(Cg::TriangleMesh)
{

        vertices.push_back(glm::vec3(-1,-1,-1));
        vertices.push_back(glm::vec3(1,-1,-1));
        vertices.push_back(glm::vec3(1,1,-1));
        vertices.push_back(glm::vec3(-1,1,-1));

        vertices.push_back(glm::vec3(-1,-1,1));
        vertices.push_back(glm::vec3(1,-1,1));
        vertices.push_back(glm::vec3(1,1,1));
        vertices.push_back(glm::vec3(-1,1,1));

//vorne
    triangleIndices.push_back(0);
    triangleIndices.push_back(3);
    triangleIndices.push_back(2);


    triangleIndices.push_back(2);
    triangleIndices.push_back(1);
    triangleIndices.push_back(0);

//hinten
    triangleIndices.push_back(4);
    triangleIndices.push_back(7);
    triangleIndices.push_back(6);


    triangleIndices.push_back(6);
    triangleIndices.push_back(5);
    triangleIndices.push_back(4);

    //links
    triangleIndices.push_back(4);
    triangleIndices.push_back(0);
    triangleIndices.push_back(1);


    triangleIndices.push_back(1);
    triangleIndices.push_back(5);
    triangleIndices.push_back(4);


//unten
    triangleIndices.push_back(0);
    triangleIndices.push_back(3);
    triangleIndices.push_back(7);


    triangleIndices.push_back(7);
    triangleIndices.push_back(4);
    triangleIndices.push_back(0);


//oben
    triangleIndices.push_back(1);
    triangleIndices.push_back(2);
    triangleIndices.push_back(6);


    triangleIndices.push_back(6);
    triangleIndices.push_back(5);
    triangleIndices.push_back(1);

    //rechts
    triangleIndices.push_back(3);
    triangleIndices.push_back(7);
    triangleIndices.push_back(6);


    triangleIndices.push_back(6);
    triangleIndices.push_back(2);
    triangleIndices.push_back(3);
    berechneNormale();
    berechneSchwerPunkte();
    std::cout<<faceNormals.size()<<std::endl;
    for(int i =0;i<faceNormals.size();i++){
        std::vector<glm::vec3> x;
        x.push_back(schwerpunkte.at(i));
        x.push_back(faceNormals.at(i)+schwerpunkte.at(i));
        geraden.push_back(MeshFactory::createMyPolyline(colors,x));
    }
}


Cg::ObjectType Wuerfel::getType() const
{
    return type;
}

unsigned int Wuerfel::getID() const
{
    return id;
}

const std::vector<glm::vec3> &Wuerfel::getVertices() const
{
    return vertices;
}

const std::vector<glm::vec3> &Wuerfel::getVertexNormals() const
{

}

const std::vector<glm::vec3> &Wuerfel::getVertexColors() const
{
    return vertexColors;
}

const std::vector<glm::vec2> &Wuerfel::getVertexTexCoords() const
{
    return vertexTexCoords;
}

const std::vector<unsigned int> &Wuerfel::getTriangleIndices() const
{
    return triangleIndices;
}

const std::vector<glm::vec3> &Wuerfel::getFaceNormals() const
{
    return faceNormals;
}

const std::vector<glm::vec3> &Wuerfel::getFaceColors() const
{
    return faceColors;
}

std::vector<glm::vec3> Wuerfel::getSchwerpunkte() const
{
    return schwerpunkte;
}

void Wuerfel::setSchwerpunkte(const std::vector<glm::vec3> &value)
{
    schwerpunkte = value;
}

void Wuerfel::berechneSchwerPunkte()
{
    for(int i =0;i<triangleIndices.size();i=i+3){

        glm::vec3 l= (vertices.at(triangleIndices.at(i))+
                      vertices.at(triangleIndices.at(i+1))+
         vertices.at(triangleIndices.at(i+2)));
        schwerpunkte.push_back((glm::vec3(l.x/3,l.y/3,l.z/3)));
    }

}

void Wuerfel::berechneNormale()
{
    for(int i =0;i<triangleIndices.size();i=i+3){
        faceNormals.push_back(glm::normalize((vertices.at(triangleIndices.at(i))+
                vertices.at(triangleIndices.at(i+1))+
                vertices.at(triangleIndices.at(i+2)))));
    }
}

std::vector<MyPolyline *> Wuerfel::getGeraden() const
{

    return geraden;
}

void Wuerfel::setGeraden(const std::vector<MyPolyline *> &value)
{
    geraden = value;
}






