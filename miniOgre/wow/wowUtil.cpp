#include "OgreHeader.h"
#include "wowUtil.h"

Ogre::Vector3 fixCoordSystem(Ogre::Vector3 v)
{
	return Ogre::Vector3(v.x, v.z, -v.y);
}

Ogre::Vector3 fixCoordSystem2(Ogre::Vector3 v)
{
	return Ogre::Vector3(v.x, v.z, v.y);
}

Ogre::Vector4 fixCoordSystemQuat(Ogre::Vector4 v)
{
	return Ogre::Vector4(-v.x, -v.z, v.y, v.w);
}

std::string makeSkinTexture(std::string& texfn, std::string& skin)
{
	size_t i = texfn.find_last_of('\\');
    std::string res = res.substr(0, i + 1);
	res.append(skin);
	res.append(".blp");
	return res;
}

float frand()
{
	return rand() / (float)RAND_MAX;
}

float randfloat(float lower, float upper)
{
	return lower + (upper - lower) * (rand() / (float)RAND_MAX);
}

int randint(int lower, int upper)
{
	return lower + (int)((upper + 1 - lower) * frand());
}