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

    uint m_cylinders = 10;
    uint m_sectors = 30;
    uint m_heads = 1;
};

#endif // HARDDRIVEINFO_H
