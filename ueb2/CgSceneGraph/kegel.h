#ifndef KEGEL_H
#define KEGEL_H
#include <CgBase/CgBaseTriangleMesh.h>
#include <CgBase/CgBasePolyline.h>
class Kegel: public CgBaseTriangleMesh
{
private:
    // CgBaseRenderableObject interface
    enum Cg::ObjectType type;
    unsigned int id;
    float radius;
    float hoehe;
    int refine;
    // CgBaseTriangleMesh interface
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> vertexNormals;
    std::vector<glm::vec3> vertexColors;
    std::vector<glm::vec2> vertexTexCoords;
    std::vector<unsigned int> triangleIndices;
    std::vector<glm::vec3> faceNormals;
    std::vector<glm::vec3> faceColors;

    void erstelleRechtEck(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int count);
public:
    int create();
    Kegel();
    Kegel(int id,float radius, float hoehe,int refine);

    // CgBaseRenderableObject interface
    enum Cg::ObjectType getType() const;
    unsigned int getID() const;

    void setRefine(int wert);
    void setHoehe(float wert);


    // CgBaseTriangleMesh interface
    const std::vector<glm::vec3> &getVertices() const;
    const std::vector<glm::vec3> &getVertexNormals() const;
    const std::vector<glm::vec3> &getVertexColors() const;
    const std::vector<glm::vec2> &getVertexTexCoords() const;
    const std::vector<unsigned int> &getTriangleIndices() const;
    const std::vector<glm::vec3> &getFaceNormals() const;
    const std::vector<glm::vec3> &getFaceColors() const;
};

#endif // KEGEL_H
