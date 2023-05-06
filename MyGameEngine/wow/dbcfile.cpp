#include "dbcfile.h"

AreaDB gAreaDB;
MapDB gMapDB;
LoadingScreensDB gLoadingScreensDB;
LightDB gLightDB;
LightParamsDB gLightParamsDB;
LightSkyboxDB gLightSkyboxDB;
LightIntBandDB gLightIntBandDB;
LightFloatBandDB gLightFloatBandDB;
GroundEffectDoodadDB gGroundEffectDoodadDB;
GroundEffectTextureDB gGroundEffectTextureDB;
LiquidTypeDB gLiquidTypeDB;

DBCFile::DBCFile(const std::string&filename) : filename(filename)
{
	data = NULL;
	stringTable = NULL;
	recordSize = 0;
	recordCount = 0;
	fieldCount = 0;
	stringSize = 0;
}

bool DBCFile::open(Ogre::DataStream* stream)
{
	enum FileType {
		FT_UNK,
		FT_WDBC,
		FT_WDB2,
	};
	int db_type = FT_UNK;
	
	// Need some error checking, otherwise an unhandled exception error occurs
	// if people screw with the data path.
	if (stream->eof())
		return false;

	char header[5];
	unsigned int na,nb,es,ss;

	stream->read(header, 4); // File Header

	if (strncmp(header, "WDBC", 4) == 0)
		db_type = FT_WDBC;
	else if (strncmp(header, "WDB2", 4) == 0)
		db_type = FT_WDB2;

	if (db_type == FT_UNK) {
		data = NULL;
		return false;
	}

	//assert(header[0]=='W' && header[1]=='D' && header[2]=='B' && header[3] == 'C');

	stream->read(&na,4); // Number of records
	stream->read(&nb,4); // Number of fields
	stream->read(&es,4); // Size of a record
	stream->read(&ss,4); // String size

	if (db_type == FT_WDB2) {
		stream->seekRelative(28);
		// just some buggy check
		unsigned int check;
		stream->read(&check, 4);
		if (check == 6) // wrong place
			stream->seekRelative(-20);
		else // check == 17, right place
			stream->seekRelative(-4);
	}
	
	recordSize = es;
	recordCount = na;
	fieldCount = nb;
	stringSize = ss;
	//assert(fieldCount*4 == recordSize);
	// not always true, but it works fine till now
	assert(fieldCount*4 >= recordSize);

	data = new unsigned char[recordSize*recordCount+stringSize];
	stringTable = data + recordSize*recordCount;
	if (db_type == FT_WDB2) {
		stream->seek(stream->getStreamLength() - recordSize*recordCount - stringSize);
	}
	stream->read(data, recordSize*recordCount+stringSize);
	return true;
}

DBCFile::~DBCFile()
{
	delete [] data;
}

DBCFile::Record DBCFile::getRecord(size_t id)
{
	//assert(data);
	return Record(*this, data + id*recordSize);
}

DBCFile::Iterator DBCFile::begin()
{
	//assert(data);
	return Iterator(*this, data);
}
DBCFile::Iterator DBCFile::end()
{
	//assert(data);
	return Iterator(*this, stringTable);
}

