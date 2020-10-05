#ifndef HARDDRIVETABLEMODEL_H
#define HARDDRIVETABLEMODEL_H

#include <QAbstractTableModel>

class HardDriveTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit HardDriveTableModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // HARDDRIVETABLEMODEL_H