#include "Kegel.h"
#include <iostream>
/*        for(float y=x-(3600/refine);y<x;y=y+(3600/refine)){
            std::cout<<"y.x"<<vertices.at(0).x<<"y.y"<<vertices.at(1).y<<"y.z"<<vertices.at(1).z<<std::endl;

        }*/

Kegel::Kegel(int id,float radius,int hoehe, int refine):id(id),radius(radius),hoehe(hoehe),refine(refine)
{

    type= Cg::TriangleMesh;
    erstelleRechtEck(glm::vec3(.1,.1,.2),glm::vec3(.3,.4,.5),glm::vec3(.5,.2,.6),1);
    //create();
   /* int count=0;
    vertices.push_back(glm::vec3(0,0,0));
    for(float x=0;x<360;x=x+(360/refine)){
    vertices.push_back(glm::vec3(radius*glm::cos(glm::radians(x)),radius*glm::sin(glm::radians(x)),0));
   // vertices.push_back(glm::vec3(radius*glm::cos(glm::radians(x)),radius*glm::sin(glm::radians(x)),hoehe));

    triangleIndices.push_back(0);
    triangleIndices.push_back(count+1);
    triangleIndices.push_back(count+2);
    count++;
    }

    triangleIndices.push_back(0);
    triangleIndices.push_back(1);
    triangleIndices.push_back(count);


*/
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
    vertices.push_back(glm::vec3(0,0,0));
    vertices.push_back(glm::vec3(0,0,hoehe));

    vertices.push_back(glm::vec3(glm::cos(glm::radians(0.)),glm::sin(glm::radians(0.)),0));
    vertices.push_back(glm::vec3(glm::cos(glm::radians(0.)),glm::sin(glm::radians(0.)),hoehe));

    vertices.push_back(glm::vec3(glm::cos(glm::radians(60.)),glm::sin(glm::radians(60.)),0));
    vertices.push_back(glm::vec3(glm::cos(glm::radians(60.)),glm::sin(glm::radians(60.)),hoehe));
    vertices.push_back(glm::vec3(glm::cos(glm::radians(120.)),glm::sin(glm::radians(120.)),0));
    vertices.push_back(glm::vec3(glm::cos(glm::radians(120.)),glm::sin(glm::radians(120)),hoehe));

    vertices.push_back(glm::vec3(glm::cos(glm::radians(180.)),glm::sin(glm::radians(180.)),0));
    vertices.push_back(glm::vec3(glm::cos(glm::radians(180.)),glm::sin(glm::radians(180.)),hoehe));

    triangleIndices.push_back(2);
    triangleIndices.push_back(3);
    triangleIndices.push_back(4);

    triangleIndices.push_back(2);
    triangleIndices.push_back(4);
    triangleIndices.push_back(5);


    triangleIndices.push_back(3);
    triangleIndices.push_back(4);
    triangleIndices.push_back(0);

    triangleIndices.push_back(2);
    triangleIndices.push_back(5);
    triangleIndices.push_back(1);
}
void Kegel::erstelleRechtEck(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int count)
{
    glm::vec3 pZusatz1;
    pZusatz1.x = p2.x+(p1.x-p3.x);
    pZusatz1.y = p2.y+(p1.y-p3.y);
    pZusatz1.z = (p2.z+(p1.z-p3.z))*(-1);
    vertices.push_back(p1);
    vertices.push_back(p2);
    vertices.push_back(p3);
    vertices.push_back(pZusatz1);
    triangleIndices.push_back(0);
    triangleIndices.push_back(1);
    triangleIndices.push_back(2);

    triangleIndices.push_back(0);
    triangleIndices.push_back(2);
    triangleIndices.push_back(3);
}
