#include "Zylinder.h"
#include <iostream>
#include <stdlib.h>
/*        for(float y=x-(3600/refine);y<x;y=y+(3600/refine)){
            std::cout<<"y.x"<<vertices.at(0).x<<"y.y"<<vertices.at(1).y<<"y.z"<<vertices.at(1).z<<std::endl;

        }*/

Zylinder::Zylinder(int id,float radius,int hoehe, int refine):id(id),radius(radius),hoehe(hoehe),refine(refine)
{

    type= Cg::TriangleMesh;
   // erstelleRechtEck(glm::vec3(.1,.1,.2),glm::vec3(.3,.4,.5),glm::vec3(.5,.2,.6),1);
    create();
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
enum Cg::ObjectType Zylinder::getType() const{
    return this->type;
}
void Zylinder::setType(enum Cg::ObjectType type){
    this->type = type;
}
unsigned int Zylinder::getID() const{
    return this->id;
}

// CgBaseTriangleMesh interface
const std::vector<glm::vec3> & Zylinder::getVertices() const{
    return this->vertices;
}
const std::vector<glm::vec3> & Zylinder::getVertexNormals() const{
    return this->vertexNormals;
}
const std::vector<glm::vec3> & Zylinder::getVertexColors() const{
    return this->vertexColors;
}
const std::vector<glm::vec2> & Zylinder::getVertexTexCoords() const{
    return this->vertexTexCoords;
}
const std::vector<unsigned int> & Zylinder::getTriangleIndices() const{
    return this->triangleIndices;
}
const std::vector<glm::vec3> & Zylinder::getFaceNormals() const{
    return this->faceNormals;
}
const std::vector<glm::vec3> & Zylinder::getFaceColors() const{
    return this->faceColors;
}

int Zylinder::create(){
     /*0*/   vertices.push_back(glm::vec3(0,0,0));
     /*1*/    vertices.push_back(glm::vec3(0,0,hoehe));
    for( float x = 0.0;x<360.0+360.0/refine;x=x+(360.0/refine))
    {
        vertices.push_back(glm::vec3(radius*glm::cos(glm::radians(x)),radius*glm::sin(glm::radians(x)),0));
        vertices.push_back(glm::vec3(radius*glm::cos(glm::radians(x)),radius*glm::sin(glm::radians(x)),hoehe));
    }
 /*
    vertices.push_back(glm::vec3(0,0,0));
    vertices.push_back(glm::vec3(0,0,hoehe));

    vertices.push_back(glm::vec3(glm::cos(glm::radians(0.)),glm::sin(glm::radians(0.)),0));
    vertices.push_back(glm::vec3(glm::cos(glm::radians(0.)),glm::sin(glm::radians(0.)),hoehe));

    vertices.push_back(glm::vec3(glm::cos(glm::radians(60.)),glm::sin(glm::radians(60.)),0));
    vertices.push_back(glm::vec3(glm::cos(glm::radians(60.)),glm::sin(glm::radians(60.)),hoehe));
    //----------------
    vertices.push_back(glm::vec3(glm::cos(glm::radians(120.)),glm::sin(glm::radians(120.)),0));
    vertices.push_back(glm::vec3(glm::cos(glm::radians(120.)),glm::sin(glm::radians(120.)),hoehe));

    vertices.push_back(glm::vec3(glm::cos(glm::radians(180.)),glm::sin(glm::radians(180.)),0));
    vertices.push_back(glm::vec3(glm::cos(glm::radians(180.)),glm::sin(glm::radians(180.)),hoehe));
*/
    //bottom
int d;
    for(d = 0; d<=refine*3;d+=2)
    {

        //top
        triangleIndices.push_back(0);
        triangleIndices.push_back(d+2);
        triangleIndices.push_back(d+4);
        //bottom
        triangleIndices.push_back(1);
        triangleIndices.push_back(d+3);
        triangleIndices.push_back(d+5);
        //side
        //3.5-5.7-7.9
        //2.4-4.6-6.8
        triangleIndices.push_back(d+3);
        triangleIndices.push_back(d+5);
        triangleIndices.push_back(d+2);

        triangleIndices.push_back(d+3);
        triangleIndices.push_back(d+5);

        triangleIndices.push_back(d+4);
        if(d>= refine*3)
        {
            triangleIndices.push_back(d+4);
            triangleIndices.push_back(d+5);
            triangleIndices.push_back(3);

            triangleIndices.push_back(d+4);
            triangleIndices.push_back(2);
            triangleIndices.push_back(3);
        }
    }
                std::cout<<triangleIndices.size()<<" "<<d<<std::endl;

  /*  triangleIndices.push_back(0);
    triangleIndices.push_back(2);
    triangleIndices.push_back(4);

    triangleIndices.push_back(0);
    triangleIndices.push_back(4);
    triangleIndices.push_back(6);

    triangleIndices.push_back(0);
    triangleIndices.push_back(6);
    triangleIndices.push_back(8);*/
//top
/*
    triangleIndices.push_back(1);
    triangleIndices.push_back(3);
    triangleIndices.push_back(5);

    triangleIndices.push_back(1);
    triangleIndices.push_back(5);
    triangleIndices.push_back(7);

    triangleIndices.push_back(1);
    triangleIndices.push_back(7);
    triangleIndices.push_back(9);*/

//side
    /*
    triangleIndices.push_back(3);
    triangleIndices.push_back(5);
    triangleIndices.push_back(2);

    triangleIndices.push_back(3);
    triangleIndices.push_back(5);
    triangleIndices.push_back(4);

    triangleIndices.push_back(5);
    triangleIndices.push_back(7);
    triangleIndices.push_back(4);

    triangleIndices.push_back(5);
    triangleIndices.push_back(7);
    triangleIndices.push_back(6);

    triangleIndices.push_back(7);
    triangleIndices.push_back(9);
    triangleIndices.push_back(6);

    triangleIndices.push_back(7);
    triangleIndices.push_back(9);
    triangleIndices.push_back(8);

*/

}
void Zylinder::erstelleRechtEck(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, int count)
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


void Zylinder::setRefine(int wert){
    this->refine = wert;
    create();
}
void Zylinder::setHoehe(float wert){
    this->hoehe = wert;
    create();
}

