#ifndef FILEWORKER_H
#define FILEWORKER_H
#include <QString>
#include <QFile>
#include <QTextStream>

class FileWorker
{
public:
    FileWorker();
    static QString readTextFile(QString path);
};

#endif // FILEWORKER_H
