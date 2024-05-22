#include "OgreHeader.h"
#include "WaterEntity.h"
#include "Waves.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
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

    mVertexData->writeBindBufferData(0, (const char*)mVertexs.data(), size);


    const std::shared_ptr<Material>& mat = mSubEntity->getMaterial();
    mat->update(delta);
}

void WaterEntity::buildHardBuffer()
{
    int32_t vCount = mWave->VertexCount();
    
    VertexData* vd = new VertexData;

    vd->addElement(0, 0, 0, VET_FLOAT3, VES_POSITION);
    vd->addElement(0, 0, 12, VET_FLOAT3, VES_NORMAL);
    vd->addElement(0, 0, 24, VET_FLOAT3, VES_TANGENT);
    vd->addElement(0, 0, 36, VET_FLOAT2, VES_TEXTURE_COORDINATES);
    
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


    vd->addBindBuffer(0, sizeof(SVertexElement), mVertexs.size());

    int32_t size = stride * vCount;

    vd->writeBindBufferData(0, (const char*)mVertexs.data(), size);

    mVertexData = vd;


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
    mat->load(nullptr);

    
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