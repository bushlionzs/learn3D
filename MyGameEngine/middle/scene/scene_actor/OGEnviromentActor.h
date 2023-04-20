#ifndef OGEnviromentActor_h__
#define OGEnviromentActor_h__

#include "OGActor.h"

#include <OgreColourValue.h>
#include <OgreCommon.h>
#include <OgreAxisAlignedBox.h>
#include "OGPlacementActor.h"

using std::size_t;
using std::ifstream;
using std::ofstream;

using Ogre::Real;
using Ogre::String;
using Ogre::ColourValue;
using Ogre::Vector3;
using Ogre::Matrix4;
using Ogre::AxisAlignedBox;


namespace Orphigine
{
	class ActorFactory;
	class ActorProxy;

	class EnviromentRenderable
	{
	public:
		virtual void getWorldTransforms( Matrix4* xform ) const;
	};

	class  EnviromentActor : public PlacementActor
	{
	protected:
		class Factory;
		static const EnviromentActor* DEFAULT;

	public:
		static const String msType;
		static const String msCategory;

		static ActorFactory* getFactory( );
		static const EnviromentActor& getDefault( );

		EnviromentActor( );
		virtual ~EnviromentActor( );

		virtual const String& getType( ) const;
		virtual const String& getCategory( ) const;

		uint32_t getPropertyFlags( const String& name ) const;


		virtual void createRenderInstance( );
		virtual void destroyRenderInstance( );
		virtual void updateRenderInstance( );
		
		void apply( );


		void setWeatherParticleSystemPosition( const Vector3& pos );

		// =========================================
		// 显示环境包围盒
		void showWireBoundingBox( bool show = true );
		// =========================================
		// 得到世界包围盒
		const AxisAlignedBox* getWorldBoundingBox( ) const;

		virtual bool loadFromStream(
			Serializer* pSerializer,
			std::shared_ptr<DataStream>& stream,
			int32_t version);
		virtual bool saveToBinaryFile( Serializer* pSerializer);
		virtual size_t	calcSerializedSize( );

		// dscky add 
		bool saveToBinaryFile( FILE * pFile );
		bool saveToMemory( char*& pCurrentPos );
		bool saveToStream( ofstream& os );
		bool loadFromMemory( char*& pCurrentPos );
		bool loadFromFile( FILE* pFile);
		bool loadFromStream( ifstream& is );
		// dscky add

	protected:
		void createWeatherParticleSystemNode( );
		void destroyWeatherParticleSystemNode( );

		void createWeatherParticleSystem( );
		void destroyWeatherParticleSystem( );

		// =========================================
		// 取得可渲染包围盒
		void calculateRenderableBox( );

		ParticleSystem* mWeatherParticleSystem;

	public:     // Intend for direct access by property commands only, DO NOT access outside
		ColourValue mAmbientLight;
		ColourValue mBackgroundColour;

		Real mGrayFactor;

		ColourValue mFogColour;
		uint8_t mFogMode;
		Real mFogExpDensity;
		Real mFogLinearStart;
		Real mFogLinearEnd;
		Real mFogStartScale;
		Real mFogEndScale;

		Real mTerrainBrightness;
		ColourValue mTerrainFocusLight;
		Real mLightmapThrehold;
		Vector3 mSpecularExtendAdded;

		Vector3 mWindDirChange;
		Real mWindForceMax;

		Real mTerrainLoadRangeScale;
		Real mStaticModelLoadRangeScale;
		Real mEffectLoadRangeScale;

		Real mFarClipDistScale;
		Real mCullDistanceStart;
		Real mCullDistanceEnd;

		// 该对象是否是子环境对象
		bool mSubEnv;

		bool mRenderWeather;

		/// weather particle system
		String mWeatherParticleSystemName;
		SceneNode* mWeatherParticleSystemNode;

		// 局部包围盒
		AxisAlignedBox mAABB;

		Ogre::Vector4 mHDRBright;

		Ogre::Vector4 mHDRWhiteFudge;

		int mSkyIndex;

		String mSoundName;
		int mPlaySoundTimes;

		//2个主光源颜色 by changhao
		Ogre::ColourValue mOrphigineOneLightDiffuseColor;
		Ogre::ColourValue mOrphigineOneLightSpecularColor;
		Ogre::ColourValue mOrphigineTwoLightDiffuseColor;
		Ogre::ColourValue mOrphigineTwoLightSpecularColor;

		int mCurrentSkyIndex;

	private:
		// 世界包围盒
		mutable AxisAlignedBox* mWorldBoundingBox;

		// 可渲染包围盒
		EnviromentRenderable* mRenderableBox;
	};

}

#endif // OGEnviromentActor_h__