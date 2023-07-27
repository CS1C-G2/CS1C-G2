#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMenuBar>
#include <QMenu>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QPainter>
#include <QPainterPath>
#include <QMessageBox>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>
#include <QSlider>
#include <QSpinBox>


#include "line.h"
#include "rectangle.h"
#include "square.h"
#include "ellipse.h"
#include "circle.h"
#include "user.h"
#include "admin.h"
#include "guest.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {;

    ui->setupUi(this);

    currentUser = new Guest();
    updateUIForCurrentUser(); // Call this function to update the UI for the current user.

    connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);

    createMenus();
    startRenderingArea();
    onShapeCreate(currentUser);

} // MainWindow

void MainWindow::onLoginClicked() {

    // Convert QString to std::string for comparison
    std::string username = ui->usernameEdit->text().toStdString();
    std::string password = ui->passwordEdit->text().toStdString();

    // Check if the entered username and password are correct
    if(username == "admin" && password == "password") { // compare entered password to "password"
        delete currentUser;
        currentUser = new Admin("admin", "password"); // pass "password" to the Admin constructor
        QMessageBox::information(this, "Logged in", "You are now logged in as an admin.");
    } else if(!username.empty()) {
        QMessageBox::warning(this, "Login failed", "Incorrect username or password.");
    } else {
        delete currentUser;
        currentUser = new Guest();
    }

    // Update the UI according to the user permissions
    updateUIForCurrentUser();
}


void MainWindow::updateUIForCurrentUser() {
    bool isEnabled = (currentUser->getType() == "Admin");

    QWidget* excludedWidget1 = ui->loginButton;
    QWidget* excludedWidget2 = ui->usernameEdit;
    QWidget* excludedWidget3 = ui->passwordEdit;

    QList<QPushButton*> buttons = findChildren<QPushButton*>();
    for (QPushButton* button : buttons) {
        if (button != excludedWidget1 && button != excludedWidget2 && button != excludedWidget3) {
            button->setEnabled(isEnabled);
        }
    }

    QList<QLineEdit*> lineEdits = findChildren<QLineEdit*>();
    for (QLineEdit* lineEdit : lineEdits) {
        if (lineEdit != excludedWidget1 && lineEdit != excludedWidget2 && lineEdit != excludedWidget3) {
            lineEdit->setEnabled(isEnabled);
        }
    }

    QList<QCheckBox*> checkBoxes = findChildren<QCheckBox*>();
    for (QCheckBox* checkBox : checkBoxes) {
        checkBox->setEnabled(isEnabled);
    }

    QList<QRadioButton*> radioButtons = findChildren<QRadioButton*>();
    for (QRadioButton* radioButton : radioButtons) {
        radioButton->setEnabled(isEnabled);
    }

    QList<QComboBox*> comboBoxes = findChildren<QComboBox*>();
    for (QComboBox* comboBox : comboBoxes) {
        comboBox->setEnabled(isEnabled);
    }

    QList<QSlider*> sliders = findChildren<QSlider*>();
    for (QSlider* slider : sliders) {
        slider->setEnabled(isEnabled);
    }

    QList<QSpinBox*> spinBoxes = findChildren<QSpinBox*>();
    for (QSpinBox* spinBox : spinBoxes) {
        if (spinBox != excludedWidget1 && spinBox != excludedWidget2 && spinBox != excludedWidget3) {
            spinBox->setEnabled(isEnabled);
        }
    }
}

// this right here starts all the rendering stuff and the menubar
void MainWindow::startRenderingArea() {
    // Create the graphics view and scene
    graphicsView = ui->graphicsView;
    graphicsScene = new QGraphicsScene(this);
    // Set the scene on the view
    graphicsView->setScene(graphicsScene);


} // startRenderingArea

void MainWindow::createShape(User* user) {
    if(user->getType() == "Admin") {
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
    } else {
        // Show an error message or do nothing
    }
}

void MainWindow::onShapeCreate(User* currentUser) {

    // Create "Create" button for Square tab
    QPushButton* createButton = ui->CreateShape;

    // Connect the button to the createShape() slot
    connect(createButton, &QPushButton::clicked, this, [this, currentUser]() {
        this->createShape(currentUser);
    });
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

}

void MainWindow::createPolygon() {

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

// deleting everything
MainWindow::~MainWindow() {
    delete ui;
    delete currentUser;
    delete contactAction;
    delete helpAction;
    delete aboutAction;
} // ~MainWindow()
