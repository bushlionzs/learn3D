#pragma once
#include <stdint.h>

struct M2Sphere
{
	float min[3];
	float max[3];
	float radius;
};

struct M2Header {
	char id[4];
	uint8_t version[4];
	uint32_t nameLength;
	uint32_t nameOfs;
	uint32_t GlobalModelFlags; // 1: tilt x, 2: tilt y, 4:, 8: add another field in header, 16: ; (no other flags as of 3.1.1);

	uint32_t nGlobalSequences; // AnimationRelated
	uint32_t ofsGlobalSequences; // A list of timestamps.
	uint32_t nAnimations; // AnimationRelated
	uint32_t ofsAnimations; // Information about the animations in the model.
	uint32_t nAnimationLookup; // AnimationRelated
	uint32_t ofsAnimationLookup; // Mapping of global IDs to the entries in the Animation sequences block.
	//uint32 nD;
	//uint32 ofsD;
	uint32_t nBones; // BonesAndLookups
	uint32_t ofsBones; // Information about the bones in this model.
	uint32_t nKeyBoneLookup; // BonesAndLookups
	uint32_t ofsKeyBoneLookup; // Lookup table for key skeletal bones.

	uint32_t nVertices; // GeometryAndRendering
	uint32_t ofsVertices; // Vertices of the model.
	uint32_t nViews; // GeometryAndRendering
	//uint32 ofsViews; // Views (LOD) are now in .skins.

	uint32_t nColors; // ColorsAndTransparency
	uint32_t ofsColors; // Color definitions.

	uint32_t nTextures; // TextureAndTheifAnimation
	uint32_t ofsTextures; // Textures of this model.

	uint32_t nTransparency; // H,  ColorsAndTransparency
	uint32_t ofsTransparency; // Transparency of textures.
	//uint32 nI;   // always unused ?
	//uint32 ofsI;
	uint32_t nTexAnims;	// J, TextureAndTheifAnimation
	uint32_t ofsTexAnims;
	uint32_t nTexReplace; // TextureAndTheifAnimation
	uint32_t ofsTexReplace; // Replaceable Textures.

	uint32_t nTexFlags; // Render Flags
	uint32_t ofsTexFlags; // Blending modes / render flags.
	uint32_t nBoneLookup; // BonesAndLookups
	uint32_t ofsBoneLookup; // A bone lookup table.

	uint32_t nTexLookup; // TextureAndTheifAnimation
	uint32_t ofsTexLookup; // The same for textures.

	uint32_t nTexUnitLookup;		// L, TextureAndTheifAnimation, seems gone after Cataclysm
	uint32_t ofsTexUnitLookup; // And texture units. Somewhere they have to be too.
	uint32_t nTransparencyLookup; // M, ColorsAndTransparency
	uint32_t ofsTransparencyLookup; // Everything needs its lookup. Here are the transparencies.
	uint32_t nTexAnimLookup; // TextureAndTheifAnimation
	uint32_t ofsTexAnimLookup; // Wait. Do we have animated Textures? Wasn't ofsTexAnims deleted? oO

	M2Sphere collisionSphere;
	M2Sphere boundSphere;

	uint32_t nBoundingTriangles; // Miscellaneous
	uint32_t ofsBoundingTriangles;
	uint32_t nBoundingVertices; // Miscellaneous
	uint32_t ofsBoundingVertices;
	uint32_t nBoundingNormals; // Miscellaneous
	uint32_t ofsBoundingNormals;

	uint32_t nAttachments; // O, Miscellaneous
	uint32_t ofsAttachments; // Attachments are for weapons etc.
	uint32_t nAttachLookup; // P, Miscellaneous
	uint32_t ofsAttachLookup; // Of course with a lookup.
	uint32_t nEvents; // 
	uint32_t ofsEvents; // Used for playing sounds when dying and a lot else.
	uint32_t nLights; // R
	uint32_t ofsLights; // Lights are mainly used in loginscreens but in wands and some doodads too.
	uint32_t nCameras; // S, Miscellaneous
	uint32_t ofsCameras; // The cameras are present in most models for having a model in the Character-Tab.
	uint32_t nCameraLookup; // Miscellaneous
	uint32_t ofsCameraLookup; // And lookup-time again, unit16
	uint32_t nRibbonEmitters; // U, Effects
	uint32_t ofsRibbonEmitters; // Things swirling around. See the CoT-entrance for light-trails.
	uint32_t nParticleEmitters; // V, Effects
	uint32_t ofsParticleEmitters; // Spells and weapons, doodads and loginscreens use them. Blood dripping of a blade? Particles.
};

struct M2ModelVertex {
	Ogre::Vector3 pos;
	uint8_t weights[4];
	uint8_t bones[4];
	Ogre::Vector3 normal;
	Ogre::Vector2 texcoords;
	int unk1, unk2; // always 0,0 so this is probably unused
};

#define TEXTURE_MAX 32
struct ModelTextureDef {
	uint32_t type;
	uint32_t flags;
	uint32_t nameLen;
	uint32_t nameOfs;
};

enum TextureTypes {
	TEXTURE_FILENAME = 0,			// Texture given in filename
	TEXTURE_BODY,				// Body + clothes
	TEXTURE_CAPE,				// Item, Capes ("Item\ObjectComponents\Cape\*.blp")
	TEXTURE_ITEM = TEXTURE_CAPE,
	TEXTURE_ARMORREFLECT,		// 
	TEXTURE_HAIR = 6,				// Hair, bear
	TEXTURE_FUR = 8,				// Tauren fur
	TEXTURE_INVENTORY_ART1,		// Used on inventory art M2s (1): inventoryartgeometry.m2 and inventoryartgeometryold.m2
	TEXTURE_QUILL,				// Only used in quillboarpinata.m2. I can't even find something referencing that file. Oo Is it used?
	TEXTURE_GAMEOBJECT1,		// Skin for creatures or gameobjects #1
	TEXTURE_GAMEOBJECT2,		// Skin for creatures or gameobjects #2
	TEXTURE_GAMEOBJECT3,		// Skin for creatures or gameobjects #3
	TEXTURE_INVENTORY_ART2,		// Used on inventory art M2s (2): ui-buffon.m2 and forcedbackpackitem.m2 (LUA::Model:ReplaceIconTexture("texture"))
	TEXTURE_15,					// Patch 12857, Unknown
	TEXTURE_16,					//
	TEXTURE_17,					//
};

enum TextureFlags {
	TEXTURE_WRAPX = 1,
	TEXTURE_WRAPY
};

enum GRAPHIC_EFFECTS {
	FRAGMENT_SHADER,
	VERTEX_SHADER,
	GLSL,
	COMPRESSED_TEXTURES,
	MULTI_TEXTURES,
	DRAW_RANGE_ELEMENTS,
	POINT_SPRITES,
	//bool supportShaders;//  = false;
	ANTI_ALIAS,
	VERTEX_BUFFER,
	PIXEL_BUFFER,
	FRAME_BUFFER,
	NON_POWEROFTWO,
	OPENGL_20,
	WGLPIXELFORMAT,

	NUM_EFFECTS
};

enum ModelType {
	MT_NORMAL,
	MT_CHAR,
	MT_WMO,
	MT_NPC
};