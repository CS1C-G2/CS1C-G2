#include "ShapeModel.h"
#include "Shape.h"

ShapeModel::ShapeModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ShapeModel::rowCount(const QModelIndex &parent) const
{
    return shapes.size();
}

QVariant ShapeModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= shapes.size())
        return QVariant();

    const Shape &shape = shapes[index.row()];
    if (role == Qt::DisplayRole)
        return shape.name();

    return QVariant();
}

void ShapeModel::addShape(const Shape &shape)
{
    beginInsertRows(QModelIndex(), shapes.size(), shapes.size());
    shapes.append(shape);
    endInsertRows();
}

void ShapeModel::removeShape(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    shapes.removeAt(index);
    endRemoveRows();
}
