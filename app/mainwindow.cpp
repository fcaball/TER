#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTreeView>
#include <QFileSystemModel>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QRadioButton>
#include <QVBoxLayout>

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
