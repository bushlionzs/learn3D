#pragma once

#include "OgreEntity.h"
#include "OgreSubEntity.h"
#include "OgreSceneNode.h"
#include "OgreIndexData.h"

class WaterSubEntity;
class Waves;
class VertexDeclaration;


class WaterEntity : public Ogre::Entity
{
public:
    WaterEntity(const std::string& name);
    ~WaterEntity();
    virtual VertexData* getVertexData();
    virtual IndexData* getIndexData();
private:
    virtual void update(float delta);

    
private:
    void buildHardBuffer();
private:
    WaterSubEntity* mSubEntity;
    std::unique_ptr<Waves> mWave;
    std::vector<SVertexElement> mVertexs;
    float mTotal = 0.0f;
    float mLast = 0.0f;
    std::unique_ptr<VertexDeclaration> mVertexDeclaration;

    VertexData* mVertexData;
    IndexData* mIndexData;
};



class WaterSubEntity : public Ogre::SubEntity
{
public:
    WaterSubEntity(Ogre::Entity* entity, int32_t indexCount);
    ~WaterSubEntity();

    virtual VertexData* getVertexData();
    virtual IndexData* getIndexData();
    virtual IndexDataView* getIndexView();

    
private:
    IndexDataView mIndexDataView;

    WaterEntity* mWaterEntity;
};