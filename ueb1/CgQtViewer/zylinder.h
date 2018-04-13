#ifndef ZYLINDER_H
#define ZYLINDER_H
#include <CgBase/CgBaseTriangleMesh.h>

class Zylinder : public CgBaseTriangleMesh
{
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> norms;
    std::vector<glm::vec3> color;
    std::vector<glm::vec3> verttext;
    std::vector<unsigned int> indexe;
    std::vector<glm::vec3> facenorms;
    std::vector<glm::vec3> facecolors;
    enum Cg::ObjectType type;
    unsigned int id;

public:
    Zylinder();

    ~Zylinder(){};


    const std::vector<glm::vec3>& getVertices()const;
    const std::vector<glm::vec3>& getVertexNormals() const;
    const std::vector<glm::vec3>& getVertexColors() const;

    const std::vector<glm::vec2>& getVertexTexCoords() const;

    // ein Dreieck hat immer 3 Indices, also ist die Index-Liste 3 mal so lang wie die Anzahl der Dreiecke
    const std::vector<unsigned int>& getTriangleIndices() const;

    // Es gibt so viele Face-Normalen wie Polygone/Dreiecke, da ein Face als planar angenommen wird und daher genau eine Normale hat.
     const std::vector<glm::vec3>& getFaceNormals() const ;

    // Falls eine Farbe pro Polygon spezifiziert ist, so ist es einfarbig in genau dieser Farbe, also auch #Farben=#Faces
     const std::vector<glm::vec3>& getFaceColors() const ;

     Cg::ObjectType getType() const  ;
     unsigned int getID() const  ;
};

#endif // ZYLINDER_H
