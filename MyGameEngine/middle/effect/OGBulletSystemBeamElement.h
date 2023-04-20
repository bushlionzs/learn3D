#ifndef OGBulletSystemBeamElement_h__
#define OGBulletSystemBeamElement_h__

#include "OGBulletSystemElement.h"
#include "OGImpact.h"

#include <OgreColourValue.h>

namespace Ogre	{
	class EffectBillboardChain;
}

namespace Orphigine	
{

	struct TransformInfo;

	class BulletSystemBeamElement : public BulletSystemElement
	{
	public:		

		BulletSystemBeamElement();
		virtual ~BulletSystemBeamElement();

		// ≤Œ ˝√¸¡Ó
		class CmdNoiseXMin : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdNoiseXMax : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdNoiseYMin : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdNoiseYMax : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdNoiseZMin : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdNoiseZMax : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdNumElements : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdWidthStart : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdWidthEnd : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdColour : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdColourRangeStart : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdColourRangeEnd : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdMaterial : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdFrequency : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdDestPos : public Ogre::ParamCommand
		{
		public:
			String doGet( const void *target ) const;
			void doSet( void *target, const String &val );
		};

		/////////////////////////////////////////////////////////////

		virtual bool				createRenderInstance(void);
		virtual void				destroyRenderInstance(void);
		virtual void				updateRenderInstance( Real time , const Ogre::Vector3& sourcePosition,
			const Ogre::Vector3& destPosition);

		//////////////////////////////////////////////////////////////////////////
		void						setNumBillboardElements( int num );
		int							getNumBillboardElements(void) const;

		void						setColour(const Ogre::ColourValue& colour);
		void						setColour(const Ogre::ColourValue& colourStart, const Ogre::ColourValue& colourEnd);
		void						setColourRangeStart(const Ogre::ColourValue& colour);
		void						setColourRangeEnd(const Ogre::ColourValue& colour);
		const Ogre::ColourValue&	getColour(void) const;
		const Ogre::ColourValue&	getColourRangeStart(void) const;
		const Ogre::ColourValue&	getColourRangeEnd(void) const;

		void						setMaterialName(const String &matName);
		const String&				getMaterialName(void) const;

		void						setFrequency(float frequency);
		float						getFrequency(void) const;

		/// …Ë÷√visible flag
		virtual void				setVisibleFlag(uint32 flags);

		virtual void				sleep(void);

		void						copyAttributesTo(BulletSystemBeamElement& target) const;

		void						createElementSceneNode(Ogre::SceneNode* node);

	protected:

		bool						_createBillboardChains(void);
		void						_destroyBillboardChains(void);
		void						_updateBillboardChains( Real time );

		void						genColour(Ogre::ColourValue& destColour);

	protected:

		Ogre::EffectBillboardChain*		mBillboardChain;	

		float							mNoiseXMin;
		float							mNoiseXMax;
		float							mNoiseYMin;
		float							mNoiseYMax;
		float							mNoiseZMin;
		float							mNoiseZMax;
		int								mNumBillboardElements;
		float							mWidthStart;
		float							mWidthEnd;
		Ogre::ColourValue				mColourRangeStart;
		Ogre::ColourValue				mColourRangeEnd;
		String							mMaterialName;
		float							mFrequency;

		Ogre::Vector3					m_sourcePosition;
		Ogre::Vector3					m_destPosition;	
		float							mFrequencyTime;
		float							mCurrentFrequencyTime;

		static CmdNoiseXMin				msNoiseXMinCmd;
		static CmdNoiseXMax				msNoiseXMaxCmd;
		static CmdNoiseYMin				msNoiseYMinCmd;
		static CmdNoiseYMax				msNoiseYMaxCmd;
		static CmdNoiseZMin				msNoiseZMinCmd;
		static CmdNoiseZMax				msNoiseZMaxCmd;
		static CmdNumElements			msNumElementsCmd;
		static CmdWidthStart			msWidthStartCmd;
		static CmdWidthEnd				msWidthEndCmd;
		static CmdColour				msColourCmd;
		static CmdColourRangeStart		msColourRangeStartCmd;
		static CmdColourRangeEnd		msColourRangeEndCmd;
		static CmdMaterial				msMaterialCmd;
		static CmdFrequency				msFrequencyCmd;
	};
}
#endif // OGBulletSystemBeamElement_h__