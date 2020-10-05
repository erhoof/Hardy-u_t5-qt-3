#include "HardDriveTableModel.h"

#include "HardDrive.h"
#include <QColor>

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

    switch (role)
    {
    case Qt::DisplayRole:
        return 1;
        break;
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
        break;
    case Qt::BackgroundRole:
        if (index.column() == static_cast<int>(HardDrive::instance()->curSector()))
            return QVariant(QColor(Qt::green));
    default:
        return QVariant();
    }
}

void HardDriveTableModel::timerTick()
{
    // Sector Column
    auto hd = HardDrive::instance();
    QModelIndex start = index(0, hd->curSector());
    QModelIndex end = index(hd->cylindersCount(), hd->curSector());

    emit dataChanged(start, end);
}
