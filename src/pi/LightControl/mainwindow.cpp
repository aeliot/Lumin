#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../MPR121/mpr121.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CapaTouch.begin();
    while(true){
        dial();
    }
}


void MainWindow::dial(){
        int val;
        key=CapaTouch.wheelKey();
        if(key>0 && key!=keyOld){
            if(keyOld>0 && (key > keyOld || (keyOld == 16 && key == 1)) && !(keyOld == 1 && key == 16)){
                val = ui->dialMaster->value();
                if(val != 99){
                    val++;
                }

                ui->dialMaster->setValue(val);
            }
        } else if(keyOld>0 && (key < keyOld || (keyOld == 1 && key == 16))){
            val = ui->dialMaster->value();
            if(val != 0){
                val--;
            }

            ui->dialMaster->setValue(val);
        }
        keyOld = key;

}

MainWindow::~MainWindow()
{
    delete ui;
}

