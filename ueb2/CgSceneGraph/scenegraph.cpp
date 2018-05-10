#include "scenegraph.h"
#include "CgBase/CgBaseRenderableObject.h"
#include "sceneentity.h"
#include "iostream"

Scenegraph::Scenegraph(SceneEntity* sc):sc(sc){

    matrixstack.push(glm::mat4x4(glm::vec4(1,0,0,0),
                                 glm::vec4(0,1,0,0),
                                 glm::vec4(0,0,1,0),
                                 glm::vec4(0,0,0,1)));
    counter=0;
   // std::cout<<matrixstack.top()<<std::endl;

}
SceneEntity *Scenegraph::getSc() const
{

    return sc;
}

void Scenegraph::setSc(SceneEntity *value)
{
    sc = value;
}

void Scenegraph::render(CgBaseRenderer *render,SceneEntity* sc)
{

    counter++;
   int x=(counter/1000)%360;


    std::cout<<x<<std::endl;
    glm::mat4x4 ma= matrixstack.top()*sc->getTransformation();
    matrixstack.push(ma);
    sc->transform(0,0,x,ma);
    for(int i=0; i < sc->getChildren().size(); i++){
        std::cout<<"sada"<<std::endl;
        this->render(render,sc->getChildren().at(i));

    }
    render->init(sc->getOb());
    render->render(sc->getOb(),ma);
    matrixstack.pop();

}

void Scenegraph::pushMatrix()
{
    matrixstack.push(glm::mat4x4(glm::vec4(1,0,0,0),
                                 glm::vec4(0,1,0,0),
                                 glm::vec4(0,0,1,0),
                                 glm::vec4(0,0,0,1)));
}

void Scenegraph::popMatrix()
{
    matrixstack.pop();
}

void Scenegraph::applyTransform(glm::mat4 x)
{
    matrixstack.top()*x;
}


void Scenegraph::fillstack(SceneEntity* sc){
    if(sc->getChildren().empty()){
        matrixstack.push(matrixstack.top());
        matrixstack.top() = matrixstack.top()*sc->getTransformation();
    }
    if(!sc->getChildren().empty()){
        matrixstack.push(matrixstack.top());
        matrixstack.top()= matrixstack.top()*sc->getTransformation();
        for(int i=0;i<=sc->getChildren().size()-1;i++){
            fillstack(sc->getChildren().at(i));
        }
    }
}


