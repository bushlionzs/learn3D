#include "OgreHeader.h"
#include "AVBoard.h"
#include "OgreRoot.h"
#include "OgreTextureManager.h"
#include "OgreMaterialManager.h"
#include "OgreSceneNode.h"
#include "OgreMeshManager.h"
#include "OgreEntity.h"
#include "OgreResourceManager.h"
#include "OgreTextureUnit.h"

using namespace Ogre;


AVBoard::AVBoard() : mAVFrameQueue(4)
{

}

AVBoard::~AVBoard()
{

}

void AVBoard::setupAVBoard(
    const Ogre::String& matName,
    const Ogre::String& videoName)
{
    mMatName = matName;
    mVideoName = videoName;
    CAVPlayer::Config config;
    config.volume = 1.0;
    mAVPlayer = CAVPlayer::Create();

    auto res = ResourceManager::getSingleton().getResource(videoName);
    mAVPlayer->Play(res->_fullname.c_str(), this, config);

    Root::getSingleton().addFrameListener(this);
}

void AVBoard::play(const Ogre::String& url)
{
    if (mAVPlayer)
    {
        mAVPlayer->Stop(true);
        CAVPlayer::Config config;
        config.volume = 1.0;
        mAVPlayer->Play(url.c_str(), this, config);
    }
}

void AVBoard::make_board_object(int w, int h)
{
    if(!mAVTexture)
    {
        mAVMaterial = Ogre::MaterialManager::getSingleton().getByName(mMatName);
        TextureProperty texProperty;
        texProperty._width = w;
        texProperty._height = h;
        texProperty._tex_format = PF_A8R8G8B8;
        texProperty._tex_usage = TU_DYNAMIC_WRITE_ONLY;
        mAVTexture = TextureManager::getSingleton().createManual(mMatName, texProperty);
        mAVMaterial->addTexture(mAVTexture);
    }

    uint32 tw = mAVTexture->getWidth();
    uint32 th = mAVTexture->getHeight();
    if( w != tw || h != th)
    {
        mAVTexture->freeInternalResources();
        mAVTexture->setWidth(w);
        mAVTexture->setHeight(h);
        mAVTexture->createInternalResources();
    }
}

void AVBoard::OnVideoFrame(AVFrame& frame)
{
    mAVFrameQueue.PushBack(frame, false);
}

bool AVBoard::frameStarted(const Ogre::FrameEvent& evt)
{
    AVFrame frame;
    if (mAVFrameQueue.PopFront(frame, false) > 0)
    {
        make_board_object(frame.width, frame.height);

        const auto& buffer = mAVTexture->getBuffer();
        buffer->writeData(0, buffer->getSizeInBytes(), frame.data[0]);
        buffer->uploadData();
        UnrefFrm(&frame);
    }

    return true;
}


