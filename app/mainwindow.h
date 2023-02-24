#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionOpen_pictures_folder_triggered();

    void on_actionZoom_triggered();

    void on_actionZoom_2_triggered();

    void on_actionCaracteristics_extraction_triggered();

    void on_actionCorrespondance_triggered();

    void on_actionTriangulation_triggered();

    void on_actionContact_us_triggered();

    void on_pushButton_clicked();

    void on_treeView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    QString currentDirectory;
    int lastPictureAdded;
};

#endif // MAINWINDOW_H
