#ifndef APPEARANCE_H
#define APPEARANCE_H

#include "glm/glm.hpp"
#include <string>
class Appearance
{

private:
    glm::vec3 color;
    glm::vec4 vierDcolor;
    glm::vec3 mats;
    std::string text;

public:
    Appearance();
    Appearance(const std::string& text, const glm::vec3& color);
    Appearance(const std::string& text, const glm::vec4& color);
    glm::vec3 getMats() const;
    void setMats(const glm::vec3 &value);
    glm::vec3 getColor() const;
    void setColor(const glm::vec3 &value);
    std::string getText() const;
    void setText(const std::string &value);
    glm::vec4 getVierDcolor() const;
    void setVierDcolor(const glm::vec4 &value);
};

#endif // APPEARANCE_H
