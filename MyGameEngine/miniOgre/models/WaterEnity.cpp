#include "OgreHeader.h"
#include "WaterEntity.h"
#include "Waves.h"
#include "vertex_data.h"
#include "index_data.h"
#include "vertex_declaration.h"
#include "OgreHardwareBufferManager.h"
#include "renderSystem.h"
#include "OgreMaterialManager.h"

WaterEntity::WaterEntity(const std::string& name)
:Entity(name, std::shared_ptr<Mesh>())
{
    mWave = std::make_unique<Waves>(128, 128, 1.0f, 0.03f, 4.0f, 0.2f);
    buildHardBuffer();
}

WaterEntity::~WaterEntity()
{

}

VertexData* WaterEntity::getVertexData()
{
    return mVertexData;
}

IndexData* WaterEntity::getIndexData()
{
    return mIndexData;
}

void WaterEntity::update(float delta)
{
    mTotal += delta;

    if (mTotal - mLast >= 0.25f)
    {
        mLast += 0.25f;
        
        int i = Ogre::Math::RangeRandom(4, mWave->RowCount() - 5);
        int j = Ogre::Math::RangeRandom(4, mWave->ColumnCount() - 5);

        float r = Ogre::Math::RangeRandom(0.2f, 0.5f);

        mWave->Disturb(i, j, r);
    }

    mWave->Update(delta);
    int32_t stride = 32;
    int32_t vCount = mWave->VertexCount();
    for (int i = 0; i < vCount; ++i)
    {
        SVertexElement& v = mVertexs[i];
        v.mPosition = mWave->Position(i);

        v.mNormal = mWave->Normal(i);

        // Derive tex-coords from position by 
        // mapping [-w/2,w/2] --> [0,1]
        v.mUV.x = 0.5f + v.mPosition.x / mWave->Width();
        v.mUV.y = 0.5f - v.mPosition.z / mWave->Depth();
    }

    int32_t size = stride * vCount;

    VertexSlotInfo& slotInfo = mVertexData->vertexSlotInfo.back();

    slotInfo.writeData((const char*)mVertexs.data(), size);


    const std::shared_ptr<Material>& mat = mSubEntity->getMaterial();
    mat->update(delta);
}

void WaterEntity::buildHardBuffer()
{
    int32_t vCount = mWave->VertexCount();
    

    mVertexDeclaration = std::make_unique<VertexDeclaration>();

    mVertexDeclaration->addElement(0, 0, 0, VET_FLOAT3, VES_POSITION);
    mVertexDeclaration->addElement(0, 0, 12, VET_FLOAT3, VES_NORMAL);
    mVertexDeclaration->addElement(0, 0, 24, VET_FLOAT3, VES_TANGENT);
    mVertexDeclaration->addElement(0, 0, 36, VET_FLOAT2, VES_TEXTURE_COORDINATES);
    VertexData* vd = new VertexData;

    vd->vertexDeclaration = mVertexDeclaration.get();
    int32_t stride = sizeof(SVertexElement);
    

    mVertexs.resize(vCount);

    for (int i = 0; i < vCount; ++i)
    {
        SVertexElement& v = mVertexs[i];
        v.mPosition = mWave->Position(i);
        v.mNormal = mWave->Normal(i);
        
        // Derive tex-coords from position by 
        // mapping [-w/2,w/2] --> [0,1]
        v.mUV.x = 0.5f + v.mPosition.x / mWave->Width();
        v.mUV.y = 0.5f - v.mPosition.z / mWave->Depth();
    }

    vd->vertexSlotInfo.emplace_back();
    VertexSlotInfo& slotInfo = vd->vertexSlotInfo.back();
    slotInfo.slot = 0;
    vd->vertexCount = mVertexs.size();
    slotInfo.vertexSize = sizeof(SVertexElement);


    slotInfo.hardwareVertexBuffer = HardwareBufferManager::getSingletonPtr()->createVertexBuffer(
        stride,
        vCount,
        5
    );

    mVertexData = vd;

    int32_t size = stride * vCount;
    slotInfo.writeData((const char*)mVertexs.data(), size);

    std::vector<std::uint32_t> indices(3 * mWave->TriangleCount());

    int m = mWave->RowCount();
    int n = mWave->ColumnCount();
    int k = 0;
    for (int i = 0; i < m - 1; ++i)
    {
        for (int j = 0; j < n - 1; ++j)
        {
            indices[k] = i * n + j;
            indices[k + 1] = i * n + j + 1;
            indices[k + 2] = (i + 1) * n + j;

            indices[k + 3] = (i + 1) * n + j;
            indices[k + 4] = i * n + j + 1;
            indices[k + 5] = (i + 1) * n + j + 1;

            k += 6; // next quad
        }
    }

    IndexData* indexdata = new IndexData;
    indexdata->createBuffer(4, indices.size());

    size = 4 * indices.size();
    indexdata->writeData((const char*)indices.data(), size);

    mIndexData = indexdata;


    mSubEntity = new WaterSubEntity(this, indices.size());
    mSubEntityList.push_back(mSubEntity);

    std::shared_ptr<Material> mat = MaterialManager::getSingletonPtr()->create("water");

    mat->scale(5.0f, 5.0f);
    mat->animation(0.1f, 0.01f);

    std::string texname = "water1.dds";
    mat->addTexture(texname);

    ShaderInfo sinfo;

    sinfo.shaderName = "basic";
    mat->addShader(sinfo);
    Ogre::ColourBlendState state;
    state.sourceFactor = Ogre::SBF_SOURCE_ALPHA;
    state.destFactor = Ogre::SBF_DEST_ALPHA;
    state.sourceFactorAlpha = Ogre::SBF_SOURCE_ALPHA;
    state.destFactorAlpha = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
    mat->setBlendState(state);
    this->setMaterial(0, mat);
    mat->load();

    
}

WaterSubEntity::WaterSubEntity(Entity* entity, int32_t indexCount)
    :SubEntity(entity, nullptr)
{
    mIndexDataView.mBaseVertexLocation = 0;
    mIndexDataView.mIndexLocation = 0;
    mIndexDataView.mIndexCount = indexCount;

    mWaterEntity = (WaterEntity*)entity;
}

WaterSubEntity::~WaterSubEntity()
{

}


IndexData* WaterSubEntity::getIndexData()
{
    return mWaterEntity->getIndexData();
}

VertexData* WaterSubEntity::getVertexData()
{
    return mWaterEntity->getVertexData();
}

IndexDataView* WaterSubEntity::getIndexView()
{
    return &mIndexDataView;
}