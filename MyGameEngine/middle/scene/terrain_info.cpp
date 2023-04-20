#include "OgreHeader.h"
#include "terrain_info.h"
#include "OGUtils.h"
#include "OGUtil.h"

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

	if (ray.getDirection().x == 0 && ray.getDirection().z == 0)//���ߵķ������ϻ�����
	{
		// special case ...

		if (!negativeSide && ray.getDirection().y >= 0)//��������
			return false;
		if (!positiveSide && ray.getDirection().y <= 0)//��������
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
		if (!Ogre::Math::intersects(ray, computerBoundBox(), &d1, &d2))//���Χ�в��ཻ
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
		//���Grid���ĸ�����
		const Ogre::Vector3 vertices[4] =
		{
			getWorldPosFromGridIndex(gridXIndex + 0, gridZIndex + 0),
				getWorldPosFromGridIndex(gridXIndex + 1, gridZIndex + 0),
				getWorldPosFromGridIndex(gridXIndex + 0, gridZIndex + 1),
				getWorldPosFromGridIndex(gridXIndex + 1, gridZIndex + 1),
		};
		const AreaVertexEnum* corners = getGridInfo(getGridIndex(gridXIndex, gridZIndex)).getVertexes();
		std::pair<bool, Real> r;
		//������������
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