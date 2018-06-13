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

    counter+=(counter+1)%360;
    if(counter>=359){
        counter=0;
    }
    //sc->setAusrichtung();
    glm::mat4x4 ma= matrixstack.top()*sc->getTransformation();
    matrixstack.push(ma);
    sc->rotate(counter,counter,counter);
    for(int i=0; i < sc->getChildren().size(); i++){
        render->setUniformValue("amb",sc->getChildren().at(i)->getAppear()->getMaterial()->getAmb());
        render->setUniformValue("def",sc->getChildren().at(i)->getAppear()->getMaterial()->getDef());
        render->setUniformValue("spec",sc->getChildren().at(i)->getAppear()->getMaterial()->getSpec());
        render->setUniformValue("spec",sc->getChildren().at(i)->getAppear()->getMaterial()->getScalar());
        this->render(render,sc->getChildren().at(i));

    }
    render->setUniformValue("amb",sc->getAppear()->getMaterial()->getAmb());
    render->setUniformValue("def",sc->getAppear()->getMaterial()->getDef());
    render->setUniformValue("spec",sc->getAppear()->getMaterial()->getSpec());
    render->setUniformValue("spec",sc->getAppear()->getMaterial()->getScalar());
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


