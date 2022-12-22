#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showCurrent(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showCurrent(bool updateoption)
{
  QString path = qApp->applicationDirPath();

  QFile oglbak(QString("%1/opengl32.bak").arg(path));
  QFile ogl(QString("%1/opengl32.dll").arg(path));
  const char * name;

  if (! ogl.exists())
    name = "system";
  else
    name = "software";

  ui->currentText->setText(QString("Current: %1 OpenGL").arg(name));

  if(updateoption)
    {
      if (QString(name) == "system")
        ui->systemOption->setChecked(true);
      if (QString(name) == "software")
          ui->softwareOption->setChecked(true);
    }
}

void MainWindow::setCurrent(const char *name)
{
  QString path = qApp->applicationDirPath();

  QFile oglbak(QString("%1/opengl32.bak").arg(path));
  QFile ogl(QString("%1/opengl32.dll").arg(path));

  if (QString(name) == "software")
    {
      if (!ogl.exists())
        {
          if (!oglbak.exists())
	    {
              QMessageBox msgBox;
              msgBox.setText("Failed to find opengl files");
              msgBox.setIcon(QMessageBox::Critical);
              msgBox.setInformativeText(QString("opengl32.bak"));
              msgBox.setStandardButtons(QMessageBox::Ok);
              msgBox.exec();
	    }
          else
            {
              if (ogl.open(QIODevice::WriteOnly|QIODevice::Truncate) == false ||
                  oglbak.open(QIODevice::ReadOnly) == false)
	        {
                  QMessageBox msgBox;
                  msgBox.setText("Failed to open opengl files");
                  msgBox.setIcon(QMessageBox::Critical);
                  if(ogl.error() != QFileDevice::NoError)
                    msgBox.setInformativeText(ogl.errorString());
                  else
                    msgBox.setInformativeText(oglbak.errorString());

                  msgBox.setStandardButtons(QMessageBox::Ok);
                  msgBox.exec();
 
	        }
	      else
	        {
                  char buff[1024];
                  qint64 sz = oglbak.read(buff, sizeof(buff));
                  qint64 wsz = 0;
                  while (sz > 0 && wsz >= 0)
                    {
                      wsz = ogl.write(buff, sz);

                      sz = oglbak.read(buff, sizeof(buff));
                    }
                  if(wsz < 0)
                    {
                      QMessageBox msgBox;
                      msgBox.setText("Failed to write to opengl file");
                      msgBox.setIcon(QMessageBox::Critical);
                      msgBox.setInformativeText(ogl.errorString());
                      msgBox.setStandardButtons(QMessageBox::Ok);
                      msgBox.exec();
                    }
                }

              ogl.close();
              oglbak.close();
	    }
        }
    }
  else
    {
      if (ogl.exists())
        {
          if (oglbak.open(QIODevice::WriteOnly|QIODevice::Truncate) == false ||
                ogl.open(QIODevice::ReadOnly) == false)
	    {
              QMessageBox msgBox;
              msgBox.setText("Failed to open opengl32 files");
              msgBox.setIcon(QMessageBox::Critical);
              if(ogl.error() != QFileDevice::NoError)
                msgBox.setInformativeText(ogl.errorString());
              else
                msgBox.setInformativeText(oglbak.errorString());

              msgBox.setStandardButtons(QMessageBox::Ok);
              msgBox.exec();

            }
          else
            {
              char buff[1024];
              qint64 sz = ogl.read(buff, sizeof(buff));
              qint64 wsz = 0;
              while (sz > 0 && wsz >= 0)
                {
                  wsz = oglbak.write(buff, sz);

                  sz = ogl.read(buff, sizeof(buff));
                }

              if(wsz < 0)
                {
                  QMessageBox msgBox;
                  msgBox.setText("Failed to write to opengl files");
                  msgBox.setIcon(QMessageBox::Critical);
                  msgBox.setInformativeText(oglbak.errorString());
                  msgBox.setStandardButtons(QMessageBox::Ok);
                  msgBox.exec();
                }
            }

          ogl.close();
          oglbak.close();
      }
  }

  showCurrent(true);
}

void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
{
    qDebug("pressed %s", button->text().toUtf8().data());
    if(ui->buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole)
    {
      if(ui->systemOption->isChecked())
      {
        setCurrent("system");
      }
      else if(ui->softwareOption->isChecked())
      {
        setCurrent("software");
      }
    }
    else if(ui->buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
    {
      close();
    }
}
