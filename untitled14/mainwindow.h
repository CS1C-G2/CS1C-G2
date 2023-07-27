#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QAction>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QDockWidget>
#include <QPushButton>

#include "vector.cpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void startRenderingArea();
    void createShape();

private slots:
    void createMenus();
    void onContactUs();
    void onAbout();
    void onHelp();
    void onShapeCreate();
    void onAddTestimonial();
    void onViewTestimonials();
    void createLine();
    void createPolyline();
    void createPolygon();
    void createRectangle();
    void createSquare();
    void createEllipse();
    void createCircle();
    void createText();
    void addPolylinePoint();
    void addPolygonPoint();
    void clearTestimonials();

private:
    void emptyInputVectors();

    Ui::MainWindow *ui;
    QAction *contactAction;
    QAction *helpAction;
    QAction *aboutAction;
    QAction *addTestimonial;
    QAction *viewTestimonial;
    QGraphicsView *graphicsView;
    QGraphicsScene *graphicsScene;
    QPushButton* createButton;

    myStd::vector<int> inputX;
    myStd::vector<int> inputY;
};

#endif // MAINWINDOW_H
