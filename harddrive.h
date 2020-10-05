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
    static HardDrive *instance();

    bool initHardDrive(HardDriveInfo &info);

    float accessTimeValue() const;
    float rotationDelayValue() const;
    float transferSpeedValue() const;

    uint cylindersCount() const;
    uint sectorsCount() const;
    uint headsCount() const;

    Direction curDirection() const;

public slots:
    void tick();

private:
    static HardDrive *m_instance;

    HardDrive() = default;
    HardDrive(const HardDrive &);
    HardDrive &operator=(HardDrive &);

    float m_accessTime = 1;
    float m_rotationDelay = 0.5;
    float m_transferSpeed = 10.0;

    uint m_cylinders = 5;
    uint m_sectors = 15;
    uint m_heads = 1;

    uint m_curCylinder = 0;
    uint m_curSector = 0;
    Direction m_curDirection = Direction::In;
};

#endif // HARDDRIVE_H
