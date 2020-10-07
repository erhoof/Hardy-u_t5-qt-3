#ifndef HARDDRIVEINFO_H
#define HARDDRIVEINFO_H

enum class Direction {
    In, Out
};

struct HardDriveInfo
{
    float m_accessTime = 1;
    float m_rotationDelay = 0.5;
    float m_transferSpeed = 10.0;

    int m_cylinders = 10;
    int m_sectors = 30;
    int m_heads = 1;
};

struct HardDrivePointer
{
    int cylinder;
    int head;
    int sector;
};

#endif // HARDDRIVEINFO_H
