#ifndef OGSKELETONMESHCOMPONENTSERIALIZER_H
#define OGSKELETONMESHCOMPONENTSERIALIZER_H


#include "OgreSerializer.h"

namespace Orphigine
{
	class SkeletonMeshComponent;
	class SkeletonMeshComponentSerializerImpl;

	class _OrphigineExport SkeletonMeshComponentSerializer : public Ogre::Serializer
	{
	public:
		friend class SkeletonMeshComponentSerializerImpl;

		enum SkeletonMeshComponentFileFormatEnum
		{
			SMCFF_FILEHEADER					= 0x1000,// 文件头
			SMCFF_SKELETONMESHCOMPONENT			= 0x0100,
			//SMCFF_GENERAL			= 0x0200,
			//SMCFF_GRIDINFO			= 0x0300,
			//SMCFF_HEIGHTMAP			= 0x0400,
			//SMCFF_LIGHTMAP			= 0x0500,		
		};
		SkeletonMeshComponentSerializer(void);
		virtual ~SkeletonMeshComponentSerializer();

		bool exportSkeletonMeshComponentToFile(SkeletonMeshComponent* pSkeletonMeshComponent,const String& fileName,Ogre::Serializer::Endian endianMode = Ogre::Serializer::ENDIAN_NATIVE);
		bool importSkeletonMeshComponentFromStream(Ogre::DataStreamPtr& stream,SkeletonMeshComponent* pSkeletonMeshComponent);
		//兼容旧的文件格式//////////////////////////////////////////////////////////////////////
		struct LModelHeader
		{

			LModelHeader()
			{
				mFOUCC = 0;
				mVer = 0;
			}
			void init()
			{
				mFOUCC = 'LMOD';
				mVer = 101; //lmodel版本升级到101 by changhao
				mInfo = "Copyright (c) 2009 Beijing Kylin Network Information Science and Technology Co, Ltd. All Rights Reserved.";
			}
			bool isValid() 
			{
				if (mFOUCC != 'LMOD')
					return false;
				return true;
			}
			int mFOUCC;
			int mVer;
			std::string mInfo;
		};
		struct skeletonAnimationsMapInfoStr
		{
			std::string							skeletonMeshName;
			std::map<std::string,std::string>	skeletonAnimationsMap;
		};

		bool readInt(Ogre::MemoryDataStream * stream, int & i);
		bool readFloat(Ogre::MemoryDataStream * stream, float & i);
		bool readBool(Ogre::MemoryDataStream * stream, bool & i);
		bool readString(Ogre::DataStreamPtr& stream, std::string & str);

		bool importSkeletonMeshComponentFromOldStream(Ogre::DataStreamPtr& stream,SkeletonMeshComponent* pSkeletonMeshComponent,skeletonAnimationsMapInfoStr* pSkeletonAnimationsMapInfo);
		bool exportSkeletonMeshComponentToOldFile(SkeletonMeshComponent* pSkeletonMeshComponent,const String& fileName,Ogre::Serializer::Endian endianMode = Ogre::Serializer::ENDIAN_NATIVE);
		//兼容旧的文件格式//////////////////////////////////////////////////////////////////////
	protected:
		//版本
		static Ogre::String							mCurrentSkeletonMeshComponentVersion;
		typedef std::map<Ogre::String,				SkeletonMeshComponentSerializerImpl* > SkeletonMeshComponentSerializerImplMap;
		SkeletonMeshComponentSerializerImplMap		mSkeletonMeshComponentImplementations;
	};

	class SkeletonMeshComponentSerializerImpl : public Ogre::Serializer
	{
	public:	
		SkeletonMeshComponentSerializerImpl();
		virtual ~SkeletonMeshComponentSerializerImpl();
		bool exportSkeletonMeshComponentToFile(SkeletonMeshComponent* pSkeletonMeshComponent, const String& filename,Ogre::Serializer::Endian endianMode = Ogre::Serializer::ENDIAN_NATIVE);
		bool importSkeletonMeshComponentFromStream(Ogre::DataStreamPtr& stream, SkeletonMeshComponent* pSkeletonMeshComponent);

	protected:
		virtual bool	writeSkeletonMeshComponent(SkeletonMeshComponent* pSkeletonMeshComponent);
		virtual bool	readSkeletonMeshComponent(Ogre::DataStreamPtr& stream, SkeletonMeshComponent* pSkeletonMeshComponent);
		String mFileType;
		String mFileName;
	};
	
}

#endif // OGSKELETONMESHCOMPONENTSERIALIZER_H


