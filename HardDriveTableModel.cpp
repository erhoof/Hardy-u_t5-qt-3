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
        /*if (index.column() == m_curSector)
            return QVariant(QColor(Qt::green));*/
    default:
        return QVariant();
    }
}

void HardDriveTableModel::timerTick()
{

}
