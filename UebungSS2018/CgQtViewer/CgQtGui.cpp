
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
#include <QComboBox>


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


// go

void CgQtGui::init()
{
    //--------------------------------------------------------------

    amb.push_back(glm::vec4(.25,.25,.25,1.0));
    def.push_back(glm::vec4(.40,.40,.40,1.0));
    spec.push_back(glm::vec4(.77,.77,.77,1.0));
    scala.push_back(76.8);

    amb.push_back(glm::vec4(.25,.21,.21,.90));
    def.push_back(glm::vec4(0.99,.83,.83,.90));
    spec.push_back(glm::vec4(0.30,0.30,0.30,0.90));
    scala.push_back(11.3);

    amb.push_back(glm::vec4(0.5,0.5,0.7,0.8));
    def.push_back(glm::vec4(0.18,0.17,0.23,0.8));
    spec.push_back(glm::vec4(0.33,0.33,0.35,0.8));
    scala.push_back(38.4);

    amb.push_back(glm::vec4(0.14,0.22,0.16,0.9));
    def.push_back(glm::vec4(0.54,0.89,0.63,0.9));
    spec.push_back(glm::vec4(0.32,0.32,0.32,0.9));
    scala.push_back(12.8);

    amb.push_back(glm::vec4(0.25,0.22,0.6,1.0));
    def.push_back(glm::vec4(0.35,0.31,0.9,1.0));
    spec.push_back(glm::vec4(0.8,0.72,0.21,1.0));
    scala.push_back(83.2);
    //--------------------------------------------------------------
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

    QWidget* opt6 = new QWidget;
    page6(opt6);

//    connect(opt4, SIGNAL(objectNameChanged(QString)), this, SLOT(tabChange(QString)));
//    opt4->addAction(tabChange());

    QTabWidget* m_tabs = new QTabWidget();
    m_tabs->addTab(opt2,"&Aufgabe 1");
    m_tabs->addTab(opt,"&Aufgabe 2");
    m_tabs->addTab(opt3,"&Aufagbe 3");
    m_tabs->addTab(opt4,"&Aufagbe 4");
    m_tabs->addTab(opt5,"&Aufgabe 5");
    m_tabs->addTab(opt6,"&Aufgabe 6");
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

    lab_lane_refine= new QLabel("Lane-Riesenfeld Refine");
    tab1_control->addWidget(lab_lane_refine);

    sl_rota_lane_refine = createSlider();
    tab1_control->addWidget(sl_rota_lane_refine);
    sl_rota_lane_refine->setMinimum(1);
    sl_rota_lane_refine->setMaximum(5);
    sl_rota_lane_refine->setValue(1);
    sl_rota_lane_refine->setTickInterval(1);
    connect(sl_rota_lane_refine, SIGNAL(sliderReleased()), this, SLOT(laneRotaChange()));
    connect(sl_rota_lane_refine, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_rota_refine= new QLabel("Rotationskörper Refine");
    tab1_control->addWidget(lab_rota_refine);

    sl_rota_refine = createSlider();
    tab1_control->addWidget(sl_rota_refine);
    sl_rota_refine->setMinimum(1);
    sl_rota_refine->setMaximum(360);
    sl_rota_refine->setValue(1);
    sl_rota_refine->setTickInterval(1);
    connect(sl_rota_refine, SIGNAL(sliderReleased()), this, SLOT(changeRotaKoerper()));
    connect(sl_rota_refine, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_rota_hoehe = new QLabel("Rotationskörper Hoehe");
    tab1_control->addWidget(lab_rota_hoehe);

    sl_rota_hoehe = createSlider();
    tab1_control->addWidget(sl_rota_hoehe);
    sl_rota_hoehe->setMinimum(1);
    sl_rota_hoehe->setMaximum(5);
    sl_rota_hoehe->setValue(1);
    sl_rota_hoehe->setTickInterval(1);
    connect(sl_rota_hoehe, SIGNAL(sliderReleased()), this, SLOT(changeRotaKoerper()));
    connect(sl_rota_hoehe, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    QLabel* lab9= new QLabel("----------------------------------------------------------------------------------");
    tab1_control->addWidget(lab9);

    bt_show_normal = new QPushButton("Zeige Normale");
    tab1_control->addWidget(bt_show_normal);
    bt_show_normal->setCheckable(false);
    connect(bt_show_normal, SIGNAL( clicked() ), this, SLOT(zeige_normale_taste_page2()));

    lab_Zylinder_refine = new QLabel("Zylinder Refine");
    tab1_control->addWidget(lab_Zylinder_refine);

    sl_zylinder_refine = createSlider();
    tab1_control->addWidget(sl_zylinder_refine);
    sl_zylinder_refine->setMinimum(1);
    sl_zylinder_refine->setMaximum(60);
    sl_zylinder_refine->setValue(20);
    sl_zylinder_refine->setTickInterval(1);
    connect(sl_zylinder_refine, SIGNAL(sliderReleased()), this, SLOT(changeZylinder()));
    connect(sl_zylinder_refine, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_Zylinder_radius = new QLabel("Zylinder Radius");
    tab1_control->addWidget(lab_Zylinder_radius);

    sl_zylinder_radius = createSlider();
    tab1_control->addWidget(sl_zylinder_radius);
    sl_zylinder_radius->setMinimum(0);
    sl_zylinder_radius->setMaximum(60);
    sl_zylinder_radius->setValue(20);
    sl_zylinder_radius->setTickInterval(1);
    connect(sl_zylinder_radius, SIGNAL(sliderReleased()), this, SLOT(changeZylinder()));
    connect(sl_zylinder_radius, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_Zylinder_Hoehe = new QLabel("Zylinder Hoehe");
    tab1_control->addWidget(lab_Zylinder_Hoehe);

    sl_zylinder_hoehe = createSlider();
    tab1_control->addWidget(sl_zylinder_hoehe);
    sl_zylinder_hoehe->setMinimum(0);
    sl_zylinder_hoehe->setMaximum(60);
    sl_zylinder_hoehe->setValue(20);
    sl_zylinder_hoehe->setTickInterval(1);
    connect(sl_zylinder_hoehe, SIGNAL(sliderReleased()), this, SLOT(changeZylinder()));
    connect(sl_zylinder_hoehe, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_Kegel_refine = new QLabel("Kegel Refine");
    tab1_control->addWidget(lab_Kegel_refine);

    sl_kegel_refine = createSlider();
    tab1_control->addWidget(sl_kegel_refine);
    sl_kegel_refine->setMinimum(3);
    sl_kegel_refine->setMaximum(60);
    sl_kegel_refine->setValue(20);
    sl_kegel_refine->setTickInterval(1);
    connect(sl_kegel_refine, SIGNAL(sliderReleased()), this, SLOT(changeKegel()));
    connect(sl_kegel_refine, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_Kegel_radius = new QLabel("Kegel Radius");
    tab1_control->addWidget(lab_Kegel_radius);

    sl_kegel_radius = createSlider();
    tab1_control->addWidget(sl_kegel_radius);
    sl_kegel_radius->setMinimum(0);
    sl_kegel_radius->setMaximum(60);
    sl_kegel_radius->setValue(20);
    sl_kegel_radius->setTickInterval(1);
    connect(sl_kegel_radius, SIGNAL(sliderReleased()), this, SLOT(changeKegel()));
    connect(sl_kegel_radius, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_Kegel_hoehe = new QLabel("Kegel Hoehe");
    tab1_control->addWidget(lab_Kegel_hoehe);

    sl_kegel_hoehe = createSlider();
    tab1_control->addWidget(sl_kegel_hoehe);
    sl_kegel_hoehe->setMinimum(0);
    sl_kegel_hoehe->setMaximum(60);
    sl_kegel_hoehe->setValue(20);
    sl_kegel_hoehe->setTickInterval(1);
    connect(sl_kegel_hoehe, SIGNAL(sliderReleased()), this, SLOT(changeKegel()));
    connect(sl_kegel_hoehe, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

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

    RButton1 = new QRadioButton( "&X");
    connect(RButton1, SIGNAL(pressed()), this, SLOT(selectX()));
    RButton2 = new QRadioButton( "&Y");
    connect(RButton2, SIGNAL(pressed()), this, SLOT(selectY()));
    RButton3 = new QRadioButton( "&Z");
    connect(RButton3, SIGNAL(pressed()), this, SLOT(selectZ()));


    sl_change_RotaX = new QSlider(Qt::Horizontal);
    sl_change_RotaX->setMaximum(10);
    sl_change_RotaX->setValue(0);
    sl_change_RotaX->setTickInterval(1);
    sl_change_RotaX->setVisible(false);
    connect(sl_change_RotaX, SIGNAL(sliderReleased()), this, SLOT(changeRotationPlanet()));
    connect(sl_change_RotaX, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    sl_change_RotaY = new QSlider(Qt::Horizontal);
    sl_change_RotaY->setMaximum(10);
    sl_change_RotaY->setValue(0);
    sl_change_RotaY->setTickInterval(1);
    sl_change_RotaY->setVisible(false);
    connect(sl_change_RotaY, SIGNAL(sliderReleased()), this, SLOT(changeRotationPlanet()));
    connect(sl_change_RotaY, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    sl_change_RotaZ = new QSlider(Qt::Horizontal);
    sl_change_RotaZ->setMaximum(10);
    sl_change_RotaZ->setValue(0);
    sl_change_RotaZ->setTickInterval(1);
    sl_change_RotaZ->setVisible(false);
    connect(sl_change_RotaZ, SIGNAL(sliderReleased()), this, SLOT(changeRotationPlanet()));
    connect(sl_change_RotaZ, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    myButtonGroup->addButton(RButton1,0);
    myButtonGroup->addButton(RButton2,1);
    myButtonGroup->addButton(RButton3,2);

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

    vbox->addWidget(RButton1);
    vbox->addWidget(sl_change_RotaX);

    vbox->addWidget(RButton2);
    vbox->addWidget(sl_change_RotaY);

    vbox->addWidget(RButton3);
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



void CgQtGui::page6(QWidget *parent)
{
    QVBoxLayout *tab1_control = new QVBoxLayout();

    combo_box_objekt = new QComboBox();
    combo_box_objekt->addItem("Stern");
    combo_box_objekt->addItem("Planet 1");
    combo_box_objekt->addItem("Planet 2");
    combo_box_objekt->addItem("Erde");
    combo_box_objekt->addItem("Planet 1");
    combo_box_objekt->addItem("Planet 2");
    combo_box_objekt->addItem("Planet 3");
    combo_box_objekt->setToolTip("first: select object, second: select material");
    tab1_control->addWidget(combo_box_objekt);
   // connect(combo_box_objekt, SIGNAL(activated(int)), this, SLOT(materialChanged()));


    combo_box_material = new QComboBox();
    combo_box_material->addItem("Chrom");
    combo_box_material->addItem("Perle");
    combo_box_material->addItem("Obsidian");
    combo_box_material->addItem("Jade");
    combo_box_material->addItem("Poliertes Gold");
    tab1_control->addWidget(combo_box_material);
    connect(combo_box_material, SIGNAL(activated(int)), this, SLOT(materialChanged()));

    lab_licht_rot = new QLabel("Licht Rot: 1");
    tab1_control->addWidget(lab_licht_rot);

    sl_licht_rot = createSlider();
    tab1_control->addWidget(sl_licht_rot);
    sl_licht_rot->setMinimum(1);
    sl_licht_rot->setMaximum(360);
    sl_licht_rot->setValue(5);
    connect( sl_licht_rot, SIGNAL(sliderReleased()), this, SLOT(changeLichtFarbe()));
    connect( sl_licht_rot, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_licht_gruen = new QLabel("Licht Gruen: 1");
    tab1_control->addWidget(lab_licht_gruen);

    sl_licht_gruen = createSlider();
    tab1_control->addWidget(sl_licht_gruen);
    sl_licht_gruen->setMinimum(1);
    sl_licht_gruen->setMaximum(360);
    sl_licht_gruen->setValue(5);
    connect( sl_licht_gruen, SIGNAL(sliderReleased()), this, SLOT(changeLichtFarbe()));
    connect( sl_licht_gruen, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_licht_blau = new QLabel("Licht Blau: 1");
    tab1_control->addWidget(lab_licht_blau);

    sl_licht_blau = createSlider();
    tab1_control->addWidget(sl_licht_blau);
    sl_licht_blau->setMinimum(1);
    sl_licht_blau->setMaximum(360);
    sl_licht_blau->setValue(5);
    connect( sl_licht_blau, SIGNAL(sliderReleased()), this, SLOT(changeLichtFarbe()));
    connect( sl_licht_blau, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_licht_X = new QLabel("Licht X Pos: 1");
    tab1_control->addWidget(lab_licht_X);

    sl_licht_X = createSlider();
    tab1_control->addWidget(sl_licht_X);
    sl_licht_X->setMinimum(1);
    sl_licht_X->setMaximum(360);
    sl_licht_X->setValue(5);
    connect( sl_licht_X, SIGNAL(sliderReleased()), this, SLOT(changeLichtPosition()));
    connect( sl_licht_X, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_licht_Y = new QLabel("Licht Y Pos: 1");
    tab1_control->addWidget(lab_licht_Y);

    sl_licht_Y = createSlider();
    tab1_control->addWidget(sl_licht_Y);
    sl_licht_Y->setMinimum(1);
    sl_licht_Y->setMaximum(360);
    sl_licht_Y->setValue(5);
    connect( sl_licht_Y, SIGNAL(sliderReleased()), this, SLOT(changeLichtPosition()));
    connect( sl_licht_Y, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_licht_Z = new QLabel("Licht Z Pos: 1");
    tab1_control->addWidget(lab_licht_Z);

    sl_licht_Z = createSlider();
    tab1_control->addWidget(sl_licht_Z);
    sl_licht_Z->setMinimum(1);
    sl_licht_Z->setMaximum(360);
    sl_licht_Z->setValue(5);
    connect( sl_licht_Z, SIGNAL(sliderReleased()), this, SLOT(changeLichtPosition()));
    connect( sl_licht_Z, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));


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
    s = QStringLiteral("rotations Tageswert: %1").arg(tag);
    lab_day_rota->setText(s);
    std::cout<<"erhöhe tages wert"<<std::endl;
    traeger->setAn_aus(1);
    notifyObserver(new bestersliderMoveEvent(Cg::CgChangeTageswert,traeger));
}

void CgQtGui::verringereTageswert()
{
    if(tag>=2){
    tag -= 1;
    s = QStringLiteral("rotations Tageswert: %1").arg(tag);
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

void CgQtGui::materialChanged()
{
    std::cout<<"wähle material"<<std::endl;

    traeger->setAmb(amb.at(combo_box_material->currentIndex()));
    traeger->setDef(def.at(combo_box_material->currentIndex()));
    traeger->setSpec(spec.at(combo_box_material->currentIndex()));
    traeger->setScala(scala.at(combo_box_material->currentIndex()));
    traeger->setName(combo_box_objekt->currentText());

    notifyObserver(new bestersliderMoveEvent(Cg::CgChangeMaterial,traeger));
}

void CgQtGui::changeLichtFarbe()
{
    std::cout<<"Change licht Fabre"<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_licht_rot->value(),sl_licht_gruen->value(),sl_licht_blau->value()));
    notifyObserver(new bestersliderMoveEvent(Cg::CgChangeLichtFarbe,traeger));
}

void CgQtGui::changeLichtPosition()
{
    std::cout<<"change Licht Position"<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_licht_X->value(),sl_licht_Y->value(),sl_licht_Z->value()));
    notifyObserver(new bestersliderMoveEvent(Cg::CgChangeLichtPosition,traeger));
}

void CgQtGui::reranderLabelofSlider()
{

    SuperVar = sl_licht_rot->value();
    s = QStringLiteral("Licht Rot: %1").arg(SuperVar);
    lab_licht_rot->setText(s);

    SuperVar = sl_licht_gruen->value();
    s = QStringLiteral("Licht Gruen: %1").arg(SuperVar);
    lab_licht_gruen->setText(s);

    SuperVar = sl_licht_blau->value();
    s = QStringLiteral("Licht Blau: %1").arg(SuperVar);
    lab_licht_blau->setText(s);

    SuperVar = sl_licht_X->value();
    s = QStringLiteral("Licht X Pos: %1").arg(SuperVar);
    lab_licht_X->setText(s);

    SuperVar = sl_licht_Y->value();
    s = QStringLiteral("Licht Y Pos: %1").arg(SuperVar);
    lab_licht_Y->setText(s);

    SuperVar = sl_licht_Z->value();
    s = QStringLiteral("Licht Z Pos: %1").arg(SuperVar);
    lab_licht_Z->setText(s);

    SuperVar = sl_change_RotaX->value();
    s = QStringLiteral("X: %1").arg(SuperVar);
    RButton1->setText(s);

    SuperVar = sl_change_RotaY->value();
    s = QStringLiteral("Y: %1").arg(SuperVar);
    RButton2->setText(s);

    SuperVar = sl_change_RotaZ->value();
    s = QStringLiteral("Z: %1").arg(SuperVar);
    RButton3->setText(s);

    SuperVar = sl_rota_lane_refine->value();
    s = QStringLiteral("Lane-Riesenfeld Refine: %1").arg(SuperVar);
    lab_lane_refine->setText(s);

    SuperVar = sl_rota_refine->value();
    s = QStringLiteral("Rotationskörper Refine: %1").arg(SuperVar);
    lab_rota_refine->setText(s);

    SuperVar = sl_rota_hoehe->value();
    s = QStringLiteral("Rotationskörper Hoehe: %1").arg(SuperVar);
    lab_rota_hoehe->setText(s);

    SuperVar = sl_zylinder_refine->value();
    s = QStringLiteral("Zylinder Refine: %1").arg(SuperVar);
    lab_Zylinder_refine->setText(s);

    SuperVar = sl_zylinder_radius->value();
    s = QStringLiteral("Zylinder Radius: %1").arg(SuperVar);
    lab_Zylinder_radius->setText(s);

    SuperVar = sl_zylinder_hoehe->value();
    s = QStringLiteral("Zylinder Hoehe: %1").arg(SuperVar);
    lab_Zylinder_Hoehe->setText(s);

    SuperVar = sl_kegel_refine->value();
    s = QStringLiteral("Kegel Refine: %1").arg(SuperVar);
    lab_Kegel_refine->setText(s);

    SuperVar = sl_kegel_radius->value();
    s = QStringLiteral("Kegel Radius: %1").arg(SuperVar);
    lab_Kegel_radius->setText(s);

    SuperVar = sl_kegel_hoehe->value();
    s = QStringLiteral("Kegel hoehe: %1").arg(SuperVar);
    lab_Kegel_hoehe->setText(s);
}

CgBaseRenderer* CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}
