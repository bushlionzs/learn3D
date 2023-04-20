#ifndef OGImpactMeshModule_h__
#define OGImpactMeshModule_h__



#include "OGImpactModule.h"

// ogre header
namespace Ogre	{
	class Entity;
}

namespace Orphigine	{

	class ImpactMeshModule : public ImpactModule
	{
	public:

		// ≤Œ ˝√¸¡Ó
		class CmdMeshName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdMaterialName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif	
		};

		/////////////////////////////////////////////////////////////
		ImpactMeshModule(const String &type);
		~ImpactMeshModule();

		virtual bool createRenderInstance(void);
		virtual void destroyRenderInstance(void);
		virtual void destroyMe(void);
		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();
		virtual char * readFromBuffer(char * pCurrent);
		virtual void saveToFile(std::ofstream & of);

		void setMeshName(const String &name);

		const String &getMeshName(void) const	{	return mMeshName;	}

		void setMaterialName(const String &name);

		const String &getMaterialName(void) const	{	return mMaterialName;	}

		/// …Ë÷√visible flag
		virtual void setVisibleFlag(uint32 flags);
	protected:

		bool _createMesh(void);
		void _destroyMesh(void);

	protected:

		String mMeshName;
		String mMaterialName;
		Ogre::Entity *mEntity;

		////////////////////////////////////////////////////////////////
		static CmdMeshName msMeshNameCmd;
		static CmdMaterialName msMaterialNameCmd;
	};
}

#endif // OGImpactMeshModule_h__