#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createMenus();
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
