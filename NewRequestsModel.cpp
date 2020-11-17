#include "NewRequestsModel.h"

#include <QDebug>

NewRequestsModel::NewRequestsModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int NewRequestsModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return static_cast<int>(m_list.size());
}

QVariant NewRequestsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_list[index.row()].toString();

    return QVariant();
}

void NewRequestsModel::addRequest(RequestModel req)
{
    m_list.push_back(req);
    updateData();

    emit listUpdated();
}

bool NewRequestsModel::removeRequest(uint id)
{
    int i = 0;
    for (auto &req : m_list)
    {
        if (req.id == id)
            break;

        i++;
    }

    qDebug() << "REMID: " << QString::number(i);

    if (static_cast<uint>(i) > m_list.size())
        return false;
    else
        m_list.erase(m_list.begin() + i);

    updateData();

    emit listUpdated();

    return true;
}

std::vector<RequestModel> &NewRequestsModel::list()
{
    return m_list;
}

int NewRequestsModel::listSize() const
{
    return m_list.size();
}

void NewRequestsModel::updateData()
{
    // TODO: replace with removing by id

    QModelIndex start = index(0, 0);
    QModelIndex end = index(static_cast<int>(m_list.size()), 0);

    emit dataChanged(start, end);
}

void NewRequestsModel::removeTask(uint id)
{
    qDebug() << "NEWREQLIST REMOVE: " << QString::number(id);
    removeRequest(id);
}
