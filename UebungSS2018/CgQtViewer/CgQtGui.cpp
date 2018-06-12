
#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgSceneGraph/CgSceneControl.h"
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
#include <string>
#include <ostream>


//Höhe slider definieren, funktionalität inkludieren-------------------------------------CHECK
//normalen von rota-körper und kegel und zylinder anzeigen "taste", FUNKTIONALITÄT-------CHECK
//                    merke MyPolyline hat den lane riesenfeld algo !!!!
//aufgabe 4.c
//aufgbae 6.c ?
//aufgabe 7.c verscheibung des obejktes implementierung
//aufgabe 8.b vergleich der rotamatritzen implementerung
//aufgabe 10 refactorn
//aufgabe 13 EVENTUEL
//aufgabe 14 EVENTUEL



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

    QWidget* opt5 = new QWidget;
    page5(opt5);

//    connect(opt4, SIGNAL(objectNameChanged(QString)), this, SLOT(tabChange(QString)));
//    opt4->addAction(tabChange());

    QTabWidget* m_tabs = new QTabWidget();
    m_tabs->addTab(opt2,"&Aufgabe 1");
    m_tabs->addTab(opt,"&Aufgabe 2");
    m_tabs->addTab(opt3,"&Aufagbe 3");
    m_tabs->addTab(opt4,"&Aufagbe 4");
    m_tabs->addTab(opt5,"&Aufgabe 5");
    m_tabs->adjustSize();
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
    file_menu->addAction("&Load Hase", this, SLOT(objectOpenHase()));
    file_menu->addAction("&Load Tyranosaorus", this, SLOT(objectOpenTyra()));
    file_menu->addAction("&Load Porsche", this, SLOT(objectOpenPorshe()));

    //file_menu->addAction("&Open Mesh Model", this, SLOT(slotLoadMeshFile()));
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

QSlider *CgQtGui::createSlider(int max,int min,int steps)
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
    bt_show_poly = new QPushButton("Zeige Polyline");
    bt_show_poly->setCheckable(false);
    tab1_control->addWidget(bt_show_poly);
    connect(bt_show_poly, SIGNAL( clicked() ), this, SLOT(ZeigePolylineButton()));

    bt_rese_poly = new QPushButton("Reset Polyline");
    tab1_control->addWidget(bt_rese_poly);
    connect(bt_rese_poly, SIGNAL( clicked() ), this, SLOT(ResetPolylineButton()));

    QLabel* lab10= new QLabel("Lane-Riesenfeld Refine");
    tab1_control->addWidget(lab10);

    sl_rota_lane_refine = createSlider();
    tab1_control->addWidget(sl_rota_lane_refine);
    sl_rota_lane_refine->setMinimum(1);
    sl_rota_lane_refine->setMaximum(5);
    sl_rota_lane_refine->setValue(1);
    sl_rota_lane_refine->setTickInterval(1);
    connect(sl_rota_lane_refine, SIGNAL(sliderReleased()), this, SLOT(laneRotaChange()));


    QLabel* lab7= new QLabel("RotationsKörper Refine");
    tab1_control->addWidget(lab7);

    sl_rota_refine = createSlider();
    tab1_control->addWidget(sl_rota_refine);
    sl_rota_refine->setMinimum(1);
    sl_rota_refine->setMaximum(360);
    sl_rota_refine->setValue(1);
    sl_rota_refine->setTickInterval(1);
    connect(sl_rota_refine, SIGNAL(sliderReleased()), this, SLOT(changeRotaKoerper()));

    QLabel* lab8= new QLabel("RotationsKörper Hoehe");
    tab1_control->addWidget(lab8);

    sl_rota_hoehe = createSlider();
    tab1_control->addWidget(sl_rota_hoehe);
    sl_rota_hoehe->setMinimum(1);
    sl_rota_hoehe->setMaximum(5);
    sl_rota_hoehe->setValue(1);
    sl_rota_hoehe->setTickInterval(1);
    connect(sl_rota_hoehe, SIGNAL(sliderReleased()), this, SLOT(changeRotaKoerper()));


    QLabel* lab9= new QLabel("----------------------------------------------------------------------------------");
    tab1_control->addWidget(lab9);

    bt_show_normal = new QPushButton("Zeige Normale");
    tab1_control->addWidget(bt_show_normal);
    bt_show_normal->setCheckable(false);
    connect(bt_show_normal, SIGNAL( clicked() ), this, SLOT(zeige_normale_taste_page2()));

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
    //connect(myButton1, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()) );

    QPushButton* myButton2 = new QPushButton("Zeige Normale");
    tab3_control->addWidget(myButton2);
    //connect(myButton2, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()) );


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

    //----------------------------------------------------------------------------------------
//    QGroupBox* mySpinnerBox = new QGroupBox("figur drehen ");
//    QVBoxLayout* SBox = new QVBoxLayout;
//    mySpinnerBox->setLayout(SBox);

    QVBoxLayout *subSBox = new QVBoxLayout();
//    subSBox->addWidget(mySpinnerBox);
    tab4_control->addLayout(subSBox);


    QLabel* lab2= new QLabel("drehung X achse");
    subSBox->addWidget(lab2);

    obj_rotate_X = new QSpinBox();
    tab4_control->addWidget(obj_rotate_X);
    obj_rotate_X->setMinimumHeight(25);
    obj_rotate_X->setMinimum(1);
    obj_rotate_X->setMaximum(50);
    obj_rotate_X->setValue(1);
    connect( obj_rotate_X, SIGNAL(editingFinished()), this, SLOT(changeRotationObject()));
    subSBox->addWidget(obj_rotate_X);

    QLabel* lab3= new QLabel("drehung Y achse");
    subSBox->addWidget(lab3);

    obj_rotate_Y = new QSpinBox();
    tab4_control->addWidget(obj_rotate_Y);
    obj_rotate_Y->setMinimum(1);
    obj_rotate_Y->setMaximum(50);
    obj_rotate_Y->setValue(1);
    connect( obj_rotate_Y, SIGNAL(editingFinished()), this, SLOT(changeRotationObject()));
    subSBox->addWidget(obj_rotate_Y);

    QLabel* lab4= new QLabel("drehung Z achse");
    subSBox->addWidget(lab4);

    obj_rotate_Z = new QSpinBox();
    tab4_control->addWidget(obj_rotate_Z);
    obj_rotate_Z->setMinimum(1);
    obj_rotate_Z->setMaximum(50);
    obj_rotate_Z->setValue(1);
    connect( obj_rotate_Z, SIGNAL(editingFinished()), this, SLOT(changeRotationObject()));
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

    sl_change_RotaX = new QSlider(Qt::Horizontal);
    sl_change_RotaX->setMaximum(10);
    sl_change_RotaX->setValue(0);
    sl_change_RotaX->setTickInterval(1);
    sl_change_RotaX->setVisible(false);
    connect(sl_change_RotaX, SIGNAL(sliderReleased()), this, SLOT(changeRotationPlanet()));

    sl_change_RotaY = new QSlider(Qt::Horizontal);
    sl_change_RotaY->setMaximum(10);
    sl_change_RotaY->setValue(0);
    sl_change_RotaY->setTickInterval(1);
    sl_change_RotaY->setVisible(false);
    connect(sl_change_RotaY, SIGNAL(sliderReleased()), this, SLOT(changeRotationPlanet()));

    sl_change_RotaZ = new QSlider(Qt::Horizontal);
    sl_change_RotaZ->setMaximum(10);
    sl_change_RotaZ->setValue(0);
    sl_change_RotaZ->setTickInterval(1);
    sl_change_RotaZ->setVisible(false);
    connect(sl_change_RotaZ, SIGNAL(sliderReleased()), this, SLOT(changeRotationPlanet()));

    myButtonGroup->addButton(radiobutton11,0);
    myButtonGroup->addButton(radiobutton12,1);
    myButtonGroup->addButton(radiobutton13,2);

   bt_vergleiche_matritzen = new QPushButton("Vergleiche Matritzen");
    connect(bt_vergleiche_matritzen, SIGNAL(clicked()), this, SLOT(matrizenCheck()));

    lab_matr_check= new QLabel("Matritzen unchecked");


//    CgChangeTageswert               = 0x9786354,
//    CgZeigeSonnenSystem             = 0x1847200,
//    CgStartRotation                 = 0x1837260,
//    CgZeige3DPfeile                 = 0x9955883


    bt_inc_day = new QPushButton("erhöhe tageswert");
    connect(bt_inc_day, SIGNAL(clicked()), this, SLOT(erhoeheTageswert()));
    bt_dec_day = new QPushButton("verringere tageswert");
    connect(bt_dec_day, SIGNAL(clicked()), this, SLOT(verringereTageswert()));

    lab_day_rota= new QLabel("rotations Tageswert: 1");

    bt_show_sun = new QPushButton("Zeige Sonnensystem");
    bt_show_sun->setCheckable(false);
    connect(bt_show_sun, SIGNAL(clicked()), this, SLOT(zeigeSonnensystem()));

    bt_hide_all= new QPushButton("Hide All");
    connect(bt_hide_all, SIGNAL(clicked()), this, SLOT(hideAll()));

    bt_start_rotation = new QPushButton("Start Rotation");
    bt_start_rotation->setCheckable(false);
    connect(bt_start_rotation, SIGNAL(clicked()), this, SLOT(startRotation()));

    bt_show_3d_arrow = new QPushButton("zeige 3D Pfeile");
    bt_show_3d_arrow->setCheckable(false);
    connect(bt_show_3d_arrow, SIGNAL(clicked()), this, SLOT(show3dArrow()));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(bt_hide_all);
    vbox->addWidget(bt_show_sun);
    vbox->addWidget(bt_show_3d_arrow);
    vbox->addWidget(bt_inc_day);
    vbox->addWidget(bt_dec_day);
    vbox->addWidget(lab_day_rota);
    vbox->addWidget(bt_start_rotation);
    vbox->addWidget(bt_vergleiche_matritzen);

    vbox->addWidget(lab_matr_check);
    vbox->addWidget(radiobutton11);
    vbox->addWidget(sl_change_RotaX);
    vbox->addWidget(radiobutton12);
    vbox->addWidget(sl_change_RotaY);
    vbox->addWidget(radiobutton13);
    vbox->addWidget(sl_change_RotaZ);

    vbox->addStretch(1);

    myGroupBox->setLayout(vbox);
    subBox->addWidget(myGroupBox);
    tab5_control->addLayout(subBox);
    parent->setLayout(tab5_control);
}

void CgQtGui::page5(QWidget *parent)
{
    QVBoxLayout *tab1_control = new QVBoxLayout();


    parent->setLayout(tab1_control);
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

void CgQtGui::laneRotaChange()
{
    std::cout<<"lane-riesenfeld refine "<<sl_rota_lane_refine->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_rota_lane_refine->value(),0,0));
    notifyObserver(new bestersliderMoveEvent(Cg::CgLaneRefine,traeger));
}

void CgQtGui::changeColor()
{
    std::cout<<"farbe "<<sl_change_Red->value()<<sl_change_Green->value()<<sl_change_Blue->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_change_Red->value(),sl_change_Green->value(),sl_change_Blue->value()));
    notifyObserver(new bestersliderMoveEvent(Cg::CgChangeColor,traeger));
}

void CgQtGui::ZeigePolylineButton()
{
    if(bt_show_poly->isCheckable()){
        bt_show_poly->setCheckable(false);
        bt_show_poly->setText("Zeige polyline");
        std::cout<<"verstecke polyline"<<std::endl;
        traeger->setAn_aus(0);
        notifyObserver(new bestersliderMoveEvent(Cg::CgZeigePolyline,traeger));
    }else{
        bt_show_poly->setCheckable(true);
        bt_show_poly->setText("verstecke polyline");
        std::cout<<"zeige polyline"<<std::endl;
        traeger->setAn_aus(1);
        notifyObserver(new bestersliderMoveEvent(Cg::CgZeigePolyline,traeger));
    }
}

void CgQtGui::ResetPolylineButton()
{
    std::cout<<"Reset Polyline"<<std::endl;
    traeger = new TraegerKlasse();
    notifyObserver(new bestersliderMoveEvent(Cg::CgResetPolyline,traeger));
}

void CgQtGui::zeige_normale_taste_page2()
{

    if(bt_show_normal->isCheckable()){
        bt_show_normal->setCheckable(false);
        bt_show_normal->setText("Zeige Normale");
        std::cout<<"verstecke Noemale"<<std::endl;
        traeger->setAn_aus(0);
        notifyObserver(new bestersliderMoveEvent(Cg::CgZeigeNormalePage2,traeger));
    }else{
        bt_show_normal->setCheckable(true);
        bt_show_normal->setText("verstecke Normale");
        std::cout<<"zeige Normale"<<std::endl;
        traeger->setAn_aus(1);
        notifyObserver(new bestersliderMoveEvent(Cg::CgZeigeNormalePage2,traeger));
    }
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

void CgQtGui::selectX()
{
    if(!sl_change_RotaX->isVisible()){
        sl_change_RotaX->setVisible(true);
    }else{
        sl_change_RotaX->setVisible(false);
    }
}

void CgQtGui::selectY()
{
    if(!sl_change_RotaY->isVisible()){
        sl_change_RotaY->setVisible(true);
    }else{
        sl_change_RotaY->setVisible(false);
    }
}

void CgQtGui::selectZ()
{
    if(!sl_change_RotaZ->isVisible()){
        sl_change_RotaZ->setVisible(true);
    }else{
        sl_change_RotaZ->setVisible(false);
    }
}

void CgQtGui::matrizenCheck()
{
    std::cout<<"checke matritzen"<<std::endl;
    traeger = new TraegerKlasse();
    notifyObserver(new bestersliderMoveEvent(Cg::CgMatritzeChecken,traeger));
}

void CgQtGui::changeRotationPlanet()
{
    std::cout<<"change rota page4   "<<sl_change_RotaX->value()<<" "<<sl_change_RotaY->value()<<" "<<sl_change_RotaZ->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_change_RotaX->value(),sl_change_RotaY->value(),sl_change_RotaZ->value()));
    notifyObserver(new bestersliderMoveEvent(Cg::CgChangeRotationPlaneten,traeger));
}

void CgQtGui::objectOpenHase()
{
    std::cout<<"load Hase"<<std::endl;
    traeger->setAn_aus(0);
    notifyObserver(new bestersliderMoveEvent(Cg::CgChangeWahl,traeger));
}


void CgQtGui::objectOpenTyra()
{
    std::cout<<"load Tyra"<<std::endl;
    traeger->setAn_aus(1);
    notifyObserver(new bestersliderMoveEvent(Cg::CgChangeWahl,traeger));
}


void CgQtGui::objectOpenPorshe()
{
    std::cout<<"load Porshe"<<std::endl;
    traeger->setAn_aus(2);
    notifyObserver(new bestersliderMoveEvent(Cg::CgChangeWahl,traeger));
}

void CgQtGui::hideAll()
{
    if(!bt_inc_day->isVisible()){
        bt_hide_all->setText("Hide All");
        bt_inc_day->setVisible(true);
        bt_dec_day->setVisible(true);
        bt_show_3d_arrow->setVisible(true);
        bt_show_sun->setVisible(true);
        bt_start_rotation->setVisible(true);
        lab_day_rota->setVisible(true);
        bt_vergleiche_matritzen->setVisible(true);
        lab_matr_check->setVisible(true);
    }else{
        bt_hide_all->setText("Show All");
        bt_inc_day->setVisible(false);
        bt_dec_day->setVisible(false);
        bt_show_3d_arrow->setVisible(false);
        bt_show_sun->setVisible(false);
        bt_start_rotation->setVisible(false);
        lab_day_rota->setVisible(false);
        bt_vergleiche_matritzen->setVisible(false);
        lab_matr_check->setVisible(false);
    }
}

void CgQtGui::erhoeheTageswert()
{
    tag += 1;
    QString s = QStringLiteral("rotations Tageswert: %1").arg(tag);
    lab_day_rota->setText(s);
    std::cout<<"erhöhe tages wert"<<std::endl;
    traeger->setAn_aus(1);
    notifyObserver(new bestersliderMoveEvent(Cg::CgChangeTageswert,traeger));
}

void CgQtGui::verringereTageswert()
{
    if(tag>=2){
    tag -= 1;
    QString s = QStringLiteral("rotations Tageswert: %1").arg(tag);
    lab_day_rota->setText(s);
    std::cout<<"verringere tages wert"<<std::endl;
    traeger->setAn_aus(0);
    notifyObserver(new bestersliderMoveEvent(Cg::CgChangeTageswert,traeger));
    }else{
        lab_day_rota->setText("weniger als 1 geht es nicht");
    }
}

void CgQtGui::zeigeSonnensystem()
{
    if(bt_show_sun->isCheckable()){
        bt_show_sun->setCheckable(false);
        bt_show_sun->setText("Zeige Sonnensystem");
        std::cout<<"verstecke sonnen system"<<std::endl;
        traeger->setAn_aus(0);
        notifyObserver(new bestersliderMoveEvent(Cg::CgZeigeSonnenSystem,traeger));
    }else{
        bt_show_sun->setCheckable(true);
        bt_show_sun->setText("verstecke Sonnensystem");
        std::cout<<"zeige sonnen system"<<std::endl;
        traeger->setAn_aus(1);
        notifyObserver(new bestersliderMoveEvent(Cg::CgZeigeSonnenSystem,traeger));
    }
}

void CgQtGui::startRotation()
{
    if(bt_start_rotation->isCheckable()){
        bt_start_rotation->setCheckable(false);
        bt_start_rotation->setText("Start Rotation");
        std::cout<<"beende Rotation"<<std::endl;
        traeger->setAn_aus(0);
        notifyObserver(new bestersliderMoveEvent(Cg::CgStartRotation,traeger));
    }else{
        bt_start_rotation->setCheckable(true);
        bt_start_rotation->setText("End Rotation");
        std::cout<<"starte rotation"<<std::endl;
        traeger->setAn_aus(1);
        notifyObserver(new bestersliderMoveEvent(Cg::CgStartRotation,traeger));
    }
}

void CgQtGui::show3dArrow()
{
    if(bt_show_3d_arrow->isCheckable()){
        bt_show_3d_arrow->setCheckable(false);
        bt_show_3d_arrow->setText("zeige 3D Pfeile");
        std::cout<<"Verstecke 3D Pfeile"<<std::endl;
        traeger->setAn_aus(0);
        notifyObserver(new bestersliderMoveEvent(Cg::CgZeige3DPfeile,traeger));
    }else{
        bt_show_3d_arrow->setCheckable(true);
        bt_show_3d_arrow->setText("verstecke 3D Pfeile");
        std::cout<<"Zeige 3D Pfeile"<<std::endl;
        traeger->setAn_aus(1);
        notifyObserver(new bestersliderMoveEvent(Cg::CgZeige3DPfeile,traeger));
    }
}



/*
void CgQtGui::selectSlider(QSlider* sl)
{
    if(!sl->isVisible()){
        sl->setVisible(true);
    }else{
        sl->setVisible(false);
    }
}
*/

CgBaseRenderer* CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}
