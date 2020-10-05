#ifndef REQUESTMODEL_H
#define REQUESTMODEL_H

#include <QTime>

struct RequestModel
{
    uint id;
    QString filename;

    int cyllinder;
    int sector;

    QTime creationTime;
    QTime finishTime;

    int progressMsecs()
    {
        return creationTime.msecsTo(finishTime);
    }
};

#endif // REQUESTMODEL_H
