#pragma once

class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();

	virtual bool loadMeshFromFile(std::shared_ptr<Ogre::DataStream>& stream, Ogre::Mesh* mesh)
	{
		return false;
	}
};