#pragma once

#include "OgreSingleton.h"

namespace Orphigine
{
    class Actor;
};
class Terrain;

enum GAME_AXIS_TYPE
{
    GAT_SCENE,				/* 游戏场景坐标（米） */
    GAT_GAME,				/* 游戏坐标（米） */
    GAT_ENGINE,				/* 引擎渲染系统坐标（厘米） */
    GAT_SCREEN,				/* 屏幕像素坐标 */
};

class EngineManager : public Ogre::Singleton<EngineManager>
{
public:
    EngineManager();
    ~EngineManager();

    bool initialise();

    Ogre::Vector3 getMyPosition();
    void setMyPosition(Ogre::Vector3& position);

    Ogre::SceneManager* getSceneManager();

    Ogre::SceneNode* getBaseSceneNode();

    Ogre::Camera* getMainCamera();
    Ogre::Viewport* getMainViewPort();


    void setViewPort(Ogre::Viewport* vp);

    Terrain* getTerrain();
    void setTerrain(Terrain* pTerrain);

    void setCameraPosition(Ogre::Vector3& eyePos);

    bool getTerrainIntersects(const Ogre::Ray& ray, 
        Ogre::Vector3& position, 
        Ogre::Vector3* normal = 0, 
        bool allowOutside = false) const;
    bool getTerrainIntersects(Real winx, Real winy, 
        Ogre::Vector3& position, 
        Ogre::Vector3* normal = 0, 
        bool allowOutside = false) const;
    Orphigine::Actor* getRegisterObject(Ogre::String& ObjName);
    bool registerObject(const Ogre::String& ObjName, Orphigine::Actor* pObj);
    void unregisterObject(const Ogre::String& ObjName);

    bool positionAxisTrans(
        GAME_AXIS_TYPE typeSource,
        const Ogre::Vector3& fvSource,
        GAME_AXIS_TYPE	typeTar,
        Ogre::Vector3& fvTarget,
        bool bTerrainHeight = true);
private:
    bool axisCheckValid(GAME_AXIS_TYPE typeSource, const Ogre::Vector3& fvAxis);
private:
    Ogre::Vector3 mPosition;
    Ogre::SceneManager* mSceneManager;
    Ogre::Camera* mMainCamera;
    Ogre::Viewport* mMainViewport = nullptr;
    Terrain* mTerrain;
    std::map<String, Orphigine::Actor*> mObjectMap;
};