#ifndef DONEREQLISTMODEL_H
#define DONEREQLISTMODEL_H

#include <QAbstractListModel>

#include "RequestModel.h"

class HardDrive;

class DoneReqListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit DoneReqListModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

public slots:
    void taskFinished(RequestModel reqModel);

signals:
    void removeTask(uint id);
    void operateNextTask();

private:
    std::vector<RequestModel> m_list;

};

#endif // DONEREQLISTMODEL_H
