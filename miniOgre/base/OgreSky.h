#pragma once
namespace Ogre {


    class  SkyRenderer
    {
    public:
        enum BoxPlane
        {
            BP_FRONT = 0,
            BP_BACK = 1,
            BP_LEFT = 2,
            BP_RIGHT = 3,
            BP_UP = 4,
            BP_DOWN = 5
        };
    protected:
        SceneManager* mSceneManager;
        void nodeDestroyed(const Node*);
    public:
        SkyRenderer(SceneManager* owner);

        SceneNode* mSceneNode;
        bool mEnabled;

        void setEnabled(bool enable);
        void postFindVisibleObjects(SceneManager* source, Viewport* vp);
    };

    struct SkyBoxGenParameters
    {
        Real skyBoxDistance;
    };

    class  SkyBoxRenderer : public SkyRenderer
    {
        Quaternion mSkyBoxOrientation;
    public:
        SkyBoxRenderer(SceneManager* owner);
        SkyBoxGenParameters mSkyBoxGenParameters;
        void setSkyBox(bool enable, const String& materialName, Real distance,
            uint8 renderQueue, const Quaternion& orientation,
            const String& groupName);
    };
}