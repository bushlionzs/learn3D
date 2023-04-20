/*!
	@file
	@author		Albert Semenov
	@date		05/2008
*/
#include <OgreHeader.h>
#include "MyGUI_OgreDataManager.h"
#include "MyGUI_OgreDiagnostic.h"
#include "MyGUI_OgreDataStream.h"
#include "OgreResourceManager.h"


namespace MyGUI
{

	OgreDataManager::OgreDataManager() :
		mAllGroups(false),
		mIsInitialise(false)
	{
	}

	void OgreDataManager::initialise(const std::string& _group)
	{
		MYGUI_PLATFORM_ASSERT(!mIsInitialise, getClassTypeName() << " initialised twice");
		MYGUI_PLATFORM_LOG(Info, "* Initialise: " << getClassTypeName());

		mGroup = _group;

		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully initialized");
		mIsInitialise = true;
	}

	void OgreDataManager::shutdown()
	{
		MYGUI_PLATFORM_ASSERT(mIsInitialise, getClassTypeName() << " is not initialised");
		MYGUI_PLATFORM_LOG(Info, "* Shutdown: " << getClassTypeName());

		MYGUI_PLATFORM_LOG(Info, getClassTypeName() << " successfully shutdown");
		mIsInitialise = false;
	}

	IDataStream* OgreDataManager::getData(const std::string& _name) const
	{
		try
		{
			Ogre::DataStreamPtr stream = Ogre::ResourceManager::getSingleton().openResource(_name, mGroup);
			OgreDataStream* data = new OgreDataStream(stream);

			return data;
		}
		catch (const Ogre::FileNotFoundException& _e)
		{
			MYGUI_PLATFORM_LOG(Warning, _e.getDescription());
		}

		return nullptr;
	}

	void OgreDataManager::freeData(IDataStream* _data)
	{
		delete _data;
	}

	bool OgreDataManager::isDataExist(const std::string& _name) const
	{
		return Ogre::ResourceManager::getSingleton().hasResource(_name);
	}

	const VectorString& OgreDataManager::getDataListNames(const std::string& _pattern) const
	{
		return getDataListNames(_pattern, false);
	}

	const VectorString& OgreDataManager::getDataListNames(const std::string& _pattern, bool _fullpath) const
	{
		static VectorString result;
		result.clear();

		return result;
	}

	const std::string& OgreDataManager::getDataPath(const std::string& _name) const
	{
		static std::string result;
		result.clear();

		const VectorString& files = getDataListNames(_name, true);
		if (!files.empty())
		{
			result = files[0];
			if (files.size() > 1)
			{
				MYGUI_PLATFORM_LOG(Warning, "There are several files with name '" << _name << "'. '" << result << "' was used.");
				MYGUI_PLATFORM_LOG(Warning, "Other candidates are:");
				for (size_t index = 1; index < files.size(); index++)
					MYGUI_PLATFORM_LOG(Warning, " - '" << files[index] << "'");
			}
		}

		return result;
	}

	void OgreDataManager::addResourceLocation(const std::string& _name, bool _recursive)
	{
		Ogre::ResourceManager::getSingleton().addDirectory(_name, mGroup, _recursive);
	}

} // namespace MyGUI
