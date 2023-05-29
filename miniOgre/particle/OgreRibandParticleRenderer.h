#ifndef OgreRibandParticleRenderer_h__
#define OgreRibandParticleRenderer_h__


#include <OgreParticleSystemRenderer.h>
#include "particle_common.h"

namespace Ogre
{
	class RibandSet;
	class RibandParticleRenderer : public ParticleSystemRenderer
	{
	public:
		class  CmdHeadAlpha : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class  CmdTailAlpha : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class  CmdHeadWidthScale : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class  CmdTailWidthScale : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class  CmdElementCount : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		RibandParticleRenderer();
		~RibandParticleRenderer();

		void setHeadAlpha(Real alpha);
		Real getHeadAlpha(void) const;

		void setTailAlpha(Real alpha);
		Real getTailAlpha(void) const;

		void setHeadWidthScale(Real width);
		Real getHeadWidthScale(void) const;

		void setTailWidthScale(Real width);
		Real getTailWidthScale(void) const;

		void setElementCount(size_t count);
		size_t getElementCount(void) const;

		virtual const String& getType(void) const;
		virtual void _updateRenderQueue(RenderQueue* queue, 
			std::list<Particle*>& currentParticles, bool cullIndividually);
		virtual void _setMaterial(MaterialPtr& mat);
		virtual void _notifyCurrentCamera(Camera* cam);
		virtual void _notifyParticleRotated(void);
		virtual void _notifyParticleResized(void);
		virtual void _notifyParticleQuota(size_t quota);
		virtual void _notifyAttached(Node* parent, bool isTagPoint = false);
		virtual void _notifyDefaultDimensions(Real width, Real height);
		virtual void setRenderQueueGroup(uint8 queueID);
		virtual void setKeepParticlesInLocalSpace(bool keepLocal);
		virtual Ogre::SortMode _getSortMode(void) const;
		virtual ParticleVisualData* _createVisualData(void);
		virtual void _destroyVisualData(ParticleVisualData* vis);
		virtual void _notifyParticleExpired(Particle* particle);
		virtual void _notifyParticleMoved(std::list<Particle*>& currentParticles);

		virtual char * readFromBuffer(char * pCurrent);
		virtual void saveToFile(std::ofstream & of);
		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();
	protected:

		RibandSet*	mRibbonSet;
		bool		mIsWorldSpace;
		/// 用于标识当前的空闲ribbon下标
		size_t		mNextRibbonIndex;
		static CmdHeadAlpha msHeadAlphaCmd;
		static CmdTailAlpha msTailAlphaCmd;
		static CmdHeadWidthScale msHeadWidthScaleCmd;
		static CmdTailWidthScale msTailWidthScaleCmd;
		static CmdElementCount msElementCountCmd;
	};

	class RibbonRendererFactory : public ParticleSystemRendererFactory
	{
	public:
		static String msRendererType;

		virtual const String& getType() const
		{
			return msRendererType;
		}
		virtual ParticleSystemRenderer* createInstance( const String& name )
		{
			return new RibandParticleRenderer();
		}
		virtual void destroyInstance( ParticleSystemRenderer* inst)
		{
			delete inst;
		}
	};
}

#endif // OgreRibandParticleRenderer_h__