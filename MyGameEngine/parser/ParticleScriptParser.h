#pragma once


#include "OgreScriptLoader.h"

namespace Ogre
{
	class ParticleSystem;
	class ParticleEmitter;
	class ParticleAffector;
}
class ParticleScriptParser : public ScriptLoader
{
public:
	virtual String getSuffix();
	virtual void parseScript(DataStreamPtr& stream, const String& groupName);
	virtual Real getLoadingOrder(void) const;
private:
	void parseParticleImpl(const std::string& content);
	bool readParticle(std::stringstream& ss, ParticleSystem* particle);
	bool readEmitter(std::stringstream& ss, ParticleEmitter* emitter);
	bool readAffector(std::stringstream& ss, ParticleAffector* affector);

};