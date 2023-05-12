#include "OgreHeader.h"
#include "M2Loader.h"
#include "OgreMemoryStream.h"
#include "OgreResourceManager.h"
#include "OgreMesh.h"
#include "OgreSubMesh.h"
#include "vertex_data.h"
#include "OgreMaterialManager.h"
#include "OgreString.h"
#include "vertex_declaration.h"
#include "myutils.h"
#include "OgreSkeleton.h"
#include "OgreBone.h"
#include "OgreAnimation.h"
#include "keyframe.h"
#include "animation_track.h"
#include "dbcfile.h"
#include "m2Bone.h"
#include "wowUtil.h"
#include "wowParticle.h"


static bool usesAnimation(const M2Bone& b, size_t animIdx) {
	return (b.trans.uses((unsigned int)animIdx) ||
		b.rot.uses((unsigned int)animIdx) ||
		b.scale.uses((unsigned int)animIdx));
}

M2Loader::M2Loader()
{
}

M2Loader::~M2Loader()
{

}

std::shared_ptr<Ogre::Mesh> M2Loader::loadMeshFromFile(std::shared_ptr<Ogre::DataStream>& stream)
{
	mName = stream->getName();
	std::shared_ptr<Ogre::Mesh> mesh;


	uint32_t streamLength = stream->getStreamLength();
	

	stream->read(&mHeader, sizeof(M2Header));

	if (mHeader.id[0] != 'M' &&
		mHeader.id[1] != 'D' &&
		mHeader.id[2] != '2' &&
		mHeader.id[3] != '0')
	{
		return mesh;
	}

	if (mHeader.nameOfs != 304 && mHeader.nameOfs != 320)
	{
		return mesh;
	}

	if (mHeader.version[0] != 4 && 
		mHeader.version[1] != 1 && 
		mHeader.version[2] != 0 && 
		mHeader.version[3] != 0)
	{
	
		return mesh;
	}

	if (streamLength < mHeader.ofsParticleEmitters)
	{
		return mesh;
	}

	animated = isAnimated(stream.get());

	initCommon(stream.get());

	if (animated)
	{
		initAnimated(stream.get());
		mSkeleton->setBindingPose();
		std::shared_ptr<Skeleton> tmp(mSkeleton);
		mMesh->applySkeleton(tmp);
	}

	// particle systems
	if (mHeader.nParticleEmitters) {
		if (mHeader.version[0] >= 0x10) {
			ModelParticleEmitterDefV10* pdefsV10 = (ModelParticleEmitterDefV10*)(
				stream->getStreamData() + mHeader.ofsParticleEmitters);
			ModelParticleEmitterDef* pdefs;
			particleSystems = new WowParticleSystem[mHeader.nParticleEmitters];
			for (size_t i = 0; i < mHeader.nParticleEmitters; i++) {
				pdefs = (ModelParticleEmitterDef*)&pdefsV10[i];
				particleSystems[i].init(stream, *pdefs, globalSequences.data(), this);
			}
		}
		else {
			ModelParticleEmitterDef* pdefs = (ModelParticleEmitterDef*)(
				stream->getStreamData() + mHeader.ofsParticleEmitters);
			particleSystems = new WowParticleSystem[mHeader.nParticleEmitters];
			for (size_t i = 0; i < mHeader.nParticleEmitters; i++) {
				particleSystems[i].init(stream, pdefs[i], globalSequences.data(), this);
			}
		}
	}

	mesh = std::shared_ptr<Ogre::Mesh>(mMesh);
	return mesh;
}

std::string M2Loader::getTexture(uint32_t i)
{
	return texnames[i];
}

Bone* M2Loader::getBone(uint32_t i)
{
	return mSkeleton->getBone(i);
}

void M2Loader::initCommon(Ogre::DataStream* stream)
{
	mOrigVertices = (M2ModelVertex*)(stream->getStreamData() + mHeader.ofsVertices);

	for (size_t i = 0; i < mHeader.nVertices; i++)
	{
		mOrigVertices[i].pos = fixCoordSystem(mOrigVertices[i].pos);
		mOrigVertices[i].normal = fixCoordSystem(mOrigVertices[i].normal);
	}

	// textures
	ModelTextureDef* texdef = (ModelTextureDef*)(stream->getStreamData() + mHeader.ofsTextures);
	if (mHeader.nTextures) {
		texturetypes.resize(mHeader.nTextures);
		texnames.resize(mHeader.nTextures);

		for (size_t i = 0; i < mHeader.nTextures; i++) {

			// Error check
			if (i > TEXTURE_MAX - 1) {

				break;
			}

			texturetypes[i] = texdef[i].type;
			if (texdef[i].type == TEXTURE_FILENAME)
			{
				const char* name = stream->getStreamData() + texdef[i].nameOfs;
				texnames[i] = name;
			}
			else
			{
				assert(false);
				std::vector<uint32_t> specialTextures(mHeader.nTextures);


				std::string texname = "Special_";
				texname += std::to_string(texdef[i].type);

				if (mModelType == MT_NORMAL) {
					if (texdef[i].type == TEXTURE_HAIR)
						texname = "Hair.blp";
					else if (texdef[i].type == TEXTURE_BODY)
						texname = "Body.blp";
					else if (texdef[i].type == TEXTURE_FUR)
						texname = "Fur.blp";
				}

				texnames[i] = texname;

				if (texdef[i].type < TEXTURE_MAX)
				{
					assert(false);
				}


				if (texdef[i].type == TEXTURE_ARMORREFLECT)
				{
					assert(false);
				}
			}
		}
	}

	if (mHeader.nTexAnims > 0)
	{

	}

	if (mHeader.nAttachments)
	{
		int kk = 0;
	}

	if (mHeader.nAttachLookup)
	{
		int kk = 0;
	}

	// init colors
	if (mHeader.nColors)
	{
		int kk = 0;
	}

	//// init transparency
	if (mHeader.nTransparency)
	{
		int kk = 0;
	}

	if (mHeader.nViews)
	{
		setLOD(stream, 0);
	}

	if (mHeader.nGlobalSequences) {
		globalSequences.resize(mHeader.nGlobalSequences);
		memcpy(globalSequences.data(), (stream->getStreamData() + mHeader.ofsGlobalSequences),
			mHeader.nGlobalSequences * sizeof(uint32_t));
	}
}

typedef size_t			TimeT;
typedef std::map<TimeT, int>	Timeline;

static const int KEY_TRANSLATE = 1;
static const int KEY_ROTATE = 2;
static const int KEY_SCALE = 4;

static void updateTimeline(Timeline& timeline, std::vector<TimeT>& times, int keyMask) {
	size_t numTimes = times.size();
	for (size_t n = 0; n < numTimes; n++) {
		TimeT time = times[n];
		Timeline::iterator it = timeline.find(time);
		if (it != timeline.end()) {
			it->second |= keyMask;
		}
		else {
			timeline[time] = keyMask;
		}
	}
}

Ogre::Vector3 M2Loader::getBoneParentTrans(int n) const
{
	const M2Bone& b = bones[n];
	Ogre::Vector3 tr = b.pivot;
	int pid = b.parent;
	if (pid > -1)
		tr -= bones[pid].pivot;
	return tr;
}

void M2Loader::initAnimated(Ogre::DataStream* stream)
{
	mSkeleton = new Skeleton(mName);
	if (mHeader.nAnimations > 0) {
		mAnimations.resize(mHeader.nAnimations);
		std::string tempname;
			
		mAnimNamefiles.resize(mHeader.nAnimations);

		auto prefix = removeSuffix(mName);
		memcpy(mAnimations.data(), stream->getStreamData() + mHeader.ofsAnimations, 
			sizeof(ModelAnimation) * mHeader.nAnimations);
		for (size_t i = 0; i < mHeader.nAnimations; i++)
		{
			tempname = Ogre::StringUtil::format("%s%04d-%02d.ANIM", prefix.c_str(), 
				mAnimations[i].animID, mAnimations[i].subAnimID);
			mAnimNamefiles[i] = tempname;
		}
	}

	if (animBones) {
		bones.resize(mHeader.nBones);
		std::vector<std::shared_ptr<DataStream>> animfiles(mHeader.nAnimations);
		for (uint32_t i = 0; i < mHeader.nAnimations; i++)
		{
			auto anim = ResourceManager::getSingleton().openResource(mAnimNamefiles[i]);
			animfiles[i] = anim;
		}
		ModelBoneDef* mb = (ModelBoneDef*)(stream->getStreamData() + mHeader.ofsBones);
		for (size_t i = 0; i < mHeader.nBones; i++) {
			bones[i].parent = mb[i].parent;
			bones[i].initV3(stream, mb + i, animfiles, globalSequences);
			mSkeleton->createBone(std::to_string(i), i);
		}

		for (size_t i = 0; i < mHeader.nBones; i++) {
			Bone* bone = mSkeleton->getBone(i);
			Bone* boneParent = mSkeleton->getBone(mb[i].parent);
			bone->updateParent(boneParent);
			bone->setBillboard(bones[i].billboard);
			Ogre::Vector3 pos = getBoneParentTrans(i);
			bone->setPosition(pos);
		}

		if (mHeader.nKeyBoneLookup < BONE_MAX)
		{
			memcpy(keyBoneLookup, stream->getStreamData() + mHeader.ofsKeyBoneLookup,
				sizeof(int16) * mHeader.nKeyBoneLookup);
		}
		else
		{
			memcpy(keyBoneLookup, stream->getStreamData() + mHeader.ofsKeyBoneLookup,
				sizeof(int16) * BONE_MAX);
		}

		std::string aniname;
		for (uint32_t animIdx = 0; animIdx < mHeader.nAnimations; animIdx++)
		{
			if (hasAnimation(animIdx))
			{
				ModelAnimation& anim = mAnimations[animIdx];
				try
				{
					AnimDB::Record r = gAnimDB.getByAnimID(anim.animID);
					aniname = r.getString(AnimDB::Name);
					aniname += std::to_string(animIdx);
				}
				catch(...)
				{
					aniname = mName + "_animation" + std::to_string(animIdx);
				}
				
				Ogre::Animation* ogreAni = mSkeleton->createAnimation(aniname, 0);
				
				for (size_t boneIdx = 0; boneIdx < bones.size(); boneIdx++) {
					M2Bone& b = bones[boneIdx];
					if (usesAnimation(b, animIdx)) {
						AnimationTrack* track = ogreAni->createNodeTrack(boneIdx, nullptr);
						Timeline timeline;
						updateTimeline(timeline, b.trans.times[animIdx], KEY_TRANSLATE);
						updateTimeline(timeline, b.rot.times[animIdx], KEY_ROTATE);
						updateTimeline(timeline, b.scale.times[animIdx], KEY_SCALE);
		
						size_t ntrans = 0;
						size_t nrot = 0;
						size_t nscale = 0;
						for (Timeline::iterator it = timeline.begin(); it != timeline.end(); it++) {
							KeyFrame* frame = track->createKeyFrame(it->first / 1000.0f);
							if (it->second & KEY_TRANSLATE) {
								Ogre::Vector3& v = b.trans.data[animIdx][ntrans];
								frame->setTranslate(v);
								ntrans++;
							}
							if (it->second & KEY_ROTATE) {
								Quaternion q;
								q.x = -b.rot.data[animIdx][nrot].x;
								q.y = -b.rot.data[animIdx][nrot].y;
								q.z = -b.rot.data[animIdx][nrot].z;
								q.w = b.rot.data[animIdx][nrot].w;
								frame->setRotation(q);
								nrot++;
							}
							if (it->second & KEY_SCALE) 
							{
								Ogre::Vector3& v = b.scale.data[animIdx][nscale];
								nscale++;
							}
						}

					}
				}
			}
		}	

		//skinned

		VertexData* vd = mMesh->getVertexData();
		vd->vertexCount = mHeader.nVertices;
		vd->mBoneAssignments.reserve(mHeader.nVertices);
		VertexBoneAssignment tmp;
		for (uint32_t i = 0; i < mHeader.nVertices; i++)
		{
			for (uint32_t j = 0; j < 4; j++)
			{
				if (mOrigVertices[i].weights[j] == 0)
					continue;
				tmp.boneIndex = mOrigVertices[i].bones[j];
				tmp.vertexIndex = i;
				tmp.weight = (float)mOrigVertices[i].weights[j] / 255.0f;
				vd->mBoneAssignments.push_back(tmp);
			}
		}
		vd->buildHardBuffer();
	}
}

bool M2Loader::isAnimated(Ogre::DataStream* stream)
{
	ModelBoneDef* bo = (ModelBoneDef*)(stream->getStreamData() + mHeader.ofsBones);

	animGeometry = false;
	animBones = false;
	ind = false;

	M2ModelVertex* verts = (M2ModelVertex*)(stream->getStreamData() + mHeader.ofsVertices);
	for (size_t i = 0; i < mHeader.nVertices && !animGeometry; i++) {
		for (size_t b = 0; b < 4; b++) {
			if (verts[i].weights[b] > 0) {
				ModelBoneDef& bb = bo[verts[i].bones[b]];
				if (bb.translation.type || bb.rotation.type || bb.scaling.type || (bb.flags & MODELBONE_BILLBOARD)) {
					if (bb.flags & MODELBONE_BILLBOARD) {
						// if we have billboarding, the model will need per-instance animation
						ind = true;
					}
					animGeometry = true;
					break;
				}
			}
		}
	}

	if (animGeometry)
		animBones = true;
	else {
		for (size_t i = 0; i < mHeader.nBones; i++) {
			ModelBoneDef& bb = bo[i];
			if (bb.translation.type || bb.rotation.type || bb.scaling.type) {
				animBones = true;
				animGeometry = true;
				break;
			}
		}
	}

	animTextures = mHeader.nTexAnims > 0;

	bool animMisc = mHeader.nCameras > 0 || // why waste time, pretty much all models with cameras need animation
		mHeader.nLights > 0 || // same here
		mHeader.nParticleEmitters > 0 ||
		mHeader.nRibbonEmitters > 0;

	if (animMisc)
		animBones = true;

	// animated colors
	if (mHeader.nColors) {
		ModelColorDef* cols = (ModelColorDef*)(stream->getStreamData() + mHeader.ofsColors);
		for (size_t i = 0; i < mHeader.nColors; i++) {
			if (cols[i].color.type != 0 || cols[i].opacity.type != 0) {
				animMisc = true;
				break;
			}
		}
	}

	// animated opacity
	if (mHeader.nTransparency && !animMisc) {
		ModelTransDef* trs = (ModelTransDef*)(stream->getStreamData() + mHeader.ofsTransparency);
		for (size_t i = 0; i < mHeader.nTransparency; i++) {
			if (trs[i].trans.type != 0) {
				animMisc = true;
				break;
			}
		}
	}

	// guess not...
	return animGeometry || animTextures || animMisc;
}

void M2Loader::setLOD(Ogre::DataStream* stream, int index)
{
	// Texture definitions
	ModelTextureDef* texdef = (ModelTextureDef*)(stream->getStreamData() + mHeader.ofsTextures);

	// Transparency
	int16* transLookup = (int16*)(stream->getStreamData() + mHeader.ofsTransparencyLookup);

	// I thought the view controlled the Level of detail,  but that doesn't seem to be the case.
	// Seems to only control the render order.  Which makes this function useless and not needed :(

	// remove suffix .M2
	std::string lodname = mName.substr(0, mName.length() - 3);
	lodname.append("00.SKIN");

	std::shared_ptr<DataStream> lodstream = ResourceManager::getSingleton().openResource(lodname);
	ModelView* view = (ModelView*)(lodstream->getStreamData());

	if (view->id[0] != 'S' || view->id[1] != 'K' || view->id[2] != 'I' || view->id[3] != 'N') {
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "load lod-view failed");
	}

	// Indices,  Triangles
	uint16_t* indexLookup = (uint16_t*)(lodstream->getStreamData() + view->ofs_index);
	uint16_t* triangles = (uint16_t*)(lodstream->getStreamData() + view->ofs_triangle);
	nIndices = view->n_triangle;
	indices.resize(nIndices);
	for (size_t i = 0; i < nIndices; i++) {
		indices[i] = indexLookup[triangles[i]];
	}

	auto indice_data = indices.data();
	// render ops
	ModelGeoset* ops = (ModelGeoset*)(lodstream->getStreamData() + view->ofs_submesh);
	ModelTexUnit* texunit = (ModelTexUnit*)(lodstream->getStreamData() + view->ofs_texture_unit);
	ModelRenderFlags* renderFlags = (ModelRenderFlags*)(stream->getStreamData() + mHeader.ofsTexFlags);
	uint16* texlookup = (uint16*)(stream->getStreamData()+ mHeader.ofsTexLookup);
	uint16* texanimlookup = (uint16*)(stream->getStreamData()+ mHeader.ofsTexAnimLookup);
	int16* texunitlookup = (int16*)(stream->getStreamData()+ mHeader.ofsTexUnitLookup);

	showGeosets.resize(view->n_submesh);

	for (size_t i = 0; i < view->n_submesh; i++) {
		showGeosets[i] = true;
	}
	ModelRenderPass pass;

	mMesh = new Mesh(mName);
	AxisAlignedBox bounds;
	bounds.setInfinite();
	mMesh->_setBounds(bounds);
	Ogre::ColourBlendState blendState;
	for (size_t j = 0; j < view->n_texture_unit; j++) {
		
		size_t geoset = texunit[j].op;

		pass.indexStart = ops[geoset].istart;
		pass.indexCount = ops[geoset].icount;
		
		pass.tex = texlookup[texunit[j].textureid];

		ModelRenderFlags& rf = renderFlags[texunit[j].flagsIndex];
		pass.blendmode = rf.blend;
		pass.noZWrite = (rf.flags & RENDERFLAGS_ZBUFFERED) != 0;
		const std::string& texname = texnames[pass.tex];

		if (texname == "CREATURE\\AKAMA\\AKAMABRACERSKIRTBELT.BLP")
		{
			//continue;
		}
		std::string name = Ogre::StringUtil::format("%s%d", mName.c_str(), j);
		std::shared_ptr<Material> mat = MaterialManager::getSingleton().create(name);
		
		mat->addTexture(texname);
		ShaderInfo info;
		info.shaderName = "basic";
		if(animated)
			info.shaderMacros.emplace_back("SKINNED", "1");
		mat->addShader(info);
		mat->setCullMode(CULL_NONE);
		if (pass.noZWrite)
		{
			mat->setWriteDepth(false);
		}

		if (pass.blendmode == BM_OPAQUE)
		{
			int kk = 0;
		}
		else if (pass.blendmode == BM_TRANSPARENT)
		{
			blendState.sourceFactor = Ogre::SBF_SOURCE_ALPHA;
			blendState.destFactor = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
			blendState.sourceFactorAlpha = Ogre::SBF_SOURCE_ALPHA;
			blendState.destFactorAlpha = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
			mat->setBlendState(blendState);
		}
		else if (pass.blendmode == BM_ADDITIVE_ALPHA)
		{
			blendState.sourceFactor = Ogre::SBF_SOURCE_ALPHA;
			blendState.destFactor = Ogre::SBF_ONE;
			blendState.sourceFactorAlpha = Ogre::SBF_ONE;
			blendState.destFactorAlpha = Ogre::SBF_ZERO;
			mat->setBlendState(blendState);
		}
		else
		{
			blendState.sourceFactor = Ogre::SBF_DEST_COLOUR;
			blendState.destFactor = Ogre::SBF_SOURCE_COLOUR;
			blendState.sourceFactorAlpha = SBF_DEST_ALPHA;
			blendState.destFactorAlpha = SBF_SOURCE_ALPHA;
			mat->setBlendState(blendState);
		}

		SubMesh* sub = mMesh->addSubMesh(true, true);
		sub->setMaterial(mat);
		sub->addIndexs(pass.indexCount, pass.indexStart, 0);
	}

	VertexData* vd = mMesh->getVertexData();



	vd->vertexDeclaration->addElement(0, 0, 0, VET_FLOAT3, VES_POSITION);
	vd->vertexDeclaration->addElement(0, 0, 20, VET_FLOAT3, VES_NORMAL);
	vd->vertexDeclaration->addElement(0, 0, 32, VET_FLOAT2, VES_TEXTURE_COORDINATES);

	vd->vertexSlotInfo.emplace_back();
	auto& back = vd->vertexSlotInfo.back();
	auto vertexSize = sizeof(M2ModelVertex);
	back.createBuffer(vertexSize, mHeader.nVertices);
	back.writeData((const char*)mOrigVertices, vertexSize * mHeader.nVertices);

	IndexData* indexdata = mMesh->getIndexData();

	indexdata->createBuffer(2, nIndices);
	indexdata->writeData((const char*)indices.data(), 2 * nIndices);
}

bool M2Loader::hasAnimation(size_t animIdx) const
{
	for (size_t n = 0; n < bones.size(); n++) {
		const M2Bone& b = bones.at(n);
		if (usesAnimation(b, animIdx))
			return true;
	}
	return false;
}

