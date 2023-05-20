#include "process.h"
#include <iostream>
#include <QThread>
Process::Process( MainWindow *w){
    this->w=w;
}


class ProcessThread : public QThread
{
public:
    ProcessThread(const QString& command, const QStringList& arguments) :
        m_command(command),
        m_arguments(arguments)
    {
    }

protected:
    void run() override
    {
        QProcess process;
        process.start(m_command, m_arguments);
        process.waitForFinished(-1);
    }

private:
    QString m_command;
    QStringList m_arguments;
};


bool Process::correspondance(QString arg1, QString arg2,QString path)
{
    std::cout<<"extraction de caractéristiques"<<std::endl;



    // Commande Python à exécuter
    QString pythonCommand = "python3";

    QStringList pythonArguments;
    pythonArguments << "/home/marie/Desktop/PCL/opencv/ptsInteret_Corres.py" << arg1 << arg2<<path<<QString::number(1);

    // Création du processus
    QProcess process;
    process.start(pythonCommand, pythonArguments);
    process.waitForFinished(-1); // Attendre la fin de l'exécution

    // Récupérer la sortie standard du processus
    return true;
}

bool Process::pointCloud(QString arg1, QString arg2,QString arg3,QString arg4)
{
    std::cout<<"point cloud"<<std::endl;

    QThread* thread = new QThread();

    // Connectez le signal started du thread à un lambda qui contient votre code
    QObject::connect(thread, &QThread::started, [=]() {
        w->setCursor(Qt::WaitCursor);
        // CORRESPONDANCE TO OFF

        //    // Commande Python à exécuter
        QString pythonCommand = "python3";

        QStringList pythonArguments;
        pythonArguments << "/home/marie/Desktop/PCL/reconstruction.py" << arg2 << arg3<<arg1+"/Points3D.off";

        // Création du processus
        QProcess process;
        process.start(pythonCommand, pythonArguments);
        process.waitForFinished(-1); // Attendre la fin de l'exécution


        // OFF TO PLY

        // Commande Python à exécuter
        QString offply = "/home/marie/Desktop/PCL/buildPCL/off_to_ply";

        QStringList offplyArguments;
        offplyArguments << arg1+"/Points3D.off" << arg1+"/Points3D.ply";

        // Création du processus
        QProcess processoffply;
        processoffply.start(offply, offplyArguments);
        processoffply.waitForFinished(-1); // Attendre la fin de l'exécution

        // PLY TO PCD

        //Commande Python à exécuter
        QString plypcd = "/home/marie/Desktop/PCL/buildPCL/ply_to_pcd";

        QStringList plypcdArguments;
        plypcdArguments << arg1+"/Points3D.ply" << arg4;

        // Création du processus
        QProcess processplypcd;
        processplypcd.start(plypcd, plypcdArguments);
        processplypcd.waitForFinished(-1); // Attendre la fin de l'exécution

        //View PCD

        QString pythonCommand1 = "/home/marie/Desktop/PCL/buildPCL/view_pcd";
        QStringList pythonArguments1;
        pythonArguments1 << arg4;

        // Création du processus
        QProcess process1;

        process1.start(pythonCommand1, pythonArguments1);
        process1.waitForFinished(-1); // Attendre la fin de l'exécution
        //w->setCursor(Qt::ArrowCursor);

        thread->quit();
    });

    // Démarrez le thread
    thread->start();
    return true;
}

bool Process::getCaracteristique(QString arg1, QString arg2,QString path)
{
    std::cout<<"extraction de caractéristiques"<<std::endl;



    // Commande Python à exécuter
    QString pythonCommand = "python3";

    QStringList pythonArguments;
    pythonArguments << "/home/marie/Desktop/PCL/opencv/ptsInteret_Corres.py" << arg1 << arg2<<path<<QString::number(0);

    // Création du processus
    QProcess process;
    process.start(pythonCommand, pythonArguments);
    process.waitForFinished(-1); // Attendre la fin de l'exécution

    // Récupérer la sortie standard du processus
    return true;
}


bool Process::reconstruction3D(QString arg1, QString arg2, QString arg3)
{

    std::cout<<"reconstruction3D"<<arg2.toStdString()<<std::endl;
    QThread* thread = new QThread();

    // Connectez le signal started du thread à un lambda qui contient votre code
    QObject::connect(thread, &QThread::started, [=]() {
        w->setCursor(Qt::WaitCursor);
        QString pythonCommand1 = "/home/marie/Desktop/PCL/buildPCL/pipeline_pcd";
        QStringList pythonArguments1;
        pythonArguments1 << arg1 << arg2<< arg3<<QString::number(1);

        // Création du processus
        QProcess process1;

        process1.start(pythonCommand1, pythonArguments1);
        process1.waitForFinished(-1); // Attendre la fin de l'exécution
        w->setCursor(Qt::ArrowCursor);

        thread->quit();
    });

    // Démarrez le thread
    thread->start();
    return true;
}

bool Process::pointcloudfinalrecale(QString arg1, QString arg2)
{
    std::cout<<"reconstruction3D"<<arg2.toStdString()<<std::endl;

    QThread* thread = new QThread();

    // Connectez le signal started du thread à un lambda qui contient votre code
    QObject::connect(thread, &QThread::started, [=]() {
        w->setCursor(Qt::WaitCursor);

        QString pythonCommand1 = "/home/marie/Desktop/PCL/buildPCL/pipeline_pcd";
        QStringList pythonArguments1;
        pythonArguments1 << arg1 << arg2 << "arg3" << QString::number(0);

        // Créez un objet QProcess pour exécuter le processus
        QProcess process;
        process.start(pythonCommand1, pythonArguments1);
        process.waitForFinished(-1);

        // Émettez le signal finished lorsque le processus est terminé (si nécessaire)
        // emit finished();

        // Arrêtez le thread lorsque le code est terminé
        w->setCursor(Qt::ArrowCursor);

        thread->quit();
    });

    // Démarrez le thread
    thread->start();
    return true;
}
