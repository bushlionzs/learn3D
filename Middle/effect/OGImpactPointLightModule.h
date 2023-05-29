#ifndef OGImpactPointLightModule_h__
#define OGImpactPointLightModule_h__


#include "OGImpactModule.h"

#include <OgreColourValue.h>

namespace Ogre	{
	class Light;
}

namespace Orphigine	{

	class ImpactPointLightModule : public ImpactModule
	{
	public:

		class CmdDiffuse : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdSpecular : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		class CmdRange : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		class CmdAttenuationConstant : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		class CmdAttenuationLinear : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		class CmdAttenuationQuadric : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif      
		};

		/////////////////////////////////////////////////////////////
		ImpactPointLightModule(const String &type);
		~ImpactPointLightModule();

		virtual bool createRenderInstance(void);
		virtual void destroyRenderInstance(void);
		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();
		virtual char * readFromBuffer(char * pCurrent);
		virtual void saveToFile(std::ofstream & of);

		void setDiffuse(const Ogre::ColourValue& diffuse);
		Ogre::ColourValue getDiffuse(void) const
		{
			return mDiffuse;
		}

		void setSpecular(const Ogre::ColourValue& specular);
		Ogre::ColourValue getSpecular(void) const
		{
			return mSpecular;
		}

		void setRange(Real range);
		Real getRange(void) const
		{
			return mRange;
		}

		void setAttenuationConstant(Real constant);
		Real getAttenuationConstant(void) const
		{
			return mAttenuationConstant;
		}

		void setAttenuationLinear(Real linear);
		Real getAttenuationLinear(void) const
		{
			return mAttenuationLinear;
		}

		void setAttenuationQuadric(Real quadric);
		Real getAttenuationQuadric(void) const
		{
			return mAttenuationQuadric;
		}

		/// …Ë÷√visible flag
		virtual void setVisibleFlag(uint32 flags);

		void update( Real time, TransformInfo &info );
		void OnParamChanged();
	protected:

		bool _createLight(void);
		void _destroyLight(void);

	protected:

		Ogre::Light* mLight;

		Ogre::ColourValue mDiffuse;
		Ogre::ColourValue mSpecular;

		Real mRange;
		Real mAttenuationConstant;
		Real mAttenuationLinear;
		Real mAttenuationQuadric;

		////////////////////////////////////////////////////////////////
		static CmdDiffuse  msDiffuseCmd;
		static CmdSpecular msSpecularCmd;
		static CmdRange msRangeCmd;
		static CmdAttenuationConstant msAttenuationConstantCmd;
		static CmdAttenuationLinear msAttenuationLinearCmd;
		static CmdAttenuationQuadric msAttenuationQuadricCmd;

	public:
		Ogre::ColourValue __getColourValueByTime( float nTime );

		Ogre::ColourValue			mColourStart;
		Ogre::ColourValue			mColourEnd;
		float						mTimeChange;

		Ogre::ColourValue			mColourDelta1;
		Ogre::ColourValue			mColourDelta2;
		float						mTimePass;


	};
}

#endif // OGImpactPointLightModule_h__