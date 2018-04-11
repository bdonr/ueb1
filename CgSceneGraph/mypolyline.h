#ifndef POLYLINE_H
#define POLYLINE_H
#include <CgBase/CgBasePolyline.h>
#include <CgBase/CgEnums.h>
class MyPolyline: public CgBasePolyline
{

private:
    glm::vec3 color;
unsigned int width;
std::vector<glm::vec3>* vertices;
enum Cg::ObjectType type;
const int id;
static int all_id;

public:
MyPolyline();
MyPolyline(glm::vec3 start,glm::vec3 end,glm::vec3 color);
    ~MyPolyline();
    const std::vector<glm::vec3>& getVertices() const;
    glm::vec3 getColor() const;
    unsigned int getLineWidth() const;
    Cg::ObjectType getType() const;
    unsigned int getID() const;
};

#endif // POLYLINE_H
