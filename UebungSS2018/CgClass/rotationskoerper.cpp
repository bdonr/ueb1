#include "rotationskoerper.h"
#include "meshfactory.h"
#include <glm/vec3.hpp>
#include <vector>
#include <iostream>

RotationsKoerper::RotationsKoerper(MyPolyline* poly, int refine):poly(poly), refine(refine)
{

}

RotationsKoerper::RotationsKoerper(int id, int refine,int hoehe,bool showline,bool shownormals):refine(refine),
    id(id),hoehe(hoehe),showline(showline),shownormals(shownormals)
{
    drehe();
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
            if(shownormals){
                k.push_back(normalen(a,b,c,mittelpunkt));

                std::vector<glm::vec3> m;
                glm::vec3 mittelpunkt2=mittelPunkt(d,b,c);
                this->normale.push_back(MeshFactory::createMyPolyline(glm::vec3(0,255,0),k));
                m.push_back(normalen(d,b,c,mittelpunkt2));
                this->normale.push_back(MeshFactory::createMyPolyline(glm::vec3(0,255,0),m));
            };
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

std::vector<glm::vec3> RotationsKoerper::initLines()
{
    std::vector<glm::vec3> vect;
    vect.push_back(glm::vec3(0,.0,0));
    vect.push_back(glm::vec3(.5,.25,0));
    vect.push_back(glm::vec3(1,.75,0));
    vect.push_back(glm::vec3(1.5,.0,0));

    for(unsigned int i =0;i< hoehe-1; i++){
        LaneAlgo(vect);
    }
    for(unsigned int i = 0; i < vect.size()-2;i++){
        glm::vec3 a = vect.at(i);
        glm::vec3 b = vect.at(i+1);
        std::vector<glm::vec3> ab;
        ab.push_back(a);
        ab.push_back(b);
        this->polyVec.push_back(MeshFactory::createMyPolyline(glm::vec3(255,12,12),ab));
    }
    return vect;
}

void RotationsKoerper::drehe(){
    int count = 0;
    std::vector<glm::vec3> vect = initLines();

        if(!showline){
            for( float y = 0;y<360.0+360.0/refine;y=y+(360.0/refine))
            {
                std::vector<glm::vec3> matrix;
                matrix.push_back(glm::vec3(1,0,0));
                matrix.push_back(glm::vec3(0,glm::cos(glm::radians(y)),(-1)*glm::sin(glm::radians(y))));
                matrix.push_back(glm::vec3(0,glm::sin(glm::radians(y)),glm::cos(glm::radians(y))));
                std::vector<glm::vec3> vectneu;
                for(unsigned int i=0;i<vect.size();i++){
                    vectneu.push_back(vectorMalMatrix(vect.at(i),matrix));
                }
                polyVec.push_back(MeshFactory::createMyPolyline(glm::vec3(255,0,0),vectneu));
                count++;
            }
            zieheLinieZwischenZweiNachBarSegmenten();
        }

}

//kopiere benachbarte Elemente in ein resizetes array
void RotationsKoerper::LaneAlgo(std::vector<glm::vec3>& muh){
    unsigned int ende = muh.size();
    muh.resize(ende+ende);
    unsigned int neuende = muh.size()-1;
    for(int i=ende-1;i>=0;i--){
        muh.at(neuende) = muh.at(i);
        muh.at(neuende-1)=muh.at(i);
        neuende=neuende-2;
    }
    rechne(muh);
}
void RotationsKoerper::rechne(std::vector<glm::vec3>&muh) {
    unsigned int laenge = muh.size();
    for (unsigned int i = 0; i < laenge - 2; i=i+2) {
        muh.at(i).x = (muh.at(i).x*0.75)+(muh.at(i+2).x*0.25);
        muh.at(i).y = (muh.at(i).y*0.75)+(muh.at(i+2).y*0.25);
        muh.at(i).z = (muh.at(i).z*0.75)+(muh.at(i+2).z*0.25);
        muh.at(i+1).x = (muh.at(i).x*0.25)+(muh.at(i+2).x*0.75);
        muh.at(i+1).y = (muh.at(i).y*0.25)+(muh.at(i+2).y*0.75);
        muh.at(i+1).z = (muh.at(i).z*0.25)+(muh.at(i+2).z*0.75);
    }
}





