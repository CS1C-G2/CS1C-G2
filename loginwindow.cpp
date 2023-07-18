#include "loginwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    layout->addWidget(new QLabel("Username:"));
    usernameEdit = new QLineEdit(this);
    layout->addWidget(usernameEdit);

    layout->addWidget(new QLabel("Password:"));
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordEdit);

    QPushButton *loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton);

    QPushButton *guestLoginButton = new QPushButton("Guest Login", this);
    layout->addWidget(guestLoginButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::login);
    connect(guestLoginButton, &QPushButton::clicked, this, &LoginWindow::accept);

    resize(400, 200);
}

void LoginWindow::login()
{
    if (usernameEdit->text() == "admin" && passwordEdit->text() == "password") {
        accept();
    } else {
        QMessageBox::warning(this, "Login failed", "Invalid username or password");
    }
}
