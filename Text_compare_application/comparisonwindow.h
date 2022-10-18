#ifndef COMPARISONWINDOW_H
#define COMPARISONWINDOW_H

#include "mainwindow.h"
#include "v.h"
#include <QColorDialog>
#include <QFontDialog>
#include <QDebug>

namespace Ui {
class ComparisonWindow;
}

class ComparisonWindow : public MainWindow
{
    Q_OBJECT

public:
    explicit ComparisonWindow(QWidget *parent = nullptr);
    explicit ComparisonWindow(QString filePath1 = nullptr, QString filePath2 = nullptr,
                              QWidget *parent = nullptr);
    ~ComparisonWindow();

private slots:

    void on_actionColor_triggered();

    void on_actionFont_triggered();

    void on_actionName_triggered();


private:
    Ui::ComparisonWindow *ui;

    QString filePath1, filePath2;
};

#endif // COMPARISONWINDOW_H
