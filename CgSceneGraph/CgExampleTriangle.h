#ifndef CGEXAMPLETRIANGLE_H
#define CGEXAMPLETRIANGLE_H

#include <vector>
#include <glm/glm.hpp>

#include "CgBase/CgBaseTriangleMesh.h"
#include"mypolyline.h"

class CgExampleTriangle : public CgBaseTriangleMesh
{

public:
    CgExampleTriangle();
    CgExampleTriangle(glm::vec3 a,glm::vec3 b, glm::vec3 c);
    CgExampleTriangle(int id);
    CgExampleTriangle(int id,bool v);

    ~CgExampleTriangle();

    //inherited from CgBaseRenderableObject
    Cg::ObjectType getType() const;
    unsigned int getID() const;

    //inherited from CgBaseTriangleMesh
    const std::vector<glm::vec3>& getVertices() const;
    const std::vector<glm::vec3>& getVertexNormals() const;
    const std::vector<glm::vec3>& getVertexColors() const;
   const std::vector<glm::vec2>& getVertexTexCoords() const;
    MyPolyline* getPoly() const;
    const std::vector<unsigned int>& getTriangleIndices() const;

    const std::vector<glm::vec3>& getFaceNormals() const;
    const std::vector<glm::vec3>& getFaceColors() const;
    const glm::vec3& getMittelpunkt() const;

    glm::vec3 mittelpunkt;
    glm::vec3 berechneNormale();


private:
    glm::vec3 rechneMittelpunkt();
    glm::vec3 normale;
    MyPolyline* poly;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec3> m_vertex_normals;
    std::vector<glm::vec3> m_vertex_colors;
    std::vector<glm::vec2> m_tex_coords;

    std::vector<unsigned int>  m_triangle_indices;

    std::vector<glm::vec3> m_face_normals;
    std::vector<glm::vec3> m_face_colors;

    const Cg::ObjectType m_type;
    const unsigned int m_id;
    static int all_id;


};


inline Cg::ObjectType  CgExampleTriangle::getType() const {return m_type;}
inline unsigned int CgExampleTriangle::getID() const {return m_id;}

#endif // CGEXAMPLETRIANGLE_H
