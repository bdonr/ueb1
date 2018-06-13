#include "appearance.h"



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



Mats *Appearance::getMaterial() const
{
    return material;
}

void Appearance::setMaterial(Mats *value)
{
    material = value;
}

Appearance::Appearance()
{
    this->material=new Mats();
}

Appearance::Appearance(Mats *material)
{
    this->material=material;
}

Appearance::Appearance(const std::string& text, const glm::vec4 &color)
{
    this->text=text;
    this->vierDcolor=color;
    this->material=new Mats();
}

Appearance::Appearance(const std::string& text,const glm::vec3& color)
{
    this->text=text;
    this->color=color;
    this->material=new Mats();
}

