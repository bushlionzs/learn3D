#include "OgreHeader.h"
#include "line3d.h"
#include "OgreNode.h"
#include "OgreHardwareVertexBuffer.h"
#include "OgreCamera.h"
#include "OgreRoot.h"
#include "vertex_declaration.h"
#include "OgreHardwareBufferManager.h"

Line3D::Line3D(void)
{
	mRenderOp.vertexData = new Ogre::VertexData();
	mDrawn = false;

	this->setMaterial("BaseWhiteNoLighting");
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Line3D::~Line3D(void)
{
	delete mRenderOp.vertexData;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Line3D::addPoint(const vector3 &p)
{
	mPoints.push_back(p);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const vector3 &Line3D::getPoint(unsigned short index) const
{
	assert(index < mPoints.size() && "Point index is out of bounds!!");

	return mPoints[index];
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
unsigned short Line3D::getNumPoints(void) const
{
	return (unsigned short) mPoints.size();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Line3D::updatePoint(unsigned short index, const vector3 &value)
{
	if (index < mPoints.size())
	{
		mPoints[index] = value;
	}	
}

void Line3D::UpdatePos(const vector3& fvPos)
{
	vector3 fvRelatePos = fvPos - m_fvOriginPos;

	Ogre::Matrix4 worldMatrix = Ogre::Matrix4::IDENTITY;
	worldMatrix.setTrans(fvRelatePos);
	//setWorldTransform(worldMatrix);

	Ogre::AxisAlignedBox box = m_OriginBox;
	box.transform(worldMatrix);	
	setBoundingBox(box);

	if (getParentNode())
		getParentNode()->needUpdate(true);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Line3D::drawLine(vector3 &start, vector3 &end)
{
	if(mPoints.size()) mPoints.clear();

	mPoints.push_back(start);
	mPoints.push_back(end);

	drawLines();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Line3D::drawLines(void)
{
	if(mDrawn)
		return;

	mDrawn = true;

	/* Initialization stuff */
	mRenderOp.indexData = 0;
	mRenderOp.vertexData->vertexCount = mPoints.size();
	mRenderOp.vertexData->vertexStart = 0;
	mRenderOp.operationType = Ogre::RenderOperation::OT_LINE_STRIP;	/* OT_LINE_LIST, OT_LINE_STRIP */
	mRenderOp.useIndexes = false;

	VertexDeclaration	*decl = mRenderOp.vertexData->vertexDeclaration;


	size_t offset = 0;
	decl->addElement(POSITION_BINDING, 0, offset, VET_FLOAT3, VES_POSITION);
	offset += VertexElement::getTypeSize(VET_FLOAT3);
	decl->addElement(POSITION_BINDING, 0, offset, VET_COLOUR, VES_DIFFUSE);

	m_VertexBufferSharedPtr = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer
		(
			decl->getVertexSize(POSITION_BINDING),
			mRenderOp.vertexData->vertexCount,
			Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE
		);

	bind->setBinding(POSITION_BINDING, m_VertexBufferSharedPtr);

	UpdateLine();
}

void Line3D::UpdateLine()
{
	if (mPoints.empty())
		return;

	if (!m_VertexBufferSharedPtr.get())
		return;

	if (mRenderOp.vertexData->vertexCount != mPoints.size())
		return;

	int32	size = (int32) mPoints.size();
	vector3 vaabMin = mPoints[0];
	vector3 vaabMax = mPoints[0];
	Ogre::Real	*prPos = static_cast<Ogre::Real *>( m_VertexBufferSharedPtr->lock( Ogre::HardwareBuffer::HBL_DISCARD ) );

	for(int32 i = 0; i < size; i++)
	{
		*prPos++ = mPoints[i].x;
		*prPos++ = mPoints[i].y;
		*prPos++ = mPoints[i].z;
		*prPos = m_colour.getAsBYTE();
		*prPos++;

		if(mPoints[i].x < vaabMin.x) vaabMin.x = mPoints[i].x;
		if(mPoints[i].y < vaabMin.y) vaabMin.y = mPoints[i].y;
		if(mPoints[i].z < vaabMin.z) vaabMin.z = mPoints[i].z;
		if(mPoints[i].x > vaabMax.x) vaabMax.x = mPoints[i].x;
		if(mPoints[i].y > vaabMax.y) vaabMax.y = mPoints[i].y;
		if(mPoints[i].z > vaabMax.z) vaabMax.z = mPoints[i].z;
	}

	m_VertexBufferSharedPtr->unlock();

	mBox.setExtents(vaabMin, vaabMax);
	m_OriginBox = mBox;

	getMaterial()->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
	setQueryFlags(0);
	if (getParentNode())
		getParentNode()->needUpdate(true);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Ogre::Real Line3D::getSquaredViewDepth(const Ogre::Camera *cam) const
{
	vector3 vMin, vMax, vMid, vDist;

	vMin = mBox.getMinimum();
	vMax = mBox.getMaximum();
	vMid = ((vMin - vMax) * 0.5) + vMin;
	vDist = cam->getDerivedPosition() - vMid;

	return vDist.squaredLength();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Ogre::Real Line3D::getBoundingRadius(void) const
{
	return Ogre::Math::Sqrt( std::max( mBox.getMaximum().squaredLength(), mBox.getMinimum().squaredLength() ) );
}


const Ogre::Quaternion &Line3D::getWorldOrientation(void) const
{
	return Ogre::Quaternion::IDENTITY;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
const vector3 &Line3D::getWorldPosition(void) const
{
	return vector3::ZERO;
}


void Line3D::_updateRenderQueue(Ogre::RenderQueue *queue)
{
	
}
