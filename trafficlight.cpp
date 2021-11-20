#include "trafficlight.h"
#include <QWidget>
#include <QLayout>
#include <QRadioButton>
#include <QTimer>
#include <QApplication>



TrafficLight::TrafficLight(QWidget * parent): QWidget(parent){

    //Creatign the widgets
    createWidgets();

    //place Widgets
    placeWidgets();

    lights.append(redlight);
    lights.append(yellowlight);
    lights.append(greenlight);
    index=0;

}

void TrafficLight::createWidgets()
{

  redlight = new QRadioButton;
  redlight->setEnabled(false);
  redlight->toggle(); //activation
  redlight->setStyleSheet("QRadioButton::indicator:checked { background-color: red;}");

  yellowlight = new QRadioButton;
  yellowlight->setEnabled(false);
  yellowlight->setStyleSheet("QRadioButton::indicator:checked { background-color: yellow;}");

  greenlight = new QRadioButton;
  greenlight->setEnabled(false);
  greenlight->setStyleSheet("QRadioButton::indicator:checked { background-color: green;}");

}


void TrafficLight::placeWidgets()
{

  // Placing the widgets
  auto layout = new QVBoxLayout;
  layout->addWidget(redlight);
  layout->addWidget(yellowlight);
  layout->addWidget(greenlight);
  setLayout(layout);
  startTimer(1000);
}

void TrafficLight::timerEvent(QTimerEvent *e)
{

         index = ( index + 1)% 3;
         lights[index]->toggle();

    //si le Red est activé == Activer le Yellow

    if(redlight->isChecked())
        yellowlight->toggle();

    //si le Yellow est activé == Activer le green

    else if(yellowlight->isChecked())
        greenlight->toggle();

    //si le Green est activé == Activer le Red

    else if(greenlight->isChecked())
        redlight->toggle();


  }



 void TrafficLight::keyPressEvent(QKeyEvent *e)
 {
     if(e->key()== Qt::Key_Escape)
         qApp->exit();
     if( e->key() == Qt::Key_R)
     {
       index=0; //HIDDEN STATE
       lights[index]->toggle();


     }
     if(  e->key() == Qt::Key_Y)
     {
        index=1; //HIDDEN STATE
        lights[index]->toggle();

     }
     if(  e->key() == Qt::Key_Y)
     {
         index=2; //HIDDEN STATE
         lights[index]->toggle();

     }

 }






