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
    float o=0.0;
    counter++;
   int x=(counter/1000)%360;
    o=o+.1;
    if(o>=359){
        o=0.1;
       // x=0;
    }

    if(x>=359){
        x=0;
    }
    //sc->setAusrichtung();
    glm::mat4x4 ma= matrixstack.top()*sc->getTransformation();
    matrixstack.push(ma);
    sc->rotate(0,o,o,ma);
    for(int i=0; i < sc->getChildren().size(); i++){

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


