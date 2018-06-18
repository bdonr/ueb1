#include "wuerfel.h"
#include <iostream>
/**
 * @brief Wuerfel::Wuerfel
 * @param id
 * @param colors
 *
 * erstelle würfel mit farben und id sowie typ
 */
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
     berechneSchwerPunkte();
    berechneNormale();

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
/**
 * @brief Wuerfel::berechneSchwerPunkte
 *
 * berechne schwerpunkt mit Hilfe der indeces und dessen schwerpunkt
 */
void Wuerfel::berechneSchwerPunkte()
{
    for(int i =0;i<triangleIndices.size();i=i+3){

        glm::vec3 l= (vertices.at(triangleIndices.at(i))+
                      vertices.at(triangleIndices.at(i+1))+
         vertices.at(triangleIndices.at(i+2)));
        schwerpunkte.push_back((glm::vec3(l.x/3,l.y/3,l.z/3)));
    }

}
/**
 * @brief Wuerfel::berechneNormale
 * berechne normale
 *
 */
void Wuerfel::berechneNormale()
{
    int d=0;
    for(unsigned int i =0;i<triangleIndices.size();i=i+3){

        if(triangleIndices.at(i+2)<vertices.size()
                && triangleIndices.at(i)<vertices.size()
                && triangleIndices.at(i+1)<vertices.size()){
            faceNormals.push_back(normalen(vertices.at(triangleIndices.at(i)),
                                           vertices.at(triangleIndices.at(i+1)),
                                           vertices.at(triangleIndices.at(i+2)),schwerpunkte.at(d)));
            d++;
        }
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
glm::vec3 Wuerfel::normalen(glm::vec3 a,glm::vec3 b, glm::vec3 c,glm::vec3 mittelpunkt){
    glm::vec3 k;

    glm::vec3 vab = b-a;
    glm::vec3 vac = c-a;

    k.x = vab.y*vac.z - vac.y*vab.z;
    k.y = vab.z*vac.x - vac.z*vab.x;
    k.z = vab.x*vac.y - vac.x*vab.y;
    glm::vec3 o;
    o.x=k.x+mittelpunkt.x;
    o.y=k.y+mittelpunkt.y;
    o.z=k.z+mittelpunkt.z;
    return glm::normalize(o);
}





