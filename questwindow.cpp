#include "guestwindow.h"

GuestWindow::GuestWindow(ShapeModel *model, QWidget *parent)
    : QMainWindow(parent), shapeModel(model) {
    // Implement your read-only UI here
}

GuestWindow::~GuestWindow() {
    // Clean up if necessary
}
