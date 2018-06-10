#include "kamera.h"
#include "iostream"
glm::mat4 Kamera::getLookAt() const
{
    return lookAt;
}

void Kamera::setLookAt(const glm::mat4 &value)
{
    lookAt = value;
}

glm::mat4 Kamera::getProjection() const
{
    return projection;
}

void Kamera::setProjection(const glm::mat4 &value)
{
    projection = value;
}

glm::vec2 Kamera::getFenster() const
{

}

void Kamera::setFenster(const glm::vec2 &value)
{

}

glm::mat4 Kamera::perspective(float alpha, float aspect, float near, float far)
{
    return frustrum(
                -near * glm::tan(glm::radians(alpha*aspect/2)),
                near * glm::tan(glm::radians(alpha*aspect/2)),
                -near * glm::tan(glm::radians(alpha/2)),
                near * glm::tan(glm::radians(alpha/2)),near,far);
}

void Kamera::flyPLUS(float x)
{
    eye +=glm::vec3(0,0,1);
    v = glm::vec3(0,1,0);
    center +=glm::vec3(1,0,0);

    glm::vec3 f= glm::normalize(center-eye); //f
    glm::vec3 s = glm::normalize(glm::cross(f,v));
    glm::vec3 h = glm::cross(s,f);

    lookAt= glm::mat4(glm::vec4(s.x,h.x,-f.x,0),
                      glm::vec4(s.y,h.y,-f.y,0),
                      glm::vec4(s.z,h.z,f.z,0),
                      glm::vec4(-dot(s,eye),-dot(h,eye),dot(f,eye),1));
}

void Kamera::flyMINUS(float x)
{
    eye -=glm::vec3(1,0,0);
    v = glm::vec3(0,1,0);
    center +=glm::vec3(1,0,0);

    glm::vec3 f= glm::normalize(center-eye); //f
    glm::vec3 s = glm::normalize(glm::cross(f,v));
    glm::vec3 h = glm::cross(s,f);

    lookAt= glm::mat4(glm::vec4(s.x,h.x,-f.x,0),
                      glm::vec4(s.y,h.y,-f.y,0),
                      glm::vec4(s.z,h.z,f.z,0),
                      glm::vec4(-dot(s,eye),-dot(h,eye),dot(f,eye),1));
}

void Kamera::strafePLUS(float x)
{
    eye +=glm::vec3(1,0,0);

    center +=glm::vec3(1,0,0);

    glm::vec3 f= glm::normalize(center-eye); //f
    glm::vec3 s = glm::normalize(glm::cross(f,v));
    glm::vec3 h = glm::cross(s,f);

    lookAt= glm::mat4(glm::vec4(s.x,h.x,-f.x,0),
                      glm::vec4(s.y,h.y,-f.y,0),
                      glm::vec4(s.z,h.z,f.z,0),
                      glm::vec4(-dot(s,eye),-dot(h,eye),dot(f,eye),1));
}

void Kamera::strafeMINUS(float x)
{
    eye -=glm::vec3(1,0,0);
    center -=glm::vec3(1,0,0);

    glm::vec3 f= glm::normalize(center-eye); //f
    glm::vec3 s = glm::normalize(glm::cross(f,v));
    glm::vec3 h = glm::cross(s,f);

    lookAt= glm::mat4(glm::vec4(s.x,h.x,-f.x,0),
                      glm::vec4(s.y,h.y,-f.y,0),
                      glm::vec4(s.z,h.z,f.z,0),
                      glm::vec4(-dot(s,eye),-dot(h,eye),dot(f,eye),1));
}

void Kamera::towardPLUS(float x)
{
    eye +=glm::vec3(0,0,1);
    v = glm::vec3(0,1,0);
    //center +=glm::vec3(1,0,0);

    glm::vec3 f= glm::normalize(center-eye); //f
    glm::vec3 s = glm::normalize(glm::cross(f,v));
    glm::vec3 h = glm::cross(s,f);

    lookAt= glm::mat4(glm::vec4(s.x,h.x,-f.x,0),
                      glm::vec4(s.y,h.y,-f.y,0),
                      glm::vec4(s.z,h.z,f.z,0),
                      glm::vec4(-dot(s,eye),-dot(h,eye),dot(f,eye),1));
}

void Kamera::towardMINUS(float x)
{
    eye -=glm::vec3(0,0,1);
    v = glm::vec3(0,1,0);
    //center +=glm::vec3(1,0,0);

    glm::vec3 f= glm::normalize(center-eye); //f
    glm::vec3 s = glm::normalize(glm::cross(f,v));
    glm::vec3 h = glm::cross(s,f);

    lookAt= glm::mat4(glm::vec4(s.x,h.x,-f.x,0),
                      glm::vec4(s.y,h.y,-f.y,0),
                      glm::vec4(s.z,h.z,f.z,0),
                      glm::vec4(-dot(s,eye),-dot(h,eye),dot(f,eye),1));
}
void Kamera::rotatePlus(){
    countQ+=.5;
    center=glm::vec3(glm::sin(glm::radians(countQ)),0,-glm::cos(glm::radians(countQ)));
    std::cout<<center.x<<std::endl;
    //eye +=glm::vec3(0,0,1);
    v = glm::vec3(0,1,0);
    //center +=glm::vec3(1,0,0);

    glm::vec3 f= glm::normalize(center-eye); //f
    glm::vec3 s = glm::normalize(glm::cross(f,v));
    glm::vec3 h = glm::cross(s,f);

    lookAt= glm::mat4(glm::vec4(s.x,h.x,-f.x,0),
                      glm::vec4(s.y,h.y,-f.y,0),
                      glm::vec4(s.z,h.z,f.z,0),
                      glm::vec4(-dot(s,eye),-dot(h,eye),dot(f,eye),1));


}
void Kamera::rotateMinus(){
countQ-=.5;
    center=glm::vec3(glm::sin(glm::radians(countQ)),0,-glm::cos(glm::radians(countQ)));
   std::cout<<center.x<<std::endl;
    //eye +=glm::vec3(0,0,1);
    v = glm::vec3(0,1,0);
    //center +=glm::vec3(1,0,0);

    glm::vec3 f= glm::normalize(center-eye); //f
    glm::vec3 s = glm::normalize(glm::cross(f,v));
    glm::vec3 h = glm::cross(s,f);

    lookAt= glm::mat4(glm::vec4(s.x,h.x,-f.x,0),
                      glm::vec4(s.y,h.y,-f.y,0),
                      glm::vec4(s.z,h.z,f.z,0),
                      glm::vec4(-dot(s,eye),-dot(h,eye),dot(f,eye),1));


}



Kamera::Kamera()
{


    //


//    tvec3<T, P> const f(normalize(center - eye));
 //   tvec3<T, P> const s(normalize(cross(f, up)));
  //  tvec3<T, P> const u(cross(s, f));
    countQ = 0;
    eye = glm::vec3(0,0,1.0);
    v = glm::vec3(0,1,0);
    center =glm::vec3(0,0,0);

    glm::vec3 f= glm::normalize(center-eye); //f
    glm::vec3 s = glm::normalize(glm::cross(f,v));
    glm::vec3 h = glm::cross(s,f);

    lookAt= glm::mat4(glm::vec4(s.x,h.x,-f.x,0),
                      glm::vec4(s.y,h.y,-f.y,0),
                      glm::vec4(s.z,h.z,f.z,0),
                      glm::vec4(-dot(s,eye),-dot(h,eye),dot(f,eye),1));

}

glm::mat4 Kamera::frustrum(float left, float right, float bottom,float top, float near, float far)
{
    return glm::mat4(glm::vec4(((2*near)/(right-left)),0,0,0),
                     glm::vec4(0,((2*near)/(top-bottom)),0,0),
                     glm::vec4(((right+left)/(right-left)),((top+bottom)/(top-bottom)),((-1)*((far+near)/(far-near))),-1),
                     glm::vec4(0,0,((-1)*((2*far*near)/(far-near))),0));
}

glm::mat4 Kamera::calculateNew(){

    w= glm::normalize(center-eye); //f
    v= glm::normalize(glm::vec3(0,1,0)); //v = up   w=f


    glm::vec3 j = glm::cross(v,w);
    u=glm::cross(j,w);
    v=glm::normalize(glm::cross(w,u));
    u = glm::normalize(u);

    lookAt= glm::mat4(glm::vec4(u.x,v.x,w.x,0),
                      glm::vec4(u.y,v.y,w.y,0),
                      glm::vec4(u.z,v.z,w.z,0),
                      glm::vec4(-dot(u,eye),-dot(v,eye),dot(w,eye),1));
}

