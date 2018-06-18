#include "CgQtGLRenderWidget.h"
#include "CgQtGlBufferObject.h"

#include "CgBase/CgBasePolyline.h"
#include "CgBase/CgBasePolygonMesh.h"

#include "CgBase/CgBaseRenderableObject.h"
#include "CgBase/CgEnums.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <QString>
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <iostream>
#include "CgClass/light.h"

#include "CgBase/CgBaseSceneControl.h"
#include "CgTrackball.h"

bool CgQtGLRenderWidget::m_transparent = false;

CgQtGLRenderWidget::CgQtGLRenderWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_program(0),
      m_custom_rotation(false),
      m_lighting(false),
      m_scene_control(NULL),
      m_backface_culling(false),
      m_polygonmode(1)
{
    m_core = QSurfaceFormat::defaultFormat().profile() == QSurfaceFormat::CoreProfile;
    this->light=new Light();
    light->setAdir(glm::vec3(1.0f,0.f,0.f));
    light->setAamb(glm::vec4(.5f,.5f,.5f,1.f));
    light->setAspec(glm::vec4(1.f,1.f,1.f,1.f));
    light->setAdif(glm::vec4(0.3f,.3f,.3f,1.f));
    // --transparent causes the clear color to be transparent. Therefore, on systems that
    // support it, the widget will become transparent apart from the logo.
    if (m_transparent) {
        QSurfaceFormat fmt = format();
        fmt.setAlphaBufferSize(8);
        setFormat(fmt);
    }



}

CgQtGLRenderWidget::~CgQtGLRenderWidget()
{
    cleanup();
}

void CgQtGLRenderWidget::redraw()
{
    update();
}


QSize CgQtGLRenderWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize CgQtGLRenderWidget::sizeHint() const
{
    return QSize(400, 400);
}



void CgQtGLRenderWidget::cleanup()
{
    if (m_program == NULL)
        return;
    makeCurrent();
    delete m_program;
    m_program = 0;
    doneCurrent();
}




void CgQtGLRenderWidget::render(CgBaseRenderableObject* obj,glm::mat4 world_coordinates)
{
    m_world=world_coordinates;


    // here arcball rotation

    if(!m_custom_rotation)
    {
        glm::mat4 arc_rot= m_trackball->getRotationMatrix();
        m_world = arc_rot* m_world ;
    }

    glm::mat4 mv_matrix = m_lookat * m_world ;
    glm::mat3 normal_matrix = glm::transpose(glm::inverse(glm::mat3(mv_matrix)));
    glm::mat4 ndc = m_proj * m_lookat * m_world;
    setUniformValue("viewPos",m_lookat);
    setUniformValue("ndc",mv_matrix);
    setUniformValue("mv",ndc);
    setUniformValue("worldMatrix",m_world);
    setUniformValue("normalMatrix",normal_matrix);

    setUniformValue("light.lamb",light->getAamb());
    setUniformValue("light.ldir",light->getAdir());
    setUniformValue("light.ldif",light->getAdif());
    setUniformValue("light.lspec",light->getAspec());


    if(m_gl_buffer_objects.find(obj->getID())!=m_gl_buffer_objects.end())
    {
        m_gl_buffer_objects[obj->getID()]->draw(obj);
    }


}


void CgQtGLRenderWidget::setUniformValue(std::string name,glm::mat3 val)
{
    if(m_attribute_locations.find(name)==m_attribute_locations.end())
        m_attribute_locations.insert(std::make_pair(name, m_program->uniformLocation(name.c_str())));
    m_program->bind();
    m_program->setUniformValue(m_attribute_locations[name], QMatrix3x3(glm::value_ptr(val)).transposed());

}

void CgQtGLRenderWidget::setUniformValue(std::string name,glm::mat4 val)
{

    if(m_attribute_locations.find(name)==m_attribute_locations.end())
        m_attribute_locations.insert(std::make_pair(name, m_program->uniformLocation(name.c_str())));
    m_program->bind();
    m_program->setUniformValue(m_attribute_locations[name], QMatrix4x4(glm::value_ptr(val)).transposed());
}


void CgQtGLRenderWidget::setUniformValue(std::string name,glm::vec4 val)
{

    if(m_attribute_locations.find(name)==m_attribute_locations.end()){
        m_attribute_locations.insert(std::make_pair(name, m_program->uniformLocation(name.c_str())));
        std::cout <<std::endl;
        std::cout <<""
                    "found "<<name<<std::endl;
        std::cout <<std::endl;
    }else{

    }
    m_program->bind();
    m_program->setUniformValue(m_attribute_locations[name],QVector4D(val.x,val.y,val.z,val.w));
       redraw();
}


void CgQtGLRenderWidget::setUniformValue(std::string name,glm::vec3 val)
{
    if(m_attribute_locations.find(name)==m_attribute_locations.end())
        m_attribute_locations.insert(std::make_pair(name, m_program->uniformLocation(name.c_str())));
    m_program->bind();
    m_program->setUniformValue(m_attribute_locations[name],QVector3D(val.x,val.y,val.z));
       redraw();
}

void CgQtGLRenderWidget::setUniformValue(std::string name,double val)
{
    if(m_attribute_locations.find(name)==m_attribute_locations.end())
        m_attribute_locations.insert(std::make_pair(name, m_program->uniformLocation(name.c_str())));
    m_program->bind();
    m_program->setUniformValue(m_attribute_locations[name],(float)val);
}

void CgQtGLRenderWidget::setUniformValue(std::string name,int val)
{
    if(m_attribute_locations.find(name)==m_attribute_locations.end())
        m_attribute_locations.insert(std::make_pair(name, m_program->uniformLocation(name.c_str())));
    m_program->bind();
    m_program->setUniformValue(m_attribute_locations[name],val);
}


void CgQtGLRenderWidget::setLookAtMatrix(glm::mat4 lookat)
{
    m_lookat=lookat;
}

void CgQtGLRenderWidget::setProjectionMatrix(glm::mat4 proj)
{
    m_proj=proj;
}


void CgQtGLRenderWidget::init(CgBaseRenderableObject* obj)
{
    CgQtGlBufferObject* bobj;

    if(m_gl_buffer_objects.find(obj->getID())!=m_gl_buffer_objects.end())
        bobj = m_gl_buffer_objects[obj->getID()];
    else
    {
        bobj = new CgQtGlBufferObject(m_program);
        m_gl_buffer_objects.insert(std::make_pair(obj->getID(),bobj));
    }



    if(obj->getType()==Cg::TriangleMesh)
    {
        bobj->initTriangleMesh((CgBaseTriangleMesh*)obj);
    }
    if(obj->getType()==Cg::PolygonalMesh)
    {
        bobj->initPolygonMesh((CgBasePolygonMesh*)obj);
    }
    if(obj->getType()==Cg::Polyline)
    {
        bobj->initPolyline((CgBasePolyline*)obj);
    }
    if(obj->getType()==Cg::PointCloud)
    {
        bobj->initPointCloud((CgBasePointCloud*)obj);
    }

}




void CgQtGLRenderWidget::initializeGL()
{


    m_trackball = new CgTrackball();
    m_trackball->init();
    m_trackball->place(glm::vec3(0.0,0.0,0.0),0.75);


    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &CgQtGLRenderWidget::cleanup);

    initializeOpenGLFunctions();

    glFrontFace(GL_CCW);
    glClearColor(0, 0, 0, m_transparent ? 0 : 1);
    m_program = new QOpenGLShaderProgram;

    setShaderSourceFiles("../UebungSS2018/CgShader/simple.vert","../UebungSS2018/CgShader/simple.frag");

    m_program->link();


    m_program->bind();

    setUniformValue("mycolor",glm::vec4(0.0,1.0,0.0,1.0));

    // Our camera never changes in this example.
    m_lookat=glm::lookAt(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0,0.0,0.0),glm::vec3(0.0,1.0,0.0));
    m_world=glm::mat4(1.);


    // Light position is fixed.
    m_light_pos=glm::vec3(0.0,0.0,70.0);

}

void CgQtGLRenderWidget::setShaderSourceFiles(std::string filename_vert,std::string filename_fragment)
{
    if(m_program->isLinked())
        m_program->release();

    m_program->removeAllShaders();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,filename_vert.c_str());
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,filename_fragment.c_str());
    m_program->link();
    m_program->bind();
}



void CgQtGLRenderWidget::paintGL()
{


    switch(m_polygonmode)
    {
    case 0: glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        break;
    case 1: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    case 2: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    default: break;
    }


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    m_program->bind();

    if(m_scene_control!=NULL)
        m_scene_control->renderObjects();



    m_program->release();

}

void CgQtGLRenderWidget::resizeGL(int w, int h)
{
    emit viewportChanged(w,h);
}

void CgQtGLRenderWidget::mousePressEvent(QMouseEvent *event)
{
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    GLfloat w=(GLfloat)viewport[2];
    GLfloat h=(GLfloat)viewport[3];

    float x= (float)event->x();
    float y= (float)event->y();


    // normalize into [-1;1]
    x=2.0*x / w -1.0;
    if (x<-1.0) x=-1.0;
    if (x>1.0) x=1.0;

    y=2.0*y / h -1.0;
    if (y<-1.0) y=-1.0;
    if (y>1.0) y=1.0;

    if(event->button()&Qt::LeftButton)
    {
        m_trackball->Ball_Mouse(glm::vec3(x,-y,0.0));
        m_trackball->beginDrag();
    }

    emit mouseEvent(event);
    update();
}

void CgQtGLRenderWidget::mouseMoveEvent(QMouseEvent *event)
{

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT,viewport);
    GLfloat w=(GLfloat)viewport[2];
    GLfloat h=(GLfloat)viewport[3];

    float x= (float)event->x();
    float y= (float)event->y();


    // normalize into [-1;1]
    x=2.0*x / w -1.0;
    if (x<-1.0) x=-1.0;
    if (x>1.0) x=1.0;

    y=2.0*y / h -1.0;
    if (y<-1.0) y=-1.0;
    if (y>1.0) y=1.0;

    m_trackball->Ball_Mouse(glm::vec3(x,-y,0.0));
    m_trackball->Ball_Update();

    emit mouseEvent(event);

    update();
}


void CgQtGLRenderWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()&Qt::LeftButton)
    {
        m_trackball->endDrag();

    }
    emit mouseEvent(event);
    update();
}

void CgQtGLRenderWidget::slotCustomColor()
{

    update();
}

void CgQtGLRenderWidget::slotCustomRotation()
{

    m_custom_rotation=!m_custom_rotation;
    update();
}

void CgQtGLRenderWidget::slotCustomRotationX(int x)
{
 std::cout << x<<std::endl;
    glm::vec3 k= this->light->getAdir();
    k.x=x;
    light->setAdir(k);
    update();

}

void CgQtGLRenderWidget::slotCustomRotationY(int y)
{

    glm::vec3 k= this->light->getAdir();
    k.y=y;
     std::cout << k.y<<std::endl;
    light->setAdir(k);
    update();
}

void CgQtGLRenderWidget::slotCustomRotationZ(int z)
{

     std::cout << z<<std::endl;
    glm::vec3 k= this->light->getAdir();
    k.z=z;
    light->setAdir(k);
    update();
}

void CgQtGLRenderWidget::slotCustomColorX(int x)
{

    glm::vec3 k= this->light->getAdir();
      std::cout << x<<std::endl;
    k.x=x;
    light->setAdir(k);
    update();
}

void CgQtGLRenderWidget::slotCustomColorY(int y)
{
    glm::vec4 k= this->light->getAamb();
    std::cout << y<<std::endl;
    k.y=y;
    light->setAamb(k);
    update();
}

void CgQtGLRenderWidget::slotCustomColorZ(int z)
{
    glm::vec4 k= this->light->getAamb();
      std::cout << z<<std::endl;
    k.z=z;
    light->setAamb(k);
    update();
}

void CgQtGLRenderWidget::slotLighting()
{
    m_lighting=!m_lighting;
    if(m_lighting){
        setShaderSourceFiles("../UebungSS2018/CgShader/phong/phong.vert","../UebungSS2018/CgShader/phong/phong.frag");
        update();
    }
    else{
        setShaderSourceFiles("../UebungSS2018/CgShader/simple.vert","../UebungSS2018/CgShader/simple.frag");
        update();
    }

    update();
}


void CgQtGLRenderWidget::slotPolygonPoints()
{
    m_polygonmode=0;
    update();
}


void CgQtGLRenderWidget::slotPolygonWireframe()
{
    m_polygonmode=1;
    update();
}

void CgQtGLRenderWidget::slotPolygonFilled()
{
    m_polygonmode=2;
    update();
}
