#include <QApplication>
#include "AdminWindow.h"
#include "GuestWindow.h"
#include "ShapeModel.h"
#include "LoginWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ShapeModel *model = new ShapeModel;

    qDebug() << "Before LoginWindow creation";
    LoginWindow loginWindow;
    qDebug() << "After LoginWindow creation";

    QMainWindow *window;

    if (loginWindow.exec() == QDialog::Accepted) {
        // Assume `isAdmin()` returns true if admin, false if guest
        if (loginWindow.isAdmin()) {
            window = new AdminWindow(model);
        } else {
            window = new GuestWindow(model);
        }
        window->resize(800, 600);
        window->show();
        return app.exec();
    } else {
        delete model;
        return 0;  // end the application if the login dialog is cancelled or login fails
    }
}
