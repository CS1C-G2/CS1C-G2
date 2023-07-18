#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
    this part is confusing to me and I still dont know a fix to it
    so this right here will literally find where the text file is stored,
    the actual intention is for this to find a text file inside the qt project
    folder however it just cant find it for some reason, so I had to hard code it
    */
    readShapesFromFile("C:/Users/suraj/OneDrive/Documents/shape/shapes.txt");
}

void MainWindow::readShapesFromFile(const QString &fileName)
{
    QFile file(fileName); // this will get our file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) // this is super important
    {
        // this right here will stop a majority of errors we will get if the file is not found
        qDebug() << "Failed to open file: " << fileName;
        return;
    }

    /*
    QTextStream allows us to read from the file, similar to c++ fstream
    */
    QTextStream in(&file);
    while (!in.atEnd()) // if the file is not at the end
    {
        QString line = in.readLine(); // this is similar to the c++ string line from #include <string>
        QStringList parts = line.split(" "); // in order for us to read in data, we must split the line
        /*
        your text file should look like this:
        Rectangle 100 50
        What we need to do is to split this into 3 parts based off where the spaces are
        first part will be the shape name
        2nd part will be the base
        3rd part will be the heigh
        The reason we need to do this is because we need to find a way to take these values and
        put them appropriately when we print out the rectangle

        */
        if (parts.size() == 3) // this is soley just to check if the text file has all 3 parts
        {
            ShapeData shape; // our struct
            shape.shapeName = parts[0]; // part 1
            shape.base = parts[1].toInt(); // part 2
            shape.height = parts[2].toInt(); // part 3
            shapes.append(shape); // appending to our vector
        }
    }
    file.close(); // make sure to close the file after wards
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event); // this is confusing but what this will do is it will to suppress the "unused variable" compiler warning
    QPainter painter(this); // painting

    for (const auto &shape : shapes) // reading in from the vector
    {
        if (shape.shapeName == "Rectangle") // checking the shape
        {
            painter.drawRect(10, 10, shape.base, shape.height); // painting the shape
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

