#ifndef KUGEL_H
#define KUGEL_H
#include "rotationskoerper.h"
#include "CgBase/CgBaseTriangleMesh.h"
#include "vector"
#include "glm/glm.hpp"
#include "CgClass/appearance.h"
#include <map>
class Kugel : public CgBaseTriangleMesh
{


private :
    int id;
    float radius;float hoehe;
    int refine;
        enum Cg::ObjectType type;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3>vertexNormals;
    std::vector<glm::vec3> vertexColors;
    std::vector<glm::vec2> vertexTexCoords;
    std::vector<unsigned int> triangleIndices;
    std::vector<glm::vec3> faceNormals;
    std::vector<glm::vec3> faceColors;

    Appearance* appear;
    std::vector<glm::vec3> schwerpunkte;
    std::vector<glm::vec3> normals;
     std::vector<MyPolyline*> geraden;
    std::multimap<unsigned int, unsigned int> verticesOfFaces;

public:
    Kugel();
    Kugel(int id,float radius,float hoehe, int refine);

    // CgBaseRenderableObject interface
public:
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    // CgBaseTriangleMesh interface
public:
    const std::vector<glm::vec3> &getVertices() const;
    const std::vector<glm::vec3> &getVertexNormals() const;
    const std::vector<glm::vec3> &getVertexColors() const;
    const std::vector<glm::vec2> &getVertexTexCoords() const;
    const std::vector<unsigned int> &getTriangleIndices() const;
    const std::vector<glm::vec3> &getFaceNormals() const;
    const std::vector<glm::vec3> &getFaceColors() const;
    int create();
    Appearance *getAppear() const;
    void setAppear(Appearance *value);
    void berechneSchwerPunkte();
    void berechneNormale();
    glm::vec3 normalen(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 mittelpunkt);
    void punktNormalen();
};

#endif // KUGEL_H
