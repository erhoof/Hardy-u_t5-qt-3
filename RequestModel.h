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

    uint cylinder;
    uint sector;
    uint head;

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
        if (finishTime == creationTime)
            return QString("%6 - %1 (%2) [c%3:h%7:s%4] :: start At %5")
                    .arg(QString::number(id),
                         filename,
                         QString::number(cylinder),
                         QString::number(sector),
                         creationTime.toString("hh:mm:ss.z"),
                         operationTypeString(),
                         QString::number(head));
        else
            return QString("%6 - %1 (%2) [c%3:h%7:s%4] :: for %5 secs")
                    .arg(QString::number(id),
                         filename,
                         QString::number(cylinder),
                         QString::number(sector),
                         QString::number(progressSecs()),
                         operationTypeString(),
                         QString::number(head));
    }
};

#endif // REQUESTMODEL_H
