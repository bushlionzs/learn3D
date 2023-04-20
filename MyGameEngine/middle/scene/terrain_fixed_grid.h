
#include "terrain_grid.h"
class VertexData;
class CustomRenderable;
class VertexDeclaration;
class TerrainFixedGrid : public TerrainGrid
{
public:
	
public:
	TerrainFixedGrid(SceneNode* parent, Terrain *creator,
		int32_t xbase, int32_t zbase, int32_t xsize, int32_t zsize, int32_t TileIndex);
    virtual ~TerrainFixedGrid();
	
	virtual const std::vector<Renderable*>& getRenderableList();
	virtual bool createGeometry(
		TerrainInfo* data, 
		int32_t xbase, 
		int32_t zbase,
		int32_t xsize,
		int32_t zsize);
	virtual bool destoryGeometry(void);
	bool directCreateGeometry(
		TerrainInfo* data, 
		int xbase, 
		int zbase, 
		int xsize, 
		int zsize);
	bool createGeometryData();
	bool createGeometryFromData(TempMaterialBucketMap& matMap);

	const AxisAlignedBox& getBoundingBox(void) const;
public:
    /** Returns the type of the movable. */
    const String&		getMovableType(void) const;

    /** Internal method add Renderable subclass instances to the rendering queue. */
    virtual void		_updateRenderQueue();
	
protected:
	void setVertexDeclaration(
		VertexDeclaration& vertexDeclaration, 
		uint32 textureLayerNumber ) const;
	void setVertexData(
		VertexData& vertexData, 
		uint32 textureLayerNumber, 
		bool memoryVertexBuffer = true ) const;
	CustomRenderable* addRenderable(
		VertexData& vertexData, 
		const std::shared_ptr<Material>& materialPtr);

private:
	int32_t mTileIndex = -1;
	std::vector<VertexData*> mVertexDatas;
	std::vector<Renderable*> mRenderables;

	Ogre::AxisAlignedBox		mBounds;
};

