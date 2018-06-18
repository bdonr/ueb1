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
    counterIncre= 1;


}

/**
 * @brief Scenegraph::findAndSetAppear
 * @param appear
 * @param type
 * finde Entitie mit Hilfe des jeweiligen Typen
 */
void Scenegraph::findAndSetAppear(Appearance *appear, enum Cg::ObjectType type)
{
    findAndSetAppear(this->getSc(),appear,type);
}
/**
 * @brief Scenegraph::findAndSetAppear
 * @param sc
 * @param appear
 * @param type
 * setze Appearance einer SceneEntity
 */
int Scenegraph::getCounterIncre() const
{
    return counterIncre;
}

void Scenegraph::setCounterIncre(int value)
{
    counterIncre = value;
}

void Scenegraph::findAndSetAppear(SceneEntity * sc,Appearance *appear, enum Cg::ObjectType type)
{
    if(sc->getChildren().empty()){
        if(sc->getOb()->getType()==type){
            sc->setAppear(appear);
        }
    }
    if(!sc->getChildren().empty()){
        for(int i=0;i<sc->getChildren().size();i++){
            findAndSetAppear(sc->getChildren().at(i),appear,type);
        }
    }
}
SceneEntity *Scenegraph::getSc() const
{

    return sc;
}

void Scenegraph::setSc(SceneEntity *value)
{
    sc = value;
}

//rendere jede entity mit seiner jeweiligen matrix
/**
 * @brief Scenegraph::render
 * @param render
 * @param sc
 */
void Scenegraph::setUniform(int i, CgBaseRenderer *render, SceneEntity* sc,bool lighton)
{
    if(lighton){
      render->setUniformValue("material.mamb",sc->getChildren().at(i)->getAppear()->getMaterial()->getAmb());
      render->setUniformValue("material.mdif",sc->getChildren().at(i)->getAppear()->getMaterial()->getDef());
      render->setUniformValue("material.mspec",sc->getChildren().at(i)->getAppear()->getMaterial()->getSpec());
      render->setUniformValue("material.mshine",sc->getChildren().at(i)->getAppear()->getMaterial()->getScalar());
      }
      else{
          render->setUniformValue("rgb",sc->getChildren().at(i)->getAppear()->getMaterial()->getAmb());
  }

}
void Scenegraph::setUniform(CgBaseRenderer *render, SceneEntity* sc,bool lighton)
{
    if(lighton){
    render->setUniformValue("material.mamb",sc->getAppear()->getMaterial()->getAmb());
    render->setUniformValue("material.mdif",sc->getAppear()->getMaterial()->getDef());
    render->setUniformValue("material.mspec",sc->getAppear()->getMaterial()->getSpec());
    render->setUniformValue("material.mshine",sc->getAppear()->getMaterial()->getScalar());
    }
    else{
        render->setUniformValue("rgb",sc->getAppear()->getMaterial()->getAmb());
    }
}
/**
 * @brief Scenegraph::render
 * @param render
 * @param sc
 * lasse jede SceneEntitty sein eigenes Object rendern
 */
void Scenegraph::render(CgBaseRenderer *render,SceneEntity* sc,bool lighton)
{

    counter+=(counter+counterIncre)%360;
    if(counter>=359){
        counter=0;
    }
    //sc->setAusrichtung();
    glm::mat4x4 ma= matrixstack.top()*sc->getTransformation();
    matrixstack.push(ma);
    sc->rotate(counter,counter,counter);
    for(int i=0; i < sc->getChildren().size(); i++){
        sc->getChildren().at(i)->rotate(counter,counter,counter);
        setUniform(i, render, sc,lighton);
        this->render(render,sc->getChildren().at(i),lighton);

    }
    setUniform(render,sc,lighton);
    render->init(sc->getOb());
    render->render(sc->getOb(),ma);
    matrixstack.pop();

}
/**
 * @brief Scenegraph::pushMatrix
 */
void Scenegraph::pushMatrix()
{
    matrixstack.push(glm::mat4x4(glm::vec4(1,0,0,0),
                                 glm::vec4(0,1,0,0),
                                 glm::vec4(0,0,1,0),
                                 glm::vec4(0,0,0,1)));
}

/**
 * @brief Scenegraph::popMatrix
 */
void Scenegraph::popMatrix()
{
    matrixstack.pop();
}

void Scenegraph::applyTransform(glm::mat4 x)
{
    matrixstack.top()*x;
}

//fülle stack mit den entities und deren transformationen
/**
 * @brief Scenegraph::fillstack
 * @param sc
 */
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


