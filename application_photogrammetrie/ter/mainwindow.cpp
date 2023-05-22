#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileSystemModel>
#include <QPixmap>
#include <QVariant>
#include <QMessageBox>
#include <QString>
#include <QLabel>
#include <iostream>
#include <QSize>
#include <QImageReader>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <process.h>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->checkBox->setVisible(false);
    image_checker=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
}

void MainWindow::on_actionOpen_folder_triggered()
{
    PATH = QFileDialog::getExistingDirectory(this, tr("Open directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    QFileSystemModel *Dossier = new QFileSystemModel;
    Dossier->setRootPath(PATH);
    ui->treeView->setModel(Dossier);
    ui->treeView->setRootIndex(Dossier->index(PATH));
    this->currentDirectory=PATH;
    ui->treeView->setColumnWidth(0,200);
}

void MainWindow::renderImage(){
    setImage(image_directory[i]);
    namePicture=image_directory[i].split("/").back();
}

void MainWindow::infoImage(){
    ui->infosimage->setText("");
    setImageInfos(image_directory[i]);
}

void MainWindow::setImage(QString chemin){
    QPixmap *image = new QPixmap(chemin);
    ui->imagespace->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->imagespace->setPixmap(image->scaled(ui->imagespace->width(), ui->imagespace->height(), Qt::KeepAspectRatio));
    if(std::count(ImagesSelectedForCorrespondance.begin(), ImagesSelectedForCorrespondance.end(), chemin)==0){
        ui->checkBox->setChecked(false);
    }else{
        ui->checkBox->setChecked(true);
    }
}

void MainWindow::start_animation(){
    QPixmap image = temp_directory;
    ui->sliderholder->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->sliderholder->setPixmap(image.scaled(ui->imagespace->width(), ui->imagespace->height(), Qt::KeepAspectRatio));

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
    QPropertyAnimation *anim = new QPropertyAnimation(effect, "opacity");

    ui->imagespace->setGraphicsEffect(effect);
    anim->setDuration(anim_period*1000);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    connect(anim, &QPropertyAnimation::finished, [=](){});
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::end_animation(){
    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect();
    QPropertyAnimation *anim = new QPropertyAnimation(effect, "opacity");

    ui->sliderholder->setGraphicsEffect(effect);
    anim->setDuration(anim_period*1000);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    connect(anim, &QPropertyAnimation::finished, [=](){});
    anim->start(QAbstractAnimation::DeleteWhenStopped);

}


void MainWindow::setImageInfos(QString chemin){
    QImageReader imagereader(chemin);
    QString format(imagereader.format());
    QString name(imagereader.fileName());
    QSize size = imagereader.size();
    QString width = QString::number(size.width());
    QString height = QString::number(size.height());
    ui->infosimage->setStyleSheet("QLabel { background-color : lightgrey; color : black; }");
    ui->infosimage->setText(ui->infosimage->text() + "Nom : " + chemin + "\nType : " + format + "\nWidth : " + width + "\nHeight : " + height);
}

void MainWindow::previous_image(){
    if (image_checker)
    {
        temp_directory = image_directory[i];
        if (i == 0)
        {
            i = count - 1;
        }
        else
        {
            i--;
        }

        renderImage();
        infoImage();

    }
}

void MainWindow::next_image(){
    if (image_checker)
    {
        temp_directory = image_directory[i];

        if (i == count - 1)
        {
            i = 0;
        }
        else
        {
            i++;
        }
        renderImage();
        infoImage();

    }
}


void MainWindow::on_slideleft_clicked()
{


    previous_image();


}

void MainWindow::on_slideright_clicked()
{

    next_image();

}



void MainWindow::on_actionZoom_triggered()
{
    QMessageBox::information(this, "title", "Zoom forward");
}

void MainWindow::on_actionZoom_2_triggered()
{
    QMessageBox::information(this, "title", "Zoom backward");
}

void MainWindow::updatePictures(QString s1)
{

    ui->imagespace->setVisible(true);
    ui->checkBox->setVisible(true);
    ui->slideleft->setVisible(true);
    ui->slideright->setVisible(true);

    ui->infosimage->setVisible(true);

    namePicture = s1.split("/").back();
    ui->infosimage->setText("");
    setImageInfos(s1);
    setImage(s1);

}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    ui->imagespace->setVisible(true);
    ui->checkBox->setVisible(true);
    ui->infosimage->setVisible(true);
    ui->slideleft->setVisible(true);
    ui->slideright->setVisible(true);

    image_checker = false;
    count = 0;
    QDir path(PATH);
    QStringList imagesPath = path.entryList(QStringList() << "*.jpg" << "*.jpeg" << "*.bmp" << "*.pbm" << "*.pgm" << "*.ppm" << "*.xbm" << "*.xpm" << "*.png", QDir::Files);
    foreach (QString filename, imagesPath) {
        image_directory[count] = path.filePath(filename);
        count ++;
    }
    if(count>0){
        for (int var = 0; var < count; ++var) {
            if(QString(currentDirectory+"/"+namePicture)==QString(image_directory[count])){
                i=var;
            }
        }
        image_checker = true;
        QVariant data = ui->treeView->model()->data(index);
        namePicture = data.toString();
        setImage(currentDirectory+"/"+namePicture);
        ui->infosimage->setText("");
        setImageInfos(currentDirectory+"/"+namePicture);
    }
}

void MainWindow::on_actionReconstruction_3D_triggered()
{
    ui->imagespace->setVisible(true);
    ui->checkBox->setVisible(true);

    bool res;
    Process p(this);
    QDialog dialog;
    dialog.setWindowTitle("Saisie d'informations");

    // Layout pour organiser les widgets
    QFormLayout layout(&dialog);

    // Champs de saisie
    QLineEdit lineEdit1;
    QLineEdit lineEdit2;

    // Ajout des champs de saisie au layout
    layout.addRow("Alpha:", &lineEdit1);
    layout.addRow("Nombre d'Images:", &lineEdit2);

    // Bouton "OK"
    QPushButton buttonOK("OK");
    layout.addRow(&buttonOK);
    QString value1 ;
    QString value2 ;
    // Gestionnaire de signaux pour le bouton "OK"
    QObject::connect(&buttonOK, &QPushButton::clicked, [&]() {
        // Récupérer les valeurs saisies
        value1 = lineEdit1.text();
        value2 = lineEdit2.text();

        // Afficher les valeurs récupérées
        qDebug() <<  value1;
        qDebug() <<  value2;

        // Fermer le dialogue
        dialog.accept();

        this->setCursor(Qt::WaitCursor);

        res=p.reconstruction3D(value2,currentDirectory+"/",value1);
        if(res){
            this->setCursor(Qt::ArrowCursor);
        }

    });
    dialog.exec();
}


void MainWindow::on_actionMise_en_correspondance_triggered()
{
    ui->imagespace->setVisible(true);
    ui->checkBox->setVisible(true);
    if(ImagesSelectedForCorrespondance.size()!=2){
        QMessageBox::information(this, "Information", "Vous devez sélectionner 2 images pour faire la correspondance");
    }else{

        ui->infosimage->setVisible(true);

        bool res;
        Process p(this);
        this->setCursor(Qt::WaitCursor);

        res=p.correspondance(ImagesSelectedForCorrespondance[0],ImagesSelectedForCorrespondance[1],currentDirectory+"/");

        updatePictures(currentDirectory+"/CorrespondanceFiltree.jpg");
        this->setCursor(Qt::ArrowCursor);
    }
}

void MainWindow::on_actionExtraction_de_caract_ristiques_triggered()
{
    Process p(this);
    this->setCursor(Qt::WaitCursor);

    p.getCaracteristique(currentDirectory+"/"+namePicture,"nodefine.png",currentDirectory+"/");
    updatePictures(currentDirectory+"/KeyPoints.jpg");

    this->setCursor(Qt::ArrowCursor);

}

void MainWindow::on_checkBox_clicked(bool checked)
{
    if(checked){
        ImagesSelectedForCorrespondance.push_back(currentDirectory+"/"+namePicture);
    }else{
        std::vector<QString>::iterator it = std::find(ImagesSelectedForCorrespondance.begin(), ImagesSelectedForCorrespondance.end(), currentDirectory+"/"+namePicture);
        ImagesSelectedForCorrespondance.erase(it);
    }
}

void MainWindow::on_actionVisualisation_des_points_3D_triggered()
{
    ui->imagespace->setVisible(true);
    ui->checkBox->setVisible(true);
    if(ImagesSelectedForCorrespondance.size()!=2){
        QMessageBox::information(this, "Information", "Vous devez sélectionner 2 images pour faire la correspondance");
    }else{

        ui->infosimage->setVisible(true);

        bool res;
        Process p(this);
        this->setCursor(Qt::WaitCursor);

        //pour corres to off
        //        res=p.pointCloud(ImagesSelectedForCorrespondance[0],ImagesSelectedForCorrespondance[1],currentDirectory);

        QDialog dialog;
        dialog.setWindowTitle("Saisie des indices");

        // Layout pour organiser les widgets
        QFormLayout layout(&dialog);

        // Champs de saisie
        QLineEdit lineEdit1;
        QLineEdit lineEdit2;

        // Ajout des champs de saisie au layout
        layout.addRow("Indice 1:", &lineEdit1);
        layout.addRow("Indice 2:", &lineEdit2);

        // Bouton "OK"
        QPushButton buttonOK("OK");
        layout.addRow(&buttonOK);
        QString value1 ;
        QString value2 ;
        // Gestionnaire de signaux pour le bouton "OK"
        QObject::connect(&buttonOK, &QPushButton::clicked, [&]() {
            // Récupérer les valeurs saisies
            value1 = lineEdit1.text();
            value2 = lineEdit2.text();

            // Afficher les valeurs récupérées
            qDebug() <<  value1;
            qDebug() <<  value2;

            // Fermer le dialogue
            dialog.accept();
            res=p.pointCloud(currentDirectory,ImagesSelectedForCorrespondance[0],ImagesSelectedForCorrespondance[1],currentDirectory+"/pointcloud"+value1+"::"+value2+".pcd");

            this->setCursor(Qt::ArrowCursor);
        });

        // Afficher le dialogue
        dialog.exec();
        //pour ply to pcd

    }

}

void MainWindow::on_actionNuage_de_point_final_triggered()
{
    ui->imagespace->setVisible(true);
    ui->checkBox->setVisible(true);

    bool res;
    Process p(this);
    QDialog dialog;
    dialog.setWindowTitle("Saisie d'informations");

    // Layout pour organiser les widgets
    QFormLayout layout(&dialog);

    // Champs de saisie
    QLineEdit lineEdit2;

    // Ajout des champs de saisie au layout
    layout.addRow("Nombre d'Images:", &lineEdit2);

    // Bouton "OK"
    QPushButton buttonOK("OK");
    layout.addRow(&buttonOK);
    QString value2 ;
    // Gestionnaire de signaux pour le bouton "OK"
    QObject::connect(&buttonOK, &QPushButton::clicked, [&]() {
        // Récupérer les valeurs saisies
        value2 = lineEdit2.text();

        // Afficher les valeurs récupérées
        qDebug() <<  value2;

        // Fermer le dialogue
        dialog.accept();

        this->setCursor(Qt::WaitCursor);

        res=p.pointcloudfinalrecale(value2,currentDirectory+"/");
        if(res){
            this->setCursor(Qt::ArrowCursor);
        }

    });
    dialog.exec();
}
