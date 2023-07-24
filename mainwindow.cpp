#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMenuBar>
#include <QMenu>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createMenus();
}

void MainWindow::createMenus() {

    // Create the menu bar
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    // Create the "File" menu and add it to the menu bar
    QMenu *fileMenu = menuBar->addMenu("file");

    // Create the "Contact Us" QAction and add it to the "File" menu
    contactAction = new QAction("Contact Us", this);
    helpAction = new QAction("help", this);
    aboutAction = new QAction("About us", this);

    fileMenu->addAction(contactAction);
    fileMenu->addAction(helpAction);
    fileMenu->addAction(aboutAction);

    connect(contactAction, &QAction::triggered, this, &MainWindow::onContactUs);
    connect(helpAction, &QAction::triggered, this, &MainWindow::onHelp);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);

} // createMenus

void MainWindow::onContactUs() {
    QDialog *contactDialog = new QDialog(this);
    contactDialog->setWindowTitle("Contact Us");

    QLabel *label = new QLabel("please email us at: someone@email.com", contactDialog);
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(contactDialog);
    layout->addWidget(label);

    contactDialog->exec();

} //onContactUs

void MainWindow::onHelp() {

    QDialog *contactDialog = new QDialog(this);
    contactDialog->setWindowTitle("Help");

    QLabel *label = new QLabel("please email us at: someone@email.com", contactDialog);
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(contactDialog);
    layout->addWidget(label);

    contactDialog->exec();

} // onHelp

void MainWindow::onAbout() {
    QDialog *contactDialog = new QDialog(this);
    contactDialog->setWindowTitle("about");

    QLabel *label = new QLabel("This is the 2D Graphics Modeler application", contactDialog);
    label->setAlignment(Qt::AlignCenter);

    QVBoxLayout *layout = new QVBoxLayout(contactDialog);
    layout->addWidget(label);
    contactDialog->exec();

} // onAbout


MainWindow::~MainWindow()
{
    delete ui;
}


