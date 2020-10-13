#ifndef SORTEDREQLISTMODEL_H
#define SORTEDREQLISTMODEL_H

#include <QAbstractListModel>

class SortedReqListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit SortedReqListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
};

#endif // SORTEDREQLISTMODEL_H
