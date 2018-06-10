#include "kugel.h"
#include <iostream>
Kugel::Kugel()
{

}

Kugel::Kugel(int id,float radius,float hoehe, int refine):id(id),type(Cg::TriangleMesh),refine(refine),hoehe(hoehe),radius(radius)
{
    create();
}

Cg::ObjectType Kugel::getType() const
{
    return type;
}

unsigned int Kugel::getID() const
{
    return id;
}

const std::vector<glm::vec3> &Kugel::getVertices() const
{
    return vertices;
}

const std::vector<glm::vec3> &Kugel::getVertexNormals() const
{
    return vertexNormals;
}

const std::vector<glm::vec3> &Kugel::getVertexColors() const
{
    return vertexColors;
}

const std::vector<glm::vec2> &Kugel::getVertexTexCoords() const
{
    return vertexTexCoords;
}

const std::vector<unsigned int> &Kugel::getTriangleIndices() const
{
    return triangleIndices;
}

const std::vector<glm::vec3> &Kugel::getFaceNormals() const
{
    return faceNormals;
}

const std::vector<glm::vec3> &Kugel::getFaceColors() const
{
    return faceColors;
}

int Kugel::create(){
     /*0*/   //vertices.push_back(glm::vec3(0,0,0));
    refine=refine*1.;

    this->vertexColors.push_back(glm::vec3(255,0,0));
    this->faceColors.push_back(glm::vec3(255,23,23));

            float ky=360.0/hoehe;
            float kx=180.0/refine;
            float y = 360.0;
            float x=180.0;

            int k=0;
            vertices.push_back(glm::vec3(0,0,0));
            vertices.push_back(glm::vec3(radius*glm::sin(glm::radians(x))*glm::cos(glm::radians(hoehe)),radius*glm::sin(glm::radians(x))*glm::sin(glm::radians(hoehe)),radius*glm::cos(glm::radians(x))));
            while(x>0){

                while(y>0){
                    y=y-ky;
                    vertices.push_back(glm::vec3(radius*glm::sin(glm::radians(x))*glm::cos(glm::radians(y)),radius*glm::sin(glm::radians(x))*glm::sin(glm::radians(y)),radius*glm::cos(glm::radians(x))));
                    //k++;
                    x=x-kx;
                    vertices.push_back(glm::vec3(radius*glm::sin(glm::radians(x))*glm::cos(glm::radians(y)),radius*glm::sin(glm::radians(x))*glm::sin(glm::radians(y)),radius*glm::cos(glm::radians(x))));
                    //k++;
                    x=x+kx;

                    if(x>0){
                        triangleIndices.push_back(vertices.size()-4);
                        triangleIndices.push_back(vertices.size()-3);
                        triangleIndices.push_back(vertices.size()-2);

                        triangleIndices.push_back(vertices.size()-2);
                        triangleIndices.push_back(vertices.size()-3);
                        triangleIndices.push_back(vertices.size()-1);
                    }
                }
                y=360.0;
                x=x-kx;
            }
}



