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

	mesh = std::shared_ptr<Ogre::Mesh>(pMesh);
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

	// render ops
	ModelGeoset* ops = (ModelGeoset*)(lodstream->getStreamData() + view->ofs_submesh);
	ModelTexUnit* texunit = (ModelTexUnit*)(lodstream->getStreamData() + view->ofs_texture_unit);
	ModelRenderFlags* renderFlags = (ModelRenderFlags*)(lodstream->getStreamData() + mHeader.ofsTexFlags);
	uint16* texlookup = (uint16*)(lodstream->getStreamData()+ mHeader.ofsTexLookup);
	uint16* texanimlookup = (uint16*)(lodstream->getStreamData()+ mHeader.ofsTexAnimLookup);
	int16* texunitlookup = (int16*)(lodstream->getStreamData()+ mHeader.ofsTexUnitLookup);

	showGeosets.resize(view->n_submesh);

	for (size_t i = 0; i < view->n_submesh; i++) {
		showGeosets[i] = true;
	}
	ModelRenderPass pass;

	pMesh = new Mesh(mName);
	AxisAlignedBox bounds;
	bounds.setInfinite();
	pMesh->_setBounds(bounds);
	VertexData* vd = pMesh->getVertexData();

	vd->vertexDeclaration->addElement(0, 0, 0, VET_FLOAT3, VES_POSITION);
	vd->vertexDeclaration->addElement(0, 0, 20, VET_FLOAT3, VES_NORMAL);
	vd->vertexDeclaration->addElement(0, 0, 32, VET_FLOAT2, VES_TEXTURE_COORDINATES);

	vd->vertexSlotInfo.emplace_back();
	auto& back = vd->vertexSlotInfo.back();
	auto vertexSize = sizeof(M2ModelVertex);
	back.createBuffer(vertexSize, mHeader.nVertices);
	back.writeData((const char*)mOrigVertices, vertexSize * mHeader.nVertices);

	IndexData* indexdata = pMesh->getIndexData();

	indexdata->createBuffer(2, nIndices);
	indexdata->writeData((const char*)indices.data(), 2 * nIndices);
	for (size_t j = 0; j < view->n_texture_unit; j++) {
		
		size_t geoset = texunit[j].op;

		pass.geoset = (int)geoset;

		pass.indexStart = ops[geoset].istart;
		pass.indexCount = ops[geoset].icount;
		pass.vertexStart = ops[geoset].vstart;
		pass.vertexEnd = pass.vertexStart + ops[geoset].vcount;
		pass.tex = texlookup[texunit[j].textureid];

		SubMesh* sub = pMesh->addSubMesh(true, true);

		std::string name = Ogre::StringUtil::format("%s%d", mName, j);
		std::shared_ptr<Material> mat = MaterialManager::getSingleton().create(name);
		const std::string& texname = texnames[pass.tex];
		mat->addTexture(texname);
		ShaderInfo info;
		info.shaderName = "ogresimple";
		mat->addShader(info);
		mat->setCullMode(CULL_NONE);
		sub->setMaterial(mat);

		sub->addIndexs(pass.indexCount, pass.indexStart, pass.vertexStart);
	}
}