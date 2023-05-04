
#include "OgreHeader.h"
#include "m2Bone.h"
#include "wowUtil.h"



void M2Bone::initV3(DataStream* m2stream,
	ModelBoneDef* mb,
	std::vector<std::shared_ptr<DataStream>>& animfiles,
	std::vector<uint32_t>& globalSequences)
{
	calc = false;

	pivot = fixCoordSystem(mb->pivot);
	billboard = (mb->flags & MODELBONE_BILLBOARD) != 0;
	
	boneDef = *mb;

	trans.init(mb->translation, m2stream, globalSequences.data(), animfiles);
	rot.init(mb->rotation, m2stream, globalSequences.data(), animfiles);
	scale.init(mb->scaling, m2stream, globalSequences.data(), animfiles);
	trans.fix(fixCoordSystem);
	rot.fix(fixCoordSystemQuat);
	scale.fix(fixCoordSystem2);
}



