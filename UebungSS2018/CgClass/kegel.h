#ifndef KEGEL_H
#define KEGEL_H
#include <CgBase/CgBaseTriangleMesh.h>
#include <CgBase/CgBasePolyline.h>
#include "CgClass/Mypolyline.h"
#include "CgClass/meshfactory.h"
#include "CgClass/appearance.h"
class Kegel: public CgBaseTriangleMesh
{
private:
    // CgBaseRenderableObject interface
    enum Cg::ObjectType type;
    enum Cg::ObjectType intern;
    Appearance* appear;
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
    std::vector<MyPolyline*> geraden;
    std::vector<glm::vec3> schwerpunkte;
    bool normalsberechnen;
    void erstelleRechtEck(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int count);
public:
    void create();
    Kegel();
    Kegel(int id,float radius, float hoehe,int refine,bool normalsberechnen);
    void setType(enum Cg::ObjectType x);

    // CgBaseRenderableObject interface
    enum Cg::ObjectType getType() const;
    enum Cg::ObjectType getInternType() const;

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
    void berechneNormaleInSchwerpunkt();
    std::vector<MyPolyline *> getGeraden() const;
    void setGeraden(const std::vector<MyPolyline *> &value);
    std::vector<glm::vec3> getSchwerpunkte() const;
    void setSchwerpunkte(const std::vector<glm::vec3> &value);
    void berechneSchwerPunkte();
    void berechneNormale();
    glm::vec3 normalen(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 mittelpunkt);
    bool getNormalsberechnen() const;
    void setNormalsberechnen(bool value);
    Appearance *getAppear() const;
    void setAppear(Appearance *value);
};

#endif // KEGEL_H
