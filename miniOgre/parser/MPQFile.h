#pragma once

#include "OgreScriptLoader.h"

class MPQArchive : public PackFileBase
{
public:
    MPQArchive(const String& name);

    void load();

    Ogre::StreamContent* getPackfile(
        const String& name, const String& group);
private:
    HANDLE _archiveHandle;
    std::atomic<bool> finished = false;
    std::string _mpqName;
};