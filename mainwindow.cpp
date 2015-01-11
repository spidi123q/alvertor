#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QProcess>
#include<QtGui>
#include<QtCore>
#include "about.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

     ui->comboBox->addItem("rpm Generate a Red Hat package");
    ui->comboBox->addItem("deb Generate a Debian Ubuntu package");
    ui->comboBox->addItem("lsb more compatible package rpm");
    ui->comboBox->addItem("tgz Generate a Slackware package");
    ui->comboBox->addItem("pkg Generate a Solaris pkg package");
    ui->progressBar->setValue(0);

             QDir aln("/usr/bin/alien");
             if(!aln.isReadable())
             {
                 QMessageBox::critical(this,"no alien found on your system","this program will not work without alien\ntry to reinstall alien package");
             }













}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{


    QDir in(ui->inputfileLabel->text());
    QDir out(ui->outputfileLineEdit->text());
    QString in1=ui->inputfileLabel->text();
    QString out2=ui->outputfileLineEdit->text();

    if(in1.isEmpty()|out2.isEmpty())
    {
        ui->textEdit->clear();
        ui->textEdit->setText(" file path not found");

    }

    if (!in.isReadable()|!out.isReadable())
    {
        ui->textEdit->clear();
        ui->textEdit->setText("file path not readable");
    }




    if (in.isReadable()&out.isReadable())
     {

        if(!in1.isEmpty()&!out2.isEmpty())
        {

            QString alienpath="alien";
            QStringList argument;
            ui->textEdit->clear();
            QString pack;

            if(ui->comboBox->currentText()=="deb Generate a Debian Ubuntu package")
            {

                pack="-d";
            }
            else if(ui->comboBox->currentText()=="rpm Generate a Red Hat package")
            {

                pack="-r";
            }
            else if(ui->comboBox->currentText()=="lsb more compatible package rpm")
            {

                pack="-l";
            }
            else if(ui->comboBox->currentText()=="pkg Generate a Solaris pkg package")
            {

                pack="-p";
            }
            else if(ui->comboBox->currentText()=="tgz Generate a Slackware package")
            {
                pack="-t";
            }


            argument<<pack<<ui->inputfileLabel->text();
            QProcess *alien=new QProcess(this);
            alien->setStandardErrorFile("/home/suraj/a.txt", QIODevice::Append);

            alien->start(alienpath,argument);
            alien->setEnvironment( QProcess::systemEnvironment() );
              alien->setProcessChannelMode( QProcess::MergedChannels );
              alien->waitForStarted();
              int stat=QProcess::Running;
              if(stat==2)
              {
                  ui->textEdit->setText("alien started");
              }
              ui->progressBar->setMaximum(0);

              ui->centralWidget->setDisabled(true);


                connect( alien, SIGNAL(readyReadStandardOutput()), this, SLOT(ReadOut()) );
                connect( alien, SIGNAL(readyReadStandardError()), this, SLOT(ReadErr()) );
               connect(alien, SIGNAL(finished(int , QProcess::ExitStatus )), this, SLOT(ProcessFinish(int , QProcess::ExitStatus )));

        }
    }









}


void MainWindow::on_openfilebutton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                 tr("Open Package"), "/home", tr("Package Files (*.deb *.rpm *.pkg *.tar)"));
                              ui->inputfileLabel->setText(fileName);

}





void MainWindow::on_savebutton_clicked()
{
    QString outputfilename = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                               "",
                                                              QFileDialog::ShowDirsOnly);


   ui->outputfileLineEdit->setText(outputfilename);
   QDir::setCurrent(outputfilename);
}

void MainWindow::ReadOut()
{
    QProcess *alien = dynamic_cast<QProcess *>( sender() );

    if (alien)
      ui->textEdit->append(alien->readAll() );
}
void MainWindow::ReadErr()
{
    QProcess *alien = dynamic_cast<QProcess *>( sender() );

    if (alien)
      ui->textEdit->append(alien->readAll() );
}
void MainWindow::ProcessFinish(int , QProcess::ExitStatus )
{
    ui->progressBar->setMaximum(100);
    ui->progressBar->setValue(100);
    ui->centralWidget->setDisabled(false);
    


}



void MainWindow::on_pushButton_2_clicked()
{
    About mabout;
    mabout.setModal(true);
    mabout.exec();

}

