#include "dreieck.h"

Dreieck::Dreieck()
{

}

Dreieck::Dreieck(int id,std::vector<glm::vec3> vertices):id(id),
    type(Cg::TriangleMesh),

    vetices(vertices)
{
    this->vcolor.push_back(glm::vec3(255,0,0));
    this->fcolor.push_back(glm::vec3(255,0,0));
}

enum Cg::ObjectType Dreieck::getType() const{
    return type;
}

unsigned int Dreieck::getID() const{
    return id;
}

const std::vector<glm::vec3> & Dreieck::getVertices() const{
    return vetices;
}
const std::vector<glm::vec3> & Dreieck::getVertexNormals() const{
    return vernormals;
}
const std::vector<glm::vec3> & Dreieck::getVertexColors() const{
    return vcolor;
}
const std::vector<glm::vec2> & Dreieck::getVertexTexCoords() const{
    return triangletextcoords;
}
const std::vector<unsigned int> & Dreieck::getTriangleIndices() const{
    return indeces;
}
const std::vector<glm::vec3> & Dreieck::getFaceNormals() const{
    return facenormals;
}
const std::vector<glm::vec3> & Dreieck::getFaceColors() const{
    return fcolor;
}

