#pragma once

class FrameGraph;

class PassUtil
{
public:
	struct PassConfig
	{
		Ogre::SceneManager* scene;
		Ogre::Camera* cam;

		// MSAA sample count
		uint8_t msaa = 1;
		// Clear flags

		// Clear color
		Ogre::Vector4 clearColor = {};
		// Clear stencil
		uint8_t clearStencil = 0u;
	};

};