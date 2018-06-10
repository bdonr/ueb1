#include "appearance.h"

glm::vec3 Appearance::getMats() const
{
    return mats;
}

void Appearance::setMats(const glm::vec3 &value)
{
    mats = value;
}

glm::vec3 Appearance::getColor() const
{
    return color;
}

void Appearance::setColor(const glm::vec3 &value)
{
    color = value;
}

std::string Appearance::getText() const
{
    return text;
}

void Appearance::setText(const std::string &value)
{
    text = value;
}

glm::vec4 Appearance::getVierDcolor() const
{
    return vierDcolor;
}

void Appearance::setVierDcolor(const glm::vec4 &value)
{
    vierDcolor = value;
}

Appearance::Appearance()
{

}

Appearance::Appearance(const std::string& text, const glm::vec4 &color)
{
    this->text=text;
    this->vierDcolor=color;
}

Appearance::Appearance(const std::string& text,const glm::vec3& color)
{
    this->text=text;
    this->color=color;
}

