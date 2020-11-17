#include "HardDriveTableModel.h"

#include "harddrive.h"
#include <QColor>

HardDriveTableModel::HardDriveTableModel(QObject *parent, HardDrive *hardDrive)
    : QAbstractTableModel(parent),
      m_hardDrive(hardDrive)
{
}

int HardDriveTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_hardDrive->cylindersCount();
}

int HardDriveTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_hardDrive->sectorsCount();
}

QVariant HardDriveTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
    case Qt::DisplayRole:
        // Cylinder Head Sector
        return m_hardDrive->getBitFastAt(index.row(), m_curHead, index.column());
        break;
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
        break;
    case Qt::BackgroundRole:
        if (index.column() == static_cast<int>(m_hardDrive->position().sector) &&
            index.row() == static_cast<int>(m_hardDrive->position().cylinder))
            return QVariant(QColor(Qt::red));
        else if (index.column() == static_cast<int>(m_hardDrive->position().sector))
            return QVariant(QColor(Qt::green));
    default:
        return QVariant();
    }
}

void HardDriveTableModel::updateData()
{
    // Sector Column
    QModelIndex start = index(0, m_hardDrive->position().sector);
    QModelIndex end = index(m_hardDrive->cylindersCount(), m_hardDrive->position().sector);

    emit dataChanged(start, end);
}

void HardDriveTableModel::nextHead()
{
    if (m_curHead + 1 != m_hardDrive->headsCount())
        m_curHead++;
}

void HardDriveTableModel::previousHead()
{
    if (m_curHead != 0)
        m_curHead--;
}
