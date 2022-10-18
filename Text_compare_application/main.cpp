#include "mainwindow.h"
#include "comparisonwindow.h"
#include "fileworker.h"
#include <QApplication>



/*!
 * \brief entry point of program
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    MainWindow w;
    w.show();
    return a.exec();
}
