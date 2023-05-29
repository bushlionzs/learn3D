#ifndef OgreMeshComponentParticleRenderer_h__
#define OgreMeshComponentParticleRenderer_h__


#include "OgreParticleSystemRenderer.h"
#include "OgreMaterial.h"
#include "particle_common.h"

namespace Ogre	{

	class MeshComponentParticleVisualData;
	class Node;

	/** The type of billboard to use. */
	enum MeshOrientationType
	{
		/// origin mesh orientation
		MOT_ORIENTED_ORIGIN,
		/// oriented speed direction
		MOT_ORIENTED_SELF,
	};

	class _OrphigineExport MeshComponentParticleRenderer : public ParticleSystemRenderer
	{
	public:

		class  CmdMeshName : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class  CmdOrientType : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		typedef std::vector<MeshComponentParticleVisualData *> MeshComponentParticleVisualDataPool;

		//////////////////////////////////////////////////////////////////////////
		MeshComponentParticleRenderer();
		~MeshComponentParticleRenderer();

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
		virtual void _notifyParticleMoved(std::list<Particle*>& currentParticles);
		virtual void _notifyParticleExpired(Particle* particle);

		void setMeshName(const String& name);
		const String& getMeshName(void) const	{	return mMeshName;	}

		void setMaterialName( const String& name );

		void setMeshOrientationType(MeshOrientationType mot);
		MeshOrientationType getMeshOrientationType(void) const;

		void removeAllMeshParticle(void);

		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();
		virtual char * readFromBuffer(char * pCurrent);
		virtual void saveToFile(std::ofstream & of);
		void _freeMeshComponentParticleVisualDatas(void);

	protected:
		String mMeshName;
		String mMaterialName;
		MaterialPtr mpMaterial;

		bool mWorldSpace;
		bool mMeshRotation;
		bool mMeshSizeChanged;
		Node *mParticleSystemNode;
		Real mDefaultWidth;
		Real mDefaultHeight;
		MeshOrientationType mMeshOrientationType;
		MeshComponentParticleVisualDataPool mMeshComponentParticleVisualDataPool;
		size_t mNextPoolIndex;
		uint8_t mRenderQueue_ID;
	protected:

		static CmdMeshName msMeshNameCmd;
		static CmdOrientType msOrientationTypeCmd;
	};

	class MeshComponentParticleRendererFactory : public ParticleSystemRendererFactory
	{
	public:
		static String msRendererType;
		virtual const String& getType() const
		{
			return msRendererType;
		}

		virtual ParticleSystemRenderer* createInstance( const String& name )
		{
			return new MeshComponentParticleRenderer();
		}
		virtual void destroyInstance( ParticleSystemRenderer* inst)
		{
			delete inst;
		}
	};
}

#endif // OgreMeshComponentParticleRenderer_h__