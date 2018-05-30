
#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "../CgBase/CgEnums.h"
#include "../CgEvents/CgMouseEvent.h"
#include "../CgEvents/CgKeyEvent.h"
#include "../CgEvents/CgWindowResizeEvent.h"
#include "../CgSceneGraph/CgSceneControl.h"
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



CgQtGui::CgQtGui(CgQtMainApplication *mw)
    : m_mainWindow(mw),radius(0.0),hoehe(0.0),refine(0)
{

    color = glm::vec3(0,0,0);
    m_glRenderWidget = new CgQtGLRenderWidget;

    connect(m_glRenderWidget, SIGNAL(mouseEvent(QMouseEvent*)), this, SLOT(mouseEvent(QMouseEvent*)));
    connect(m_glRenderWidget, SIGNAL(viewportChanged(int,int)), this, SLOT(viewportChanged(int,int)));
    //  connect(m_glRenderWidget, SIGNAL(valueChanged(int)), this, SLOT(sliderMove(int)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;

    QWidget *opt = new QWidget;
    aufgabe2(opt);

    QWidget *opt2 = new QWidget;
    page1(opt2);

    QWidget* opt3 = new QWidget;
    page2(opt3);

    QWidget* opt4 = new QWidget;
    page3(opt4);
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
    slider->setTickInterval(1);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;

}


void CgQtGui::aufgabe2(QWidget* parent)
{
    QVBoxLayout *tab1_control = new QVBoxLayout();



    QPushButton* myButton2 = new QPushButton("Zeige Polyline");
    tab1_control->addWidget(myButton2);
    connect(myButton2, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()) );

    QLabel* lab7= new QLabel("RotationsKörper Refine");
    tab1_control->addWidget(lab7);

    QSlider *RotationsSlider = createSlider();
    tab1_control->addWidget(RotationsSlider);
    RotationsSlider->setMinimum(3);
    RotationsSlider->setMaximum(60);
    RotationsSlider->setValue(20);
    RotationsSlider->setTickInterval(1);
    connect(RotationsSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeRefineRota(int)));

    QLabel* lab8= new QLabel("RotationsKörper Hoehe");
    tab1_control->addWidget(lab8);

    QSlider *HoeheSlider = createSlider();
    tab1_control->addWidget(HoeheSlider);
    HoeheSlider->setMinimum(1);
    HoeheSlider->setMaximum(60);
    HoeheSlider->setValue(20);
    HoeheSlider->setTickInterval(1);
    //  connect(RotationsSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeHoeheZylinder(int)));


    QLabel* lab9= new QLabel("----------------------------------------------------------------------------------");
    tab1_control->addWidget(lab9);

    QPushButton* myButton1 = new QPushButton("Zeige Normale");
    tab1_control->addWidget(myButton1);
    connect(myButton1, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()) );

    QLabel* lab1= new QLabel("Zylinder Hoehe");
    tab1_control->addWidget(lab1);

    QSlider *zylinderHoeheSlider = createSlider();
    tab1_control->addWidget(zylinderHoeheSlider);
    zylinderHoeheSlider->setMinimum(0);
    zylinderHoeheSlider->setMaximum(60);
    zylinderHoeheSlider->setValue(20);
    zylinderHoeheSlider->setTickInterval(1);
    connect(zylinderHoeheSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeHoeheZylinder(int)));

    QLabel* lab2= new QLabel("Zylinder Radius");
    tab1_control->addWidget(lab2);

    QSlider *zylinderRadiusSlider = createSlider();
    tab1_control->addWidget(zylinderRadiusSlider);
    zylinderRadiusSlider->setMinimum(0);
    zylinderRadiusSlider->setMaximum(60);
    zylinderRadiusSlider->setValue(20);
    zylinderRadiusSlider->setTickInterval(1);
    connect(zylinderRadiusSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeRadiusZylinder(int)));

    QLabel* lab3= new QLabel("Zylinder Refine");
    tab1_control->addWidget(lab3);

    QSlider *zylinderRefineSlider = createSlider();
    tab1_control->addWidget(zylinderRefineSlider);
    zylinderRefineSlider->setMinimum(1);
    zylinderRefineSlider->setMaximum(60);
    zylinderRefineSlider->setValue(20);
    zylinderRefineSlider->setTickInterval(1);
    connect(zylinderRefineSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeRefineZylinder(int)));

    QLabel* lab4= new QLabel("Kegel Refine");
    tab1_control->addWidget(lab4);

    QSlider *kegelRefineSlider = createSlider();
    tab1_control->addWidget(kegelRefineSlider);
    kegelRefineSlider->setMinimum(3);
    kegelRefineSlider->setMaximum(60);
    kegelRefineSlider->setValue(20);
    kegelRefineSlider->setTickInterval(1);
    connect(kegelRefineSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeRefineKegel(int)));

    QLabel* lab5= new QLabel("Kegel Radius");
    tab1_control->addWidget(lab5);

    QSlider *kegelRadiusSlider = createSlider();
    tab1_control->addWidget(kegelRadiusSlider);
    kegelRadiusSlider->setMinimum(0);
    kegelRadiusSlider->setMaximum(60);
    kegelRadiusSlider->setValue(20);
    kegelRadiusSlider->setTickInterval(1);
    connect(kegelRadiusSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeRadiusKegel(int)));

    QLabel* lab6= new QLabel("Kegel Hoehe");
    tab1_control->addWidget(lab6);

    QSlider *kegelHoeheSlider = createSlider();
    tab1_control->addWidget(kegelHoeheSlider);
    kegelHoeheSlider->setMinimum(0);
    kegelHoeheSlider->setMaximum(60);
    kegelHoeheSlider->setValue(20);
    kegelHoeheSlider->setTickInterval(1);
    connect(kegelHoeheSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeHoeheKegel(int)));



    QLabel* lab10= new QLabel("Kugel Refine");
    tab1_control->addWidget(lab10);

    QSlider *kugelRefineSlider = createSlider();
    tab1_control->addWidget(kugelRefineSlider);
    kugelRefineSlider->setMinimum(3);
    kugelRefineSlider->setMaximum(60);
    kugelRefineSlider->setValue(20);
    kugelRefineSlider->setTickInterval(1);
    connect(kugelRefineSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeRefineKugel(int)));

    QLabel* lab11= new QLabel("Kugel Radius");
    tab1_control->addWidget(lab11);

    QSlider *kugelRadiusSlider = createSlider();
    tab1_control->addWidget(kugelRadiusSlider);
    kugelRadiusSlider->setMinimum(0);
    kugelRadiusSlider->setMaximum(60);
    kugelRadiusSlider->setValue(20);
    kugelRadiusSlider->setTickInterval(1);
    connect(kugelRadiusSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeRadiusKugel(int)));

    QLabel* lab12= new QLabel("Kugel Hoehe");
    tab1_control->addWidget(lab12);

    QSlider *kugelHoeheSlider = createSlider();
    tab1_control->addWidget(kugelHoeheSlider);
    kugelHoeheSlider->setMinimum(0);
    kugelHoeheSlider->setMaximum(60);
    kugelHoeheSlider->setValue(20);
    kugelHoeheSlider->setTickInterval(1);
    connect(kugelHoeheSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeHoeheKugel(int)));





    parent->setLayout(tab1_control);

}

void CgQtGui::createOptionPanelExample2(QWidget* parent)
{


    QVBoxLayout *tab2_control = new QVBoxLayout();
    QHBoxLayout *subBox = new QHBoxLayout();

    /*Example for using a label */

    QLabel *options_label = new QLabel("Options");
    tab2_control->addWidget(options_label);
    options_label->setAlignment(Qt::AlignCenter);


    /*Example for using a spinbox */

    mySpinBox1 = new QSpinBox();
    tab2_control->addWidget(mySpinBox1);
    mySpinBox1->setMinimum(1);
    mySpinBox1->setMaximum(50);
    mySpinBox1->setValue(3);
    // mySpinBox1->setSuffix("   suffix");
    // mySpinBox1->setPrefix("Prefix:  ");
    connect(mySpinBox1, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );
    tab2_control->addWidget(mySpinBox1);

    /*Example for using a checkbox */

    myCheckBox1 = new QCheckBox("enable Option 1");
    myCheckBox1->setCheckable(true);
    myCheckBox1->setChecked(false);
    connect(myCheckBox1, SIGNAL( clicked() ), this, SLOT(slotMyCheckBox1Changed()) );
    tab2_control->addWidget(myCheckBox1);


    /*Example for using a button */

    QPushButton* myButton1 = new QPushButton("&drueck mich");
    tab2_control->addWidget(myButton1);

    connect(myButton1, SIGNAL( clicked() ), this, SLOT(slotMyButton1Pressed()) );

    /*Example for using a button group */

    QGroupBox* myGroupBox = new QGroupBox("Radiobutton Group Example ");

    myButtonGroup = new QButtonGroup(subBox);
    myButtonGroup->setExclusive(true);

    QRadioButton* radiobutton1 = new QRadioButton( "&Option1");
    QRadioButton* radiobutton2 = new QRadioButton( "&Option2");
    QRadioButton* radiobutton3 = new QRadioButton( "&Option3");
    QRadioButton* radiobutton4 = new QRadioButton( "&Option4");
    QRadioButton* radiobutton5 = new QRadioButton( "&Option5");
    QRadioButton* radiobutton6 = new QRadioButton( "&Option6");

    radiobutton2->setChecked(true);

    myButtonGroup->addButton(radiobutton1,0);
    myButtonGroup->addButton(radiobutton2,1);
    myButtonGroup->addButton(radiobutton3,2);
    myButtonGroup->addButton(radiobutton4,3);
    myButtonGroup->addButton(radiobutton5,4);
    myButtonGroup->addButton(radiobutton6,5);


    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobutton1);
    vbox->addWidget(radiobutton2);
    vbox->addWidget(radiobutton3);
    vbox->addWidget(radiobutton4);
    vbox->addWidget(radiobutton5);
    vbox->addWidget(radiobutton6);
    vbox->addStretch(1);
    myGroupBox->setLayout(vbox);
    subBox->addWidget(myGroupBox);
    tab2_control->addLayout(subBox);

    connect(myButtonGroup, SIGNAL( buttonClicked(int) ), this, SLOT( slotButtonGroupSelectionChanged() ) );
    parent->setLayout(tab2_control);

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
     connect(sl_change_Red, SIGNAL(sliderMoved(int)), this, SLOT(changeColor()));


    QLabel* lab3= new QLabel("Gruen");
    tab3_control->addWidget(lab3);

    sl_change_Green = createSlider();
    tab3_control->addWidget(sl_change_Green);
    sl_change_Green->setMinimum(0);
    sl_change_Green->setMaximum(255);
    sl_change_Green->setValue(20);
    sl_change_Green->setTickInterval(4);
    connect(sl_change_Green, SIGNAL(sliderMoved(int)), this, SLOT(changeColor()));
    //connect(zylinderRadiusSlider, SIGNAL(sliderMoved(int)), this, SLOT(ÄNDERE FARBE));

    QLabel* lab4= new QLabel("Blau");
    tab3_control->addWidget(lab4);
    sl_change_Blue = createSlider();
    tab3_control->addWidget(sl_change_Blue);
    sl_change_Blue->setMinimum(3);
    sl_change_Blue->setMaximum(255);
    sl_change_Blue->setValue(20);
    sl_change_Blue->setTickInterval(4);
    connect(sl_change_Blue, SIGNAL(sliderMoved(int)), this, SLOT(changeColor()));
    //connect(zylinderRefineSlider, SIGNAL(sliderMoved(int)), this, SLOT(ÄNDERE FARBE));


    parent->setLayout(tab3_control);


}
void CgQtGui::page2(QWidget* parent)
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
    QGroupBox* mySpinnerBox = new QGroupBox("figur drehen ");
    QHBoxLayout* SBox = new QHBoxLayout;
    mySpinnerBox->setLayout(SBox);

    QVBoxLayout *subSBox = new QVBoxLayout();
    subSBox->addWidget(mySpinnerBox);
    tab4_control->addLayout(subSBox);


    QLabel* lab2= new QLabel("drehung X achse");
    subSBox->addWidget(lab2);

    QSpinBox* spin1 = new QSpinBox();
    tab4_control->addWidget(spin1);
    spin1->setMinimum(1);
    spin1->setMaximum(50);
    spin1->setValue(1);
    // spin1->setSuffix("   suffix");
    // mySpinBox1->setPrefix("Prefix:  ");
    connect( spin1, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );
    subSBox->addWidget(spin1);

    QLabel* lab3= new QLabel("drehung Y achse");
    subSBox->addWidget(lab3);

    QSpinBox* spin2 = new QSpinBox();
    tab4_control->addWidget(spin2);
    spin2->setMinimum(1);
    spin2->setMaximum(50);
    spin2->setValue(1);
    // spin1->setSuffix("   suffix");
    // mySpinBox1->setPrefix("Prefix:  ");
    connect( spin2, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );
    subSBox->addWidget(spin2);

    QLabel* lab4= new QLabel("drehung Z achse");
    subSBox->addWidget(lab4);

    QSpinBox* spin3 = new QSpinBox();
    tab4_control->addWidget(spin3);
    spin3->setMinimum(1);
    spin3->setMaximum(50);
    spin3->setValue(1);
    // spin1->setSuffix("   suffix");
    // mySpinBox1->setPrefix("Prefix:  ");
    connect( spin3, SIGNAL(valueChanged(int) ), this, SLOT(slotMySpinBox1Changed()) );
    subSBox->addWidget(spin3);

    QLabel* lab1= new QLabel("zoom mit +/- \n drehen mit y/x/z");
    tab4_control->addWidget(lab1);
    parent->setLayout(tab4_control);

}

void CgQtGui::page3(QWidget* parent)
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

void CgQtGui::changeColor()
{
    std::cout<<sl_change_Blue->value()<<std::endl;
}

void CgQtGui::changeRefineKugel(int x)
{

}

void CgQtGui::changeRadiusKugel(int x)
{

}

void CgQtGui::changeHoeheKugel(int x)
{

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


CgBaseRenderer* CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}






void changeColor(void){

}

