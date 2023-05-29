#pragma once
#include "OgreSerializer.h"

class TerrainInfo;

enum TerrainFileFormatEnum
{
	TFF_FILEHEADER = 0x1000,// ÎÄ¼þÍ·
	TFF_TERRAIN = 0x0100,
	TFF_GENERAL = 0x0200,
	TFF_GRIDINFO = 0x0300,
	TFF_HEIGHTMAP = 0x0400,
	TFF_LIGHTMAP = 0x0500,
};

class TerrainElementSerializer : public Serializer
{
public:
	TerrainElementSerializer();
	~TerrainElementSerializer();

	void import(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
	String readVersion(std::shared_ptr<DataStream>& stream);

	virtual void readElement(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain) {}
protected:
	String mVersion;
	String mFileType;
};

class TerrainSerializer: public TerrainElementSerializer
{
public:
	TerrainSerializer();
	~TerrainSerializer();
protected:
	virtual void readElement(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
	void readGeometryInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
	virtual void readHeightmapInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
	virtual void readGridInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
	virtual void readLightmapInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
	virtual void readExtendInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
	virtual void readImageNames(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
	virtual void readPixmap(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
	virtual void readTextureNameSet(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
	virtual void readTileInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
	virtual void readMaterialTemplate(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
	virtual void readFogInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
	virtual void readSurfaceParameter(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
};

class TerrainGeneralSerializerImpl_v1_1 : public TerrainSerializer
{
public:
	TerrainGeneralSerializerImpl_v1_1();
	~TerrainGeneralSerializerImpl_v1_1();
protected:
	virtual void readExtendInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
};

class TerrainGeneralSerializerImpl_v1_2 : public TerrainGeneralSerializerImpl_v1_1
{
public:
	TerrainGeneralSerializerImpl_v1_2();
	~TerrainGeneralSerializerImpl_v1_2();
protected:
	virtual void readLightmapInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);

	virtual void readTileInfo(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
};

class TerrainHeightMapSerializer : public TerrainElementSerializer
{
public:
	TerrainHeightMapSerializer();
	~TerrainHeightMapSerializer();

	
private:
	void readElement(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
};

class TerrainGridInfoSerializer : public TerrainElementSerializer
{
public:
	TerrainGridInfoSerializer();
	~TerrainGridInfoSerializer();

private:
	void readElement(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
};

class TerrainLightMapSerializer : public TerrainElementSerializer
{
public:
	TerrainLightMapSerializer();
	~TerrainLightMapSerializer();

private:
	void readElement(std::shared_ptr<DataStream>& stream, TerrainInfo* pTerrain);
};