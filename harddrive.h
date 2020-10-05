#ifndef HARDDRIVE_H
#define HARDDRIVE_H

struct HardDriveInfo
{
    float m_accessTime = 1;
    float m_rotationDelay = 0.5;
    float m_transferSpeed = 10.0;

    int m_cylinders = 10;
    int m_sectors = 30;
    int m_heads = 1;
};

class HardDrive
{
public:
    static HardDrive *instance();

    bool initHardDrive(HardDriveInfo &info);

    float accessTimeValue() const;
    float rotationDelayValue() const;
    float transferSpeedValue() const;

    int cylindersCount() const;
    int sectorsCount() const;
    int headsCount() const;
private:
    static HardDrive *m_instance;

    HardDrive() = default;
    HardDrive(const HardDrive &);
    HardDrive &operator=(HardDrive &);

    float m_accessTime = 1;
    float m_rotationDelay = 0.5;
    float m_transferSpeed = 10.0;

    int m_cylinders = 5;
    int m_sectors = 15;
    int m_heads = 1;
};

#endif // HARDDRIVE_H
