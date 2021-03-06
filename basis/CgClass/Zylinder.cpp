#include "Zylinder.h"
#include <iostream>
#include <stdlib.h>
/*        for(float y=x-(3600/refine);y<x;y=y+(3600/refine)){
            std::cout<<"y.x"<<vertices.at(0).x<<"y.y"<<vertices.at(1).y<<"y.z"<<vertices.at(1).z<<std::endl;

        }*/

Zylinder::Zylinder(int id,float radius,float hoehe, int refine,bool normalsberechnen):id(id),radius(radius),hoehe(hoehe),refine(refine)
  ,normalsberechnen(normalsberechnen),type(Cg::TriangleMesh){
    create();

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

std::vector<MyPolyline *> Zylinder::getGeraden() const
{
    return geraden;
}

void Zylinder::setGeraden(const std::vector<MyPolyline *> &value)
{
    geraden = value;
}

bool Zylinder::getNormalsberechnen() const
{
    return normalsberechnen;
}

void Zylinder::setNormalsberechnen(bool value)
{
    normalsberechnen = value;
    vertices.clear();
    triangleIndices.clear();
    vertexNormals.clear();
    faceColors.clear();
    geraden.clear();
    create();
}

int Zylinder::create(){
    /*0*/   vertices.push_back(glm::vec3(0,0,0));
    /*1*/    vertices.push_back(glm::vec3(0,0,hoehe));
    for( float x = 0.0;x<360.0+360.0/refine;x=x+(360.0/refine))
    {
        vertices.push_back(glm::vec3(radius*glm::cos(glm::radians(x)),radius*glm::sin(glm::radians(x)),0));
        vertices.push_back(glm::vec3(radius*glm::cos(glm::radians(x)),radius*glm::sin(glm::radians(x)),hoehe));
    }

    //bottom
    int d;
    for(d = 0; d<=refine*3;d+=2)
    {

        //top
        triangleIndices.push_back(d+4);
        triangleIndices.push_back(d+2);
        triangleIndices.push_back(0);

        //bottom
        triangleIndices.push_back(d+1);
        triangleIndices.push_back(d+3);
        triangleIndices.push_back(1);


        //side
        //3.5-5.7-7.9
        //2.4-4.6-6.8
        triangleIndices.push_back(d+3);
        triangleIndices.push_back(d+2);
        triangleIndices.push_back(d+5);

        triangleIndices.push_back(d+3);
        triangleIndices.push_back(d+4);
        triangleIndices.push_back(d+5);



    }
    if(normalsberechnen){
        berechneSchwerPunkte();
        berechneNormale();
        for(int i =0;i<faceNormals.size();i++){
            std::vector<glm::vec3> x;
            x.push_back(schwerpunkte.at(i));
            x.push_back(glm::normalize(faceNormals.at(i))+schwerpunkte.at(i));
            geraden.push_back(MeshFactory::createMyPolyline(glm::vec3(244,44,44),x));
        }
        std::cout<<triangleIndices.size()<<" "<<d<<std::endl;
    }

}

void Zylinder::setRefine(int wert){
    this->refine = wert;
    create();
}
void Zylinder::setHoehe(float wert){
    this->hoehe = wert;
    create();
}

void Zylinder::berechneSchwerPunkte()
{
    for(int i =0;i<triangleIndices.size();i=i+3){
        if(triangleIndices.at(i)<vertices.size()
                && triangleIndices.at(i+1)<vertices.size()
                && triangleIndices.at(i+2)<vertices.size()){
            glm::vec3 l= (vertices.at(triangleIndices.at(i))+
                          vertices.at(triangleIndices.at(i+1))+
                          vertices.at(triangleIndices.at(i+2)));
            glm::vec3 k =glm::vec3(l.x/3,l.y/3,l.z/3);
            schwerpunkte.push_back(k);
        }

    }

}

void Zylinder::berechneNormale()
{
    int d=0;
    for(int i =0;i<triangleIndices.size();i=i+3){

        if(triangleIndices.at(i+2)<vertices.size()
                && triangleIndices.at(i)<vertices.size()
                && triangleIndices.at(i+1)<vertices.size()){
            faceNormals.push_back(normalen(vertices.at(triangleIndices.at(i)),
                                           vertices.at(triangleIndices.at(i+1)),
                                           vertices.at(triangleIndices.at(i+2)),schwerpunkte.at(d)));
            d++;
        }
    }
}

glm::vec3 Zylinder::normalen(glm::vec3 a,glm::vec3 b, glm::vec3 c,glm::vec3 mittelpunkt){
    glm::vec3 k;

    glm::vec3 vab = b-a;
    glm::vec3 vac = c-a;

    k.x = vab.y*vac.z - vac.y*vab.z;
    k.y = vab.z*vac.x - vac.z*vab.x;
    k.z = vab.x*vac.y - vac.x*vab.y;
    glm::vec3 o;
    o.x=k.x+mittelpunkt.x;
    o.y=k.y+mittelpunkt.y;
    o.z=k.z+mittelpunkt.z;
    return glm::normalize(o);
}
