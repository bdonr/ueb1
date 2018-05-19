#ifndef WUERFEL_H
#define WUERFEL_H

#include "CgBase/CgBaseTriangleMesh.h"
#include "Mypolyline.h"
#include "meshfactory.h"
class MyPolyline;
class Wuerfel : public CgBaseTriangleMesh
{


public:
     Wuerfel(int id);
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

    std::vector<glm::vec3> getSchwerpunkte() const;
    void setSchwerpunkte(const std::vector<glm::vec3> &value);



    std::vector<MyPolyline *> getGeraden() const;
    void setGeraden(const std::vector<MyPolyline *> &value);

private:
    unsigned int id;
    enum Cg::ObjectType type;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> vertexNormals;
         std::vector<glm::vec3> vertexColors ;
         std::vector<glm::vec2> vertexTexCoords ;
         std::vector<unsigned int> triangleIndices ;
         std::vector<glm::vec3> faceNormals ;
         std::vector<glm::vec3> faceColors ;
         std::vector<glm::vec3> schwerpunkte;
         void berechneSchwerPunkte();
         void berechneNormale();
         std::vector<MyPolyline*> geraden;

};

#endif // WUERFEL_H
