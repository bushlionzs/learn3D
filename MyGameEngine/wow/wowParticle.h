#ifndef PARTICLE_H
#define PARTICLE_H



#include "M2Header.h"
#include "animated.h"
#include "OgreColourValue.h"

#include <list>
class WowParticleSystem;
class RibbonEmitter;
class M2Bone;
class M2Loader;

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

class WowParticleSystem {
	float mid, slowdown, rotation;
	Ogre::Vector3 pos;
	std::string texture;
	ParticleEmitter *emitter;
	ParticleList particles;
	int blend, order, ParticleType;
	size_t manim, mtime;
	int rows, cols;
	std::vector<TexCoordSet> tiles;
	void initTile(Ogre::Vector2*tc, int num);
	bool billboard;

	float rem;
	//bool transform;

	// unknown parameters omitted for now ...
	int32 flags;
	int16 EmitterType;

	Bone*parent;

public:
	float tofs;

	Animated<uint16> enabled;
	Animated<float> speed, variation, spread, lat, gravity, lifespan, rate, areal, areaw, deacceleration;
	Ogre::ColourValue colors[3];
	float sizes[3];

	WowParticleSystem(): mid(0), emitter(0), rem(0)
	{
		blend = 0;
		order = 0;
		ParticleType = 0;
		manim = 0;
		mtime = 0;
		rows = 0;
		cols = 0;

		parent = 0;

		slowdown = 0;
		rotation = 0;
		tofs = 0;
	}
	~WowParticleSystem() { delete emitter; }

	void init(
		std::shared_ptr<DataStream>& stream, 
		ModelParticleEmitterDef &mta,
		uint32 *globals,
		M2Loader* model);
	void update(float dt);

	void setup(size_t anim, size_t time);
	void draw();

	friend class PlaneParticleEmitter;
	friend class SphereParticleEmitter;

	friend std::ostream& operator<<(std::ostream& out, ParticleSystem& v)
	{
		
		return out;
	}
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
