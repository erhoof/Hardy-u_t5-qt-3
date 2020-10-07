#include "HardDrive.h"

HardDrive::HardDrive(HardDriveInfo &info)
{
    if (info.m_accessTime > 0.0)
        m_accessTime = info.m_accessTime;
    else
        m_accessTime = 1;

    if (info.m_cylinders > 0)
        m_cylinders = info.m_cylinders;
    else
        m_cylinders = 5;

    if (info.m_heads > 0)
        m_heads = info.m_heads;
    else
        m_heads = 1;

    if (info.m_rotationDelay > 0.0)
        m_rotationDelay = info.m_rotationDelay;
    else
        m_rotationDelay = 2;

    if (info.m_sectors > 0)
        m_sectors = info.m_sectors;
    else
        m_sectors = 10;

    if (info.m_transferSpeed > 0.0)
        m_transferSpeed = info.m_transferSpeed;
    else
        m_transferSpeed = 10;

    m_curCylinder = 0;
    m_curSector = 0;
    m_curDirection = Direction::Out;
}

float HardDrive::accessTimeValue() const
{
    return m_accessTime;
}

float HardDrive::rotationDelayValue() const
{
    return m_rotationDelay;
}

float HardDrive::transferSpeedValue() const
{
    return m_transferSpeed;
}

uint HardDrive::cylindersCount() const
{
    return m_cylinders;
}

uint HardDrive::sectorsCount() const
{
    return m_sectors;
}

uint HardDrive::headsCount() const
{
    return m_heads;
}

uint HardDrive::curCylinder() const
{
    return m_curCylinder;
}

uint HardDrive::curSector() const
{
    return m_curSector;
}

Direction HardDrive::curDirection() const
{
    return m_curDirection;
}

/*void HardDrive::tick()
{
    if (m_counter == 3) {
        if (m_curCylinder == 0)
            m_curDirection = Direction::Out;
        else if (m_curCylinder == m_cylinders - 1)
            m_curDirection = Direction::In;

        if (m_curDirection == Direction::In)
            m_curCylinder--;
        else
            m_curCylinder++;
        m_counter = 0;
    }
    else
    {
        m_counter++;
    }

    if (m_curSector == m_sectors - 1)
        m_curSector = 0;
    else
        m_curSector++;
}*/
