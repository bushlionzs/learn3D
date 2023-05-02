#pragma once

class OgreBlpImage
{
public:
	OgreBlpImage();
	~OgreBlpImage();
	bool load(std::shared_ptr<DataStream>& stream);
};