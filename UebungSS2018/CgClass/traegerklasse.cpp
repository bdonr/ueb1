#include "traegerklasse.h"




glm::vec3 TraegerKlasse::getIntvec() const
{
    return intvec;
}

void TraegerKlasse::setIntvec(const glm::vec3 &value)
{
    intvec = value;
}

int TraegerKlasse::getTab() const
{
    return tab;
}

void TraegerKlasse::setTab(int value)
{
    tab = value;
}

std::vector<int> TraegerKlasse::getX() const
{
    return x;
}

glm::vec3 TraegerKlasse::getDreiDVector() const
{
    return dreiDVector;
}

void TraegerKlasse::setDreiDVector(const glm::vec3 &value)
{
    dreiDVector = value;
}

int TraegerKlasse::getAn_aus() const
{
    return an_aus;
}

void TraegerKlasse::setAn_aus(int value)
{
    an_aus = value;
}



glm::vec4 TraegerKlasse::getDef() const
{
    return def;
}

void TraegerKlasse::setDef(const glm::vec4 &value)
{
    def = value;
}

glm::vec4 TraegerKlasse::getSpec() const
{
    return spec;
}

void TraegerKlasse::setSpec(const glm::vec4 &value)
{
    spec = value;
}

double TraegerKlasse::getScala() const
{
    return scala;
}

void TraegerKlasse::setScala(double value)
{
    scala = value;
}

glm::vec4 TraegerKlasse::getAmb() const
{
    return amb;
}

void TraegerKlasse::setAmb(const glm::vec4 &value)
{
    amb = value;
}

QString TraegerKlasse::getName() const
{
    return name;
}

void TraegerKlasse::setName(const QString &value)
{
    name = value;
}

int TraegerKlasse::getShading() const
{
    return shading;
}

void TraegerKlasse::setShading(int value)
{
    shading = value;
}

int TraegerKlasse::getInterpol() const
{
    return interpol;
}

void TraegerKlasse::setInterpol(int value)
{
    interpol = value;
}

TraegerKlasse::TraegerKlasse()
{
    intvec=glm::vec3(0,0,0);
}

TraegerKlasse::TraegerKlasse(std::vector<int> k)
{
    this->x=k;
}

TraegerKlasse::TraegerKlasse(glm::vec3 dreiDVector)
{
    this->dreiDVector= dreiDVector;
}

void TraegerKlasse::setX(int x)
{
    intvec.x=x;
}

void TraegerKlasse::setY(int y)
{
    intvec.y=y;
}

void TraegerKlasse::setZ(int z)
{
    intvec.z=z;
}

