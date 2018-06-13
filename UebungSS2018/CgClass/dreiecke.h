#ifndef DREIECK_H
#define DREIECK_H
#include "CgBase/CgBaseTriangleMesh.h"
#include "CgClass/Mypolyline.h"
#include "CgClass/meshfactory.h"

class MyPolyline;
class Dreiecke:public CgBaseTriangleMesh
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
    std::vector<glm::vec3> pointnormals;
    std::vector<MyPolyline*> geraden;

public:
    Dreiecke();
    Dreiecke(int id,std::vector<glm::vec3>x,std::vector<unsigned int>k);

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

    bool equal(glm::vec3 a, glm::vec3 b);
    bool equalDouble(double x, double y);
    bool berechnePunktNormale();
    glm::vec3 berechneSchwerPunkte(glm::vec3 a, glm::vec3 b, glm::vec3 c);
    glm::vec3 normalenV(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 mittelpunkt);
    std::vector<MyPolyline *> getGeraden() const;
    void setGeraden(const std::vector<MyPolyline *> &value);
};

#endif // DREIECK_H
