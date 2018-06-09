#ifndef Zylinder_H
#define Zylinder_H
#include <CgBase/CgBaseTriangleMesh.h>
#include <vector>
#include "CgClass/Mypolyline.h"
#include "CgClass/meshfactory.h"
class Zylinder: public CgBaseTriangleMesh
{

private:
    // CgBaseRenderableObject interface
    enum Cg::ObjectType type;
    unsigned int id;
    float radius;
    float hoehe;
    int refine;
    bool normalsberechnen;
    // CgBaseTriangleMesh interface
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> vertexNormals;
    std::vector<glm::vec3> vertexColors;
    std::vector<glm::vec2> vertexTexCoords;
    std::vector<unsigned int> triangleIndices;
    std::vector<glm::vec3> faceNormals;
    std::vector<glm::vec3> faceColors;
    std::vector<MyPolyline*> geraden;
    std::vector<glm::vec3> schwerpunkte;
    int create();
    void erstelleRechtEck(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int count);
public:
    Zylinder();
    Zylinder(int id,float radius, float hoehe,int refine,bool normalsberechnen);

    // CgBaseRenderableObject interface
    enum Cg::ObjectType getType() const;
    unsigned int getID() const;
    void setType(enum Cg::ObjectType type);

    // CgBaseTriangleMesh interface
    const std::vector<glm::vec3> &getVertices() const;
    const std::vector<glm::vec3> &getVertexNormals() const;
    const std::vector<glm::vec3> &getVertexColors() const;
    const std::vector<glm::vec2> &getVertexTexCoords() const;
    const std::vector<unsigned int> &getTriangleIndices() const;
    const std::vector<glm::vec3> &getFaceNormals() const;
    const std::vector<glm::vec3> &getFaceColors() const;
    void setRefine(int wert);
    void setHoehe(float wert);
    std::vector<MyPolyline *> getGeraden() const;
    void setGeraden(const std::vector<MyPolyline *> &value);
    void berechneSchwerPunkte();
    void berechneNormale();
    glm::vec3 normalen(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 mittelpunkt);
};

#endif // Zylinder_H
