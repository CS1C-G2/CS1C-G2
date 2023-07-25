#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QFormLayout *layout = new QFormLayout;

    shapeComboBox = new QComboBox;
    createShapeButton = new QPushButton("Create Shape");

    shapeComboBox->addItem("Square"); // add "Square" to the combo box
    shapeComboBox->addItem("Circle"); // add "Circle" to the combo box
    shapeComboBox->addItem("Triangle"); // add "Triangle" to the combo box

    layout->addRow(shapeComboBox); // Add widgets to the layout.
    layout->addRow(createShapeButton);

    shapeComboBox->setFixedSize(200, 25); // Sets the size to 200px wide and 50px tall
    createShapeButton->setFixedSize(200, 25); // Sets the size to 200px wide and 50px tall

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget); //Sets the size to 200px wide and 50px tall



    createMenus();

    connect(createShapeButton, &QPushButton::clicked, this, &MainWindow::createShape);
}

void MainWindow::createMenus()
{
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(tr("&About"), this, &MainWindow::about);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About 2D Graphics Modeler"),
                       tr("This is the 2D Graphics Modeler application."));
}

void MainWindow::createShape()
{
    QString selectedShape = shapeComboBox -> currentText();
}
