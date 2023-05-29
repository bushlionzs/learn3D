#ifndef OGStaticMeshComponent_h__
#define OGStaticMeshComponent_h__

#include <OgreEntity.h>
#include "OGUtils.h"

namespace Ogre 
{
	class StaticMeshBaseComponent : public Entity
	{
		friend class StaticMeshBaseComponentFactory;
	protected:
		StaticMeshBaseComponent();
		StaticMeshBaseComponent(const String& name, MeshPtr& mesh, bool suppressSkeletalAnimation = false);

		virtual ~StaticMeshBaseComponent( );

		typedef std::vector<MaterialPtr> SMMaterialList;
		SMMaterialList mMaterialBackupList;

		bool beyondFogDirty;

	public:
		virtual void _notifyCurrentCamera(Camera* camera);

		void convertToHardwareSkinning( );

	protected:
		void deriveFogMaterial( );
		void updateFogMaterial( );

		//所有LogicModel自己生成的材质名集合，用于卸载
		Orphigine::DerivedMaterialsList mDerivedMaterials;
	};

	class StaticMeshComponent : public StaticMeshBaseComponent
	{
		friend class StaticMeshComponentFactory;
	protected:
		StaticMeshComponent();
		StaticMeshComponent(const String& name, MeshPtr& mesh);

	public:
		const String& getMovableType(void) const;
		void _updateRenderQueue(RenderQueue* queue);

		typedef std::map<AnimationState*, Real> AnimationStateList;

		void _updateAutoAnimationStates(void);
		void addAutoUpdateAnimationState(const String& name, Real timeOffset = 0);
		void removeAutoUpdateAnimationState(const String& name);
		void removeAllAutoUpdateAnimationStates(void);
		const AnimationStateList& getAutoUpdateAnimationStateList(void) const;

	protected:
		AnimationStateList mAutoUpdateAnimationStateList;
		Real mLastUpdateTime;
	};

	class _OrphigineExport StaticMeshBaseComponentFactory : public EntityFactory
	{
	protected:
		MoveObject* createInstanceImpl(const String& name, const NameValuePairList* params);

	public:
		StaticMeshBaseComponentFactory( ) {}
	};

	class _OrphigineExport StaticMeshComponentFactory : public MovableObjectFactory
	{
	protected:
		MoveObject* createInstanceImpl(const String& name, const NameValuePairList* params);

	public:
		StaticMeshComponentFactory() {}
		~StaticMeshComponentFactory() {}

		static String FACTORY_TYPE_NAME;

		const String& getType(void) const;
		void destroyInstance(MoveObject* obj);
	};

} // namespace

#endif // OGStaticMeshComponent_h__