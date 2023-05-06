// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#include "OgreHeader.h"
#include "MapChunk.h"
#include "OgreDataStream.h"
#include "Misc.h"
#include <algorithm>
#include <iostream>
#include <map>

MapChunk::MapChunk(
    MapTile *maintile, 
    std::shared_ptr<DataStream>& stream, 
    bool bigAlpha, 
    tile_mode mode)
  : _mode(mode)
  , mt(maintile)
  , use_big_alphamap(bigAlpha)
{
  uint32_t fourcc;
  uint32_t size;

  size_t base = stream->tell();

  hasMCCV = false;

  // - MCNK ----------------------------------------------
  {
      stream->read(&fourcc, 4);
      stream->read(&size, 4);

    assert(fourcc == 'MCNK');

    stream->read(&header, 0x80);

    header_flags.value = header.flags;
    areaID = header.areaid;

    zbase = header.zpos;
    xbase = header.xpos;
    ybase = header.ypos;

    px = header.ix;
    py = header.iy;

    holes = header.holes;

    // correct the x and z values ^_^
    zbase = zbase*-1.0f + ZEROPOINT;
    xbase = xbase*-1.0f + ZEROPOINT;

    vmin = Ogre::Vector3(9999999.0f, 9999999.0f, 9999999.0f);
    vmax = Ogre::Vector3(-9999999.0f, -9999999.0f, -9999999.0f);
  }

 
  // - MCVT ----------------------------------------------
  {
      stream->seek(base + header.ofsHeight);
      stream->read(&fourcc, 4);
      stream->read(&size, 4);

    assert(fourcc == 'MCVT');

    Ogre::Vector3*ttv = mVertices;

    // vertices
    for (int j = 0; j < 17; ++j) {
      for (int i = 0; i < ((j % 2) ? 8 : 9); ++i) {
        float h, xpos, zpos;
        stream->read(&h, 4);
        xpos = i * UNITSIZE;
        zpos = j * 0.5f * UNITSIZE;
        if (j % 2) {
          xpos += UNITSIZE*0.5f;
        }
        Ogre::Vector3 v = Ogre::Vector3(xbase + xpos, ybase + h, zbase + zpos);
        *ttv++ = v;
        vmin.y = std::min(vmin.y, v.y);
        vmax.y = std::max(vmax.y, v.y);
      }
    }

    vmin.x = xbase;
    vmin.z = zbase;
    vmax.x = xbase + 8 * UNITSIZE;
    vmax.z = zbase + 8 * UNITSIZE;

    update_intersect_points();

    // use absolute y pos in vertices
    ybase = 0.0f;
    header.ypos = 0.0f;
  }
  // - MCNR ----------------------------------------------
  {
      stream->seek(base + header.ofsNormal);
      stream->read(&fourcc, 4);
      stream->read(&size, 4);

    assert(fourcc == 'MCNR');

    char nor[3];
    Ogre::Vector3*ttn = mNormals;
    for (int i = 0; i< mapbufsize; ++i)
    {
      stream->read(nor, 3);
      *ttn++ = Ogre::Vector3(nor[0] / 127.0f, nor[2] / 127.0f, nor[1] / 127.0f);
    }
  }
  // - MCSH ----------------------------------------------
  if(header.ofsShadow && header.sizeShadow)
  {
      stream->seek(base + header.ofsShadow);
      stream->read(&fourcc, 4);
      stream->read(&size, 4);

    assert(fourcc == 'MCSH');


    uint8_t compressed_shadow_map[64 * 64 / 8];

    // shadow map 64 x 64
    stream->read(compressed_shadow_map, 0x200);
    stream->seekRelative(-0x200);

    uint8_t *p, *c;
    p = _shadow_map;
    c = compressed_shadow_map;
    for (int i = 0; i<64 * 8; ++i)
    {
      for (int b = 0x01; b != 0x100; b <<= 1)
      {
        *p++ = ((*c) & b) ? 85 : 0;
      }
      c++;
    }

    if (!header_flags.flags.do_not_fix_alpha_map)
    {
      for (std::size_t i(0); i < 64; ++i)
      {
        _shadow_map[i * 64 + 63] = _shadow_map[i * 64 + 62];
        _shadow_map[63 * 64 + i] = _shadow_map[62 * 64 + i];
      }
      _shadow_map[63 * 64 + 63] = _shadow_map[62 * 64 + 62];
    }
  }
  else
  {
    /** We have no shadow map (MCSH), so we got no shadows at all!  **
    ** This results in everything being black.. Yay. Lets fake it! **/
    memset(_shadow_map, 0, 64 * 64);
  }
  // - MCCV ----------------------------------------------
  if(header.ofsMCCV)
  {
      stream->seek(base + header.ofsMCCV);
      stream->read(&fourcc, 4);
      stream->read(&size, 4);

    assert(fourcc == 'MCCV');

    if (!(header_flags.flags.has_mccv))
    {
      header_flags.flags.has_mccv = 1;
    }

    hasMCCV = true;

    unsigned char t[4];
    for (int i = 0; i < mapbufsize; ++i)
    {
        stream->read(t, 4);
      mccv[i] = Ogre::Vector3((float)t[2] / 127.0f, (float)t[1] / 127.0f, (float)t[0] / 127.0f);
    }
  }
  else
  {
      Ogre::Vector3 mccv_default(1.f, 1.f, 1.f);
    for (int i = 0; i < mapbufsize; ++i)
    {
      mccv[i] = mccv_default;
    }
  }

  if (header.sizeLiquid > 8)
  {
    stream->seek(base + header.ofsLiquid);

    stream->read(&fourcc, 4);
    stream->seekRelative(4); // ignore the size here, the valid size is in the header

    assert(fourcc == 'MCLQ');

    int layer_count = (header.sizeLiquid - 8) / sizeof(mclq);
    std::vector<mclq> layers(layer_count);
    stream->read(layers.data(), sizeof(mclq)*layer_count);

    mt->Water.getChunk(px, py)->from_mclq(layers);
    // remove the liquid flags as it'll be saved as MH2O
    header_flags.value &= ~(0xF << 2);
  }

  // no need to create indexes when applying the uid fix
  if (_mode == tile_mode::edit)
  {
    initStrip();
  }

  vcenter = (vmin + vmax) * 0.5f;
}

int MapChunk::indexLoD(int x, int y)
{
  return (x + 1) * 9 + x * 8 + y;
}

int MapChunk::indexNoLoD(int x, int y)
{
  return x * 8 + x * 9 + y;
}

void MapChunk::update_intersect_points()
{
  // update the center of the chunk and visibility when the vertices changed
  vcenter = (vmin + vmax) * 0.5f;
  _need_visibility_update = true;

  _intersect_points.clear();
  _intersect_points = misc::intersection_points(vmin, vmax);
}

void MapChunk::upload()
{
  // uid fix adt should never/can't be rendered
  // add the check here once to avoid checks all over the place
  // editing requires rendering anyway
  if (_mode == tile_mode::uid_fix_all)
  {
    throw std::logic_error("Trying to render an ADT/chunk that is supposed to be used for the uid fix all only");
  }



  update_shadows();



  update_indices_buffer();
  _uploaded = true;
}

void MapChunk::update_indices_buffer()
{
  
}

std::optional<int> MapChunk::get_lod_level(Ogre::Vector3 const& camera_pos, display_mode display) const
{
  float dist = display == display_mode::in_2D
             ? std::abs(camera_pos.y - vcenter.y)
             : (camera_pos - vcenter).length();

  if (dist < 500.f)
  {
      return std::optional<int>();
  }
  else if (dist < 1000.f)
  {
    return 0;
  }
  else if (dist < 2000.f)
  {
    return 1;
  }
  else if (dist < 4000.f)
  {
    return 2;
  }
  else
  {
    return 3;
  }
}

std::vector<uint8_t> MapChunk::compressed_shadow_map() const
{
  std::vector<uint8_t> shadow_map(64 * 64 / 8);

  for (int i = 0; i < 64 * 64; ++i)
  {
    if (_shadow_map[i])
    {
      shadow_map[i / 8] |= 1 << i % 8;
    }
  }

  return shadow_map;
}

bool MapChunk::has_shadows() const
{
  for (int i = 0; i < 64 * 64; ++i)
  {
    if (_shadow_map[i])
    {
      return true;
    }
  }

  return false;
}

void MapChunk::initStrip()
{
  strip_with_holes.clear();
  strip_without_holes.clear();
  strip_lods.clear();

  for (int x = 0; x<8; ++x)
  {
    for (int y = 0; y<8; ++y)
    {
      strip_without_holes.emplace_back (indexLoD(y, x)); //9
      strip_without_holes.emplace_back (indexNoLoD(y, x)); //0
      strip_without_holes.emplace_back (indexNoLoD(y + 1, x)); //17
      strip_without_holes.emplace_back (indexLoD(y, x)); //9
      strip_without_holes.emplace_back (indexNoLoD(y + 1, x)); //17
      strip_without_holes.emplace_back (indexNoLoD(y + 1, x + 1)); //18
      strip_without_holes.emplace_back (indexLoD(y, x)); //9
      strip_without_holes.emplace_back (indexNoLoD(y + 1, x + 1)); //18
      strip_without_holes.emplace_back (indexNoLoD(y, x + 1)); //1
      strip_without_holes.emplace_back (indexLoD(y, x)); //9
      strip_without_holes.emplace_back (indexNoLoD(y, x + 1)); //1
      strip_without_holes.emplace_back (indexNoLoD(y, x)); //0

      if (isHole(x / 2, y / 2))
        continue;

      // todo: better hole check ?
      for (int lod_level = 0; lod_level < 4; ++lod_level)
      {
        int n = 1 << lod_level;
        if ((x % n) == 0 && (y % n) == 0)
        {
          strip_lods[lod_level].emplace_back (indexNoLoD(y, x)); //0
          strip_lods[lod_level].emplace_back (indexNoLoD(y + n, x)); //17
          strip_lods[lod_level].emplace_back (indexNoLoD(y + n, x + n)); //18
          strip_lods[lod_level].emplace_back (indexNoLoD(y + n, x + n)); //18
          strip_lods[lod_level].emplace_back (indexNoLoD(y, x + n)); //1
          strip_lods[lod_level].emplace_back (indexNoLoD(y, x)); //0
        }
      }

      strip_with_holes.emplace_back (indexLoD(y, x)); //9
      strip_with_holes.emplace_back (indexNoLoD(y, x)); //0
      strip_with_holes.emplace_back (indexNoLoD(y + 1, x)); //17
      strip_with_holes.emplace_back (indexLoD(y, x)); //9
      strip_with_holes.emplace_back (indexNoLoD(y + 1, x)); //17
      strip_with_holes.emplace_back (indexNoLoD(y + 1, x + 1)); //18
      strip_with_holes.emplace_back (indexLoD(y, x)); //9
      strip_with_holes.emplace_back (indexNoLoD(y + 1, x + 1)); //18
      strip_with_holes.emplace_back (indexNoLoD(y, x + 1)); //1
      strip_with_holes.emplace_back (indexLoD(y, x)); //9
      strip_with_holes.emplace_back (indexNoLoD(y, x + 1)); //1
      strip_with_holes.emplace_back (indexNoLoD(y, x)); //0
    }
  }

  _need_indice_buffer_update = true;
}

bool MapChunk::GetVertex(float x, float z, Ogre::Vector3 *V)
{
  float xdiff, zdiff;

  xdiff = x - xbase;
  zdiff = z - zbase;

  const int row = static_cast<int>(zdiff / (UNITSIZE * 0.5f) + 0.5f);
  const int column = static_cast<int>((xdiff - UNITSIZE * 0.5f * (row % 2)) / UNITSIZE + 0.5f);
  if ((row < 0) || (column < 0) || (row > 16) || (column >((row % 2) ? 8 : 9)))
    return false;

  *V = mVertices[17 * (row / 2) + ((row % 2) ? 9 : 0) + column];
  return true;
}

float MapChunk::getHeight(int x, int z)
{
  if (x > 9 || z > 9 || x < 0 || z < 0) return 0.0f;
  return mVertices[indexNoLoD(x, z)].y;
}

float MapChunk::getMinHeight()
{
  float min (mVertices[0].y);

  for (auto&& vertex : mVertices)
  {
    min = std::min (min, (float)vertex.y);
  }

  return min;
}

void MapChunk::clearHeight()
{
  for (int i = 0; i < mapbufsize; ++i)
  {
    mVertices[i].y = 0.0f;
  }

  vmin.y = 0.0f;
  vmax.y = 0.0f;

  update_intersect_points();

}

void MapChunk::updateVerticesData()
{
  vmin.y = std::numeric_limits<float>::max();
  vmax.y = std::numeric_limits<float>::lowest();

  for (int i(0); i < mapbufsize; ++i)
  {
    vmin.y = std::min(vmin.y, mVertices[i].y);
    vmax.y = std::max(vmax.y, mVertices[i].y);
  }

  update_intersect_points();

}

void MapChunk::recalcNorms (std::function<std::optional<float> (float, float)> height)
{
  

}

bool MapChunk::changeTerrain(
    Ogre::Vector3 const& pos, float change, float radius, int BrushType, float inner_radius)
{
  float dist, xdiff, zdiff;
  bool changed = false;

  for (int i = 0; i < mapbufsize; ++i)
  {
    xdiff = mVertices[i].x - pos.x;
    zdiff = mVertices[i].z - pos.z;
    if (BrushType == eTerrainType_Quadra)
    {
      if ((std::abs(xdiff) < std::abs(radius / 2)) && (std::abs(zdiff) < std::abs(radius / 2)))
      {
        dist = std::sqrt(xdiff*xdiff + zdiff*zdiff);
        mVertices[i].y += change * (1.0f - dist * inner_radius / radius);
        changed = true;
      }
    }
    else
    {
      dist = std::sqrt(xdiff*xdiff + zdiff*zdiff);
      if (dist < radius)
      {
        changed = true;

        switch (BrushType)
        {
          case eTerrainType_Flat:
            mVertices[i].y += change;
            break;
          case eTerrainType_Linear:
            mVertices[i].y += change * (1.0f - dist * (1.0f - inner_radius) / radius);
            break;
          case eTerrainType_Smooth:
            mVertices[i].y += change / (1.0f + dist / radius);
            break;
          case eTerrainType_Polynom:
            mVertices[i].y += change*((dist / radius)*(dist / radius) + dist / radius + 1.0f);
            break;
          case eTerrainType_Trigo:
            mVertices[i].y += change*cos(dist / radius);
            break;
          case eTerrainType_Gaussian:
            mVertices[i].y += dist < radius * inner_radius ? change * std::exp(-(std::pow(radius * inner_radius / radius, 2) / (2 * std::pow(0.39f, 2)))) : change * std::exp(-(std::pow(dist / radius, 2) / (2 * std::pow(0.39f, 2))));

            break;
          default:

            changed = false;
            break;
        }
      }
    }
  }
  if (changed)
  {
    updateVerticesData();
  }
  return changed;
}

bool MapChunk::ChangeMCCV(
    Ogre::Vector3 const& pos,
    Ogre::ColourValue const& color, float change, float radius, bool editMode)
{
  float dist;
  bool changed = false;

  if (!hasMCCV)
  {
    for (int i = 0; i < mapbufsize; ++i)
    {
      mccv[i].x = 1.0f; // set default shaders
      mccv[i].y = 1.0f;
      mccv[i].z = 1.0f;
    }

    changed = true;
    header_flags.flags.has_mccv = 1;
    hasMCCV = true;
  }

  for (int i = 0; i < mapbufsize; ++i)
  {
    dist = misc::dist(mVertices[i], pos);
    if (dist <= radius)
    {
      float edit = change * (1.0f - dist / radius);
      if (editMode)
      {
        mccv[i].x += (color.r / 0.5f - mccv[i].x)* edit;
        mccv[i].y += (color.g / 0.5f - mccv[i].y)* edit;
        mccv[i].z += (color.b / 0.5f - mccv[i].z)* edit;
      }
      else
      {
        mccv[i].x += (1.0f - mccv[i].x) * edit;
        mccv[i].y += (1.0f - mccv[i].y) * edit;
        mccv[i].z += (1.0f - mccv[i].z) * edit;
      }

      mccv[i].x = std::min(std::max(mccv[i].x, 0.0f), 2.0f);
      mccv[i].y = std::min(std::max(mccv[i].y, 0.0f), 2.0f);
      mccv[i].z = std::min(std::max(mccv[i].z, 0.0f), 2.0f);

      changed = true;
    }
  }


  return changed;
}

Ogre::Vector3 MapChunk::pickMCCV(Ogre::Vector3 const& pos)
{
  float dist;
  float cur_dist = UNITSIZE;

  if (!hasMCCV)
  {
    return Ogre::Vector3(1.0f, 1.0f, 1.0f);
  }

  int v_index = 0;
  for (int i = 0; i < mapbufsize; ++i)
  {
    dist = misc::dist(mVertices[i], pos);
    if (dist <= cur_dist)
    {
      cur_dist = dist;
      v_index = i;
    }
  }

  return mccv[v_index];

}

bool MapChunk::flattenTerrain (Ogre::Vector3 const& pos
                              , float remain
                              , float radius
                              , int BrushType
                              , flatten_mode const& mode
                              , Ogre::Vector3 const& origin
                              , Ogre::Radian angle
                              , Ogre::Radian orientation
                              )
{
    return true;
}

bool MapChunk::blurTerrain ( Ogre::Vector3 const& pos
                           , float remain
                           , float radius
                           , int BrushType
                           , flatten_mode const& mode
                           , std::function<std::optional<float> (float, float)> height
                           )
{
    return true;
  
}




void MapChunk::update_shadows()
{
 
}

void MapChunk::clear_shadows()
{
  memset(_shadow_map, 0, 64 * 64);

  if (_uploaded)
  {
    update_shadows();
  }
}

bool MapChunk::isHole(int i, int j)
{
  return (holes & ((1 << ((j * 4) + i)))) != 0;
}

void MapChunk::setHole(Ogre::Vector3 const& pos, bool big, bool add)
{
  if (big)
  {
    holes = add ? 0xFFFFFFFF : 0x0;
  }
  else
  {
    int v = 1 << ((int)((pos.z - zbase) / MINICHUNKSIZE) * 4 + (int)((pos.x - xbase) / MINICHUNKSIZE));
    holes = add ? (holes | v) : (holes & ~v);
  }

  initStrip();
}

void MapChunk::setAreaID(int ID)
{
  areaID = ID;
}

int MapChunk::getAreaID()
{
  return areaID;
}


void MapChunk::setFlag(bool changeto, uint32_t flag)
{
  if (changeto)
  {
    header_flags.value |= flag;
  }
  else
  {
    header_flags.value &= ~flag;
  }
}



bool MapChunk::fixGapLeft(const MapChunk* chunk)
{
  if (!chunk)
    return false;

  bool changed = false;

  for (size_t i = 0; i <= 136; i+= 17)
  {
    float h = chunk->mVertices[i + 8].y;
    if (mVertices[i].y != h)
    {
      mVertices[i].y = h;
      changed = true;
    }
  }

  if (changed)
  {
    updateVerticesData();
  }

  return changed;
}

bool MapChunk::fixGapAbove(const MapChunk* chunk)
{
  if (!chunk)
    return false;

  bool changed = false;

  for (size_t i = 0; i < 9; i++)
  {
    float h = chunk->mVertices[i + 136].y;
    if (mVertices[i].y != h)
    {
      mVertices[i].y = h;
      changed = true;
    }
  }

  if (changed)
  {
    updateVerticesData();
  }

  return changed;
}


void MapChunk::selectVertex(
    Ogre::Vector3 const& pos, 
    float radius, 
    std::set<Ogre::Vector3*>& vertices)
{
  if (misc::getShortestDist(pos.x, pos.z, xbase, zbase, CHUNKSIZE) > radius)
  {
    return;
  }

  for (int i = 0; i < mapbufsize; ++i)
  {
    if (misc::dist(pos.x, pos.z, mVertices[i].x, mVertices[i].z) <= radius)
    {
      vertices.emplace(&mVertices[i]);
    }
  }
}

void MapChunk::fixVertices(std::set<Ogre::Vector3*>& selected)
{
  std::vector<int> ids ={ 0, 1, 17, 18 };
  // iterate through each "square" of vertices
  for (int i = 0; i < 64; ++i)
  {
    int not_selected = 0, count = 0, mid_vertex = ids[0] + 9;
    float h = 0.0f;

    for (int& index : ids)
    {
      if (selected.find(&mVertices[index]) == selected.end())
      {
        not_selected = index;
      }
      else
      {
        count++;
      }
      h += mVertices[index].y;
      index += (((i+1) % 8) == 0) ? 10 : 1;
    }

    if (count == 2)
    {
      mVertices[mid_vertex].y = h * 0.25f;
    }
    else if (count == 3)
    {
      mVertices[mid_vertex].y = (h - mVertices[not_selected].y) / 3.0f;
    }
  }
}

bool MapChunk::isBorderChunk(std::set<Ogre::Vector3*>& selected)
{
  for (int i = 0; i < mapbufsize; ++i)
  {
    // border chunk if at least a vertex isn't selected
    if (selected.find(&mVertices[i]) == selected.end())
    {
      return true;
    }
  }

  return false;
}

ChunkWater* MapChunk::liquid_chunk() const
{
  return mt->Water.getChunk(px, py);
}
