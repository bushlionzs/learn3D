#ifndef OgreTexcoordBillboardParticleRenderer_h__
#define OgreTexcoordBillboardParticleRenderer_h__


#include "OgreBillboardParticleRenderer.h"
#include "OgreParticle.h"

namespace Ogre	{

	//////////////////////////////////////////////////////////////////////////	
	class TexCoordBillboardParticleRenderer : public BillboardParticleRenderer
	{
	public:
		class CmdTexcoordStacks : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};
		class CmdTexcoordSlices : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};
		class CmdTexcoordRepeatTimes : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		//////////////////////////////////////////////////////////////////////////
		TexCoordBillboardParticleRenderer();

		virtual const String& getType(void) const;
		virtual void _updateRenderQueue(RenderQueue* queue, 
			std::list<Particle*>& currentParticles, bool cullIndividually);

		void setTexcoordStacks(ulong stacks);
		ulong getTexcoordStacks(void) const;

		void setTexcoordSlices(ulong slices);
		ulong getTexcoordSlices(void) const;

		void setTexcoordRepeatTimes(Real times);
		Real getTexcoordRepeatTimes(void) const;

		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();
		virtual char * readFromBuffer(char * pCurrent);
		virtual void saveToFile(std::ofstream & of);

		virtual void _notifyTextureAtlasInf(int uAtlasNum, int vAtlasNum, int uIndex, int vIndex) {}
	protected:
		ulong mTexcoordStacks;
		ulong mTexcoordSlices;
		Real  mTexcoordRepeatTimes;

		//////////////////////////////////////////////////////////////////////////
		static CmdTexcoordStacks msTexcoordStacksCmd;
		static CmdTexcoordSlices msTexcoordSlicesCmd;
		static CmdTexcoordRepeatTimes   msTexcoordRepeatTimesCmd;
	};

	class TexCoordBillboardParticleRendererFactory : public ParticleSystemRendererFactory
	{
	public:
		static String msRendererType;
		virtual const String& getType() const
		{
			return msRendererType;
		}

		virtual ParticleSystemRenderer* createInstance( const String& name )
		{
			return new TexCoordBillboardParticleRenderer();
		}

		virtual void destroyInstance( ParticleSystemRenderer* inst)
		{
			delete inst;
		}
	};
}

#endif // OgreTexcoordBillboardParticleRenderer_h__