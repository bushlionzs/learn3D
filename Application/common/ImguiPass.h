#include "pass.h"
#include "InputManager.h"

using ImGuiPassCallback = std::function< void()>;
class ImGuiPass : public PassBase, public InputListener
{
public:
    struct ImGuiFrameData
    {
        filament::backend::Handle<filament::backend::HwBufferObject> cbPassHandle;
        std::unordered_map<Ogre::OgreTexture*, filament::backend::Handle<filament::backend::HwDescriptorSet>> mDescriptorSetMap;
    };

    struct ImGuiUniform
    {
        Ogre::Vector2 scale;
        Ogre::Vector2 translate;
    };
    ImGuiPass(RenderPassInput& input, ImGuiPassCallback cb);
    ~ImGuiPass();

    virtual void execute(RenderSystem* rs);
    virtual void update(float delta);
    virtual void injectMouseMove(int _absx, int _absy, int _absz);
    virtual void injectMousePress(int _absx, int _absy, OIS::MouseButtonID _id);
    virtual void injectMouseRelease(int _absx, int _absy, OIS::MouseButtonID _id);
    virtual void injectKeyPress(KeyCode _key, uint32_t _text);
    virtual void injectKeyRelease(KeyCode _key);
    virtual void injectMouseCursor();
private:
    void init();
    void imguiInit();
    void newFrame();
    void updateBuffers();
    void bindReresource();
    filament::backend::Handle<filament::backend::HwDescriptorSet> getDescriptorSet(Ogre::OgreTexture* source);
private:

    Ogre::Vector2 mMousePosition;
    bool left = false;
    bool right = false;
    bool middle = false;
    uint32_t mWidth;
    uint32_t mHeight;
    Ogre::Matrix4 mProjectionMatrix;
    Ogre::Matrix4 mViewMatrix;
    RenderPassInput mRenderPassInput;

    ImGuiPassCallback mCallback;

    uint32_t mVertexCount = 0;
    uint32_t mIndexCount = 0;

    filament::backend::Handle<filament::backend::HwProgram> mProgramHandle;
    filament::backend::Handle<filament::backend::HwPipeline> mPipelineHandle;

    filament::backend::Handle<filament::backend::HwBufferObject> mVertexBufferHandle;
    filament::backend::Handle<filament::backend::HwBufferObject> mIndexBufferHandle;

    std::vector<ImGuiFrameData> mFrameDataList;

    Ogre::OgreTexture* mFontTexture;

    filament::backend::Handle<filament::backend::HwSampler> mSamplerHandle;
};