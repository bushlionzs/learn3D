/*=============================================================================
	Copyright (c) 2009 Beijing Kylin Network Information 
	Science and Technology Co, Ltd. All Rights Reserved.
	Filename : OGPhyCollectionFileFormat.h
	Created:   ½ªÍþ 2008/10/13
	Description :	
    Revision :

=============================================================================*/

#ifndef OGPhyCollectionFileFormat_h__
#define OGPhyCollectionFileFormat_h__

namespace Orphigine
{
	enum PhyCollectionFileFormat
	{
		PC_FILEHEADER = 0x1000,
		PC_PHYSICS_WORLD = 0x2000,
		PC_PHYSICS_ACTOR = 0x3000,
		PC_PHYSICS_SHAPE =0x4000
	};
}
#endif // OGPhyCollectionFileFormat_h__