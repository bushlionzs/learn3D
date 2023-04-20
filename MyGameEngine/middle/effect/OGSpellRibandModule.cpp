#include "OgreHeader.h"
#include "OGSpellRibandModule.h"
#include "OGImpactManager.h"

#include <OgreStringConverter.h>
#include <OgreCamera.h>
#include <OgreRoot.h>
#include "OgreSceneNode.h"
#include "engine_manager.h"
#include "OgreSceneManager.h"
#include "vertex_declaration.h"
#include <OgreHardwareBufferManager.h>

namespace Orphigine	{

	SpellRibbonModule::CmdAttachTime	SpellRibbonModule::msAttachTimeCmd;
	SpellRibbonModule::CmdAttachPoint		SpellRibbonModule::msAttachPointCmd;
	SpellRibbonModule::CmdOffsetPos	 SpellRibbonModule::msOffsetPosCmd;
	SpellRibbonModule::CmdOffsetRotation	SpellRibbonModule::msOffsetRotationCmd;

	SpellRibbonModule::CmdPointCount SpellRibbonModule::msPointCountCmd;
	SpellRibbonModule::CmdStartColour SpellRibbonModule::msStartColour;
	SpellRibbonModule::CmdEndColour SpellRibbonModule::msEndColour;
	SpellRibbonModule::CmdStartAlpha SpellRibbonModule::msStartAlpha;
	SpellRibbonModule::CmdEndAlpha SpellRibbonModule::msEndAlpha;
	SpellRibbonModule::CmdFadeInTime SpellRibbonModule::msFadeInTimeCmd;
	SpellRibbonModule::CmdFadeOutTime SpellRibbonModule::msFadeOutTimeCmd;
	SpellRibbonModule::CmdMaterial SpellRibbonModule::msMaterialCmd;
	SpellRibbonModule::CmdRibbonWidth SpellRibbonModule::msRibbonWidthCmd;
	SpellRibbonModule::CmdLifeTime SpellRibbonModule::msLifeTimeCmd;
	SpellRibbonModule::CmdUseInter SpellRibbonModule::msUseInterCmd;
	SpellRibbonModule::CmdInterTimes SpellRibbonModule::msInterTimesCmd;
	SpellRibbonModule::CmdVertexLifeTime SpellRibbonModule::msVertexLifeTimeCmd;

	SpellRibbonModule::CmdUseAttachRotation	SpellRibbonModule::msUseAttachRotationCmd;
	//////////////////////////////////////////////////////////////////////////

	SpellRibbonModule::SpellRibbonModule(unsigned short pointCount, float lifeTime, float ribbonWidth,
		const Ogre::ColourValue &startColour, const Ogre::ColourValue &endColour,
		float startAlpha, float endAlpha, float vertexLifeTime ) :
	mPointCount(pointCount), 
		mLifeTime(lifeTime), 
		mRibbonWidth(ribbonWidth),
		mStartColour(startColour), 
		mEndColour(endColour),
		mStartAlphaValue(startAlpha), 
		mEndAlphaValue(endAlpha), 
		mVertexLifeTime(vertexLifeTime),
		mCreateInstance(false), 
		mCurrentLifeTime(0.0f),
		mAttachTime(0.0f), 
		mAttachPoint(""), 
		mBasicNode(NULL), 
		mOffsetPos(Ogre::Vector3::ZERO), 
		mOffsetRotation(Ogre::Quaternion::IDENTITY),
		mInterpolationTimes(2), 
		mUseInterpolation(false), 
		mBuffersCreated(false),
		mFadeInTime(0.0f), 
		mFadeOutTime(1.0f), 
		mCurrentStartAlphaValue(1.0f), 
		mCurrentEndAlphaValue(1.0f),
		mUseAttachRotation(true)
	{
		mPoints.clear();

		if (mUseInterpolation)
			mCurrentVertexCount = mPointCount * mInterpolationTimes;
		else
			mCurrentVertexCount = mPointCount;

		if (createParamDictionary("AnimationRibbon"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			dict->addParameter(Ogre::ParameterDef("AttachTime", 
				"the time that showing the ribbon.",
				Ogre::PT_REAL),&msAttachTimeCmd);	  

			dict->addParameter(Ogre::ParameterDef("AttachPoint", 
				"the attached bone or locator.",
				Ogre::PT_STRING),&msAttachPointCmd);	  

			dict->addParameter(Ogre::ParameterDef("OffsetPos", 
				"offset position to the attach point.",
				Ogre::PT_VECTOR3),&msOffsetPosCmd);	  

			dict->addParameter(Ogre::ParameterDef("OffsetRotation", 
				"offset orientation to the attach point.",
				Ogre::PT_QUATERNION),&msOffsetRotationCmd);	  

			dict->addParameter(Ogre::ParameterDef("PointCount", 
				"the number of points.",
				Ogre::PT_UNSIGNED_INT),&msPointCountCmd);

			dict->addParameter(Ogre::ParameterDef("LifeTime", 
				"the life time of ribbon vertex.",
				Ogre::PT_REAL),&msLifeTimeCmd);

			dict->addParameter(Ogre::ParameterDef("RibbonWidth", 
				"the width of ribbon.",
				Ogre::PT_REAL),&msRibbonWidthCmd);

			dict->addParameter(Ogre::ParameterDef("StartAlphaValue", 
				"the head point alpha value.",
				Ogre::PT_REAL),&msStartAlpha);

			dict->addParameter(Ogre::ParameterDef("EndAlphaValue", 
				"the tail point of alpha value.",
				Ogre::PT_REAL),&msEndAlpha);

			dict->addParameter(Ogre::ParameterDef("StartColour", 
				"the colour of head point.",
				Ogre::PT_COLOURVALUE),&msStartColour);

			dict->addParameter(Ogre::ParameterDef("EndColour", 
				"the colour of tail point.",
				Ogre::PT_COLOURVALUE),&msEndColour);

			dict->addParameter(Ogre::ParameterDef("FadeInTime", 
				"the alpha fade in time.",
				Ogre::PT_REAL),&msFadeInTimeCmd);

			dict->addParameter(Ogre::ParameterDef("FadeOutTime", 
				"the alpha fade out time.",
				Ogre::PT_REAL),&msFadeOutTimeCmd);

			dict->addParameter(Ogre::ParameterDef("Material", 
				"name of ribbon material.",
				Ogre::PT_STRING),&msMaterialCmd);	 

			dict->addParameter(Ogre::ParameterDef("InterTimes", 
				"the time that showing the ribbon.",
				Ogre::PT_INT),&msInterTimesCmd);	  

			dict->addParameter(Ogre::ParameterDef("UseInter", 
				"the time that showing the ribbon.",
				Ogre::PT_BOOL),&msUseInterCmd);	 

			dict->addParameter(Ogre::ParameterDef("VertexLifeTime", 
				"the life time of vertex.",
				Ogre::PT_REAL),&msVertexLifeTimeCmd);

			dict->addParameter(Ogre::ParameterDef("UseAttachRotation",
				"Use attach point rotation to update offset position and offset rotation.",
				Ogre::PT_BOOL),&msUseAttachRotationCmd);
		}
	}
	//-----------------------------------------------------------------------
	SpellRibbonModule::~SpellRibbonModule()
	{
		destroyRenderInstance();
	}
	//-----------------------------------------------------------------------
	bool SpellRibbonModule::createRenderInstance(void)
	{	
		if (mCreateInstance)
		{
			// 如果已经创建，就马上返回
			mBasicNode->setVisible(true);

			mCurrentLifeTime = 0.0f;

			//mPoints.clear();

			return true;
		}
		else
		{
			// create scene node

			Ogre::SceneNode* baseNode = EngineManager::getSingletonPtr()->getBaseSceneNode();

			mBasicNode = baseNode->createChildSceneNode(BLANKSTRING);

			Ogre::SceneNode* parent = mBasicNode;

			if (parent)
			{
				/*mRenderOp.operationType = Ogre::RenderOperation::OT_TRIANGLE_STRIP;
				mRenderOp.useIndexes = false;*/

				if (mUseInterpolation)
					_createBuffer( mPointCount * mInterpolationTimes );
				else
					_createBuffer( mPointCount );

				parent->attachObject(this);

				setMaterial(m_strMatName);

				setCastShadows(false);

				mCreateInstance = true;

				return true;
			}

			return false;
		}		
	}
	//-----------------------------------------------------------------------
	void SpellRibbonModule::destroyRenderInstance(void)
	{
		_destroyBuffer();

		// delete scene node
		if (mBasicNode)
		{
			mBasicNode->getCreator()->destroySceneNode(mBasicNode);
			mBasicNode = NULL;
		}	

		mCreateInstance = false;
	}
	//-----------------------------------------------------------------------
	void SpellRibbonModule::updateRenderInstance( float time, TransformInfo &transform )
	{
		if (mCreateInstance)
		{
			// 如果ribbon生命期不为默认值(0.0f)，就需要计算当前的生命期
			if ( false == Ogre::Math::RealEqual(0.0f, mLifeTime) )
			{
				mCurrentLifeTime += time;

				if (mCurrentLifeTime >= mLifeTime)
				{
					mBasicNode->setVisible(false);
					mPoints.clear();

					return;
				}
			}

			// 如果vertex生命期不为默认值(0.0f)，就需要计算当前的生命期
			if ( false == Ogre::Math::RealEqual(0.0f, mVertexLifeTime) )
			{
				// 给所有的点添加life time，如果这个点的生命期到了，就从列表中删除
				for (Points::iterator i = mPoints.begin(); i != mPoints.end();)
				{
					Vertex& vertex = *i;

					vertex.lifeTime += time;

					if (vertex.lifeTime >= mVertexLifeTime)
					{
						i = mPoints.erase(i);
					}
					else
						++i;
				}

				// 保证点的个数是2的倍数
				if (mPoints.size() % 2 != 0)
					mPoints.pop_back();
			}

			Ogre::Vector3 firstPos = transform.mPosition;

			Ogre::Vector3 dir = transform.mRotation.xAxis();
			dir.normalise();
			Ogre::Vector3 secondPos = firstPos + 
				dir * mRibbonWidth;

			mPoints.push_front( Vertex(secondPos) );
			mPoints.push_front( Vertex( firstPos ) );

			while ( mPoints.size() > mPointCount )
			{
				mPoints.pop_back();
				mPoints.pop_back();
			}

			mFirstPosSpline.clear();
			mSecondPosSpline.clear();

			std::list<Vertex>::iterator it = mPoints.begin();

			if (mUseInterpolation)
			{
				while ( it != mPoints.end() )
				{
					mSecondPosSpline.addPoint(it->pos);

					++it;

					mFirstPosSpline.addPoint(it->pos);

					++it;
				}
			}

			// change the vertex buffer,if necessary
			if (!mBuffersCreated)
			{
				if (mUseInterpolation)
					_createBuffer( mPointCount * mInterpolationTimes );
				else
					_createBuffer( mPointCount );
			}

			// set the vertex count that will be rendered
			if (mUseInterpolation)
				mRenderOp.vertexData->vertexCount = mPoints.size() * mInterpolationTimes;
			else
				mRenderOp.vertexData->vertexCount = mPoints.size();

			RenderSystem *pSys = Ogre::Root::getSingleton().getRenderSystem();

			float *lockPtr = static_cast<float *>(vbuf->lock(Ogre::HardwareBuffer::HBL_DISCARD));

			float count = 0.0f;

			float maxSqLen = -1.0f;

			Ogre::Vector3 min(Ogre::Math::POS_INFINITY, Ogre::Math::POS_INFINITY, Ogre::Math::POS_INFINITY);
			Ogre::Vector3 max(Ogre::Math::NEG_INFINITY, Ogre::Math::NEG_INFINITY, Ogre::Math::NEG_INFINITY);

			// 如果alpha值有一个不为0,才需要计算当前的alpha值
			if ( false == Ogre::Math::RealEqual(1.0f, mStartAlphaValue) ||
				false == Ogre::Math::RealEqual(1.0f, mStartAlphaValue) )
			{
				// 由于现在lifetime都保留在各个点中了，所以不进行alpha 的插值
				float timeRatio = mCurrentLifeTime / mLifeTime;

				// 根据当前的生命时间来决定透明度
				if (timeRatio < mFadeInTime)
				{
					// 如果在淡入时间内，就根据比例设置透明度
					float ratio = mCurrentLifeTime / (mFadeInTime * mLifeTime);
					mCurrentStartAlphaValue *= ratio;
					mCurrentEndAlphaValue *= ratio;
				}
				else if(timeRatio > mFadeOutTime)
				{
					// 否则，如果在淡出时间内，就根据比例设置透明度
					float ratio = (mLifeTime - mCurrentLifeTime) / (mFadeOutTime * mLifeTime);
					mCurrentStartAlphaValue *= ratio;
					mCurrentEndAlphaValue *= ratio;
				}
				else
				{
					// 在淡入与淡出时间中，就用原透明度
					mCurrentStartAlphaValue = mStartAlphaValue;
					mCurrentEndAlphaValue = mEndAlphaValue;
				}
			}
			else
			{
				mCurrentStartAlphaValue = 1.0f;
				mCurrentEndAlphaValue = 1.0f;
			}

			if (mUseInterpolation)
			{
				// if we use the simple spline to interpolate the ribbon
				// we will render more vertexs
				int numLoop = mPoints.size() / 2 * mInterpolationTimes; 
				for (int i=0; i<numLoop; ++i)
				{
					float delta = 1.0f;
					if (numLoop > 0.0f)
						delta = count/(numLoop-1);

					float endOpacity = (1.0 - delta) * mCurrentEndAlphaValue;
					float startOpacity = (1.0 - delta) * mCurrentStartAlphaValue;

					// compute the bounding box
					const Ogre::Vector3& pos = mSecondPosSpline.interpolate( (float)i / (float)(numLoop-1) );

					min.makeFloor(pos);
					max.makeCeil(pos);

					maxSqLen = std::max(maxSqLen, pos.squaredLength());

					// point1
					*lockPtr++ = pos.x;
					*lockPtr++ = pos.y;
					*lockPtr++ = pos.z;

					Ogre::RGBA *pCol;
					pCol = static_cast<Ogre::RGBA*>(static_cast<void*>(lockPtr));
					*pCol = Ogre::ColourValue(mEndColour.r * endOpacity, mEndColour.g * endOpacity,
						mEndColour.b * endOpacity, 1.0f).getAsRGBA();
					pCol++;
					// Update lock pointer
					lockPtr = static_cast<float*>(static_cast<void*>(pCol));

					*lockPtr++ = delta;
					*lockPtr++ = 1.0;

					const Ogre::Vector3& pos1 = mFirstPosSpline.interpolate( (float)i / (float)(numLoop-1) );
					min.makeFloor(pos1);
					max.makeCeil(pos1);

					maxSqLen = std::max(maxSqLen, pos1.squaredLength());

					// point2
					*lockPtr++ = pos1.x;
					*lockPtr++ = pos1.y;
					*lockPtr++ = pos1.z;

					pCol = static_cast<Ogre::RGBA*>(static_cast<void*>(lockPtr));
					*pCol = Ogre::ColourValue(mStartColour.r * startOpacity, mStartColour.g * startOpacity,
						mStartColour.b * startOpacity, 1.0f).getAsRGBA();
					pCol++;
					// Update lock pointer
					lockPtr = static_cast<float*>(static_cast<void*>(pCol));

					*lockPtr++ = delta;
					*lockPtr++ = 0.0;

					count+=1.0f;
				}

			}
			else
			{
				float pointCount = (float)(mPoints.size());

				while ( it != mPoints.end() )
				{
					float delta = count/(pointCount-2);
					float endOpacity = (1.0 - delta) * mCurrentEndAlphaValue;
					float startOpacity = (1.0 - delta) * mCurrentStartAlphaValue;

					// compute the bounding box
					const Ogre::Vector3& pos = it->pos;

					min.makeFloor(pos);
					max.makeCeil(pos);

					maxSqLen = std::max(maxSqLen, pos.squaredLength());

					// point1
					*lockPtr++ = it->pos.x;
					*lockPtr++ = it->pos.y;
					*lockPtr++ = it->pos.z;

					Ogre::RGBA *pCol;
					pCol = static_cast<Ogre::RGBA*>(static_cast<void*>(lockPtr));
					*pCol = Ogre::ColourValue(mEndColour.r * endOpacity, mEndColour.g * endOpacity,
						mEndColour.b * endOpacity, 1.0f).getAsRGBA();
					pCol++;
					// Update lock pointer
					lockPtr = static_cast<float*>(static_cast<void*>(pCol));

					*lockPtr++ = delta;
					*lockPtr++ = 1.0;
					++it;

					const Ogre::Vector3& pos1 = it->pos;
					min.makeFloor(pos1);
					max.makeCeil(pos1);

					maxSqLen = std::max(maxSqLen, pos1.squaredLength());

					// point2
					*lockPtr++ = it->pos.x;
					*lockPtr++ = it->pos.y;
					*lockPtr++ = it->pos.z;

					pCol = static_cast<Ogre::RGBA*>(static_cast<void*>(lockPtr));
					*pCol = Ogre::ColourValue(mStartColour.r * startOpacity, mStartColour.g * startOpacity,
						mStartColour.b * startOpacity, 1.0f).getAsRGBA();
					pCol++;
					// Update lock pointer
					lockPtr = static_cast<float*>(static_cast<void*>(pCol));

					*lockPtr++ = delta;
					*lockPtr++ = 0.0;

					++it;

					count+=2.0f;
				}
			}

			vbuf->unlock();

			mBox.setExtents(min, max);
			mBoundingRadius = Ogre::Math::Sqrt(maxSqLen);
			getParentNode()->needUpdate();
		}		
	} 
	//-----------------------------------------------------------------------
	float SpellRibbonModule::getBoundingRadius(void) const
	{
		// TODO: Implementation
		return mBoundingRadius;
	}
	//-----------------------------------------------------------------------
	float SpellRibbonModule::getSquaredViewDepth(const Ogre::Camera* cam) const
	{
		// TODO: Implementation
		Ogre::Vector3 min, max, mid, dist;

		min = mBox.getMinimum();
		max = mBox.getMaximum();
		mid = ((min - max) * 0.5) + min;
		dist = cam->getDerivedPosition() - mid;

		return dist.squaredLength();
		//return 0.0f;
	}	
	//-----------------------------------------------------------------------
	void SpellRibbonModule::_createBuffer( size_t vertexCount )
	{
		if ( vertexCount == 0 )
			return;

		assert (vertexCount % 2 == 0);

		mRenderOp.vertexData = new VertexData;

		mRenderOp.vertexData->vertexCount = vertexCount;
		mRenderOp.vertexData->vertexStart = 0;
		// declaration
		VertexDeclaration *decl = mRenderOp.vertexData->vertexDeclaration;

		size_t offset = 0;

		decl->addElement(0, 0, offset, VET_FLOAT3, VES_POSITION);

		offset += VertexElement::getTypeSize(VET_FLOAT3);
		decl->addElement(0, 0, offset, VET_COLOUR, VES_DIFFUSE);

		offset += VertexElement::getTypeSize(VET_COLOUR);
		decl->addElement(0, 0, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES);

		// create the vertex buffer
		vbuf = 
			Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
			decl->getVertexSize(0),
			mRenderOp.vertexData->vertexCount,
			Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

		mRenderOp.vertexData->setBinding(0, vbuf);

		mBuffersCreated = true;
	}
	//-----------------------------------------------------------------------
	void SpellRibbonModule::_destroyBuffer(void)
	{


		mBuffersCreated = false;
	}
	//-----------------------------------------------------------------------
	void SpellRibbonModule::setUseInterpolation(bool use)
	{
		mUseInterpolation = use;

		_destroyBuffer();
	}

	const String& SpellRibbonModule::getMaterialName(void) const
	{
		return BLANKSTRING;
	}

	//-----------------------------------------------------------------------
	void SpellRibbonModule::setInterpolationTimes(int times)
	{
		mInterpolationTimes = times;

		_destroyBuffer();
	}
	//-----------------------------------------------------------------------
	void SpellRibbonModule::setPointCount( unsigned short count )
	{
		// 保证点的个数是2的倍数
		if (count % 2 != 0)
			--count;

		// we need 4 point to draw a rectangle in OT_TRIANGLE_STRIP mode
		if (count < 4)
			mPointCount = 4;
		else
			mPointCount = count;

		_destroyBuffer();
	}
	
	//-----------------------------------------------------------------------
	void SpellRibbonModule::setFadeInTime(float time)
	{
		if((time < 0.0f) || (time > 1.0f))
			mFadeInTime = 0.0f;
		else
			mFadeInTime = time;
	}
	//-----------------------------------------------------------------------
	void SpellRibbonModule::setFadeOutTime(float time)
	{
		if((time < 0.0f) || (time > 1.0f))
			mFadeOutTime = 0.0f;
		else
			mFadeOutTime = time;
	}
	//-----------------------------------------------------------------------
	void SpellRibbonModule::setVisibleFlag(uint32 flags)
	{
	}
	//-----------------------------------------------------------------------
	void SpellRibbonModule::copyParameters(SpellRibbonModule& newInfo) const
	{        
		newInfo.mPointCount = mPointCount;
		newInfo.mStartColour = mStartColour;
		newInfo.mEndColour = mEndColour;
		newInfo.mStartAlphaValue = mStartAlphaValue;
		newInfo.mEndAlphaValue = mEndAlphaValue;
		newInfo.mFadeInTime = mFadeInTime;
		newInfo.mFadeOutTime = mFadeOutTime;
		newInfo.m_strMatName = m_strMatName;
		newInfo.mRibbonWidth = mRibbonWidth;
		newInfo.mLifeTime = mLifeTime;
		newInfo.mAttachTime = mAttachTime;
		newInfo.mAttachPoint = mAttachPoint;
		newInfo.mOffsetPos = mOffsetPos;
		newInfo.mOffsetRotation = mOffsetRotation;
		newInfo.mUseInterpolation = mUseInterpolation;
		newInfo.mInterpolationTimes = mInterpolationTimes;
		newInfo.mVertexLifeTime = mVertexLifeTime;
		newInfo.mUseAttachRotation = mUseAttachRotation;
	}
	//////////////////////////////////////////////////////////////////////////
	String SpellRibbonModule::CmdPointCount::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getPointCount() );
	}
	void SpellRibbonModule::CmdPointCount::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setPointCount(Ogre::StringConverter::parseUnsignedInt(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdPointCount::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setPointCount(
			static_cast<const SpellRibbonModule *>(source)->getPointCount() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdRibbonWidth::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getRibbonWidth() );
	}
	void SpellRibbonModule::CmdRibbonWidth::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setRibbonWidth(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdRibbonWidth::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setRibbonWidth(
			static_cast<const SpellRibbonModule *>(source)->getRibbonWidth() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdStartColour::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getStartColour() );
	}
	void SpellRibbonModule::CmdStartColour::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setStartColour(Ogre::StringConverter::parseColourValue(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdStartColour::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setStartColour(
			static_cast<const SpellRibbonModule *>(source)->getStartColour() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdEndColour::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getEndColour() );
	}
	void SpellRibbonModule::CmdEndColour::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setEndColour(Ogre::StringConverter::parseColourValue(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdEndColour::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setEndColour(
			static_cast<const SpellRibbonModule *>(source)->getEndColour() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdStartAlpha::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getStartAlpha() );
	}
	void SpellRibbonModule::CmdStartAlpha::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setStartAlpha(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdStartAlpha::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setStartAlpha(
			static_cast<const SpellRibbonModule *>(source)->getStartAlpha() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdEndAlpha::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getEndAlpha() );
	}
	void SpellRibbonModule::CmdEndAlpha::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setEndAlpha(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdEndAlpha::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setEndAlpha(
			static_cast<const SpellRibbonModule *>(source)->getEndAlpha() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdFadeInTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getFadeInTime() );
	}
	void SpellRibbonModule::CmdFadeInTime::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setFadeInTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdFadeInTime::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setFadeInTime(
			static_cast<const SpellRibbonModule *>(source)->getFadeInTime() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdFadeOutTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getFadeOutTime() );
	}
	void SpellRibbonModule::CmdFadeOutTime::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setFadeOutTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdFadeOutTime::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setFadeOutTime(
			static_cast<const SpellRibbonModule *>(source)->getFadeOutTime() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdMaterial::doGet(const void* target) const
	{
		return static_cast<const SpellRibbonModule *>(target)->getMaterialName();
	}
	void SpellRibbonModule::CmdMaterial::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setMaterial(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdMaterial::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setMaterialName(
			static_cast<const SpellRibbonModule *>(source)->getMaterialName() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdLifeTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getLifeTime() );
	}
	void SpellRibbonModule::CmdLifeTime::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setLifeTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdLifeTime::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setLifeTime(
			static_cast<const SpellRibbonModule *>(source)->getLifeTime() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdAttachTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getAttachTime() );
	}
	void SpellRibbonModule::CmdAttachTime::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setAttachTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdAttachTime::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setAttachTime(
			static_cast<const SpellRibbonModule *>(source)->getAttachTime() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdAttachPoint::doGet(const void* target) const
	{
		return static_cast<const SpellRibbonModule *>(target)->getAttachPoint();
	}
	void SpellRibbonModule::CmdAttachPoint::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setAttachPoint(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdAttachPoint::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setAttachPoint(
			static_cast<const SpellRibbonModule *>(source)->getAttachPoint() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdOffsetPos::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getOffsetPos() );
	}
	void SpellRibbonModule::CmdOffsetPos::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setOffsetPos(Ogre::StringConverter::parseVector3(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdOffsetPos::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setOffsetPos(
			static_cast<const SpellRibbonModule *>(source)->getOffsetPos() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdOffsetRotation::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getOffsetRotation() );
	}
	void SpellRibbonModule::CmdOffsetRotation::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setOffsetRotation(Ogre::StringConverter::parseQuaternion(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdOffsetRotation::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setOffsetRotation(
			static_cast<const SpellRibbonModule *>(source)->getOffsetRotation() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdUseInter::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getUseInterpolation() );
	}
	void SpellRibbonModule::CmdUseInter::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setUseInterpolation( Ogre::StringConverter::parseBool(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdUseInter::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setUseInterpolation(
			static_cast<const SpellRibbonModule *>(source)->getUseInterpolation() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdInterTimes::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getInterpolationTimes() );
	}
	void SpellRibbonModule::CmdInterTimes::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setInterpolationTimes( Ogre::StringConverter::parseInt(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdInterTimes::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setInterpolationTimes(
			static_cast<const SpellRibbonModule *>(source)->getInterpolationTimes() );
	}
#endif
	//-----------------------------------------------------------------------
	String SpellRibbonModule::CmdVertexLifeTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule *>(target)->getVertexLifeTime() );
	}
	void SpellRibbonModule::CmdVertexLifeTime::doSet(void* target, const String& val)
	{
		static_cast<SpellRibbonModule *>(target)->setVertexLifeTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void SpellRibbonModule::CmdVertexLifeTime::doCopy(void* target, const void* source)
	{
		// Default implementation just get/set, derived class should be implement
		// their special case version for effective (i.e. avoid string conversion).
		static_cast<SpellRibbonModule *>(target)->setVertexLifeTime(
			static_cast<const SpellRibbonModule *>(source)->getVertexLifeTime() );
	}
#endif

	String SpellRibbonModule::CmdUseAttachRotation::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const SpellRibbonModule*>(target)->getUseAttachRotation());
	}
	void SpellRibbonModule::CmdUseAttachRotation::doSet(void* target,const String& val)
	{
		static_cast<SpellRibbonModule*>(target)->setUseAttachRotation(Ogre::StringConverter::parseBool(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void SpellRibbonModule::CmdUseAttachRotation::doCopy(void* target,const void* source)
	{
		static_cast<SpellRibbonModule*>(target)->setUseAttachRotation(
			static_cast<const SpellRibbonModule*>(source)->getUseAttachRotation());
	}
#endif

	/*
	static CmdPointCount msPointCountCmd;
	static CmdStartColour msStartColour;
	static CmdEndColour msEndColour;
	static CmdStartAlpha msStartAlpha;
	static CmdEndAlpha msEndAlpha;
	static CmdFadeInTime msFadeInTimeCmd;
	static CmdFadeOutTime msFadeOutTimeCmd;
	static CmdMaterial msMaterial;
	static CmdRibbonWidth msRibbonWidthCmd;
	static CmdLifeTime msLifeTimeCmd;
	static CmdAttachTime msAttachTimeCmd;
	static CmdAttachPoint msAttachPointCmd;
	static CmdOffsetPos msOffsetPosCmd;
	static CmdOffsetRotation msOffsetRotationCmd;
	static CmdUseInter msUseInterCmd;
	static CmdInterTimes msInterTimesCmd;
	static CmdVertexLifeTime msVertexLifeTimeCmd;
	static CmdUseAttachRotation msUseAttachRotationCmd;

	unsigned short mPointCount;
	Ogre::ColourValue mStartColour;
	Ogre::ColourValue mEndColour;
	float mStartAlphaValue;
	float mEndAlphaValue;
	float mFadeInTime;
	float mFadeOutTime;
	float mRibbonWidth;
	float mLifeTime;
	float mAttachTime;
	String m_strMatName;
	String mAttachPoint;
	Ogre::Vector3 mOffsetPos;
	Ogre::Quaternion mOffsetRotation;
	bool mUseInterpolation;
	int mInterpolationTimes;
	float mVertexLifeTime;
	bool mUseAttachRotation;
	*/
	/// stream overhead = ID + size
	//const long STREAM_OVERHEAD_SIZE = sizeof(uint16) + sizeof(uint32);
	void SpellRibbonModule::loadBinary( SpellsSerializer* serializer,Ogre::DataStreamPtr& stream )
	{
		serializer->readShorts(stream,&mPointCount,1);
		stream->read(&mStartColour,sizeof(Ogre::ColourValue));
		stream->read(&mEndColour,sizeof(Ogre::ColourValue));
		serializer->readFloats(stream,&mStartAlphaValue,1);
		serializer->readFloats(stream,&mEndAlphaValue,1);
		serializer->readFloats(stream,&mFadeInTime,1);
		serializer->readFloats(stream,&mFadeOutTime,1);
		serializer->readFloats(stream,&mRibbonWidth,1);
		serializer->readFloats(stream,&mLifeTime,1);
		serializer->readFloats(stream,&mAttachTime,1);
		m_strMatName = serializer->readString(stream);
		mAttachPoint = serializer->readString(stream);
		serializer->readObject(stream,mOffsetPos);
		serializer->readObject(stream,mOffsetRotation);
		serializer->readBools(stream,&mUseInterpolation,1);
		stream->read(&mInterpolationTimes,sizeof(int));
		serializer->readFloats(stream,&mVertexLifeTime,1);
		serializer->readBools(stream,&mUseAttachRotation,1);
	}

	void SpellRibbonModule::saveBinary( SpellsSerializer* serializer )
	{
	}

	std::size_t SpellRibbonModule::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;

		tmpSize += sizeof(unsigned short);
		tmpSize += sizeof(Ogre::ColourValue);
		tmpSize += sizeof(Ogre::ColourValue);
		tmpSize += sizeof(float) * 7;
		tmpSize += m_strMatName.length() + 1;
		tmpSize += mAttachPoint.length() + 1;
		tmpSize += sizeof(Ogre::Vector3);
		tmpSize += sizeof(Ogre::Quaternion);
		tmpSize += sizeof(bool);
		tmpSize += sizeof(int);
		tmpSize += sizeof(float);
		tmpSize += sizeof(bool);

		return tmpSize;
	}
}