#include "Mypolyline.h"
#include <iostream>

MyPolyline::~MyPolyline(){

}
MyPolyline::MyPolyline(int id,glm::vec3 color,std::vector<glm::vec3> x):id(id),type(Cg::Polyline){
    this->color=color;
    this->width=.1;

    for(int i=0;i<=x.size()-1;i++){
        vertices.push_back(x.at(i));
    }

}
 const std::vector<glm::vec3>& MyPolyline::getVertices()  const{
     return this->vertices;
 }

void MyPolyline::setVertices(std::vector<glm::vec3> x){
    this->vertices=x;
}
 glm::vec3 MyPolyline::getColor()const{
     return this->color;
 }
unsigned int MyPolyline::getLineWidth() const{
    return this->width;
}

Cg::ObjectType MyPolyline::getType() const{
    return this->type;
}


unsigned int MyPolyline::getID() const{
    return this->id;
}

void MyPolyline::setColor(const glm::vec3 x){
    this->color=x;
}

