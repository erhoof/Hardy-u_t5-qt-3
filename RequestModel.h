#ifndef REQUESTMODEL_H
#define REQUESTMODEL_H

#include <QTime>

struct RequestModel
{
    uint id;
    QString filename;

    uint cylinder;
    uint sector;

    QTime creationTime;
    QTime finishTime;

    int progressSecs()
    {
        return creationTime.secsTo(finishTime);
    }

    QString toString()
    {
        if (finishTime == creationTime)
            return QString("%1 (%2) [c%3:s%4] :: start At %5")
                    .arg(QString::number(id),
                         filename,
                         QString::number(cylinder),
                         QString::number(sector),
                         creationTime.toString("hh:mm:ss.z"));
        else
            return QString("%1 (%2) [c%3:s%4] :: for %5 secs")
                    .arg(QString::number(id),
                         filename,
                         QString::number(cylinder),
                         QString::number(sector),
                         QString::number(progressSecs()));
    }
};

#endif // REQUESTMODEL_H
