#ifndef OGPhyBoxShape_h__
#define OGPhyBoxShape_h__

#include "OGPhyShape.h"
#include "OgreVector3.h"

namespace Orphigine
{
	class PhyBoxShape : public PhyShape
	{
	public:
		PhyBoxShape(const Ogre::Vector3& size );
		virtual ~PhyBoxShape();

		class CmdSize : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		const Ogre::Vector3& getSize() const;
		void setSize(const Ogre::Vector3& val);

		static			CmdSize			ms_size;
	protected:
		Ogre::Vector3		m_size;

	private:
	};
}
#endif // OGPhyBoxShape_h__
