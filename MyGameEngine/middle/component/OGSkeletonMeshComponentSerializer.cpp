#include "OgreHeader.h"
#include "OGSkeletonMeshComponentSerializer.h"
#include <platform_log.h>
#include "OGSkeletonMeshComponent.h"
#include "OgreMemoryStream.h"
#include "OgreSerializer.h"

namespace Orphigine
{
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ogre::String	SkeletonMeshComponentSerializer::mCurrentSkeletonMeshComponentVersion = "[SkeletonMeshComponentSerializer_v1.00]";
SkeletonMeshComponentSerializer::SkeletonMeshComponentSerializer(void)
{
	// Set up map
	mSkeletonMeshComponentImplementations.insert(SkeletonMeshComponentSerializerImplMap::value_type("[SkeletonMeshComponentSerializer_v1.00]",new SkeletonMeshComponentSerializerImpl() ));       
}
SkeletonMeshComponentSerializer::~SkeletonMeshComponentSerializer()
{
	// delete map
	for (SkeletonMeshComponentSerializerImplMap::iterator i = mSkeletonMeshComponentImplementations.begin();i != mSkeletonMeshComponentImplementations.end(); ++i)
	{
		delete i->second;
	}
	mSkeletonMeshComponentImplementations.clear();	
}
bool SkeletonMeshComponentSerializer::exportSkeletonMeshComponentToFile(SkeletonMeshComponent* pSkeletonMeshComponent,const String& fileName,Ogre::Serializer::Endian endianMode)
{
	SkeletonMeshComponentSerializerImplMap::iterator implSkeletonMeshComponent = mSkeletonMeshComponentImplementations.find(mCurrentSkeletonMeshComponentVersion);
	if (implSkeletonMeshComponent == mSkeletonMeshComponentImplementations.end())
	{
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot find serializer implementation for "
			"current version " + mCurrentSkeletonMeshComponentVersion, "SkeletonMeshComponentSerializer::exportSkeletonMeshComponentToFile");
		return false;
	}
	implSkeletonMeshComponent->second->exportSkeletonMeshComponentToFile(pSkeletonMeshComponent, fileName, endianMode);
	return true;
}
bool SkeletonMeshComponentSerializer::importSkeletonMeshComponentFromStream(Ogre::DataStreamPtr& stream, SkeletonMeshComponent* pSkeletonMeshComponent)
{
	if(stream)
	{
		//文件头
		unsigned short headerID = 0;
		stream->read(&headerID, sizeof(unsigned short));// Read header ID
		unsigned int length = 0 ;
		stream->read(&length,sizeof(unsigned int));
		char * pStr = new char[length];
		stream->read(pStr,sizeof(char)*length);
		pStr[length-1] = 0;
		String version = String(pStr);
		delete[] pStr;
		stream->seek(0);	
		SkeletonMeshComponentSerializerImplMap::iterator impl = mSkeletonMeshComponentImplementations.find(version);//找到合适的解析器
		if (impl == mSkeletonMeshComponentImplementations.end())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot find serializer implementation for "
				"current version " + version, "SkeletonMeshComponentSerializer::importSkeletonMeshComponentFromStream");
			return false;
		}	
		impl->second->importSkeletonMeshComponentFromStream(stream, pSkeletonMeshComponent);	
		if (version != mCurrentSkeletonMeshComponentVersion)//写log，警告
		{

		}
		return true;	
	}	
	return false;
}
bool SkeletonMeshComponentSerializer::readInt(Ogre::MemoryDataStream * stream, int & i)
{
	size_t sizeRead = stream->read(&i, sizeof(int));
	if (sizeRead != sizeof(int))
		return false;
	return true;
}
bool SkeletonMeshComponentSerializer::readFloat(Ogre::MemoryDataStream * stream, float & i)
{
	size_t sizeRead = stream->read(&i, sizeof(float));
	if (sizeRead != sizeof(float))
		return false;
	return true;
}
bool SkeletonMeshComponentSerializer::readBool(Ogre::MemoryDataStream * stream, bool & i)
{
	size_t sizeRead = stream->read(&i, sizeof(bool));
	if (sizeRead != sizeof(bool))
		return false;
	return true;
}
bool SkeletonMeshComponentSerializer::readString(Ogre::DataStreamPtr& stream, std::string & str)
{
	int size = 0;
	readData(stream, &size, sizeof(int), 1);
    str.clear();
    if (size == 0) 
		return true;
	char buf[1024];
	if (size >= sizeof(buf))
		return false;
	readData(stream, buf, size, 1);
	buf[size] = 0;
	str = buf;
	return true;
}

bool SkeletonMeshComponentSerializer::exportSkeletonMeshComponentToOldFile(SkeletonMeshComponent* pSkeletonMeshComponent,const String& fileName,Ogre::Serializer::Endian endianMode)
{
	

	return true;
}

bool SkeletonMeshComponentSerializer::importSkeletonMeshComponentFromOldStream(Ogre::DataStreamPtr& stream,SkeletonMeshComponent* pSkeletonMeshComponent,skeletonAnimationsMapInfoStr* pSkeletonAnimationsMapInfo)
{
	if(stream && pSkeletonMeshComponent)
	{
		LModelHeader header;
		readData(stream, &header.mFOUCC, sizeof(header.mFOUCC), 1);
		readData(stream, &header.mVer, sizeof(header.mVer), 1);
		readString(stream, header.mInfo);
		if (!header.isValid())
			return false;
		Ogre::String realObjectName;

		readString(stream, realObjectName);


		String baseName = realObjectName;
		pSkeletonMeshComponent->setName(baseName);

		//attributes
		{
			int attributeNum = 0;
			readData(stream, &attributeNum, sizeof(attributeNum), 1);
			String name, value, hints;
			for (int i=0; i<attributeNum; i++)
			{
				
				readString(stream, name);
				readString(stream, value);
				readString(stream, hints);

				pSkeletonMeshComponent->addAttribute(name, value,pSkeletonMeshComponent->getAttributeTypeFromString(hints));
			}

		}

		//Entitys
		{
			int entityNum = 0;
			readData(stream, &entityNum, sizeof(entityNum), 1);
			String name, file, material;
			for (int i=0; i<entityNum; i++)
			{
				readString(stream, name);
				readString(stream, file);
				readString(stream, material);

				pSkeletonMeshComponent->addEntity(name, file, material);
			}
		}

		//MaterialList
		{
			int materialNum = 0;
			readData(stream, &materialNum, sizeof(materialNum), 1);
			String name, entity, material;
			for (int i=0; i<materialNum; i++)
			{
				readString(stream, name);
				readString(stream, entity);
				readString(stream, material);

				pSkeletonMeshComponent->addMaterial(name, entity, material);

			}
		}

		//locators
		{
			int locatorsNum = 0;
	
			readData(stream, &locatorsNum, sizeof(locatorsNum), 1);

			String name, bonename;
			for (int i=0; i<locatorsNum; i++)
			{
				bool addSlot = true;

				
				float x,y,z;
				float qx,qy,qz,qw;
				bool transferable, translateFirst, childInheritScale;
				String DestLocator;

				Ogre::Vector3 LocatorOffPos = Ogre::Vector3::ZERO;
				Ogre::Quaternion LocatorOffRot = Ogre::Quaternion::IDENTITY;

				readString(stream, name);
				readString(stream, bonename);

				readData(stream, &x, sizeof(x), 1);
				readData(stream, &y, sizeof(y), 1);
				readData(stream, &z, sizeof(z), 1);
		

				LocatorOffPos.x = x; LocatorOffPos.y = y; LocatorOffPos.z = z;

				readData(stream, &qx, sizeof(qx), 1);
				readData(stream, &qy, sizeof(qy), 1);
				readData(stream, &qz, sizeof(qz), 1);
				readData(stream, &qw, sizeof(qw), 1);
				LocatorOffRot.FromAngleAxis(Ogre::Radian(qw), Ogre::Vector3(qx, qy, qz));//这里计算出四元数


				readData(stream, &transferable, sizeof(transferable), 1);
				readData(stream, &translateFirst, sizeof(translateFirst), 1);
				readData(stream, &childInheritScale, sizeof(childInheritScale), 1);
				readString(stream, DestLocator);


				if (DestLocator.size() > 0)	
				{				
					transferable = true;				
				}

				if( false == pSkeletonMeshComponent->addLocator(name, bonename, LocatorOffPos, LocatorOffRot, 
					transferable, translateFirst, childInheritScale, 
					DestLocator) )
				{				
					addSlot = false;
				}

				int slotNum = 0;
				readData(stream, &slotNum, sizeof(slotNum), 1);
	
				if (slotNum > 0)  
				{				
					String slotname, object, attribs;
					for (int j=0; j<slotNum; j++)
					{
						readString(stream, slotname);
						readString(stream, object);
						readString(stream, attribs);
		

						if (!object.empty())
						{
							char buf[1024];
							strncpy(buf, object.c_str(), sizeof(buf)-1);
							buf[sizeof(buf)-1] = 0;

							char * p = strstr(buf, ".obj");
							if (p) 
							{
								p[0] = 0;
								object = buf + String(".lmodel");
							}
						}

						if (addSlot)
						{
							pSkeletonMeshComponent->addSlot(name, slotname, object);
						}
					}
				}
			}
		}

		//effects
		{
			int effectsNum = 0;
			readData(stream, &effectsNum, sizeof(effectsNum), 1);
			String name, effect, locator;

			for (int i=0; i<effectsNum; i++)
			{
				
				bool translateAll;
				Ogre::ColourValue colour;
				readString(stream, name);
				readString(stream, effect);
				readString(stream, locator);

				readData(stream, &translateAll, sizeof(translateAll), 1);
				readData(stream, &colour.r, sizeof(colour.r), 1);
				readData(stream, &colour.g, sizeof(colour.g), 1);
				readData(stream, &colour.b, sizeof(colour.b), 1);
				readData(stream, &colour.a, sizeof(colour.a), 1);

				Ogre::Vector3 OffsetPos = Ogre::Vector3::ZERO;
				Ogre::Quaternion OffsetQuat = Ogre::Quaternion::IDENTITY;
				if (header.mVer == 101)
				{
					readData(stream, &OffsetPos[0], sizeof(OffsetPos[0]), 1);
					readData(stream, &OffsetPos[1], sizeof(OffsetPos[1]), 1);
					readData(stream, &OffsetPos[2], sizeof(OffsetPos[2]), 1);
					readData(stream, &OffsetQuat.w, sizeof(OffsetQuat.w), 1);
					readData(stream, &OffsetQuat.x, sizeof(OffsetQuat.x), 1);
					readData(stream, &OffsetQuat.y, sizeof(OffsetQuat.y), 1);
					readData(stream, &OffsetQuat.z, sizeof(OffsetQuat.z), 1);
				}

				pSkeletonMeshComponent->addEffectInfo(name, effect, locator, translateAll, colour, OffsetPos, OffsetQuat);			
			}
		}

		//shadowUncasts
		{
			int shadowUncastsNum = 0;
			readData(stream, &shadowUncastsNum, sizeof(shadowUncastsNum), 1);

			String meshname;

			for (int i=0; i<shadowUncastsNum; i++)
			{
				readString(stream, meshname);

				pSkeletonMeshComponent->addShadowUncastable(meshname);
			}
		}

		//skeleton links
		{
			int skeletonNum = 0;
			readData(stream, &skeletonNum, sizeof(skeletonNum), 1);

			if (skeletonNum)
			{
				// 新建一个link map
				if(pSkeletonAnimationsMapInfo)
					pSkeletonAnimationsMapInfo->skeletonMeshName = baseName;
				//AnimationSkeletonLinks* links = _createAnimationSkeletonLinksForModel(baseName);
				String skeleton, animations;
				for (int i=0; i<skeletonNum; ++i)
				{
					readString(stream, skeleton);
					readString(stream, animations);

					if (skeleton.empty() || animations.empty())
					{
						assert(false);
						continue;
					}
					if(pSkeletonAnimationsMapInfo)
					{
						pSkeletonAnimationsMapInfo->skeletonAnimationsMap.insert(std::make_pair(skeleton,animations));
					}
					
				}
			}
		}
		//aas
		{																																																																																																																																														
			int aasNum = 0;
			readData(stream, &aasNum, sizeof(aasNum), 1);

			String name;
			for (int i=0; i<aasNum; i++)
			{
				readString(stream, name);

				pSkeletonMeshComponent->setAdvancedAnimationSystemName(name);			
			}
		}

		//fabrics,无用信息，为了兼容旧的文件格式
		{
			int fabricsNum = 0;
			readData(stream, &fabricsNum, sizeof(fabricsNum), 1);
			String name, locator, info;
			for (int i=0; i<fabricsNum; i++)
			{
				readString(stream, name);
				readString(stream, locator);
				readString(stream, info);
			}
		}	
		return true;
	}

	return false;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
SkeletonMeshComponentSerializerImpl::SkeletonMeshComponentSerializerImpl()
{
	mFileType = "SKEB";	
	mVersion = SkeletonMeshComponentSerializer::mCurrentSkeletonMeshComponentVersion;
}
SkeletonMeshComponentSerializerImpl::~SkeletonMeshComponentSerializerImpl()
{
}
bool SkeletonMeshComponentSerializerImpl::exportSkeletonMeshComponentToFile(SkeletonMeshComponent* pSkeletonMeshComponent, const String& filename,Ogre::Serializer::Endian endianMode)
{	
	
	return true;
}
bool SkeletonMeshComponentSerializerImpl::writeSkeletonMeshComponent(SkeletonMeshComponent* pSkeletonMeshComponent)
{
	if(pSkeletonMeshComponent )
	{
		return pSkeletonMeshComponent->saveToBinaryFile(this);	
	}
	return false;
}
bool SkeletonMeshComponentSerializerImpl::importSkeletonMeshComponentFromStream(Ogre::DataStreamPtr& stream, SkeletonMeshComponent* pSkeletonMeshComponent)
{	
	mFileName = stream->getName();
	//WARNING_LOG("SkeletonMeshComponentSerializer import data...",Ogre::LML_TRIVIAL);
	determineEndianness(stream);
	//readFileHeader(stream);
	unsigned short headerID = 0;
	readShorts(stream, &headerID, 1);
    if (headerID == HEADER_STREAM_ID)
	{
		String version = readStringBin(stream);
		if (version != mVersion)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, 
                    "Invalid file: version incompatible, file reports " + version +
                    " Serializer is version " + mVersion,
                    "TerrainSerializerImpl::importTerrainFromStream");
		}
	}
	else
	{
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Invalid file: no header","TerrainSerializerImpl::readFileHeader");
		return false;
	}
	String FileType = readStringBin(stream);
    String CopyRight = readStringBin(stream);
	if (FileType != mFileType)
	{
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, 
			"Invalid file: type incompatible, file reports " + String(FileType) + 
			" Serializer is type " + mFileType,
			"TerrainSerializer::importTerrainFromStream");
		return false;
	}
	readSkeletonMeshComponent(stream,pSkeletonMeshComponent);
	//WARNING_LOG("SkeletonMeshComponentSerializer import successful.",Ogre::LML_TRIVIAL);
	return true;
}
bool SkeletonMeshComponentSerializerImpl::readSkeletonMeshComponent(Ogre::DataStreamPtr& stream, SkeletonMeshComponent* pSkeletonMeshComponent)
{
	if(pSkeletonMeshComponent )
	{
		return pSkeletonMeshComponent->loadFromStream(this,stream);
	}
	return false;
}

}
