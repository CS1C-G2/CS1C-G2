#include <QApplication>
#include "mainwindow.h"
#include "loginwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    LoginWindow loginWindow;
    if (loginWindow.exec() == QDialog::Accepted) {
        MainWindow mainWindow;
        mainWindow.resize(800, 600);
        mainWindow.show();
        return app.exec();
    } else {
        return 0;  // end the application if the login dialog is cancelled or login fails
    }
}
