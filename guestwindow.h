#ifndef GUESTWINDOW_H
#define GUESTWINDOW_H

#include <QMainWindow>
#include "ShapeModel.h"

class GuestWindow : public QMainWindow {
    Q_OBJECT

public:
    GuestWindow(ShapeModel *model, QWidget *parent = nullptr);
    ~GuestWindow();

private:
    ShapeModel *shapeModel;
};

#endif // GUESTWINDOW_H
