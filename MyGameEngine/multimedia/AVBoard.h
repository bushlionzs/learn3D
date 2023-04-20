#pragma once


#include <OgreSceneManager.h>
#include <OgreVector3.h>
#include <OgreFrameListener.h>
#include "AVPlayer.h"



class AVBoard : public IAVPlayCallback
              , public Ogre::FrameListener
{
public:
    AVBoard();
    ~AVBoard();

    void setupAVBoard(
        const Ogre::String& name, 
        const Ogre::String& videoName);
    void play(const Ogre::String& videoName);
private:
    void make_board_object(int w, int h);

private:
    Ogre::SceneManager* mSceneMgr = nullptr;
    std::string         mMatName;
    std::string   mVideoName;
    Ogre::TexturePtr    mAVTexture;
    Ogre::MaterialPtr   mAVMaterial;

    uint32_t mWidth = 0;
    uint32_t mHeight = 0;

private:
    std::shared_ptr<CAVPlayer> mAVPlayer;
    CAVFrameQueue   mAVFrameQueue;

    virtual void    OnCacheBegin() override {};
    virtual void    OnCacheEnd() override {};
    virtual void    OnPlayerStateChanged(int state) override {};
    virtual void    OnVideoFrame(AVFrame& frame) override;

private:
    virtual bool    frameStarted(const Ogre::FrameEvent& evt) override;
};


