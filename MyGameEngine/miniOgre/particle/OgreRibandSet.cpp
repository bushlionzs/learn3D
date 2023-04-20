#include "OgreHeader.h"
#include "OgreRibandSet.h"

#include <OgreSceneNode.h>

namespace Ogre
{
	RibandSet::RibandSet(const String& name, size_t maxElements, 
		size_t numberOfChains, bool useTextureCoords, bool useColours)
		: BillboardChain(name, maxElements, 0, useTextureCoords, useColours, true)
		, mSquaredElemLength(0.0f)
		, mDefaultElemWidth(0.0f)
		, mDefaultElemLength(0.0f)
		, mAllDefaultSize(true)
		, mHeadAlpha(1.0f)
		, mTailAlpha(1.0f)
		, mNeedChangeColour(false)
		, mHeadWidthScale(1.0f)
		, mTailWidthScale(1.0f)
		, mNeedChangeWidth(false)
	{
		// use U as varying texture coord, so we can use 1D textures to 'smear'
		setTextureCoordDirection(TCD_U);
	}
	//-----------------------------------------------------------------------
	void RibandSet::_notifyResized(void)
	{
		mAllDefaultSize = false;
	}
	//-----------------------------------------------------------------------
	void RibandSet::setNumberOfChains(size_t numChains)
	{
		BillboardChain::setNumberOfChains(numChains);
	}
	//-----------------------------------------------------------------------
	void RibandSet::updateRiband(size_t index, const Vector3& pos, bool worldSpace, const ColourValue& colour, Real elemWidth)
	{
		// Node has changed somehow, we're only interested in the derived position
		ChainSegment& seg = mChainSegmentList[index];
		Real realWidth;
		// �����ǰ�õ�������ϵͳ�����������Ӵ�С
		if (mAllDefaultSize)
			realWidth = mDefaultElemWidth;
		// �����ǰ�õ�������ϵͳӰ���������������Ӵ�С
		else
			realWidth = elemWidth;
		Vector3 newPos = pos;
		if (mParent && worldSpace)
		{
			// Transform position to ourself space
			newPos = mParent->_getDerivedOrientation().UnitInverse() *
				(newPos - mParent->_getDerivedPosition()) / mParent->_getDerivedScale();
		}
		bool done = false;
		Ogre::Quaternion quater;
		if (seg.head == SEGMENT_EMPTY)
		{
			
			Element e(newPos, realWidth, 0, colour, quater);
			addChainElement(index, e);
			addChainElement(index, e);
			done = true;
		}

		while (!done)
		{

			Element& headElem = mChainElementList[seg.start + seg.head];
			size_t nextElemIdx = seg.head + 1;
			if (nextElemIdx == mMaxElementsPerChain)
				nextElemIdx = 0;
			Element& nextElem = mChainElementList[seg.start + nextElemIdx];

			Vector3 diff = newPos - nextElem.position;
			Real sqlen = diff.squaredLength();
			if (sqlen >= mSquaredElemLength)
			{
				Vector3 scaledDiff = diff * (mDefaultElemLength / Math::Sqrt(sqlen));
				headElem.position = nextElem.position + scaledDiff;

				Element newElem(newPos, realWidth, 0.0f, colour, quater);
				addChainElement(index, newElem);

				diff = newPos - headElem.position;
				if (diff.squaredLength() <= mSquaredElemLength)   
					done = true;
			}
			else
			{
				headElem.position = newPos;
				done = true;
			}

			if ((seg.tail + 1) % mMaxElementsPerChain == seg.head)
			{
				Element& tailElem = mChainElementList[seg.start + seg.tail];
				size_t preTailIdx;
				if (seg.tail == 0)
					preTailIdx = mMaxElementsPerChain - 1;
				else
					preTailIdx = seg.tail - 1;
				Element& preTailElem = mChainElementList[seg.start + preTailIdx];

				Vector3 taildiff = tailElem.position - preTailElem.position;
				Real taillen = taildiff.length();
				if (taillen > 1e-06)
				{
					Real tailsize = mDefaultElemLength - diff.length();
					taildiff *= tailsize / taillen;
					tailElem.position = preTailElem.position + taildiff;
				}
			}
		}

		size_t elementCount;
		// ����addElement�е�ʵ�֣����head����tail��˵��chain�Ѿ��������ˣ����headС��tail��˵��chainδ��
		if (seg.head > seg.tail)
			elementCount = getMaxChainElements();
		else if (seg.head < seg.tail)
			elementCount = seg.tail - seg.head + 1;

		assert (seg.head != seg.tail);

		// ȡ�����chain�е�һ�������һ��Ԫ��
		const Element& firstElem = mChainElementList[seg.start + seg.tail];
		const Element& lastElem = mChainElementList[seg.start + seg.head];

		// ��������֮���ƽ������
		Real totalLength = (lastElem.position - firstElem.position).squaredLength();

		// ����������0���Ž��м��㣨��ÿ��particle��һ�ν����������ʱ�����ǵľ�����0��
		if (false == Math::RealEqual(0.0f, totalLength))
		{
			// ������ǰchain�е�����ʵ��Ԫ��
			for (size_t i=0; i<elementCount; ++i)
			{
				Element e = getChainElement(index, i);

				// ���㵱ǰԪ�����һ��Ԫ��֮���ƽ�����룬������Ԫ����chain�е�ʵ��λ�ã��������������ƽ��������̣��ٿ���
				// ��ֱ���������ʵ��length�������ܽ�ʡһ�ο�������
				Real ratio = 1.0f - Math::Sqrt( (e.position - firstElem.position).squaredLength() / totalLength );
				e.texCoord = ratio;

				if (mNeedChangeColour)
					e.colour = colour * (mHeadAlpha + (mTailAlpha - mHeadAlpha) * ratio);

				if (mNeedChangeWidth)
					e.width = realWidth * (mHeadWidthScale + (mTailWidthScale - mHeadWidthScale) * ratio);

				updateChainElement(index,i,e);
			}
		}

		mBoundsDirty = true;

		if (mParent)
			mParent->needUpdate();
	}
	//-----------------------------------------------------------------------
	void RibandSet::resetRiband(size_t index)
	{
		clearChain(index);

		// we removed an entry so indexes need updating
		mIndexContentDirty = true;
		mBoundsDirty = true;
		// tell parent node to update bounds
		if (mParent)
			mParent->needUpdate();
	}
	//-----------------------------------------------------------------------
	void RibandSet::setHeadAlpha(Real alpha)
	{
		mHeadAlpha = alpha;

		// �����һ����ֵ��Ϊ1������Ҫ�ı���ɫ
		if ( false == Math::RealEqual(1.0f, mHeadAlpha) || 
			false == Math::RealEqual(1.0f, mTailAlpha) )
			mNeedChangeColour = true;            
	}

	Ogre::Real RibandSet::getHeadAlpha( void ) const
	{
		return mHeadAlpha;
	}

	//-----------------------------------------------------------------------
	void RibandSet::setTailAlpha(Real alpha)
	{
		mTailAlpha = alpha;

		// �����һ����ֵ��Ϊ1������Ҫ�ı���ɫ
		if ( false == Math::RealEqual(1.0f, mHeadAlpha) || 
			false == Math::RealEqual(1.0f, mTailAlpha) )
			mNeedChangeColour = true;
	}

	Ogre::Real RibandSet::getTailAlpha( void ) const
	{
		return mTailAlpha;
	}

	//-----------------------------------------------------------------------
	void RibandSet::setHeadWidthScale(Real scale)
	{
		mHeadWidthScale = scale;

		// �����һ����ֵ��Ϊ1������Ҫ�ı���ɫ
		if ( false == Math::RealEqual(1.0f, mHeadWidthScale) || 
			false == Math::RealEqual(1.0f, mTailWidthScale) )
			mNeedChangeWidth = true;
	}

	Ogre::Real RibandSet::getHeadWidthScale( void ) const
	{
		return mHeadWidthScale;
	}

	//-----------------------------------------------------------------------
	void RibandSet::setTailWidthScale(Real scale)
	{
		mTailWidthScale = scale;

		// �����һ����ֵ��Ϊ1������Ҫ�ı���ɫ
		if ( false == Math::RealEqual(1.0f, mHeadWidthScale) || 
			false == Math::RealEqual(1.0f, mTailWidthScale) )
			mNeedChangeWidth = true;
	}

	Ogre::Real RibandSet::getTailWidthScale( void ) const
	{
		return mTailWidthScale;
	}

	//-----------------------------------------------------------------------
	void RibandSet::setDefaultSize(Real width, Real length)
	{
		mDefaultElemWidth = width;
		mDefaultElemLength = length;

		mSquaredElemLength = mDefaultElemLength * mDefaultElemLength;
	}
	//-----------------------------------------------------------------------
	void RibandSet::setMaxChainElements(size_t maxElements)
	{
		BillboardChain::setMaxChainElements(maxElements);
		mBuffersNeedRecreating = mIndexContentDirty = true;
	}
}