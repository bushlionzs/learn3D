#pragma once

class RenderableData
{
public:
	RenderableData(Ogre::Renderable* r);
	virtual ~RenderableData();
protected:
	Ogre::Renderable* _r;
};

class RenderFrame
{
public:
	RenderFrame();
	~RenderFrame();
};