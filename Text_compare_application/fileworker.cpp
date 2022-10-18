#include "fileworker.h"

FileWorker::FileWorker()
{

}
/*!
 * \brief read text from given path
 * \param path address of the desired file
 * \return returns the contents of the file
 */
QString FileWorker::readTextFile(QString path)
{
    QFile file(path);

    if  (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        return in.readAll();
    }

    return "";
}

//background-color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:0, stop:0 rgba(66, 39, 90, 255), stop:1 rgba(115, 75, 109, 255));
