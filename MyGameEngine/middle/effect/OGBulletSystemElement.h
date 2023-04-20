#ifndef OGBulletSystemElement_h__
#define OGBulletSystemElement_h__

#include "OgreStringInterface.h"
#include "OgreQuaternion.h"

class Ogre::SceneNode;

namespace Orphigine
{
	class BulletSystemElement : public Ogre::StringInterface
	{
	public:
		BulletSystemElement(const String& typeName);
		virtual ~BulletSystemElement();

		class CmdOffsetPos : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdOffsetRotation : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		const Ogre::Vector3&		getOffsetPosition() const;
		void						setOffsetPosition(const Ogre::Vector3& val);

		const Ogre::Quaternion&		getOffsetQuaternion() const;
		void						setOffsetQuaternion(const Ogre::Quaternion& val);

		static CmdOffsetPos					ms_offsetPosCmd;
		static CmdOffsetRotation			ms_offsetRotationCmd;
	protected:
		bool						_initParameters(const String& typeName);

	protected:
		String						m_typeName;
		Ogre::SceneNode*			m_sceneNode;

		Ogre::Vector3				m_offsetPosition;
		Ogre::Quaternion			m_offsetQuaternion;
	private:
	};
}
#endif // OGBulletSystemElement_h__