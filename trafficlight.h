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
