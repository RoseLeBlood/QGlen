#include "include/criticalsection.h"

QGLEN_BEGIN
CriticalSection::CriticalSection(void) : QMutex()
{
}

CriticalSection::~CriticalSection(void)
{
}
QGLEN_END
