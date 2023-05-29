// This file is part of Noggit3, licensed under GNU General Public License (version 3).
#include "OgreHeader.h"
#include "ChunkWater.hpp"
#include "liquid_layer.hpp"
#include "MapChunk.h"
#include "Misc.h"
#include "OgreDataStream.h"

ChunkWater::ChunkWater(float x, float z, bool use_mclq_green_lava)
  : xbase(x)
  , zbase(z)
  , vmin(x, 0.f, z)
  , vmax(x + CHUNKSIZE, 0.f, z + CHUNKSIZE)
  , _use_mclq_green_lava(use_mclq_green_lava)
{
}

void ChunkWater::from_mclq(std::vector<mclq>& layers)
{
  Ogre::Vector3 pos(xbase, 0.0f, zbase);

  for (mclq& liquid : layers)
  {
    std::uint8_t mclq_liquid_type = 0;

    for (int z = 0; z < 8; ++z)
    {
      for (int x = 0; x < 8; ++x)
      {
        mclq_tile const& tile = liquid.tiles[z * 8 + x];

        misc::bit_or(Render.fishable, x, z, tile.fishable);
        misc::bit_or(Render.fatigue, x, z, tile.fatigue);

        if (!tile.dont_render)
        {
          mclq_liquid_type = tile.liquid_type;
        }
      }
    }

    switch (mclq_liquid_type)
    {
      case 1:_layers.emplace_back(pos, liquid, 2); break;
      case 3:_layers.emplace_back(pos, liquid, 4); break;
      case 4:_layers.emplace_back(pos, liquid, 1); break;
      case 6:_layers.emplace_back(pos, liquid, (_use_mclq_green_lava ? 15 : 3)); break;
      default:
        break;
    }
  }
  update_layers();
}

void ChunkWater::fromFile(std::shared_ptr<DataStream>& stream, size_t basePos)
{
  MH2O_Header header;
  stream->read(&header, sizeof(MH2O_Header));

  if (!header.nLayers)
  {
    return;
  }

  //render
  if (header.ofsRenderMask)
  {
      stream->seek(basePos + header.ofsRenderMask + sizeof(MH2O_Render));
      stream->read(&Render, sizeof(MH2O_Render));
  }

  for (std::size_t k = 0; k < header.nLayers; ++k)
  {
    MH2O_Information info;
    uint64_t infoMask = 0xFFFFFFFFFFFFFFFF; // default = all water

    //info
    stream->seek(basePos + header.ofsInformation + sizeof(MH2O_Information)* k);
    stream->read(&info, sizeof(MH2O_Information));

    //mask
    if (info.ofsInfoMask > 0 && info.height > 0)
    {
      size_t bitmask_size = static_cast<size_t>(std::ceil(info.height * info.width / 8.0f));

      stream->seek(info.ofsInfoMask + basePos);
      // only read the relevant data
      stream->read(&infoMask, bitmask_size);
    }

    Ogre::Vector3 pos(xbase, 0.0f, zbase);
    _layers.emplace_back(stream, basePos, pos, info, infoMask);
  }

  update_layers();
}


void ChunkWater::save(sExtendableArray& adt, int base_pos, int& header_pos, int& current_pos)
{
  MH2O_Header header;

  // remove empty layers
  cleanup();

  if (hasData(0))
  {
    header.nLayers = _layers.size();
    header.ofsRenderMask = current_pos - base_pos;
    adt.Insert(current_pos, sizeof(MH2O_Render), reinterpret_cast<char*>(&Render));
    current_pos += sizeof(MH2O_Render);

    header.ofsInformation = current_pos - base_pos;
    int info_pos = current_pos;

    std::size_t info_size = sizeof(MH2O_Information) * _layers.size();
    current_pos += info_size;

    adt.Extend(info_size);

    for (liquid_layer& layer : _layers)
    {
      layer.save(adt, base_pos, info_pos, current_pos);
    }
  }

  memcpy(adt.GetPointer<char>(header_pos), &header, sizeof(MH2O_Header));
  header_pos += sizeof(MH2O_Header);
}


void ChunkWater::autoGen(MapChunk *chunk, float factor)
{
  for (liquid_layer& layer : _layers)
  {
    layer.update_opacity(chunk, factor);
  }
  update_layers();
}


void ChunkWater::CropWater(MapChunk* chunkTerrain)
{
  for (liquid_layer& layer : _layers)
  {
    layer.crop(chunkTerrain);
  }
  update_layers();
}

int ChunkWater::getType(size_t layer) const
{
  return hasData(layer) ? _layers[layer].liquidID() : 0;
}

void ChunkWater::setType(int type, size_t layer)
{
  if(hasData(layer))
  {
    _layers[layer].changeLiquidID(type);
  }
}


void ChunkWater::update_layers()
{
  for (liquid_layer& layer : _layers)
  {
    layer.update_indices();
    vmin.y = std::min (vmin.y, layer.min());
    vmax.y = std::max (vmax.y, layer.max());
  }

  vcenter = (vmin + vmax) * 0.5f;

  _intersect_points.clear();
  _intersect_points = misc::intersection_points(vmin, vmax);
}

bool ChunkWater::hasData(size_t layer) const
{
  return _layers.size() > layer;
}


void ChunkWater::cleanup()
{
  for (int i = _layers.size() - 1; i >= 0; --i)
  {
    if (_layers[i].empty())
    {
      _layers.erase(_layers.begin() + i);
    }
  }
}

void ChunkWater::copy_height_to_layer(
    liquid_layer& target, 
    Ogre::Vector3 const& pos, float radius)
{
  for (liquid_layer& layer : _layers)
  {
    if (layer.liquidID() == target.liquidID())
    {
      continue;
    }

    for (int z = 0; z < 8; ++z)
    {
      for (int x = 0; x < 8; ++x)
      {
        if (misc::getShortestDist(pos.x, pos.z, xbase + x*UNITSIZE, zbase + z*UNITSIZE, UNITSIZE) <= radius)
        {
          if (layer.hasSubchunk(x, z))
          {
            target.copy_subchunk_height(x, z, layer);
          }
        }
      }
    }
  }
}
