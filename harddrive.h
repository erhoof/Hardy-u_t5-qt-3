#ifndef HARDDRIVE_H
#define HARDDRIVE_H

#include <QObject>

enum class Direction {
    In, Out
};

struct HardDriveInfo
{
    float m_accessTime = 1;
    float m_rotationDelay = 0.5;
    float m_transferSpeed = 10.0;

    uint m_cylinders = 10;
    uint m_sectors = 30;
    uint m_heads = 1;
};

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
    Direction m_curDirection;

    // Speed multiplier for rotation
    uint m_counter = 0;
};

#endif // HARDDRIVE_H
