#include "HardDrive.h"

HardDrive::HardDrive(HardDriveInfo &info)
{
    // Check for input params
    if (info.m_accessTime > 0.0)
        m_accessTime = info.m_accessTime;
    else
        m_accessTime = 1;

    if (info.m_cylinders > 0)
        m_size.cylinder = info.m_cylinders;
    else
        m_size.cylinder = 5;

    if (info.m_heads > 0)
        m_size.head = info.m_heads;
    else
        m_size.head = 1;

    if (info.m_rotationDelay > 0.0)
        m_rotationDelay = info.m_rotationDelay;
    else
        m_rotationDelay = 2;

    if (info.m_sectors > 0)
        m_size.sector = info.m_sectors;
    else
        m_size.sector = 10;

    if (info.m_transferSpeed > 0.0)
        m_transferSpeed = info.m_transferSpeed;
    else
        m_transferSpeed = 10;

    // Set cur properties
    m_direction = Direction::Out;
    m_status = HardDriveStatus::Free;

    // Allocate space for data
    m_data = new bool**[m_size.head];
    for (int i = 0; i < m_size.head; i++)
    {
        m_data[i] = new bool*[m_size.cylinder];

        for (int j = 0; j < m_size.cylinder; j++)
        {
            m_data[j][i] = new bool[m_size.sector];
        }
    }
}

// Destructor
HardDrive::~HardDrive()
{
    for (int i = 0; i < m_size.cylinder; ++i)
    {
        for (int j = 0; j < m_size.sector; ++j)
        {
            delete [] m_data[m_size.cylinder][m_size.sector];
        }

        delete [] m_data[m_size.cylinder];
    }

    delete [] m_data;
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

HardDrivePointer HardDrive::position() const
{
    return m_position;
}

Direction HardDrive::curDirection() const
{
    return m_curDirection;
}

void HardDrive::getBitAt(HardDrivePointer position)
{
    setDirectionTo(position);

    m_reqPosition = position;

    m_status = HardDriveStatus::Read;
}

bool HardDrive::setBitAt(HardDrivePointer position, bool value)
{
    // Check for input parameters
    if (position.cylinder >= m_size.cylinder ||
            position.head >= m_size.head ||
            position.sector >= m_size.sector)
        return false;

    m_reqPosition = position;

    m_newValue = value;
    m_status = HardDriveStatus::Write;

    return true;
}

bool HardDrive::getFinishValue()
{
    bool val = m_newValue; // For thread safety

    m_status = HardDriveStatus::Free;

    return val;
}

void HardDrive::setDirectionTo(HardDrivePointer position)
{
    if (m_direction == Direction::In)
    {
        if (position.cylinder > m_position.cylinder)
            m_direction = Direction::Out;
    }
    else
    {
        if (position.cylinder < m_position.cylinder)
            m_direction = Direction::In;
    }
}

// Timers
void HardDrive::accessTimeTick()
{

}

void HardDrive::rotationDelayTick()
{

}

void HardDrive::dataTransferTick()
{

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
