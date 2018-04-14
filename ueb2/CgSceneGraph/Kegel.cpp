#include "Kegel.h"
#include <iostream>
/*        for(float y=x-(3600/refine);y<x;y=y+(3600/refine)){
            std::cout<<"y.x"<<vertices.at(0).x<<"y.y"<<vertices.at(1).y<<"y.z"<<vertices.at(1).z<<std::endl;

        }*/

Kegel::Kegel(int id,float radius,int hoehe, int refine):id(id),radius(radius),hoehe(hoehe),refine(refine)
{

    type= Cg::TriangleMesh;
    faceColors.push_back(glm::vec3(255,0,0));
    vertexColors.push_back(glm::vec3(255,255,0));
    int count=0;

    vertices.push_back(glm::vec3(0,0,0));
    for(float x=0;x<360;x=x+(360/refine)){
    vertices.push_back(glm::vec3(glm::cos(radius*glm::radians(x)),glm::sin(radius*glm::radians(x)),0));

    triangleIndices.push_back(0);
    triangleIndices.push_back(count+1);
    triangleIndices.push_back(count+2);
    count++;
    }

    triangleIndices.push_back(0);
    triangleIndices.push_back(1);
    triangleIndices.push_back(count);



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
