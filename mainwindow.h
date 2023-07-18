#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    /*
    this function will allow us to read in files from a text file
    I wanted to use garret's parser function but his has alot of implementation
    that I have no idea how to do yet, so instead I made this
    */
    void readShapesFromFile(const QString &fileName); // a QString is similar to c++ include<string>
    void paintEvent(QPaintEvent *event); // this paints the shapes onto the main window

    Ui::MainWindow *ui;

    struct ShapeData { QString shapeName; int base; int height; }; // this stores the shape name, base, and height, we can edit this to include coords
    QVector<ShapeData> shapes; // stores the shape into a QT vector
};
#endif // MAINWINDOW_H
