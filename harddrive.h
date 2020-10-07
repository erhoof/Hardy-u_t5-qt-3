#ifndef HARDDRIVE_H
#define HARDDRIVE_H

#include <QObject>

#include "HardDriveInfo.h"

class HardDrive : public QObject
{
    Q_OBJECT

public:
    explicit HardDrive(HardDriveInfo &info);

    float accessTimeValue() const;
    float rotationDelayValue() const;
    float transferSpeedValue() const;

    uint cylindersCount() const;
    uint sectorsCount() const;
    uint headsCount() const;

    Direction curDirection() const;
    uint curCylinder() const;
    uint curSector() const;

public slots:
    void accessTimeTick();
    void rotationDelayTick();
    void dataTransferTick();

private:
    float m_accessTime;
    float m_rotationDelay;
    float m_transferSpeed;

    uint m_cylinders;
    uint m_sectors;
    uint m_heads;

    uint m_curCylinder;
    uint m_curSector;
    Direction m_curDirection ;

    // Speed multiplier for rotation
    uint m_counter = 0;
};

#endif // HARDDRIVE_H
