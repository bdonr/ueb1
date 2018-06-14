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
   //Compute normals per vertex
        for(int vertice=0; vertice < m_vertices.size(); vertice++) //For every vertex
        {
            int normCounter = 0;
            int faceCounter = 0;
            glm::vec3 norm= glm::vec3(0,0,0);

            for(int indexCounter=0; indexCounter < m_triangle_indices.size() - 3; indexCounter+=3){ //Through every Face


                if(m_triangle_indices.at(indexCounter) == vertice || m_triangle_indices.at(indexCounter+1) == vertice || m_triangle_indices.at(indexCounter+2) == vertice)// Check if face includes vertex
                {
                    norm= norm + m_face_normals.at(faceCounter);
                    normCounter++;
                }

                faceCounter++;
            }

            m_vertex_normals.push_back(glm::normalize(norm / (float)normCounter));
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

