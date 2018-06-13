#ifndef KUGEL_H
#define KUGEL_H
#include "rotationskoerper.h"
#include "CgBase/CgBaseTriangleMesh.h"
#include "vector"
#include "glm/glm.hpp"
#include "CgClass/appearance.h"
class Kugel : public CgBaseTriangleMesh
{


private :
    float radius;float hoehe;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3>vertexNormals;
    std::vector<glm::vec3> vertexColors;
    std::vector<glm::vec2> vertexTexCoords;
    std::vector<unsigned int> triangleIndices;
    std::vector<glm::vec3> faceNormals;
    std::vector<glm::vec3> faceColors;
    enum Cg::ObjectType type;
    Appearance* appear;
    int refine;
    int id;
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
};

#endif // KUGEL_H
