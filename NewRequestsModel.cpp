#include "NewRequestsModel.h"

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
    {
        return m_list[index.row()].toString();
    }

    return QVariant();
}

void NewRequestsModel::addRequest(RequestModel req)
{
    m_list.push_back(req);
}

bool NewRequestsModel::removeRequest(uint id)
{
    int i=0;
    for (auto &req : m_list)
    {
        if (req.id == id)
            break;

        i++;
    }

    if (id > m_list.size())
        return false;
    else
        m_list.erase(m_list.begin() + id);

    return true;
}
