#ifndef OGTerrainLiquidActor_h__
#define OGTerrainLiquidActor_h__

#include "OGActor.h"
#include "OgreAxisAlignedBox.h"
#include "OgreColourValue.h"

class TerrainInfo;

namespace Orphigine {

	class ActorFactory;
	class Engine;
	class GroundInfo;
	class TerrainNewLiquidComponent;
	class  TerrainLiquidActor : public Actor
	{
	protected:
		class Factory;

	public:

		TerrainLiquidActor(void);
		virtual ~TerrainLiquidActor();

		virtual const String& getType(void) const;
		virtual const String& getCategory(void) const;
		virtual void createRenderInstance();
		virtual void destroyRenderInstance(void);
		virtual void updateRenderInstance(void);
		virtual bool loadFromStream(
			Serializer* pSerializer, 
			std::shared_ptr<DataStream>& stream,
			int32_t version);
		virtual bool saveToBinaryFile(Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();

		bool saveToBinaryFile(FILE * pFile);
		bool saveToMemory(char*& pCurrentPos);
		bool saveToStream(std::ofstream& os);
		bool loadFromMemory(char*& pCurrentPos);
		bool loadFromFile(FILE* pFile);
		bool loadFromStream(std::ifstream& is);
		bool buildTerrainLiquidAndCpuData(TerrainInfo* pData);


		void setVisible(bool show);


		//////////////////////////////////////////////////////////////////////////

		static const String msType;
		static const String msCategory;

		static ActorFactory* getFactory(void);

		//////////////////////////////////////////////////////////////////////////

		

		const Ogre::AxisAlignedBox & getBoundingBox(void) const
		{
			return mAABB;
		}

		void setBoundingBox(const Ogre::AxisAlignedBox& aab)
		{
			mAABB = aab;
		}

		Ogre::Real getUpdateFrequency() const;
		void setUpdateFrequency(Ogre::Real updateFrequency);

	protected:
		TerrainNewLiquidComponent* mTerrainLiquid;

	protected:
		void createTerrainLiquid();
		void destroyTerrainLiquid(void);

	public:     // Intend for direct access by property commands only, DO NOT access outside
		String mMaterialName;

		Ogre::Real mAlphaDependDepth;
		Ogre::Vector3 mPosition;					//水体位置
		Ogre::ColourValue mLiquidColour;		//深水体颜色
		Ogre::ColourValue mHighLiquidColour;		//shader水体颜色
		Ogre::Real mTexCoordTimes;					//纹理迭代倍数
		Ogre::Real mHighTexCoordTimes;				//shader法线纹理迭代倍数
		Ogre::Real mTexSpeed;						//纹理动画速度 fps = num/mTexSpeed
		Ogre::Real mHighTexSpeed;					//纹理动画速度 fps = num/mTexSpeed

		Ogre::Real mHighWaveSpeed;					//波速
		Ogre::Real mHighGridSize;					//波峰高度

		int						mLiquidIndex;		//水的索引号，表示水是当前地图的第几块水
		Ogre::AxisAlignedBox	mAABB;				//水的包围盒，从文件中读取，用来判断是否加载水
	public:
		bool mMaterialDirty;
		bool mAlphaDepthDirty;
		bool mPositionDirty;
		bool mLiquidColourDirty;
		//bool mColourDependDepthDirty;
		bool mTexCoordTimesDirty;
		bool mTexSpeedDirty;

		bool mHighLiquidColourDirty;
		bool mHighTexSpeedDirty;
		bool mHighTexCoordTimesDirty;
		bool mHighWaveSpeedDirty;
		bool mHighGridSizeDirty;
		bool mRenderClassDirty;
	};
}

#endif // OGTerrainLiquidActor_h__