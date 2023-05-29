#include "OgreHeader.h"
#include "OGImpactSerializer.h"
#include "OGImpactManager.h"
#include "platform_log.h"
#include "OgreParticleSystemManager.h"
#include "OgreParticleSystem.h"
#include "OGImpact.h"
#include "OGImpactModule.h"
#include "OGImpactParticleModule.h"

namespace Orphigine
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Ogre::String	s_LastVersion = "[EffectSerializer_v1.00]";
	Ogre::String	ImpactSerializer::mCurrentVersion = "[EffectSerializer_v1.01]";
	ImpactSerializer::ImpactSerializer(void)
	{
		// Set up map
		mImplementations.insert(EffectSerializerImplMap::value_type("[EffectSerializer_v1.00]",new ImpactSerializerImpl() ));       
		mImplementations.insert(EffectSerializerImplMap::value_type("[EffectSerializer_v1.01]",new ImpactSerializerImpl() ));       
	}
	ImpactSerializer::~ImpactSerializer()
	{
		// delete map
		for (EffectSerializerImplMap::iterator i = mImplementations.begin();i != mImplementations.end(); ++i)
		{
			delete i->second;
		}
		mImplementations.clear();
	}
	
	bool ImpactSerializer::importEffectFromStream(Ogre::DataStreamPtr& stream, Impact *pEffect)
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
		EffectSerializerImplMap::iterator impl = mImplementations.find(version);//找到合适的解析器
		if (impl == mImplementations.end())
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot find serializer implementation for "
				"current version " + version, "EffectSerializer::importEffect");
			return false;
		}	
		impl->second->importEffectFromStream(stream, pEffect);	
		if (version != mCurrentVersion)//写log，警告
		{
			//WARNING_LOG("WARNING: " + pEffect->getTemplateName() + 
			//	" is an older format (" + version + "); you should upgrade it as soon as possible" +
			//	" using the OgreMeshUpgrade tool.",Ogre::LML_TRIVIAL);
		}
		return true;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	ImpactSerializerImpl::ImpactSerializerImpl()
	{
		mFileType = "EFFB";	
		mVersion = ImpactSerializer::mCurrentVersion;
		mFileVersion = 101;
	}
	ImpactSerializerImpl::~ImpactSerializerImpl()
	{
	}
	bool ImpactSerializerImpl::writeEffect(Impact* pEffect)
	{
		return false;	
	}
	bool ImpactSerializerImpl::importEffectFromStream(Ogre::DataStreamPtr& stream, Impact *pEffect)
	{
		//WARNING_LOG("EffectSerializer import data...",Ogre::LML_TRIVIAL);
		determineEndianness(stream);
		//readFileHeader(stream);
		unsigned short headerID = 0;
		readShorts(stream, &headerID, 1);
		if (headerID == HEADER_STREAM_ID)
		{
			String version = readStringBin(stream);
			if (version != mVersion)
			{
				if (version != s_LastVersion) //既不是新版本也不是上个版本则报错
				{
					OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, 
						"Invalid file: version incompatible, file reports " + version +
						" Serializer is version " + mVersion,
						"EffectSerializerImpl::importEffectFromStream");
				}
				mFileVersion = 100;//旧版本
			}
		}
		else
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Invalid file: no header","TerrainSerializerImpl::readFileHeader");
			return false;
		}
		pEffect->setVersion(mFileVersion);

		String FileType = readStringBin(stream);
		String CopyRight = readStringBin(stream);
		if (FileType != mFileType)
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, 
				"Invalid file: type incompatible, file reports " + String(FileType) + 
				" Serializer is type " + mFileType,
				"EffectSerializerImpl::importEffectFromStream");
			return false;
		}
		readEffect(stream,pEffect);
		//WARNING_LOG("EffectSerializer import successful.",Ogre::LML_TRIVIAL);
		return true;
	}
	bool ImpactSerializerImpl::readEffect(Ogre::DataStreamPtr& stream, Impact* pEffect)
	{
		if(pEffect)
			return pEffect->loadFromStream(this,stream);
		return false;	
	}

}