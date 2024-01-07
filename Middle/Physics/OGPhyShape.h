#ifndef OGPhyShape_h__
#define OGPhyShape_h__

#include "OgreVector3.h"
#include "OgreStringInterface.h"
#include "OgreDataStream.h"

class btCollisionShape;

namespace Orphigine
{
	class PhyCollection;
	class PhyCollectionSerializer;

	class PhyShape : public Ogre::StringInterface
	{
	public:
		PhyShape(const String& type);
		virtual ~PhyShape();

		virtual const Ogre::Vector3&		getLocalScaling() const = 0;
	
		virtual void						setLocalScaling(const Ogre::Vector3& val) = 0;

		btCollisionShape*					getBtShape() const ;

		const String&				getType() const;

		void								setType(const String& val);

		virtual	size_t						calcSize();		

		virtual void						writeToBinary(PhyCollectionSerializer* serializer,
			PhyCollection* system);

		virtual void						readFromBinary(PhyCollectionSerializer* serializer,Ogre::DataStreamPtr& stream,
			PhyCollection* system);

	protected:
		bool								_initBaseAttribute(const String& type);

	protected:
		btCollisionShape*					m_shape;
		String								m_type;

	private:
	};
}
#endif // OGPhyShape_h__