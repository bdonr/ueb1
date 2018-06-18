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

    berechneSchwerPunkte();
    berechneNormale();
    for (unsigned int i = 0; i < indeces.size(); i = i + 3) {
            verticesOfFaces.insert(std::pair<unsigned int, unsigned int>(indeces[i], i/3));
            verticesOfFaces.insert(std::pair<unsigned int, unsigned int>(indeces[i+1], i/3));
            verticesOfFaces.insert(std::pair<unsigned int, unsigned int>(indeces[i+2], i/3));
        }

    punktNormalen();
    for(int i =0;i<vertices.size();i++){
        std::vector<glm::vec3> l;
        l.push_back(vertices.at(i));
        l.push_back(normals.at(i));
        geraden.push_back(MeshFactory::createMyPolyline(glm::vec3(1,1,1),l));
    }
    //berechnePunktNormale();
}

enum Cg::ObjectType Dreiecke::getType() const{
    return type;
}
//Laufzeit O(n*k)
bool Dreiecke::berechnePunktNormale(){
   //Compute normals per vertex
        for(unsigned int i=0; i < vetices.size(); i++) //For every vertex
        {
            int normCounter = 0;
            int faceCounter = 0;
            glm::vec3 norm= glm::vec3(0,0,0);

            for(unsigned int indexCounter=0; indexCounter < indeces.size() - 3; indexCounter+=3){ //Through every Face
                if(indeces.at(indexCounter) == i || indeces.at(indexCounter+1) == i || indeces.at(indexCounter+2) == i)// Check if face includes vertex
                {
                    norm= norm + facenormals.at(faceCounter);
                    normCounter++;
                }
                faceCounter++;
            }

            this->normals.push_back(glm::normalize(norm / (float)normCounter));
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

void Dreiecke::punktNormalen(){
for (unsigned int i = 0 ; i<=this->vetices.size(); i++)
    {
      unsigned int number = 0;
      glm::vec3 vertexNormal;
      std::multimap<unsigned int, unsigned int>::iterator it;
      for (it=verticesOfFaces.equal_range(i).first; it!=verticesOfFaces.equal_range(i).second; ++it) {
        vertexNormal += facenormals[(*it).second];
        number ++;
      }
      vertexNormal.x /= number;
      vertexNormal.y /= number;
      vertexNormal.z /= number;
      normals.push_back(vertexNormal);
    }
}



void Dreiecke::berechneSchwerPunkte()
{
    for(unsigned int i =0;i<indeces.size();i=i+3){
        if(indeces.at(i)<vetices.size()
                && indeces.at(i+1)<vetices.size()
                && indeces.at(i+2)<vetices.size()){
            glm::vec3 l= (vetices.at(indeces.at(i))+
                          vetices.at(indeces.at(i+1))+
                          vetices.at(indeces.at(i+2)));
            glm::vec3 k =glm::vec3(l.x/3,l.y/3,l.z/3);
            schwerpunkte.push_back(k);
        }

    }

}
/**
 * @brief Zylinder::berechneNormale
 * berechne die Normale mit Hilfe der Schwerpunkte
 *
 **/
void Dreiecke::berechneNormale()
{
    int d=0;
    for(unsigned int i =0;i<indeces.size();i=i+3){

        if(indeces.at(i+2)<vetices.size()
                && indeces.at(i)<vetices.size()
                && indeces.at(i+1)<vetices.size()){
            facenormals.push_back(normalen(vetices.at(indeces.at(i)),
                                           vetices.at(indeces.at(i+1)),
                                           vetices.at(indeces.at(i+2)),schwerpunkte.at(d)));
            d++;
        }
    }
}
/**
 * @brief Zylinder::normalen
 * @param a
 * @param b
 * @param c
 * @param mittelpunkt
 * @return
 * Hilfefunktion zur berechnung der Normalen
 **/
glm::vec3 Dreiecke::normalen(glm::vec3 a,glm::vec3 b, glm::vec3 c,glm::vec3 mittelpunkt){

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
