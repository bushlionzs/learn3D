#ifndef OgreRibandSet_h__
#define OgreRibandSet_h__

#include "OgreBillboardChain.h"
#include "OgreParticle.h"

namespace Ogre
{
	class RibandSet : public BillboardChain
	{
	public:

		RibandSet(const String& name, size_t maxElements = 20, size_t numberOfChains = 1, 
			bool useTextureCoords = true, bool useColours = true);

		void _notifyResized(void);
		void setDefaultSize(Real width, Real length);

		void setNumberOfChains(size_t numChains);
		void setMaxChainElements(size_t maxElements);

		void updateRiband(size_t index, const Vector3& pos, bool worldSpace, const ColourValue& colour, Real elemWidth);
		void resetRiband(size_t index);

		void setHeadAlpha(Real alpha);
		Real getHeadAlpha(void) const;

		void setTailAlpha(Real alpha);
		Real getTailAlpha(void) const;

		void setHeadWidthScale(Real scale);
		Real getHeadWidthScale(void) const;

		void setTailWidthScale(Real scale);
		Real getTailWidthScale(void) const;

	protected:
		Real mDefaultElemWidth;
		Real mDefaultElemLength;
		bool mAllDefaultSize;
		Real mSquaredElemLength;
		Real mHeadAlpha;
		Real mTailAlpha;
		bool mNeedChangeColour;
		Real mHeadWidthScale;
		Real mTailWidthScale;
		bool mNeedChangeWidth;
	};

	class RibbonParticleData : public ParticleVisualData
	{
	public:
		RibbonParticleData(size_t chainIndex)
			: mRibbonIndex(chainIndex)
		{
		}

		size_t getRibbonIndex(void)
		{
			return mRibbonIndex;
		}

	protected:
		size_t mRibbonIndex;
	};
}

#endif // OgreRibandSet_h__