#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeView>
#include <QFileSystemModel>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QModelIndex>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QInputDialog>
#include <QImageReader>
#include <QTimer>
#include <QMimeData>
#include <QCompleter>
#include <QStringListModel>
#include <QContextMenuEvent>
#include <QStyleOptionFrameV3>
#include "images.h"

MainWindow::MainWindow(QWidget *parent) :

                                          QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_pictures_folder_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    const QString chosenFolder = dialog.getExistingDirectory(this, tr("Select Output Folder"), QDir::homePath());
    QFileSystemModel *directory = new QFileSystemModel;
    directory->setRootPath(chosenFolder);
    ui->treeView->setModel(directory);
    ui->treeView->setRootIndex(directory->index(chosenFolder));
    this->currentDirectory = chosenFolder;
    ui->treeView->setColumnWidth(0,200);
}

void MainWindow::on_actionZoom_triggered()
{
    QMessageBox::information(this, "title", "Zoom forward");
}

void MainWindow::on_actionZoom_2_triggered()
{
    QMessageBox::information(this, "title", "Zoom backward");
}

void MainWindow::on_actionCorrespondance_triggered()
{
    ui->picture1->setVisible(false);
    ui->picture2->setVisible(false);
    ui->picture3->setVisible(true);

    ui->textimage3->setVisible(true);
    ui->textimage2->setVisible(false);
    ui->textimage1->setVisible(false);


        QString text=namePicture1.split("Carac")[0]+"Corres."+namePicture1.split(".").back();
        images IMG(this);
        cv::Mat img1 = cv::imread((currentDirectory+"/"+namePicture1.split("Carac")[0].split(".")[0]+"."+namePicture1.split(".").back()).toStdString());
            cv::Mat img2 = cv::imread((currentDirectory+"/"+namePicture2.split("Carac")[0].split(".")[0]+"."+namePicture1.split(".").back()).toStdString());

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
//            IMG.drawMatche(img1, keypoints1, img2, keypoints2, good_matches12, img_matches12);
            IMG.drawMatche(img1, keypoints1, img2, keypoints2, matches12, img_matches12);

            cv::Size size12 = img_matches12.size();
            cv::Mat left(img_matches12, cv::Rect(0, 0, size12.width, size12.height));
            img_matches12.copyTo(left);

            // Afficher l'image finale avec les correspondances entre les deux images
            cv::imwrite((currentDirectory+"/"+text).toStdString(), img_matches12);

            cv::waitKey(0);

    updatePictures(currentDirectory+"/"+text,3);

}

void MainWindow::on_actionTriangulation_triggered()
{
}

void MainWindow::on_actionContact_us_triggered()
{
    QMessageBox::information(this, "title", "Help");
}

void MainWindow::on_actionCaracteristics_extraction_triggered()
{

        QString text=namePicture1.split(".")[0]+"Carac1"+"."+namePicture1.split(".").back();
        QString text1=namePicture2.split(".")[0]+"Carac2"+"."+namePicture2.split(".").back();

        images img(this);
        img.getCaracteristiques((currentDirectory + "/" + namePicture1),(currentDirectory+"/"+text), 1);

        img.getCaracteristiques((currentDirectory + "/" + namePicture2),(currentDirectory+"/"+text1),2);

}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    ui->picture3->setVisible(false);
    ui->picture1->setVisible(true);
    ui->picture2->setVisible(true);

    ui->textimage3->setVisible(false);
    ui->textimage2->setVisible(true);
    ui->textimage1->setVisible(true);

    QVariant data = ui->treeView->model()->data(index);
    QString text = data.toString();
    QPixmap *pixmap_img = new QPixmap(currentDirectory + "/" + text);
    QImage img = pixmap_img->toImage();
    const QPixmap *p = ui->picture1->pixmap();
    const QPixmap *p2 = ui->picture2->pixmap();

    QImageReader imgR(currentDirectory + "/" + text);
    QString format(imgR.format());
    QString name(imgR.fileName());
    QSize size = imgR.size();
    QString width = QString::number(size.width());
    QString height = QString::number(size.width());

    if (p == NULL)
    {
        ui->picture1->setPixmap(*pixmap_img);
        ui->textimage1->setText(ui->textimage1->text() + "Nom: " + text + "\nType: " + format + "\nWidth: " + width + "\nHeight: " + height );
        namePicture1 = text;
        lastPictureAdded = 1;
    }
    else if (p2 == NULL)
    {
        ui->picture2->setPixmap(*pixmap_img);
        ui->textimage2->setText("");
        ui->textimage2->setText(ui->textimage2->text() + "Nom: " + text + "\nType: " + format + "\nWidth: " + width + "\nHeight: " + height );
        namePicture2 = text;
        lastPictureAdded = 2;
    }
    else if (lastPictureAdded == 1)
    {
        ui->picture2->setPixmap(*pixmap_img);
        ui->textimage2->setText("");
        ui->textimage2->setText(ui->textimage2->text() + "Nom: " + text + "\nType: " + format + "\nWidth: " + width + "\nHeight: " + height);
        namePicture2 = text;
        lastPictureAdded = 2;
    }
    else
    {
        ui->picture1->setPixmap(*pixmap_img);
        ui->textimage1->setText("");
        ui->textimage1->setText(ui->textimage1->text() + "Nom: " + text + "\nType: " + format + "\nWidth: " + width + "\nHeight: " + height );
        namePicture1 = text;
        lastPictureAdded = 1;
    }
}


void MainWindow::updatePictures(QString s1, int nb)
{

    ui->picture3->setVisible(false);
    ui->picture1->setVisible(true);
    ui->picture2->setVisible(true);

    ui->textimage3->setVisible(false);
    ui->textimage2->setVisible(true);
    ui->textimage1->setVisible(true);

    if (nb == 1)
    {
        QImageReader imgR(s1);

        QString format(imgR.format());
        QString name(imgR.fileName());
        QSize size = imgR.size();
        QString width = QString::number(size.width());
        QString height = QString::number(size.width());

        QPixmap *pixmap_img = new QPixmap(s1);
        ui->picture1->setPixmap(*pixmap_img);
        ui->textimage1->setText("");
        ui->textimage1->setText(ui->textimage1->text() + "Nom: " + s1.split("/").back() + "\nType: " + format + "\nWidth: " + width + "\nHeight: " + height);

        namePicture1 = s1.split("/").back();
        lastPictureAdded = 1;
    }
    else if (nb == 2)
    {
        QImageReader imgR(s1);

        QString format(imgR.format());
        QString name(imgR.fileName());
        QSize size = imgR.size();
        QString width = QString::number(size.width());
        QString height = QString::number(size.width());

        QPixmap *pixmap_img = new QPixmap(s1);
        ui->picture2->setPixmap(*pixmap_img);
        ui->textimage2->setText("");
        ui->textimage2->setText(ui->textimage2->text() + "Nom: " + s1.split("/").back() + "\nType: " + format + "\nWidth: " + width + "\nHeight: " + height);

        namePicture2 = s1.split("/").back();
        lastPictureAdded = 2;
    }else if(nb==3){
        ui->picture3->setVisible(true);
        ui->picture1->setVisible(false);
        ui->picture2->setVisible(false);

        ui->textimage3->setVisible(true);
        ui->textimage2->setVisible(false);
        ui->textimage1->setVisible(false);

        QImageReader imgR(s1);

        QString format(imgR.format());
        QString name(imgR.fileName());
        QSize size = imgR.size();
        QString width = QString::number(size.width());
        QString height = QString::number(size.width());

        QPixmap *pixmap_img = new QPixmap(s1);
        ui->picture3->setPixmap(*pixmap_img);
        ui->textimage3->setText("");
        ui->textimage3->setText(ui->textimage3->text() + "Nom: " + s1.split("/").back() + "\nType: " + format + "\nWidth: " + width + "\nHeight: " + height);

        namePicture3 = s1.split("/").back();
        lastPictureAdded = 3;
    }
}
