#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "glm/glm.hpp"
#include <string>
#include <CgClass/mats.h>
class Appearance
{

private:
    glm::vec3 color;
    glm::vec4 vierDcolor;
    glm::vec3 mats;
    std::string text;
    Mats* material;

public:
    Appearance();
    Appearance(Mats* material);
    Appearance(const std::string& text, const glm::vec3& color);
    Appearance(const std::string& text, const glm::vec4& color);

    std::string getText() const;
    void setText(const std::string &value);
    glm::vec4 getVierDcolor() const;
    void setVierDcolor(const glm::vec4 &value);

    Mats *getMaterial() const;
    void setMaterial(Mats *value);
};

#endif // APPEARANCE_H
