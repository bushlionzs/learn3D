/*=============================================================================
	Copyright (c) 2009 Beijing Kylin Network Information 
	Science and Technology Co, Ltd. All Rights Reserved.
	Filename : OGPhySoftBody.h
	Created:   ½ªÍþ 2008/10/20
	Description :	
    Revision :

=============================================================================*/

#ifndef OGPhySoftBody_h__
#define OGPhySoftBody_h__


#include "OgreMoveObject.h"
#include "OgreSceneNode.h"
#include "OgreAxisAlignedBox.h"

class btSoftBody;

namespace Orphigine
{
	class PhySoftBody : public Ogre::MoveObject
	{
	public:
		PhySoftBody();
		virtual ~PhySoftBody();

		/*
		 *	ÖØÔØOgreº¯Êý£¬¼ûOgre::MovableObject
		 */
		virtual const String&						getMovableType(void) const;

		virtual const Ogre::AxisAlignedBox&			getBoundingBox(void) const;

		virtual Real								getBoundingRadius(void) const;

		virtual void								_updateRenderQueue(Ogre::RenderQueue* queue);


		btSoftBody*									getBtSoftBody() const;

		void										setBtSoftBody(btSoftBody* val);

	protected:
		btSoftBody*									m_softBody;
		
		Ogre::SceneNode*							m_sceneNode;
		Ogre::AxisAlignedBox						m_boundingBox;
	private:
	};
}
#endif // OGPhySoftBody_h__
