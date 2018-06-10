#include "kegel.h"
#include <iostream>

Kegel::Kegel(int id,float radius,float hoehe, int refine,bool shownormals):id(id),radius(radius),hoehe(hoehe),refine(refine),
    normalsberechnen(normalsberechnen),type(Cg::TriangleMesh)
{
create();
}

// CgBaseRenderableObject interface
enum Cg::ObjectType Kegel::getType() const{
    return this->type;
}

enum Cg::ObjectType Kegel::getInternType() const{
    return this->intern;
}

void Kegel::setType(enum Cg::ObjectType x){
    this->type=x;
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

std::vector<MyPolyline *> Kegel::getGeraden() const
{
    return geraden;
}

void Kegel::setGeraden(const std::vector<MyPolyline *> &value)
{
    geraden = value;
}

std::vector<glm::vec3> Kegel::getSchwerpunkte() const
{
    return schwerpunkte;
}
void Kegel::setRefine(int wert){
    this->refine = wert;
}
void Kegel::setHoehe(float wert){
    this->hoehe = wert;
}

void Kegel::setSchwerpunkte(const std::vector<glm::vec3> &value)
{
    schwerpunkte = value;
}

bool Kegel::getNormalsberechnen() const
{
    return normalsberechnen;
}

void Kegel::setNormalsberechnen(bool value)
{
    normalsberechnen = value;
    vertices.clear();
    triangleIndices.clear();
    vertexNormals.clear();
    faceColors.clear();
    geraden.clear();
     create();
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
    for(d = 0; d<=refine*3;d+=1)
    {

        //bottom
        triangleIndices.push_back(d+3);
        triangleIndices.push_back(d+1);
        triangleIndices.push_back(0);

        //side
        //3.5-5.7-7.9
        //2.4-4.6-6.8
        triangleIndices.push_back(d+2);
        triangleIndices.push_back(d+3);
        triangleIndices.push_back(1);

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

void Kegel::berechneSchwerPunkte()
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

void Kegel::berechneNormale()
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

glm::vec3 Kegel::normalen(glm::vec3 a,glm::vec3 b, glm::vec3 c,glm::vec3 mittelpunkt){
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

