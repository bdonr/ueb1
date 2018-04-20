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

void MyPolyline::fuelleAuf(){
    int mitte = this->vertices.size() / 2;
    int ende = this->vertices.size();
    std::cout << ende << "," << mitte << std::endl;
    //unterscheide grade und ungerade anzahl
    if (this->vertices.size() % 2 == 0) {
        //hänge an altes array doppelte ab mitte an
        for (int i = mitte; i < ende; i++) {
            std::cout << "-------" << std::endl;
            this->vertices.push_back(this->vertices.at(i));
            this->vertices.push_back(this->vertices.at(i));
        }

        //hänge an altes array doppelte ab mitte an
        int div = 1;
        for (int i = 1; i < ende; i = i + 2) {
            this->vertices.at(ende - i) = this->vertices.at(mitte - div);
            this->vertices.at(ende - i - 1) = this->vertices.at(mitte - div);
            div++;
        }
    } else {

        //hänge an altes array doppelte ab mitte an
        this->vertices.push_back(this->vertices.at(mitte));
        for (int i = mitte + 1; i < ende; i++) {
            std::cout << "-------" << std::endl;
            this->vertices.push_back(this->vertices.at(i));
            this->vertices.push_back(this->vertices.at(i));

        }
        // von mitte aus nach links alle doppel eintragen
        this->vertices.at(ende - 1) = this->vertices.at(mitte);
        int div = 1;
        for (int i = 2; i < ende - 1; i = i + 2) {
            this->vertices.at(ende - i) = this->vertices.at(mitte - div);
            this->vertices.at(ende - i - 1) = this->vertices.at(mitte - div);
            std::cout<<"er geht da nicht rein!"<<std::endl;
            div++;
        }

        this->vertices.at(1) = this->vertices.at(0);
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


