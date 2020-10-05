#include "HardDrive.h"

HardDrive *HardDrive::m_instance = 0;

HardDrive *HardDrive::instance()
{
    if (!m_instance)
    {
        m_instance = new HardDrive();
    }

    return m_instance;
}

bool HardDrive::initHardDrive(HardDriveInfo &info)
{
    if (info.m_accessTime > 0.0)
        m_accessTime = info.m_accessTime;
    else
        return false;

    if (info.m_cylinders > 0)
        m_cylinders = info.m_cylinders;
    else
        return false;

    if (info.m_heads > 0)
        m_heads = info.m_heads;
    else
        return false;

    if (info.m_rotationDelay > 0.0)
        m_rotationDelay = info.m_rotationDelay;
    else
        return false;

    if (info.m_sectors > 0)
        m_sectors = info.m_sectors;
    else
        return false;

    if (info.m_transferSpeed > 0.0)
        m_transferSpeed = info.m_transferSpeed;
    else
        return false;

    return true;
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

int HardDrive::cylindersCount() const
{
    return m_cylinders;
}

int HardDrive::sectorsCount() const
{
    return m_sectors;
}

int HardDrive::headsCount() const
{
    return m_heads;
}