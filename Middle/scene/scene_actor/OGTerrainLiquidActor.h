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
		Ogre::Vector3 mPosition;					//ˮ��λ��
		Ogre::ColourValue mLiquidColour;		//��ˮ����ɫ
		Ogre::ColourValue mHighLiquidColour;		//shaderˮ����ɫ
		Ogre::Real mTexCoordTimes;					//�����������
		Ogre::Real mHighTexCoordTimes;				//shader���������������
		Ogre::Real mTexSpeed;						//�������ٶ� fps = num/mTexSpeed
		Ogre::Real mHighTexSpeed;					//�������ٶ� fps = num/mTexSpeed

		Ogre::Real mHighWaveSpeed;					//����
		Ogre::Real mHighGridSize;					//����߶�

		int						mLiquidIndex;		//ˮ�������ţ���ʾˮ�ǵ�ǰ��ͼ�ĵڼ���ˮ
		Ogre::AxisAlignedBox	mAABB;				//ˮ�İ�Χ�У����ļ��ж�ȡ�������ж��Ƿ����ˮ
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