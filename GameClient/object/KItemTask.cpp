#include "OgreHeader.h"
#include "KItemTask.h"

KItemTask::KItemTask(uint64_t id)
	:KItem(id)
{
	mObjectType = ObjectType_ItemTask;
}

KItemTask::~KItemTask()
{

}
