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
// #include "../build/test/DisplayImage.cpp"
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
    bool ok, ok1;
    QString text = QInputDialog::getText(this, tr("Nom Image de sortie"),
                                         tr("First name (sans l'extension):"), QLineEdit::Normal,
                                         QDir::home().dirName(), &ok);

    while (text.isEmpty() && ok)
    {
        text = QInputDialog::getText(this, tr("Nom Image de sortie"),
                                     tr("First name  (sans l'extension):"), QLineEdit::Normal,
                                     QDir::home().dirName(), &ok);
    }
    QString text1;
    if (ok)
    {
        text1 = QInputDialog::getText(this, tr("Nom Image de sortie"),
                                      tr("Second name  (sans l'extension):"), QLineEdit::Normal,
                                      QDir::home().dirName(), &ok1);

        while (text1.isEmpty() && ok1)
        {
            text1 = QInputDialog::getText(this, tr("Nom Image de sortie"),
                                          tr("Second name  (sans l'extension):"), QLineEdit::Normal,
                                          QDir::home().dirName(), &ok1);
        }
    }

    if (ok && ok1 && !text.isEmpty() && !text1.isEmpty())
    {
        text+=".jpeg";
        text1+=".jpeg";
        getCaracteristiques(currentDirectory + "/" + namePicture1,text, 1);

        getCaracteristiques(currentDirectory + "/" + namePicture2, text1, 2);
    }
}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex &index)
{
    QVariant data = ui->treeView->model()->data(index);
    QString text = data.toString();
    QPixmap *pixmap_img = new QPixmap(currentDirectory + "/" + text);
    QImage img = pixmap_img->toImage();
    const QPixmap *p = ui->picture1->pixmap();
    const QPixmap *p2 = ui->picture2->pixmap();

    QImageReader imgR(currentDirectory + "/" + text);
    QString format(imgR.format());
    QString Format(imgR.imageFormat());
    QString name(imgR.fileName());
    QSize size = imgR.size();
    QString width = QString::number(size.width());
    QString height = QString::number(size.width());

    if (p == NULL)
    {
        ui->picture1->setPixmap(*pixmap_img);
        ui->textimage1->setText(ui->textimage1->text() + "Nom: " + text + "\nType: " + format + "\nWidth: " + width + "\nHeight: " + height + "\nFormat: " + Format);
        namePicture1 = text;
        lastPictureAdded = 1;
    }
    else if (p2 == NULL)
    {
        ui->picture2->setPixmap(*pixmap_img);
        ui->textimage2->setText("");
        ui->textimage2->setText(ui->textimage2->text() + "Nom: " + text + "\nType: " + format + "\nWidth: " + width + "\nHeight: " + height + "\nFormat: " + Format);
        namePicture2 = text;
        lastPictureAdded = 2;
    }
    else if (lastPictureAdded == 1)
    {
        ui->picture2->setPixmap(*pixmap_img);
        ui->textimage2->setText("");
        ui->textimage2->setText(ui->textimage2->text() + "Nom: " + text + "\nType: " + format + "\nWidth: " + width + "\nHeight: " + height + "\nFormat: " + Format);
        namePicture2 = text;
        lastPictureAdded = 2;
    }
    else
    {
        ui->picture1->setPixmap(*pixmap_img);
        ui->textimage1->setText("");
        ui->textimage1->setText(ui->textimage1->text() + "Nom: " + text + "\nType: " + format + "\nWidth: " + width + "\nHeight: " + height + "\nFormat: " + Format);
        namePicture1 = text;
        lastPictureAdded = 1;
    }
}

void MainWindow::getCaracteristiques(QString in, QString out, int nb)
{
    cv::Mat src, src_gray;
    int thresh = 200;
    int max_thresh = 255;

    src = cv::imread(in.toStdString());

    cv::Ptr<cv::SiftFeatureDetector> detector = cv::SiftFeatureDetector::create();
    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    detector->detect(src, keypoints1);
    detector->detect(src, keypoints2);

    // Fill the file with key points
    // for(int i=0; i<keypoints.size(); i++)
    // {
    // 	fprintf(KeyPoint1, "%f %f\n", keypoints[i].pt.x, keypoints[i].pt.y);
    // }

    // Add results to image and save.
    cv::Mat output;
    cv::drawKeypoints(src, keypoints1, output, cv::Scalar_<double>::all(-1), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    cv::imwrite(currentDirectory.toStdString()+"/"+out.toStdString(), output);

    cv::waitKey(0);

    updatePictures(out, nb);
}

void MainWindow::updatePictures(QString s1, int nb)
{

    if (nb == 1)
    {
        QImageReader imgR(currentDirectory+"/"+s1);

        QString format(imgR.format());
        QString Format(imgR.imageFormat());
        QString name(imgR.fileName());
        QSize size = imgR.size();
        QString width = QString::number(size.width());
        QString height = QString::number(size.width());

        QPixmap *pixmap_img = new QPixmap(currentDirectory+"/"+s1);
        ui->picture1->setPixmap(*pixmap_img);
        ui->textimage1->setText("");
        ui->textimage1->setText(ui->textimage1->text() + "Nom: " + s1 + "\nType: " + format + "\nWidth: " + width + "\nHeight: " + height + "\nFormat: " + Format);

        namePicture1 = s1;
        lastPictureAdded = 1;
    }
    else if (nb == 2)
    {
        QImageReader imgR(currentDirectory+"/"+s1);

        QString format(imgR.format());
        QString Format(imgR.imageFormat());
        QString name(imgR.fileName());
        QSize size = imgR.size();
        QString width = QString::number(size.width());
        QString height = QString::number(size.width());

        QPixmap *pixmap_img = new QPixmap(currentDirectory+"/"+s1);
        ui->picture2->setPixmap(*pixmap_img);
        ui->textimage2->setText("");
        ui->textimage2->setText(ui->textimage2->text() + "Nom: " + s1 + "\nType: " + format + "\nWidth: " + width + "\nHeight: " + height + "\nFormat: " + Format);

        namePicture2 = s1;
        lastPictureAdded = 2;
    }
}
