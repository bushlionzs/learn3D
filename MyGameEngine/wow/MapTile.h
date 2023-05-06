// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#pragma once

#include "map_enums.hpp"
#include "MapChunk.h"
#include "MapHeaders.h"
#include "TileWater.hpp"
#include "tile_index.hpp"
#include "AsyncObject.h"
#include <map>
#include <string>
#include <vector>

namespace math
{
  class frustum;
  struct vector_3d;
}

class World;

class MapTile : public AsyncObject
{
public:
	MapTile( int x0
         , int z0
         , std::string const& pFilename
         , bool pBigAlpha
         , bool pLoadModels
         , bool use_mclq_green_lava
         , bool reloading_tile
         , World*
         , tile_mode mode = tile_mode::edit
         );
  ~MapTile();

  void finishLoading();

  //! \todo on destruction, unload ModelInstances and WMOInstances on this tile:
  // a) either keep up the information what tiles the instances are on at all times
  //    (even while moving), to then check if all tiles it was on were unloaded, or
  // b) do the reference count lazily by iterating over all instances and checking
  //    what MapTiles they span. if any of those tiles is still loaded, keep it,
  //    otherwise remove it.
  //
  // I think b) is easier. It only requires
  // `std::set<C2iVector> XInstance::spanning_tiles() const` followed by
  // `if_none (isTileLoaded (x, y)): unload instance`, which is way easier than
  // constantly updating the reference counters.
  // Note that both approaches do not cover the issue that the instance might not
  // be saved to any tile, thus the movement might have been lost.

	//! \brief Get the maximum height of terrain on this map tile.
	float getMaxHeight();

  void convert_alphamap(bool to_big_alpha);

  //! \brief Get chunk for sub offset x,z.
  MapChunk* getChunk(unsigned int x, unsigned int z);
  //! \todo map_index style iterators
  std::vector<MapChunk*> chunks_in_range (Ogre::Vector3 const& pos, float radius) const;

  const tile_index index;
  float xbase, zbase;

  std::atomic<bool> changed;

  bool GetVertex(float x, float z, Ogre::Vector3 *V);

  void saveTile(World*);
	void CropWater();

  bool isTile(int pX, int pZ);


  bool has_model(uint32_t uid) const
  {
    return std::find(uids.begin(), uids.end(), uid) != uids.end();
  }

  void remove_model(uint32_t uid);
  void add_model(uint32_t uid);

  TileWater Water;

  bool tile_is_being_reloaded() const { return _tile_is_being_reloaded; }

private:
  tile_mode _mode;
  bool _tile_is_being_reloaded;
  bool finished;
  // MFBO:
  Ogre::Vector3 mMinimumValues[3 * 3];
  Ogre::Vector3 mMaximumValues[3 * 3];

  bool _mfbo_buffer_are_setup = false;


  // MHDR:
  int mFlags;
  bool mBigAlpha;

  // Data to be loaded and later unloaded.
  std::vector<std::string> mTextureFilenames;
  std::vector<std::string> mModelFilenames;
  std::vector<std::string> mWMOFilenames;
  
  std::vector<uint32_t> uids;

  std::unique_ptr<MapChunk> mChunks[16][16];
  std::vector<TileWater*> chunksLiquids; //map chunks liquids for old style water render!!! (Not MH2O)

  bool _load_models;
  World* _world;

  friend class MapChunk;
  friend class TextureSet;
};
