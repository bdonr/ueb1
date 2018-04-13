#include "zylinder.h"


Zylinder::Zylinder():id(100001)
{

}



const std::vector<glm::vec3>& Zylinder::getVertices()const{
    return this->vertices;
}
const std::vector<glm::vec3>& Zylinder::getVertexNormals() const{
    return this->norms;
}
const std::vector<glm::vec3>& Zylinder::getVertexColors() const{
    return this->color;
}


const std::vector<glm::vec2>& Zylinder::getVertexTexCoords() const{
    return this->verttext;
}

// ein Dreieck hat immer 3 Indices, also ist die Index-Liste 3 mal so lang wie die Anzahl der Dreiecke
const std::vector<unsigned int>& Zylinder::getTriangleIndices() const{
    return this->indexe;
}

// Es gibt so viele Face-Normalen wie Polygone/Dreiecke, da ein Face als planar angenommen wird und daher genau eine Normale hat.
 const std::vector<glm::vec3>& Zylinder::getFaceNormals() const{
     return this->norms
 }

// Falls eine Farbe pro Polygon spezifiziert ist, so ist es einfarbig in genau dieser Farbe, also auch #Farben=#Faces
 const std::vector<glm::vec3>& Zylinder::getFaceColors() const {
    return this->facecolors;
 }

 Cg::ObjectType Zylinder::getType() const{
     return type;
 }
 unsigned int Zylinder::getID() const{
     return this->id;
 }

