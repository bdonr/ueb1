
#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "CgBase/CgEnums.h"
#include "CgEvents/CgMouseEvent.h"
#include "CgEvents/CgKeyEvent.h"
#include "CgEvents/CgWindowResizeEvent.h"
#include "CgSceneGraph/CgSceneControl.h"
#include "CgEvents/allgemeinesEvent.h"
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

//                    merke MyPolyline hat den lane riesenfeld algo !!!!
//aufgbae 6.c (o(n punkt normale berechnen))
//aufgabe 8.b vergleich der rotamatritzen implementerung
//aufgabe 14 EVENTUEL

//planeten rotations geschwindigkeit wird in



//sozusagen der eigentliche Konstruktor.
void CgQtGui::init()
{
    tag=1;

    SuperVar=1;
    //--------------------------------------------------------------
    // füllen der liste Der materialien
    amb.push_back(glm::vec4(.25f,.25f,.25f,1.0));
    def.push_back(glm::vec4(.40f,.40f,.40f,1.0));
    spec.push_back(glm::vec4(.77f,.77f,.77f,1.0));
    scala.push_back(76.8);

    amb.push_back(glm::vec4(.25f,.21f,.21f,.90f));
    def.push_back(glm::vec4(0.99f,.83f,.83f,.90f));
    spec.push_back(glm::vec4(0.30f,0.30f,0.30f,0.90f));
    scala.push_back(11.3);

    amb.push_back(glm::vec4(0.5f,0.5f,0.7f,0.8f));
    def.push_back(glm::vec4(0.18f,0.17f,0.23f,0.8f));
    spec.push_back(glm::vec4(0.33f,0.33f,0.35f,0.8f));
    scala.push_back(38.4);

    amb.push_back(glm::vec4(0.14f,0.22f,0.16f,0.9f));
    def.push_back(glm::vec4(0.54f,0.89f,0.63f,0.9f));
    spec.push_back(glm::vec4(0.32f,0.32f,0.32f,0.9f));
    scala.push_back(12.8);

    amb.push_back(glm::vec4(0.25f,0.22f,0.6f,1.0f));
    def.push_back(glm::vec4(0.35f,0.31f,0.9f,1.0f));
    spec.push_back(glm::vec4(0.8f,0.72f,0.21f,1.0f));
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

//page<zahl> sind die konstruktoen der jewaligen Tabs
void CgQtGui::page2(QWidget* parent)
{
    QVBoxLayout *tab1_control = new QVBoxLayout();
    bt_show_poly = new QPushButton("Reset Polyline");
    bt_show_poly->setCheckable(false);
    tab1_control->addWidget(bt_show_poly);
    connect(bt_show_poly, SIGNAL( clicked() ), this, SLOT(ZeigePolylineButton()));

    bt_rese_poly = new QPushButton("Hide Polyline/Rotakörper");
    tab1_control->addWidget(bt_rese_poly);
    connect(bt_rese_poly, SIGNAL( clicked() ), this, SLOT(ResetPolylineButton()));

    lab_lane_refine= new QLabel("Lane-Riesenfeld Refine (Polyline)");
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
    sl_rota_refine->setMaximum(100);
    sl_rota_refine->setValue(1);
    sl_rota_refine->setTickInterval(1);
    connect(sl_rota_refine, SIGNAL(sliderReleased()), this, SLOT(changeRotaKoerper()));
    connect(sl_rota_refine, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_rota_hoehe = new QLabel("Rotationskörper Lane-Riesenfeld");
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

    QPushButton* myButton1 = new QPushButton("Zeige Würfel");
    tab3_control->addWidget(myButton1);
    connect(myButton1, SIGNAL( clicked() ), this, SLOT(createWuerfel()) );

    QPushButton* myButton2 = new QPushButton("Zeige Normale");
    tab3_control->addWidget(myButton2);
    connect(myButton2, SIGNAL( clicked() ), this, SLOT(showWuerfelNormals()) );


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
    obj_rotate_X->setSingleStep(1);
    obj_rotate_X->setMinimum(0);
    obj_rotate_X->setMaximum(45);
    obj_rotate_X->setValue(0);
    connect( obj_rotate_X, SIGNAL(editingFinished()), this, SLOT(changeRotationObject()));
    subSBox->addWidget(obj_rotate_X);

    QLabel* lab3= new QLabel("drehung Y achse");
    subSBox->addWidget(lab3);

    obj_rotate_Y = new QSpinBox();
    tab4_control->addWidget(obj_rotate_Y);
    obj_rotate_Y->setSingleStep(1);
    obj_rotate_Y->setMinimum(0);
    obj_rotate_Y->setMaximum(45);
    obj_rotate_Y->setValue(0);
    connect( obj_rotate_Y, SIGNAL(editingFinished()), this, SLOT(changeRotationObject()));
    subSBox->addWidget(obj_rotate_Y);

    QLabel* lab4= new QLabel("drehung Z achse");
    subSBox->addWidget(lab4);

    obj_rotate_Z = new QSpinBox();
    tab4_control->addWidget(obj_rotate_Z);
    obj_rotate_Z->setSingleStep(1);
    obj_rotate_Z->setMinimum(0);
    obj_rotate_Z->setMaximum(45);
    obj_rotate_Z->setValue(0);
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
    obj_translate_X->setMinimum(0);
    obj_translate_X->setSingleStep(1);
    obj_translate_X->setMaximum(100);
    obj_translate_X->setValue(0);
    connect( obj_translate_X, SIGNAL(editingFinished()), this, SLOT(changeTranslateObject()));
    subSBox->addWidget(obj_translate_X);

    QLabel* lab32= new QLabel("bewegung Y achse");
    subSBox->addWidget(lab32);

    obj_translate_Y = new QSpinBox();
    tab4_control->addWidget(obj_translate_Y);
    obj_translate_Y->setMinimum(0);
    obj_translate_Y->setSingleStep(1);
    obj_translate_Y->setMaximum(100);
    obj_translate_Y->setValue(0);
    connect( obj_translate_Y, SIGNAL(editingFinished()), this, SLOT(changeTranslateObject()));
    subSBox->addWidget(obj_translate_Y);

    QLabel* lab42= new QLabel("bewegung Z achse");
    subSBox->addWidget(lab42);

    obj_translate_Z = new QSpinBox();
    tab4_control->addWidget(obj_translate_Z);
    obj_translate_Z->setMinimum(0);
    obj_translate_Z->setSingleStep(1);
    obj_translate_Z->setMaximum(100);
    obj_translate_Z->setValue(0);
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
    combo_box_objekt->addItem("Zylinder");
    combo_box_objekt->addItem("Kegel");
    combo_box_objekt->setToolTip("first: select object, second: select material,dotn forget to set Shading and interpolation");
    tab1_control->addWidget(combo_box_objekt);


    combo_box_material = new QComboBox();
    combo_box_material->addItem("Chrom");
    combo_box_material->addItem("Perle");
    combo_box_material->addItem("Obsidian");
    combo_box_material->addItem("Jade");
    combo_box_material->addItem("Poliertes Gold");
    combo_box_material->setToolTip("first: select object, second: select material,dotn forget to set Shading and interpolation");
    tab1_control->addWidget(combo_box_material);

    combo_box_shading = new QComboBox();
    combo_box_shading->addItem("Gouraud");
    combo_box_shading->addItem("Phong");
    combo_box_shading->setToolTip("first: select object, second: select material,dotn forget to set Shading and interpolation");
    tab1_control->addWidget(combo_box_shading);

    combo_box_interpol = new QComboBox();
    combo_box_interpol->addItem("Flat");
    combo_box_interpol->addItem("Smooth");
    combo_box_interpol->setToolTip("first: select object, second: select material,dotn forget to set Shading and interpolation");
    tab1_control->addWidget(combo_box_interpol);


    QPushButton* ButtonXY = new QPushButton("erstelle Object");
    connect(ButtonXY, SIGNAL(clicked()), this, SLOT(materialChanged()));
    tab1_control->addWidget(ButtonXY);


    licht = new QPushButton("Licht An");
    licht->setCheckable(false);
    connect(licht, SIGNAL(clicked()), this, SLOT(lightChanged()));
    tab1_control->addWidget(licht);

    lab_licht_rot = new QLabel("Licht Rot: 1");
    tab1_control->addWidget(lab_licht_rot);

    sl_licht_rot = createSlider();
    tab1_control->addWidget(sl_licht_rot);
    sl_licht_rot->setMinimum(0);
    sl_licht_rot->setMaximum(255);
    sl_licht_rot->setValue(0);
    connect( sl_licht_rot, SIGNAL(sliderReleased()), this, SLOT(changeLichtFarbe()));
    connect( sl_licht_rot, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_licht_gruen = new QLabel("Licht Gruen: 1");
    tab1_control->addWidget(lab_licht_gruen);

    sl_licht_gruen = createSlider();
    tab1_control->addWidget(sl_licht_gruen);
    sl_licht_gruen->setMinimum(0);
    sl_licht_gruen->setMaximum(255);
    sl_licht_gruen->setValue(0);
    connect( sl_licht_gruen, SIGNAL(sliderReleased()), this, SLOT(changeLichtFarbe()));
    connect( sl_licht_gruen, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_licht_blau = new QLabel("Licht Blau: 1");
    tab1_control->addWidget(lab_licht_blau);

    sl_licht_blau = createSlider();
    tab1_control->addWidget(sl_licht_blau);
    sl_licht_blau->setMinimum(0);
    sl_licht_blau->setMaximum(255);
    sl_licht_blau->setValue(0);
    connect( sl_licht_blau, SIGNAL(sliderReleased()), this, SLOT(changeLichtFarbe()));
    connect( sl_licht_blau, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_licht_X = new QLabel("Licht X Pos: 1");
    tab1_control->addWidget(lab_licht_X);

    sl_licht_X = createSlider();
    tab1_control->addWidget(sl_licht_X);
    sl_licht_X->setMinimum(0);
    sl_licht_X->setMaximum(360);
    sl_licht_X->setValue(0);
    connect( sl_licht_X, SIGNAL(sliderReleased()), this, SLOT(changeLichtPosition()));
    connect( sl_licht_X, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_licht_Y = new QLabel("Licht Y Pos: 1");
    tab1_control->addWidget(lab_licht_Y);

    sl_licht_Y = createSlider();
    tab1_control->addWidget(sl_licht_Y);
    sl_licht_Y->setMinimum(0);
    sl_licht_Y->setMaximum(360);
    sl_licht_Y->setValue(0);
    connect( sl_licht_Y, SIGNAL(sliderReleased()), this, SLOT(changeLichtPosition()));
    connect( sl_licht_Y, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));

    lab_licht_Z = new QLabel("Licht Z Pos: 1");
    tab1_control->addWidget(lab_licht_Z);

    sl_licht_Z = createSlider();
    tab1_control->addWidget(sl_licht_Z);
    sl_licht_Z->setMinimum(0);
    sl_licht_Z->setMaximum(360);
    sl_licht_Z->setValue(0);
    connect( sl_licht_Z, SIGNAL(sliderReleased()), this, SLOT(changeLichtPosition()));
    connect( sl_licht_Z, SIGNAL(sliderMoved(int)), this, SLOT(reranderLabelofSlider()));


    parent->setLayout(tab1_control);
}
//rotieren der objecte (hase, porshe, tyra)
void CgQtGui::changeRotationObject()
{
    std::cout<<"rotate obj "<<obj_rotate_X->value()<<" "<<obj_rotate_Y->value()<<" "<<obj_rotate_Z->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(obj_rotate_X->value(),obj_rotate_Y->value(),obj_rotate_Z->value()));
    notifyObserver(new allgemeinesEvent(Cg::CgObjRotate,traeger));
}
//bewegen der objecte (hase, porshe, tyra)
void CgQtGui::changeTranslateObject()
{
    std::cout<<"translate obj "<<obj_translate_X->value()<<" "<<obj_translate_Y->value()<<" "<<obj_translate_Z->value()<<std::endl;
    std::cout<<(double)obj_translate_X->value()/10<<std::endl;
    traeger->setDreiDVector(glm::vec3((double)obj_translate_X->value()/100,(double)obj_translate_Y->value()/100,(double)obj_translate_Z->value()/100));
    notifyObserver(new allgemeinesEvent(Cg::CgObjTranslate,traeger));
}
// verändern des Rotation-Körpers in refine, also rotatorische feinheit und einheit des Lane-Risenfeld algorithmus
void CgQtGui::changeRotaKoerper()
{
    std::cout<<"rotationskörper: "<<sl_rota_refine->value()<<" "<<sl_rota_hoehe->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_rota_refine->value(),sl_rota_hoehe->value(),0));
    notifyObserver(new allgemeinesEvent(Cg::CgChangeRota,traeger));
}
// anwendung des Lane. Risenfeld algo auf die polyline
void CgQtGui::laneRotaChange()
{
    std::cout<<"lane-riesenfeld refine "<<sl_rota_lane_refine->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_rota_lane_refine->value(),0,0));
    notifyObserver(new allgemeinesEvent(Cg::CgLaneRefine,traeger));
}
//ändern der farbe des würfels
void CgQtGui::changeColor()
{
    std::cout<<"farbe "<<sl_change_Red->value()<<sl_change_Green->value()<<sl_change_Blue->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_change_Red->value(),sl_change_Green->value(),sl_change_Blue->value()));
    notifyObserver(new allgemeinesEvent(Cg::CgChangeColor,traeger));
}
// zeigen und verstecken der Polyline
void CgQtGui::ZeigePolylineButton()
{
    if(bt_show_poly->isCheckable()){
        bt_show_poly->setCheckable(false);
        std::cout<<"verstecke polyline"<<std::endl;
        traeger->setAn_aus(0);
        notifyObserver(new allgemeinesEvent(Cg::CgZeigePolyline,traeger));
    }else{
        bt_show_poly->setCheckable(true);
        std::cout<<"zeige polyline"<<std::endl;
        traeger->setAn_aus(1);
        notifyObserver(new allgemeinesEvent(Cg::CgZeigePolyline,traeger));
    }
}
// zurücksetzen der polyline auf ausgangswert ohne LAne-Riesenfeld verfeinerung
void CgQtGui::ResetPolylineButton()
{
    std::cout<<"Reset Polyline"<<std::endl;
    traeger = new TraegerKlasse();
    notifyObserver(new allgemeinesEvent(Cg::CgResetPolyline,traeger));
}
//zeigen der normalen bei den Zylinder und Kegel
void CgQtGui::zeige_normale_taste_page2()
{

    if(bt_show_normal->isCheckable()){
        bt_show_normal->setCheckable(false);
        bt_show_normal->setText("Zeige Normale");
        std::cout<<"verstecke Noemale"<<std::endl;
        traeger->setAn_aus(0);
        notifyObserver(new allgemeinesEvent(Cg::CgZeigeNormalePage2,traeger));
    }else{
        bt_show_normal->setCheckable(true);
        bt_show_normal->setText("verstecke Normale");
        std::cout<<"zeige Normale"<<std::endl;
        traeger->setAn_aus(1);
        notifyObserver(new allgemeinesEvent(Cg::CgZeigeNormalePage2,traeger));
    }
}
// neu erstellung des Kegels bei veränderung von seiner Höhe/breite/rotatorische feinheit
void CgQtGui::changeKegel()
{
    std::cout<<"kegel "<<sl_kegel_hoehe->value()<<" "<<sl_kegel_radius->value()<<" "<<sl_kegel_refine->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_kegel_hoehe->value(),sl_kegel_radius->value(),sl_kegel_refine->value()));
    notifyObserver(new allgemeinesEvent(Cg::KegelChange,traeger));
}
// neu erstellung des Zylinders bei veränderung von seiner Höhe/breite/rotatorische feinheit
void CgQtGui::changeZylinder()
{
    std::cout<<"zylinder "<<sl_zylinder_hoehe->value()<<" "<<sl_zylinder_radius->value()<<" "<<sl_zylinder_refine->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_zylinder_hoehe->value(),sl_zylinder_radius->value(),sl_zylinder_refine->value()));
    notifyObserver(new allgemeinesEvent(Cg::ZylinderChange,traeger));
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
//SLOT zur änderung des Tabs
void CgQtGui::tabChange(int x)
{
    TraegerKlasse* tr = new TraegerKlasse();
    tr->setTab(x);
    allgemeinesEvent* bsl = new allgemeinesEvent(Cg::TabChange,tr);
    notifyObserver(bsl);
}
//SLOT zum Zeigen eines Sliders der X werte des Planetensystems Verändert
void CgQtGui::selectX()
{
    if(!sl_change_RotaX->isVisible()){
        sl_change_RotaX->setVisible(true);
    }else{
        sl_change_RotaX->setVisible(false);
    }
}
//SLOT zum Zeigen eines Sliders der Y werte des Planetensystems Verändert
void CgQtGui::selectY()
{
    if(!sl_change_RotaY->isVisible()){
        sl_change_RotaY->setVisible(true);
    }else{
        sl_change_RotaY->setVisible(false);
    }
}
//SLOT zum Zeigen eines Sliders der Z werte des Planetensystems Verändert
void CgQtGui::selectZ()
{
    if(!sl_change_RotaZ->isVisible()){
        sl_change_RotaZ->setVisible(true);
    }else{
        sl_change_RotaZ->setVisible(false);
    }
}
//SLOT zu vergleich der von uns berechneten matritzen und der von QT berechneten matritzen
void CgQtGui::matrizenCheck()
{
    std::cout<<"checke matritzen"<<std::endl;
    traeger = new TraegerKlasse();
    notifyObserver(new allgemeinesEvent(Cg::CgMatritzeChecken,traeger));
}
//SLOT zu änderung der rotation der planeten
void CgQtGui::changeRotationPlanet()
{
    std::cout<<"change rota page4   "<<sl_change_RotaX->value()<<" "<<sl_change_RotaY->value()<<" "<<sl_change_RotaZ->value()<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_change_RotaX->value(),sl_change_RotaY->value(),sl_change_RotaZ->value()));
    notifyObserver(new allgemeinesEvent(Cg::CgChangeRotationPlaneten,traeger));
}
//SLOT zum öffnen der objecte
void CgQtGui::objectOpenHase()
{
    std::cout<<"load Hase"<<std::endl;
    traeger->setAn_aus(0);
    notifyObserver(new allgemeinesEvent(Cg::CgChangeWahl,traeger));
}
//SLOT zum öffnen der objecte
void CgQtGui::objectOpenTyra()
{
    std::cout<<"load Tyra"<<std::endl;
    traeger->setAn_aus(1);
    notifyObserver(new allgemeinesEvent(Cg::CgChangeWahl,traeger));
}
//SLOT zum öffnen der objecte
void CgQtGui::objectOpenPorshe()
{
    std::cout<<"load Porshe"<<std::endl;
    traeger->setAn_aus(2);
    notifyObserver(new allgemeinesEvent(Cg::CgChangeWahl,traeger));
}
//SLOT zum verstecken aller GUI bestandteileder Tab 4
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
//SLOT zur erhöhung der Rotation in tageswerten
void CgQtGui::erhoeheTageswert()
{
    tag += 1;
    s = QStringLiteral("rotations Tageswert: %1").arg(tag);
    lab_day_rota->setText(s);
    std::cout<<"erhöhe tages wert"<<std::endl;
    traeger->setAn_aus(1);
    notifyObserver(new allgemeinesEvent(Cg::CgChangeTageswert,traeger));
}
//SLOT zur verringerung der Rotation in tageswerten
void CgQtGui::verringereTageswert()
{
    if(tag>=2){
    tag -= 1;
    s = QStringLiteral("rotations Tageswert: %1").arg(tag);
    lab_day_rota->setText(s);
    std::cout<<"verringere tages wert"<<std::endl;
    traeger->setAn_aus(0);
    notifyObserver(new allgemeinesEvent(Cg::CgChangeTageswert,traeger));
    }else{
        lab_day_rota->setText("weniger als 1 geht es nicht");
    }
}
//SLOT zum zeigen des Sonnensystems
void CgQtGui::zeigeSonnensystem()
{
    if(bt_show_sun->isCheckable()){
        bt_show_sun->setCheckable(false);
        bt_show_sun->setText("Zeige Sonnensystem");
        std::cout<<"verstecke sonnen system"<<std::endl;
        traeger->setAn_aus(0);
        notifyObserver(new allgemeinesEvent(Cg::CgZeigeSonnenSystem,traeger));
    }else{
        bt_show_sun->setCheckable(true);
        bt_show_sun->setText("verstecke Sonnensystem");
        std::cout<<"zeige sonnen system"<<std::endl;
        traeger->setAn_aus(1);
        notifyObserver(new allgemeinesEvent(Cg::CgZeigeSonnenSystem,traeger));
    }
}
//SLOT der die rotation der planeten startet und stoppt
void CgQtGui::startRotation()
{
    if(bt_start_rotation->isCheckable()){
        bt_start_rotation->setCheckable(false);
        bt_start_rotation->setText("Start Rotation");
        std::cout<<"beende Rotation"<<std::endl;
        traeger->setAn_aus(0);
        notifyObserver(new allgemeinesEvent(Cg::CgStartRotation,traeger));
    }else{
        bt_start_rotation->setCheckable(true);
        bt_start_rotation->setText("End Rotation");
        std::cout<<"starte rotation"<<std::endl;
        traeger->setAn_aus(1);
        notifyObserver(new allgemeinesEvent(Cg::CgStartRotation,traeger));
    }
}
//SLOT zum zeigen der bewegungsrichtungs der planeten
void CgQtGui::show3dArrow()
{
    if(bt_show_3d_arrow->isCheckable()){
        bt_show_3d_arrow->setCheckable(false);
        bt_show_3d_arrow->setText("zeige 3D Pfeile");
        std::cout<<"Verstecke 3D Pfeile"<<std::endl;
        traeger->setAn_aus(0);
        notifyObserver(new allgemeinesEvent(Cg::CgZeige3DPfeile,traeger));
    }else{
        bt_show_3d_arrow->setCheckable(true);
        bt_show_3d_arrow->setText("verstecke 3D Pfeile");
        std::cout<<"Zeige 3D Pfeile"<<std::endl;
        traeger->setAn_aus(1);
        notifyObserver(new allgemeinesEvent(Cg::CgZeige3DPfeile,traeger));
    }
}
//SLOT zum erstellen von Planeten und objecten(zylinder, kegel) mit oberflächen beschaffenheit
void CgQtGui::materialChanged()
{
    std::cout<<"wähle material"<<std::endl;

    traeger->setAmb(amb.at(combo_box_material->currentIndex()));
    traeger->setDef(def.at(combo_box_material->currentIndex()));
    traeger->setSpec(spec.at(combo_box_material->currentIndex()));
    traeger->setScala(scala.at(combo_box_material->currentIndex()));
    traeger->setName(combo_box_objekt->currentText());
    traeger->setShading(combo_box_shading->currentIndex());
    traeger->setInterpol(combo_box_interpol->currentIndex());

    notifyObserver(new allgemeinesEvent(Cg::CgChangeMaterial,traeger));
}
//SLOT zum an/ausmachen der beleuchtung
void CgQtGui::lightChanged()
{

    if(licht->isCheckable()){
        licht->setCheckable(false);
        licht->setText("Licht an");
        std::cout<<"Licht ist aus"<<std::endl;
    }else{
        licht->setCheckable(true);
        licht->setText("Licht aus");
        std::cout<<"Licht ist an"<<std::endl;

    }

    notifyObserver(new allgemeinesEvent(Cg::CgTurnLightOnOff,traeger));
}
//SLOT zum ändern des farbspektrums des lichts
void CgQtGui::changeLichtFarbe()
{
    std::cout<<"Change licht Farb"<<std::endl;
    traeger->setDreiDVector(glm::vec3((double)sl_licht_rot->value()/10,(double)sl_licht_gruen->value()/10,(double)sl_licht_blau->value()/10));
    notifyObserver(new allgemeinesEvent(Cg::CgChangeLichtFarbe,traeger));
}
//SLOT zum ändern der position des lichts
void CgQtGui::changeLichtPosition()
{
    std::cout<<"change Licht Position"<<std::endl;
    traeger->setDreiDVector(glm::vec3(sl_licht_X->value(),sl_licht_Y->value(),sl_licht_Z->value()));
    notifyObserver(new allgemeinesEvent(Cg::CgChangeLichtPosition,traeger));
}

void CgQtGui::createWuerfel()
{
    notifyObserver(new allgemeinesEvent(Cg::CgCreateWuerfel,NULL));
}

void CgQtGui::showWuerfelNormals()
{
    notifyObserver(new allgemeinesEvent(Cg::CgShowNormalsWuerfel,NULL));

}
//SLOT zur globalen anzeigen der werte der jewaligen slider
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
