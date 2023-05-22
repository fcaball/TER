#ifndef PROCESS_H
#define PROCESS_H

#include <QString>
#include <QProcess>
#include <QStringList>
#include <QByteArray>
#include <mainwindow.h>


class Process
{
public:
    Process( MainWindow *w);

    bool reconstruction3D(QString arg1, QString arg2, QString arg3);
    bool pointcloudfinalrecale(QString arg1, QString arg2);
    bool getCaracteristique(QString arg1, QString arg2,QString path);
    bool pointCloud(QString arg1, QString arg2,QString arg3,QString arg4);
    bool correspondance(QString arg1, QString arg2,QString path);
    void endThread();

    MainWindow *w;

};

#endif // PROCESS_H
