#include "OgreHeader.h"
#include "OGCollisionBuildingSerializer.h"
#include "OGCollisionBuildingFileFormat.h"
#include "OGCollisionBuilding.h"
#include "terrain_info.h"
#include "engine_manager.h"
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

	CollisionBuildingSerializer::CollisionBuildingSerializer()
	{	
		mVersion = "[Serializer_v1.10]";
	}

	CollisionBuildingSerializer::~CollisionBuildingSerializer()
	{

	}

	void CollisionBuildingSerializer::exportCollisionBuilding( CollisionBuilding* collisionBuilding,const String& name,Endian endianMode /*= ENDIAN_NATIVE*/ )
	{
		
	}

	void CollisionBuildingSerializer::importCollisionBuilding( Ogre::DataStreamPtr& stream,CollisionBuilding* collisionBuilding )
	{
		// Determine endianness (must be the first thing we do!)
		determineEndianness(stream);

		// Check header
		readFileHeader(stream);

		// 读取CBuilding数据 [5/5/2008 JiangWei]
		//Ogre::LogManager::getSingleton().logMessage("Collision Building..",Ogre::LML_TRIVIAL);
		readPhysicsSpace(stream,collisionBuilding);
		//Ogre::LogManager::getSingleton().logMessage("Collision Building imported.",Ogre::LML_TRIVIAL);

	}

	void CollisionBuildingSerializer::writePhysicsSpace( CollisionBuilding* collisionBuilding)
	{
		
	}

	void CollisionBuildingSerializer::writePhysicsActors( CollisionBuilding* collisionBuilding ,PhyActor* physicsActor)
	{
		

	}

	void CollisionBuildingSerializer::writePhysicsShapes( CollisionBuilding* collisionBuilding,PhyShape* physicsShape )
	{
		//physicsShape->writeToBinary(this,collisionBuilding);
	}

	void CollisionBuildingSerializer::readPhysicsSpace( Ogre::DataStreamPtr& stream,CollisionBuilding* collisionBuilding )
	{

		unsigned short streamID = readChunk(stream);

		if(CB_PHYSICS_SPACE == streamID && !stream->eof())
		{
			streamID = readChunk(stream);
			while (CB_PHYSICS_ACTOR == streamID && !stream->eof())
			{
				readPhysicsActors(stream,collisionBuilding);

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

	void CollisionBuildingSerializer::readPhysicsActors( Ogre::DataStreamPtr& stream,CollisionBuilding* collisionBuilding )
	{

		Ogre::Vector3 tmpPosition; 
		readObject(stream,tmpPosition);
		Ogre::Quaternion tmpRotation;
		readObject(stream,tmpRotation);

		btTransform tmpTrans;
		tmpTrans.setIdentity();

		tmpTrans.setOrigin(ogreToBulletVector3(tmpPosition));

		tmpTrans.setRotation(ogreToBulletQuaternion(tmpRotation));

		PhyActor* physicsActor = new PhyActor(tmpPosition,tmpRotation);

		physicsActor->getBtActor()->setWorldTransform(tmpTrans);

		size_type tFind = mVersion.find("_v");
		String subStr = mVersion.substr(tFind + 2, 4);
		float fVer = Ogre::StringConverter::parseReal(subStr);
		if (fVer >= 1.20)
		{
			uint32_t iType = 0;
			readInts(stream, &iType, 1);
			physicsActor->setTypeWorld(iType);
		}

		unsigned short streamID;
		if	(!stream->eof())
		{
			streamID = readChunk(stream);

			while (CB_PHYSICS_SHAPE == streamID && !stream->eof())
			{
				readPhysicsShapes(stream,collisionBuilding,physicsActor);

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

	void CollisionBuildingSerializer::readPhysicsShapes( Ogre::DataStreamPtr& stream,CollisionBuilding* collisionBuilding ,
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

		assert(NULL != physicsShape && "CollisionBuildingSerializer::readPhysicsShapes");

		collisionBuilding->addCollisionActor(physicsActor);
	}


	size_t CollisionBuildingSerializer::calcPhysicsSpace( CollisionBuilding* collisionBuilding )
	{
		size_t spaceSize = STREAM_OVERHEAD_SIZE;

		return spaceSize;
	}

	size_t CollisionBuildingSerializer::calcPhysicsActors( PhyActor* physicsActor )
	{
		size_t actorSize = STREAM_OVERHEAD_SIZE;

		actorSize += sizeof(Ogre::Vector3);// Physics Actor Position [9/25/2008 JiangWei]

		actorSize += sizeof(Ogre::Quaternion);// Physics Actor Rotation [9/25/2008 JiangWei]

		return actorSize;
	}

	size_t CollisionBuildingSerializer::calcPhysicsShape( PhyShape* physicsSpace )
	{
		size_t shapeSize = STREAM_OVERHEAD_SIZE;

		return shapeSize;
	}
	
}