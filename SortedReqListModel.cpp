#include "SortedReqListModel.h"

#include "NewRequestsModel.h"
#include "harddrive.h"

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
    m_list.assign(m_newReqModel->list().begin(), m_newReqModel->list().end());

    Direction direction = m_hardDrive->curDirection();
    int curCylinder = m_hardDrive->position().cylinder;

    for (auto &i : m_newReqModel->list())
    {
        if (direction == Direction::Out)
        {
            auto part = std::partition(m_list.begin(), m_list.end(),
                                  [&](RequestModel const &rm) {
                    return true;
            });
        }
    }
}

void SortedReqListModel::execTask()
{

}
