#include "HardDriveTableModel.h"

#include "HardDrive.h"

HardDriveTableModel::HardDriveTableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int HardDriveTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return HardDrive::instance()->cylindersCount();
}

int HardDriveTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return HardDrive::instance()->sectorsCount();
}

QVariant HardDriveTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
    {
        return 1;
    }

    return QVariant();
}
