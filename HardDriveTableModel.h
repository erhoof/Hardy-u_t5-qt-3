#ifndef HARDDRIVETABLEMODEL_H
#define HARDDRIVETABLEMODEL_H

#include <QAbstractTableModel>

class HardDrive;

class HardDriveTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    HardDriveTableModel(QObject *parent = nullptr, HardDrive *hardDrive = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void updateData();
    void nextHead();
    void previousHead();

private:
    HardDrive *m_hardDrive;
    int m_curHead = 0; // Current head for table
};

#endif // HARDDRIVETABLEMODEL_H
