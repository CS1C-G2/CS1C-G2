#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QAction>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void createMenus();
    void onContactUs();
    void onAbout();
    void onHelp();

private:
    Ui::MainWindow *ui;
    QAction *contactAction;
    QAction *helpAction;
    QAction *aboutAction;

};

#endif // MAINWINDOW_H
