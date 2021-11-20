                                                                                       | 19/11/2021 |

<h1 style="color:#0B615E;  text-align:center; vertical-align: middle; padding:40px 0; margin-top:30px " > Qt Signal-and-Slots </h1>
             </br>
<h2 style="color:#0B615E;">
TOPICS :  <li>Signals.</li>
<li>Click events.</li>
<li>Mouse Events.</li>
<li>Timer events.</li>
</h2>
<h4 style="color:#088A85;">
  
Preface
  
</h4>
<p>

><strong>Signals and slots are </strong>used for communication between objects. The signals and slots mechanism is a central feature of Qt and probably the part that differs most from the features provided by other frameworks. 
>In Qt, we have an alternative to the callback technique: We use signals and slots.
><strong>A signal</strong> is emitted when a particular event occurs. Qt's widgets have many predefined signals, but we can always subclass widgets to add our own signals to them.
<strong> A slot</strong> is a function that is called in response to a particular signal. Qt's widgets have many pre-defined slots, but it is common practice to subclass widgets and add your own slots so that you can handle the signals that you are interested in.
Slots are almost idential to ordinary C++ member functions. They can be virtual, public, protected or private. They can also be directly invoked as any other C++ member functions. Also their parameters can be of any type. The main difference is that slots can be automatically connected to respond to a signal.

><strong>The goal</strong> of this report is to we simulate a traffic light and create a digital oclock using events and the QTimer. add interactive functionality to the calculator widgets that we creater  in the previous homework(Programming widgets layout). We will use Signals and Slots to simulate a basic calculator behavior.  </p>

<ul>
<h3 style="color:#58ACFA";>

<li> <a href="#Traffic-id">Traffic Light</a> </li>
<li> <a href="#digital-id">Digital oclock</a> </li>
<li> <a href="#Calcul-id">Calculator</a> </li>
</h3>
</ul>
      
------------
   <h3 style="color:#088A85" id="Traffic-id" > Traffic light </h3>
The following code is for Simulating Traffic Light using Radio Buttons.
We will investigate the code in order to underhand each component of the TrafficLight class, and we will  add some functions in order to change each 3 sedonds in the order: Red -> Green -> Yellow
<h5 style="color:#FF8000"> main class </h5>

```c++
#include <QApplication>
#include "trafficlight.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //Creating the traffic light
    auto light = new TrafficLight;


    //showing the trafic light
    light->show();

    return a.exec();
}



```
<h5 style="color:#FF8000">trafficlight.h file:</h5>


```c++
#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H
#include <QTimer>
#include <QWidget>
#include <QLabel>
#include <QVector>
#include <QKeyEvent>





class QRadioButton;

class TrafficLight: public QWidget{
  Q_OBJECT

public:

  TrafficLight(QWidget * parent = nullptr);

protected:
     void createWidgets();
     void placeWidgets();
protected:
     void timerEvent(QTimerEvent *e)override;
void keyPressEvent(QKeyEvent *e) override;





private:

  QRadioButton * redlight;
  QRadioButton * yellowlight;
  QRadioButton * greenlight;

  QVector<QRadioButton*>lights;
  int index;
  int curentTime;
};


#endif


```
<h5 style="color:#FF8000">trafficlight.cpp file:</h5>

```c++

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








 ```
<h5 style="color:#FF8000">The result:</h5>

![lightred](https://user-images.githubusercontent.com/86807424/142734446-33efcfaf-f66b-4d05-82ee-bb256edb9c24.png)

![lightyellow](https://user-images.githubusercontent.com/86807424/142734448-5deab9d6-d084-4ecb-8e1f-f7311deb0805.png)

![lightgreen](https://user-images.githubusercontent.com/86807424/142734455-626a7f84-6012-4a0f-96a6-0ae556087756.png)





   <h3 style="color:#088A85;" id="digital-id" > Digital oclock </h3>
   
   The goal of the exercice is learn to create a digital oclock with the hours, minutes and the seconds,  updated and mached with the current time.
<h5 style="color:#FF8000"> main file:</h5>

```c++
#include "digitalclock.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto D = new digitalclock;
    D-> show();
    return a.exec();
}

```

<h5 style="color:#FF8000"> digitalclock.h file:</h5>

```c++
#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include<QWidget>
#include<QLCDNumber>
#include<QTimerEvent>



class digitalclock : public QWidget
{
    Q_OBJECT

public:
   explicit digitalclock(QWidget *parent = nullptr);


protected:
    void createWidgets();
    void placeWidgets();
    void updateTime();
    void timerEvent(QTimerEvent *e) override;
private:
    QLCDNumber *hour;
    QLCDNumber *minute;
    QLCDNumber *second;
};
#endif // DIGITALCLOCK_H



```

<h5 style="color:#FF8000">digitalclock.cpp file:</h5> 


```c++

#include "digitalclock.h"
#include<QHBoxLayout>
#include<QLayout>
#include<QTime>
digitalclock::digitalclock(QWidget *parent):QWidget(parent)
{
   createWidgets();
   placeWidgets();
   updateTime();
   startTimer(1000);  //This contructor Add a timer listener each 1000 miliscons (1 second):


}
void digitalclock::createWidgets()
{
    hour= new QLCDNumber;
    hour->setDigitCount(2);
    minute=new QLCDNumber;
    minute->setDigitCount(2);
    second=new QLCDNumber;
    second->setDigitCount(2);

}
 void digitalclock::placeWidgets()
 {
     QLayout*layout = new QHBoxLayout;
     setLayout(layout);

     layout->addWidget(hour);
     layout->addWidget(minute);
     layout->addWidget(second);


 }
 //the code for the overidden function:
 void digitalclock::timerEvent(QTimerEvent *e)
 {
     updateTime();
 }

 void digitalclock::updateTime()
 {
     //obtain the actual time

     auto T = QTime::currentTime();

     //update each lcd
     hour->display(T.hour());
     minute->display(T.minute());
     second->display(T.second());


 }


```
<h5 style="color:#FF8000" >Here is the result:</h5>

![digitalclock](https://user-images.githubusercontent.com/86807424/142734223-4016f2e8-b392-4e9d-8161-e40f678f4673.png)


   <h3 style="color:#088A85;" id="Calcul-id" >Calculator</h3>
   
The exercise follows up to add interactive functionality to the calculator widgets written in the previous homework. The goal is to use Signals and Slots to simulate a basic calculator behavior. The supported operations are *, +, -, /.

 <h5 style="color:#FF8000" > main file:</h5>
 
```c++
#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    calculator w;
    w.setWindowTitle("Calculator");
    w.resize(450,300);
    w.show();
    return a.exec();
}


```
 <h5 style="color:#FF8000"> Calculator.h file: </h5>

```c++

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QLCDNumber>

class calculator : public QWidget
{
    Q_OBJECT
public:
    calculator(QWidget *parent = nullptr);
    ~calculator();
  public  slots:
 void   newDigit();
 void changeOperation();
 void showresult();
 void reset();

//void pow();
//void sqrt();
//void buttonClicked();
 //void PointClicked();
 //waitingForOperand

 //void modulo();


void newDigitCL(QKeyEvent *e);

protected:
    void createWidgets();        
    void placeWidget();         
    void makeConnexions();
    
protected:
    void keyPressEvent(QKeyEvent *e)override;     //Override the keypress events
private:
    QGridLayout *buttonsLayout; // layout for the buttons
    QVBoxLayout *layout;        //main layout for the button
    QVector<QPushButton*> digits;  //Vector for the digits
    QPushButton *enter;
    QPushButton *pow;

    QPushButton *modulo;
    QPushButton *Clear;
    QPushButton *powerButton;
    QPushButton *sqrt;
    QPushButton *pointclick;
    QVector<QPushButton*> operations; //operation buttons
    QLCDNumber *disp;// Where to display the numbers
private:
    double * leftOperand=nullptr;
    double * rightOperand=nullptr;
    QString *operation=nullptr;  // Pointer on the current operation
};
#endif // CALCULATOR_H


```

<h5 style="color:#FF8000"> Calculator.cpp :</h5>

```c++
#include "calculator.h"
#include <QKeyEvent>
#include <QApplication>
#include <qmath.h>
#include<QGridLayout>
#include<QWidget>
#include<QWidgetAction>

calculator::calculator(QWidget *parent)
    : QWidget(parent)
{
    createWidgets();
    placeWidget();
    makeConnexions();
}
calculator::~calculator()
{
    delete disp;
    delete layout;
    delete buttonsLayout;
}
void calculator::createWidgets()
{
    //Creating the layouts
    layout = new QVBoxLayout();
    layout->setSpacing(2);

    //grid layout
    buttonsLayout = new QGridLayout;


    //creating the buttons
    for(int i=0;i<=9 ;i++)
    {
        digits.push_back(new QPushButton(QString::number(i)));
        digits.back()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        digits.back()->resize(sizeHint().width(), sizeHint().height());

        digits.back()->setStyleSheet("QPushButton:enabled { background-color: rgb(154,205,50); }\n");
    }
    //clear button
    Clear = new QPushButton("ClearAll",this);
     Clear->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
     Clear->resize(sizeHint().width(), sizeHint().height());
     Clear->setStyleSheet("QPushButton:enabled { background-color: rgb(85,107,47); }\n");

    //enter button
    enter = new QPushButton("Enter",this);
    enter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    enter->resize(sizeHint().width(), sizeHint().height());
    enter->setStyleSheet("QPushButton:enabled { background-color: rgb(85,107,47); }\n");
/*    //pow button
    pow = new QPushButton("pow",this);
    pow->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
   pow->resize(sizeHint().width(), sizeHint().height());
   pow->setStyleSheet("QPushButton:enabled { background-color: rgb(85,107,47); }\n");
   //sqrt button
   sqrt = new QPushButton("Sqrt",this);
   sqrt->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
   sqrt->resize(sizeHint().width(), sizeHint().height());
   sqrt->setStyleSheet("QPushButton:enabled { background-color: rgb(85,107,47); }\n");
   //point button
  pointclick= new QPushButton(".",this);
  pointclick->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  pointclick->resize(sizeHint().width(), sizeHint().height());
  pointclick->setStyleSheet("QPushButton:enabled { background-color: rgb(85,107,47); }\n");
  //modulo button
  modulo= new QPushButton("%",this);
  modulo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  modulo->resize(sizeHint().width(), sizeHint().height());
  modulo->setStyleSheet("QPushButton:enabled { background-color: rgb(85,107,47); }\n");
*/

  //operatiosn buttons
    operations.push_back(new QPushButton("+"));
    operations.back()->setStyleSheet("QPushButton:enabled { background-color: rgb(95,158,160); }\n");

    operations.push_back(new QPushButton("-"));
    operations.back()->setStyleSheet("QPushButton:enabled { background-color: rgb(95,158,160); }\n");

    operations.push_back(new QPushButton("*"));
    operations.back()->setStyleSheet("QPushButton:enabled { background-color: rgb(95,158,160); }\n");

    operations.push_back(new QPushButton("/"));
    operations.back()->setStyleSheet("QPushButton:enabled { background-color: rgb(95,158,160); }\n");
/*
    operations.push_back(new QPushButton("%"));
    operations.back()->setStyleSheet("QPushButton:enabled { background-color: rgb(95,158,160); }\n");

    operations.push_back(new QPushButton("Sqrt"));
    operations.back()->setStyleSheet("QPushButton:enabled { background-color: rgb(95,158,160); }\n");

    operations.push_back(new QPushButton("."));
    operations.back()->setStyleSheet("QPushButton:enabled { background-color: rgb(95,158,160); }\n");
    operations.push_back(new QPushButton("^"));
    operations.back()->setStyleSheet("QPushButton:enabled { background-color: rgb(95,158,160); }\n");
*/

    //creating the lcd
    disp = new QLCDNumber(this);
    disp->setDigitCount(6);

}

void calculator::placeWidget()
{




    layout->addWidget(disp);
    layout->addLayout(buttonsLayout);
    //adding the buttons
    for(int i=1; i <10; i++)
        buttonsLayout->addWidget(digits[i], (i-1)/3, (i-1)%3);
    //Adding the operations
    for(int i=0; i < 4; i++)
        buttonsLayout->addWidget(operations[ i], i,4);
    //Adding the 0 button

    setLayout(layout);
        layout->addWidget(disp);
        layout->addLayout(buttonsLayout);
    buttonsLayout->addWidget(digits[7], 0, 1);
    buttonsLayout->addWidget(digits[8], 0, 2);
    buttonsLayout->addWidget(digits[9], 0,3);
    buttonsLayout->addWidget(digits[4], 1, 1);
    buttonsLayout->addWidget(digits[5], 1 , 2);
    buttonsLayout->addWidget(digits[6], 1, 3);
    buttonsLayout->addWidget(digits[1], 2, 1);
    buttonsLayout->addWidget(digits[2], 2, 2);
    buttonsLayout->addWidget(digits[3], 2, 3);
    buttonsLayout->addWidget(digits[0], 3, 2);
    buttonsLayout->addWidget(Clear, 3, 3 );
    buttonsLayout->addWidget(enter, 3,1);

 /* *  buttonsLayout->addWidget(pow, 0, 4);
    buttonsLayout->addWidget(sqrt, 1, 4);
    buttonsLayout->addWidget(%, 2, 4);
    buttonsLayout->addWidget(., 3, 4);
    buttonsLayout  *sqrt = buttonsLayout(tr("Sqrt"), SLOT(unaryOperatorClicked()));
    buttonsLayout *power = buttonsLayout(tr("x\302\262"), SLOT(unaryOperatorClicked()));*/




}
void calculator::makeConnexions()
{
    for(int i=0; i <10; i++)

        connect(digits[i], &QPushButton::clicked,
                this, &calculator::newDigit);
    for(int i=0; i <4; i++)

        connect(operations[i], &QPushButton::clicked,
                this, &calculator::changeOperation);
        connect(enter,&QPushButton::clicked,
                this,&calculator::showresult);
        connect(Clear,&QPushButton::clicked,
                this,&calculator::reset);
}

/* void Calculator::pointClicked()
{
 if (waitingForOperand)
     disp->setText("0");
 if (!disp->text().contains('.'))
     display->setText(display->text() + tr("."));
 waitingForOperand = false;
}*/

void calculator::newDigitCL(QKeyEvent *e )
{


    //getting the value
    double value = e->text().toInt();
    //Check if we have an operation defined
            if(!leftOperand)
                leftOperand = new double{value};
            else
                *leftOperand = 10 * (*leftOperand) + value;
            disp->display(value);
        }
void calculator::newDigit( )
{
   //getting the sender
    auto button = dynamic_cast<QPushButton*>(sender());
    //getting the value
    double value = button->text().toInt();
    //Check if we have an operation defined
      if(operation)
   {
        //check if we have a value or not
      if(!rightOperand)
        rightOperand = new double{value};
      else
         *rightOperand = 10 * (*rightOperand) + value;
       disp->display(*rightOperand);
   }
      else
   {
      if(!leftOperand)
       leftOperand = new double{value};
       else
        *leftOperand = 10 * (*leftOperand) + value;
       disp->display(*leftOperand);
   }

}
void calculator::changeOperation()
{

    auto button = dynamic_cast<QPushButton*>(sender()); //Get the sender button


    operation = new QString{button->text()}; //Store operation


    rightOperand = new double{0.0}; //Initiate the right button


    disp->display("cal");     // the display while operation
}
void calculator::showresult(){
    //Getting the sender button
    auto button = dynamic_cast<QPushButton*>(sender());
    //Storing the operation
   enter = new QPushButton{button};
 if(*operation=="+")
 {
     disp->display(*leftOperand+(*rightOperand));
     *leftOperand= *leftOperand+(*rightOperand);
 }
 else if(*operation=="-")
 {
     disp->display(*leftOperand-(*rightOperand));
     *leftOperand= *leftOperand-(*rightOperand);
 }
else if(*operation=="*")
 {
     disp->display(*leftOperand*(*rightOperand));
     *leftOperand= *leftOperand*(*rightOperand);
 }
else  if(*operation=="/")
 {
     if(*rightOperand==0)
         disp->display("sytax error");
     else
         disp->display(*leftOperand/(*rightOperand));
         *leftOperand= *leftOperand/(*rightOperand);
 }
else  disp->display(*leftOperand);


/*
  if(*operation=="sqrt")
 {
     disp->display(*leftOperand sqrt(*rightOperand));
     *leftOperand= *leftOperand sqrt((*rightOperand));
 }
 if(*operation=="%")
 {
     disp->display(*leftOperand%(*rightOperand));
     *leftOperand= *leftOperand%((*rightOperand));
 }
 if(*operation=="pow")
 {
     disp->display(*leftOperand pow(*rightOperand));
     *leftOperand= *leftOperand pow(*rightOperand);
 }
 if(*operation==".")
 {
     disp->display(*leftOperand.(*rightOperand));
     *leftOperand= *leftOperand.(*rightOperand);
 } */
}


void calculator::reset()
{
    rightOperand = new double{0.0};
    leftOperand = new double{0.0};
    operation=nullptr;
    disp->display(0);
}


void calculator::keyPressEvent(QKeyEvent *e)
{
    //Exiting the application by a click on space
    if( e->key() == Qt::Key_Escape)
        qApp->exit(0);
    if( e->key() == Qt::Key_1)
        newDigitCL(e);
    if( e->key() == Qt::Key_2)
        newDigitCL(e);
    if( e->key() == Qt::Key_3)
        newDigitCL(e);
    if( e->key() == Qt::Key_4)
       newDigitCL(e);
    if( e->key() == Qt::Key_5)
        newDigitCL(e);
    if( e->key() == Qt::Key_6)
        newDigitCL(e);
    if( e->key() == Qt::Key_7)
        newDigitCL(e);
    if( e->key() == Qt::Key_8)
        newDigitCL(e);
    if( e->key() == Qt::Key_9)
        newDigitCL(e);
    if( e->key() == Qt::Key_0)
        newDigitCL(e);
}


```

<h5 style="color:#FF8000">result :</h5>

![Capture d’écran 2021-11-20 181403](https://user-images.githubusercontent.com/86807424/142735468-4c269d8a-e2ce-4503-ac96-02c05b9ceb4a.png)


------------
<h3 style="color:#088A85"; > Wrap up </h3>
  
  
>In this chapter,we  dived deeper in the the signal and slots mecansim to create a calculator.
we have seen the mecanism of creating widgetscomponents, make connexion between them using the concept of signals ans slots. We have seen  the gridlayout, which is an alternative to the box layout and default widget positining, In addition to the functions click events ,mouse events, timer events.

--------
 
<h4 style="background-color:#F6CEF5" > By: OUMKOULTHOUME BOUNOUA </h4>
  
  </div>
