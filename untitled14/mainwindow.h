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
    void updateUIForCurrentUser();

public slots:
    void startRenderingArea();
    void createShape(User* user);
private slots:
    void createMenus();
    void onContactUs();
    void onAbout();
    void onHelp();
    void onShapeCreate(User* currentUser);
    void createLine();
    void createPolyline();
    void createPolygon();
    void createRectangle();
    void createSquare();
    void createEllipse();
    void createCircle();
    void createText();
    void onLoginClicked();


private:
    Ui::MainWindow *ui;
    QAction *contactAction;
    QAction *helpAction;
    QAction *aboutAction;
    QGraphicsView *graphicsView;
    QGraphicsScene *graphicsScene;
    QPushButton* createButton;
    QPushButton* loginButton;

    User *currentUser;

};

#endif // MAINWINDOW_H
