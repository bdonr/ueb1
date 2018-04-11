#include "mybox.h"



int MyBox::all_id=1000;
MyBox::MyBox():id(++all_id)
{

    m_vertices.push_back(glm::vec3(0.1,0.1,0.1));
    m_vertices.push_back(glm::vec3(.2,0.1,0.1));
    m_vertices.push_back(glm::vec3(0.2,0.2,0.1));
    m_vertices.push_back(glm::vec3(0.1,0.2,0.1));

    m_vertices.push_back(glm::vec3(0.1,0.1,0.2));
    m_vertices.push_back(glm::vec3(.2,0.1,0.2));
    m_vertices.push_back(glm::vec3(0.2,0.2,0.2));
    m_vertices.push_back(glm::vec3(0.1,0.2,0.2));





    dreiecke.push_back(new CgExampleTriangle(m_vertices.at(0),m_vertices.at(1),m_vertices.at(3)));
   dreiecke.push_back(new CgExampleTriangle(m_vertices.at(3),m_vertices.at(2),m_vertices.at(1)));
    dreiecke.push_back(new CgExampleTriangle(m_vertices.at(1),m_vertices.at(5),m_vertices.at(2)));
    dreiecke.push_back(new CgExampleTriangle(m_vertices.at(5),m_vertices.at(6),m_vertices.at(2)));
    dreiecke.push_back(new CgExampleTriangle(m_vertices.at(7),m_vertices.at(6),m_vertices.at(5)));
    dreiecke.push_back(new CgExampleTriangle(m_vertices.at(4),m_vertices.at(5),m_vertices.at(7)));
    dreiecke.push_back(new CgExampleTriangle(m_vertices.at(3),m_vertices.at(7),m_vertices.at(4)));
    dreiecke.push_back(new CgExampleTriangle(m_vertices.at(0),m_vertices.at(4),m_vertices.at(3)));
    dreiecke.push_back(new CgExampleTriangle(m_vertices.at(3),m_vertices.at(6),m_vertices.at(7)));
    dreiecke.push_back(new CgExampleTriangle(m_vertices.at(3),m_vertices.at(2),m_vertices.at(6)));
    dreiecke.push_back(new CgExampleTriangle(m_vertices.at(0),m_vertices.at(1),m_vertices.at(5)));
    dreiecke.push_back(new CgExampleTriangle(m_vertices.at(0),m_vertices.at(5),m_vertices.at(7)));

}
MyBox::~MyBox()
{
--all_id;
};


Cg::ObjectType MyBox::getType() const{
    return this->type;
}
unsigned int MyBox::getID() const{
    return this->id;
}
std::vector<CgExampleTriangle*> MyBox::getDreiecke(){
    return this->dreiecke;
}
