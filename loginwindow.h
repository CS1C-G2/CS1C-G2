#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

class QLineEdit;

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);

private slots:
    void login();

private:
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
};

#endif // LOGINWINDOW_H
