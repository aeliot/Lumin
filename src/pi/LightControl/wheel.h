#ifndef WHEEL_H
#define WHEEL_H

#include <QObject>
#include <../MPR121/mpr121.h>

class Wheel : public QObject
{
    Q_OBJECT
public:
    explicit Wheel(QObject *parent = 0);
    
signals:
    void increase();
    void decrease();
    void select();
    
public slots:
private:
    int keyNew;
    int keyOld;
    
};

#endif // WHEEL_H
