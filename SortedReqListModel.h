#ifndef SORTEDREQLISTMODEL_H
#define SORTEDREQLISTMODEL_H

#include <QAbstractListModel>

#include <vector>
#include "RequestModel.h"

class NewRequestsModel;
class HardDrive;

class SortedReqListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    SortedReqListModel(QObject *parent = nullptr,
                       NewRequestsModel *newReqModel = nullptr,
                       HardDrive *hardDrive = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int finishedTaskID() const;

public slots:
    void updateList();
    void execTask();

signals:
    void taskFinished();

private:
    NewRequestsModel *m_newReqModel;
    HardDrive *m_hardDrive;
    std::vector<RequestModel> m_list;

    int m_finishedTaskID;
};

#endif // SORTEDREQLISTMODEL_H
