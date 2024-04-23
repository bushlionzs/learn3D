#include "OgreHeader.h"
#include "wowParticle.h"
#include "wowUtil.h"
#include "M2Loader.h"
#include "OgreBone.h"
#include "OgreVertexData.h"
#include "OgreIndexData.h"
#include "OgreVertexDeclaration.h"
#include "OgreHardwareVertexBuffer.h"
#include "OgreHardwareIndexBuffer.h"
#include "OgreCamera.h"
#include "OgreMaterial.h"
#include "OgreController.h"
#include "OgreControllerManager.h"
#include "OgreRoot.h"
#include "OgreSceneNode.h"
#include "OgreSceneManager.h"

#define MAX_PARTICLES 10000
bool bZeroParticle = true;

class WowParticleSystemUpdateValue : public ControllerValue<Real>
{
protected:
	std::vector<WowParticleSystem*> mParticleSystemVector;
public:
	WowParticleSystemUpdateValue()
	{

	}

	Real getValue(void) const { return 0; } // N/A

	void setValue(Real value)
	{
		return;
		for (auto ps : mParticleSystemVector)
		{
			ps->update(value);
		}
	}

	void addParticleSystem(WowParticleSystem* ps)
	{
		mParticleSystemVector.push_back(ps);
	}
};

Ogre::ColourValue fromARGB(uint32 color)
{
	const float a = ((color & 0xFF000000) >> 24) / 255.0f;
	const float r = ((color & 0x00FF0000) >> 16) / 255.0f;
	const float g = ((color & 0x0000FF00) >>  8) / 255.0f;
	const float b = ((color & 0x000000FF)      ) / 255.0f;
    return Ogre::ColourValue(r,g,b,a);
}

template<class T>
T lifeRamp(float life, float mid, const T &a, const T &b, const T &c)
{
	if (life<=mid) 
		return interpolate<T>(life / mid,a,b);
	else 
		return interpolate<T>((life-mid) / (1.0f-mid),b,c);
}

WowParticleSystem::WowParticleSystem() : mid(0), emitter(0), rem(0)
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

	static WowParticleSystemUpdateValue* pWowParticleSystemUpdateValue = nullptr;

	if (!pWowParticleSystemUpdateValue)
	{
		pWowParticleSystemUpdateValue = new WowParticleSystemUpdateValue();

		ControllerManager& mgr = ControllerManager::getSingleton();

		ControllerValueRealPtr updValue(pWowParticleSystemUpdateValue);

		mgr.createFrameTimePassthroughController(updValue);
	}

	pWowParticleSystemUpdateValue->addParticleSystem(this);

	auto sceneMgr = Ogre::Root::getSingleton().getSceneManager(MAIN_SCENE_MANAGER);
	auto root = sceneMgr->getRoot();

	auto sub = root->createChildSceneNode("");

	sub->attachObject(this);
}

void WowParticleSystem::init(
	std::shared_ptr<DataStream>& stream, 
	ModelParticleEmitterDef &mta,
	uint32 *globals,
	M2Loader* model)
{
	mtime = 0.0f;
	speed.init (mta.EmissionSpeed, stream.get(), globals);
	variation.init (mta.SpeedVariation, stream.get(), globals);
	spread.init (mta.VerticalRange, stream.get(), globals);
	lat.init (mta.HorizontalRange, stream.get(), globals);
	gravity.init (mta.Gravity, stream.get(), globals);
	lifespan.init (mta.Lifespan, stream.get(), globals);
	rate.init (mta.EmissionRate, stream.get(), globals);
	areal.init (mta.EmissionAreaLength, stream.get(), globals);
	areaw.init (mta.EmissionAreaWidth, stream.get(), globals);
	deacceleration.init (mta.Gravity2, stream.get(), globals);
	enabled.init (mta.en, stream.get(), globals);


	Ogre::Vector3 colors2[3];
	memcpy(colors2, stream->getStreamData()+mta.p.colors.ofsKeys, sizeof(Ogre::Vector3)*3);
	for (size_t i=0; i<3; i++) {
		float opacity = *(short*)(stream->getStreamData() +mta.p.opacity.ofsKeys+i*2);
		colors[i] = Ogre::ColourValue(colors2[i].x/255.0f, colors2[i].y/255.0f, colors2[i].z/255.0f, opacity/32767.0f);
		sizes[i] = (*(float*)(stream->getStreamData() +mta.p.sizes.ofsKeys+i*sizeof(Ogre::Vector2)))*mta.p.scales[i];
	}
	mid = 0.5; // mid can't be 0 or 1, TODO, Alfred

		
	slowdown = mta.p.slowdown;
	rotation = mta.p.rotation;
	pos = fixCoordSystem(mta.pos);
	texture = model->getTexture(mta.texture);
	blend = mta.blend;
	rows = mta.rows;
	if (rows == 0)
		rows = 1;
	cols = mta.cols;
	if (cols == 0)
		cols = 1;
	ParticleType = mta.ParticleType;
	//order = mta.s2;
	order = mta.ParticleType>0 ? -1 : 0;
	parent = model->getBone(mta.bone);

	billboard = !(mta.flags & MODELPARTICLE_FLAGS_DONOTBILLBOARD);

	// diagnosis test info
	EmitterType = mta.EmitterType;
	flags = mta.flags; // 0x10	Do not Trail

	manim = mtime = 0;
	rem = 0;

	emitter = 0;
	switch (EmitterType) {
	case MODELPARTICLE_EMITTER_PLANE:
		emitter = new PlaneParticleEmitter(this);
		break;
	case MODELPARTICLE_EMITTER_SPHERE:
		emitter = new SphereParticleEmitter(this);
		break;
	case MODELPARTICLE_EMITTER_SPLINE: // Spline? (can't be bothered to find one)
	default:
		assert(false);
		break;
	}

	tofs = frand();

	// init tiles, slice the texture
	for (int i=0; i<rows*cols; i++) {
		TexCoordSet tc;
		initTile(tc.tc, i);
		tiles.push_back(tc);
	}

	//create vertex buffer and index buffer

	mVertexData.reset(new VertexData);
	mVertexData->vertexCount = maxParticles;
	mVertexData->vertexSlotInfo.emplace_back();
	mVertexData->vertexDeclaration->addElement(0, 0, 0, VET_FLOAT3, VES_POSITION);
	mVertexData->vertexDeclaration->addElement(0, 0, 12, VET_FLOAT2, VES_TEXTURE_COORDINATES);
	mVertexData->vertexDeclaration->addElement(0, 0, 20, VET_UBYTE4_NORM, VES_DIFFUSE);
	auto& back = mVertexData->vertexSlotInfo.back();
	//position
	//color
	//texcoord
	uint32_t vertexSize = 4*3 + 4*2 + 4;
	back.createBuffer(vertexSize, maxParticles * 4);
	mIndexDataView.reset(new IndexDataView);
	mIndexDataView->mIndexCount = 0;
	mIndexDataView->mBaseVertexLocation = 0;
	mIndexDataView->mIndexLocation = 0;
	mIndexData.reset(new IndexData());
	mIndexData->mIndexStart = 0;
	mIndexData->mIndexCount = maxParticles * 6;
	mIndexData->createBuffer(2, mIndexData->mIndexCount);
	/* Create indexes (will be the same every frame)
	   Using indexes because it means 1/3 less vertex transforms (4 instead of 6)

	   Billboard layout relative to camera:

		0-----1
		|    /|
		|  /  |
		|/    |
		2-----3
	*/

	HardwareBufferLockGuard lockGuard(mIndexData->mIndexBuffer.get());
	uint16_t* pIdx = (uint16_t*)lockGuard.data();

	for (size_t idx, idxOff, bboard = 0; bboard < maxParticles; ++bboard)
	{
		// Do indexes
		idx = bboard * 6;
		idxOff = bboard * 4;

		pIdx[idx] = static_cast<unsigned short>(idxOff); // + 0;, for clarity
		pIdx[idx + 1] = static_cast<unsigned short>(idxOff + 2);
		pIdx[idx + 2] = static_cast<unsigned short>(idxOff + 1);
		pIdx[idx + 3] = static_cast<unsigned short>(idxOff + 1);
		pIdx[idx + 4] = static_cast<unsigned short>(idxOff + 2);
		pIdx[idx + 5] = static_cast<unsigned short>(idxOff + 3);
	}

	mMaterial = std::make_shared<Material>("wowParticle");
	mMaterial->addTexture(texture);

	Ogre::ColourBlendState blendState;

	if (blend == BM_TRANSPARENT)
	{
		blendState.sourceFactor = Ogre::SBF_SOURCE_ALPHA;
		blendState.destFactor = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
		blendState.sourceFactorAlpha = Ogre::SBF_SOURCE_ALPHA;
		blendState.destFactorAlpha = Ogre::SBF_ONE_MINUS_SOURCE_ALPHA;
		mMaterial->setBlendState(blendState);
	}
	else if (blend == BM_ADDITIVE_ALPHA)
	{
		blendState.sourceFactor = Ogre::SBF_SOURCE_ALPHA;
		blendState.destFactor = Ogre::SBF_ONE;
		blendState.sourceFactorAlpha = Ogre::SBF_ONE;
		blendState.destFactorAlpha = Ogre::SBF_ZERO;
		mMaterial->setBlendState(blendState);
	}

	ShaderInfo info;
	info.shaderName = "ogreparticle";
	mMaterial->addShader(info);


	mRenderables.push_back(this);
}

void WowParticleSystem::initTile(Ogre::Vector2 *tc, int num)
{
	Ogre::Vector2 otc[4];
	Ogre::Vector2 a,b;
	int x = num % cols;
	int y = num / cols;
	a.x = x * (1.0f / cols);
	b.x = (x+1) * (1.0f / cols);
	a.y = y * (1.0f / rows);
	b.y = (y+1) * (1.0f / rows);

	otc[0] = a;
	otc[2] = b;
	otc[1].x = b.x;
	otc[1].y = a.y;
	otc[3].x = a.x;
	otc[3].y = b.y;

	for (size_t i=0; i<4; i++) {
		tc[(i+4-order) & 3] = otc[i];
	}
}


void WowParticleSystem::update(float dt)
{
	size_t l_manim = manim;
	if (bZeroParticle)
		l_manim = 0;
	float grav = gravity.getValue(l_manim, mtime);
	float deaccel = deacceleration.getValue(l_manim, mtime);

	// spawn new particles
	if (emitter)
	{
		float frate = rate.getValue(l_manim, mtime);
		float flife = lifespan.getValue(l_manim, mtime);

		float ftospawn;
		if (flife)
			ftospawn = (dt * frate / flife) + rem;
		else
			ftospawn = rem;
		if (ftospawn < 1.0f) {
			rem = ftospawn;
			if (rem < 0) 
				rem = 0;
		} 
		else
		{
			unsigned int tospawn = (int)ftospawn;

			if ((tospawn + particles.size()) > maxParticles)
			{
				tospawn = (unsigned int)(maxParticles - particles.size());
			}
				

			rem = ftospawn - (float)tospawn;

			float w = areal.getValue(l_manim, mtime) * 0.5f;
			float l = areaw.getValue(l_manim, mtime) * 0.5f;
			float spd = speed.getValue(l_manim, mtime);
			float var = variation.getValue(l_manim, mtime);
			float spr = spread.getValue(l_manim, mtime);
			float spr2 = lat.getValue(l_manim, mtime);
			bool en = true;
			if (enabled.uses(manim))
				en = enabled.getValue(manim, mtime)!=0;

			//rem = 0;
			if (en) {
				for (size_t i=0; i<tospawn; i++) {
					WowParticle p = emitter->newParticle(manim, mtime, w, l, spd, var, spr, spr2);
					// sanity check:
					if (particles.size() < MAX_PARTICLES) // No need to check this every loop iteration. Already checked above.
						particles.push_back(p);
				}
			}
		}
	}

	
	float mspeed = 1.0f;

	for (auto it = particles.begin(); it != particles.end(); )
	{
		WowParticle&p = *it;
		p.speed += p.down * grav * dt - p.dir * deaccel * dt;

		if (slowdown>0)
		{
			mspeed = expf(-1.0f * slowdown * p.life);
		}
		p.pos += p.speed * mspeed * dt;
		
		p.life += dt;
		float rlife = p.life / p.maxlife;
		if (rlife >= 1.0f)
		{
			rlife = 1.0f;
		}
		// calculate size and color based on lifetime
		p.size = lifeRamp<float>(rlife, mid, sizes[0], sizes[1], sizes[2]);
		p.color = lifeRamp<Ogre::ColourValue>(rlife, mid, colors[0], colors[1], colors[2]);

		// kill off old particles
		if (rlife >= 1.0f) 
			it = particles.erase(it);
		else 
			++it;
	}

	
	mIndexDataView->mIndexCount = particles.size() * 6;

	Ogre::Vector3 vRight(1.0f, 0.0f, 0.0f);
	Ogre::Vector3 vUp(0.0f, 1.0f, 0.0f);

	if (billboard)
	{
		Camera* cam = (Camera*)mCamera;
		if (cam)
		{
			Quaternion camQ = cam->getDerivedOrientation();
			vRight = camQ * Vector3::UNIT_X;
			vUp = camQ * Vector3::UNIT_Y;
		}
		
	}

	RGBA* pCol;
	std::shared_ptr<Ogre::HardwareVertexBuffer>& buf = mVertexData->vertexSlotInfo.back().hardwareVertexBuffer;
	float* lockPtr = reinterpret_cast<float*>(buf->lock());
	float* firstPtr = lockPtr;
	for (auto it = particles.begin(); it != particles.end(); it++)
	{
		const float size = it->size;
		RGBA colour = it->color.getAsBYTE();
		
		//top-left
		Ogre::Vector3 leftTop = it->pos - (vRight - vUp) * size;
		*lockPtr++ = leftTop.x;
		*lockPtr++ = leftTop.y;
		*lockPtr++ = leftTop.z;
		
		*lockPtr++ = tiles[it->tile].tc[3].x;
		*lockPtr++ = tiles[it->tile].tc[3].y;

		pCol = static_cast<RGBA*>(static_cast<void*>(lockPtr));
		*pCol++ = colour;
		lockPtr = static_cast<float*>(static_cast<void*>(pCol));

		//top-right
		Ogre::Vector3 topRight = it->pos + (vRight + vUp) * size;
		*lockPtr++ = topRight.x;
		*lockPtr++ = topRight.y;
		*lockPtr++ = topRight.z;

		*lockPtr++ = tiles[it->tile].tc[2].x;
		*lockPtr++ = tiles[it->tile].tc[2].y;

		pCol = static_cast<RGBA*>(static_cast<void*>(lockPtr));
		*pCol++ = colour;
		lockPtr = static_cast<float*>(static_cast<void*>(pCol));

		//left-bottom
		Ogre::Vector3 leftBottom = it->pos - (vRight + vUp) * size;
		*lockPtr++ = leftBottom.x;
		*lockPtr++ = leftBottom.y;
		*lockPtr++ = leftBottom.z;

		*lockPtr++ = tiles[it->tile].tc[0].x;
		*lockPtr++ = tiles[it->tile].tc[0].y;

		pCol = static_cast<RGBA*>(static_cast<void*>(lockPtr));
		*pCol++ = colour;
		lockPtr = static_cast<float*>(static_cast<void*>(pCol));

		//right-bottom

		Ogre::Vector3 rightBottom = it->pos + (vRight - vUp) * size;
		*lockPtr++ = rightBottom.x;
		*lockPtr++ = rightBottom.y;
		*lockPtr++ = rightBottom.z;

		*lockPtr++ = tiles[it->tile].tc[1].x;
		*lockPtr++ = tiles[it->tile].tc[1].y;

		pCol = static_cast<RGBA*>(static_cast<void*>(lockPtr));
		*pCol++ = colour;
		lockPtr = static_cast<float*>(static_cast<void*>(pCol));
	}
	buf->unlock();
}

void WowParticleSystem::setup(size_t anim, size_t time)
{
	manim = anim;
	mtime = time;
}

const AxisAlignedBox& WowParticleSystem::getBoundingBox(void) const
{
	static AxisAlignedBox box;
	box.setInfinite();
	return box;
}

void WowParticleSystem::_notifyCurrentCamera(ICamera* cam)
{
	mCamera = cam;
}

Matrix4 CalcSpreadMatrix(float Spread1,float Spread2, float w, float l)
{
	int i,j;
	float a[2],c[2],s[2];
	Matrix4	Temp;
	
	Matrix4 SpreadMat = Matrix4::IDENTITY;
	
	a[0]=randfloat(-Spread1,Spread1)/2.0f;
	a[1]=randfloat(-Spread2,Spread2)/2.0f;

	for(i=0;i<2;i++)
	{		
		c[i]=cos(a[i]);
		s[i]=sin(a[i]);
	}
	Temp = Matrix4::IDENTITY;
	Temp[1][1]=c[0];
	Temp[2][1]=s[0];
	Temp[2][2]=c[0];
	Temp[1][2]=-s[0];

	SpreadMat=SpreadMat*Temp;

	Temp = Matrix4::IDENTITY;
	Temp[0][0]=c[1];
	Temp[1][0]=s[1];
	Temp[1][1]=c[1];
	Temp[0][1]=-s[1];

	SpreadMat=SpreadMat*Temp;

	float Size=abs(c[0])*l+abs(s[0])*w;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			SpreadMat[i][j]*=Size;

	return SpreadMat;
}

WowParticle PlaneParticleEmitter::newParticle(
	size_t anim, size_t time, float w, float l, float spd, float var, float spr, float spr2)
{
	WowParticle p;

	//Spread Calculation
	Matrix4 SpreadMat = CalcSpreadMatrix(spr, spr, 1.0f, 1.0f);
	Matrix4 mrot = Matrix4::IDENTITY;
	Matrix4 mat = Matrix4::IDENTITY;
	mrot = mrot*SpreadMat;
	
	if (sys->flags == 1041) { // Trans Halo
		assert(false);
		p.pos = mat * (sys->pos + Ogre::Vector3(randfloat(-l,l), 0, randfloat(-w,w)));

		const float t = randfloat(0.0f, float(2*Ogre::Math::PI));

		p.pos = Ogre::Vector3(0.0f, sys->pos.y + 0.15f, sys->pos.z) + Ogre::Vector3(cos(t)/8, 0.0f, sin(t)/8); 

		Ogre::Vector3 dir(0.0f, 1.0f, 0.0f);
		p.dir = dir;
		dir.normalise();
		p.speed = dir * spd * randfloat(0, var);
	} 
	else if (sys->flags == 25 ) 
	{ // Weapon Flame
		assert(false);
	} 
	else if (sys->flags == 17 )
	{ // Weapon Glow
		
		assert(false);
	} 
	else 
	{
		p.pos = sys->pos + Ogre::Vector3(randfloat(-l,l), 0, randfloat(-w,w));

		Ogre::Vector3 dir = Ogre::Vector3(0,1,0);
		
		p.dir = dir;//.normalize();
		p.down = Ogre::Vector3(0,-1.0f,0); // dir * -1.0f;
		float tmp = spd * (1.0f + randfloat(-var, var));
		dir.normalise();
		p.speed = dir * tmp;
	}

	if(!sys->billboard)	{
		p.corners[0] = mrot * Ogre::Vector3(-1,0,+1);
		p.corners[1] = mrot * Ogre::Vector3(+1,0,+1);
		p.corners[2] = mrot * Ogre::Vector3(+1,0,-1);
		p.corners[3] = mrot * Ogre::Vector3(-1,0,-1);
	}

	p.life = 0;
	size_t l_anim = anim;
	if (bZeroParticle)
		l_anim = 0;
	p.maxlife = sys->lifespan.getValue(l_anim, time);
	if (p.maxlife == 0)
		p.maxlife = 1;

	p.origin = p.pos;

	p.tile = randint(0, sys->rows*sys->cols-1);

	if (p.tile >= sys->rows * sys->cols)
	{
		p.tile = sys->rows * sys->cols - 1;
	}
	return p;
}

WowParticle SphereParticleEmitter::newParticle(
	size_t anim, size_t time, float w, float l, float spd, float var, float spr, float spr2)
{
	WowParticle p;
	assert(false);
	return p;
}

void RibbonEmitter::init(
	std::shared_ptr<DataStream>& stream, 
	ModelRibbonEmitterDef &mta, 
	uint32 *globals,
	M2Loader* model)
{
	color.init(mta.color, stream.get(), globals);
	opacity.init(mta.opacity, stream.get(), globals);
	above.init(mta.above, stream.get(), globals);
	below.init(mta.below, stream.get(), globals);

	parent = model->getBone(mta.bone);
	int *texlist = (int*)(stream->getStreamData() + mta.ofsTextures);
	// just use the first texture for now; most models I've checked only had one
	texture = model->getTexture(texlist[0]);

	tpos = pos = fixCoordSystem(mta.pos);

	// TODO: figure out actual correct way to calculate length
	// in BFD, res is 60 and len is 0.6, the trails are very short (too long here)
	// in CoT, res and len are like 10 but the trails are supposed to be much longer (too short here)
	numsegs = (int)mta.res;
	seglen = mta.length;
	length = mta.res * seglen;

	// create first segment
	RibbonSegment rs;
	rs.pos = tpos;
	rs.len = 0;
	segs.push_back(rs);
}

void RibbonEmitter::setup(size_t anim, size_t time)
{
	Matrix4 mat = Matrix4::IDENTITY;
	Ogre::Vector3 ntpos = mat * pos;
	Ogre::Vector3 ntup = mat * (pos + Ogre::Vector3(0,0,1));
	ntup -= ntpos;
	ntup.normalise();
	float dlen = (ntpos-tpos).length();

	manim = anim;
	mtime = time;

	// move first segment
	RibbonSegment &first = *segs.begin();
	if (first.len > seglen) {
		// add new segment
		first.back = (tpos-ntpos).normalise();
		first.len0 = first.len;
		RibbonSegment newseg;
		newseg.pos = ntpos;
		newseg.up = ntup;
		newseg.len = dlen;
		segs.push_front(newseg);
	} else {
		first.up = ntup;
		first.pos = ntpos;
		first.len += dlen;
	}

	// kill stuff from the end
	float l = 0;
	bool erasemode = false;
	for (std::list<RibbonSegment>::iterator it = segs.begin(); it != segs.end(); ) {
		if (!erasemode) {
			l += it->len;
			if (l > length) {
				it->len = l - length;
				erasemode = true;
			}
			++it;
		} else {
			segs.erase(it++);
		}
	}

	tpos = ntpos;
	auto v = color.getValue(anim, time);
	tcolor = Ogre::ColourValue(v.x, v.y, v.z, opacity.getValue(anim, time));
	
	tabove = above.getValue(anim, time);
	tbelow = below.getValue(anim, time);
}

void RibbonEmitter::draw()
{
	
}





