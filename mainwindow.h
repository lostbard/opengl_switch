#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QAbstractButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::MainWindow *ui;

    void showCurrent(bool updateoption=false);
    void setCurrent(const char *name);
};
#endif // MAINWINDOW_H
