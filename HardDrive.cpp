#include "harddrive.h"

#include <QTimer>

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
            m_data[i][j] = new bool[m_size.sector];
        }
    }

    // Setup timers
    m_accessTickTimer = new QTimer(this);
    m_rotationDelayTimer = new QTimer(this);
    m_dataTransferTimer = new QTimer(this);
    m_spinTimer = new QTimer(this);

    connect(m_accessTickTimer, &QTimer::timeout, this, &HardDrive::accessTimeTick);
    connect(m_rotationDelayTimer, &QTimer::timeout, this, &HardDrive::rotationDelayTick);
    connect(m_dataTransferTimer, &QTimer::timeout, this, &HardDrive::dataTransferTick);
    connect(m_spinTimer, &QTimer::timeout, this, &HardDrive::spinTick);

    m_accessTickTimer->setInterval(m_accessTime);
    m_rotationDelayTimer->setInterval(m_rotationDelay);
    m_dataTransferTimer->setInterval(m_transferSpeed);
    m_spinTimer->setInterval(100);

    m_spinTimer->start();
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
    return m_direction;
}

int HardDrive::cylindersCount() const
{
    return m_size.cylinder;
}

int HardDrive::sectorsCount() const
{
    return m_size.sector;
}

int HardDrive::headsCount() const
{
    return m_size.head;
}

void HardDrive::getBitAt(HardDrivePointer position)
{
    setDirectionTo(position);

    m_reqPosition = position;

    m_status = HardDriveStatus::Read;

    // Start search timers
    m_spinTimer->stop(); // Stop animation
    m_accessTickTimer->start();
    m_rotationDelayTimer->start();
}

bool HardDrive::getBitFastAt(HardDrivePointer position)
{
    return m_data[position.head][position.cylinder][position.sector];
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

    m_spinTimer->stop(); // Stop animation
    m_accessTickTimer->start();
    m_rotationDelayTimer->start();

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

// Timer
void HardDrive::accessTimeTick()
{
    m_position.cylinder = m_reqPosition.cylinder;

    checkPosition();

    m_accessTickTimer->stop();
}

void HardDrive::rotationDelayTick()
{
    m_position.sector = m_reqPosition.sector;

    checkPosition();

    m_rotationDelayTimer->stop();
}

void HardDrive::dataTransferTick()
{
    if (m_status == HardDriveStatus::Read)
    {
        m_newValue = m_data[m_reqPosition.head][m_reqPosition.cylinder][m_reqPosition.sector];
        // Free is not set for thread safety
        emit byteReadFinish();
    }
    else if (m_status == HardDriveStatus::Write)
    {
        m_data[m_reqPosition.head][m_reqPosition.cylinder][m_reqPosition.sector] = m_newValue;
        m_status = HardDriveStatus::Free;
        emit dataChanged();
        emit byteWriteFinish();
    }

    m_dataTransferTimer->stop();
    m_spinTimer->start(); // Start animation
}

void HardDrive::spinTick()
{
    if (m_position.cylinder == 0)
        m_direction = Direction::Out;
    else if (m_position.cylinder == m_size.cylinder - 1)
        m_direction = Direction::In;

    if (m_direction == Direction::In)
        m_position.cylinder--;
    else
        m_position.cylinder++;

    if (m_position.sector == m_size.sector - 1)
        m_position.sector = 0;
    else
        m_position.sector++;

    emit dataChanged();
}

// Check if got req position
void HardDrive::checkPosition()
{
    if (m_position == m_reqPosition)
        m_dataTransferTimer->start();
}
