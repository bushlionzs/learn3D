// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#include "OgreHeader.h"
#include "MapChunk.h"
#include "MapTile.h"
#include "map_index.hpp"
#include "OgreResourceManager.h"
#include "OgreDataStream.h"
#include "Misc.h"
#include "WMOInstance.h"
#include <forward_list>

MapIndex::MapIndex (const std::string &pBasename, int map_id, World* world)
  : basename(pBasename)
  , _map_id (map_id)
  , _last_unload_time((clock() / CLOCKS_PER_SEC)) // to not try to unload right away
  , mBigAlpha(false)
  , mHasAGlobalWMO(false)
  , noadt(false)
  , changed(false)
  , _sort_models_by_size_class(false)
  , highestGUID(0)
  , _world (world)
{
  std::stringstream filename;
  filename << "World\\Maps\\" << basename << "\\" << basename << ".wdt";

  auto stream = ResourceManager::getSingleton().openResource(filename.str());
  uint32_t fourcc;
  uint32_t size;

  // - MVER ----------------------------------------------

  uint32_t version;

  stream->read(&fourcc, 4);
  stream->read(&size, 4);
  stream->read(&version, 4);

  //! \todo find the correct version of WDT files.
  assert(fourcc == 'MVER' && version == 18);

  // - MHDR ----------------------------------------------

  stream->read(&fourcc, 4);
  stream->read(&size, 4);

  assert(fourcc == 'MPHD');

  stream->read(&mphd, sizeof(MPHD));

  mHasAGlobalWMO = mphd.flags & 1;
  mBigAlpha = (mphd.flags & 4) != 0;
  _sort_models_by_size_class = mphd.flags & 0x8;

  if (!(mphd.flags & FLAG_SHADING))
  {
    mphd.flags |= FLAG_SHADING;
    changed = true;
  }

  // - MAIN ----------------------------------------------

  stream->read(&fourcc, 4);
  stream->seekRelative(4);

  assert(fourcc == 'MAIN');

  /// this is the theory. Sadly, we are also compiling on 64 bit machines with size_t being 8 byte, not 4. Therefore, we can't do the same thing, Blizzard does in its 32bit executable.
  //theFile.read( &(mTiles[0][0]), sizeof( 8 * 64 * 64 ) );

  for (int j = 0; j < 64; ++j)
  {
      for (int i = 0; i < 64; ++i)
      {
          stream->read(&mTiles[j][i].flags, 4);
          stream->seekRelative(4);

          std::stringstream adt_filename;
          adt_filename << "World\\Maps\\" << basename << "\\" << basename << "_" << i << "_" << j << ".adt";

          mTiles[j][i].tile = nullptr;
          mTiles[j][i].onDisc = ResourceManager::getSingleton().getResource(adt_filename.str()) != nullptr;

          if (mTiles[j][i].onDisc && !(mTiles[j][i].flags & 1))
          {
              mTiles[j][i].flags |= 1;
              changed = true;
          }

      }

      if (!stream->eof() && mHasAGlobalWMO)
      {
          //! \note We actually don't load WMO only worlds, so we just stop reading here, k?
          //! \bug MODF reads wrong. The assertion fails every time. Somehow, it keeps being MWMO. Or are there two blocks?
          //! \nofuckingbug  on eof read returns just without doing sth to the var and some wdts have a MWMO without having a MODF so only checking for eof above is not enough

          mHasAGlobalWMO = false;

          // - MWMO ----------------------------------------------

          stream->read(&fourcc, 4);
          stream->read(&size, 4);

          assert(fourcc == 'MWMO');

          globalWMOName = std::string(stream->getCurrentStreamData(), size);
          stream->seekRelative(size);

          // - MODF ----------------------------------------------

          stream->read(&fourcc, 4);
          stream->read(&size, 4);

          assert(fourcc == 'MODF');

          stream->read(&wmoEntry, sizeof(ENTRY_MODF));
      }
  }

}

void MapIndex::saveall(World* world)
{
  
}

void MapIndex::save()
{
 
}

void MapIndex::enterTile(const tile_index& tile)
{
  if (!hasTile(tile))
  {
    noadt = true;
    return;
  }

  noadt = false;
  int cx = tile.x;
  int cz = tile.z;

  for (int pz = std::max(cz - 1, 0); pz < std::min(cz + 2, 63); ++pz)
  {
    for (int px = std::max(cx - 1, 0); px < std::min(cx + 2, 63); ++px)
    {
      loadTile(tile_index(px, pz));
    }
  }
}

void MapIndex::update_model_tile(const tile_index& tile, model_update type, uint32_t uid)
{
  if (!hasTile(tile))
  {
    return;
  }

  MapTile* adt = loadTile(tile);
  adt->wait_until_loaded();
  adt->changed = true;

  if (type == model_update::add)
  {
    adt->add_model(uid);
  }
  else if(type == model_update::remove)
  {
    adt->remove_model(uid);
  }
}

void MapIndex::setChanged(const tile_index& tile)
{
  MapTile* mTile = loadTile(tile);

  if (!!mTile)
  {
    mTile->changed = true;
  }
}

void MapIndex::setChanged(MapTile* tile)
{
  setChanged(tile->index);
}

void MapIndex::unsetChanged(const tile_index& tile)
{
  // change the changed flag of the map tile
  if (hasTile(tile))
  {
    mTiles[tile.z][tile.x].tile->changed = false;
  }
}

bool MapIndex::has_unsaved_changes(const tile_index& tile) const
{
  return (tileLoaded(tile) ? getTile(tile)->changed.load() : false);
}

void MapIndex::setFlag(bool to, Ogre::Vector3 const& pos, uint32_t flag)
{
  tile_index tile(pos);

  if (tileLoaded(tile))
  {
    setChanged(tile);

    int cx = (pos.x - tile.x * TILESIZE) / CHUNKSIZE;
    int cz = (pos.z - tile.z * TILESIZE) / CHUNKSIZE;

    getTile(tile)->getChunk(cx, cz)->setFlag(to, flag);
  }
}

MapTile* MapIndex::loadTile(const tile_index& tile, bool reloading)
{
  if (!hasTile(tile))
  {
    return nullptr;
  }

  if (tileLoaded(tile) || tileAwaitingLoading(tile))
  {
    return mTiles[tile.z][tile.x].tile.get();
  }

  std::stringstream filename;
  filename << "World\\Maps\\" << basename << "\\" << basename << "_" << tile.x << "_" << tile.z << ".adt";

  if (!ResourceManager::getSingleton().hasResource(filename.str()))
  {
    return nullptr;
  }
  
  mTiles[tile.z][tile.x].tile = std::make_unique<MapTile> (tile.x, tile.z, filename.str(), mBigAlpha, true, use_mclq_green_lava(), reloading, _world);

  MapTile* adt = mTiles[tile.z][tile.x].tile.get();

  return adt;
}

void MapIndex::reloadTile(const tile_index& tile)
{
  if (tileLoaded(tile))
  {
    mTiles[tile.z][tile.x].tile.reset();
    loadTile(tile, true);
  }
}

void MapIndex::unloadTiles(const tile_index& tile)
{
  if (((clock() / CLOCKS_PER_SEC) - _last_unload_time) > _unload_interval)
  {
    for (MapTile* adt : loaded_tiles())
    {
      if (tile.dist(adt->index) > _unload_dist)
      {
        //Only unload adts not marked to save
        if (!adt->changed.load())
        {
          unloadTile(adt->index);
        }
      }
    }

    _last_unload_time = clock() / CLOCKS_PER_SEC;
  }
}

void MapIndex::unloadTile(const tile_index& tile)
{
  // unloads a tile with givn cords
  if (tileLoaded(tile))
  {
    mTiles[tile.z][tile.x].tile = nullptr;
  }
}

void MapIndex::markOnDisc(const tile_index& tile, bool mto)
{
  if(tile.is_valid())
  {
    mTiles[tile.z][tile.x].onDisc = mto;
  }
}

bool MapIndex::isTileExternal(const tile_index& tile) const
{
  // is onDisc
  return tile.is_valid() && mTiles[tile.z][tile.x].onDisc;
}

void MapIndex::saveTile(const tile_index& tile, World* world)
{
  
}

void MapIndex::saveChanged (World* world)
{
  
}

bool MapIndex::hasAGlobalWMO()
{
  return mHasAGlobalWMO;
}


bool MapIndex::hasTile(const tile_index& tile) const
{
  return tile.is_valid() && (mTiles[tile.z][tile.x].flags & 1);
}

bool MapIndex::tileAwaitingLoading(const tile_index& tile) const
{
  return hasTile(tile) && mTiles[tile.z][tile.x].tile && !mTiles[tile.z][tile.x].tile->finishedLoading();
}

bool MapIndex::tileLoaded(const tile_index& tile) const
{
  return hasTile(tile) && mTiles[tile.z][tile.x].tile && mTiles[tile.z][tile.x].tile->finishedLoading();
}

bool MapIndex::hasAdt()
{
  return noadt;
}

void MapIndex::setAdt(bool value)
{
  noadt = value;
}

MapTile* MapIndex::getTile(const tile_index& tile) const
{
  return (tile.is_valid() ? mTiles[tile.z][tile.x].tile.get() : nullptr);
}

MapTile* MapIndex::getTileAbove(MapTile* tile) const
{
  tile_index above(tile->index.x, tile->index.z - 1);
  if (tile->index.z == 0 || (!tileLoaded(above) && !tileAwaitingLoading(above)))
  {
    return nullptr;
  }

  MapTile* tile_above = mTiles[tile->index.z - 1][tile->index.x].tile.get();
  tile_above->wait_until_loaded();

  return tile_above;
}

MapTile* MapIndex::getTileLeft(MapTile* tile) const
{
  tile_index left(tile->index.x - 1, tile->index.z);
  if (tile->index.x == 0 || (!tileLoaded(left) && !tileAwaitingLoading(left)))
  {
    return nullptr;
  }

  MapTile* tile_left = mTiles[tile->index.z][tile->index.x - 1].tile.get();
  tile_left->wait_until_loaded();

  return tile_left;
}

uint32_t MapIndex::getFlag(const tile_index& tile) const
{
  return (tile.is_valid() ? mTiles[tile.z][tile.x].flags : 0);
}

void MapIndex::convert_alphamap(bool to_big_alpha)
{
  mBigAlpha = to_big_alpha;
  if (to_big_alpha)
  {
    mphd.flags |= 4;
  }
  else
  {
    mphd.flags &= 0xFFFFFFFB;
  }
}


uint32_t MapIndex::getHighestGUIDFromFile(const std::string& pFilename) const
{
	uint32_t highGUID = 0;
    auto guidstream = ResourceManager::getSingleton().openResource(pFilename);

    if (!guidstream)
    {
      return highGUID;
    }

    uint32_t fourcc;
    uint32_t size;

    MHDR Header;

    // - MVER ----------------------------------------------

    uint32_t version;

    guidstream->read(&fourcc, 4);
    guidstream->seekRelative(4);
    guidstream->read(&version, 4);

    assert(fourcc == 'MVER' && version == 18);

    // - MHDR ----------------------------------------------

    guidstream->read(&fourcc, 4);
    guidstream->seekRelative(4);

    assert(fourcc == 'MHDR');

    guidstream->read(&Header, sizeof(MHDR));

    // - MDDF ----------------------------------------------

    guidstream->seek(Header.mddf + 0x14);
    guidstream->read(&fourcc, 4);
    guidstream->read(&size, 4);

    assert(fourcc == 'MDDF');

    ENTRY_MDDF const* mddf_ptr = reinterpret_cast<ENTRY_MDDF const*>(guidstream->getCurrentStreamData());
    for (unsigned int i = 0; i < size / sizeof(ENTRY_MDDF); ++i)
    {
        highGUID = std::max(highGUID, mddf_ptr[i].uniqueID);
    }

    // - MODF ----------------------------------------------

    guidstream->seek(Header.modf + 0x14);
    guidstream->read(&fourcc, 4);
    guidstream->read(&size, 4);

    assert(fourcc == 'MODF');

    ENTRY_MODF const* modf_ptr = reinterpret_cast<ENTRY_MODF const*>(guidstream->getCurrentStreamData());
    for (unsigned int i = 0; i < size / sizeof(ENTRY_MODF); ++i)
    {
        highGUID = std::max(highGUID, modf_ptr[i].uniqueID);
    }

    return highGUID;
}

uint32_t MapIndex::newGUID()
{
  std::unique_lock<std::mutex> lock (_mutex);

#ifdef USE_MYSQL_UID_STORAGE
  QSettings settings;

  if (settings->value ("project/mysql/enabled", false).toBool())
  {
    mysql::updateUIDinDB(_map_id, highestGUID + 1); // update the highest uid in db, note that if the user don't save these uid won't be used (not really a problem tho) 
  }
#endif
  return ++highestGUID;
}

uid_fix_status MapIndex::fixUIDs (World* world, bool cancel_on_model_loading_error)
{
  // pre-cond: mTiles[z][x].flags are set

  // unload any previously loaded tile, although there shouldn't be as
  // the fix is executed before loading the map
  for (int z = 0; z < 64; ++z)
  {
    for (int x = 0; x < 64; ++x)
    {
      if (mTiles[z][x].tile)
      {
        MapTile* tile = mTiles[z][x].tile.get();

        // don't unload half loaded tiles
        tile->wait_until_loaded();

        unloadTile(tile->index);
      }
    }
  }

  _uid_fix_all_in_progress = true;

  std::forward_list<ENTRY_MDDF> models;
  std::forward_list<ENTRY_MODF> wmos;

  for (int z = 0; z < 64; ++z)
  {
    for (int x = 0; x < 64; ++x)
    {
      if (!(mTiles[z][x].flags & 1))
      {
        continue;
      }

      std::stringstream filename;
      filename << "World\\Maps\\" << basename << "\\" << basename << "_" << x << "_" << z << ".adt";
      auto adtstream = ResourceManager::getSingleton().openResource(filename.str());

      if (!adtstream)
      {
        continue;
      }

      Ogre::Vector3 tileExtents[2];
      tileExtents[0] = { x*TILESIZE, 0, z*TILESIZE };
      tileExtents[1] = { (x+1)*TILESIZE, 0, (z+1)*TILESIZE };

      std::forward_list<ENTRY_MDDF> modelEntries;
      std::forward_list<ENTRY_MODF> wmoEntries;
      std::vector<std::string> modelFilenames;
      std::vector<std::string> wmoFilenames;

      uint32_t fourcc;
      uint32_t size;

      MHDR Header;

      // - MVER ----------------------------------------------
      uint32_t version;
      adtstream->read(&fourcc, 4);
      adtstream->seekRelative(4);
      adtstream->read(&version, 4);
      assert(fourcc == 'MVER' && version == 18);

      // - MHDR ----------------------------------------------
      adtstream->read(&fourcc, 4);
      adtstream->seekRelative(4);
      assert(fourcc == 'MHDR');
      adtstream->read(&Header, sizeof(MHDR));

      // - MDDF ----------------------------------------------
      adtstream->seek(Header.mddf + 0x14);
      adtstream->read(&fourcc, 4);
      adtstream->read(&size, 4);
      assert(fourcc == 'MDDF');

      ENTRY_MDDF const* mddf_ptr = reinterpret_cast<ENTRY_MDDF const*>(adtstream->getCurrentStreamData());

      for (unsigned int i = 0; i < size / sizeof(ENTRY_MDDF); ++i)
      {
        bool add = true;
        ENTRY_MDDF const& mddf = mddf_ptr[i];

        if (!pointInside({ mddf.pos[0], 0, mddf.pos[2] }, tileExtents))
        {
          continue;
        }

        // check for duplicates
        for (ENTRY_MDDF& entry : modelEntries)
        {
          if ( mddf.nameID == entry.nameID
            && misc::float_equals(mddf.pos[0], entry.pos[0])
            && misc::float_equals(mddf.pos[1], entry.pos[1])
            && misc::float_equals(mddf.pos[2], entry.pos[2])
            && misc::float_equals(mddf.rot[0], entry.rot[0])
            && misc::float_equals(mddf.rot[1], entry.rot[1])
            && misc::float_equals(mddf.rot[2], entry.rot[2])
            && mddf.scale == entry.scale
            )
          {
            add = false;
            break;
          }
        }

        if (add)
        {
          modelEntries.emplace_front(mddf);
        }
      }

      // - MODF ----------------------------------------------
      adtstream->seek(Header.modf + 0x14);
      adtstream->read(&fourcc, 4);
      adtstream->read(&size, 4);
      assert(fourcc == 'MODF');

      ENTRY_MODF const* modf_ptr = reinterpret_cast<ENTRY_MODF const*>(adtstream->getCurrentStreamData());

      for (unsigned int i = 0; i < size / sizeof(ENTRY_MODF); ++i)
      {
        bool add = true;
        ENTRY_MODF const& modf = modf_ptr[i];

        if (!pointInside({ modf.pos[0], 0, modf.pos[2] }, tileExtents))
        {
          continue;
        }

        // check for duplicates
        for (ENTRY_MODF& entry : wmoEntries)
        {
          if (modf.nameID == entry.nameID
            && misc::float_equals(modf.pos[0], entry.pos[0])
            && misc::float_equals(modf.pos[1], entry.pos[1])
            && misc::float_equals(modf.pos[2], entry.pos[2])
            && misc::float_equals(modf.rot[0], entry.rot[0])
            && misc::float_equals(modf.rot[1], entry.rot[1])
            && misc::float_equals(modf.rot[2], entry.rot[2])
            )
          {
            add = false;
            break;
          }
        }

        if (add)
        {
          wmoEntries.emplace_front(modf);
        }
      }

      // - MMDX ----------------------------------------------
      adtstream->seek(Header.mmdx + 0x14);
      adtstream->read(&fourcc, 4);
      adtstream->read(&size, 4);
      assert(fourcc == 'MMDX');

      {
        char const* lCurPos = reinterpret_cast<char const*>(adtstream->getCurrentStreamData());
        char const* lEnd = lCurPos + size;

        while (lCurPos < lEnd)
        {
          modelFilenames.push_back(std::string(lCurPos));
          lCurPos += strlen(lCurPos) + 1;
        }
      }

      // - MWMO ----------------------------------------------
      adtstream->seek(Header.mwmo + 0x14);
      adtstream->read(&fourcc, 4);
      adtstream->read(&size, 4);
      assert(fourcc == 'MWMO');

      {
        char const* lCurPos = reinterpret_cast<char const*>(adtstream->getCurrentStreamData());
        char const* lEnd = lCurPos + size;

        while (lCurPos < lEnd)
        {
          wmoFilenames.push_back(std::string(lCurPos));
          lCurPos += strlen(lCurPos) + 1;
        }
      }

      for (ENTRY_MDDF& entry : modelEntries)
      {
        models.push_front(entry);
      }
      for (ENTRY_MODF& entry : wmoEntries)
      {
        wmos.push_front(entry);
      }
    }
  }

  // set all uids
  // for each tile save the m2/wmo present inside
  highestGUID = 0;

  std::map<std::size_t, std::map<std::size_t, std::forward_list<std::uint32_t>>> uids_per_tile;

  bool loading_error = false;

  for (auto& entry : models)
  {
    
  }

  models.clear();

  for (auto& entry : wmos)
  {
    
  }

  wmos.clear();

  if (cancel_on_model_loading_error && loading_error)
  {
    return uid_fix_status::failed;
  }

  // load each tile without the models and
  // save them with the models with the new uids
  for (int z = 0; z < 64; ++z)
  {
    for (int x = 0; x < 64; ++x)
    {
      if (!(mTiles[z][x].flags & 1))
      {
        continue;
      }

      // load even the tiles without models in case there are old ones
      // that shouldn't be there to avoid creating new duplicates

      std::stringstream filename;
      filename << "World\\Maps\\" << basename << "\\" << basename << "_" << x << "_" << z << ".adt";

      // load the tile without the models
      MapTile tile(x, z, filename.str(), mBigAlpha, false, use_mclq_green_lava(), false, world, tile_mode::uid_fix_all);
      tile.finishLoading();

      // add the uids to the tile to be able to save the models
      // which have been loaded in world earlier
      for (std::uint32_t uid : uids_per_tile[z][x])
      {
        tile.add_model(uid);
      }

      tile.saveTile(world);
    }
  }

  // override the db highest uid if used
  saveMaxUID();

  _uid_fix_all_in_progress = false;


  return loading_error ? uid_fix_status::done_with_errors : uid_fix_status::done;
}

void MapIndex::searchMaxUID()
{
  for (int z = 0; z < 64; ++z)
  {
    for (int x = 0; x < 64; ++x)
    {
      if (!(mTiles[z][x].flags & 1))
      {
        continue;
      }

      std::stringstream filename;
      filename << "World\\Maps\\" << basename << "\\" << basename << "_" << x << "_" << z << ".adt";
      highestGUID = std::max(highestGUID, getHighestGUIDFromFile(filename.str()));
    }
  }

  saveMaxUID();
}

void MapIndex::saveMaxUID()
{

}

void MapIndex::loadMaxUID()
{
  
}
