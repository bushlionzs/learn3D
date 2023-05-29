#ifndef OGRECPURESOURCE_H
#define OGRECPURESOURCE_H


#include "OgreDataStream.h"
#include "OgreImage.h"
//#include "OgreMemory.h"
//#include "OgreMemoryMeshData.h"

#ifndef RESOURCE_BACKGROUND_PARSE
#define RESOURCE_BACKGROUND_PARSE 1
#endif

namespace Ogre {

	//////////////////////////////////////////////////////////////////
	class  CpuResource
	{
		friend class CpuResourceBuilder;
		friend class ResourceThread;
	public:
		enum CpuResourceType
		{
			RT_UNKNOWN = 0,
			RT_MESH				=1,
			RT_IMAGE			=2,
			RT_SKELETON			=3,
			RT_ASS				=4,
			RT_TERRAINTILEVB	=5,
			RT_FUTURE  = 6
		}  CRT_TYPE;

		struct ResArchiveInfoStr
		{
			String ResName;
			String ArchiveName;
			String ArchiveType;
			bool operator== (const ResArchiveInfoStr& rais) const
			{
				return ResName == rais.ResName &&
					ArchiveName == rais.ArchiveName && 
					ArchiveType == rais.ArchiveType;
			}
			bool operator!= (const ResArchiveInfoStr& rais) const
			{
				return !(*this == rais);
			}
		};		
		//构造
		//	实现不同类型加载资源的自我封装
		CpuResource(CpuResourceType	Type,
			String&			Name,
			Ogre::Archive*	pArc);
		//析构
		virtual ~CpuResource();
		//加载CPU资源
		virtual bool load()=0;
		//生成CPU资源
		virtual void* getData()=0;
	protected:
		CpuResourceType				mType;
		String 						mName;
		Ogre::Archive*				mArc;
		size_t						mSize;
	};

	class  CpuResourceBuilder 
	{
	public:
		//创建方法
		static CpuResource* Create(CpuResource::CpuResourceType Type,
			const String& Name,Ogre::Archive* pArc);
		//销毁方法
		static bool Destroy(CpuResource** hResource);

	};
	
	//////////////////////////////////////////////////////////////////
	class  MeshResource : public CpuResource
	{
	public:
		MeshResource(std::string meshName,Ogre::Archive* pArc);
		virtual ~MeshResource();
		virtual bool load();
		virtual void* getData();
	private:
		//Ogre::Mesh*				mMesh;
		Ogre::MemoryDataStreamPtr	mMesh;

	};
	//////////////////////////////////////////////////////////////////
	class  ImageResource : public CpuResource
	{
	public:
		ImageResource(std::string imageName,Ogre::Archive*	pArc);
		virtual ~ImageResource();
		virtual bool load();
		virtual void* getData();
	private:
		Ogre::CImage*				mImage;
		Ogre::MemoryDataStreamPtr	mImageData;
		Ogre::String				mExt;
		//地形阴影的额外文件
		bool						mIsLightMapImage;
		Ogre::CImage*				mMidLightMapImage;
		Ogre::CImage*				mLowLightMapImage;


	};
	//////////////////////////////////////////////////////////////////
	class  SkeletonResource : public CpuResource
	{
	public:
		SkeletonResource(std::string skeletonName,Ogre::Archive*	pArc);
		virtual ~SkeletonResource();
		virtual bool load();
		virtual void* getData();

		virtual void loadResource( Resource* pResource );

	private:
		//Ogre::Skeleton*			mSkeleton;
#if RESOURCE_BACKGROUND_PARSE == 0
		Ogre::MemoryDataStreamPtr	mSkeleton;
#else
		SkeletonPtr					mSkeleton;
#endif
	};

	//////////////////////////////////////////////////////////////////
	class  ASSResource : public CpuResource
	{
	public:
		ASSResource(std::string ASSName,Ogre::Archive*	pArc);
		virtual ~ASSResource();
		virtual bool load();
		virtual void* getData();
	private:
		//Ogre::MemoryDataStream*	mASS;
		Ogre::MemoryDataStreamPtr	mASS;
	};

}// namespace

#endif