#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QFormLayout>
#include "qpushbutton.h"
#include "qcombobox.h"
#include "parser.cpp"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void about();
    void createShape();

private:
    QComboBox* shapeComboBox;
    QPushButton* createShapeButton;
    void createMenus();
};

#endif // MAINWINDOW_H
