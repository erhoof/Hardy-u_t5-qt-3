#include "DoneReqListModel.h"

#include <QDebug>

DoneReqListModel::DoneReqListModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int DoneReqListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_list.size();
}

QVariant DoneReqListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_list[index.row()].toString();

    return QVariant();
}

void DoneReqListModel::taskFinished(RequestModel reqModel) {
    qDebug() << "TASK FINISHED.";

    m_list.push_back(reqModel);

    QModelIndex start = index(0, 0);
    QModelIndex end = index(static_cast<int>(m_list.size()), 0);

    emit dataChanged(start, end);
    emit removeTask(reqModel.id);
    emit operateNextTask();
}
