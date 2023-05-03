#pragma once

#include "OgreScriptLoader.h"

class MPQArchive : public Ogre::ScriptLoader, public PackFileBase
{
public:
    MPQArchive(const std::string& name, bool doListfile);
    bool hasFile(const std::string& filename) const;
    bool openFile(const std::string& filename, HANDLE* fileHandle) const;
    static void loadMPQ(const std::string& filename, bool doListfile = false);

    virtual String getSuffix();
    virtual void parseScript(ResourceInfo* res, const String& groupName);
    virtual Real getLoadingOrder(void) const;

    Ogre::StreamContent* getPackfile(
        const String& name, const String& group);
private:
    HANDLE _archiveHandle;
    std::atomic<bool> finished = false;
    std::string _mpqName;
};