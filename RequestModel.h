#ifndef REQUESTMODEL_H
#define REQUESTMODEL_H

#include <QTime>

enum class OperationType
{
    Read, Write
};

struct RequestModel
{
    uint id;
    QString filename;

    int cylinder;
    int sector;
    int head;

    QTime creationTime;
    QTime finishTime;

    OperationType operationType;

    int progressSecs() const
    {
        return creationTime.secsTo(finishTime);
    }

    QString operationTypeString() const
    {
        if (operationType == OperationType::Read)
            return "Read";
        else
            return "Write";
    }

    QString toString() const
    {
        // TODO: Refactor to make counting correct
        if (finishTime == creationTime)
            return QString("%6 - %1 (%2) [c%3:h%7:s%4] :: start At %5")
                    .arg(QString::number(id),
                         filename,
                         QString::number(cylinder + 1),
                         QString::number(sector + 1),
                         creationTime.toString("hh:mm:ss.z"),
                         operationTypeString(),
                         QString::number(head + 1));
        else
            return QString("%6 - %1 (%2) [c%3:h%7:s%4] :: for %5 secs")
                    .arg(QString::number(id),
                         filename,
                         QString::number(cylinder + 1),
                         QString::number(sector + 1),
                         QString::number(progressSecs()),
                         operationTypeString(),
                         QString::number(head + 1));
    }
};

#endif // REQUESTMODEL_H
