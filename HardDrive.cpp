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
