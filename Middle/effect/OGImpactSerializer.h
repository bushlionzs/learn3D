#ifndef OGImpactSerializer_h__
#define OGImpactSerializer_h__


#include "OgreSerializer.h"
#include "OgreDataStream.h"

namespace Orphigine
{
	class Impact;
	class ImpactSerializerImpl;
	class _OrphigineExport ImpactSerializer
	{
	public:
		friend class ImpactSerializerImpl;
		enum EffectFileFormatEnum
		{
			EFF_FILEHEADER			= 0x1000,// 文件头
			EFF_EFFECT				= 0x0100,
			EFF_PARTICLE_ELEMENT	= 0x0200,
			EFF_MESH_ELEMENT		= 0x0300,
			EFF_BILLBOARDSET_ELEMENT= 0x0400,
			EFF_POINTLIGHT_ELEMENT	= 0x0500,
			EFF_PROJECTOR_ELEMENT	= 0x0600,
			EFF_RIBBONEFFECT_ELEMENT= 0x0700,
			EFF_BEAM_ELEMENT		= 0x0800		
		};
		ImpactSerializer(void);
		virtual ~ImpactSerializer();
		
		bool importEffectFromStream(Ogre::DataStreamPtr& stream, Impact *pEffect);

	protected:
		//版本
		static Ogre::String					mCurrentVersion;
		typedef std::map<Ogre::String, ImpactSerializerImpl* > EffectSerializerImplMap;
		EffectSerializerImplMap				mImplementations;
	};

	class ImpactSerializerImpl : public Ogre::Serializer
	{
	public:	
		friend class ImpactSerializer;
		ImpactSerializerImpl();
		virtual ~ImpactSerializerImpl();
		bool importEffectFromStream(Ogre::DataStreamPtr& stream, Impact *pEffect);
	protected:
		virtual bool writeEffect(Impact* pEffect);
		virtual bool readEffect(Ogre::DataStreamPtr& stream, Impact* pEffect);
		int mFileVersion;
	};
}
#endif // OGImpactSerializer_h__