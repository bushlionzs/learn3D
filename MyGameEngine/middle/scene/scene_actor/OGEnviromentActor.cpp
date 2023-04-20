#include "OgreHeader.h"
#include "OGEnviromentActor.h"
#include "OGActorFactory.h"
#include "scene_serializer.h"
#include "OgreDataStream.h"


namespace Orphigine
{
	void EnviromentRenderable::getWorldTransforms( Matrix4* xform ) const
	{
		
	}

	//////////////////////////////////////////////////////////////////////////
	// Factory
	//////////////////////////////////////////////////////////////////////////
	class EnviromentActor::Factory : public ActorFactory
	{
	public:
		const String& getType( ) const
		{
			return msType;
		}

		Actor* createInstance( )
		{
			return new EnviromentActor;
		}
	};

	

	//////////////////////////////////////////////////////////////////////////
	// EnviromentActor class
	//////////////////////////////////////////////////////////////////////////
	const String EnviromentActor::msType = "Enviroment";
	const String EnviromentActor::msCategory = "Enviroment";

	const EnviromentActor* EnviromentActor::DEFAULT = NULL;

	ActorFactory* EnviromentActor::getFactory(void)
	{
		static Factory factory;
		return &factory;
	}

	const EnviromentActor& EnviromentActor::getDefault( )
	{
		if ( DEFAULT == NULL )
			DEFAULT = new EnviromentActor( );

		return *DEFAULT;
	}

	EnviromentActor::EnviromentActor( )
		: PlacementActor( )
		, mFogMode( Ogre::FOG_NONE )
		, mFogExpDensity( 0.001f )
		, mFogLinearStart( 0.0f )
		, mFogLinearEnd( 1.0f )
		, mAmbientLight( ColourValue::Black )
		, mBackgroundColour( ColourValue::Black )
		, mFogColour( ColourValue::White )
		, mGrayFactor( 0.0f )
		, mWeatherParticleSystemName( "" )
		, mWeatherParticleSystem( NULL )
		, mWeatherParticleSystemNode( NULL )
		, mTerrainLoadRangeScale( 4.f )
		, mStaticModelLoadRangeScale( 4.f )
		, mEffectLoadRangeScale( 4.f )
		, mFogStartScale( 1.f )
		, mFogEndScale( 1.f )
		, mFarClipDistScale( 1.f )
		, mCullDistanceStart(10000.0f)
		, mCullDistanceEnd( 100000.0f )
		, mRenderWeather( true )
		, mTerrainBrightness( 1.0f )
		, mTerrainFocusLight( ColourValue::White )
		, mLightmapThrehold( 1 )
		, mSpecularExtendAdded( Ogre::Vector3::UNIT_SCALE )
		, mWindDirChange( 1, 0, 1 )
		, mWindForceMax ( 0.8 )
		, mSubEnv( false )
		, mWorldBoundingBox( NULL )
		, mRenderableBox( NULL )
	{
		

		mAABB.setMinimum(-100, 0, -100);
		mAABB.setMaximum(100, 200, 100);
	}

	EnviromentActor::~EnviromentActor( )
	{
		destroyRenderInstance( );
	}

	const String& EnviromentActor::getType( ) const
	{
		return msType;
	}

	const String& EnviromentActor::getCategory( ) const
	{
		return msCategory;
	}

	uint32_t EnviromentActor::getPropertyFlags( const String& name ) const
	{
		return 0;
	}

	

	void EnviromentActor::createRenderInstance( )
	{
		
	}

	void EnviromentActor::destroyRenderInstance( )
	{
		
	}

	void EnviromentActor::updateRenderInstance( )
	{
		
	}

	void EnviromentActor::apply( )
	{
		
	}

	void EnviromentActor::setWeatherParticleSystemPosition( const Ogre::Vector3& pos )
	{

	}

	void EnviromentActor::showWireBoundingBox( bool show )
	{
		
	}

	const AxisAlignedBox* EnviromentActor::getWorldBoundingBox( ) const
	{
		return nullptr;
	}

	bool EnviromentActor::loadFromStream(
		Serializer* pSerializer, 
		std::shared_ptr<DataStream>& stream,
		int32_t version)
	{
		if ( pSerializer == NULL || stream->eof() )
			return false;

		unsigned short chunkId = pSerializer->readChunk( stream );
		if(chunkId != SceneSerializer::SFF_ENVIROMENT_OBJ)
		{
			pSerializer->skipChunk( stream );
			return false;
		}

		pSerializer->readData( stream, &mAmbientLight, 1, sizeof( ColourValue ) );
		pSerializer->readData( stream, &mBackgroundColour, 1, sizeof( ColourValue ) );

		pSerializer->readData( stream, &mFogMode, 1, sizeof( int32_t ) );
		pSerializer->readData( stream, &mFogColour, 1, sizeof( ColourValue ) );

		pSerializer->readData( stream, &mFogExpDensity, 1, sizeof( Real ) );
		pSerializer->readData( stream, &mFogLinearStart, 1, sizeof( Real ) );
		pSerializer->readData( stream, &mFogLinearEnd, 1, sizeof( Real ) );
		pSerializer->readData( stream, &mLightmapThrehold, 1, sizeof( Real ) );

		pSerializer->readData( stream, &mSpecularExtendAdded, 1, sizeof( Vector3 ) );
		pSerializer->readData( stream, &mWindDirChange, 1, sizeof( Vector3 ) );

		pSerializer->readData( stream, &mWindForceMax, 1, sizeof( Real ) );
		pSerializer->readData( stream, &mTerrainBrightness, 1, sizeof( Real ) );
		pSerializer->readData( stream, &mTerrainFocusLight, 1, sizeof( ColourValue ) );
		pSerializer->readData( stream, &mRenderWeather, 1, sizeof( bool ) );

		mWeatherParticleSystemName = pSerializer->readStringBin( stream );

		// 因为初始的代码是直接读写Ogre::AxisAlignedBox类对象，而sizeof(Ogre::AxisAlignedBox)
		// 是28个字节，其中，mMinimum占12个字节,mMaximum占12个字节,而mNull因为字节对齐的缘故,
		// 在后面追加了3个字节的废数据，共4个字节，改写成各个成员单独读写的话，需要写3个字节
		// 的废数据,这3个字节可以在场景文件升级时，去除掉 [dscky edit 2009/08/03]
		//pSerializer->readData(stream,&mAABB,1,sizeof(Ogre::AxisAlignedBox));
		Vector3 AABBmin;
		Vector3 AABBmax;
		bool isNull = true;

		pSerializer->readData( stream, &AABBmin, 1, sizeof( Vector3 ) );
		pSerializer->readData( stream, &AABBmax, 1, sizeof( Vector3 ) );
		pSerializer->readData( stream, &isNull, 1, sizeof( bool ) );
		
		// 利用一个字节的废数据作为是否子环境标志
		pSerializer->readData( stream, &mSubEnv, 1, sizeof( bool ) );

		mAABB.setMinimum( AABBmin );
		mAABB.setMaximum( AABBmax );
		if( isNull )
			mAABB.setNull();

		unsigned short subVersion = 0;
		pSerializer->readData( stream, &subVersion, 1, sizeof( unsigned short ) );

		if( subVersion >= 1 )
		{
			pSerializer->readData( stream, &mGrayFactor, 1, sizeof( Real ) );
			pSerializer->readData( stream, &mTerrainLoadRangeScale, 1, sizeof( Real ) );
			pSerializer->readData( stream, &mStaticModelLoadRangeScale, 1, sizeof( Real ) );
			pSerializer->readData( stream, &mEffectLoadRangeScale, 1, sizeof( Real ) );
			pSerializer->readData( stream, &mFogStartScale, 1, sizeof( Real ) );
			pSerializer->readData( stream, &mFogEndScale, 1, sizeof( Real ) );
			pSerializer->readData( stream, &mFarClipDistScale, 1, sizeof( Real ) );
			pSerializer->readData( stream, &mCullDistanceEnd, 1, sizeof( Real ) );
			mCullDistanceStart = mCullDistanceEnd;
		}

		if ( subVersion >= 2 )
		{
			pSerializer->readData( stream, &mCullDistanceStart, 1, sizeof( Real ) );
			
			Ogre::Vector4 temp;
			pSerializer->readData(stream, &mHDRBright, 1, sizeof(Ogre::Vector4));
			pSerializer->readData(stream, &mHDRWhiteFudge, 1, sizeof(Ogre::Vector4));
			pSerializer->readData(stream, &temp, 1, sizeof(Ogre::Vector4));
			pSerializer->readData(stream, &temp, 1, sizeof(Ogre::Vector4));
		}

		// 版本3新加数据 by changhao
		if (subVersion >= 3)
		{

			pSerializer->readData(stream, &mSkyIndex, 1, sizeof(mSkyIndex));

			mSoundName = pSerializer->readStringBin(stream);
			pSerializer->readData(stream, &mPlaySoundTimes, 1, sizeof(int));

			pSerializer->readData(stream, &mOrphigineOneLightDiffuseColor, 1, sizeof(ColourValue));
			pSerializer->readData(stream, &mOrphigineOneLightSpecularColor, 1, sizeof(ColourValue));
			pSerializer->readData(stream, &mOrphigineTwoLightDiffuseColor, 1, sizeof(ColourValue));
			pSerializer->readData(stream, &mOrphigineTwoLightSpecularColor, 1, sizeof(ColourValue));
		}

		return true;			
	}

	bool EnviromentActor::saveToBinaryFile( Serializer* pSerializer )
	{
		
		
		return true;
	}	
	
	size_t EnviromentActor::calcSerializedSize( )
	{
		

		return 0;
	}

	bool EnviromentActor::saveToBinaryFile( FILE * pFile )
	{
		
		return false;
	}

	bool EnviromentActor::saveToMemory( char*& pCurrentPos )//暂时未实现
	{
		assert(false);
		return false;
	}

	bool EnviromentActor::saveToStream( ofstream& os )//暂时未实现
	{
		assert(false);
		return false;
	}

	bool EnviromentActor::loadFromMemory( char*& pCurrentPos )
	{
		
		return false;
	}

	bool EnviromentActor::loadFromFile( FILE* pFile )//暂时未实现
	{
		assert(false);
		return false;
	}

	bool EnviromentActor::loadFromStream( ifstream& is )//暂时未实现
	{
		assert(false);
		return false;
	}

	void EnviromentActor::createWeatherParticleSystemNode( )
	{
		
	}

	void EnviromentActor::destroyWeatherParticleSystemNode( )
	{

	}

	void EnviromentActor::createWeatherParticleSystem( )
	{
		
	}

	void EnviromentActor::destroyWeatherParticleSystem( )
	{
		
	}


	void EnviromentActor::calculateRenderableBox( )
	{
	}

}
