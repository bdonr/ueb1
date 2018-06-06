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
    erstelleKugel();
}

std::vector <MyPolyline*> RotationsKoerper::getPolyVec(){
    return this->polyVec;
}

std::vector <MyPolyline*> RotationsKoerper::getKeisVec(){
    return this->kreisVec;
}
std::vector<MyPolyline*> RotationsKoerper::getNormale(){
    return this->normale;
}

void RotationsKoerper::erstelleKugel(){
    int count = 0;
    float y = 0;


    std::vector<glm::vec3> vect;
    std::vector<glm::vec3> matrix;


    for(float i=0.0; i<=180.;i=i+20.){
        std::cout<<i<<std::endl;
        // std::cout<<"hallo"<<vectneu.size()<<std::endl;
            vect.push_back(glm::vec3(glm::sin(glm::radians(i)),glm::cos(glm::radians(i)),0));
        //    std::cout<<glm::cos(i)<<","<<glm::sin(i)<<"i"<<i<<std::endl;
            //vectneu.at(i)->fuelleAuf();
    }

    for( float y = 0.0;y<360.0+360.0/refine;y=y+(360.0/refine))
    {
        std::vector<glm::vec3> matrix;
        matrix.push_back(glm::vec3(glm::cos(glm::radians(y)),0,glm::sin(glm::radians(y))));
        matrix.push_back(glm::vec3(0,1,0));
        matrix.push_back(glm::vec3((-1)*glm::sin(glm::radians(y)),0,glm::cos(glm::radians(y))));
        std::vector<glm::vec3> vectneu;
        // std::cout<<"hallo"<<vectneu.size()<<std::endl;
        for(int i=0;i<vect.size();i++){
            vectneu.push_back(vectorMalMatrix(vect.at(i),matrix));
            
            //vectneu.at(i)->fuelleAuf();

        }

        polyVec.push_back(MeshFactory::createMyPolyline(glm::vec3(255,0,0),vectneu));

        // polyVec.at(count)->fuelleAuf();
        // polyVec.at(count)->fuelleAuf();

        count++;
    }
    zieheLinieZwischenZweiNachBarSegmenten();

}

void RotationsKoerper::erstelleRotationsKoerper(){

}

glm::vec3 RotationsKoerper::vectorMalMatrix(glm::vec3 vector,std::vector<glm::vec3>matrix){
    glm::vec3 erg;
    erg.x= (vector.x*matrix.at(0).x)+(vector.y*matrix.at(0).y)+(vector.z*matrix.at(0).z);
    erg.y= (vector.x*matrix.at(1).x)+(vector.y*matrix.at(1).y)+(vector.z*matrix.at(1).z);
    erg.z= (vector.x*matrix.at(2).x)+(vector.y*matrix.at(2).y)+(vector.z*matrix.at(2).z);
    return erg;
}

void RotationsKoerper::zieheLinieZwischenZweiNachBarSegmenten(){
    //-2 da wir am ende nicht doppelt haben wollen
    for(int i=0;i<=this->polyVec.size()-2;i++){
        for(int j=0;j<this->polyVec.at(i)->getVertices().size()-1;j++){
            std::vector<glm::vec3> x;
            std::vector<glm::vec3> y;
            glm::vec3 a=polyVec.at(i)->getVertices().at(j);
            glm::vec3 b=polyVec.at(i+1)->getVertices().at(j);
            glm::vec3 c=polyVec.at(i+1)->getVertices().at(j+1);
            glm::vec3 d=polyVec.at(i+1)->getVertices().at(j+1);
            x.push_back(a);
            x.push_back(b);
            this->kreisVec.push_back(MeshFactory::createMyPolyline(glm::vec3(255,0,255),x));
            y.push_back(a);
            y.push_back(c);
            this->kreisVec.push_back(MeshFactory::createMyPolyline(glm::vec3(255,0,255),y));
            std::vector<glm::vec3> k;
            glm::vec3 mittelpunkt=mittelPunkt(a,b,c);
            k.push_back(mittelpunkt);
            k.push_back(normalen(a,b,c,mittelpunkt));

            std::vector<glm::vec3> m;
            glm::vec3 mittelpunkt2=mittelPunkt(d,b,c);
            this->normale.push_back(MeshFactory::createMyPolyline(glm::vec3(0,255,0),k));
            m.push_back(normalen(d,b,c,mittelpunkt2));
            this->normale.push_back(MeshFactory::createMyPolyline(glm::vec3(0,255,0),m));
        }
    }
}

glm::vec3 RotationsKoerper::mittelPunkt(glm::vec3 a,glm::vec3 b, glm::vec3 c){
    glm::vec3 mittelPunkt;
    mittelPunkt= a+b+c;

    mittelPunkt.x = mittelPunkt.x/3;
    mittelPunkt.y = mittelPunkt.y/3;
    mittelPunkt.z = mittelPunkt.z/3;
    return mittelPunkt;
}

glm::vec3 RotationsKoerper::normalen(glm::vec3 a,glm::vec3 b, glm::vec3 c,glm::vec3 mittelpunkt){
    glm::vec3 k;

    glm::vec3 vab = b-a;
    glm::vec3 vac = c-a;

    k.x = vab.y*vac.z - vac.y*vab.z;
    k.y = vab.z*vac.x - vac.z*vab.x;
    k.z = vab.x*vac.y - vac.x*vab.y;

    k.x=k.x+mittelpunkt.x;
    k.y=k.y+mittelpunkt.y;
    k.z=k.z+mittelpunkt.z;
    return k;
}




