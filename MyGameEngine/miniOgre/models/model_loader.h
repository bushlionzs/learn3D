#pragma once

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	virtual std::shared_ptr<Ogre::Mesh> loadMeshFromFile(std::shared_ptr<Ogre::DataStream>& stream)
	{
		return std::shared_ptr<Ogre::Mesh>();
	}
};