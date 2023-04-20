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
		static const int LiquidCellSize = 64 ;//水体基本单元大小，为地形基本单元大小的整数倍
		//水体面结构
		struct LiquidFace
		{
			bool mUsed; 
			size_t mV0; 
			size_t mV1; 
			size_t mV2;
			LiquidFace():mUsed(false),mV0(0),mV1(0),mV2(0){}
		};
		//水体子体结构，对应renderable
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
		//水体二进制读写
		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();


		bool isHaveValidVertex(void);
		bool buildGeometry(void);//水体生成接口
		bool buildGpuData(void);
		bool buildCpuData(void);
		bool releaseCpuData(void);
		bool releaseGpuData(void);
		bool releaseGeometry(void);
		bool registerTerrainLiquildTypeInfo();

		void clearUp(void);

		//初始化材质
		//void initMaterial(const String& materialName);

		//材质
		void setMaterialName(const String& materialName);
		const String& getMaterialName(void) const;

		//基于y的alpha值
		void setLiquidAlphaDependDepth(const Ogre::Real &depth);
		Ogre::Real getLiquidAlphaDependDepth(void) const;

		//水体颜色
		void setLiquidColour(const Ogre::ColourValue &liquidColour);
		Ogre::ColourValue getLiquidColour(void) const;

		//水体颜色深度
		//void setLiquidColourDependDepth(const Ogre::Real &depth);
		//Ogre::Real getLiquidColourDependDepth(void) const;

		//纹理坐标重复次数
		void setTexCoordTimes(const Ogre::Real &times);
		Ogre::Real getTexCoordTimes(void) const;

		//纹理动画滚动速度
		void setTexSpeed(const Ogre::Real &speed);
		Ogre::Real getTexSpeed(void) const;

		void setHighTexSpeed(const Ogre::Real &speed);

		void updateRenderables(LiquidRenderLevelEnum renderclass);			//更新renderable

		bool setTerrainRelatedData(TerrainInfo* pData);

		Ogre::Real getUpdateFrequency() const;
		void setUpdateFrequency(Ogre::Real updateFrequency);

		virtual const std::vector<Renderable*>& getRenderableList();

	public://以下函数 是 movable要求的
		const String&				getMovableType(void) const;
		const Ogre::AxisAlignedBox& getBoundingBox(void) const;
		Real						getBoundingRadius(void) const;
		void						_notifyCurrentCamera(Ogre::Camera* camera);
		void						_updateRenderQueue(Ogre::RenderQueue *queue);

	protected:
		bool calculateLiquidGridIndex();		//计算水体覆盖的格子
		void calculateVertexPosition(void);		//计算顶点位置
		void calculateTexcoords(void);			//计算纹理坐标
		void calculateVertexColour(void);		//计算顶点颜色

		void createHardwareBuffers(void);		//创建硬件缓存并填充数据
		void createRenderables(void);			//创建renderable

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

		//来自于地形的数据
		TerrainInfo*				mTerrainData;
		int32_t					mTerrainXSize;
		int32_t					mTerrainZSize;
		Ogre::Real *			mHeightmap;
		Ogre::Camera*			mCurrentCamera;

		//本身数据
		int32_t				mRenderableNum;				//渲染子体个数
		int32_t*			mCellFacesNum;				//每个渲染子体的面数

		//cpu数据
		int32_t					mVertexNum;					//顶点个数
		int*					mVertexGridIndex;			//顶点格子索引数组
		float *					mTempPositionBuffer;	//顶点缓存
		Ogre::AxisAlignedBox	mBoundingBox;
		float *					mTempTexcoordBuffer;	//纹理缓存
		uint32_t *			mTempColourBuffer;		//颜色缓存
		unsigned short **		mTempIndexBuffer;		//索引缓存	



		//关于材质的成员
		ReflectRenderTargetListener *	mReflectRenderTargetListener; //反射rendertarget监听器
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

		//渲染数据
		VertexData*					mVertexData; 
		IndexData**					mIndexData;
		//gpu数据
		Ogre::HardwareVertexBufferSharedPtr mPositionVertexBuffer;
		Ogre::HardwareVertexBufferSharedPtr mTexcoordVertexBuffer;
		Ogre::HardwareVertexBufferSharedPtr mColourVertexBuffer;
		typedef std::vector<LiquidWarCraftRenderable*> LiquidRenderableList;
		LiquidRenderableList				mLiquidRenderables;

		typedef std::vector<LiquidCell> CellList;
		CellList						mCellList;							//用于求水体的边

		//editor 控制数据  fixed-function
		Ogre::Real			mAlphaDependDepth;
		Ogre::Vector3		mPosition;				//水体位置
		Ogre::ColourValue	mLiquidColour;			//深水体颜色
		Ogre::Real			mTexCoordTimes;			//纹理迭代倍数
		Ogre::Real			mTexSpeed;				//影响材质

		//shader 相关
		Ogre::ColourValue mHighLiquidColour;		//深水体颜色
		Ogre::Real mHighTexCoordTimes;				//纹理迭代倍数
		Ogre::Real mHighTexSpeed;					//影响材质
		Ogre::Real mHighWaveSpeed;					//波速
		Ogre::Real mHighGridSize;					//波峰高度

		static size_t	mTextureNums;//用于产生随机名称
	};
}

#endif // OGTerrainNewLiquidComponent_h__