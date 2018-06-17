#include "CgCamera.h"
#include <iostream>
#include <glm/glm.hpp>


CgCamera::CgCamera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, int windowHeight, int windowWidth)
{
    this->eye = eye;
    this->center = center;
    this->up = up;
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;
}

//@author Gerrit Harmes
glm::mat4x4 CgCamera::getProjectionMatrix(int projection)
{
    bool debug = false;

    glm::mat4x4 result;

    float n, f, r, l, t, b;
    r = 0.5;
    l = -0.5;
    t = 0.5;
    b = -0.5;
    n = 1;
    f = 5;

    if(projection == 0){
        //Parallel Projektion
        std::cout << "Parallel Projektion" << std::endl;

        result = glm::mat4x4(glm::vec4( (2)/(r-l) , 0 , 0 , -(r+l)/(r-l) ),
                             glm::vec4( 0 , (2)/(t-b) , 0 , -(t+b)/(t-b) ),
                             glm::vec4( 0 , 0 , (-2)/(f-n) , -(f+n)/(f-n) ),
                             glm::vec4( 0 , 0 , 0 , 1 ));

    }else if(projection == 1){
        //Zentral Projektion
        std::cout << "Zentral Projektion" << std::endl;

        result = glm::mat4x4(glm::vec4( (2*n)/(r-l) , 0 , (r+l)/(r-l) , 0 ),
                             glm::vec4( 0 , (2*n)/(t-b) , (t+b)/(t-b) , 0 ),
                             glm::vec4( 0 , 0 , -(f+n)/(f-n) , -(2*f*n)/(f-n) ),
                             glm::vec4( 0 , 0 , -1 , 0 ));

    }else{
        //Ginkel Standart Matrix
        return glm::mat4x4(glm::vec4(1.792591, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.792591, 0.0, 0.0), glm::vec4(0.0, 0.0, -1.0002, -1.0), glm::vec4(0.0, 0.0, -0.020002, 0.0));
    }


    if(debug){


        std::cout << "Projektionsmatrix" << std::endl;
        print4x4Matrix(result);

        glm::vec4 testVec = glm::vec4(0.3,-0.1,0,4);
        glm::mat4x4 testLookAtMatrix = getLookAtMatrix();

        std::cout << "TestVec WeltKoordinaten:    " << testVec.x << " " << testVec.y << " " << testVec.z << " " << std::endl;
        testVec =  testLookAtMatrix * testVec;
        std::cout << "TestVec Kamera Koordinaten: " << testVec.x << " " << testVec.y << " " << testVec.z << " " << std::endl;
        testVec = result * testVec;
        std::cout << "TestVec NDC:                " << testVec.x << " " << testVec.y << " " << testVec.z << " " << std::endl;
        std::cout << std::endl;
    }

    //m_proj_matrix=glm::perspective(45.0f, (float)(ev->w()) / ev->h(), 0.01f, 100.0f); //????


    return result;
}

//@author Gerrit
void CgCamera::matrizenTest()
{
    glm::mat4x4 lookAt = getLookAtMatrix();
    glm::mat4x4 projektionParallel = getProjectionMatrix(0);
    glm::mat4x4 projektionZentral = getProjectionMatrix(1);

    std::cout << "Projektionsmatrix Parallel" << std::endl;
    print4x4Matrix(projektionParallel);

    std::cout << "Projektionsmatrix Zentral" << std::endl;
    print4x4Matrix(projektionParallel);

    std::cout << "LookAt" << std::endl;
    print4x4Matrix(projektionParallel);

    glm::vec4 testVec = glm::vec4(0.3,-0.1,0,4);

    std::cout << "TestVec WeltKoordinaten:    " << testVec.x << " " << testVec.y << " " << testVec.z << " " << std::endl;
    testVec =  lookAt * testVec;
    std::cout << "TestVec Kamera Koordinaten: " << testVec.x << " " << testVec.y << " " << testVec.z << " " << std::endl;


    glm::vec4 testVecParallel = projektionParallel * testVec;
    std::cout << "TestVec Parallel projeziert in NDC:                " << testVecParallel.x << " " << testVecParallel.y << " " << testVecParallel.z << " " << std::endl;
    std::cout << std::endl;

    glm::vec4 testVecZentral = projektionZentral * testVec;
    std::cout << "TestVec Zentral projeziert in NDC:                " << testVecZentral.x << " " << testVecZentral.y << " " << testVecZentral.z << " " << std::endl;
    std::cout << std::endl;

}


//@author Gerrit Harmes
glm::mat4x4 CgCamera::getLookAtMatrix()
{
    bool debug = false;

    if(debug){
        std::cout << "eye: " << eye.x << " " << eye.y << " " << eye.z << std::endl;
        std::cout << "center: " << center.x << " " << center.y << " " << center.z << std::endl;
        std::cout << "up: " << up.x << " " << up.y << " " << up.z << std::endl;

        std::cout << "Vergleichsmatrix Ginkel:" << std::endl; //Only for debugging
        glm::mat4x4 tempMat = glm::mat4x4(glm::vec4(1.0, 0.0, 0.0, 0.0), glm::vec4(0.0, 1.0, 0.0, 0.0), glm::vec4(0.0, 0.0, 1.0, -1.0), glm::vec4(0.0, 0.0, -1.0, 1.0));
        print4x4Matrix(tempMat);
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



