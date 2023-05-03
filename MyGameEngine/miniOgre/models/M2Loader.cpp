#include "OgreHeader.h"
#include "M2Loader.h"
#include "OgreMemoryStream.h"
#include "OgreResourceManager.h"


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

	initStatic(stream.get());

	return mesh;
}

void M2Loader::initStatic(Ogre::DataStream* stream)
{
	initCommon(stream);
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
		std::vector<uint32_t> textures(mHeader.nTextures);
		std::vector<std::string> texnames(mHeader.nTextures);
		for (size_t i = 0; i < mHeader.nTextures; i++) {

			// Error check
			if (i > TEXTURE_MAX - 1) {

				break;
			}


			if (texdef[i].type == TEXTURE_FILENAME)
			{
				const char* name = stream->getStreamData() + texdef[i].nameOfs;
				texnames[i] = name;
			}
			else
			{
				assert(false);
				std::vector<uint32_t> specialTextures(mHeader.nTextures);
				// special texture - only on characters and such...
				textures[i] = 0;
				//while (texdef[i].type < TEXTURE_MAX && specialTextures[texdef[i].type]!=-1) texdef[i].type++;
				//if (texdef[i].type < TEXTURE_MAX)specialTextures[texdef[i].type] = (int)i;
				specialTextures[i] = texdef[i].type;

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

				texnames.push_back(texname);

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
}

bool M2Loader::isAnimated(Ogre::DataStream* stream)
{
	return false;
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
	lodname.append("00.skin");

	std::shared_ptr<DataStream> lodstream = ResourceManager::getSingleton().openResource(lodname);
	ModelView* view = (ModelView*)(lodstream->getStreamData());

	if (view->id[0] != 'S' || view->id[1] != 'K' || view->id[2] != 'I' || view->id[3] != 'N') {
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "load lod-view failed");
	}

	// Indices,  Triangles
	uint16_t* indexLookup = (uint16_t*)(lodstream->getStreamData() + view->ofs_index);
	uint16_t* triangles = (uint16_t*)(lodstream->getStreamData() + view->ofs_triangle);
	nIndices = view->n_triangle;
	if (indices)
	{
		delete indices;
	}
	indices = new uint16_t[nIndices];
	for (size_t i = 0; i < nIndices; i++) {
		indices[i] = indexLookup[triangles[i]];
	}

	// render ops
	ModelGeoset* ops = (ModelGeoset*)(lodstream->getStreamData() + view->ofs_submesh);
	ModelTexUnit* tex = (ModelTexUnit*)(lodstream->getStreamData() + view->ofs_texture_unit);
	ModelRenderFlags* renderFlags = (ModelRenderFlags*)(lodstream->getStreamData() + mHeader.ofsTexFlags);
	uint16* texlookup = (uint16*)(lodstream->getStreamData()+ mHeader.ofsTexLookup);
	uint16* texanimlookup = (uint16*)(lodstream->getStreamData()+ mHeader.ofsTexAnimLookup);
	int16* texunitlookup = (int16*)(lodstream->getStreamData()+ mHeader.ofsTexUnitLookup);

	showGeosets.resize(view->n_submesh);

	for (size_t i = 0; i < view->n_submesh; i++) {
		showGeosets[i] = true;
	}

	for (size_t j = 0; j < view->n_texture_unit; j++) {
		ModelRenderPass pass;

		pass.useTex2 = false;
		pass.useEnvMap = false;
		pass.cull = false;
		pass.trans = false;
		pass.unlit = false;
		pass.noZWrite = false;
		pass.billboard = false;
		pass.texanim = -1; // no texture animation

		//pass.texture2 = 0;
		size_t geoset = tex[j].op;

		pass.geoset = (int)geoset;

		pass.indexStart = ops[geoset].istart;
		pass.indexCount = ops[geoset].icount;
		pass.vertexStart = ops[geoset].vstart;
		pass.vertexEnd = pass.vertexStart + ops[geoset].vcount;

		//TextureID texid = textures[texlookup[tex[j].textureid]];
		//pass.texture = texid;
		pass.tex = texlookup[tex[j].textureid];

		// TODO: figure out these flags properly -_-
		ModelRenderFlags& rf = renderFlags[tex[j].flagsIndex];

		pass.blendmode = rf.blend;
		//if (rf.blend == 0) // Test to disable/hide different blend types
		//	continue;

		pass.color = tex[j].colorIndex;
		pass.opacity = transLookup[tex[j].transid];

		pass.unlit = (rf.flags & RENDERFLAGS_UNLIT) != 0;

		pass.cull = (rf.flags & RENDERFLAGS_TWOSIDED) == 0;

		pass.billboard = (rf.flags & RENDERFLAGS_BILLBOARD) != 0;

		// Use environmental reflection effects?
		pass.useEnvMap = (texunitlookup[tex[j].texunit] == -1) && pass.billboard && rf.blend > 2; //&& rf.blend<5;

		//todo


		pass.noZWrite = (rf.flags & RENDERFLAGS_ZBUFFERED) != 0;

		// ToDo: Work out the correct way to get the true/false of transparency
		pass.trans = (pass.blendmode > 0) && (pass.opacity > 0);	// Transparency - not the correct way to get transparency

		pass.p = ops[geoset].BoundingBox[0].z;

		// Texture flags
		pass.swrap = (texdef[pass.tex].flags & TEXTURE_WRAPX) != 0; // Texture wrap X
		pass.twrap = (texdef[pass.tex].flags & TEXTURE_WRAPY) != 0; // Texture wrap Y

	}

}