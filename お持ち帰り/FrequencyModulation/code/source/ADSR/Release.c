#include "../../include/ADSR/Release.h"

void Release_Constructor(Release* release)
{
	Release_SetDuration(release, 0);
}

void Release_SetDuration(Release* release, const uint32_t duration)
{
	release->duration = duration;
}
