#ifndef PARTICLE_H
#define PARTICLE_H



#include "M2Header.h"
#include "animated.h"
#include "OgreColourValue.h"
#include "OgreMoveObject.h"
#include "OgreRenderable.h"
#include <list>
class WowParticleSystem;
class RibbonEmitter;
class M2Bone;
class M2Loader;
class VertexData;
class IndexData;
class IndexDataView;
struct WowParticle
{
	Ogre::Vector3 pos, speed, down, origin, dir;
	Ogre::Vector3	corners[4];
	float size, life, maxlife;
	size_t tile;
	Ogre::ColourValue color;
};

typedef std::list<WowParticle> ParticleList;

class ParticleEmitter
{
protected:
	WowParticleSystem*sys;
public:
	ParticleEmitter(WowParticleSystem*sys): sys(sys) {}
	virtual WowParticle newParticle(
		size_t anim, 
		size_t time, 
		float w, 
		float l, 
		float spd, 
		float var, 
		float spr, 
		float spr2) = 0;
	virtual ~ParticleEmitter() {}
};

class PlaneParticleEmitter: public ParticleEmitter {
public:
	PlaneParticleEmitter(WowParticleSystem*sys): ParticleEmitter(sys) {}
	WowParticle newParticle(
		size_t anim, 
		size_t time, 
		float w, 
		float l, 
		float spd, 
		float var, 
		float spr, 
		float spr2);
};

class SphereParticleEmitter: public ParticleEmitter {
public:
	SphereParticleEmitter(WowParticleSystem *sys): ParticleEmitter(sys) {}
	WowParticle newParticle(
		size_t anim, 
		size_t time, 
		float w, 
		float l, 
		float spd, 
		float var, 
		float spr, 
		float spr2);
};

struct TexCoordSet {
    Ogre::Vector2 tc[4];
};

class WowParticleSystem: public MoveObject, public Renderable
{
	float mid, slowdown, rotation;
	Ogre::Vector3 pos;
	std::string texture;
	ParticleEmitter *emitter;
	ParticleList particles;
	int blend, order, ParticleType;
	size_t manim;
	size_t mtime;
	int rows, cols;
	std::vector<TexCoordSet> tiles;
	void initTile(Ogre::Vector2*tc, int num);
	bool billboard;
	int index;
	float rem;
	int32 flags;
	int16 EmitterType;
	int32 maxParticles = 100;
	Bone*parent;
	ICamera* mCamera = nullptr;
	std::unique_ptr<VertexData> mVertexData;
	std::unique_ptr<IndexData> mIndexData;
	std::unique_ptr<IndexDataView> mIndexDataView;
public:
	float tofs;

	Animated<uint16> enabled;
	Animated<float> speed, variation, spread, lat, gravity, lifespan, rate, areal, areaw, deacceleration;
	Ogre::ColourValue colors[3];
	float sizes[3];

	WowParticleSystem();
	~WowParticleSystem() { delete emitter; }

	void init(
		std::shared_ptr<DataStream>& stream, 
		ModelParticleEmitterDef &mta,
		uint32 *globals,
		M2Loader* model);
	void update(float dt);

	void setup(size_t anim, size_t time);
	virtual const AxisAlignedBox& getBoundingBox(void) const;
	virtual void _notifyCurrentCamera(ICamera* cam);
	virtual VertexData* getVertexData() override
	{
		return mVertexData.get();
	}

	IndexData* getIndexData() override
	{
		return mIndexData.get();
	}
	IndexDataView* getIndexView() override
	{
		return mIndexDataView.get();
	}

	friend class PlaneParticleEmitter;
	friend class SphereParticleEmitter;
};


struct RibbonSegment {
	Ogre::Vector3 pos, up, back;
	float len,len0;
};

class RibbonEmitter {
	Animated<Ogre::Vector3> color;
	AnimatedShort opacity;
	Animated<float> above, below;

	Bone *parent;
	float f1, f2;

	Ogre::Vector3 pos;

	size_t manim, mtime;
	float length, seglen;
	int numsegs;
	
	Ogre::Vector3 tpos;
	Ogre::ColourValue tcolor;
	float tabove, tbelow;

	std::string texture;

	std::list<RibbonSegment> segs;

public:

	void init(
		std::shared_ptr<DataStream>& stream, 
		ModelRibbonEmitterDef &mta, 
		uint32 *globals,
		M2Loader* model);
	void setup(size_t anim, size_t time);
	void draw();
};



#endif
