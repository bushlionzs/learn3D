#ifndef OGTerrainNewLiquidComponent_h__
#define OGTerrainNewLiquidComponent_h__

#include <OgreMoveObject.h>
#include <OgreDataStream.h>
#include <platform_log.h>

#include <OgreCamera.h>
#include <OgrePlane.h>
#include "OgreColourValue.h"
#include "OgreRenderTargetListener.h"
class VertexData;
class IndexData;
class TerrainInfo;

namespace Orphigine 
{
	class LiquidWarCraftRenderable;
	class TerrainLiquidActor;
	class TerrainNewLiquidComponent;

	class ReflectRenderTargetListener : public Ogre::RenderTargetListener
	{
	public:
		ReflectRenderTargetListener(TerrainNewLiquidComponent *liquid, const Ogre::Vector3 &position, Ogre::String materialname);
		virtual ~ReflectRenderTargetListener();

		virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
		virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);

		void setUpdateCycle(unsigned long millisecond);
		unsigned long getUpdateCycle() const;

		void enableUpdate(bool enable);
		bool isUpdateEnable() const;

	private:
		bool needUpdate() const;

	protected:
		TerrainNewLiquidComponent *mTerrainLiquid;
		Ogre::Camera *mCamera;
		//Ogre::Camera *mReflectCamera;		
		Ogre::Plane *mReflectPlane;
		//Ogre::SceneManager*	mSceneManager;
		Ogre::String mReflectTextureName;
		Ogre::TexturePtr mReflectTexture;
		Ogre::RenderTarget*	mRenderTarget;

		mutable uint64_t mTimePosition;
		uint64_t mUpdateCycle;
	};


	enum LiquidRenderLevelEnum
	{
		LIQUID_LOW = 1,
		LIQUID_MIDDILE = LIQUID_LOW << 1,
		LIQUID_HIGH = LIQUID_LOW << 2,
		LIQUID_UNKNOWN
	};

	class TerrainNewLiquidComponent: public Ogre::MoveObject
	{
		friend class MapSerializer;
		friend class ReflectRenderTargetListener;
		friend class TerrainLiquidActor;
	public:
		static const int LiquidCellSize = 64 ;//ˮ�������Ԫ��С��Ϊ���λ�����Ԫ��С��������
		//ˮ����ṹ
		struct LiquidFace
		{
			bool mUsed; 
			size_t mV0; 
			size_t mV1; 
			size_t mV2;
			LiquidFace():mUsed(false),mV0(0),mV1(0),mV2(0){}
		};
		//ˮ������ṹ����Ӧrenderable
		struct LiquidCell
		{	
			LiquidFace mFaces[LiquidCellSize][LiquidCellSize][2];
			size_t mCellX; 
			size_t mCellZ; 
			size_t mFacesNum; 
			LiquidCell():mFacesNum(0),mCellX(0),mCellZ(0){}
		};
		TerrainNewLiquidComponent(
			const Ogre::Vector3& position
			,const Ogre::String &materialname
			,const Ogre::ColourValue &colour
			,const Ogre::Real& alphadepth
			,const Ogre::Real& coordtimes
			,const Ogre::Real& speed);

		virtual ~TerrainNewLiquidComponent(void);
		//ˮ������ƶ�д
		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();


		bool isHaveValidVertex(void);
		bool buildGeometry(void);//ˮ�����ɽӿ�
		bool buildGpuData(void);
		bool buildCpuData(void);
		bool releaseCpuData(void);
		bool releaseGpuData(void);
		bool releaseGeometry(void);
		bool registerTerrainLiquildTypeInfo();

		void clearUp(void);

		//��ʼ������
		//void initMaterial(const String& materialName);

		//����
		void setMaterialName(const String& materialName);
		const String& getMaterialName(void) const;

		//����y��alphaֵ
		void setLiquidAlphaDependDepth(const Ogre::Real &depth);
		Ogre::Real getLiquidAlphaDependDepth(void) const;

		//ˮ����ɫ
		void setLiquidColour(const Ogre::ColourValue &liquidColour);
		Ogre::ColourValue getLiquidColour(void) const;

		//ˮ����ɫ���
		//void setLiquidColourDependDepth(const Ogre::Real &depth);
		//Ogre::Real getLiquidColourDependDepth(void) const;

		//���������ظ�����
		void setTexCoordTimes(const Ogre::Real &times);
		Ogre::Real getTexCoordTimes(void) const;

		//�����������ٶ�
		void setTexSpeed(const Ogre::Real &speed);
		Ogre::Real getTexSpeed(void) const;

		void setHighTexSpeed(const Ogre::Real &speed);

		void updateRenderables(LiquidRenderLevelEnum renderclass);			//����renderable

		bool setTerrainRelatedData(TerrainInfo* pData);

		Ogre::Real getUpdateFrequency() const;
		void setUpdateFrequency(Ogre::Real updateFrequency);

		virtual const std::vector<Renderable*>& getRenderableList();

	public://���º��� �� movableҪ���
		const String&				getMovableType(void) const;
		const Ogre::AxisAlignedBox& getBoundingBox(void) const;
		Real						getBoundingRadius(void) const;
		void						_notifyCurrentCamera(Ogre::Camera* camera);
		void						_updateRenderQueue(Ogre::RenderQueue *queue);

	protected:
		bool calculateLiquidGridIndex();		//����ˮ�帲�ǵĸ���
		void calculateVertexPosition(void);		//���㶥��λ��
		void calculateTexcoords(void);			//������������
		void calculateVertexColour(void);		//���㶥����ɫ

		void createHardwareBuffers(void);		//����Ӳ�����沢�������
		void createRenderables(void);			//����renderable

		void createReflectRenderTexture(void);
		void deleteReflectRenderTexture(void);

		void setReflectMatrix(const Ogre::Matrix4 &m);


		void cloneHighTechMaterial(Ogre::MaterialPtr& srcMat);
		void cloneMidTechMaterial(Ogre::MaterialPtr& srcMat);
		void cloneLowTechMaterial(Ogre::MaterialPtr& srcMat);

		void cleanClonedMaterials();
	private:
		inline int calculateGridIndex(const Ogre::Real, const Ogre::Real);
		inline void calculateIB();
		inline bool isValidPoint(Real x, Real z);
		inline bool isValidPoint(int index);

		inline bool isGridValid(int x,int z);
	protected:
		static const String msMovableType;

		//�����ڵ��ε�����
		TerrainInfo*				mTerrainData;
		int32_t					mTerrainXSize;
		int32_t					mTerrainZSize;
		Ogre::Real *			mHeightmap;
		Ogre::Camera*			mCurrentCamera;

		//��������
		int32_t				mRenderableNum;				//��Ⱦ�������
		int32_t*			mCellFacesNum;				//ÿ����Ⱦ���������

		//cpu����
		int32_t					mVertexNum;					//�������
		int*					mVertexGridIndex;			//���������������
		float *					mTempPositionBuffer;	//���㻺��
		Ogre::AxisAlignedBox	mBoundingBox;
		float *					mTempTexcoordBuffer;	//������
		uint32_t *			mTempColourBuffer;		//��ɫ����
		unsigned short **		mTempIndexBuffer;		//��������	



		//���ڲ��ʵĳ�Ա
		ReflectRenderTargetListener *	mReflectRenderTargetListener; //����rendertarget������
		Ogre::String					mReflectTextureName;
		Ogre::String					mMaterialName;
		Ogre::String					mLowMaterialName;
		Ogre::String					mMiddleMaterialName;
		Ogre::String					mHighMaterialName;

		Ogre::MaterialPtr				mMaterial;
		Ogre::MaterialPtr				mLowMaterial;
		Ogre::MaterialPtr				mMiddleMaterial;
		Ogre::MaterialPtr				mHighMaterial;

		LiquidRenderLevelEnum			mCurrentMaterialType;
		Ogre::uchar						mNumMaterials;

		typedef std::vector<Ogre::MaterialPtr > SMMaterialList;
		SMMaterialList					mMaterialBackupList;

		bool							beyondFogDirty;

		//��Ⱦ����
		VertexData*					mVertexData; 
		IndexData**					mIndexData;
		//gpu����
		Ogre::HardwareVertexBufferSharedPtr mPositionVertexBuffer;
		Ogre::HardwareVertexBufferSharedPtr mTexcoordVertexBuffer;
		Ogre::HardwareVertexBufferSharedPtr mColourVertexBuffer;
		typedef std::vector<LiquidWarCraftRenderable*> LiquidRenderableList;
		LiquidRenderableList				mLiquidRenderables;

		typedef std::vector<LiquidCell> CellList;
		CellList						mCellList;							//������ˮ��ı�

		//editor ��������  fixed-function
		Ogre::Real			mAlphaDependDepth;
		Ogre::Vector3		mPosition;				//ˮ��λ��
		Ogre::ColourValue	mLiquidColour;			//��ˮ����ɫ
		Ogre::Real			mTexCoordTimes;			//�����������
		Ogre::Real			mTexSpeed;				//Ӱ�����

		//shader ���
		Ogre::ColourValue mHighLiquidColour;		//��ˮ����ɫ
		Ogre::Real mHighTexCoordTimes;				//�����������
		Ogre::Real mHighTexSpeed;					//Ӱ�����
		Ogre::Real mHighWaveSpeed;					//����
		Ogre::Real mHighGridSize;					//����߶�

		static size_t	mTextureNums;//���ڲ����������
	};
}

#endif // OGTerrainNewLiquidComponent_h__