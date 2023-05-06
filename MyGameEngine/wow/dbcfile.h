#ifndef DBCFILE_H
#define DBCFILE_H

#include <cassert>
#include <string>
#include "OgreDataStream.h"
class DBCFile
{
public:
	DBCFile(const std::string &filename);
	~DBCFile();

	// Open database. It must be openened before it can be used.
	bool open(Ogre::DataStream* stream);

	// TODO: Add a close function?

	// Database exceptions
	class Exception
	{
	public:
		Exception(const std::string&message): message(message)
		{ }
		virtual ~Exception()
		{ }
		const std::string&getMessage() {return message;}
	private:
		std::string message;
	};

	// 
	class NotFound: public Exception
	{
	public:
		NotFound(): Exception("Key was not found")
		{ }
	};

	// Iteration over database
	class Iterator;
	class Record
	{
	public:
		Record& operator= (const Record& r)
		{
            file = r.file;
			offset = r.offset;
			return *this;
		}
		float getFloat(size_t field) const
		{
			assert(field < file.fieldCount);
			return *reinterpret_cast<float*>(offset+field*4);
		}
		unsigned int getUInt(size_t field) const
		{
			assert(field < file.fieldCount);
			return *reinterpret_cast<unsigned int*>(offset+(field*4));
		}
		int getInt(size_t field) const
		{
			assert(field < file.fieldCount);
			return *reinterpret_cast<int*>(offset+field*4);
		}
		unsigned char getByte(size_t ofs) const
		{
			assert(ofs < file.recordSize);
			return *reinterpret_cast<unsigned char*>(offset+ofs);
		}
		std::string getString(size_t field) const
		{
			assert(field < file.fieldCount);
			size_t stringOffset = getUInt(field);
			if (stringOffset >= file.stringSize)
				stringOffset = 0;
			assert(stringOffset < file.stringSize);
			//char * tmp = (char*)file.stringTable + stringOffset;
			//unsigned char * tmp2 = file.stringTable + stringOffset;
			return std::string(reinterpret_cast<char*>(file.stringTable + stringOffset));
		}
	private:
		DBCFile &file;
		unsigned char *offset;
		Record(DBCFile &file, unsigned char *offset): file(file), offset(offset) {}

		friend class DBCFile;
		friend class Iterator;
	};

	/* Iterator that iterates over records */
	class Iterator
	{
	public:
		Iterator(DBCFile &file, unsigned char *offset): 
			record(file, offset) {}
		/// Advance (prefix only)
		Iterator & operator++() { 
			record.offset += record.file.recordSize;
			return *this; 
		}	
		/// Return address of current instance
		Record const & operator*() const { return record; }
		const Record* operator->() const {
			return &record;
		}
		/// Comparison
		bool operator==(const Iterator &b) const
		{
			return record.offset == b.record.offset;
		}
		bool operator!=(const Iterator &b) const
		{
			return record.offset != b.record.offset;
		}
	private:
		Record record;
	};

	// Get record by id
	Record getRecord(size_t id);
	/// Get begin iterator over records
	Iterator begin();
	/// Get begin iterator over records
	Iterator end();
	/// Trivial
	size_t getRecordCount() const { return recordCount; }
	size_t getFieldCount() const { return fieldCount; }
	std::string getFilename() { return filename; }
	size_t size() const { return recordCount; }

private:
	std::string filename;
	size_t recordSize;
	size_t recordCount;
	size_t fieldCount;
	size_t stringSize;
	unsigned char *data;
	unsigned char *stringTable;
};

class AreaDB : public DBCFile
{
public:
	AreaDB() :
		DBCFile("DBFilesClient\\AreaTable.dbc")
	{ }

	/// Fields
	static const size_t AreaID = 0;    // uint
	static const size_t Continent = 1;  // uint
	static const size_t Region = 2;    // uint [AreaID]
	static const size_t Flags = 4;    // bit field
	static const size_t Name = 11;    // localisation string

	static std::string getAreaName(int pAreaID);
	static std::uint32_t get_area_parent(int area_id);
};

class MapDB : public DBCFile
{
public:
	MapDB() :
		DBCFile("DBFilesClient\\Map.dbc")
	{ }

	/// Fields
	static const size_t MapID = 0;        // uint
	static const size_t InternalName = 1;    // string
	static const size_t AreaType = 2;      // uint
	static const size_t IsBattleground = 4;    // uint
	static const size_t Name = 5;        // loc

	static const size_t LoadingScreen = 57;    // uint [LoadingScreen]
	static std::string getMapName(int pMapID);
};

class LoadingScreensDB : public DBCFile
{
public:
	LoadingScreensDB() :
		DBCFile("DBFilesClient\\LoadingScreens.dbc")
	{ }

	/// Fields
	static const size_t ID = 0;        // uint
	static const size_t Name = 1;      // string
	static const size_t Path = 2;      // string
};

class LightDB : public DBCFile
{
public:
	LightDB() :
		DBCFile("DBFilesClient\\Light.dbc")
	{ }

	/// Fields
	static const size_t ID = 0;        // uint
	static const size_t Map = 1;      // uint
	static const size_t PositionX = 2;    // float
	static const size_t PositionY = 3;    // float
	static const size_t PositionZ = 4;    // float
	static const size_t RadiusInner = 5;  // float
	static const size_t RadiusOuter = 6;  // float
	static const size_t DataIDs = 7;    // uint[8]
};

class LightParamsDB : public DBCFile {
public:
	LightParamsDB() :
		DBCFile("DBFilesClient\\LightParams.dbc")
	{ }

	/// Fields
	static const size_t ID = 0;        // uint
	static const size_t skybox = 2;      // uint ref to LightSkyBox
	static const size_t water_shallow_alpha = 5;
	static const size_t water_deep_alpha = 6;
	static const size_t ocean_shallow_alpha = 7;
	static const size_t ocean_deep_alpha = 8;
};

class LightSkyboxDB : public DBCFile
{
public:
	LightSkyboxDB() :
		DBCFile("DBFilesClient\\LightSkybox.dbc")
	{ }

	/// Fields
	static const size_t ID = 0;        // uint
	static const size_t filename = 1;    // string
	static const size_t flags = 2;      // uint
};

class LightIntBandDB : public DBCFile
{
public:
	LightIntBandDB() :
		DBCFile("DBFilesClient\\LightIntBand.dbc")
	{ }

	/// Fields
	static const size_t ID = 0;        // uint
	static const size_t Entries = 1;    // uint
	static const size_t Times = 2;      // uint
	static const size_t Values = 18;    // uint
};

class LightFloatBandDB : public DBCFile
{
public:
	LightFloatBandDB() :
		DBCFile("DBFilesClient\\LightFloatBand.dbc")
	{ }

	/// Fields
	static const size_t ID = 0;        // uint
	static const size_t Entries = 1;    // uint
	static const size_t Times = 2;      // uint
	static const size_t Values = 18;    // float
};

class GroundEffectTextureDB : public DBCFile
{
public:
	GroundEffectTextureDB() :
		DBCFile("DBFilesClient\\GroundEffectTexture.dbc")
	{ }

	/// Fields
	static const size_t ID = 0;        // uint
	static const size_t Doodads = 1;    // uint[4]
	static const size_t Weights = 5;    // uint[4]
	static const size_t Amount = 9;      // uint
	static const size_t TerrainType = 10;  // uint
};

class GroundEffectDoodadDB : public DBCFile
{
public:
	GroundEffectDoodadDB() :
		DBCFile("DBFilesClient\\GroundEffectDoodad.dbc")
	{ }

	/// Fields
	static const size_t ID = 0;        // uint
	static const size_t InternalID = 1;    // uint
	static const size_t Filename = 2;    // string
};

class LiquidTypeDB : public DBCFile
{
public:
	LiquidTypeDB() :
		DBCFile("DBFilesClient\\LiquidType.dbc")
	{ }

	/// Fields
	static const size_t ID = 0;        // uint
	static const size_t Name = 1;      // string
	static const size_t Type = 3;      // uint
	static const size_t ShaderType = 14;  // uint
	static const size_t TextureFilenames = 15;    // string[6]
	static const size_t TextureTilesPerBlock = 23;  // uint
	static const size_t Rotation = 24;  // uint
	static const size_t AnimationX = 23;  // uint
	static const size_t AnimationY = 24;  // uint

	static int getLiquidType(int pID);
	static std::string getLiquidName(int pID);
};

class AnimDB : public DBCFile
{
public:
	AnimDB() : DBCFile("DBFilesClient\\AnimationData.dbc") {}
	~AnimDB() {}

	/// Fields
	static const size_t AnimID = 0;		// uint
	static const size_t Name = 1;		// string
	// static const size_t WeaponState = 2;	// int, 32 = pull weapons out during animation. 16 and 4 weapons are put back.
	// static const size_t Flags = 3;
	// static const size_t Unkonwn = 4;
	// static const size_t Preceeding; // The animation, preceeding this one.
	// static const size_t RealId; // Same as ID for normal animations. (WotLK)
	// static const size_t Group; // 0 for normal, 3 for fly. (WotLK)

	Record getByAnimID(unsigned int id);
};

extern AreaDB gAreaDB;
extern MapDB gMapDB;
extern LoadingScreensDB gLoadingScreensDB;
extern LightDB gLightDB;
extern LightParamsDB gLightParamsDB;
extern LightSkyboxDB gLightSkyboxDB;
extern LightIntBandDB gLightIntBandDB;
extern LightFloatBandDB gLightFloatBandDB;
extern GroundEffectDoodadDB gGroundEffectDoodadDB;
extern GroundEffectTextureDB gGroundEffectTextureDB;
extern LiquidTypeDB gLiquidTypeDB;
extern AnimDB gAnimDB;
#endif
