#ifndef SHAPEMODEL_H
#define SHAPEMODEL_H

#include <QAbstractListModel>

class Shape;

class ShapeModel : public QAbstractListModel
{
    Q_OBJECT

public:
    ShapeModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addShape(const Shape &shape);
    void removeShape(int index);

private:
    QList<Shape> shapes;
};

#endif // SHAPEMODEL_H
