#ifndef HARDDRIVE_H
#define HARDDRIVE_H

#include <QObject>

#include "HardDriveInfo.h"

class HardDrive : public QObject
{
    Q_OBJECT

public:
    explicit HardDrive(HardDriveInfo &info);
    ~HardDrive();

    float accessTimeValue() const;
    float rotationDelayValue() const;
    float transferSpeedValue() const;

    int cylindersCount() const;
    int sectorsCount() const;
    int headsCount() const;

    HardDrivePointer position() const;
    Direction curDirection() const;

    void getBitAt(HardDrivePointer position);
    bool setBitAt(HardDrivePointer position, bool value);

    bool getFinishValue();

public slots:
    void accessTimeTick();
    void rotationDelayTick();
    void dataTransferTick();

signals:
    void byteReadFinish();
    void byteWriteFinish();

private:
    bool ***m_data; // Head -> Cylinder -> Sector !!

    float m_accessTime;
    float m_rotationDelay;
    float m_transferSpeed;

    HardDrivePointer m_size;
    HardDrivePointer m_position;
    HardDrivePointer m_reqPosition;

    Direction m_direction;
    HardDriveStatus m_status;
    bool m_newValue; // Value to Write / Read

    void setDirectionTo(HardDrivePointer position);
};

#endif // HARDDRIVE_H
