#include <stdio.h>

#include "platform_task.h"
#include "platform_util.h"
#include "platform_file_system.h"
#include "platform_common.h"



bool platform_init(bool is_init_filesystem)
{
	if (is_init_filesystem && false == CPlatformFileSystem::GetInstance()->InitFileSystem())
    {
		return false;
    }

	return true;
}

void platform_destroy()
{
}