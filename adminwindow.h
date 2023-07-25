#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include "qpushbutton.h"
#include "qcombobox.h"

class AdminWindow : public QMainWindow
{
    Q_OBJECT

public:
    AdminWindow(QWidget *parent = nullptr);

private slots:
    void about();
    void createShape();

private:
    QComboBox* shapeComboBox;
    QPushButton* createShapeButton;
    void createMenus();
};

#endif // ADMINWINDOW_H
