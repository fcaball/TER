#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeView>
#include <QFileSystemModel>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>


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
    QMessageBox::information(this, "title", "Triangulation");
}

void MainWindow::on_actionContact_us_triggered()
{
    QMessageBox::information(this, "title", "Help");
}

void MainWindow::on_actionCaracteristics_extraction_triggered()
{
    /*Q dialog(this);
    dialog.setWindowTitle("Caracteristics");
    dialog.setFixedHeight(600);
    dialog.setFixedWidth(600);

    dialog.exec();*/

}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QVariant data = ui->treeView->model()->data(index);
    QString text = data.toString();
    QPixmap *pixmap_img = new QPixmap(currentDirectory+"/"+text);
    const QPixmap* p=ui->picture1->pixmap();
    const QPixmap* p2=ui->picture2->pixmap();

    if(p==NULL){
        ui->picture1->setPixmap(*pixmap_img);
        lastPictureAdded=1;
    }
    else if(p2==NULL){
        ui->picture2->setPixmap(*pixmap_img);
        lastPictureAdded=2;
    }else if(lastPictureAdded==1){
        ui->picture2->setPixmap(*pixmap_img);
        lastPictureAdded=2;
    }else{
        ui->picture1->setPixmap(*pixmap_img);
        lastPictureAdded=1;
    }

}
