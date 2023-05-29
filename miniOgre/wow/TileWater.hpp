// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#pragma once


#include "ChunkWater.hpp"
#include "MapHeaders.h"
#include "tool_enums.hpp"


#include <memory>

class MapTile;
class sExtendableArray;

class TileWater
{
public:
  TileWater(MapTile *pTile, float pXbase, float pZbase, bool use_mclq_green_lava);

  ChunkWater* getChunk(int x, int z);

  void readFromFile(std::shared_ptr<DataStream>& stream, size_t basePos);
  void saveToFile(sExtendableArray &lADTFile, int &lMHDR_Position, int &lCurrentPosition);

  bool hasData(size_t layer);
  void CropMiniChunk(int x, int z, MapChunk* chunkTerrain);

  void autoGen(float factor);

  void setType(int type, size_t layer);
  int getType(size_t layer);

private:

  MapTile *tile;
  std::unique_ptr<ChunkWater> chunks[16][16];

  float xbase;
  float zbase;
};
