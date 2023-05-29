#include "OgreHeader.h"
#include "OgreCpuResource.h"
#include "platform_log.h"
#include "OgreRoot.h"
#include "OgreAnimation.h"
#include "OgreBone.h"
#include "OgreMemoryStream.h"
#include "OgreString.h"

namespace Ogre
{
		///////////////////////////////////////////////////////
		CpuResource::CpuResource(CpuResourceType Type,String& Name,Ogre::Archive* pArc):
			mType(Type),
			mName(Name),
			mArc(pArc),
			mSize(0)
		{

		}
		CpuResource::~CpuResource()
		{ 
			mArc=NULL;	
		}
		
		////////////////////////////////////////////////////////////////////////////////	
		CpuResource* CpuResourceBuilder::Create(CpuResource::CpuResourceType Type,
												const String& Name,Ogre::Archive* pArc)
		{
			switch (Type)
			{
			case CpuResource::RT_MESH:
				return new MeshResource(Name, pArc);
				break;
			case CpuResource::RT_IMAGE:
				return new ImageResource(Name, pArc);
				break;
			case CpuResource::RT_SKELETON:
				return new SkeletonResource(Name, pArc);
				break;
			case CpuResource::RT_ASS:
				return new ASSResource(Name, pArc);
				break;
			default:
				WARNING_LOG("UnKnown CpuResource Type,Type = %d,ResName = %s\n", Type, Name.c_str());
				return NULL;
				break;
			}
		}

		bool CpuResourceBuilder::Destroy(CpuResource** hResource)
		{
			if(*hResource)
			{
				delete *hResource;
				(*hResource) = NULL;
				return true;
			}
			else
			{
				WARNING_LOG("Destroy CpuResource Failed, Resource Handle is NULL!!");
				return false;
			}
		}
		////////////////////////////////////////////////////////////////////////////////
		MeshResource::MeshResource(std::string meshName,Ogre::Archive* pArc)
			:CpuResource(RT_MESH,meshName,pArc)
		{
		}
		MeshResource::~MeshResource()
		{
			
		}
		bool MeshResource::load()
		{
			
			{
				mSize = 0;
				WARNING_LOG("MeshResource Load Failed,ResName = %s\n", mName.c_str());
				return false;
			}
		}
		void* MeshResource::getData()
		{
			return nullptr;
		}
		////////////////////////////////////////////////////////////////////////////////
		ImageResource::ImageResource(std::string imageName,Ogre::Archive* pArc)
			:CpuResource(RT_IMAGE,imageName,pArc),mImage(NULL),mMidLightMapImage(NULL),mLowLightMapImage(NULL),mIsLightMapImage(false)
		{
			String::size_type pos = mName.find_last_of(".");
			if (pos != String::npos && pos < (mName.length() - 1))
			{
				mExt = mName.substr(pos + 1);
				StringUtil::toLowerCase(mExt);
			}
			String::size_type pos1 = mName.find(".lightmap");
			if (pos1 != String::npos && pos1 < (mName.length() - 1))//是否地形文件
			{
				mIsLightMapImage = true;
			}
		}
		ImageResource::~ImageResource()
		{ 		
			
		}	
		bool ImageResource::load()//图像文件加载
		{				
			return false;
		}
		void* ImageResource::getData()
		{
			return nullptr;
		}
		////////////////////////////////////////////////////////////////////////////////
		SkeletonResource::SkeletonResource(std::string skeletonName,Ogre::Archive* pArc)
			:CpuResource(RT_SKELETON,skeletonName,pArc)
		{
		}
		SkeletonResource::~SkeletonResource()
		{ 			
		}	
		bool SkeletonResource::load()//骨骼文件加载
		{
			return false;
		}
		void* SkeletonResource::getData( )
		{
			return nullptr;
		}
		void SkeletonResource::loadResource( Resource* pResource )
		{

		}
		////////////////////////////////////////////////////////////////////////////////
		ASSResource::ASSResource(std::string ASSName,Ogre::Archive* pArc)
			:CpuResource(RT_ASS,ASSName,pArc)
		{
		}
		ASSResource::~ASSResource()
		{ 
		}	
		bool ASSResource::load()//aas加载
		{
			return false;
		}
		void* ASSResource::getData()
		{
			if(mASS.get())
			{
				mASS->seek(0);
				return (void*)(&mASS);
			}
			else
			{
				WARNING_LOG("ASSResource getData Failed,ResName = %s", mName.c_str());
				return NULL;
			}
		}
}