/*=============================================================================
	Copyright (c) 2009 Beijing Kylin Network Information 
	Science and Technology Co, Ltd. All Rights Reserved.
	Filename : OGCollisionBuildingZonePageFileFormat.h
	Created:    ½ªÍþ 2008/09/09
	Description :	
    Revision :

=============================================================================*/

#ifndef OGCollisionBuildingZonePageFileFormat_h__
#define OGCollisionBuildingZonePageFileFormat_h__

namespace Orphigine
{
	enum CollisionBuildingFileFormat
	{
		CB_FILEHEADER = 0x1000,
		CB_PHYSICS_SPACE = 0x2000,
		CB_PHYSICS_ACTOR = 0x3000,
		CB_PHYSICS_SHAPE =0x4000
	};
}
#endif // OGCollisionBuildingZonePageFileFormat_h__