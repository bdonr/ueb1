#ifndef DREIECK_H
#define DREIECK_H
#include "CgBase/CgBaseTriangleMesh.h"

class Dreieck:public CgBaseTriangleMesh
{

private:
    int id;
    enum Cg::ObjectType type;
    std::vector<glm::vec3> vetices;
    std::vector<glm::vec3> faces;
    std::vector<glm::vec3> vernormals;
    std::vector<glm::vec3> vcolor;
    std::vector<glm::vec2> triangletextcoords;
    std::vector<unsigned int> indeces;
    std::vector<glm::vec3> facenormals;
    std::vector<glm::vec3> fcolor;

public:
    Dreieck();
    Dreieck(int id,std::vector<glm::vec3>x);

    // CgBaseRenderableObject interface
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    // CgBaseTriangleMesh interface
    const std::vector<glm::vec3> &getVertices() const;
    const std::vector<glm::vec3> &getVertexNormals() const;
    const std::vector<glm::vec3> &getVertexColors() const;
    const std::vector<glm::vec2> &getVertexTexCoords() const;
    const std::vector<unsigned int> &getTriangleIndices() const;
    const std::vector<glm::vec3> &getFaceNormals() const;
    const std::vector<glm::vec3> &getFaceColors() const;
};

#endif // DREIECK_H
