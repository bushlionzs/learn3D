// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#pragma once

#include "OgreHeader.h"
#include "liquid_layer.hpp"
#include "tool_enums.hpp"
#include "MapHeaders.h"


#include <vector>
#include <set>

class MPQFile;
class sExtendableArray;
class MapChunk;

class ChunkWater
{
public:
  ChunkWater() = delete;
  explicit ChunkWater(float x, float z, bool use_mclq_green_lava);

  ChunkWater (ChunkWater const&) = delete;
  ChunkWater (ChunkWater&&) = delete;
  ChunkWater& operator= (ChunkWater const&) = delete;
  ChunkWater& operator= (ChunkWater&&) = delete;

  void from_mclq(std::vector<mclq>& layers);
  void fromFile(std::shared_ptr<DataStream>& stream, size_t basePos);
  void save(sExtendableArray& adt, int base_pos, int& header_pos, int& current_pos);

  void autoGen(MapChunk* chunk, float factor);
  void CropWater(MapChunk* chunkTerrain);

  void setType(int type, size_t layer);
  int getType(size_t layer) const;
  bool hasData(size_t layer) const;



  float xbase, zbase;

private:
  std::vector<Ogre::Vector3> _intersect_points;

  Ogre::Vector3 vmin, vmax, vcenter;
  bool _use_mclq_green_lava;

  // remove empty layers
  void cleanup();
  // update every layer's render
  void update_layers();

  void copy_height_to_layer(
      liquid_layer& target, 
      Ogre::Vector3 const& pos,
      float radius);


  MH2O_Render Render;

  std::vector<liquid_layer> _layers;
};
