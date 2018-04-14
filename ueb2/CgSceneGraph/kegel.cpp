#include "kegel.h"
#include <iostream>

Kegel::Kegel(int id,float radius,float hoehe, int refine):id(id),radius(radius),hoehe(hoehe),refine(refine)
{
type= Cg::TriangleMesh;
create();
}

// CgBaseRenderableObject interface
enum Cg::ObjectType Kegel::getType() const{
    return this->type;
}
unsigned int Kegel::getID() const{
    return this->id;
}

// CgBaseTriangleMesh interface
const std::vector<glm::vec3> & Kegel::getVertices() const{
    return this->vertices;
}
const std::vector<glm::vec3> & Kegel::getVertexNormals() const{
    return this->vertexNormals;
}
const std::vector<glm::vec3> & Kegel::getVertexColors() const{
    return this->vertexColors;
}
const std::vector<glm::vec2> & Kegel::getVertexTexCoords() const{
    return this->vertexTexCoords;
}
const std::vector<unsigned int> & Kegel::getTriangleIndices() const{
    return this->triangleIndices;
}
const std::vector<glm::vec3> & Kegel::getFaceNormals() const{
    return this->faceNormals;
}
const std::vector<glm::vec3> & Kegel::getFaceColors() const{
    return this->faceColors;
}

int Kegel::create(){
     /*0*/   vertices.push_back(glm::vec3(0,0,0));
     /*1*/    vertices.push_back(glm::vec3(0,0,hoehe));
    for( float x = 0.0;x<360.0+360.0/refine;x=x+(360.0/refine))
    {
        vertices.push_back(glm::vec3(radius*glm::cos(glm::radians(x)),radius*glm::sin(glm::radians(x)),0));
    }

    //bottom
int d;
    for(d = 0; d<=refine*3;d+=2)
    {

        //bottom
        triangleIndices.push_back(0);
        triangleIndices.push_back(d+2);
        triangleIndices.push_back(d+4);
        //side
        //3.5-5.7-7.9
        //2.4-4.6-6.8
        triangleIndices.push_back(d+3);
        triangleIndices.push_back(d+5);
        triangleIndices.push_back(1);

    }
    std::cout<<triangleIndices.size()<<" "<<d<<std::endl;

}
