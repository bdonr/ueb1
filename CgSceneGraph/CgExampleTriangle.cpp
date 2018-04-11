#include "CgExampleTriangle.h"
#include "CgBase/CgEnums.h"
#include <stdio.h>
#include <iostream>
#include "CgSceneGraph/mypolyline.h"

int CgExampleTriangle::all_id=0;

CgExampleTriangle::CgExampleTriangle():
m_type(Cg::TriangleMesh),
m_id(++all_id)
{


    m_vertices.push_back(glm::vec3(.1,0,0));
    m_vertices.push_back(glm::vec3(0.0,0.1,0.0));
    m_vertices.push_back(glm::vec3(0.0,0,0.1));


    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);

    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));

    this->mittelpunkt=this->rechneMittelpunkt();

    this->poly = new MyPolyline(getVertices().at(0),glm::vec3(1,1,1),glm::vec3(255,0,0));

}

CgExampleTriangle::CgExampleTriangle(int id):
m_type(Cg::TriangleMesh),
m_id(++all_id)
{


    m_vertex_colors.push_back(glm::vec3(0,0,255));
    m_face_colors.push_back(glm::vec3(255,0,255));
    m_vertices.push_back(glm::vec3(-0.5,0.0,0.0));
    m_vertices.push_back(glm::vec3(0.0,-0.5,0.0));
    m_vertices.push_back(glm::vec3(0.0,0.5,0.0));
    m_vertices.push_back(glm::vec3(0.5,0.0,0.0));


    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(3);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(3);

    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));

}
CgExampleTriangle::CgExampleTriangle(glm::vec3 a,glm::vec3 b,glm::vec3 c):m_type(Cg::TriangleMesh),
m_id(++all_id){
    m_vertices.push_back(a);
    std::cout<<"sas"<<m_vertices.at(0).x;
    m_vertices.push_back(b);
    m_vertices.push_back(c);
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);


    this->mittelpunkt=this->rechneMittelpunkt();

    this->poly = new MyPolyline(mittelpunkt,berechneNormale(),glm::vec3(255,0,0));
}

CgExampleTriangle::CgExampleTriangle(int id,bool v):
m_type(Cg::TriangleMesh),
m_id(++all_id)
{

    m_vertices.push_back(glm::vec3(0,0,0));
    m_vertices.push_back(glm::vec3(.9,0,0.0));
    m_vertices.push_back(glm::vec3(0.9,0.9,0));
    m_vertices.push_back(glm::vec3(0.0,0.9,0.0));

    m_vertices.push_back(glm::vec3(0,0,0.1));
    m_vertices.push_back(glm::vec3(.1,0.0,0.1));
    m_vertices.push_back(glm::vec3(0.1,0.1,0.1));
    m_vertices.push_back(glm::vec3(0.0,0.1,0.1));



/*
    m_vertices.push_back(glm::vec3(0.2,0.2,0));
    m_vertices.push_back(glm::vec3(.3,0.2,0));
    m_vertices.push_back(glm::vec3(0.3,0.3,0));
    m_vertices.push_back(glm::vec3(0.2,0.3,0));
*/
/*before niko das vergeigt
    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(1);
    m_triangle_indices.push_back(2);

    m_triangle_indices.push_back(0);
    m_triangle_indices.push_back(2);
    m_triangle_indices.push_back(3);


    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(6);

    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(6);
    m_triangle_indices.push_back(7);
//start
    m_triangle_indices.push_back(4);
    m_triangle_indices.push_back(5);
    m_triangle_indices.push_back(6);
*/

    m_triangle_indices.push_back(0);
m_triangle_indices.push_back(1);
m_triangle_indices.push_back(3);



m_triangle_indices.push_back(3);
m_triangle_indices.push_back(2);
m_triangle_indices.push_back(1);


m_triangle_indices.push_back(1);
m_triangle_indices.push_back(5);
m_triangle_indices.push_back(2);


m_triangle_indices.push_back(5);
m_triangle_indices.push_back(6);
m_triangle_indices.push_back(2);



m_triangle_indices.push_back(7);
m_triangle_indices.push_back(6);
m_triangle_indices.push_back(5);



m_triangle_indices.push_back(4);
m_triangle_indices.push_back(5);
m_triangle_indices.push_back(7);


m_triangle_indices.push_back(3);
m_triangle_indices.push_back(7);
m_triangle_indices.push_back(4);


m_triangle_indices.push_back(0);
m_triangle_indices.push_back(4);
m_triangle_indices.push_back(3);


m_triangle_indices.push_back(3);
m_triangle_indices.push_back(6);
m_triangle_indices.push_back(7);



m_triangle_indices.push_back(3);
m_triangle_indices.push_back(2);
m_triangle_indices.push_back(6);


m_triangle_indices.push_back(0);
m_triangle_indices.push_back(1);
m_triangle_indices.push_back(5);


m_triangle_indices.push_back(0);
m_triangle_indices.push_back(5);
m_triangle_indices.push_back(7);

    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));
    m_vertex_normals.push_back(glm::vec3(0.0,0.0,1.0));

}

CgExampleTriangle::~CgExampleTriangle()
{
    m_vertices.clear();
    delete poly;
    m_vertex_normals.clear();
    m_vertex_colors.clear();
    m_tex_coords.clear();
    m_triangle_indices.clear();
    m_face_normals.clear();
    m_face_colors.clear();

}


const std::vector<glm::vec3>& CgExampleTriangle::getVertices() const
{
    return m_vertices;
}

const std::vector<glm::vec3>& CgExampleTriangle::getVertexNormals() const
{
    return m_vertex_normals;
}

const std::vector<glm::vec3>& CgExampleTriangle::getVertexColors() const
{
     return m_vertex_colors;
}

const std::vector<glm::vec2>& CgExampleTriangle:: getVertexTexCoords() const
{
    return m_tex_coords;
}

const std::vector<unsigned int>& CgExampleTriangle::getTriangleIndices() const
{
    return m_triangle_indices;
}

const std::vector<glm::vec3>& CgExampleTriangle::getFaceNormals() const
{
    return m_face_normals;
}

const std::vector<glm::vec3>& CgExampleTriangle::getFaceColors() const
{
    return m_face_colors;
}

     MyPolyline* CgExampleTriangle::getPoly() const{
        return this->poly;
    }


    const glm::vec3& CgExampleTriangle::getMittelpunkt() const{
        return this->mittelpunkt;
    }
glm::vec3 CgExampleTriangle::rechneMittelpunkt(){
    glm::vec3 k = (getVertices().at(0)+ getVertices().at(1)+getVertices().at(2));

    k.x = k.x/3;
    k.y=  k.y/3;
    k.z=  k.z/3;
    this->mittelpunkt=k;
    return k;
}

glm::vec3 CgExampleTriangle::berechneNormale(){
    glm::vec3 k;
    glm::vec3 a = this->getVertices().at(0);
    glm::vec3 b = this->getVertices().at(1);
    glm::vec3 c = this->getVertices().at(2);
std::cout<< "x" <<a.x<< "y"<< a.y<<"z"<< a.z<<std::endl;
std::cout<< "x" <<b.x<< "y"<< b.y<<"z"<< b.z<<std::endl;
std::cout<< "x" <<c.x<< "y"<< c.y<<"z"<< c.z<<std::endl;

    glm::vec3 vab = b-a;
    glm::vec3 vac = c-a;

    k.x = vab.y*vac.z - vac.y*vab.z;
    k.y = vab.z*vac.x - vac.z*vab.x;
    k.z = vab.x*vac.y - vac.x*vab.y;
    if(k.z<0)k.z=(-1)*k.z;
    if(k.y<0)k.y=(-1)*k.y;
    if(k.x<0)k.x=(-1)*k.x;
    std::cout<< "kx" <<k.x<< "ky"<< k.y<<"kz"<< k.z<<std::endl;


    this->normale=k+mittelpunkt;
    return this->normale;
}
