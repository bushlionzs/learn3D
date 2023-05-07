// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#include "OgreHeader.h"
#include <World.h>
#include <Brush.h> // brush
#include <ChunkWater.hpp>
#include <dbcfile.h>
#include <MapChunk.h>
#include <MapTile.h>
#include <Misc.h>
#include <TileWater.hpp>// tile water
#include <WMOInstance.h> // WMOInstance
#include <map_index.hpp>
#include <tool_enums.hpp>
#include <filesystem>
#include <algorithm>
#include <cassert>
#include <ctime>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <variant>
#include "OgreDataStream.h"
#include "OgreResourceManager.h"

bool World::IsEditableWorld(int pMapId)
{
  std::string lMapName;
  try
  {
    DBCFile::Record map = gMapDB.getRecord((unsigned int)pMapId);
    lMapName = map.getString(MapDB::InternalName);
  }
  catch (int)
  {
    return false;
  }

  std::stringstream ssfilename;
  ssfilename << "World\\Maps\\" << lMapName << "\\" << lMapName << ".wdt";

  auto wdtstream = ResourceManager::getSingleton().openResource(ssfilename.str());
  if (!wdtstream)
  {
    return false;
  }

  //sometimes, wdts don't open, so ignore them...
  if (wdtstream->eof())
    return false;

  const char * lPointer = reinterpret_cast<const char*>(wdtstream->getCurrentStreamData());

  // Not using the libWDT here doubles performance. You might want to look at your lib again and improve it.
  const int lFlags = *(reinterpret_cast<const int*>(lPointer + 8 + 4 + 8));
  if (lFlags & 1)
    return false;

  const int * lData = reinterpret_cast<const int*>(lPointer + 8 + 4 + 8 + 0x20 + 8);
  for (int i = 0; i < 8192; i += 2)
  {
    if (lData[i] & 1)
      return true;
  }

  return false;
}

World::World(const std::string& name, int map_id)
    :
  mapIndex (name, map_id, this)
  , mWmoFilename("")
  , mWmoEntry(ENTRY_MODF())
  , detailtexcoords(0)
  , alphatexcoords(0)
  , animtime(0)
  , time(1450)
  , basename(name)
  , fogdistance(777.0f)
  , culldistance(fogdistance)
  , _current_selection()
{
  
}

void World::update_selection_pivot()
{
  
}

bool World::is_selected(selection_type selection) const
{
    
  

  return false;
}

bool World::is_selected(std::uint32_t uid) const
{
  

  return false;
}

std::optional<selection_type> World::get_last_selected_model() const
{
    return std::optional<selection_type>();
}

void World::set_current_selection(selection_type entry)
{
  _current_selection.clear();
  _current_selection.push_back(entry);
  _multi_select_pivot.reset();
}

void World::add_to_selection(selection_type entry)
{
 
}

void World::remove_from_selection(selection_type entry)
{
  
}

void World::remove_from_selection(std::uint32_t uid)
{
  
}

void World::reset_selection()
{
  _current_selection.clear();
  _multi_select_pivot.reset();
  _selected_model_count = 0;
}

void World::delete_selected_models()
{
}

void World::snap_selected_models_to_the_ground()
{
  
}

void World::scale_selected_models(float v, m2_scaling_type type)
{
  
}

void World::move_selected_models(float dx, float dy, float dz)
{
  
}

void World::set_selected_models_pos(Ogre::Vector3 const& pos, bool change_height)
{
  
}

void World::rotate_selected_models(
    Ogre::Degree rx, 
    Ogre::Degree ry,
    Ogre::Degree rz, bool use_pivot)
{
  
}

void World::set_selected_models_rotation(
    Ogre::Degree rx, Ogre::Degree ry, Ogre::Degree rz)
{
  
}



void World::initDisplay()
{


  mapIndex.setAdt(false);

  if (mapIndex.hasAGlobalWMO())
  {
 
  }
  else
  {
   
  }
}





void World::update_models_emitters(float dt)
{
 
}

unsigned int World::getAreaID (Ogre::Vector3 const& pos)
{
  return for_maybe_chunk_at (pos, [&] (MapChunk* chunk) { return chunk->getAreaID(); }).value_or(-1);
}

void World::clearHeight(Ogre::Vector3 const& pos)
{
  for_all_chunks_on_tile(pos, [](MapChunk* chunk) {
    chunk->clearHeight();
  });
  for_all_chunks_on_tile(pos, [this] (MapChunk* chunk) {
      recalc_norms (chunk);
  });
}

void World::clearAllModelsOnADT(tile_index const& tile)
{
  update_models_by_filename();
}

void World::CropWaterADT(const tile_index& pos)
{
  for_tile_at(pos, [](MapTile* tile) { tile->CropWater(); });
}

void World::setAreaID(Ogre::Vector3 const& pos, int id, bool adt)
{
  if (adt)
  {
    for_all_chunks_on_tile(pos, [&](MapChunk* chunk) { chunk->setAreaID(id);});
  }
  else
  {
    for_chunk_at(pos, [&](MapChunk* chunk) { chunk->setAreaID(id);});
  }
}

bool World::GetVertex(float x, float z, Ogre::Vector3 *V) const
{
  tile_index tile({x, 0, z});

  if (!mapIndex.tileLoaded(tile))
  {
    return false;
  }

  MapTile* adt = mapIndex.getTile(tile);

  return adt->finishedLoading() && adt->GetVertex(x, z, V);
}

template<typename Fun>
  bool World::for_all_chunks_in_range (Ogre::Vector3 const& pos, float radius, Fun&& fun)
{
  bool changed (false);

  for (MapTile* tile : mapIndex.tiles_in_range (pos, radius))
  {
    if (!tile->finishedLoading())
    {
      continue;
    }

    for (MapChunk* chunk : tile->chunks_in_range (pos, radius))
    {
      if (fun (chunk))
      {
        changed = true;
        mapIndex.setChanged (tile);
      }
    }
  }

  return changed;
}
template<typename Fun, typename Post>
  bool World::for_all_chunks_in_range (
      Ogre::Vector3 const& pos, float radius, Fun&& fun, Post&& post)
{
  std::forward_list<MapChunk*> modified_chunks;

  bool changed ( for_all_chunks_in_range
                   ( pos, radius
                   , [&] (MapChunk* chunk)
                     {
                       if (fun (chunk))
                       {
                         modified_chunks.emplace_front (chunk);
                         return true;
                       }
                       return false;
                     }
                   )
               );

  for (MapChunk* chunk : modified_chunks)
  {
    post (chunk);
  }

  return changed;
}

void World::changeShader(
    Ogre::Vector3 const& pos, 
    Ogre::ColourValue const& color, float change, float radius, bool editMode)
{
  for_all_chunks_in_range
    ( pos, radius
    , [&] (MapChunk* chunk)
      {
        return chunk->ChangeMCCV(pos, color, change, radius, editMode);
      }
    );
}

Ogre::Vector3 World::pickShaderColor(Ogre::Vector3 const& pos)
{
  Ogre::Vector3 color = Ogre::Vector3(1.0f, 1.0f, 1.0f);
 
  return color;
}

void World::changeTerrain(Ogre::Vector3 const& pos, float change, float radius, int BrushType, float inner_radius)
{
  for_all_chunks_in_range
    ( pos, radius
    , [&] (MapChunk* chunk)
      {
        return chunk->changeTerrain(pos, change, radius, BrushType, inner_radius);
      }
    , [this] (MapChunk* chunk)
      {
        recalc_norms (chunk);
      }
    );
}

void World::flattenTerrain(
    Ogre::Vector3 const& pos, 
    float remain, 
    float radius, 
    int BrushType, flatten_mode const& mode, 
    const Ogre::Vector3& origin, 
    Ogre::Degree angle, Ogre::Degree orientation)
{
  for_all_chunks_in_range
    ( pos, radius
    , [&] (MapChunk* chunk)
      {
        return chunk->flattenTerrain(pos, remain, radius, BrushType, mode, origin, angle, orientation);
      }
    , [this] (MapChunk* chunk)
      {
        recalc_norms (chunk);
      }
    );
}

void World::blurTerrain(Ogre::Vector3 const& pos, float remain, float radius, int BrushType, flatten_mode const& mode)
{
  for_all_chunks_in_range
    ( pos, radius
    , [&] (MapChunk* chunk)
      {
        return chunk->blurTerrain ( pos
                                  , remain
                                  , radius
                                  , BrushType
                                  , mode
                                  , [this] (float x, float z) -> std::optional<float>
                                    {
                                      Ogre::Vector3 vec;
                                      auto res (GetVertex (x, z, &vec));
                                      return res?std::make_optional<float>(vec.y): std::make_optional<float>();
                                    }
                                  );
      }
    , [this] (MapChunk* chunk)
      {
        recalc_norms (chunk);
      }
    );
}

void World::recalc_norms (MapChunk* chunk) const
{
  chunk->recalcNorms ( [this] (float x, float z) -> std::optional<float>
                       {
                         Ogre::Vector3 vec;
                         auto res (GetVertex (x, z, &vec));
                         return res ? std::make_optional<float>(vec.y) : std::make_optional<float>();
                       }
                     );
}


void World::setHole(Ogre::Vector3 const& pos, bool big, bool hole)
{
  for_chunk_at(pos, [&](MapChunk* chunk) { chunk->setHole(pos, big, hole); });
}

void World::setHoleADT(Ogre::Vector3 const& pos, bool hole)
{
  for_all_chunks_on_tile(pos, [&](MapChunk* chunk) { chunk->setHole(pos, true, hole); });
}


template<typename Fun>
  void World::for_all_chunks_on_tile (Ogre::Vector3 const& pos, Fun&& fun)
{
  MapTile* tile (mapIndex.getTile (pos));

  if (tile && tile->finishedLoading())
  {
    mapIndex.setChanged(tile);

    for (size_t ty = 0; ty < 16; ++ty)
    {
      for (size_t tx = 0; tx < 16; ++tx)
      {
        fun(tile->getChunk(ty, tx));
      }
    }
  }
}

template<typename Fun>
  void World::for_chunk_at(Ogre::Vector3 const& pos, Fun&& fun)
{
  MapTile* tile(mapIndex.getTile(pos));

  if (tile && tile->finishedLoading())
  {
    mapIndex.setChanged(tile);
    fun(tile->getChunk((pos.x - tile->xbase) / CHUNKSIZE, (pos.z - tile->zbase) / CHUNKSIZE));
  }
}

template<typename Fun>
  auto World::for_maybe_chunk_at(Ogre::Vector3 const& pos, Fun&& fun) -> std::optional<decltype (fun (nullptr))>
{
  MapTile* tile (mapIndex.getTile (pos));
  if (tile && tile->finishedLoading())
  {
    return fun (tile->getChunk ((pos.x - tile->xbase) / CHUNKSIZE, (pos.z - tile->zbase) / CHUNKSIZE));
  }
  else
  {
      return std::optional<decltype (fun(nullptr))>();
  }
}

template<typename Fun>
  void World::for_tile_at(tile_index const& pos, Fun&& fun)
  {
    MapTile* tile(mapIndex.getTile(pos));
    if (tile && tile->finishedLoading())
    {
      mapIndex.setChanged(tile);
      fun(tile);
    }
  }

void World::convert_alphamap(bool to_big_alpha)
{
  if (to_big_alpha == mapIndex.hasBigAlpha())
  {
    return;
  }

  for (size_t z = 0; z < 64; z++)
  {
    for (size_t x = 0; x < 64; x++)
    {
      tile_index tile(x, z);

      bool unload = !mapIndex.tileLoaded(tile) && !mapIndex.tileAwaitingLoading(tile);
      MapTile* mTile = mapIndex.loadTile(tile);

      if (mTile)
      {
        mTile->wait_until_loaded();

        mTile->convert_alphamap(to_big_alpha);
        mTile->saveTile(this);
        mapIndex.markOnDisc (tile, true);
        mapIndex.unsetChanged(tile);

        if (unload)
        {
          mapIndex.unloadTile(tile);
        }
      }
    }
  }

  mapIndex.convert_alphamap(to_big_alpha);
  mapIndex.save();
}

void World::saveMap (int, int)
{
  throw std::runtime_error("minimap saving not implemented");
}

void World::deleteModelInstance(int pUniqueID)
{
 
}

void World::deleteWMOInstance(int pUniqueID)
{
  
}

bool World::uid_duplicates_found() const
{
    return false;
}

void World::delete_duplicate_model_and_wmo_instances()
{
  reset_selection();

  need_model_updates = true;
}

void World::unload_every_model_and_wmo_instance()
{
  reset_selection();


  _models_by_filename.clear();
}

void World::addM2 ( std::string const& filename
                  , Ogre::Vector3 newPos
                  , float scale
                  , Ogre::Vector3 rotation
                  , noggit::object_paste_params* paste_params
                  )
{
}

void World::addWMO ( std::string const& filename
                   , Ogre::Vector3 newPos
                   , Ogre::Vector3 rotation
                   )
{

}

std::uint32_t World::add_model_instance(Ogre::Entity* entity, bool from_reloading)
{
    return 0;
}

std::uint32_t World::add_wmo_instance(Ogre::Entity* entity, bool from_reloading)
{
    return 0;
}

std::optional<selection_type> World::get_model(std::uint32_t uid)
{
    return std::optional<selection_type>();
}

void World::remove_models_if_needed(std::vector<uint32_t> const& uids)
{
  
}

void World::reload_tile(tile_index const& tile)
{
  reset_selection();
  mapIndex.reloadTile(tile);
}

void World::updateTilesEntry(selection_type const& entry, model_update type)
{
  
}

void World::updateTilesWMO(WMOInstance* wmo, model_update type, bool from_reloading)
{
  
}

void World::updateTilesModel(ModelInstance* m2, model_update type, bool from_reloading)
{
 
}

void World::wait_for_all_tile_updates()
{
 
}

unsigned int World::getMapID()
{
  return mapIndex._map_id;
}

void World::clearTextures(Ogre::Vector3 const& pos)
{
  
}

void World::setBaseTexture(Ogre::Vector3 const& pos)
{
 
}

void World::clear_shadows(Ogre::Vector3 const& pos)
{
  for_all_chunks_on_tile(pos, [] (MapChunk* chunk)
  {
    chunk->clear_shadows();
  });
}



void World::removeTexDuplicateOnADT(Ogre::Vector3 const& pos)
{
  
}





void World::setWaterType(const tile_index& pos, int type, int layer)
{
  for_tile_at ( pos
              , [&] (MapTile* tile)
                {
                  tile->Water.setType (type, layer);
                }
              );
}

int World::getWaterType(const tile_index& tile, int layer)
{
  if (mapIndex.tileLoaded(tile))
  {
    return mapIndex.getTile(tile)->Water.getType (layer);
  }
  else
  {
    return 0;
  }
}

void World::autoGenWaterTrans(const tile_index& pos, float factor)
{
  for_tile_at(pos, [&](MapTile* tile) { tile->Water.autoGen(factor); });
}


void World::fixAllGaps()
{
  std::vector<MapChunk*> chunks;

  for (MapTile* tile : mapIndex.loaded_tiles())
  {
    MapTile* left = mapIndex.getTileLeft(tile);
    MapTile* above = mapIndex.getTileAbove(tile);
    bool tileChanged = false;

    // fix the gaps with the adt at the left of the current one
    if (left)
    {
      for (size_t ty = 0; ty < 16; ty++)
      {
        MapChunk* chunk = tile->getChunk(0, ty);
        if (chunk->fixGapLeft(left->getChunk(15, ty)))
        {
          chunks.emplace_back(chunk);
          tileChanged = true;
        }
      }
    }

    // fix the gaps with the adt above the current one
    if (above)
    {
      for (size_t tx = 0; tx < 16; tx++)
      {
        MapChunk* chunk = tile->getChunk(tx, 0);
        if (chunk->fixGapAbove(above->getChunk(tx, 15)))
        {
          chunks.emplace_back(chunk);
          tileChanged = true;
        }
      }
    }

    // fix gaps within the adt
    for (size_t ty = 0; ty < 16; ty++)
    {
      for (size_t tx = 0; tx < 16; tx++)
      {
        MapChunk* chunk = tile->getChunk(tx, ty);
        bool changed = false;

        // if the chunk isn't the first of the row
        if (tx && chunk->fixGapLeft(tile->getChunk(tx - 1, ty)))
        {
          changed = true;
        }

        // if the chunk isn't the first of the column
        if (ty && chunk->fixGapAbove(tile->getChunk(tx, ty - 1)))
        {
          changed = true;
        }

        if (changed)
        {
          chunks.emplace_back(chunk);
          tileChanged = true;
        }
      }
    }
    if (tileChanged)
    {
      mapIndex.setChanged(tile);
    }
  }

  for (MapChunk* chunk : chunks)
  {
    recalc_norms (chunk);
  }
}

bool World::isUnderMap(Ogre::Vector3 const& pos)
{
  tile_index const tile (pos);

  if (mapIndex.tileLoaded(tile))
  {
    size_t chnkX = (pos.x / CHUNKSIZE) - tile.x * 16;
    size_t chnkZ = (pos.z / CHUNKSIZE) - tile.z * 16;

    // check using the cursor height
    return (mapIndex.getTile(tile)->getChunk(chnkX, chnkZ)->getMinHeight()) > pos.y + 2.0f;
  }

  return true;
}

void World::selectVertices(Ogre::Vector3 const& pos, float radius)
{
  _vertex_center_updated = false;
  _vertex_border_updated = false;

  for_all_chunks_in_range(pos, radius, [&](MapChunk* chunk){
    _vertex_chunks.emplace(chunk);
    _vertex_tiles.emplace(chunk->mt);
    chunk->selectVertex(pos, radius, _vertices_selected);
    return true;
  });
}

bool World::deselectVertices(Ogre::Vector3 const& pos, float radius)
{
  _vertex_center_updated = false;
  _vertex_border_updated = false;
  std::set<Ogre::Vector3*> inRange;

  for (Ogre::Vector3* v : _vertices_selected)
  {
    if (misc::dist(*v, pos) <= radius)
    {
      inRange.emplace(v);
    }
  }

  for (Ogre::Vector3* v : inRange)
  {
    _vertices_selected.erase(v);
  }

  return _vertices_selected.empty();
}

void World::moveVertices(float h)
{
  _vertex_center_updated = false;
  for (Ogre::Vector3* v : _vertices_selected)
  {
    v->y += h;
  }

  updateVertexCenter();
  updateSelectedVertices();
}

void World::updateSelectedVertices()
{
  for (MapTile* tile : _vertex_tiles)
  {
    mapIndex.setChanged(tile);
  }

  // fix only the border chunks to be more efficient
  for (MapChunk* chunk : vertexBorderChunks())
  {
    chunk->fixVertices(_vertices_selected);
  }

  for (MapChunk* chunk : _vertex_chunks)
  {
    chunk->updateVerticesData();
    recalc_norms (chunk);
  }
}

void World::orientVertices ( Ogre::Vector3 const& ref_pos
                           , Ogre::Degree vertex_angle
                           , Ogre::Degree vertex_orientation
                           )
{
  for (Ogre::Vector3* v : _vertices_selected)
  {
    v->y = misc::angledHeight(ref_pos, *v, vertex_angle, vertex_orientation);
  }
  updateSelectedVertices();
}

void World::flattenVertices (float height)
{
  for (Ogre::Vector3* v : _vertices_selected)
  {
    v->y = height;
  }
  updateSelectedVertices();
}

void World::clearVertexSelection()
{
  _vertex_border_updated = false;
  _vertex_center_updated = false;
  _vertices_selected.clear();
  _vertex_chunks.clear();
  _vertex_tiles.clear();
}

void World::updateVertexCenter()
{
  _vertex_center_updated = true;
  _vertex_center = { 0,0,0 };
  float f = 1.0f / _vertices_selected.size();
  for (Ogre::Vector3* v : _vertices_selected)
  {
    _vertex_center += (*v) * f;
  }
}

Ogre::Vector3 const& World::vertexCenter()
{
  if (!_vertex_center_updated)
  {
    updateVertexCenter();
  }

  return _vertex_center;
}

std::set<MapChunk*>& World::vertexBorderChunks()
{
  if (!_vertex_border_updated)
  {
    _vertex_border_updated = true;
    _vertex_border_chunks.clear();

    for (MapChunk* chunk : _vertex_chunks)
    {
      if (chunk->isBorderChunk(_vertices_selected))
      {
        _vertex_border_chunks.emplace(chunk);
      }
    }
  }
  return _vertex_border_chunks;
}

void World::update_models_by_filename()
{
  _models_by_filename.clear();

  need_model_updates = false;
}
