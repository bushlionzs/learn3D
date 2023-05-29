#ifndef OGImpactRibandModule_h__
#define OGImpactRibandModule_h__

#include "OGImpactModule.h"

#include <OgreColourValue.h>

namespace Ogre
{
	class RibbonTrail;
};

namespace Orphigine
{

	class ImpactRibbonModule :	public ImpactModule
	{
	public:
		ImpactRibbonModule(const String &type);
		~ImpactRibbonModule(void);

	public:
		bool createRenderInstance(void);
		void destroyRenderInstance(void);
		void updateRenderInstance( Real time, TransformInfo &info );
		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();

		bool _createRibbonTrail();
		bool _destroyRibbonTrail();
		bool _updateRibbonTrail();

		void	setMaterialName( const String &m );

		const String	getMaterialName() const	{return mMaterialName;}

		virtual void setVisibleFlag(uint32 flags) ;

		Real					mWidthStart;
		Real					mWidthChange;
		Ogre::ColourValue		mColourChange;
		Ogre::ColourValue		mColourStart;
		Real					mTrailLength;
		Real					mWidthMin;	 
		int					mTrailSepNumber;					

	protected:
		Ogre::RibbonTrail*		m_pRibbonTrail;
		Ogre::SceneNode*		m_pRibbonSceneNode;

		Ogre::String			mMaterialName;	
	};

}


#endif // OGImpactRibandModule_h__