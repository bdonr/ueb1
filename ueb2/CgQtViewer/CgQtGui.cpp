
#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "../CgBase/CgEnums.h"
#include "../CgEvents/CgMouseEvent.h"
#include "../CgEvents/CgKeyEvent.h"
#include "../CgEvents/CgWindowResizeEvent.h"
#include "../CgSceneGraph/CgSceneControl.h"
#include "CgEvents/besterslidermoveevent.h"
#include "CgClass/traegerklasse.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMenuBar>
#include <QActionGroup>
#include <iostream>


//Höhe slider definieren, funktionalität inkludieren-------------------------------------CHECK
//normalen von rota-körper und kegel und zylinder anzeigen "taste", FUNKTIONALITÄT-------CHECK
//                    merke MyPolyline hat den lane riesenfeld algo !!!!
//aufgabe 4.c
//aufgbae 6.c ?
//aufgabe 7.b taste X, koordinaten system PFEILE
//aufgabe 7.c verscheibung des obejktes als GUI ----------------------------------------CHECK
//aufgabe 8.b vergleich der rotamatritzen, BUTTON
//aufgabe 10 refactorn
//aufgabe 13 EVENTUEL
//aufgabe 14 EVENTUEL


//problem mit zylinder und kegel in zeile 410 laut debuger, noch mal nachsehen.




void CgQtGui::init()
{
    std::vector<int> abc;
    abc.push_back(0);
    abc.push_back(0);
    abc.push_back(0);
    traeger = new TraegerKlasse(abc);
    color = glm::vec3(0,0,0);
    m_glRenderWidget = new CgQtGLRenderWidget;

    connect(m_glRenderWidget, SIGNAL(mouseEvent(QMouseEvent*)), this, SLOT(mouseEvent(QMouseEvent*)));
    connect(m_glRenderWidget, SIGNAL(viewportChanged(int,int)), this, SLOT(viewportChanged(int,int)));
    //  connect(m_glRenderWidget, SIGNAL(valueChanged(int)), this, SLOT(sliderMove(int)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;

    QWidget *opt = new QWidget;
    page2(opt);

    QWidget *opt2 = new QWidget;
    page1(opt2);

    QWidget* opt3 = new QWidget;
    page3(opt3);

    QWidget* opt4 = new QWidget;
    page4(opt4);
//    connect(opt4, SIGNAL(objectNameChanged(QString)), this, SLOT(tabChange(QString)));
//    opt4->addAction(tabChange());

    QTabWidget* m_tabs = new QTabWidget();
    m_tabs->addTab(opt2,"&Aufgabe 1");
    m_tabs->addTab(opt,"&Aufgabe 2");
    m_tabs->addTab(opt3,"&Aufagbe 3");
    m_tabs->addTab(opt4,"&Aufagbe 4");
    connect(m_tabs,SIGNAL(tabBarClicked(int)),this,SLOT(tabChange(int)));

    container->addWidget(m_tabs);

    m_tabs->setMinimumWidth(400);
    m_tabs->setMaximumWidth(600);

    container->addWidget(m_glRenderWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    m_glRenderWidget->setMinimumWidth(600);

    setLayout(mainLayout);
    setWindowTitle(tr("Übung Computergrafik 1 -  SoSe 2018"));


    /* create Menu Bar */
    m_menuBar = new QMenuBar;
    QMenu *file_menu = new QMenu("&File" );
    file_menu->addAction("&Open Mesh Model", this, SLOT(slotLoadMeshFile()));
    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    QMenu *settings_menu = new QMenu("&Setting" );
    QMenu *polygon_mode_menu = new QMenu("&Polygon Mode" );

    QAction* m_custom_rot=settings_menu->addAction("&Custom Rotations", m_glRenderWidget, SLOT(slotCustomRotation()));
    m_custom_rot->setCheckable(true);
    m_custom_rot->setChecked(false);

    QAction* m_lighting=settings_menu->addAction("&Lighting on", m_glRenderWidget, SLOT(slotLighting()));
    m_lighting->setCheckable(true);
    m_lighting->setChecked(false);


    QActionGroup* polygonmode_group = new QActionGroup(this);
    polygonmode_group->setExclusive(true);

    QAction* points=polygon_mode_menu->addAction("&Points", m_glRenderWidget, SLOT(slotPolygonPoints()));
    points->setCheckable(true);
    points->setChecked(false);


    QAction* wireframe=polygon_mode_menu->addAction("&Wireframe", m_glRenderWidget, SLOT(slotPolygonWireframe()));
    wireframe->setCheckable(true);
    wireframe->setChecked(true);

    QAction* filled=polygon_mode_menu->addAction("&Filled", m_glRenderWidget, SLOT(slotPolygonFilled()));
    filled->setCheckable(true);
    filled->setChecked(false);



    polygonmode_group->addAction(points);
    polygonmode_group->addAction(wireframe);
    polygonmode_group->addAction(filled);



    // todo: Add Quit-Action
    m_menuBar->addMenu( file_menu );
    m_menuBar->addMenu( settings_menu );
    m_menuBar->addMenu( polygon_mode_menu );


    m_mainWindow->setMenuBar(m_menuBar);
}

CgQtGui::CgQtGui(CgQtMainApplication *mw)
    : m_mainWindow(mw),radius(0.0),hoehe(0.0),refine(0)
{

    init();

}

QSlider *CgQtGui::createSlider()
{
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

QSlider *CgQtGui::createSlider(int r,int size,int max,int min,int steps)
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(min, max );
    slider->setSingleStep(1);
    slider->setPageStep(1);
    slider->setTickInterval(steps);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;

}


void CgQtGui::page2(QWidget* parent)
{
    QVBoxLayout *tab1_control = new QVBoxLayout();
    QPushButton* myButton2 = new QPushButton("Zeige Polyline");
    tab1_control->addWidget(myButton2);
    connect(myButton2, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()));

    QLabel* lab7= new QLabel("RotationsKörper Refine");
    tab1_control->addWidget(lab7);

    sl_rota_refine = createSlider();
    tab1_control->addWidget(sl_rota_refine);
    sl_rota_refine->setMinimum(3);
    sl_rota_refine->setMaximum(60);
    sl_rota_refine->setValue(20);
    sl_rota_refine->setTickInterval(1);
    connect(sl_rota_refine, SIGNAL(sliderReleased()), this, SLOT(changeRotaKoerper()));

    QLabel* lab8= new QLabel("RotationsKörper Hoehe");
    tab1_control->addWidget(lab8);

    sl_rota_hoehe = createSlider();
    tab1_control->addWidget(sl_rota_hoehe);
    sl_rota_hoehe->setMinimum(1);
    sl_rota_hoehe->setMaximum(60);
    sl_rota_hoehe->setValue(20);
    sl_rota_hoehe->setTickInterval(1);
    connect(sl_rota_hoehe, SIGNAL(sliderReleased()), this, SLOT(changeRotaKoerper()));


    QLabel* lab9= new QLabel("----------------------------------------------------------------------------------");
    tab1_control->addWidget(lab9);

    QPushButton* myButton1 = new QPushButton("Zeige Normale");
    tab1_control->addWidget(myButton1);
    connect(myButton1, SIGNAL( clicked() ), this, SLOT(zeige_normale_taste_page2()));

    QLabel* lab1= new QLabel("Zylinder Hoehe");
    tab1_control->addWidget(lab1);

    sl_zylinder_hoehe = createSlider();
    tab1_control->addWidget(sl_zylinder_hoehe);
    sl_zylinder_hoehe->setMinimum(0);
    sl_zylinder_hoehe->setMaximum(60);
    sl_zylinder_hoehe->setValue(20);
    sl_zylinder_hoehe->setTickInterval(1);
    connect(sl_zylinder_hoehe, SIGNAL(sliderReleased()), this, SLOT(changeZylinder()));

    QLabel* lab2= new QLabel("Zylinder Radius");
    tab1_control->addWidget(lab2);

    sl_zylinder_radius = createSlider();
    tab1_control->addWidget(sl_zylinder_radius);
    sl_zylinder_radius->setMinimum(0);
    sl_zylinder_radius->setMaximum(60);
    sl_zylinder_radius->setValue(20);
    sl_zylinder_radius->setTickInterval(1);
    connect(sl_zylinder_radius, SIGNAL(sliderReleased()), this, SLOT(changeZylinder()));

    QLabel* lab3= new QLabel("Zylinder Refine");
    tab1_control->addWidget(lab3);

    sl_zylinder_refine = createSlider();
    tab1_control->addWidget(sl_zylinder_refine);
    sl_zylinder_refine->setMinimum(1);
    sl_zylinder_refine->setMaximum(60);
    sl_zylinder_refine->setValue(20);
    sl_zylinder_refine->setTickInterval(1);
    connect(sl_zylinder_refine, SIGNAL(sliderReleased()), this, SLOT(changeZylinder()));

    QLabel* lab4= new QLabel("Kegel Refine");
    tab1_control->addWidget(lab4);

    sl_kegel_refine = createSlider();
    tab1_control->addWidget(sl_kegel_refine);
    sl_kegel_refine->setMinimum(3);
    sl_kegel_refine->setMaximum(60);
    sl_kegel_refine->setValue(20);
    sl_kegel_refine->setTickInterval(1);
    connect(sl_kegel_refine, SIGNAL(sliderReleased()), this, SLOT(changeKegel()));

    QLabel* lab5= new QLabel("Kegel Radius");
    tab1_control->addWidget(lab5);

    sl_kegel_radius = createSlider();
    tab1_control->addWidget(sl_kegel_radius);
    sl_kegel_radius->setMinimum(0);
    sl_kegel_radius->setMaximum(60);
    sl_kegel_radius->setValue(20);
    sl_kegel_radius->setTickInterval(1);
    connect(sl_kegel_radius, SIGNAL(sliderReleased()), this, SLOT(changeKegel()));

    QLabel* lab6= new QLabel("Kegel Hoehe");
    tab1_control->addWidget(lab6);

    sl_kegel_hoehe = createSlider();
    tab1_control->addWidget(sl_kegel_hoehe);
    sl_kegel_hoehe->setMinimum(0);
    sl_kegel_hoehe->setMaximum(60);
    sl_kegel_hoehe->setValue(20);
    sl_kegel_hoehe->setTickInterval(1);
    connect(sl_kegel_hoehe, SIGNAL(sliderReleased()), this, SLOT(changeKegel()));

    parent->setLayout(tab1_control);

}


void CgQtGui::page1(QWidget* parent)
{
    QVBoxLayout *tab3_control = new QVBoxLayout();

    QLabel* lab1= new QLabel("erstelle Wuerfel");
    tab3_control->addWidget(lab1);

    QPushButton* myButton1 = new QPushButton("Zeige Würfell");
    tab3_control->addWidget(myButton1);
    connect(myButton1, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()) );

    QPushButton* myButton2 = new QPushButton("Zeige Normale");
    tab3_control->addWidget(myButton2);
    connect(myButton2, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()) );


    QLabel* lab2= new QLabel("Rot");
    tab3_control->addWidget(lab2);

    sl_change_Red  = createSlider();
    tab3_control->addWidget(sl_change_Red);
    sl_change_Red->setMinimum(0);
    sl_change_Red->setMaximum(255);
    sl_change_Red->setValue(20);
    sl_change_Red->setTickInterval(4);
     connect(sl_change_Red, SIGNAL(sliderReleased()), this, SLOT(changeColor()));


    QLabel* lab3= new QLabel("Gruen");
    tab3_control->addWidget(lab3);

    sl_change_Green = createSlider();
    tab3_control->addWidget(sl_change_Green);
    sl_change_Green->setMinimum(0);
    sl_change_Green->setMaximum(255);
    sl_change_Green->setValue(20);
    sl_change_Green->setTickInterval(4);
    connect(sl_change_Green, SIGNAL(sliderReleased()), this, SLOT(changeColor()));

    QLabel* lab4= new QLabel("Blau");
    tab3_control->addWidget(lab4);
    sl_change_Blue = createSlider();
    tab3_control->addWidget(sl_change_Blue);
    sl_change_Blue->setMinimum(3);
    sl_change_Blue->setMaximum(255);
    sl_change_Blue->setValue(20);
    sl_change_Blue->setTickInterval(4);
    connect(sl_change_Blue, SIGNAL(sliderReleased()), this, SLOT(changeColor()));


    parent->setLayout(tab3_control);


}
void CgQtGui::page3(QWidget* parent)
{
    //tab4_control-->subBox-->myGroupBox-->vbox-->addWidget(radioButton123)    myButtonGroup-->addButton(addButton)

    QVBoxLayout *tab4_control = new QVBoxLayout();
    //---------------------------------------------------------------------------------------
    QVBoxLayout *subBox = new QVBoxLayout();


    QGroupBox* myGroupBox = new QGroupBox("Figur darstellen ");

    myButtonGroup = new QButtonGroup(subBox);
    myButtonGroup->setExclusive(true);

    QRadioButton* radiobutton1 = new QRadioButton( "&Hase");
    connect(radiobutton1, SIGNAL(pressed()), this, SLOT(objectOpenSelect1()));
    QRadioButton* radiobutton2 = new QRadioButton( "&Tyranosaorus");
    connect(radiobutton2, SIGNAL(pressed()), this, SLOT(objectOpenSelect2()));
    QRadioButton* radiobutton3 = new QRadioButton( "&Porsche");
    connect(radiobutton3, SIGNAL(pressed()), this, SLOT(objectOpenSelect3()));
    QRadioButton* radiobutton4 = new QRadioButton( "&Kugel");
    connect(radiobutton4, SIGNAL(pressed()), this, SLOT(objectOpenSelect4()));

    radiobutton3->setChecked(true);

    myButtonGroup->addButton(radiobutton1,0);
    myButtonGroup->addButton(radiobutton2,1);
    myButtonGroup->addButton(radiobutton3,2);
    myButtonGroup->addButton(radiobutton4,3);



    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobutton1);
    vbox->addWidget(radiobutton2);
    vbox->addWidget(radiobutton3);
    vbox->addWidget(radiobutton4);

    vbox->addStretch(1);
    myGroupBox->setLayout(vbox);
    subBox->addWidget(myGroupBox);
    tab4_control->addLayout(subBox);
    //----------------------------------------------------------------------------------------
//    QGroupBox* mySpinnerBox = new QGroupBox("figur drehen ");
//    QVBoxLayout* SBox = new QVBoxLayout;
//    mySpinnerBox->setLayout(SBox);

    QVBoxLayout *subSBox = new QVBoxLayout();
//    subSBox->addWidget(mySpinnerBox);
    tab4_control->addLayout(subSBox);


    QLabel* lab2= new QLabel("drehung X achse");
    subBox->addWidget(lab2);

    obj_rotate_X = new QSpinBox();
    tab4_control->addWidget(obj_rotate_X);
    obj_rotate_X->setMinimumHeight(25);
    obj_rotate_X->setMinimum(1);
    obj_rotate_X->setMaximum(50);
    obj_rotate_X->setValue(1);
    connect( obj_rotate_X, SIGNAL(editingFinished()), this, SLOT(changeRotationsObject()));
    subSBox->addWidget(obj_rotate_X);

    QLabel* lab3= new QLabel("drehung Y achse");
    subSBox->addWidget(lab3);

    obj_rotate_Y = new QSpinBox();
    tab4_control->addWidget(obj_rotate_Y);
    obj_rotate_Y->setMinimum(1);
    obj_rotate_Y->setMaximum(50);
    obj_rotate_Y->setValue(1);
    connect( obj_rotate_Y, SIGNAL(editingFinished()), this, SLOT(changeRotationsObject()));
    subSBox->addWidget(obj_rotate_Y);

    QLabel* lab4= new QLabel("drehung Z achse");
    subSBox->addWidget(lab4);

    obj_rotate_Z = new QSpinBox();
    tab4_control->addWidget(obj_rotate_Z);
    obj_rotate_Z->setMinimum(1);
    obj_rotate_Z->setMaximum(50);
    obj_rotate_Z->setValue(1);
    connect( obj_rotate_Z, SIGNAL(editingFinished()), this, SLOT(changeRotationsObject()));
    subSBox->addWidget(obj_rotate_Z);

//------------------------------------------------------------------------------------------
//    QGroupBox* mySpinnerBox2 = new QGroupBox("figur bewegen ");
//    QHBoxLayout* SBox2 = new QHBoxLayout;
//    mySpinnerBox2->setLayout(SBox2);

   // QVBoxLayout *subSBox2 = new QVBoxLayout();
//    subSBox2->addWidget(mySpinnerBox2);
   // tab4_control->addLayout(subSBox2);


    QLabel* lab22= new QLabel("bewegung X achse");
    subSBox->addWidget(lab22);

    obj_translate_X = new QSpinBox();
    tab4_control->addWidget(obj_translate_X);
    obj_translate_X->setMinimum(1);
    obj_translate_X->setMaximum(50);
    obj_translate_X->setValue(1);
    connect( obj_translate_X, SIGNAL(editingFinished()), this, SLOT(changeTranslateObject()));
    subSBox->addWidget(obj_translate_X);

    QLabel* lab32= new QLabel("bewegung Y achse");
    subSBox->addWidget(lab32);

    obj_translate_Y = new QSpinBox();
    tab4_control->addWidget(obj_translate_Y);
    obj_translate_Y->setMinimum(1);
    obj_translate_Y->setMaximum(50);
    obj_translate_Y->setValue(1);
    connect( obj_translate_Y, SIGNAL(editingFinished()), this, SLOT(changeTranslateObject()));
    subSBox->addWidget(obj_translate_Y);

    QLabel* lab42= new QLabel("bewegung Z achse");
    subSBox->addWidget(lab42);

    obj_translate_Z = new QSpinBox();
    tab4_control->addWidget(obj_translate_Z);
    obj_translate_Z->setMinimum(1);
    obj_translate_Z->setMaximum(50);
    obj_translate_Z->setValue(1);
    connect( obj_translate_Z, SIGNAL(editingFinished()), this, SLOT(changeTranslateObject()));
    subSBox->addWidget(obj_translate_Z);
//-----------------------------------------------------------------------------------------
    QLabel* lab1= new QLabel("zoom mit +/- \n drehen mit y/x/z");
    tab4_control->addWidget(lab1);
    parent->setLayout(tab4_control);

}

void CgQtGui::page4(QWidget* parent)
{
    QVBoxLayout *tab5_control = new QVBoxLayout();
    //---------------------------------------------------------------------------------------
    QVBoxLayout *subBox = new QVBoxLayout();
//    QVBoxLayout *subBox2 = new QVBoxLayout();

    QGroupBox* myGroupBox = new QGroupBox("Figur darstellen ");

    myButtonGroup = new QButtonGroup(subBox);
    myButtonGroup->setExclusive(false);

    QRadioButton* radiobutton11 = new QRadioButton( "&X");
    connect(radiobutton11, SIGNAL(pressed()), this, SLOT(selectX()));
    QRadioButton* radiobutton12 = new QRadioButton( "&Y");
    connect(radiobutton12, SIGNAL(pressed()), this, SLOT(selectY()));
    QRadioButton* radiobutton13 = new QRadioButton( "&Z");
    connect(radiobutton13, SIGNAL(pressed()), this, SLOT(selectZ()));

    sl_changeRotaX = new QSlider(Qt::Horizontal);
    sl_changeRotaX->setMaximum(10);
    sl_changeRotaX->setValue(0);
    sl_changeRotaX->setTickInterval(1);
    //sl_changeRotaX->setVisible(x);



    sl_change_RotaY = new QSlider(Qt::Horizontal);
    sl_change_RotaY->setMaximum(10);
    sl_change_RotaY->setValue(0);
    sl_change_RotaY->setTickInterval(1);
    //sl_change_RotaY->setVisible(y);

    sl_change_RotaZ = new QSlider(Qt::Horizontal);
    sl_change_RotaZ->setMaximum(10);
    sl_change_RotaZ->setValue(0);
    sl_change_RotaZ->setTickInterval(1);
    //sl_change_RotaZ->setVisible(z);



    connect(radiobutton11, SIGNAL(pressed()), this, SLOT(changeVisibleX()));
    connect(radiobutton12, SIGNAL(pressed()), this, SLOT(changeVisibleY()));
    connect(radiobutton13, SIGNAL(pressed()), this, SLOT(changeVisibleZ()));

    myButtonGroup->addButton(radiobutton11,0);
    myButtonGroup->addButton(radiobutton12,1);
    myButtonGroup->addButton(radiobutton13,2);

    connect(sl_changeRotaX,SIGNAL(sliderMoved(int)),this,SLOT(changeX(int)));
    connect(sl_change_RotaY,SIGNAL(sliderMoved(int)),this,SLOT(changeY(int)));
    connect(sl_change_RotaZ,SIGNAL(sliderMoved(int)),this,SLOT(changeZ(int)));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobutton11);
    vbox->addWidget(sl_changeRotaX);
    vbox->addWidget(radiobutton12);
    vbox->addWidget(sl_change_RotaY);
    vbox->addWidget(radiobutton13);
    vbox->addWidget(sl_change_RotaZ);

    vbox->addStretch(1);

    myGroupBox->setLayout(vbox);
    // subBox->addWidget(rotationsSlider);
    subBox->addWidget(myGroupBox);
//    subBox2->addWidget(kkk);
//    subBox2->addWidget(kkk1);
//    subBox2->addWidget(kkk2);
    tab5_control->addLayout(subBox);
//    tab5_control->addLayout(subBox2);
    parent->setLayout(tab5_control);
}

void CgQtGui::changeRotationObject()
{
    std::cout<<"rotate obj "<<obj_rotate_X->value()<<" "<<obj_rotate_Y->value()<<" "<<obj_rotate_Z->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(obj_rotate_X->value(),obj_rotate_Y->value(),obj_rotate_Z->value()));
    notifyObserver(new bestersliderMoveEvent(Cg::CgObjRotate,traeger));
}

void CgQtGui::changeTranslateObject()
{
    std::cout<<"translate obj "<<obj_translate_X->value()<<" "<<obj_translate_Y->value()<<" "<<obj_translate_Z->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(obj_translate_X->value(),obj_translate_Y->value(),obj_translate_Z->value()));
    notifyObserver(new bestersliderMoveEvent(Cg::CgObjTranslate,traeger));
}

void CgQtGui::changeRotaKoerper()
{
    std::cout<<"rotationskörper: "<<sl_rota_refine->value()<<" "<<sl_rota_hoehe->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_rota_refine->value(),sl_rota_hoehe->value(),0));
    notifyObserver(new bestersliderMoveEvent(Cg::CgChangeRota,traeger));
}

void CgQtGui::changeColor()
{
    std::cout<<"farbe "<<sl_change_Red->value()<<sl_change_Green->value()<<sl_change_Blue->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_change_Red->value(),sl_change_Green->value(),sl_change_Blue->value()));
    notifyObserver(new bestersliderMoveEvent(Cg::CgChangeColor,traeger));
}

void CgQtGui::zeige_normale_taste_page2()
{
    if(zeige_normale_anAus==0){
        zeige_normale_anAus=1;
        traeger->setZeige_normale(1);
        notifyObserver(new bestersliderMoveEvent(Cg::CgZeigeNormalePage2,traeger));
    }else{
        zeige_normale_anAus=0;
        traeger->setZeige_normale(0);
        notifyObserver(new bestersliderMoveEvent(Cg::CgZeigeNormalePage2,traeger));
    }
    std::cout<<"zeige nornmale "<<zeige_normale_anAus<<std::endl;
}

void CgQtGui::changeKegel()
{
    std::cout<<"kegel "<<sl_kegel_hoehe->value()<<" "<<sl_kegel_radius->value()<<" "<<sl_kegel_refine->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_kegel_hoehe->value(),sl_kegel_radius->value(),sl_kegel_refine->value()));
    notifyObserver(new bestersliderMoveEvent(Cg::KegelChange,traeger));
}

void CgQtGui::changeZylinder()
{
    std::cout<<"zylinder "<<sl_zylinder_hoehe->value()<<" "<<sl_zylinder_radius->value()<<" "<<sl_zylinder_refine->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_zylinder_hoehe->value(),sl_zylinder_radius->value(),sl_zylinder_refine->value()));
    notifyObserver(new bestersliderMoveEvent(Cg::ZylinderChange,traeger));
}




void CgQtGui::mouseEvent(QMouseEvent* event)
{

    // std::cout << QApplication::keyboardModifiers() << std::endl;

    //  if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)==true)
    //    std::cout << Cg::ControlModifier << endl;


    if(event->type()==QEvent::MouseButtonPress)
    {


        CgBaseEvent* e = new CgMouseEvent(Cg::CgMouseButtonPress,
                                          glm::vec2(event->localPos().x() ,event->localPos().y()),
                                          (Cg::MouseButtons)event->button());

        notifyObserver(e);
    }

    if(event->type()==QEvent::MouseMove)
    {
        CgBaseEvent* e= new CgMouseEvent(Cg::CgMouseMove,
                                         glm::vec2(event->localPos().x() ,event->localPos().y()),
                                         (Cg::MouseButtons)event->button());
        notifyObserver(e);
    }



}

void CgQtGui::keyPressEvent(QKeyEvent *event)
{
    CgBaseEvent* e= new CgKeyEvent(Cg::CgKeyPressEvent,(Cg::Key)event->key(),(Cg::KeyboardModifiers)event->nativeModifiers(),event->text().toStdString());
    notifyObserver(e);
}


void CgQtGui::viewportChanged(int w, int h)
{
    CgBaseEvent* e = new CgWindowResizeEvent(Cg::WindowResizeEvent,w,h);
    notifyObserver(e);
}

void CgQtGui::tabChange(int x)
{
    TraegerKlasse* tr = new TraegerKlasse();
    tr->setTab(x);
    bestersliderMoveEvent* bsl = new bestersliderMoveEvent(Cg::TabChange,tr);
    notifyObserver(bsl);
}


CgBaseRenderer* CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}






void changeColor(void){

}

