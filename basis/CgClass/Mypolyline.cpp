#include "Mypolyline.h"
#include <iostream>

MyPolyline::~MyPolyline(){

}
MyPolyline::MyPolyline(int id,glm::vec3 color,std::vector<glm::vec3> x):id(id),type(Cg::Polyline){
    this->color=color;
    this->width=.1;
    this->vertices=x;

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

void MyPolyline::LaneAlgo(){
    int mitte = this->vertices.size() / 2;
    int ende = this->vertices.size();
    this->vertices.resize(ende+ende);
    int neuende = this->vertices.size()-1;
    for(int i=ende-1;i>=0;i--){
        this->vertices.at(neuende) = this->vertices.at(i);
        this->vertices.at(neuende-1)=this->vertices.at(i);
        neuende=neuende-2;
    }
    rechne();

}

void MyPolyline::rechne() {
    int laenge = this->vertices.size();
    for (int i = 0; i < laenge - 2; i=i+2) {
        this->vertices.at(i).x = (this->vertices.at(i).x*0.75)+(this->vertices.at(i+2).x*0.25);
        this->vertices.at(i).y = (this->vertices.at(i).y*0.75)+(this->vertices.at(i+2).y*0.25);
        this->vertices.at(i).z = (this->vertices.at(i).z*0.75)+(this->vertices.at(i+2).z*0.25);
        this->vertices.at(i+1).x = (this->vertices.at(i).x*0.25)+(this->vertices.at(i+2).x*0.75);
        this->vertices.at(i+1).y = (this->vertices.at(i).y*0.25)+(this->vertices.at(i+2).y*0.75);
        this->vertices.at(i+1).z = (this->vertices.at(i).z*0.25)+(this->vertices.at(i+2).z*0.75);
    }
}

void MyPolyline::rechneVierPunkteSchema(){
    int mitte = this->vertices.size() / 2;
    int ende = this->vertices.size();
    float w = .0625;
//    std::cout<<"mitte"<<mitte<<"ende"<<ende<<std::endl;
    this->vertices.resize(ende+ende);
    std::cout<<this->vertices.size()<<std::endl;
    int neuende = this->vertices.size()-1;
    for(int i =ende-2; i>=4;i--){
        std::cout<<"i"<<i<<"i*2+1"<<i*2+1<<vertices.at((2*i)+1).x<<std::endl;
        std::cout<<"y"<<vertices.at((2*i)+1).y<<std::endl;
        if(((i*2)+4)>=neuende){
            this->vertices.at((2*i)+1).x = (w*(-1.)*(this->vertices.at(2*i).x))+((.5+w)*this->vertices.at((2*i)-2).x)+((.5+w)*(this->vertices.at((2*i)+2).x))+((-1.)*w*vertices.at((2*i)+4).x);
              this->vertices.at((2*i)+1).y = (w*(-1.)*(this->vertices.at(2*i).y))+((.5+w)*this->vertices.at((2*i)-2).y)+((.5+w)*(this->vertices.at((2*i)+2).y))+((-1.)*w*vertices.at((2*i)+4).y);
              this->vertices.at((2*i)+1).z = (w*(-1.)*(this->vertices.at(2*i).z))+((.5+w)*this->vertices.at((2*i)-2).z)+((.5+w)*(this->vertices.at((2*i)+2).z))+((-1.)*w*vertices.at((2*i)+4).z);
        }
        else{
      this->vertices.at((2*i)+1).x = (w*(-1.)*(this->vertices.at(2*i).x))+((.5+w)*this->vertices.at((2*i)-2).x)+((.5+w)*(this->vertices.at((2*i)+2).x))+((-1.)*w*vertices.at((2*i)-4).x);
        this->vertices.at((2*i)+1).y = (w*(-1.)*(this->vertices.at(2*i).y))+((.5+w)*this->vertices.at((2*i)-2).y)+((.5+w)*(this->vertices.at((2*i)+2).y))+((-1.)*w*vertices.at((2*i)-4).y);
        this->vertices.at((2*i)+1).z = (w*(-1.)*(this->vertices.at(2*i).z))+((.5+w)*this->vertices.at((2*i)-2).z)+((.5+w)*(this->vertices.at((2*i)+2).z))+((-1.)*w*vertices.at((2*i)-4).z);

        }std::cout<<"x"<<vertices.at((2*i)+1).x<<std::endl;
        std::cout<<"y"<<vertices.at((2*i)+1).y<<std::endl;
        std::cout<<(2*i)+4<<std::endl;
    }

}


