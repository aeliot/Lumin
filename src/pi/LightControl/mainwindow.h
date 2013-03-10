#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void dial();
    ~MainWindow();
    
private slots:

private:
    Ui::MainWindow *ui;
    int key;
    int keyOld;
};

#endif // MAINWINDOW_H
