#ifndef NEWREQUESTSMODEL_H
#define NEWREQUESTSMODEL_H

#include <QAbstractListModel>
#include <vector>

#include "RequestModel.h"

class NewRequestsModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit NewRequestsModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addRequest(RequestModel req);
    bool removeRequest(uint id);

    std::vector<RequestModel> &getList();

    void updateData();

signals:
    void listUpdated();

private:
    std::vector<RequestModel> m_list;
};

#endif // NEWREQUESTSMODEL_H
