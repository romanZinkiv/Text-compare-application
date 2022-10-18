#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "fileworker.h"
#include <QMainWindow>
#include <QPainter>
#include <QSettings>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
//#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_actionKing_Yna_triggered();

    void on_actionDeep_Space_triggered();

    void on_actionUkraine_triggered();

    void on_compareButton_clicked();

    void on_chooseFileButton1_clicked();

    void on_chooseFileButton2_clicked();

private:
    Ui::MainWindow *ui;

    void saveSettings();

    void loadSettings();
};
#endif // MAINWINDOW_H
