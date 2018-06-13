/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "../CgBase/CgObservable.h"
#include "../CgBase/CgEnums.h"
#include <QLabel>
#include <glm/glm.hpp>
#include "CgClass/traegerklasse.h"
#include <QComboBox>
#include <QRadioButton>

QT_BEGIN_NAMESPACE
class QSlider;
class QPushButton;
class QButtonGroup;
class QTabWidget;
class QTextEdit;
class QCheckBox;
class QSpinBox;
class QMenuBar;
class QAction;
QT_END_NAMESPACE

class CgQtGLRenderWidget;
class CgQtMainApplication;
class CgQtGuiEventHandler;
class CgBaseRenderer;

class CgQtGui : public QWidget,public CgObservable
{
    Q_OBJECT

public:
    CgQtGui(CgQtMainApplication *mw);
    CgBaseRenderer* getRenderer();
    void zylinderSlider();
    void kegelSlider();

    void kugelSlider();



    void init();

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;


private:
    QSlider *createSlider(int max, int min, int steps);
    QSlider *createSlider();
    // parts of the view
    CgQtGLRenderWidget*    m_glRenderWidget;
    CgQtMainApplication*        m_mainWindow;
    QTabWidget*            m_exercises_tabWidget;
    QWidget*			   m_scene_tree_view;
    QTextEdit*             m_log_browser;
    QMenuBar *             m_menuBar;

    CgQtGuiEventHandler*   m_event_handler;
    float radius;
    float hoehe;
    int refine;


    QWidget*               m_option_panel_ex1;
    QWidget*               m_option_panel_ex2;
    QWidget*               m_option_panel_ex3;
    QWidget*               m_option_panel_ex4;
    QWidget*               m_option_panel_ex5;


    /* example for usage of qt gui elements, feel free to add what you like */
    void page1(QWidget* panel);
    void page2(QWidget* panel);
    void page3(QWidget* panel);
    void page4(QWidget* panel);
    void page5(QWidget* panel);
    TraegerKlasse* traeger;
    QButtonGroup* myButtonGroup;
    QCheckBox* myCheckBox1;
    QSpinBox* mySpinBox1;

    QSlider* sl_zylinder_hoehe;
    QSlider* sl_zylinder_radius;
    QSlider* sl_zylinder_refine;

    QSlider* sl_rota_lane_refine;
    QSlider* sl_rota_refine;
    QSlider* sl_rota_hoehe;

    QSlider* sl_kegel_hoehe;
    QSlider* sl_kegel_radius;
    QSlider* sl_kegel_refine;

    QSlider * sl_change_RotaX;
    QSlider * sl_change_RotaY;
    QSlider * sl_change_RotaZ;

    QSpinBox* obj_rotate_X;
    QSpinBox* obj_rotate_Y;
    QSpinBox* obj_rotate_Z;

    QSpinBox* obj_translate_X;
    QSpinBox* obj_translate_Y;
    QSpinBox* obj_translate_Z;

    QSlider * sl_change_Red;
    QSlider * sl_change_Green;
    QSlider * sl_change_Blue;

    glm::vec3 color;

    QPushButton* bt_inc_day;
    QPushButton* bt_dec_day;
    QPushButton* bt_show_sun;
    QPushButton* bt_start_rotation;
    QPushButton* bt_show_3d_arrow;
    QPushButton* bt_vergleiche_matritzen;
    QPushButton* bt_hide_all;
    QLabel* lab_day_rota;
    QLabel* lab_matr_check;
    QPushButton* bt_show_poly;
    QPushButton* bt_rese_poly;
    QPushButton* bt_show_normal;
    QString s;
    int tag = 1;

    int SuperVar = 1;
//    int varGruen = 1;
//    int varBlau = 1;
//    int varLichtX = 1;
//    int varLichtY = 1;
//    int varLichtZ = 1;


    QComboBox* material;
    std::vector <glm::vec4> amb;
    std::vector <glm::vec4> def;
    std::vector <glm::vec4> spec;
    std::vector <double> scala;
    QSlider* sl_licht_rot;
    QSlider* sl_licht_gruen;
    QSlider* sl_licht_blau;
    QSlider* sl_licht_X;
    QSlider* sl_licht_Y;
    QSlider* sl_licht_Z;
    QLabel* lab_licht_rot;
    QLabel* lab_licht_gruen;
    QLabel* lab_licht_blau;
    QLabel* lab_licht_X;
    QLabel* lab_licht_Y;
    QLabel* lab_licht_Z;
    QRadioButton* RButton1;
    QRadioButton* RButton2;
    QRadioButton* RButton3;
    QLabel* lab_lane_refine;
    QLabel* lab_rota_refine;
    QLabel* lab_rota_hoehe;
    QLabel* lab_Zylinder_radius;
    QLabel* lab_Zylinder_refine;
    QLabel* lab_Zylinder_Hoehe;
    QLabel* lab_Kegel_refine;
    QLabel* lab_Kegel_radius;
    QLabel* lab_Kegel_hoehe;



private slots:
    void changeRotationObject();
    void changeTranslateObject();
    void changeRotaKoerper();
    void laneRotaChange();
    void changeColor(void);
    void ZeigePolylineButton();
    void ResetPolylineButton();
    void zeige_normale_taste_page2();
    void changeKegel();
    void changeZylinder();
    /* slots to catch events directly from renderer */
    void mouseEvent(QMouseEvent* event);
    void viewportChanged(int,int);
    void tabChange(int x);

    void selectX();
    void selectY();
    void selectZ();
    void matrizenCheck();
    void changeRotationPlanet();
    void objectOpenHase();
    void objectOpenTyra();
    void objectOpenPorshe();

    void hideAll();
    void erhoeheTageswert();
    void verringereTageswert();
    void zeigeSonnensystem();
    void startRotation();
    void show3dArrow();

    void materialChanged();
    void changeLichtFarbe();
    void changeLichtPosition();

    void reranderLabelofSlider();
};

#endif
