#ifndef MYBOX_H
#define MYBOX_H

#include <CgBase/CgBaseRenderableObject.h>
#include <CgSceneGraph/CgExampleTriangle.h>
class MyBox : public CgBaseRenderableObject
{

private:
    std::vector<glm::vec3> m_vertices;
    std::vector<CgExampleTriangle*> dreiecke;
    static int all_id;
    int id;
    enum Cg::ObjectType type;
public:
    MyBox();
    ~MyBox();
    std::vector<CgExampleTriangle*> getDreiecke();

    Cg::ObjectType getType() const;
    unsigned int getID() const;

};

#endif // MYBOX_H
