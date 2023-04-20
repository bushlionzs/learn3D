#ifndef OGImpactProjectorModule_h__
#define OGImpactProjectorModule_h__


#include "OGImpactModule.h"

// ogre header
#include <OgreColourValue.h>

namespace Orphigine	{

	typedef Ogre::Vector3 ProjectorScaleValue;

	class Projector;

	class _OrphigineExport ImpactProjectorModule : public ImpactModule
	{
	public:

		/** the material used by this projector */
		class CmdMaterialName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};	 
		/** the size of projected area in world unit */
		class CmdProjectionSize : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};	 

		enum { MAX_STAGES = 4 };

		/** the scale adjust of each stage */
		class CmdScaleAdjust : public Ogre::ParamCommand
		{
		public:
			size_t		mIndex;

		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};
		/** the scale time adjust of each stage */
		class CmdScaleTimeAdjust : public Ogre::ParamCommand
		{
		public:
			size_t		mIndex;

		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};
		/** the scale change time */
		class CmdScaleChangeTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};
		/** the colour adjust of each stage */
		class CmdColourAdjust : public Ogre::ParamCommand
		{
		public:
			size_t		mIndex;

		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};
		/** the colour time adjust of each stage */
		class CmdColourTimeAdjust : public Ogre::ParamCommand
		{
		public:
			size_t		mIndex;

		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};
		/** the colour change time */
		class CmdColourChangeTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};		

		class CmdShowFrustum : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		class CmdNearClipDistance : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		class CmdFarClipDistance : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		/////////////////////////////////////////////////////////////
		ImpactProjectorModule(const String &type);
		~ImpactProjectorModule();

		virtual bool createRenderInstance(void);
		virtual void destroyRenderInstance(void);
		virtual void updateRenderInstance( Real time, TransformInfo &info );
		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();
		virtual char * readFromBuffer(char * pCurrent);
		virtual void saveToFile(std::ofstream & of);

		/** set the material that will be used in projector */
		void setMaterialName(const String &name);
		const String &getMaterialName(void) const	{	return mMaterialName;	}

		Projector* getProjector(void)
		{
			return mProjector;
		}

		/** set the range of projection */
		void setProjectionSize(float size);
		float getProjectionSize(void) const
		{
			return mProjectionSize;
		}
		void setProjectionTerrainGridLimit(int size);

		void setScaleAdjust(size_t index, ProjectorScaleValue& scale);
		ProjectorScaleValue getScaleAdjust(size_t index) const;

		void setScaleTimeAdjust(size_t index, Real time);
		Real getScaleTimeAdjust(size_t index) const;		

		void setScaleChangeTime(Real time);
		Real getScaleChangeTime(void) const
		{
			return mScaleChangeTime;
		}

		void setColourAdjust(size_t index, Ogre::ColourValue colour);
		Ogre::ColourValue getColourAdjust(size_t index) const;

		void setColourTimeAdjust(size_t index, Real time);
		Real getColourTimeAdjust(size_t index) const;

		void setColourChangeTime(Real time);
		Real getColourChangeTime(void) const
		{
			return mColourChangeTime;
		}

		void setShowFrustum(bool show);
		bool getShowFrustum(void) const
		{
			return mShowFrustum;
		}

		void setNearClipDistance(Real dis);
		Real getNearClipDistance(void) const
		{
			return mNearClipDistance;
		}

		void setFarClipDistance(Real dis);
		Real getFarClipDistance(void) const
		{
			return mFarClipDistance;
		}

		/// ����visible flag
		virtual void setVisibleFlag(uint32 flags);

		virtual void setVisible(bool visible);


		virtual void shutdown(void);
		virtual void active(void);
		//end
		virtual void sleep(void);

		void enableUsingProjScene(bool bEnable);

	protected:

		bool _createProjector(void);
		void _destroyProjector(void);

		Ogre::Radian _getFovFromProjectionSize(void);

		void _updateProjectorScale(void);
		void _updateProjectorColour(void);

		void _setTextureUnitScale(float uscale, float vscale);

		void _updateProjectorMaterial(void);

	protected:



		String mMaterialName;

		/// the range of projection
		float mProjectionSize;

		ProjectorScaleValue		mScaleAdj[MAX_STAGES];
		float					mScaleTimeAdj[MAX_STAGES];

		Ogre::ColourValue		mColourAdj[MAX_STAGES];
		float					mColourTimeAdj[MAX_STAGES];





		float mScaleChangeTime;
		float mColourChangeTime;

		bool mShowFrustum;

		float mNearClipDistance;
		float mFarClipDistance;

		int   mTerrainGridLimit;
	protected:
		Projector *mProjector;
		bool m_bUsingProjScene;

		float mTextureUnitUScale;
		float mTextureUnitVScale;

		Ogre::ColourValue mProjectorColour;

		////////////////////////////////////////////////////////////////
		static CmdMaterialName msMaterialNameCmd;
		static CmdProjectionSize msProjectionSizeCmd;

		static CmdScaleAdjust	msScaleCmd[MAX_STAGES];
		static CmdScaleTimeAdjust	msScaleTimeCmd[MAX_STAGES];
		static CmdScaleChangeTime msScaleChangeTime;

		static CmdColourAdjust	msColourCmd[MAX_STAGES];
		static CmdColourTimeAdjust	msColourTimeCmd[MAX_STAGES];
		static CmdColourChangeTime msColourChangeTime;
		static CmdShowFrustum msShowFrustumCmd;
		static CmdNearClipDistance msNearClipDistanceCmd;
		static CmdFarClipDistance msFarClipDistanceCmd;
	};
}

#endif // OGImpactProjectorModule_h__