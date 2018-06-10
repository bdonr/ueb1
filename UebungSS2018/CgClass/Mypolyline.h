#ifndef MYPOLYLINE_H
#define MYPOLYLINE_H
#include <CgBase/CgBasePolyline.h>
#include "CgBase/CgBasePolyline.h"
#include "CgBase/CgEnums.h"

class MyPolyline : public CgBasePolyline
{
private:
    glm::vec3 color;
    enum Cg::ObjectType type;
    unsigned int id;
    unsigned int width;
    std::vector<glm::vec3> vertices;
public:
    MyPolyline(unsigned int id,glm::vec3 color,std::vector<glm::vec3> x);

    Cg::ObjectType getType() const;
    unsigned int getID() const;
    void setVertices(std::vector<glm::vec3> x);
    void setColor(const glm::vec3 x);

    // CgBasePolyline interface
    const std::vector<glm::vec3>& getVertices() const;
    glm::vec3 getColor() const;
    unsigned int getLineWidth() const;
    void rechne();
    void LaneAlgo();

    void rechneVierPunkteSchema();

    MyPolyline();
    ~MyPolyline();

};

#endif // MYPOLYLINE_H
