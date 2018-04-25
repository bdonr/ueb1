#include "dreiecke.h"

Dreiecke::Dreiecke()
{

}

Dreiecke::Dreiecke(int id,std::vector<glm::vec3>vertices,std::vector<unsigned int> indexes):id(id),indeces(indexes),
    type(Cg::TriangleMesh),
    vetices(vertices)
{
    this->vcolor.push_back(glm::vec3(255,0,0));
    this->fcolor.push_back(glm::vec3(0,255,0));
    create();
}

enum Cg::ObjectType Dreiecke::getType() const{
    return type;
}

unsigned int Dreiecke::getID() const{
    return id;
}

const std::vector<glm::vec3> & Dreiecke::getVertices() const{
    return vetices;
}
const std::vector<glm::vec3> & Dreiecke::getVertexNormals() const{
    return vernormals;
}
const std::vector<glm::vec3> & Dreiecke::getVertexColors() const{
    return vcolor;
}
const std::vector<glm::vec2> & Dreiecke::getVertexTexCoords() const{
    return triangletextcoords;
}
const std::vector<unsigned int> & Dreiecke::getTriangleIndices() const{
    return indeces;
}
const std::vector<glm::vec3> & Dreiecke::getFaceNormals() const{
    return facenormals;
}
const std::vector<glm::vec3> & Dreiecke::getFaceColors() const{
    return fcolor;
}

int Dreiecke::create(){


    return 1;
}
