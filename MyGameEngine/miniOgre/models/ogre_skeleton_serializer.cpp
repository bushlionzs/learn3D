#include "OgreHeader.h"
#include "ogre_skeleton_serializer.h"
#include "OgreDataStream.h"
#include "OgreBone.h"
#include "OgreSkeleton.h"
#include "OgreSkeletonFileFormat.h"
#include "keyframe.h"
#include "animation_track.h"
#include "OgreAnimation.h"

OgreSkeletonSerializerImpl::OgreSkeletonSerializerImpl()
{

}

OgreSkeletonSerializerImpl::~OgreSkeletonSerializerImpl()
{

}

void OgreSkeletonSerializerImpl::importSkeleton(
	std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Skeleton* skeleton)
{
    // Check header
    unsigned short headerID;
    readShorts(stream, &headerID, 1);
    if (headerID != HEADER_STREAM_ID_EXT)
    {
        OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "File header not found",
            "SkeletonSerializer::importSkeleton");
    }

    // Read version
    String ver = readString(stream);
    if ((ver != "[Serializer_v1.10]") &&
        (ver != "[Serializer_v1.80]"))
    {
        OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
            "Invalid file: version incompatible, file reports " + String(ver),
            "SkeletonSerializer::importSkeleton");
    }
    mVersion = ver;


    pushInnerChunk(stream);
    unsigned short streamID = readChunk(stream);

    while (!stream->eof())
    {
        switch (streamID)
        {
        case Ogre::SKELETON_BLENDMODE:
        {
            // Optional blend mode
            uint16 blendMode;
            readShorts(stream, &blendMode, 1);
            //skeleton->setBlendMode(static_cast<SkeletonAnimationBlendMode>(blendMode));
            break;
        }
        case Ogre::SKELETON_BONE:
            readBone(stream, skeleton);
            break;
        case Ogre::SKELETON_BONE_PARENT:
            readBoneParent(stream, skeleton);
            break;
        case Ogre::SKELETON_ANIMATION:
            readAnimation(stream, skeleton);
            break;
        case Ogre::SKELETON_ANIMATION_LINK:
            readSkeletonAnimationLink(stream, skeleton);
            break;
        default:
            break;
        }

        streamID = readChunk(stream);
    }
    // Assume bones are stored in the binding pose
    skeleton->setBindingPose();
    popInnerChunk(stream);
}

void OgreSkeletonSerializerImpl::readBone(
    std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Skeleton* pSkel)
{
    // char* name
    String name = readString(stream);
    // unsigned short handle            : handle of the bone, should be contiguous & start at 0
    unsigned short handle;
    readShorts(stream, &handle, 1);

    // Create new bone
    Ogre::Bone* pBone = pSkel->createBone(name, handle);

    // Vector3 position                 : position of this bone relative to parent 
    Ogre::Vector3 pos;
    readObject(stream, pos);
    pBone->setPosition(pos);
    // Quaternion orientation           : orientation of this bone relative to parent 
    Ogre::Quaternion q;
    readObject(stream, q);
    pBone->setOrientation(q);

#if OGRE_SERIALIZER_VALIDATE_CHUNKSIZE
    // Hack to fix chunk size validation:
    mChunkSizeStack.back() += calcStringSize(name);
#endif
    // TODO: don't depend on mCurrentstreamLen in next skeleton format!
    // Currently we use wrong chunk sizes, but we can't fix it, because we depend on mCurrentstreamLen
    // Do we have scale?
    if (mCurrentstreamLen > calcBoneSizeWithoutScale(pSkel, pBone))
    {
        Ogre::Vector3 scale;
        readObject(stream, scale);
        pBone->setScale(scale);
    }
}

void OgreSkeletonSerializerImpl::readBoneParent(
    std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Skeleton* pSkel)
{
    // All bones have been created by this point
    Ogre::Bone* child, * parent;
    unsigned short childHandle, parentHandle;

    // unsigned short handle             : child bone
    readShorts(stream, &childHandle, 1);
    // unsigned short parentHandle   : parent bone
    readShorts(stream, &parentHandle, 1);

    // Find bones
    parent = pSkel->getBone(parentHandle);
    child = pSkel->getBone(childHandle);

    // attach
    child->updateParent(parent);

}
//---------------------------------------------------------------------
void OgreSkeletonSerializerImpl::readAnimation(
    std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Skeleton* pSkel)
{
    // char* name                       : Name of the animation
    String name;
    name = readString(stream);
    // float length                      : Length of the animation in seconds
    float len;
    readFloats(stream, &len, 1);

    Ogre::Animation* pAnim = pSkel->createAnimation(name, len);
    // Read all tracks
    if (!stream->eof())
    {
        pushInnerChunk(stream);
        unsigned short streamID = readChunk(stream);
        // Optional base info is possible
        if (streamID == Ogre::SKELETON_ANIMATION_BASEINFO)
        {
            // char baseAnimationName
            String baseAnimName = readString(stream);
            // float baseKeyFrameTime
            float baseKeyTime;
            readFloats(stream, &baseKeyTime, 1);

            pAnim->setUseBaseKeyFrame(true, baseKeyTime, baseAnimName);

            if (!stream->eof())
            {
                // Get next stream
                streamID = readChunk(stream);
            }
        }

        while (streamID == Ogre::SKELETON_ANIMATION_TRACK && !stream->eof())
        {
            readAnimationTrack(stream, pAnim, pSkel);

            if (!stream->eof())
            {
                // Get next stream
                streamID = readChunk(stream);
            }
        }
        if (!stream->eof())
        {
            // Backpedal back to start of this stream if we've found a non-track
            backpedalChunkHeader(stream);
        }
        popInnerChunk(stream);
    }
}
//---------------------------------------------------------------------
void OgreSkeletonSerializerImpl::readAnimationTrack(
    std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Animation* anim,
    Ogre::Skeleton* pSkel)
{
    // unsigned short boneIndex     : Index of bone to apply to
    uint16_t boneHandle;
    readShorts(stream, &boneHandle, 1);

    // Find bone
    Ogre::Bone* targetBone = pSkel->getBone(boneHandle);

    // Create track
    AnimationTrack* pTrack = anim->createNodeTrack(boneHandle, targetBone);

    // Keep looking for nested keyframes
    if (!stream->eof())
    {
        pushInnerChunk(stream);
        unsigned short streamID = readChunk(stream);
        while (streamID == Ogre::SKELETON_ANIMATION_TRACK_KEYFRAME && !stream->eof())
        {
            readKeyFrame(stream, pTrack, pSkel);

            if (!stream->eof())
            {
                // Get next stream
                streamID = readChunk(stream);
            }
        }
        if (!stream->eof())
        {
            // Backpedal back to start of this stream if we've found a non-keyframe
            backpedalChunkHeader(stream);
        }
        popInnerChunk(stream);
    }


}
//---------------------------------------------------------------------
void OgreSkeletonSerializerImpl::readKeyFrame(
    std::shared_ptr<Ogre::DataStream>& stream,
    AnimationTrack* track,
    Ogre::Skeleton* pSkel)
{
    // float time                    : The time position (seconds)
    float time;
    readFloats(stream, &time, 1);

    KeyFrame* kf = track->createKeyFrame(time);

    // Quaternion rotate            : Rotation to apply at this keyframe
    Ogre::Quaternion rot;
    readObject(stream, rot);
    kf->setRotation(rot);
    // Vector3 translate            : Translation to apply at this keyframe
    Ogre::Vector3 trans;
    readObject(stream, trans);
    kf->setTranslate(trans);
    // Do we have scale?
    if (mCurrentstreamLen > calcKeyFrameSizeWithoutScale(pSkel, kf))
    {
        Ogre::Vector3 scale;
        readObject(stream, scale);
        kf->setScale(scale);
    }
}

void OgreSkeletonSerializerImpl::readSkeletonAnimationLink(
    std::shared_ptr<Ogre::DataStream>& stream,
    Ogre::Skeleton* pSkel)
{
    // char* skeletonName
    String skelName = readString(stream);
    // float scale
    float scale;
    readFloats(stream, &scale, 1);

    pSkel->addLinkedSkeletonAnimationSource(skelName, scale);

}

size_t OgreSkeletonSerializerImpl::calcBoneSize(
    const Ogre::Skeleton* pSkel, const Ogre::Bone* pBone)
{
    size_t size = calcBoneSizeWithoutScale(pSkel, pBone);

    // scale

    
    if(pBone->getScale() != Ogre::Vector3::UNIT_SCALE)
    {
        size += sizeof(float) * 3;
    }

    return size;
}

size_t OgreSkeletonSerializerImpl::calcBoneSizeWithoutScale(
    const Ogre::Skeleton* pSkel, const Ogre::Bone* pBone)
{
    size_t size = SSTREAM_OVERHEAD_SIZE;

    // TODO: Add this for next skeleton format!
    // Currently it is broken, because to determine that we have scale, it will compare chunk size.
    //size += calcStringSize(pBone->getName());

    // handle
    size += sizeof(unsigned short);

    // position
    size += sizeof(float) * 3;

    // orientation
    size += sizeof(float) * 4;

    return size;
}

size_t OgreSkeletonSerializerImpl::calcBoneParentSize(const Ogre::Skeleton* pSkel)
{
    size_t size = SSTREAM_OVERHEAD_SIZE;

    // handle
    size += sizeof(unsigned short);

    // parent handle
    size += sizeof(unsigned short);

    return size;
}

size_t OgreSkeletonSerializerImpl::calcAnimationSize(
    const Ogre::Skeleton* pSkel,
    const Ogre::Animation* pAnim,
    SkeletonVersion ver)
{
    size_t size = SSTREAM_OVERHEAD_SIZE;

    // Name, including terminator
    size += calcStringSize(pAnim->getName());
    // length
    size += sizeof(float);

    if ((int)ver > (int)SKELETON_VERSION_1_0)
    {
        if (pAnim->getUseBaseKeyFrame())
        {
            size += SSTREAM_OVERHEAD_SIZE;
            // char* baseAnimationName (including terminator)
            size += calcStringSize(pAnim->getBaseKeyFrameAnimationName());
            // float baseKeyFrameTime
            size += sizeof(float);
        }
    }

    const Ogre::Animation::NodeTrackList& trackList = pAnim->getNodeTrackList();
    // Nested animation tracks
    for (const auto& it : trackList)
    {
        size += calcAnimationTrackSize(pSkel, it.second);
    }

    return size;
}

size_t OgreSkeletonSerializerImpl::calcAnimationTrackSize(const Ogre::Skeleton* pSkel, const AnimationTrack* pTrack)
{
    size_t size = SSTREAM_OVERHEAD_SIZE;

    // unsigned short boneIndex     : Index of bone to apply to
    size += sizeof(unsigned short);

    // Nested keyframes
    for (unsigned short i = 0; i < pTrack->getNumKeyFrames(); ++i)
    {
        size += calcKeyFrameSize(pSkel, pTrack->getNodeKeyFrame(i));
    }

    return size;
}
size_t OgreSkeletonSerializerImpl::calcKeyFrameSize(const Ogre::Skeleton* pSkel, const KeyFrame* pKey)
{
    size_t size = calcKeyFrameSizeWithoutScale(pSkel, pKey);

    // Vector3 scale                : Scale to apply at this keyframe
    if (pKey->getScale() != Ogre::Vector3::UNIT_SCALE)
    {
        size += sizeof(float) * 3;
    }

    return size;
}
size_t OgreSkeletonSerializerImpl::calcKeyFrameSizeWithoutScale(const Ogre::Skeleton* pSkel, const KeyFrame* pKey)
{
    size_t size = SSTREAM_OVERHEAD_SIZE;

    // float time                    : The time position (seconds)
    size += sizeof(float);
    // Quaternion rotate            : Rotation to apply at this keyframe
    size += sizeof(float) * 4;
    // Vector3 translate            : Translation to apply at this keyframe
    size += sizeof(float) * 3;

    return size;
}
size_t OgreSkeletonSerializerImpl::calcSkeletonAnimationLinkSize(const Ogre::Skeleton* pSkel,
    const LinkedSkeletonAnimationSource& link)
{
    size_t size = SSTREAM_OVERHEAD_SIZE;

    // char* skeletonName
    //size += link.skeletonName.length() + 1;
    // float scale
    size += sizeof(float);

    return size;
}