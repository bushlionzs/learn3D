#include "OgreHeader.h"
#include "terrain_info.h"
#include "OGUtils.h"
#include "OGUtil.h"
#include "OgreFrustum.h"

const TerrainInfo::AreaVertexEnum TerrainInfo::mAreaVertexLayout[2][4] =
{
	{ V_LEFT_TOP, V_RIGHT_TOP, V_LEFT_BOTTOM, V_RIGHT_BOTTOM },
	{ V_LEFT_BOTTOM, V_LEFT_TOP, V_RIGHT_BOTTOM, V_RIGHT_TOP }
};

TerrainInfo::TerrainInfo()
{

}

TerrainInfo::~TerrainInfo()
{

}

void TerrainInfo::getLightmapGridTextureWidthAndHeight(uint32_t& width, uint32_t& height) const
{
	switch (mLightmapQuality)
	{
	default:
	case LMQ_LOW:
	{
		width = 1;
		height = 1;
		break;
	}
	case LMQ_MID:
	{
		width = 4;
		height = 4;
		break;;
	}
	case LMQ_HIGH:
	{
		width = 8;
		height = 8;
		break;
	}
	}
}

void TerrainInfo::getLightmapTileTextureWidthAndHeight(uint32_t& width, uint32_t& height) const
{
	getLightmapGridTextureWidthAndHeight(width, height);

	width *= mLightmapGridXSize;
	height *= mLightmapGridZSize;
}

void TerrainInfo::getLightmapNames(
	int32_t tileXIndex, 
	int32_t tileZIndex,
	std::vector<std::string>& lightmaps) const
{
	int tileEndXGrid = (tileXIndex + 1) * mTileGridSize;
	int tileEndZGrid = (tileZIndex + 1) * mTileGridSize;

	for (int zLightmapIndex = tileZIndex * mTileGridSize / mLightmapGridZSize; zLightmapIndex * mLightmapGridZSize < tileEndZGrid; ++zLightmapIndex)
	{
		for (int xLightmapIndex = tileXIndex * mTileGridSize / mLightmapGridXSize; xLightmapIndex * mLightmapGridXSize < tileEndXGrid; ++xLightmapIndex)
		{
			lightmaps.push_back(getLightmapName(xLightmapIndex, zLightmapIndex));
		}
	}
}

String TerrainInfo::getTerrainTileName(int tileXIndex, int tileZIndex) const
{
	char temp[256] = { 0,0 };
	sprintf(temp, "_TerrainTile_%d_%d", tileXIndex, tileZIndex);
	return mName + String(temp);
}

String TerrainInfo::getTerrainTileName(int tileIndex) const
{
	int XIndex = tileIndex % mXTileNum;
	int ZIndex = (tileIndex - XIndex) / mXTileNum;
	char temp[256] = { 0,0 };
	sprintf(temp, "_TerrainTile_%d_%d", XIndex, ZIndex);
	return mName + String(temp);
}

Ogre::Vector3 TerrainInfo::getWorldPosFromGridIndex(int gridXIndex, int gridZIndex) const
{
	return Ogre::Vector3(mFirstGridWorldPos.x + mWorldUnit.x * gridXIndex,
		mFirstGridWorldPos.y + mWorldUnit.y * getGridJointGridHeight(gridXIndex, gridZIndex),
		mFirstGridWorldPos.z + mWorldUnit.z * gridZIndex);
}

Ogre::Vector3 TerrainInfo::getGridJointNormal(int gridXIndex, int gridZIndex) const
{
	assert(isValidGridJoint(gridXIndex, gridZIndex));

	if (!isValidGridJoint(gridXIndex, gridZIndex))
		return Ogre::Vector3::UNIT_Y;

	Real h = getGridJointGridHeight(gridXIndex, gridZIndex);
	Ogre::Vector3 corners[7];
	int count = 0;

	// FIXME: Support GO_FLIP_DIAGONAL flag

#define V(i,j)	((void)(corners[count++] = Ogre::Vector3((i)*mWorldUnit.x, (getGridJointGridHeight(gridXIndex+(i),gridZIndex+(j)) - h)*mWorldUnit.y, (j)*mWorldUnit.z)))
	if (gridXIndex == 0)
	{
		if (gridZIndex != mZGridSize)
		{
			V(0, +1);
		}
		V(+1, 0);
		if (gridZIndex != 0)
		{
			V(+1, -1);
			V(0, -1);
		}
	}
	else if (gridXIndex == mXGridSize)
	{
		if (gridZIndex != 0)
		{
			V(0, -1);
		}
		V(-1, 0);
		if (gridZIndex != mZGridSize)
		{
			V(-1, +1);
			V(0, +1);
		}
	}
	else
	{
		if (gridZIndex != 0)
		{
			V(+1, 0);
			V(+1, -1);
			V(0, -1);
		}
		V(-1, 0);
		if (gridZIndex != mZGridSize)
		{
			V(-1, +1);
			V(0, +1);
			V(+1, 0);
		}
	}
#undef V

	assert(2 <= count && count <= sizeof(corners) / sizeof(*corners));

	Ogre::Vector3 sum(0, 0, 0);
	for (int i = 1; i < count; ++i)
	{
		Ogre::Vector3 n = corners[i - 1].crossProduct(corners[i]);
		assert(n.y > 0);
		n.normalise();
		sum += n;
	}
	sum.normalise();

	return sum;
}

Real TerrainInfo::getGridJointGridHeight(int gridXIndex, int gridZIndex) const
{
	return mHeightmap[getGridJointIndex(gridXIndex, gridZIndex)];
}

int TerrainInfo::getGridJointIndex(int gridXIndex, int gridZIndex) const
{
	assert(isValidGridJoint(gridXIndex, gridZIndex));
	return gridZIndex * (mXGridSize + 1) + gridXIndex;
}

bool TerrainInfo::isValidGridJoint(int gridXIndex, int gridZIndex) const
{
	return  0 <= gridXIndex && 
		gridXIndex <= mXGridSize && 0 <= gridZIndex && gridZIndex <= mZGridSize;
}

void TerrainInfo::resetDeriveValues(void)
{
	mInvWorldUnit.x = 1.0 / mWorldUnit.x;
	mInvWorldUnit.y = 1.0 / mWorldUnit.y;
	mInvWorldUnit.z = 1.0 / mWorldUnit.z;

	mWorldCenter.x = mFirstGridWorldPos.x + mWorldUnit.x * mXGridSize / 2;
	mWorldCenter.y = mFirstGridWorldPos.y;
	mWorldCenter.z = mFirstGridWorldPos.z + mWorldUnit.z * mZGridSize / 2;

	mWorldMinX = mFirstGridWorldPos.x + mWorldUnit.x * 0;
	mWorldMaxX = mFirstGridWorldPos.x + mWorldUnit.x * mXGridSize;
	mWorldMinZ = mFirstGridWorldPos.z + mWorldUnit.z * 0;
	mWorldMaxZ = mFirstGridWorldPos.z + mWorldUnit.z * mZGridSize;

	mXTileNum = (mXGridSize - 1) / mTileGridSize + 1;
	mZTileNum = (mZGridSize - 1) / mTileGridSize + 1;

	mHeightmap.resize((mXGridSize + 1) * (mZGridSize + 1));
	mGridInfos.resize(mXGridSize * mZGridSize);
}

const TerrainInfo::GridInfoStr& TerrainInfo::getGridInfo(int gridIndex) const
{
	return mGridInfos[gridIndex];
}

int TerrainInfo::getGridIndex(int gridXIndex, int gridZIndex) const
{
	return gridZIndex * mXGridSize + gridXIndex;
}

int	TerrainInfo::getXGridSize() const
{
	return mXGridSize;
}

int	TerrainInfo::getZGridSize() const
{
	return mZGridSize;
}

std::pair<Real, Real> TerrainInfo::getWorldIndexFromRealGridIndex(Real gridXIndex, Real gridZIndex) const
{
	return std::pair<Real, Real>(
		((gridXIndex * mWorldUnit.x) + mFirstGridWorldPos.x),
		((gridZIndex * mWorldUnit.z) + mFirstGridWorldPos.z));
}


Real	TerrainInfo::getWorldIndexWorldHeight(Real worldXIndex, Real worldZIndex) const
{
	if (mXGridSize <= 0 || mZGridSize <= 0)
		return 0;

	Real x_pct, z_pct;
	int x_index, z_index;

	// Safety catch, if the point asked for is outside of
	// the map, it will clamp to edge
	if (worldXIndex <= mWorldMinX)
	{
		x_index = 0;
		x_pct = 0;
	}
	else if (worldXIndex >= mWorldMaxX)
	{
		x_index = mXGridSize - 1;
		x_pct = 1;
	}
	else
	{
		x_pct = (worldXIndex - mFirstGridWorldPos.x) * mInvWorldUnit.x;
		x_index = Orphigine::getFastInt(x_pct);
		x_pct -= x_index;
		if (x_index >= mXGridSize)
		{
			x_index = mXGridSize - 1;
			x_pct = 1;
		}
	}
	if (worldZIndex <= mWorldMinZ)
	{
		z_index = 0;
		z_pct = 0;
	}
	else if (worldZIndex >= mWorldMaxZ)
	{
		z_index = mZGridSize - 1;
		z_pct = 1;
	}
	else
	{
		z_pct = (worldZIndex - mFirstGridWorldPos.z) * mInvWorldUnit.z;
		z_index = Orphigine::getFastInt(z_pct);
		z_pct -= z_index;
		if (z_index >= mZGridSize)
		{
			z_index = mZGridSize - 1;
			z_pct = 1;
		}
	}

	// bilinear interpolate to find the height.
	Real t, h;
	if (getGridInfo(getGridIndex(x_index, z_index)).gridOperationFlags & GO_FLIP_DIAGONAL)
	{
		if (z_pct <= x_pct)
		{
			t = getGridJointGridHeight(x_index + 1, z_index + 0);
			h = t +
				(getGridJointGridHeight(x_index + 0, z_index + 0) - t) * (1 - x_pct) +
				(getGridJointGridHeight(x_index + 1, z_index + 1) - t) * z_pct;
		}
		else
		{
			t = getGridJointGridHeight(x_index + 0, z_index + 1);
			h = t +
				(getGridJointGridHeight(x_index + 0, z_index + 0) - t) * (1 - z_pct) +
				(getGridJointGridHeight(x_index + 1, z_index + 1) - t) * x_pct;
		}
	}
	else
	{
		if (x_pct + z_pct <= 1)
		{
			t = getGridJointGridHeight(x_index + 0, z_index + 0);
			h = t +
				(getGridJointGridHeight(x_index + 1, z_index + 0) - t) * x_pct +
				(getGridJointGridHeight(x_index + 0, z_index + 1) - t) * z_pct;
		}
		else
		{
			t = getGridJointGridHeight(x_index + 1, z_index + 1);
			h = t +
				(getGridJointGridHeight(x_index + 1, z_index + 0) - t) * (1 - z_pct) +
				(getGridJointGridHeight(x_index + 0, z_index + 1) - t) * (1 - x_pct);
		}
	}

	return mFirstGridWorldPos.y + mWorldUnit.y * h;
}

Real	TerrainInfo::getGridJointWorldHeight(int gridXIndex, int gridZIndex) const
{
	return mFirstGridWorldPos.y + getGridJointGridHeight(gridXIndex, gridZIndex) * mWorldUnit.y;
}

bool TerrainInfo::setGroundTileAABB(
	Ogre::AxisAlignedBox& box,
	int gridXIndex,
	int gridZIndex,
	int gridXSize,
	int gridZSize) const
{
	if (gridXIndex >= 0 && gridXSize > 0 && (gridXIndex + gridXSize <= mXGridSize) &&
		gridZIndex >= 0 && gridZSize > 0 && (gridZIndex + gridZSize <= mZGridSize)
		)
	{
		Real minHeight = Ogre::Math::POS_INFINITY;
		Real maxHeight = Ogre::Math::NEG_INFINITY;
		int patch = mXGridSize + 1;
		const Real* pHeight = &mHeightmap[gridZIndex * patch + gridXIndex];
		for (int z = 0; z <= gridZSize; ++z, pHeight += patch)
		{
			for (int x = 0; x <= gridXSize; ++x)
			{
				Real h = pHeight[x];
				if (minHeight > h) minHeight = h;
				if (maxHeight < h) maxHeight = h;
			}
		}


		box.setExtents(
			Ogre::Vector3(mFirstGridWorldPos.x + mWorldUnit.x * gridXIndex,
				mFirstGridWorldPos.y + mWorldUnit.y * minHeight,
				mFirstGridWorldPos.z + mWorldUnit.z * gridZIndex),
			Ogre::Vector3(mFirstGridWorldPos.x + mWorldUnit.x * (gridXIndex + gridXSize),
				mFirstGridWorldPos.y + mWorldUnit.y * maxHeight,
				mFirstGridWorldPos.z + mWorldUnit.z * (gridZIndex + gridZSize))
		);
		return true;
	}
	return false;
}

bool TerrainInfo::isRayIntersectGround(
	const Ogre::Ray& ray,
	Ogre::Vector3& intersectPos,
	Ogre::Vector3* intersectNormal,
	bool allowOutside,
	bool positiveSide,
	bool negativeSide) const
{
	float x, z;

	if (ray.getDirection().x == 0 && ray.getDirection().z == 0)//射线的方向向上或向下
	{
		// special case ...

		if (!negativeSide && ray.getDirection().y >= 0)//方向向上
			return false;
		if (!positiveSide && ray.getDirection().y <= 0)//方向向下
			return false;

		x = ray.getOrigin().x;
		z = ray.getOrigin().z;
		if (!allowOutside && !isValidWorldIndex(x, z))
			return false;

		Real h = getWorldIndexWorldHeight(x, z);

		if (!negativeSide && ray.getOrigin().y < h)
			return false;

		if (!positiveSide && ray.getOrigin().y > h)
			return false;
	}
	else
	{
		Real d1, d2;
		if (!Ogre::Math::intersects(ray, computerBoundBox(), &d1, &d2))//与包围盒不相交
			return false;

		Ogre::Vector3 start = ray.getPoint(d1);
		Ogre::Vector3 end = ray.getPoint(d2);

		// intersect test through each grid that 'touch' the line segment
		std::pair<bool, Real> r(false, 0.0f);

		Real xstep = ray.getDirection().x * mWorldUnit.z;
		Real zstep = ray.getDirection().z * mWorldUnit.x;
		if (Ogre::Math::Abs(xstep) < Ogre::Math::Abs(zstep))
		{
			// step base z axis
			
			int zinc = ray.getDirection().z > 0 ? +1 : -1;
			Real zstart = (start.z - mFirstGridWorldPos.z) * mInvWorldUnit.z;
			int zbegin = Ogre::Math::Floor(zstart) - zinc;
			int zend = Ogre::Math::Floor((end.z - mFirstGridWorldPos.z) * mInvWorldUnit.z) + zinc;
			Real xfactor = xstep / zstep;
			Real xinc = zinc * xfactor;
			Real xiter = ((start.x - mFirstGridWorldPos.x) * mInvWorldUnit.x) - (zstart - zbegin) * xfactor;
			assert((zend - zbegin) * zinc > 0);
			assert(Ogre::Math::Abs(xinc) <= 1);
			for (int zi = zbegin; zi != zend; zi += zinc, xiter += xinc)
			{
				int xi = Ogre::Math::Floor(xiter);
				r = isRayIntersectGrid(ray, xi + 0, zi, positiveSide, negativeSide);
				if (r.first)
					break;
				r = isRayIntersectGrid(ray, xi - 1, zi, positiveSide, negativeSide);
				if (r.first)
					break;
				r = isRayIntersectGrid(ray, xi + 1, zi, positiveSide, negativeSide);
				if (r.first)
					break;
			}
		}
		else
		{
			// step base x azis
			int xinc = ray.getDirection().x > 0 ? +1 : -1;
			Real xstart = (start.x - mFirstGridWorldPos.x) * mInvWorldUnit.x;
			int xbegin = Ogre::Math::Floor(xstart) - xinc;
			int xend = Ogre::Math::Floor((end.x - mFirstGridWorldPos.x) * mInvWorldUnit.x) + xinc;
			Real zfactor = zstep / xstep;
			Real zinc = xinc * zfactor;
			Real ziter = ((start.z - mFirstGridWorldPos.z) * mInvWorldUnit.z) - (xstart - xbegin) * zfactor;
			assert((xend - xbegin) * xinc > 0);
			assert(Ogre::Math::Abs(zinc) <= 1);
			for (int xi = xbegin; xi != xend; xi += xinc, ziter += zinc)
			{
				int zi = Ogre::Math::Floor(ziter);
				r = isRayIntersectGrid(ray, xi, zi + 0, positiveSide, negativeSide);
				if (r.first)
					break;
				r = isRayIntersectGrid(ray, xi, zi - 1, positiveSide, negativeSide);
				if (r.first)
					break;
				r = isRayIntersectGrid(ray, xi, zi + 1, positiveSide, negativeSide);
				if (r.first)
					break;
			}
		}

		if (!r.first)
			return false;

		x = ray.getOrigin().x + ray.getDirection().x * r.second;
		z = ray.getOrigin().z + ray.getDirection().z * r.second;
	}

	if (intersectNormal)
		getWorldIndexPosAndNormal(x, z, intersectPos, *intersectNormal);
	else
		intersectPos = Ogre::Vector3(x, getWorldIndexWorldHeight(x, z), z);
	return true;
}

const Ogre::AxisAlignedBox& TerrainInfo::computerBoundBox() const
{
	if (mAABBox.isNull())
	{
		if (!mHeightmap.empty())
		{
			std::vector<Ogre::Real>::const_iterator it = mHeightmap.begin();
			Real minHeight = *it;
			Real maxHeight = *it;
			while (++it != mHeightmap.end())
			{
				Real height = *it;
				if (minHeight > height)
					minHeight = height;
				else if (maxHeight < height)
					maxHeight = height;
			}
			mAABBox.setExtents(mWorldMinX, 
				mFirstGridWorldPos.y + mWorldUnit.y * minHeight, mWorldMinZ,
				mWorldMaxX, mFirstGridWorldPos.y + mWorldUnit.y * maxHeight, mWorldMaxZ);
		}
	}
	else
	{
		if (mHeightmap.empty())
			mAABBox.setNull();
	}
	return mAABBox;
}

bool TerrainInfo::isValidGridIndex(int gridXIndex, int gridZIndex) const
{
	return 0 <= gridXIndex && 
		gridXIndex < mXGridSize && 
		0 <= gridZIndex && 
		gridZIndex < mZGridSize;
}

std::pair<bool, Real>	TerrainInfo::isRayIntersectGrid(
	const Ogre::Ray& ray,
	int gridXIndex,
	int gridZIndex,
	bool positiveSide,
	bool negativeSide) const
{
	if (isValidGridIndex(gridXIndex, gridZIndex))
	{
		//获得Grid的四个顶点
		const Ogre::Vector3 vertices[4] =
		{
			getWorldPosFromGridIndex(gridXIndex + 0, gridZIndex + 0),
				getWorldPosFromGridIndex(gridXIndex + 1, gridZIndex + 0),
				getWorldPosFromGridIndex(gridXIndex + 0, gridZIndex + 1),
				getWorldPosFromGridIndex(gridXIndex + 1, gridZIndex + 1),
		};
		const AreaVertexEnum* corners = getGridInfo(getGridIndex(gridXIndex, gridZIndex)).getVertexes();
		std::pair<bool, Real> r;
		//射线三角形求交
		r = Ogre::Math::intersects(ray, vertices[corners[1]], vertices[corners[0]], vertices[corners[2]], positiveSide, negativeSide);
		if (r.first)
			return r;

		r = Ogre::Math::intersects(ray, vertices[corners[1]], vertices[corners[2]], vertices[corners[3]], positiveSide, negativeSide);
		if (r.first)
			return r;
	}

	return std::pair<bool, Real>(false, 0.0f);
}

bool TerrainInfo::getWorldIndexPosAndNormal(
	Real worldXIndex, 
	Real worldZIndex, 
	Ogre::Vector3& worldPos, 
	Ogre::Vector3& worldNormal) const
{
	Ogre::Vector3& here = worldPos;
	here = Ogre::Vector3(worldXIndex, getWorldIndexWorldHeight(worldXIndex, worldZIndex), worldZIndex);
	// FIXME
	Ogre::Vector3 left;
	left.x = worldXIndex - 1;
	left.z = worldZIndex;
	left.y = getWorldIndexWorldHeight(left.x, left.z);

	Ogre::Vector3 down;
	down.x = worldXIndex;
	down.z = worldZIndex + 1;
	down.y = getWorldIndexWorldHeight(down.x, down.z);

	left = left - here;
	down = down - here;

	worldNormal = left.crossProduct(down);
	worldNormal.normalise();
	return true;
}

std::pair<Real, Real> TerrainInfo::getRealGridIndexFromWorldIndex(Real worldXIndex, Real worldZIndex) const
{
	return std::pair<Real, Real>(
		(worldXIndex - mFirstGridWorldPos.x) * mInvWorldUnit.x,
		(worldZIndex - mFirstGridWorldPos.z) * mInvWorldUnit.z);
}


uint32_t TerrainInfo::getClippingMask(const Ogre::Matrix4& m, const Ogre::Vector3& v)
{
	Ogre::Vector4 p;
	p = v;
	p = m * p;

	uint32_t mask = 0;
	if (p.x <= -p.w) mask |= 1 << Ogre::FRUSTUM_PLANE_LEFT;
	if (p.x >= +p.w) mask |= 1 << Ogre::FRUSTUM_PLANE_RIGHT;
	if (p.y <= -p.w) mask |= 1 << Ogre::FRUSTUM_PLANE_BOTTOM;
	if (p.y >= +p.w) mask |= 1 << Ogre::FRUSTUM_PLANE_TOP;
	if (p.z <= -p.w) mask |= 1 << Ogre::FRUSTUM_PLANE_NEAR;
	if (p.z >= +p.w) mask |= 1 << Ogre::FRUSTUM_PLANE_FAR;
	return mask;
}

std::pair<int, int>	TerrainInfo::getNearestGridJoint(Real worldXIndex, Real worldZIndex) const
{
	return std::pair<int, int>(
		Ogre::Math::Floor((worldXIndex - mFirstGridWorldPos.x) * mInvWorldUnit.x + (Real)0.5),
		Ogre::Math::Floor((worldZIndex - mFirstGridWorldPos.z) * mInvWorldUnit.z + (Real)0.5));
}

size_t TerrainInfo::isFrustumIntersectGround(
	const Ogre::Frustum* frustum,
	int areaLimit,
	bool receivedDecalOnly,
	std::vector<Ogre::Vector3>& positions,
	std::vector<Ogre::Vector3>* normals)
{
	assert(areaLimit >= 0);

	const Ogre::AxisAlignedBox& bound = computerBoundBox();
	if (!frustum->isVisible(bound))
		return false;

	// Clip by Y plane to found terrain region that affect by the frustum

	const Ogre::Vector3* corners = frustum->getWorldSpaceCorners();
	static const size_t edges[][2] =
	{
		0, 1,       // top-near
			1, 2,       // left-near
			2, 3,       // bottom-near
			3, 0,       // right-near

			4, 5,       // top-far
			5, 6,       // left-far
			6, 7,       // bottom-far
			7, 4,       // right-far

			0, 4,       // top-right
			1, 5,       // top-left
			2, 6,       // bottom-left
			3, 7,       // bottom-right
	};

	const Real minY = bound.getMinimum().y;
	const Real maxY = bound.getMaximum().y;
	Real minX = Ogre::Math::POS_INFINITY;
	Real minZ = Ogre::Math::POS_INFINITY;
	Real maxX = Ogre::Math::NEG_INFINITY;
	Real maxZ = Ogre::Math::NEG_INFINITY;
	const Real epsilon = 1e-3f;
	for (size_t e = 0; e < sizeof(edges) / sizeof(*edges); ++e)
	{
		const Ogre::Vector3& v0 = corners[edges[e][0]];
		const Ogre::Vector3& v1 = corners[edges[e][1]];
		Real diff = v1.y - v0.y;
		if (Ogre::Math::Abs(diff) <= epsilon)
		{
			if (Ogre::Math::RealEqual(minY, v0.y, epsilon) || Ogre::Math::RealEqual(maxY, v0.y, epsilon))
			{
				Real x = v0.x;
				Real z = v0.z;
				if (minX > x) minX = x;
				if (maxX < x) maxX = x;
				if (minZ > z) minZ = z;
				if (maxZ < z) maxZ = z;
			}
		}
		else
		{
			Real denom = 1 / diff;
			Real t;

			t = (minY - v0.y) * denom;
			if (0 <= t && t <= 1)
			{
				Real x = v0.x + (v1.x - v0.x) * t;
				Real z = v0.z + (v1.z - v0.z) * t;
				if (minX > x) minX = x;
				if (maxX < x) maxX = x;
				if (minZ > z) minZ = z;
				if (maxZ < z) maxZ = z;
			}

			t = (maxY - v0.y) * denom;
			if (0 <= t && t <= 1)
			{
				Real x = v0.x + (v1.x - v0.x) * t;
				Real z = v0.z + (v1.z - v0.z) * t;
				if (minX > x) minX = x;
				if (maxX < x) maxX = x;
				if (minZ > z) minZ = z;
				if (maxZ < z) maxZ = z;
			}
		}
	}

	if (!(minX < maxX && minZ < maxZ))
	{
		// The projector may be full inside the terrain bounding box, so use the
		// projector world bounding box to determinate the intersection triangles
		const Ogre::AxisAlignedBox& aabb = frustum->getWorldBoundingBox(true);
		minX = aabb.getMinimum().x; minZ = aabb.getMinimum().z;
		maxX = aabb.getMaximum().x; maxZ = aabb.getMaximum().z;
	}

	if (!(minX < maxX && minZ < maxZ))
		return 0;

	int startX = std::max(Ogre::Math::Floor((minX - this->mFirstGridWorldPos.x) * this->mInvWorldUnit.x), 0.0f);
	int startZ = std::max(Ogre::Math::Floor((minZ - this->mFirstGridWorldPos.z) * this->mInvWorldUnit.z), 0.0f);
	int endX = std::min(Ogre::Math::Ceil((maxX - this->mFirstGridWorldPos.x) * this->mInvWorldUnit.x), (float)mXGridSize);
	int endZ = std::min(Ogre::Math::Ceil((maxZ - this->mFirstGridWorldPos.z) * this->mInvWorldUnit.z), (float)mZGridSize);
	if (!(startX < endX && startZ < endZ))
		return 0;

	Ogre::Matrix4 eyeToWorld = frustum->getViewMatrix().inverse();

	// Adjust max vertices
	int sizeX = endX - startX;
	int sizeZ = endZ - startZ;
	if (sizeX * sizeZ > areaLimit)
	{
		Ogre::Ray ray(
			Ogre::Vector3(+eyeToWorld[0][3], +eyeToWorld[1][3], +eyeToWorld[2][3]),
			Ogre::Vector3(-eyeToWorld[0][2], -eyeToWorld[1][2], -eyeToWorld[2][2]));
		Ogre::Vector3 position;
		if (!this->isRayIntersectGround(ray, position))
			return 0; // just in case

		std::pair<int, int> hit = this->getNearestGridJoint(position.x, position.z);
		if (sizeX < sizeZ)
		{
			sizeX = std::max(Ogre::Math::Floor(Ogre::Math::Sqrt(
				(Real)areaLimit * sizeX / sizeZ)), 1.0f);
			sizeZ = areaLimit / sizeX;
		}
		else
		{
			sizeZ = std::max(Ogre::Math::Floor(Ogre::Math::Sqrt(
				(Real)areaLimit * sizeZ / sizeX)), 1.0f);
			sizeX = areaLimit / sizeZ;
		}
		startX = std::max(hit.first - sizeX / 2, 0);
		startZ = std::max(hit.second - sizeZ / 2, 0);
		endX = std::min(startX + sizeX, this->mXGridSize);
		endZ = std::min(startZ + sizeZ, this->mZGridSize);
		assert(startX < endX&& startZ < endZ);
		if (!(startX < endX && startZ < endZ))
			return 0; // just in case
	}
	size_t maxVertices = sizeX * sizeZ * 2 * 3;

	// Pre-allocate buffer
	// 此处耗费内存过大，有待优化 [15/01/2009 dscky 内存优化]
	positions.reserve(positions.size() + maxVertices);
	if (normals)
		normals->reserve(normals->size() + maxVertices);

	// Compute view and projection matrix for fast clipping 
	Ogre::Matrix4 viewProjectionMatrix =
		frustum->getProjectionMatrix() * frustum->getViewMatrix();

	// Get the view vector base on projection type
	Ogre::Vector4 vv;
	if (frustum->getProjectionType() == Ogre::PT_PERSPECTIVE)
	{
		// Use view position as view vector
		vv[0] = eyeToWorld[0][3];
		vv[1] = eyeToWorld[1][3];
		vv[2] = eyeToWorld[2][3];
		vv[3] = eyeToWorld[3][3];
	}
	else
	{
		// Use view direction as view vector
		vv[0] = eyeToWorld[0][2];
		vv[1] = eyeToWorld[1][2];
		vv[2] = eyeToWorld[2][2];
		vv[3] = eyeToWorld[3][2];
	}

	// Gather triangles
	size_t numTriangles = 0;
	for (int z = startZ; z < endZ; ++z)
	{
		for (int x = startX; x < endX; ++x)
		{
			const GridInfoStr& gridInfo = this->getGridInfo(getGridIndex(x, z));

			// Skip decal disabled grids
			if (receivedDecalOnly && (gridInfo.gridOperationFlags & GO_DISABLE_DECAL))
				continue;

			const Ogre::Vector3 p[4] =
			{
				this->getWorldPosFromGridIndex(x + 0, z + 0),
					this->getWorldPosFromGridIndex(x + 1, z + 0),
					this->getWorldPosFromGridIndex(x + 0, z + 1),
					this->getWorldPosFromGridIndex(x + 1, z + 1),
			};

			/*const uint m[4] =
			{
				getClippingMask(viewProjectionMatrix, p[0]),
					getClippingMask(viewProjectionMatrix, p[1]),
					getClippingMask(viewProjectionMatrix, p[2]),
					getClippingMask(viewProjectionMatrix, p[3]),
			};
			if (m[0] & m[1] & m[2] & m[3])
				continue;

			if ((m[0] & 1 << Ogre::FRUSTUM_PLANE_FAR) ||
				(m[1] & 1 << Ogre::FRUSTUM_PLANE_FAR) ||
				(m[2] & 1 << Ogre::FRUSTUM_PLANE_FAR) ||
				(m[3] & 1 << Ogre::FRUSTUM_PLANE_FAR))
			{
				continue;
			}*/

			const Ogre::Vector3 n[4] =
			{
				this->getGridJointNormal(x + 0, z + 0),
					this->getGridJointNormal(x + 1, z + 0),
					this->getGridJointNormal(x + 0, z + 1),
					this->getGridJointNormal(x + 1, z + 1),
			};

			const TerrainInfo::AreaVertexEnum* corners = gridInfo.getVertexes();
			Ogre::Vector4 faceNormal;

			faceNormal = Ogre::Math::calculateFaceNormalWithoutNormalize(p[corners[1]], p[corners[0]], p[corners[2]]);
			if (faceNormal.dotProduct(vv) > 0)
			{
				positions.push_back(p[corners[1]]);
				positions.push_back(p[corners[0]]);
				positions.push_back(p[corners[2]]);
				if (normals)
				{
					normals->push_back(n[corners[1]]);
					normals->push_back(n[corners[0]]);
					normals->push_back(n[corners[2]]);
				}
				++numTriangles;
			}

			faceNormal = Ogre::Math::calculateFaceNormalWithoutNormalize(p[corners[1]], p[corners[2]], p[corners[3]]);
			if (faceNormal.dotProduct(vv) > 0)
			{
				positions.push_back(p[corners[1]]);
				positions.push_back(p[corners[2]]);
				positions.push_back(p[corners[3]]);
				if (normals)
				{
					normals->push_back(n[corners[1]]);
					normals->push_back(n[corners[2]]);
					normals->push_back(n[corners[3]]);
				}
				++numTriangles;
			}
		}
	}

	return numTriangles * 3;
}