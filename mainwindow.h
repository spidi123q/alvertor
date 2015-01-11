#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QString>
#include<QtCore>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow(QWidget *parent = 0);
    QProcess *alien;

    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();

    void on_openfilebutton_clicked();



    void on_savebutton_clicked();

    void ReadOut();

    void ReadErr();


    void ProcessFinish(int , QProcess::ExitStatus );


    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;



};

#endif // MAINWINDOW_H
