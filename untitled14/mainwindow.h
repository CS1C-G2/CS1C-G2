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
#include "Shape.h"

class User;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addShape(Shape* shape);
    void removeShape(int id, int comboBoxIndex);
    void moveShape(int id, int x, int y);
    void updateUIForCurrentUser();

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
    void onDeleteShape();
    void onMoveShape();
    void onLoginClicked();

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
    QPushButton* loginButton;
    QAction* saveAction;
    QAction* loadAction;
    User *currentUser;
    myStd::vector<int> inputX;
    myStd::vector<int> inputY;
    myStd::vector<Shape*> shapes;
    int id {0};
};

#endif // MAINWINDOW_H
