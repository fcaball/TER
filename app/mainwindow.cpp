#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "images.h"
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

void MainWindow::setAnimation(){
    start_animation();
    end_animation();
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

int MainWindow::randomize(int low, int high){
    return qrand() % ((high + 1) - low) + low;
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

        setAnimation();

        if (anim_checker)
        {

            renderImage();

            infoImage();

        }
        else
        {
            setAnimation();
            renderImage();
            infoImage();
        }
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
        setAnimation();

        if (anim_checker)
        {
            renderImage();
            infoImage();
        }
        else
        {
            setAnimation();
            renderImage();
            infoImage();
        }
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
    if(ImagesSelectedForCorrespondance.size()!=2){
        QMessageBox::information(this, "Information", "Vous devez sélectionner 2 images pour faire la correspondance");
    }else{
    images img(this);
    QString offName=ImagesSelectedForCorrespondance[0].split(".")[0]+".off";
    bool res=img.reconstruction3D(ImagesSelectedForCorrespondance[0],ImagesSelectedForCorrespondance[1],offName);

    if(res){

    }
    }
}


void MainWindow::on_actionMise_en_correspondance_triggered()
{
        ui->imagespace->setVisible(true);
        ui->checkBox->setVisible(true);
        if(ImagesSelectedForCorrespondance.size()!=2){
            QMessageBox::information(this, "Information", "Vous devez sélectionner 2 images pour faire la correspondance");
        }else{

            ui->infosimage->setVisible(true);

            QString text=namePicture.split(".")[0]+"Corres."+namePicture.split(".").back();
            images IMG(this);
            cv::Mat img2 = cv::imread(ImagesSelectedForCorrespondance[1].toStdString());
            cv::Mat img1 = cv::imread(ImagesSelectedForCorrespondance[0].toStdString());

                // Définir le détecteur et l'extraction de descripteurs SIFT
                cv::Ptr<cv::FeatureDetector> detector = cv::SIFT::create();
                cv::Ptr<cv::DescriptorExtractor> extractor = cv::SIFT::create();

                // Détecter les points d'intérêt...
                std::vector<cv::KeyPoint> keypoints1, keypoints2, keypoints3;
                cv::Mat descriptors1, descriptors2;
                detector->detect(img1, keypoints1);
                detector->detect(img2, keypoints2);

                // ...et extraire les descripteurs pour les deux images
                extractor->compute(img1, keypoints1, descriptors1);
                extractor->compute(img2, keypoints2, descriptors2);

                // Trouver les correspondances de descripteurs entre les deux images
                cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create(cv::DescriptorMatcher::FLANNBASED);
                std::vector<cv::DMatch> matches12;
                matcher->match(descriptors1, descriptors2, matches12);

                // Filtrer les correspondances pour ne conserver que les correspondances les plus proches
                double max_dist = 0;
                double min_dist = 100;
                double dist;
                for (int i = 0; i < descriptors1.rows; i++)
                {
                    dist = matches12[i].distance;
                    if (dist < min_dist)
                        min_dist = dist;
                    if (dist > max_dist)
                        max_dist = dist;
                }
                std::vector<cv::DMatch> good_matches12;
                for (int i = 0; i < descriptors1.rows; i++)
                {
                    if (matches12[i].distance < 2 * min_dist)
                    {
                        good_matches12.push_back(matches12[i]);
                    }
                }

                max_dist = 0;
                min_dist = 100;

                // Calculer la matrice d'homographie à partir des correspondances de points d'intérêt
                cv::Mat img_matches12;
                //IMG.drawMatche(img1, keypoints1, img2, keypoints2, good_matches12, img_matches12);
                IMG.drawMatche(img1, keypoints1, img2, keypoints2, matches12, img_matches12);

                cv::Size size12 = img_matches12.size();
                cv::Mat left(img_matches12, cv::Rect(0, 0, size12.width, size12.height));
                img_matches12.copyTo(left);

                // Afficher l'image finale avec les correspondances entre les deux images
                cv::imwrite((currentDirectory+"/"+text).toStdString(), img_matches12);

                cv::waitKey(0);

                updatePictures(currentDirectory+"/"+text);
        }
}

void MainWindow::on_actionExtraction_de_caract_ristiques_triggered()
{
            QString text=namePicture.split(".")[0]+"Carac1"+"."+namePicture.split(".").back();

            images img(this);
            img.getCaracteristiques((currentDirectory + "/" + namePicture),(currentDirectory+"/"+text), 1);
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
