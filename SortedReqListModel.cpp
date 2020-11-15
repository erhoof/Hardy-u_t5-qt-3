#include "SortedReqListModel.h"

#include "NewRequestsModel.h"
#include "harddrive.h"

#include <QDebug>

SortedReqListModel::SortedReqListModel(QObject *parent,
                                       NewRequestsModel *newReqModel,
                                       HardDrive *hardDrive)
    : QAbstractListModel(parent),
      m_newReqModel(newReqModel),
      m_hardDrive(hardDrive)
{
}

int SortedReqListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return m_newReqModel->listSize();
}

QVariant SortedReqListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole)
        return m_list[index.row()].toString();

    return QVariant();
}

int SortedReqListModel::finishedTaskID() const
{
    return m_finishedTaskID;
}

void SortedReqListModel::updateList()
{
    // TODO: use existing vector
    //if (m_newReqModel->listSize())
      //  std::copy(m_newReqModel->list().begin(), m_newReqModel->list().end(), std::back_inserter(m_list));

    m_list.assign(m_newReqModel->list().begin(), m_newReqModel->list().end());

    Direction direction = m_hardDrive->curDirection();
    int curCylinder = m_hardDrive->position().cylinder;

    qDebug() << "HERE: " << curCylinder;
    if (direction == Direction::In)
        qDebug() << "IN";
    else
        qDebug() << "OUT";

    qDebug() << "BEFORE:";
    for (auto &i : m_list) {
        qDebug() << i.cylinder;
    }

    qDebug() << "AFTER:";
    if (direction == Direction::Out) {
        auto part = std::partition(m_list.begin(), m_list.end(),
                              [&](RequestModel const &rm) {
                return (rm.cylinder >= curCylinder);
        });
        qDebug() << "ITER: " << part->cylinder;
        std::sort(m_list.begin(), part, [&](RequestModel const &lhs, RequestModel const & rhs) { return (lhs.cylinder < rhs.cylinder); });
        std::sort(part, m_list.end(), [&](RequestModel const &lhs, RequestModel const & rhs) { return (lhs.cylinder > rhs.cylinder); });
    } else {
        auto part = std::partition(m_list.begin(), m_list.end(),
                              [&](RequestModel const &rm) {
                return (rm.cylinder <= curCylinder);
        });
        qDebug() << "ITER: " << part->cylinder;
        std::sort(m_list.begin(), part, [&](RequestModel const &lhs, RequestModel const & rhs) { return (lhs.cylinder > rhs.cylinder); });
        std::sort(part, m_list.end(), [&](RequestModel const &lhs, RequestModel const & rhs) { return (lhs.cylinder < rhs.cylinder); });
    }

    for (auto &i : m_list) {
        qDebug() << i.cylinder;
    }

    qDebug() << "size: " << m_list.size();

    QModelIndex start = index(0, 0);
    QModelIndex end = index(static_cast<int>(m_list.size()), 0);

    emit dataChanged(start, end);
}

void SortedReqListModel::execTask()
{

}
