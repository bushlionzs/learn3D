#include "OgreHeader.h"
#include "gltf_loader.h"
#include "tiny_gltf.h"
#include "OgreDataStream.h"
#include "OgreMesh.h"
#include "vertex_data.h"
#include "vertex_declaration.h"
#include "OgreMaterialManager.h"
#include "OgreMeshManager.h"
#include "OgreSkeletonManager.h"
#include "OgreSkeleton.h"
#include "keyframe.h"
#include "OgreBone.h"
#include "OgreAnimation.h"
#include "animation_track.h"
#include "gltf_helper.h"
#include "OgreMatrix4.h"

struct GltfVertex
{
    Ogre::Vector3 Pos;
    Ogre::Vector3 Normal;
    Ogre::Vector2 TexC;
};

struct GltfSkinnedVertex
{
    Ogre::Vector3 Pos;
    Ogre::Vector3 Normal;
    Ogre::Vector2 TexC;
    Ogre::Vector3 BoneWeights;
    uint32_t BoneIndices[4];
};

GltfLoader::GltfLoader()
{

}

GltfLoader::~GltfLoader()
{

}

std::shared_ptr<Ogre::Mesh> GltfLoader::loadMeshFromFile(std::shared_ptr<Ogre::DataStream>& stream)
{
	tinygltf::TinyGLTF loader;

	tinygltf::Model model = {};

	std::string err;
	std::string warn;


	uint32_t size = stream->getStreamLength();

	const char* data = stream->getStreamData();

	std::string base_dir = stream->getBaseDir();

	bool res = loader.LoadASCIIFromString(
		&model, 
		&err, 
		&warn, 
		data,
		size,
		base_dir);

    
	
    auto pMesh = new Ogre::Mesh(stream->getName());

	for (auto & mesh :model.meshes)
	{
		const tinygltf::Mesh& tm = mesh;
		int32_t i = 0;
		for (auto& prim : tm.primitives)
		{
            
			const tinygltf::Accessor& accessor = model.accessors[prim.indices];
			
			const tinygltf::BufferView& bView = model.bufferViews[accessor.bufferView];

			const tinygltf::Buffer& buffer = model.buffers[bView.buffer];

            std::map<std::string, int32_t> slotMap;
            enum
            {
                Vertex_Position = 0,
                Vertex_Normal = 1,
                Vertex_TextureCoord = 2,
                Vertex_Weight = 3,
                Vertex_Joint = 4
            };
            slotMap["POSITION"] = Vertex_Position;
            slotMap["NORMAL"] = Vertex_Normal;
            slotMap["TEXCOORD_0"] = Vertex_TextureCoord;
            slotMap["WEIGHTS_0"] = Vertex_Weight;
            slotMap["JOINTS_0"] = Vertex_Joint;

            std::vector<RawData> vertexData(5);
            for (auto& itor : vertexData)
            {
                itor.mData = nullptr;
                itor.mDataSize = 0;
                itor.mDataStride = 0;
            }
            for (auto itor : prim.attributes)
            {
                const tinygltf::Accessor& accessor = model.accessors[itor.second];

                const tinygltf::BufferView& bView = model.bufferViews[accessor.bufferView];

                const tinygltf::Buffer& buffer = model.buffers[bView.buffer];

                

                const char* start = (const char*)buffer.data.data() + bView.byteOffset + accessor.byteOffset;

                if (slotMap.count(itor.first) == 0)
                {
                    assert(false);
                }

                int32_t dataSlot = slotMap[itor.first];


               
                int32_t stride = GetStrideFromFormat(accessor.type, accessor.componentType);
                

                assert(stride != 0);

                vertexData[dataSlot].mDataStride = stride;
                vertexData[dataSlot].mData = start;
                vertexData[dataSlot].mDataSize = accessor.count * stride;
            }

            if (vertexData[Vertex_Position].mDataSize == 0 ||
                vertexData[Vertex_Normal].mDataSize == 0)
            {
                assert(false);
                continue;
            }

            int32_t positionCount =
                vertexData[Vertex_Position].mDataSize / vertexData[Vertex_Position].mDataStride;
            int32_t normalCount = 
                vertexData[Vertex_Normal].mDataSize / vertexData[Vertex_Normal].mDataStride;

            int32_t texCount = positionCount;
            if (vertexData[Vertex_TextureCoord].mDataSize)
            {
                texCount = 
                    vertexData[Vertex_TextureCoord].mDataSize / vertexData[Vertex_TextureCoord].mDataStride;
            }
                
            if (positionCount != normalCount ||
                texCount != positionCount)
            {
                assert(false);
                continue;
            }

            int32_t weightCount = 0;
            if (vertexData[Vertex_Weight].mDataSize)
            {
                weightCount = vertexData[Vertex_Weight].mDataSize / vertexData[Vertex_Weight].mDataStride;
            }

            int32_t jointCount = 0;

            if (vertexData[Vertex_Joint].mDataSize)
            {
                jointCount = vertexData[Vertex_Joint].mDataSize / vertexData[Vertex_Joint].mDataStride;
            }


            if (weightCount && (weightCount != jointCount || weightCount != positionCount))
            {
                assert(false);
                continue;
            }

            auto subMesh = pMesh->addSubMesh(false);
            VertexData* vd = subMesh->getVertexData();

            std::vector<GltfVertex> mVertexBuffer(positionCount);

            float* gltfPosition = (float*)vertexData[Vertex_Position].mData;
            float* gltfNormal   = (float*)vertexData[Vertex_Normal].mData;
            float* gltfTexture  = (float*)vertexData[Vertex_TextureCoord].mData;
            for (int32_t i = 0; i < positionCount; i++)
            {
                mVertexBuffer[i].Pos = Ogre::Vector3(gltfPosition[0], gltfPosition[1], gltfPosition[2]);
                mVertexBuffer[i].Normal = Ogre::Vector3(gltfNormal[0], gltfNormal[1], gltfNormal[2]);
                gltfPosition += 3;
                gltfNormal += 3;
                if (gltfTexture)
                {
                    mVertexBuffer[i].TexC = Ogre::Vector2(gltfTexture[0], gltfTexture[1]);
                    gltfTexture += 2;
                }
            }
            vd->vertexCount = positionCount;
            vd->vertexSlotInfo.emplace_back();
            vd->vertexSlotInfo.back().createBuffer(sizeof(GltfVertex), mVertexBuffer.size());
            vd->vertexSlotInfo.back().writeData((const char*)mVertexBuffer.data(),
                mVertexBuffer.size() * sizeof(GltfVertex));
            vd->vertexDeclaration->addElement(0, 0, 0, VET_FLOAT3, VES_POSITION);
            vd->vertexDeclaration->addElement(0, 0, 12, VET_FLOAT3, VES_NORMAL);
            vd->vertexDeclaration->addElement(0, 0, 24, VET_FLOAT2, VES_TEXTURE_COORDINATES);

            VertexBoneAssignment assignInfo;
            if (weightCount)
            {
                float* gltfWeight = (float*)vertexData[Vertex_Weight].mData;
                //joint stride is 8 or 16
                if (vertexData[Vertex_Joint].mDataStride == 8)
                {
                    uint16_t* gltfJoint = (uint16_t*)vertexData[Vertex_Joint].mData;
                    for (int32_t i = 0; i < weightCount; i++)
                    {
                        assignInfo.vertexIndex = i;
                        assignInfo.boneIndex = gltfJoint[0];
                        assignInfo.weight = gltfWeight[0];
                        vd->mBoneAssignments.push_back(assignInfo);
                        assignInfo.boneIndex = gltfJoint[1];
                        assignInfo.weight = gltfWeight[1];
                        vd->mBoneAssignments.push_back(assignInfo);
                        assignInfo.boneIndex = gltfJoint[2];
                        assignInfo.weight = gltfWeight[2];
                        vd->mBoneAssignments.push_back(assignInfo);
                        assignInfo.boneIndex = gltfJoint[3];
                        assignInfo.weight = gltfWeight[3];
                        vd->mBoneAssignments.push_back(assignInfo);
                        gltfWeight += 4;
                        gltfJoint += 4;
                    }
                }
                else
                {
                    uint32_t* gltfJoint = (uint32_t*)vertexData[Vertex_Joint].mData;
                    for (int32_t i = 0; i < weightCount; i++)
                    {
                        assignInfo.vertexIndex = i;
                        assignInfo.boneIndex = gltfJoint[0];
                        assignInfo.weight = gltfWeight[0];
                        vd->mBoneAssignments.push_back(assignInfo);
                        assignInfo.boneIndex = gltfJoint[1];
                        assignInfo.weight = gltfWeight[1];
                        vd->mBoneAssignments.push_back(assignInfo);
                        assignInfo.boneIndex = gltfJoint[2];
                        assignInfo.weight = gltfWeight[2];
                        vd->mBoneAssignments.push_back(assignInfo);
                        assignInfo.boneIndex = gltfJoint[3];
                        assignInfo.weight = gltfWeight[3];
                        vd->mBoneAssignments.push_back(assignInfo);
                        gltfWeight += 3;
                        gltfJoint += 4;
                    }
                }
            }
            
			std::vector<uint32_t> indices(accessor.count);

			int32_t stride = GetStrideFromFormat(accessor.type, accessor.componentType);
            const char* start = (const char*)buffer.data.data() + bView.byteOffset;
            if (stride == 2)
            {
                
                for (int32_t i = 0; i < accessor.count; i++)
                {
                    uint16_t* data = (uint16_t*)(start + i * stride);
                    indices[i] = *data;
                }
            }
            else
            {
                for (int32_t i = 0; i < accessor.count; i++)
                {
                    uint32_t* data = (uint32_t*)(start + i * stride);
                    indices[i] = *data;
                }
            }
            
            IndexData* indexData = subMesh->getIndexData();
            indexData->mIndexCount = accessor.count;
            indexData->createBuffer(4, indexData->mIndexCount);
            indexData->writeData((const char*)indices.data(), 4 * indexData->mIndexCount);
            
            
            
            const tinygltf::Material& tinyMat = model.materials[prim.material];
            
            int32_t texIndex = tinyMat.pbrMetallicRoughness.baseColorTexture.index;
            const tinygltf::Image& tinyImage = model.images[model.textures[texIndex].source];
            ShaderInfo sinfo;
            sinfo.shaderName = "basic";
            //sinfo.shaderMacros.push_back(std::pair<std::string, std::string>("SKINNED", "1"));
            auto mat = Ogre::MaterialManager::getSingletonPtr()->create(mesh.name);
            mat->addTexture(tinyImage.uri);
            mat->addShader(sinfo);

            subMesh->addIndexs(indices.size(), 0, 0);
            subMesh->setMaterial(mat);
		}
	}

    int32_t k = 0;
    Ogre::Vector3 position;
    for (auto& node : model.nodes)
    {
        if (node.mesh < 0 )
            continue;
        //node.translation
        auto subMesh = pMesh->getSubMesh(node.mesh);

        if (!node.translation.empty())
        {
            position.x = node.translation[0];
            position.y = node.translation[1];
            position.z = node.translation[2];

            subMesh->setPosition(position);
        }
        
    }

    std::vector<std::shared_ptr<Ogre::Skeleton>> skeletonlist;

    loadSkeleton(&model, skeletonlist);

    if (!skeletonlist.empty())
    {
        skeletonlist.front()->setBindingPose();
        pMesh->applySkeleton(skeletonlist.front());
    }
    

	return std::shared_ptr<Ogre::Mesh>(pMesh);
}

bool GltfLoader::loadSkeleton(
    tinygltf::Model* pModel, 
    std::vector<std::shared_ptr<Ogre::Skeleton>>& skeletonlist)
{
    if (pModel->skins.empty())
    {
        return false;
    }

    std::map<uint32_t, std::vector<tinygltf::AnimationChannel*>> nodeToChannelMap;
    for (auto& ani : pModel->animations)
    {
        for (auto& channel : ani.channels)
        {
            nodeToChannelMap[channel.target_node].push_back(&channel);
        }
    }

    for (auto& skin : pModel->skins)
    {
        if (skin.name.empty())
            continue;

        std::shared_ptr<Ogre::Skeleton> skeleton =
            Ogre::SkeletonManager::getSingletonPtr()->create(skin.name);

        skeletonlist.push_back(skeleton);

        loadBone(pModel, &skin, skeleton.get());
        auto ani = skeleton->createAnimation(skin.name, 0.0f);

        int32_t boneCount = skeleton->getNumBones();

        
        loadAnimation(pModel, &skin, nodeToChannelMap, ani);


        for (int32_t i = 0; i < boneCount; i++)
        {
            AnimationTrack* track = ani->getAnimationTrack(i);

            int32_t frameCount = track->getNumKeyFrames();


            auto bone = skeleton->getBone(i);
            for (int32_t j = 0; j < frameCount; j++)
            {
                KeyFrame* frame = track->getNodeKeyFrame(j);

                frame->setRotation(bone->getQuaternion().Inverse() * frame->getRotationQuat());
                
                frame->setTranslate(bone->getPosition() - frame->getTranslation());
                frame->setScale(frame->getScale() / bone->getScale());
            }
        }
        
    }


    return true;
}

bool GltfLoader::loadBone(
    tinygltf::Model* pModel, 
    tinygltf::Skin* skin,
    Ogre::Skeleton* skeleton)
{
    int32_t boneCount = skin->joints.size();


    const auto inverseBindMatricesID = skin->inverseBindMatrices;
    const auto& inverseBindMatricesAccessor = pModel->accessors[inverseBindMatricesID];
    const auto& bufferView = pModel->bufferViews[inverseBindMatricesAccessor.bufferView];
    const auto byteStride = inverseBindMatricesAccessor.ByteStride(bufferView);
    const auto& buffer = pModel->buffers[bufferView.buffer];
    const unsigned char* dataStart = buffer.data.data() + bufferView.byteOffset + inverseBindMatricesAccessor.byteOffset;
    std::array<Real, 4 * 4> floatMatrix;

    std::vector<Ogre::Matrix4> bindMatrices(inverseBindMatricesAccessor.count);
    for (int i = 0; i < inverseBindMatricesAccessor.count; ++i)
    {
        if (inverseBindMatricesAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT)
        {
            memcpy(
                floatMatrix.data(),
                reinterpret_cast<const float*>(dataStart + i * byteStride),
                4 * 4 * sizeof(float));
        }

        Ogre::Matrix4 m(floatMatrix.data());
       
        bindMatrices[i] = m.transpose().inverseAffine();
    }
    
    mBoneMap.clear();

    std::string boneName;
    for (int32_t i = 0; i < boneCount; i++)
    {
        const tinygltf::Node& node = pModel->nodes[skin->joints[i]];
        boneName = node.name;
        if (boneName.empty())
        {
            boneName = "Bone" + std::to_string(i);
        }
        auto bone = skeleton->createBone(boneName, i);
        mBoneMap[skin->joints[i]] = bone;
    }

    for (int32_t i = 0; i < boneCount; i++)
    {
        const tinygltf::Node& node = pModel->nodes[skin->joints[i]];
        for (auto child : node.children)
        {
            auto bone = mBoneMap[child];
            auto parent = mBoneMap[skin->joints[i]];
            assert(parent);
            bone->updateParent(parent);
        }
    }


    Ogre::Vector3 translate(0.0f, 0.0f, 0.0f);
    Ogre::Vector3 scale(1.0f, 1.0f, 1.0f);
    Ogre::Quaternion rotate(0.0f, 0.0f, 0.0f, 1.0f);

    const tinygltf::Node& node = pModel->nodes[skin->joints[0]];

    if (!node.translation.empty())
    {
        translate.x = node.translation[0];
        translate.y = node.translation[1];
        translate.z = node.translation[2];
          
    }

    if (!node.scale.empty())
    {
        scale.x = (Real)node.scale[0];
        scale.y = (Real)node.scale[1];
        scale.z = (Real)node.scale[2];
    }

    if (!node.rotation.empty())
    {
        rotate.x = (Real)node.rotation[0];
        rotate.y = (Real)node.rotation[1];
        rotate.z = (Real)node.rotation[2];
        rotate.w = (Real)node.rotation[3];
    }

    auto rootBone = mBoneMap[skin->joints[0]];

    rootBone->setPosition(translate);
    rootBone->setOrientation(rotate);
    rootBone->setScale(scale);

    std::vector<Ogre::Bone*> kk(boneCount);
    kk[0] = rootBone;
    for (int32_t i = 1; i < boneCount; i++)
    {
        auto bone = mBoneMap[skin->joints[i]];

        kk[i] = bone;
        auto parent = bone->getParent();

        bindMatrices[i].decomposition(translate, scale, rotate);

        Ogre::Vector3 localTranslate = parent->convertWorldToLocalPosition(translate);
        Ogre::Quaternion localRotate = parent->convertWorldToLocalOrientation(rotate);
        Ogre::Vector3 localScale = parent->_getDerivedScale() / scale;

        bone->setPosition(localTranslate);
        bone->setOrientation(localRotate);
        bone->setScale(localScale);

        int id = bone->getBoneId();
        if (id == 7)
        {
            int kk = 0;
        }
    }

    return true;
}

bool GltfLoader::loadAnimation(
    tinygltf::Model* pModel, 
    tinygltf::Skin* skin,
    std::map<uint32_t, std::vector<tinygltf::AnimationChannel*>>& nodeToChannelMap,
    Ogre::Animation* ani)
{
    for(auto joint : skin->joints)
    {
        auto itor = nodeToChannelMap.find(joint);

        assert(itor != nodeToChannelMap.end());

        int32_t boneHandle = mBoneMap[joint]->getBoneId();
  
        AnimationTrack* track = ani->createNodeTrack(boneHandle, nullptr);

        std::vector<tinygltf::AnimationChannel*>& channellist = itor->second;

        const auto translateIt
                = std::find_if(channellist.begin(), channellist.end(), 
                [](const tinygltf::AnimationChannel* c) 
                { return c->target_path == "translation"; });
        const auto rotateIt
                = std::find_if(channellist.begin(), channellist.end(),
                [](const tinygltf::AnimationChannel* c)
                { return c->target_path == "rotation"; });

        const auto scaleIt
                = std::find_if(channellist.begin(), channellist.end(),
                [](const tinygltf::AnimationChannel* c)
                { return c->target_path == "scale"; });

        tinygltf::AnimationChannel* translate = translateIt == channellist.end() ? nullptr : *translateIt;

        tinygltf::AnimationChannel* rotate = rotateIt == channellist.end() ? nullptr : *rotateIt;

        tinygltf::AnimationChannel* scale = scaleIt == channellist.end() ? nullptr : *scaleIt;


        
        //read keyframes
        int32_t frameId = 0;
        Real timepos;
        Ogre::Vector3 v;
        Ogre::Quaternion q;

        int32_t frameTotal = 1;
        int32_t animationId = 0;//todo

        if (joint == 18)
        {
            int kk = 0;
        }
        while (frameId < frameTotal)
        {
            KeyFrame* frame = track->createKeyFrame(0.0f);
            if (translate)
            {
                tinygltf::AnimationSampler& sampler = pModel->animations[animationId].samplers[translate->sampler];
                
                parseTimeposFromSampler(pModel, sampler, frameId, timepos);
                parseVector3dFromSampler(pModel, sampler, frameId, v);

                frame->setTranslate(v);

                frameTotal = pModel->accessors[sampler.input].count;
            }

            if (rotate)
            {
                tinygltf::AnimationSampler& sampler = pModel->animations[animationId].samplers[rotate->sampler];
                parseTimeposFromSampler(pModel, sampler, frameId, timepos);
                parseQuaternionFromSampler(pModel, sampler, frameId, q);
                frame->setRotation(q);

                frameTotal = pModel->accessors[sampler.input].count;
            }

            if (scale)
            {
                tinygltf::AnimationSampler& sampler = pModel->animations[animationId].samplers[scale->sampler];

                parseTimeposFromSampler(pModel, sampler, frameId, timepos);
                parseVector3dFromSampler(pModel, sampler, frameId, v);
                frame->setScale(v);
                frameTotal = pModel->accessors[sampler.input].count;
            }

            frame->setTimePos(timepos);
            frameId++;
        }
    }


    return true;
}

void GltfLoader::parseTimeposFromSampler(
    tinygltf::Model* pModel,
    tinygltf::AnimationSampler& sampler,
    int32_t frameId, float& fValue)
{
    auto& inputAccessor = pModel->accessors[sampler.input];
    auto& bufferView = pModel->bufferViews[inputAccessor.bufferView];
    auto& buffer = pModel->buffers[bufferView.buffer];
    unsigned char* dataStart = buffer.data.data() + bufferView.byteOffset + inputAccessor.byteOffset;
    const size_t byteStride = inputAccessor.ByteStride(bufferView);

    assert(inputAccessor.type == TINYGLTF_TYPE_SCALAR);


    if (inputAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT)
    { 
        fValue = *reinterpret_cast<float*>(dataStart + frameId * byteStride);
    }
    else if (inputAccessor.componentType == TINYGLTF_COMPONENT_TYPE_DOUBLE)
    {
        fValue = static_cast<float>(*reinterpret_cast<double*>(dataStart + frameId * byteStride));
    }
    else
    {
        assert(false);
    }
}

void GltfLoader::parseVector3dFromSampler(
    tinygltf::Model* pModel,
    tinygltf::AnimationSampler& sampler,
    int32_t frameId, Ogre::Vector3& v)
{
    auto& outputAccessor = pModel->accessors[sampler.output];
    auto& bufferView = pModel->bufferViews[outputAccessor.bufferView];
    auto& buffer = pModel->buffers[bufferView.buffer];
    unsigned char* dataStart = buffer.data.data() + bufferView.byteOffset + outputAccessor.byteOffset;
    const size_t byteStride = outputAccessor.ByteStride(bufferView);

    assert(outputAccessor.type == TINYGLTF_TYPE_VEC3); 

    if (outputAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT)
    { 
        Real* f = reinterpret_cast<Real*>(dataStart + frameId * byteStride);
        v.x = f[0];
        v.y = f[1];
        v.z = f[2];
    }
    else if (outputAccessor.componentType == TINYGLTF_COMPONENT_TYPE_DOUBLE) //need double to float conversion
    {
        double* d = reinterpret_cast<double*>(dataStart + frameId * byteStride);
        v.x = (Real)d[0];
        v.y = (Real)d[1];
        v.z = (Real)d[2];
    }
    else
    {
        assert(false);
    }
}

void GltfLoader::parseQuaternionFromSampler(
    tinygltf::Model* pModel,
    tinygltf::AnimationSampler& sampler,
    int32_t frameId, Ogre::Quaternion& v)
{
    auto& outputAccessor = pModel->accessors[sampler.output];
    auto& bufferView = pModel->bufferViews[outputAccessor.bufferView];
    auto& buffer = pModel->buffers[bufferView.buffer];
    unsigned char* dataStart = buffer.data.data() + bufferView.byteOffset + outputAccessor.byteOffset;
    const size_t byteStride = outputAccessor.ByteStride(bufferView);

    assert(outputAccessor.type == TINYGLTF_TYPE_VEC4);

    if (outputAccessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT)
    {
        Real* f = reinterpret_cast<Real*>(dataStart + frameId * byteStride);
        v.x = f[0];
        v.y = f[1];
        v.z = f[2];
        v.w = f[3];
    }
    else if (outputAccessor.componentType == TINYGLTF_COMPONENT_TYPE_DOUBLE) //need double to float conversion
    {
        double* d = reinterpret_cast<double*>(dataStart + frameId * byteStride);
        v.x = (Real)d[0];
        v.y = (Real)d[1];
        v.z = (Real)d[2];
        v.w = (Real)d[3];
    }
    else
    {
        assert(false);
    }
}