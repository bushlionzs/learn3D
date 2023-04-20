#ifndef __LINE3D_H__
#define __LINE3D_H__
#include "KDefine.h"
#include "OgreSimpleRenderable.h"
#include "OgreColourValue.h"

#define POSITION_BINDING	0
#define TEXCOORD_BINDING	1

typedef std::vector<vector3> PointVecter;

class Line3D :
	public Ogre::SimpleRenderable
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Line3D(void);
	~				Line3D(void);

	void			addPoint(const vector3 &p);
	const vector3	&getPoint(unsigned short index) const;
	unsigned short	getNumPoints(void) const;
	void			updatePoint(unsigned short index, const vector3 &value);
	void			drawLine( vector3 &start, vector3 &end );
	void			drawLines(void);
	void			UpdatePos(const vector3& fvPos);
	void			SetOriginPos(const vector3& fvPos)			{ m_fvOriginPos = fvPos; }
	void			SetColor(const Ogre::ColourValue& colour)	{ m_colour = colour; }

	Ogre::Real		getSquaredViewDepth(const Ogre::Camera *cam) const;
	Ogre::Real		getBoundingRadius(void) const;

	void			UpdateLine();

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	void	_updateRenderQueue(Ogre::RenderQueue * queue);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
protected:
	/*
	 * void getWorldTransforms(Matrix4 *xform) const;
	 */
	const Ogre::Quaternion&	getWorldOrientation(void) const;
	const vector3&			getWorldPosition(void) const;

protected:

	PointVecter					mPoints;
	bool						mDrawn;
	Ogre::AxisAlignedBox		m_OriginBox;
	vector3						m_fvOriginPos;
	Ogre::ColourValue			m_colour;
	Ogre::HardwareVertexBufferSharedPtr m_VertexBufferSharedPtr;

};
#endif /* __LINE3D_H__ */
