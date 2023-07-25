#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include "shape.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);
    createMenus();
    startRenderingArea();
    onShapeCreate();

} // MainWindow

// this right here starts all the rendering stuff and the menubar
void MainWindow::startRenderingArea() {
    // Create the graphics view and scene
    graphicsView = ui->graphicsView;
    graphicsScene = new QGraphicsScene(this);
    // Set the scene on the view
    graphicsView->setScene(graphicsScene);


} // startRenderingArea

void MainWindow::onShapeCreate() {

    // Create "Create" button for Square tab
    QPushButton* createButton = ui->CreateShape;
    connect(createButton, &QPushButton::clicked, this, &MainWindow::createSquare); // Connect the button to the createSquare() slot

} // onShapeCreate

void MainWindow::createSquare() {
    // getting stuff from the UI
    int x = ui->x->value();
    int y = ui->y->value();

    int length = ui->length->value();
    // Get selected pen color and style from the UI
    Qt::GlobalColor penColor = static_cast<Qt::GlobalColor>(ui->comboBox->currentIndex());
    int penWidth = ui->length_2->value();

    Qt::PenStyle penStyle = static_cast<Qt::PenStyle>(ui->comboBox_3->currentIndex());
    Qt::PenCapStyle penCapStyle = static_cast<Qt::PenCapStyle>(ui->comboBox_4->currentIndex());
    Qt::PenJoinStyle penJoinStyle = static_cast<Qt::PenJoinStyle>(ui->comboBox_5->currentIndex());

    // Get selected brush color and style from the UI
     Qt::GlobalColor brushColor = static_cast<Qt::GlobalColor>(ui->comboBox_6->currentIndex());
     Qt::BrushStyle brushStyle = static_cast<Qt::BrushStyle>(ui->comboBox_7->currentIndex());

    // Create the QPen and QBrush objects
    QPen* pen = new QPen(penColor);
    pen->setWidth(penWidth);
    pen->setStyle(penStyle);
    pen->setCapStyle(penCapStyle);
    pen->setJoinStyle(penJoinStyle);
    QBrush* brush = new QBrush(brushColor, brushStyle);
    graphicsScene->clear();
    // Create the Square object
    Square* square = new Square(x, y, length, pen, brush);

    // Add the square to the QGraphicsScene
    graphicsScene->addItem(square);

    // Call the draw function to render the square
    square->draw();

} // createSquare

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

// deleting everything
MainWindow::~MainWindow() {
    delete ui;
    delete contactAction;
    delete helpAction;
    delete aboutAction;
} // ~MainWindow()
