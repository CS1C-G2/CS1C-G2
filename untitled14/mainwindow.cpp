#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>

#include "line.h"
#include "polyline.h"
#include "polygon.h"
#include "rectangle.h"
#include "square.h"
#include "ellipse.h"
#include "circle.h"
#include "text.h"

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

void MainWindow::createShape() {
    switch (ui->tabWidget->currentIndex()) {
        case 0:
            createLine();
            break;

        case 1:
            createPolyline();
            break;

        case 2:
            createPolygon();
            break;

        case 3:
            createRectangle();
            break;

        case 4:
            createSquare();
            break;

        case 5:
            createEllipse();
            break;

        case 6:
            createCircle();
            break;

        case 7:
            createText();
            break;

        default:
            break;
    }
}

void MainWindow::onShapeCreate() {

    // Create "Create" button for Square tab
    QPushButton* createButton = ui->CreateShape;
    connect(createButton, &QPushButton::clicked, this, &MainWindow::createShape); // Connect the button to the createSquare() slot
    connect(ui->AddPoint, &QPushButton::clicked, this, &MainWindow::addPolylinePoint);
    connect(ui->AddPoint_1, &QPushButton::clicked, this, &MainWindow::addPolygonPoint);
} // onShapeCreate

void MainWindow::addPolylinePoint() {
    inputX.push_back(ui->x_6->value());
    inputY.push_back(ui->y_6->value());
}

void MainWindow::addPolygonPoint() {
    inputX.push_back(ui->x_7->value());
    inputY.push_back(ui->y_7->value());
}

void MainWindow::createLine() {
    // getting stuff from the UI
    int x = ui->x_2->value();
    int y = ui->y_2->value();
    int x1 = ui->x1_2->value();
    int y1 = ui->y1_2->value();

    // Get selected pen color and style from the UI
    Qt::GlobalColor penColor = static_cast<Qt::GlobalColor>(ui->penColorValue_2->currentIndex() + 2);
    int penWidth = ui->penWidthValue_2->value();

    Qt::PenStyle penStyle = static_cast<Qt::PenStyle>(ui->penStyleValue_2->currentIndex());
    Qt::PenCapStyle penCapStyle = static_cast<Qt::PenCapStyle>(ui->penCapStyleValue_2->currentIndex() * 16);
    Qt::PenJoinStyle penJoinStyle = static_cast<Qt::PenJoinStyle>(ui->penJoinStyleValue_2->currentIndex() * 64);

    // Create the QPen objects
    QPen* pen = new QPen(penColor);
    pen->setWidth(penWidth);
    pen->setStyle(penStyle);
    pen->setCapStyle(penCapStyle);
    pen->setJoinStyle(penJoinStyle);

    graphicsScene->clear();
    // Create the Line object
    Line* line = new Line(3, x, y, x1, y1, pen);

    // Add the line to the QGraphicsScene
    graphicsScene->addItem(line);

    // Call the draw function to render the line
    line->draw();
}

void MainWindow::createPolyline() {
    // Get selected pen color and style from the UI
    Qt::GlobalColor penColor = static_cast<Qt::GlobalColor>(ui->penColorValue_6->currentIndex() + 2);
    int penWidth = ui->penWidthValue_6->value();

    Qt::PenStyle penStyle = static_cast<Qt::PenStyle>(ui->penStyleValue_6->currentIndex());
    Qt::PenCapStyle penCapStyle = static_cast<Qt::PenCapStyle>(ui->penCapStyleValue_6->currentIndex() * 16);
    Qt::PenJoinStyle penJoinStyle = static_cast<Qt::PenJoinStyle>(ui->penJoinStyleValue_6->currentIndex() * 64);

    // Create the QPen objects
    QPen* pen = new QPen(penColor);
    pen->setWidth(penWidth);
    pen->setStyle(penStyle);
    pen->setCapStyle(penCapStyle);
    pen->setJoinStyle(penJoinStyle);

    graphicsScene->clear();
    // Create the Polyline object
    Polyline* polyline = new Polyline(5, inputX, inputY, pen);

    // Add the polyline to the QGraphicsScene
    graphicsScene->addItem(polyline);

    // Call the draw function to render the polyline
    polyline->draw();
    emptyInputVectors();
}

void MainWindow::createPolygon() {
    // Get selected pen color and style from the UI
    Qt::GlobalColor penColor = static_cast<Qt::GlobalColor>(ui->penColorValue_7->currentIndex() + 2);
    int penWidth = ui->penWidthValue_7->value();

    Qt::PenStyle penStyle = static_cast<Qt::PenStyle>(ui->penStyleValue_7->currentIndex());
    Qt::PenCapStyle penCapStyle = static_cast<Qt::PenCapStyle>(ui->penCapStyleValue_7->currentIndex() * 16);
    Qt::PenJoinStyle penJoinStyle = static_cast<Qt::PenJoinStyle>(ui->penJoinStyleValue_7->currentIndex() * 64);

    // Get selected brush color and style from the UI
    Qt::GlobalColor brushColor = static_cast<Qt::GlobalColor>(ui->brushColorValue_7->currentIndex() + 2);
    Qt::BrushStyle brushStyle = static_cast<Qt::BrushStyle>(ui->brushStyleValue_7->currentIndex());

    // Create the QPen objects
    QPen* pen = new QPen(penColor);
    pen->setWidth(penWidth);
    pen->setStyle(penStyle);
    pen->setCapStyle(penCapStyle);
    pen->setJoinStyle(penJoinStyle);

    QBrush* brush = new QBrush(brushColor, brushStyle);

    graphicsScene->clear();
    // Create the Polygon object
    Polygon* polygon = new Polygon(6, inputX, inputY, pen, brush);

    // Add the polyline to the QGraphicsScene
    graphicsScene->addItem(polygon);

    // Call the draw function to render the polygon
    polygon->draw();
    emptyInputVectors();
}

void MainWindow::createRectangle() {
    // getting stuff from the UI
    int x = ui->x_1->value();
    int y = ui->y_1->value();

    int length = ui->length_1->value();
    int width = ui->width_1->value();
    // Get selected pen color and style from the UI
    Qt::GlobalColor penColor = static_cast<Qt::GlobalColor>(ui->penColorValue_1->currentIndex() + 2);
    int penWidth = ui->penWidthValue_1->value();

    Qt::PenStyle penStyle = static_cast<Qt::PenStyle>(ui->penStyleValue_1->currentIndex());
    Qt::PenCapStyle penCapStyle = static_cast<Qt::PenCapStyle>(ui->penCapStyleValue_1->currentIndex() * 16);
    Qt::PenJoinStyle penJoinStyle = static_cast<Qt::PenJoinStyle>(ui->penJoinStyleValue_1->currentIndex() * 64);

    // Get selected brush color and style from the UI
    Qt::GlobalColor brushColor = static_cast<Qt::GlobalColor>(ui->brushColorValue_1->currentIndex() + 2);
    Qt::BrushStyle brushStyle = static_cast<Qt::BrushStyle>(ui->brushStyleValue_1->currentIndex());

    // Create the QPen and QBrush objects
    QPen* pen = new QPen(penColor);
    pen->setWidth(penWidth);
    pen->setStyle(penStyle);
    pen->setCapStyle(penCapStyle);
    pen->setJoinStyle(penJoinStyle);
    QBrush* brush = new QBrush(brushColor, brushStyle);
    graphicsScene->clear();
    // Create the Rectangle object
    Rectangle* rect = new Rectangle(2, x, y, length, width, pen, brush);

    // Add the rectangle to the QGraphicsScene
    graphicsScene->addItem(rect);

    // Call the draw function to render the rectangle
    rect->draw();
}

void MainWindow::createSquare() {
    // getting stuff from the UI
    int x = ui->x->value();
    int y = ui->y->value();

    int length = ui->length->value();
    // Get selected pen color and style from the UI
    Qt::GlobalColor penColor = static_cast<Qt::GlobalColor>(ui->penColorValue->currentIndex() + 2);
    int penWidth = ui->penWidthValue->value();

    Qt::PenStyle penStyle = static_cast<Qt::PenStyle>(ui->penStyleValue->currentIndex());
    Qt::PenCapStyle penCapStyle = static_cast<Qt::PenCapStyle>(ui->penCapStyleValue->currentIndex() * 16);
    Qt::PenJoinStyle penJoinStyle = static_cast<Qt::PenJoinStyle>(ui->penJoinStyleValue->currentIndex() * 64);

    // Get selected brush color and style from the UI
     Qt::GlobalColor brushColor = static_cast<Qt::GlobalColor>(ui->brushColorValue->currentIndex() + 2);
     Qt::BrushStyle brushStyle = static_cast<Qt::BrushStyle>(ui->brushStyleValue->currentIndex());

    // Create the QPen and QBrush objects
    QPen* pen = new QPen(penColor);
    pen->setWidth(penWidth);
    pen->setStyle(penStyle);
    pen->setCapStyle(penCapStyle);
    pen->setJoinStyle(penJoinStyle);
    QBrush* brush = new QBrush(brushColor, brushStyle);
    graphicsScene->clear();
    // Create the Square object
    Square* square = new Square(1, x, y, length, pen, brush);

    // Add the square to the QGraphicsScene
    graphicsScene->addItem(square);

    // Call the draw function to render the square
    square->draw();

} // createSquare

void MainWindow::createEllipse() {
    // getting stuff from the UI
    int x = ui->x_3->value();
    int y = ui->y_3->value();
    int radius1 = ui->radius1_3->value();
    int radius2 = ui->radius2_3->value();

    // Get selected pen color and style from the UI
    Qt::GlobalColor penColor = static_cast<Qt::GlobalColor>(ui->penColorValue_3->currentIndex() + 2);
    int penWidth = ui->penWidthValue_3->value();

    Qt::PenStyle penStyle = static_cast<Qt::PenStyle>(ui->penStyleValue_3->currentIndex());
    Qt::PenCapStyle penCapStyle = static_cast<Qt::PenCapStyle>(ui->penCapStyleValue_3->currentIndex() * 16);
    Qt::PenJoinStyle penJoinStyle = static_cast<Qt::PenJoinStyle>(ui->penJoinStyleValue_3->currentIndex() * 64);

    // Get selected brush color and style from the UI
    Qt::GlobalColor brushColor = static_cast<Qt::GlobalColor>(ui->brushColorValue_3->currentIndex() + 2);
    Qt::BrushStyle brushStyle = static_cast<Qt::BrushStyle>(ui->brushStyleValue_3->currentIndex());

    // Create the QPen and QBrush objects
    QPen* pen = new QPen(penColor);
    pen->setWidth(penWidth);
    pen->setStyle(penStyle);
    pen->setCapStyle(penCapStyle);
    pen->setJoinStyle(penJoinStyle);
    QBrush* brush = new QBrush(brushColor, brushStyle);
    graphicsScene->clear();
    // Create the Ellipse object
    Ellipse* ellipse = new Ellipse(4, x, y, radius1, radius2, pen, brush);

    // Add the ellipse to the QGraphicsScene
    graphicsScene->addItem(ellipse);

    // Call the draw function to render the ellipse
    ellipse->draw();
}

void MainWindow::createCircle() {
    // getting stuff from the UI
    int x = ui->x_4->value();
    int y = ui->y_4->value();
    int radius = ui->radius_4->value();

    // Get selected pen color and style from the UI
    Qt::GlobalColor penColor = static_cast<Qt::GlobalColor>(ui->penColorValue_4->currentIndex() + 2);
    int penWidth = ui->penWidthValue_4->value();

    Qt::PenStyle penStyle = static_cast<Qt::PenStyle>(ui->penStyleValue_4->currentIndex());
    Qt::PenCapStyle penCapStyle = static_cast<Qt::PenCapStyle>(ui->penCapStyleValue_4->currentIndex() * 16);
    Qt::PenJoinStyle penJoinStyle = static_cast<Qt::PenJoinStyle>(ui->penJoinStyleValue_4->currentIndex() * 64);

    // Get selected brush color and style from the UI
    Qt::GlobalColor brushColor = static_cast<Qt::GlobalColor>(ui->brushColorValue_4->currentIndex() + 2);
    Qt::BrushStyle brushStyle = static_cast<Qt::BrushStyle>(ui->brushStyleValue_4->currentIndex());

    // Create the QPen and QBrush objects
    QPen* pen = new QPen(penColor);
    pen->setWidth(penWidth);
    pen->setStyle(penStyle);
    pen->setCapStyle(penCapStyle);
    pen->setJoinStyle(penJoinStyle);
    QBrush* brush = new QBrush(brushColor, brushStyle);
    graphicsScene->clear();
    // Create the Circle object
    Circle* circle = new Circle(5, x, y, radius, pen, brush);

    // Add the circle to the QGraphicsScene
    graphicsScene->addItem(circle);

    // Call the draw function to render the circle
    circle->draw();
}

void MainWindow::createText() {
    // getting stuff from the UI
    int x = ui->x_5->value();
    int y = ui->y_5->value();
    int length = ui->length_5->value();
    int width = ui->width_5->value();
    QString drawText = ui->textValue_5->toPlainText();
    Qt::AlignmentFlag textAlignment = static_cast<Qt::AlignmentFlag>(ui->textAlignmentValue_5->currentIndex());  // gotta convert
    QString family = ui->textFontFamilyValue_5->toPlainText();
    int pointSize = ui->textPointSizeValue_5->value();
    QFont::Style fontStyle = static_cast<QFont::Style>(ui->textFontStyleValue_5->currentIndex());
    QFont::Weight weight = static_cast<QFont::Weight>(ui->textFontWeightValue_5->currentIndex());


    // Get selected pen color and style from the UI
    Qt::GlobalColor penColor = static_cast<Qt::GlobalColor>(ui->penColorValue_5->currentIndex() + 2);
    int penWidth = ui->penWidthValue_5->value();

    Qt::PenStyle penStyle = static_cast<Qt::PenStyle>(ui->penStyleValue_5->currentIndex());
    Qt::PenCapStyle penCapStyle = static_cast<Qt::PenCapStyle>(ui->penCapStyleValue_5->currentIndex() * 16);
    Qt::PenJoinStyle penJoinStyle = static_cast<Qt::PenJoinStyle>(ui->penJoinStyleValue_5->currentIndex() * 64);

    // Create the QPen and QBrush objects
    QPen* pen = new QPen(penColor);
    pen->setWidth(penWidth);
    pen->setStyle(penStyle);
    pen->setCapStyle(penCapStyle);
    pen->setJoinStyle(penJoinStyle);

    QFont* font = new QFont(family, pointSize, weight);
    font->setStyle(fontStyle);

    graphicsScene->clear();
    // Create the Text object
    Text* text = new Text(7, x, y, width, length, drawText, font, pen, textAlignment);

    // Add the text to the QGraphicsScene
    graphicsScene->addItem(text);

    // Call the draw function to render the circle
    text->draw();
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

void MainWindow::emptyInputVectors() {
    inputX = {};
    inputY = {};
}

// deleting everything
MainWindow::~MainWindow() {
    delete ui;
    delete contactAction;
    delete helpAction;
    delete aboutAction;
} // ~MainWindow()
