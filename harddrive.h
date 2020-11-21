#ifndef HARDDRIVE_H
#define HARDDRIVE_H

#include <QObject>
#include <QTimer>

#include "HardDriveInfo.h"
#include "RequestModel.h"

class HardDrive : public QObject
{
    Q_OBJECT

public:
    explicit HardDrive(HardDriveInfo *info);
    ~HardDrive();

    float accessTimeValue() const;
    float rotationDelayValue() const;
    float transferSpeedValue() const;

    int cylindersCount() const;
    int sectorsCount() const;
    int headsCount() const;

    HardDrivePointer position() const;
    Direction curDirection() const;

    bool getBitAt(RequestModel position);
    bool setBitAt(RequestModel position);
    bool getBitFastAt(int cyl, int head, int sec);

    bool getFinishValue();
    bool isFree();

    RequestModel requestModel();

public slots:
    void accessTimeTick();
    void rotationDelayTick();
    void dataTransferTick();
    void spinTick();
    void nextTask(RequestModel reqModel);

signals:
    void taskFinished(RequestModel reqModel);
    void dataChanged();

private:
    bool ***m_data; // Head -> Cylinder -> Sector !!

    float m_accessTime;
    float m_rotationDelay;
    float m_transferSpeed;

    HardDrivePointer m_size;
    HardDrivePointer m_position;
    HardDrivePointer m_reqPosition;
    RequestModel m_curRequest;

    Direction m_direction;
    HardDriveStatus m_status;
    bool m_newValue; // Value to Write / Read

    QTimer *m_accessTickTimer;
    QTimer *m_rotationDelayTimer;
    QTimer *m_dataTransferTimer;
    QTimer *m_spinTimer; // For free mode

    void setDirectionTo();
    void checkPosition();
};

#endif // HARDDRIVE_H
