#ifndef HARDDRIVE_H
#define HARDDRIVE_H

class HardDrive
{
public:
    static HardDrive *instance();

private:
    static HardDrive *m_instance;

    HardDrive() = default;
    HardDrive(const HardDrive &);
    HardDrive &operator=(HardDrive &);

    float m_accessTime = 1;
    float m_rotationDelay = 0.5;
    float m_transferSpeed = 10.0;

    int m_cylinders = 10;
    int m_sectors = 30;
    int m_heads = 1;
};

#endif // HARDDRIVE_H
