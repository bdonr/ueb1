#include "rotationskoerper.h"
#include "meshfactory.h"
#include <glm/vec3.hpp>
#include <vector>
#include <iostream>

RotationsKoerper::RotationsKoerper(MyPolyline* poly, int refine):poly(poly), refine(refine)
{

}

RotationsKoerper::RotationsKoerper(int id, int refine):refine(refine), id(id)
{
drehe();
}

std::vector <MyPolyline*> RotationsKoerper::getPolyVec(){
    return this->polyVec;
}

void RotationsKoerper::drehe(){
    int count = 0;
float y = 0;
std::vector<glm::vec3> vect;
vect.push_back(glm::vec3(0,0,0));
vect.push_back(glm::vec3(.5,-.10,0));
vect.push_back(glm::vec3(.5,.2,0));

vect.push_back(glm::vec3(.7,.3,0));
vect.push_back(glm::vec3(.5,.4,0));
vect.push_back(glm::vec3(.0,.5,0));
vect.push_back(glm::vec3(.5,.7,0));

    for( float y = 0.0;y<360.0+360.0/refine;y=y+(360.0/refine))
    {
        std::vector<glm::vec3> matrix;
        matrix.push_back(glm::vec3(1,0,0));
        matrix.push_back(glm::vec3(0,glm::cos(glm::radians(y)),(-1)*glm::sin(glm::radians(y))));
        matrix.push_back(glm::vec3(0,glm::sin(glm::radians(y)),glm::cos(glm::radians(y))));
        std::vector<glm::vec3> vectneu;
       // std::cout<<"hallo"<<vectneu.size()<<std::endl;
        for(int i=0;i<vect.size();i++){
            std::cout<<"hallo"<<i<<vect.size()-1 <<std::endl;
            vectneu.push_back(vectorMalMatrix(vect.at(i),matrix));
        }

        polyVec.push_back(MeshFactory::createMyPolyline(vectneu));

        //polyVec.at(count)->fuelleAuf();

        //polyVec.at(count)->fuelleAuf();

    count++;
    }
}

glm::vec3 RotationsKoerper::vectorMalMatrix(glm::vec3 vector,std::vector<glm::vec3>matrix){
    glm::vec3 erg;
    erg.x= (vector.x*matrix.at(0).x)+(vector.y*matrix.at(0).y)+(vector.z*matrix.at(0).z);
    erg.y= (vector.x*matrix.at(1).x)+(vector.y*matrix.at(1).y)+(vector.z*matrix.at(1).z);
    erg.z= (vector.x*matrix.at(2).x)+(vector.y*matrix.at(2).y)+(vector.z*matrix.at(2).z);
    return erg;
}

