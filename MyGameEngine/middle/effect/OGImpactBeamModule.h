#ifndef OGImapctBeamModule_h__
#define OGImapctBeamModule_h__


#include "OGImpactModule.h"

// ogre header
#include <OgreColourValue.h>

namespace Ogre	{
	class EffectBillboardChain;
}

namespace Orphigine	{

	class _OrphigineExport ImpactBeamModule : public ImpactModule
	{
	public:		

		// ≤Œ ˝√¸¡Ó
		class CmdNoiseXMin : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdNoiseXMax : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdNoiseYMin : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdNoiseYMax : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdNoiseZMin : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdNoiseZMax : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdNumElements : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdWidthStart : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};


		class CmdWidthEnd : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdColour : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdColourRangeStart : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdColourRangeEnd : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdMaterial : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdFrequency : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		class CmdDestPos : public Ogre::ParamCommand
		{
		public:
			String doGet( const void *target ) const;
			void doSet( void *target, const String &val );
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		/////////////////////////////////////////////////////////////
		ImpactBeamModule(const String &type);
		~ImpactBeamModule();

		virtual bool createRenderInstance(void);
		virtual void destroyRenderInstance(void);
		virtual void updateRenderInstance( Real time, TransformInfo &info );

		virtual void updateExtraTransformInfos( const TransformInfos &infos );
		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();
		virtual char * readFromBuffer(char * pCurrent);
		virtual void saveToFile(std::ofstream & of);

		//////////////////////////////////////////////////////////////////////////
		void setNumBillboardElements( int num );
		int getNumBillboardElements(void) const
		{
			return mNumBillboardElements;
		}

		void setColour(const Ogre::ColourValue& colour);
		void setColour(const Ogre::ColourValue& colourStart, const Ogre::ColourValue& colourEnd);
		void setColourRangeStart(const Ogre::ColourValue& colour);
		void setColourRangeEnd(const Ogre::ColourValue& colour);
		const Ogre::ColourValue& getColour(void) const;
		const Ogre::ColourValue& getColourRangeStart(void) const;
		const Ogre::ColourValue& getColourRangeEnd(void) const;

		void setMaterialName(const String &matName);
		const String getMaterialName(void) const
		{
			return mMaterialName;
		}

		void setFrequency(float frequency);
		float getFrequency(void) const
		{
			return mFrequency;
		}

		/// …Ë÷√visible flag
		virtual void setVisibleFlag(uint32 flags);

		virtual void sleep(void);

	protected:

		bool _createBillboardChains(void);
		void _destroyBillboardChains(void);
		void _updateBillboardChains( Real time );

		void genColour(Ogre::ColourValue& destColour);

	protected:

		float mNoiseXMin;
		float mNoiseXMax;
		float mNoiseYMin;
		float mNoiseYMax;
		float mNoiseZMin;
		float mNoiseZMax;

		int mNumBillboardElements;
		float mWidthStart;
		float mWidthEnd;
		Ogre::ColourValue mColourRangeStart;
		Ogre::ColourValue mColourRangeEnd;

		float mFrequency;
		Ogre::Vector3 mDestPos;
		String mMaterialName;

	protected:
		Ogre::EffectBillboardChain *mBillboardChain;
		float mFrequencyTime;
		float mCurrentFrequencyTime;
		////////////////////////////////////////////////////////////////
		static CmdNoiseXMin msNoiseXMinCmd;
		static CmdNoiseXMax msNoiseXMaxCmd;
		static CmdNoiseYMin msNoiseYMinCmd;
		static CmdNoiseYMax msNoiseYMaxCmd;
		static CmdNoiseZMin msNoiseZMinCmd;
		static CmdNoiseZMax msNoiseZMaxCmd;
		static CmdNumElements msNumElementsCmd;
		static CmdWidthStart msWidthStartCmd;
		static CmdWidthEnd msWidthEndCmd;

		static CmdColour msColourCmd;
		static CmdColourRangeStart msColourRangeStartCmd;
		static CmdColourRangeEnd msColourRangeEndCmd;

		static CmdMaterial msMaterialCmd;

		static CmdFrequency msFrequencyCmd;

		static CmdDestPos	msDestPosCmd;
	};
}

#endif // OGImapctBeamModule_h__