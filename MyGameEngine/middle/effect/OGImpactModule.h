#ifndef OGImpactModule_h__
#define OGImpactModule_h__


// ogre header
#include <OgreStringInterface.h>
#include <OgreDataStream.h>


#include "OGImpact.h"

class Ogre::Serializer;

namespace Orphigine	
{

	class Engine;
	class ImpactModule : public Ogre::StringInterface, public ImpactBasic
	{
	public:

		class CmdLifeTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};
		class CmdStartTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};   
		class CmdRelPos : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};		
		class CmdRelOrientation : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

	public:
		/////////////////////////////////////////////////////////////
		ImpactModule(const String &type);
		virtual ~ImpactModule();

		const String &getType(void) const 	{	return mElementType;	}

		/// dump the info of this element.
		void dump(std::ofstream &of) const;

		virtual bool createRenderInstance(void) = 0;
		virtual void destroyRenderInstance(void)	{	mIsRenderInstanceCreated = false;	}
		virtual void updateRenderInstance( Real time, TransformInfo &info ) {	}
		virtual void setTransformInfo( const TransformInfo &info );
		virtual void update( Real time, TransformInfo &info );

		///	set the relative position of the parent effect
		void setRelPos( const Ogre::Vector3 &pos );

		///	get the relative position of the parent effect
		const Ogre::Vector3& getRelPos(void) const	{	return mRelPos;	}

		/// set the relative orientation of the parent effect
		void setRelOrientation( const Ogre::Quaternion& orientation );
		/// get the relative orientation of the parent effect
		const Ogre::Quaternion& getRelOrientation(void) const
		{
			return mRelOrientation;
		}

		/**	set the born time of this element
		@param time second
		*/
		virtual void setStartTime(Real time)	{	mStartTime = time;	}
		/**	get the born time of this element
		@param time second
		*/
		Real getStartTime(void)	const {	return mStartTime;	}

		/**	set the life time of this element
		@param time second
		*/
		void setLifeTime(Real time)	{	mLifeTime = time;	}
		/**	get the born time of this element
		@param time second
		*/
		Real getLifeTime(void) const	{	return mLifeTime;	}

		/** let this element sleep.
		@remark when the element reach its life time, it will be not deleted, it will just
		be sleep(disappear in scene)
		*/
		virtual void sleep(void);

		/** the opposite operation of sleep.
		*/
		virtual void active(void);

		bool isActive(void)	{	return mIsActive;	}

		/**	set the effect parent */
		void setParent( Impact *parent )	
		{	
			assert (parent);
			mEffectParent = parent;
		}
		/**	get the effect parent */
		Impact * getParent(void)	{	return mEffectParent;	}

		/**	create the scene node of the element
		@param parentNode the parent scene node of the node of element
		*/
		void createSceneNode( Ogre::SceneNode *parentNode );

		virtual void destroyMe(void);
		bool isDestroy(void)	{	return mIsDestroy;	}

		virtual void updateExtraTransformInfos( const TransformInfos &infos )	{	}

		virtual void shutdown(void)	{	}

		virtual char * readFromBuffer(char * pCurrent);
		virtual void saveToFile(std::ofstream & of);
		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)=0;
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer)=0;
		virtual std::size_t	calcSerializedSize()=0;
	protected:

		bool initDefaults(const String &mType);

	protected:

		String mElementType;		
		/// the render instance is created?(maybe we don't need this member data)
		bool mIsRenderInstanceCreated;
		/// current life time of this element.
		Real mCurrentLifeTime;//当前期
		/// current born time of this element, if this equal to mStartTime, the element will be born.
		Real mCurrentStartTime;//当前启动期
		bool mIsActive;
		/// the parent effect
		Impact *mEffectParent;
		bool mIsDestroy;
		/// the born time of this element.
		Real mStartTime;//诞生期
		/// the life time of this element, is zero by default, if it is zero, the element will live forever.
		Real mLifeTime;//生长期
		/// the position relative to its parent scene node.
		Ogre::Vector3 mRelPos;//相对父节点的位置
		/// the orientation relative to its parent scene node.
		Ogre::Quaternion mRelOrientation;//相对父节点的旋转
		////////////////////////////////////////////////////////////////
		static CmdStartTime msStartTimeCmd;
		static CmdLifeTime msLifeTimeCmd;
		static CmdRelPos msRelPosCmd;
		static CmdRelOrientation msRelOrientationCmd;
	};
}

#endif // OGImpactModule_h__