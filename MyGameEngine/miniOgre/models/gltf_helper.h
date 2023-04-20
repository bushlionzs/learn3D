#pragma once

#include "OgreHardwareVertexBuffer.h"
#include <dxgiformat.h>
int GetFormatSize(int id);
VertexElementType GetEngineFormat(int id);
VertexElementSemantic GetEngineSemantic(const std::string& semantic);
int GetTypeSize(int type);
int GetComponentTypeSize(int componentType);
DXGI_FORMAT GetFormat(int type, int id);
int GetStrideFromFormat(int type, int id);