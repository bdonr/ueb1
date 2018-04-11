#include "mypolyline.h"


int MyPolyline::all_id=100;

MyPolyline::~MyPolyline(){

}
MyPolyline::MyPolyline():id(++all_id),type(Cg::Polyline){};

MyPolyline::MyPolyline(glm::vec3 start,glm::vec3 end,glm::vec3 color):id(++all_id),type(Cg::Polyline){
    vertices=new std::vector<glm::vec3>;
    width=1;
    vertices->push_back(start);
    vertices->push_back(end);
    this->color=color;
}
 const std::vector<glm::vec3>& MyPolyline::getVertices()  const{
     return *this->vertices;
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




