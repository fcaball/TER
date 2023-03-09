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
//#include "../build/test/DisplayImage.cpp"
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
    const QString chosenFolder=dialog.getExistingDirectory(this,tr("Select Output Folder"),QDir::homePath());
    QFileSystemModel *directory = new QFileSystemModel;
    directory->setRootPath(chosenFolder);
    ui->treeView->setModel(directory);
    ui->treeView->setRootIndex(directory->index(chosenFolder));
    this->currentDirectory=chosenFolder;
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
    QMessageBox::information(this, "title", "Correspondance");
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
    bool ok,ok1;
       QString text = QInputDialog::getText(this, tr("Nom Image de sortie"),
                                            tr("Première Image (sans l'extension):"), QLineEdit::Normal,
                                            QDir::home().dirName(), &ok);

    while(text.isEmpty() && ok){
        text = QInputDialog::getText(this, tr("Nom Image de sortie"),
                                                    tr("Première Image  (sans l'extension):"), QLineEdit::Normal,
                                                    QDir::home().dirName(), &ok);

    }
    QString text1;
    if(ok){
         text1 = QInputDialog::getText(this, tr("Nom Image de sortie"),
                                             tr("Deuxième name  (sans l'extension):"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok1);

         while(text1.isEmpty() && ok1){
             text1 = QInputDialog::getText(this, tr("Nom Image de sortie"),
                                                         tr("Deuxième name  (sans l'extension):"), QLineEdit::Normal,
                                                         QDir::home().dirName(), &ok1);

         }
    }

    QImageReader imgR(currentDirectory+"/"+text);
    QString format(imgR.format());
    QString Format(imgR.imageFormat());
    QString name(imgR.fileName());
    QSize size=imgR.size();
    QString width=QString::number(size.width());
    QString height=QString::number(size.width());

    QImageReader imgR1(currentDirectory+"/"+text1);
    QString format1(imgR.format());
    QString Format1(imgR.imageFormat());
    QString name1(imgR.fileName());
    QSize size1=imgR.size();
    QString width1=QString::number(size.width());
    QString height1=QString::number(size.width());

    if (ok && ok1 && !text.isEmpty() && !text1.isEmpty()){
//        text+=".jpeg";
        QPixmap *pixmap_img = new QPixmap(currentDirectory+"/"+text);
        ui->picture1->setPixmap(*pixmap_img);
        ui->textimage1->setText("");
       ui->textimage1->setText(ui->textimage1->text()+"Nom: "+text+"\nType: "+format+"\nWidth: "+width+"\nHeight: "+height+"\nFormat: "+Format);

        lastPictureAdded=1;
//        text1+=".jpeg";
        QPixmap *pixmap_img1 = new QPixmap(currentDirectory+"/"+text1);
        ui->picture2->setPixmap(*pixmap_img1);
        ui->textimage2->setText("");
       ui->textimage2->setText(ui->textimage2->text()+"Nom: "+text1+"\nType: "+format1+"\nWidth: "+width1+"\nHeight: "+height1+"\nFormat: "+Format1);
        lastPictureAdded=2;
    }
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QVariant data = ui->treeView->model()->data(index);
    QString text = data.toString();
    QPixmap *pixmap_img = new QPixmap(currentDirectory+"/"+text);
    QImage img=pixmap_img->toImage();
    const QPixmap* p=ui->picture1->pixmap();
    const QPixmap* p2=ui->picture2->pixmap();

    QImageReader imgR(currentDirectory+"/"+text);
    QString format(imgR.format());
    QString Format(imgR.imageFormat());
    QString name(imgR.fileName());
    QSize size=imgR.size();
    QString width=QString::number(size.width());
    QString height=QString::number(size.width());


    if(p==NULL){
        ui->picture1->setPixmap(*pixmap_img);
        ui->textimage1->setText(ui->textimage1->text()+"Nom: "+text+"\nType: "+format+"\nWidth: "+width+"\nHeight: "+height+"\nFormat: "+Format);
        lastPictureAdded=1;
    }
    else if(p2==NULL){
        ui->picture2->setPixmap(*pixmap_img);
         ui->textimage2->setText("");
        ui->textimage2->setText(ui->textimage2->text()+"Nom: "+text+"\nType: "+format+"\nWidth: "+width+"\nHeight: "+height+"\nFormat: "+Format);
        lastPictureAdded=2;
    }else if(lastPictureAdded==1){
        ui->picture2->setPixmap(*pixmap_img);
         ui->textimage2->setText("");
        ui->textimage2->setText(ui->textimage2->text()+"Nom: "+text+"\nType: "+format+"\nWidth: "+width+"\nHeight: "+height+"\nFormat: "+Format);
        lastPictureAdded=2;
    }else{
        ui->picture1->setPixmap(*pixmap_img);
         ui->textimage1->setText("");
        ui->textimage1->setText(ui->textimage1->text()+"Nom: "+text+"\nType: "+format+"\nWidth: "+width+"\nHeight: "+height+"\nFormat: "+Format);
        lastPictureAdded=1;
    }

}
