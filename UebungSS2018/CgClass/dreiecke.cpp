#include "dreiecke.h"

std::vector<MyPolyline *> Dreiecke::getGeraden() const
{
    return geraden;
}

void Dreiecke::setGeraden(const std::vector<MyPolyline *> &value)
{
    geraden = value;
}

Dreiecke::Dreiecke(): type(Cg::TriangleMesh)
{

}

Dreiecke::Dreiecke(int id,std::vector<glm::vec3>vertices,std::vector<unsigned int> indexes):id(id),indeces(indexes),
    type(Cg::TriangleMesh),
    vetices(vertices)
{
    this->vcolor.push_back(glm::vec3(255,0,0));
    this->fcolor.push_back(glm::vec3(0,255,0));
    berechnePunktNormale();
}

enum Cg::ObjectType Dreiecke::getType() const{
    return type;
}
//Laufzeit O(n*k)
bool Dreiecke::berechnePunktNormale(){
    for(unsigned int i =0;i<indeces.size();i++){
        glm::vec3 p = vetices.at(indeces.at(i));
        std::vector<glm::vec3> gerade;
        glm::vec3 normalen;
        for(int j=i;j<indeces.size()-3;j=j+3){
            int count =0;

            //wenn punkt nicht mehr im nächsten triangle vorkommt reset
            if(!equal(p,vetices.at(indeces.at(j)))&&
                    !equal(p,vetices.at(indeces.at(j+1))) &&
                    !equal(p,vetices.at(indeces.at(j+2)))){
                if(count>0){

                    glm::vec3 o = glm::vec3(normalen.x/count,normalen.y/count,normalen.z/count);
                    gerade.push_back(p);
                    gerade.push_back(o);
                    geraden.push_back(MeshFactory::createMyPolyline(glm::vec3(121,121,121),gerade));
                    this->pointnormals.push_back(o);
                    gerade.clear();
                    j=vetices.size();
                }
                else{
                    normalen+=normalenV(vetices.at(indeces.at(j)),vetices.at(indeces.at(j+1)),vetices.at(indeces.at(j+2)),
                                        berechneSchwerPunkte(vetices.at(indeces.at(j)),vetices.at(indeces.at(j+1)),vetices.at(indeces.at(j+2))));
                    count++;
                }
            }
        }
    }
}

glm::vec3 Dreiecke::berechneSchwerPunkte(glm::vec3 a, glm::vec3 b, glm::vec3 c){
    glm::vec3 l= (a+b+c);
    glm::vec3 k =glm::vec3(l.x/3,l.y/3,l.z/3);
    return k;

}

bool Dreiecke::equal(glm::vec3 a , glm::vec3 b){
    return equalDouble(a.x,b.x) && equalDouble(a.y,b.y) && equalDouble(a.z,b.z);
}

bool Dreiecke::equalDouble(double x , double y){
    if (x==y) return true;
    return glm::abs(y - x) <= 0.0000001;
}



unsigned int Dreiecke::getID() const{
    return id;
}

const std::vector<glm::vec3> & Dreiecke::getVertices() const{
    return vetices;
}
const std::vector<glm::vec3> & Dreiecke::getVertexNormals() const{
    return vernormals;
}
const std::vector<glm::vec3> & Dreiecke::getVertexColors() const{
    return vcolor;
}
const std::vector<glm::vec2> & Dreiecke::getVertexTexCoords() const{
    return triangletextcoords;
}
const std::vector<unsigned int> & Dreiecke::getTriangleIndices() const{
    return indeces;
}
const std::vector<glm::vec3> & Dreiecke::getFaceNormals() const{
    return facenormals;
}
const std::vector<glm::vec3> & Dreiecke::getFaceColors() const{
    return fcolor;
}

glm::vec3 Dreiecke::normalenV(glm::vec3 a,glm::vec3 b, glm::vec3 c,glm::vec3 mittelpunkt){
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

