#include "CgCamera.h"
#include <iostream>


CgCamera::CgCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, int windowHeight, int windowWidth)
{
    this->eye = eye;
    this->center = center;
    this->up = up;
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;
}

//@author Gerrit Harmes
glm::mat4x4 CgCamera::getProjectionMatrix()
{

    float n, f, r, l, t, b;

    r = windowWidth / 2;
    l = -r;
    t = windowHeight;
    b = -t;
    n = 0.5;
    f = 1;


    glm::mat4x4 result = glm::mat4x4(glm::vec4( (2*n)/(r-l) , 0 , (r+l)/(r-l) , 0 ),
                                     glm::vec4( 0 , (2*n)/(t-b) , (t+b)/(t-b) , 0 ),
                                     glm::vec4( 0 , 0 , -(f+n)/(f-n) , -(2*f*n)/(f-n) ),
                                     glm::vec4( 0 , 0 , -1 , 0 ));



    std::cout << "Debugging (wird aktuell nicht verwendet >CgCamera.cpp 35<): Projektionsmatrix:" << std::endl;
    print4x4Matrix(result);

    //return result;


    //m_proj_matrix=glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f); //????

    return glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
}


//@author Gerrit Harmes
glm::mat4x4 CgCamera::getLookAtMatrix()
{
    bool debug = false;

    if(debug){
        std::cout << "eye: " << eye.x << " " << eye.y << " " << eye.z << std::endl;
        std::cout << "center: " << center.x << " " << center.y << " " << center.z << std::endl;
        std::cout << "up: " << up.x << " " << up.y << " " << up.z << std::endl;
    }

    glm::vec3 w = center - eye;
    glm::normalize(w);
    glm::vec3 v = up;
    glm::vec3 u = glm::cross(v,w);
              v = glm::cross(w,u);
    glm::normalize(u);
    glm::normalize(v);

    glm::mat4x4 result = glm::mat4x4(glm::vec4(u.x, u.y, u.z, eye.x),
                                     glm::vec4(v.x, v.y, v.z, eye.y),
                                     glm::vec4(w.x, w.y, w.z, eye.z),
                                     glm::vec4(0,   0,   -1,  1 ));

    if(debug){
        std::cout << "LookAt Matrix:" << std::endl;
        print4x4Matrix(result);
    }

    return result;

    /*
        std::cout << "Vergleichsmatrix Ginkel:" << std::endl; //Only for debugging
        glm::mat4x4 tempMat = glm::mat4x4(glm::vec4(1.0, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 0.0, 1.0, -1.0), glm::vec4(0.0, 0.0, -1.0, 1.0));
        print4x4Matrix(tempMat);
    */
}






void CgCamera::print4x4Matrix(glm::mat4x4 &value)
{

    for(int m = 0; m < 4; m++){
        for(int n = 0; n < 4; n++){
            std::cout << value[m][n] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}



//-------- Getter and Setter

glm::vec3 CgCamera::getEye(void) const
{
    return eye;
}
void CgCamera::setEye(glm::vec3 value)
{
    eye = value;
}

glm::vec3 CgCamera::getCenter(void) const
{
    return center;
}
void CgCamera::setCenter(glm::vec3 value)
{
    center = value;
}

glm::vec3 CgCamera::getUp(void) const
{
    return up;
}

void CgCamera::setUp(glm::vec3 value){
    up = value;
}

int CgCamera::getWindowHeight() const
{
    return windowHeight;
}

void CgCamera::setWindowHeight(int value)
{
    windowHeight = value;
}

int CgCamera::getWindowWidth() const
{
    return windowWidth;
}

void CgCamera::setWindowWidth(int value)
{
    windowWidth = value;
}



