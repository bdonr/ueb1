#include "kugel.h"
#include <iostream>
Appearance *Kugel::getAppear() const
{
    return appear;
}

void Kugel::setAppear(Appearance *value)
{
    appear = value;
}
void Kugel::berechneSchwerPunkte()
{
    for(unsigned int i =0;i<triangleIndices.size();i=i+3){
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

void Kugel::berechneNormale()
{
    int d=0;
    for(unsigned int i =0;i<triangleIndices.size();i=i+3){

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

glm::vec3 Kugel::normalen(glm::vec3 a,glm::vec3 b, glm::vec3 c,glm::vec3 mittelpunkt){
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

void Kugel::punktNormalen(){
for (unsigned int i = 0 ; i<=this->vertices.size(); i++)
    {
      unsigned int number = 0;
      glm::vec3 vertexNormal;
      std::multimap<unsigned int, unsigned int>::iterator it;
      for (it=verticesOfFaces.equal_range(i).first; it!=verticesOfFaces.equal_range(i).second; ++it) {
        vertexNormal += faceNormals[(*it).second];
        number ++;
      }
      vertexNormal.x /= number;
      vertexNormal.y /= number;
      vertexNormal.z /= number;
      normals.push_back(vertexNormal);
    }
}

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

            berechneSchwerPunkte();
            berechneNormale();
            for(unsigned int i =0;i<faceNormals.size();i++){
                std::vector<glm::vec3> x;
                x.push_back(schwerpunkte.at(i));
                x.push_back(glm::normalize(faceNormals.at(i))+schwerpunkte.at(i));
                geraden.push_back(MeshFactory::createMyPolyline(glm::vec3(244,44,44),x));
            }
            for (unsigned int i = 0; i < triangleIndices.size(); i = i + 3) {
                    verticesOfFaces.insert(std::pair<unsigned int, unsigned int>(triangleIndices[i], i/3));
                    verticesOfFaces.insert(std::pair<unsigned int, unsigned int>(triangleIndices[i+1], i/3));
                    verticesOfFaces.insert(std::pair<unsigned int, unsigned int>(triangleIndices[i+2], i/3));
                }

            punktNormalen();

}



