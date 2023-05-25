#include "OgreHeader.h"
#include "OGPhyCollectionSerializer.h"
#include "OGPhyCollectionFileFormat.h"
#include "OGPhyCollection.h"
#include "OGPhyActor.h"
#include "OGPhyCookedTriangleMesh.h"
#include "OGPhyCookedTriangleMeshManager.h"
#include "OGPhyStaticConcaveShape.h"
#include "OGPhyUtil.h"

#include "OgreException.h"
#include "OgreVector3.h"
#include "OgreQuaternion.h"

#include "btBulletCollisionCommon.h"

namespace Orphigine
{

	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);

	PhyCollectionSerializer::PhyCollectionSerializer()
	{	
		mVersion = "[Serializer_v1.10]";
	}

	PhyCollectionSerializer::~PhyCollectionSerializer()
	{

	}

	void PhyCollectionSerializer::exportPhyCollection( PhyCollection* PhyCollection,const String& name,Endian endianMode /*= ENDIAN_NATIVE*/ )
	{
		
	}

	void PhyCollectionSerializer::importPhyCollection( Ogre::DataStreamPtr& stream,PhyCollection* PhyCollection )
	{
		// Determine endianness (must be the first thing we do!)
		determineEndianness(stream);

		// Check header
		readFileHeader(stream);

		readPhysicsSpace(stream,PhyCollection);

	}

	void PhyCollectionSerializer::writePhysicsSpace( PhyCollection* PhyCollection)
	{
		
	}

	void PhyCollectionSerializer::writePhysicsActors( PhyCollection* PhyCollection ,const PhyActor* physicsActor)
	{
		

	}

	void PhyCollectionSerializer::writePhysicsShapes( PhyCollection* PhyCollection,PhyShape* physicsShape )
	{
		physicsShape->writeToBinary(this,PhyCollection);
	}

	void PhyCollectionSerializer::readPhysicsSpace( Ogre::DataStreamPtr& stream,PhyCollection* PhyCollection )
	{

		unsigned short streamID = readChunk(stream);

		if(PC_PHYSICS_WORLD == streamID && !stream->eof())
		{
			streamID = readChunk(stream);
			while (PC_PHYSICS_ACTOR == streamID && !stream->eof())
			{
				readPhysicsActors(stream,PhyCollection);

				if(!stream->eof())
					streamID = readChunk(stream);
			}
			if (!stream->eof())
			{
				// Backpedal back to start of this stream if we've found a non-track
				stream->skip(-STREAM_OVERHEAD_SIZE);
			}
		}
	}

	void PhyCollectionSerializer::readPhysicsActors( Ogre::DataStreamPtr& stream,PhyCollection* PhyCollection )
	{

		Ogre::Vector3 tmpPosition; 
		readObject(stream,tmpPosition);// 读取Actor的偏移信息 [9/26/2008 JiangWei]

		Ogre::Quaternion tmpRotation;
		readObject(stream,tmpRotation);// 读取Actor的旋转信息 [9/26/2008 JiangWei]

		PhyActor* physicsActor = new PhyActor(tmpPosition,tmpRotation);

		size_type tFind = mVersion.find("_v");
		String subStr = mVersion.substr(tFind + 2, 4);
		float fVer = Ogre::StringConverter::parseReal(subStr);

		if (fVer >= 1.20)
		{
			uint32_t iType = 0;
			readInts(stream, &iType, 1);
			physicsActor->setTypeWorld(iType);
		}

		// 接下来读取此Actor中包含的Shapes [9/26/2008 JiangWei]
		unsigned short streamID;
		if	(!stream->eof())
		{
			streamID = readChunk(stream);

			while (PC_PHYSICS_SHAPE == streamID && !stream->eof())
			{
				readPhysicsShapes(stream,PhyCollection,physicsActor);

				if(!stream->eof())
					streamID = readChunk(stream);
			}
			if (!stream->eof())
			{
				// Backpedal back to start of this stream if we've found a non-track
				stream->skip(-STREAM_OVERHEAD_SIZE);
			}
		}

	}

	void PhyCollectionSerializer::readPhysicsShapes( Ogre::DataStreamPtr& stream,PhyCollection* PhyCollection ,
		PhyActor* physicsActor)
	{
		String physicsShapeType = readString(stream);

		PhyShape* physicsShape = NULL;

		String cookedTriangleMeshName = readString(stream);// CookedTriangleMesh模型资源名 [9/26/2008 JiangWei]

		Ogre::Vector3 localScaling;
		readObject(stream,localScaling);//  [9/26/2008 JiangWei]

		if("StaticConcaveShape" == physicsShapeType)
			physicsShape = new PhyStaticConcaveShape(cookedTriangleMeshName,localScaling);

		physicsActor->setShape(physicsShape);

		assert(NULL != physicsShape && "PhyCollectionSerializer::readPhysicsShapes");

		PhyCollection->addActor(physicsActor);
	}


	size_t PhyCollectionSerializer::calcPhysicsSpace( PhyCollection* PhyCollection )
	{
		size_t spaceSize = STREAM_OVERHEAD_SIZE;

		return spaceSize;
	}

	size_t PhyCollectionSerializer::calcPhysicsActors( const PhyActor* physicsActor )
	{
		size_t actorSize = STREAM_OVERHEAD_SIZE;

		actorSize += sizeof(Ogre::Vector3);// Physics Actor Position [9/25/2008 JiangWei]

		actorSize += sizeof(Ogre::Quaternion);// Physics Actor Rotation [9/25/2008 JiangWei]

		return actorSize;
	}

	size_t PhyCollectionSerializer::calcPhysicsShape( PhyShape* physicsSpace )
	{
		size_t shapeSize = STREAM_OVERHEAD_SIZE;

		return shapeSize;
	}

}