#pragma once

#include "OgreSingleton.h"
#include <MyGUI.h>
struct CEGUIImage
{
    String _imagename;
    MyGUI::IntCoord _coord;
    MyGUI::IntSize _size;
};

struct CEGUIImageSet
{
    std::string _groupName;
    std::string _mageFilename;
    int32_t _nativeHorzRes;
    int32_t _ativeVertRes;
    std::map<String, CEGUIImage> _imageMap;
};



class CEGUIResourceManager : public Ogre::Singleton<CEGUIResourceManager>
{
public:
    CEGUIResourceManager();
    ~CEGUIResourceManager();

    bool load(const std::string& name);

    CEGUIImage& getImageInfo(const String& imageset, const String& imagename);

    CEGUIImage& getIconImageInfo(const String& iconname);
private:
    std::map<String, CEGUIImageSet*> mGroupMap;

    std::map<String, CEGUIImageSet*> mIconMap;
    CEGUIImage mDummy;
};