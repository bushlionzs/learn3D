// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#include "OgreHeader.h"
#include "MapChunk.h"
#include "OgreDataStream.h"
#include "Misc.h"
#include "texture_set.hpp"
#include "custom_renderable.h"
#include "vertex_data.h"
#include "index_data.h"
#include "vertex_declaration.h"
#include "OgreMaterial.h"
#include "OgreSceneNode.h"
#include "OgreRoot.h"
#include "OgreSceneManager.h"
#include <algorithm>
#include <iostream>
#include <map>

Ogre::Vector2 MapChunk::mTexCorrd[mapbufsize];

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

  texture_set = std::make_unique<TextureSet>(header, stream, base, maintile, bigAlpha, !!header_flags.flags.do_not_fix_alpha_map, mode == tile_mode::uid_fix_all);

 
  // - MCVT ----------------------------------------------
  {
      stream->seek(base + header.ofsHeight);
      stream->read(&fourcc, 4);
      stream->read(&size, 4);

    assert(fourcc == 'MCVT');

    WowTerrainVertex* ttv = mWowVertices;

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
        ttv->_vertex = Ogre::Vector3(xbase + xpos, ybase + h, zbase + zpos);
        ttv++;
        vmin.y = std::min(vmin.y, ttv->_vertex.y);
        vmax.y = std::max(vmax.y, ttv->_vertex.y);
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
    WowTerrainVertex*ttn = mWowVertices;
    for (int i = 0; i< mapbufsize; ++i)
    {
      stream->read(nor, 3);
      ttn->_normal = Ogre::Vector3(nor[0] / 127.0f, nor[2] / 127.0f, nor[1] / 127.0f);
      ttn++;
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
        mWowVertices[i]._mcvv = Ogre::ColourValue((float)t[2] / 127.0f, (float)t[1] / 127.0f, (float)t[0] / 127.0f);
    }
  }
  else
  {
    for (int i = 0; i < mapbufsize; ++i)
    {
        mWowVertices[i]._mcvv = Ogre::ColourValue::White;
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

  bool calTexCoord = false;

  if (!calTexCoord)
  {
      float detail_size = 8.0f;
      float tx, ty;
      Ogre::Vector2* vt = mTexCorrd;
      const float detail_half = 0.5f * detail_size / 8.0f;
      for (int j = 0; j < 17; ++j) {
          for (int i = 0; i < ((j % 2) ? 8 : 9); ++i) {
              tx = detail_size / 8.0f * i;
              ty = detail_size / 8.0f * j * 0.5f;
              if (j % 2) {
                  // offset by half
                  tx += detail_half;
              }
              *vt++ = Ogre::Vector2(tx, ty);
          }
      }
  }

  for (uint32_t i = 0; i < mapbufsize; i++)
  {
      mWowVertices[i]._texCoord = mTexCorrd[i];
  }

  //create renderable
  initStrip();
  VertexData* vd = new VertexData;
  vd->vertexCount = mapbufsize;
  vd->vertexSlotInfo.emplace_back();
  auto& back = vd->vertexSlotInfo.back();
  back.createBuffer(sizeof(WowTerrainVertex), mapbufsize);
  vd->vertexDeclaration->addElement(0, 0, 0, VET_FLOAT3, VES_POSITION);
  vd->vertexDeclaration->addElement(0, 0, 12, VET_FLOAT3, VES_NORMAL);
  vd->vertexDeclaration->addElement(0, 0, 24, VET_FLOAT2, VES_TEXTURE_COORDINATES);
  vd->vertexDeclaration->addElement(0, 0, 32, VET_FLOAT4, VES_COLOUR);
  back.writeData((const char*)&mWowVertices[0], sizeof(WowTerrainVertex)* mapbufsize);
  IndexData* id = new IndexData;
  id->createBuffer(2, strip_with_holes.size());
  id->writeData((const char*)strip_with_holes.data(), 2 * strip_with_holes.size());
  CustomRenderable* renderable = new CustomRenderable(vd, id);
  std::shared_ptr<Material> mat = std::make_shared<Material>("");
  uint32_t texcount = texture_set->num();
  
  for (uint32_t i = 0; i < texcount; i++)
  {
      const std::string& name = texture_set->filename(i);
      mat->addTexture(name);
  }

  
  for(uint32_t i = texcount; i < 4; i++)
  {
      mat->addTexture("white1x1.dds");
  }
  IndexDataView* view = renderable->getIndexView();
  view->mIndexCount = strip_with_holes.size();
  view->mBaseVertexLocation = 0;
  view->mIndexLocation = 0;
  std::string alphaname = Ogre::StringUtil::format("alpha%d-%d", px, py);
  auto alphatex = texture_set->createAlphaMapTexture(alphaname);
  mat->addTexture(alphatex);
  
  ShaderInfo info;
  info.shaderName = "wowterrain";
  mat->addShader(info);
  mat->load(nullptr);
  renderable->setMaterial(mat);
  mRenderables.push_back(renderable);

  auto sceneMgr = Ogre::Root::getSingleton().getSceneManager(MAIN_SCENE_MANAGER);
  auto parent = sceneMgr->getRoot();
  auto node = parent->createChildSceneNode(std::string("MapChunk"));
  node->attachObject(this);
}

const AxisAlignedBox& MapChunk::getBoundingBox(void) const
{
    mAABB.setInfinite();
    return mAABB;
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

  *V = mWowVertices[17 * (row / 2) + ((row % 2) ? 9 : 0) + column]._vertex;
  return true;
}

float MapChunk::getHeight(int x, int z)
{
  if (x > 9 || z > 9 || x < 0 || z < 0) return 0.0f;
  return mWowVertices[indexNoLoD(x, z)]._vertex.y;
}

float MapChunk::getHeight(int index)
{
    return mWowVertices[index]._vertex.y;
}

float MapChunk::getMinHeight()
{
  float min (mWowVertices[0]._vertex.y);

  for (auto&& vertex : mWowVertices)
  {
    min = std::min (min, (float)vertex._vertex.y);
  }

  return min;
}

void MapChunk::clearHeight()
{
  for (int i = 0; i < mapbufsize; ++i)
  {
      mWowVertices[i]._vertex.y = 0.0f;
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
    vmin.y = std::min(vmin.y, mWowVertices[i]._vertex.y);
    vmax.y = std::max(vmax.y, mWowVertices[i]._vertex.y);
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
    xdiff = mWowVertices[i]._vertex.x - pos.x;
    zdiff = mWowVertices[i]._vertex.z - pos.z;
    if (BrushType == eTerrainType_Quadra)
    {
      if ((std::abs(xdiff) < std::abs(radius / 2)) && (std::abs(zdiff) < std::abs(radius / 2)))
      {
        dist = std::sqrt(xdiff*xdiff + zdiff*zdiff);
        mWowVertices[i]._vertex.y += change * (1.0f - dist * inner_radius / radius);
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
              mWowVertices[i]._vertex.y += change;
            break;
          case eTerrainType_Linear:
              mWowVertices[i]._vertex.y += change * (1.0f - dist * (1.0f - inner_radius) / radius);
            break;
          case eTerrainType_Smooth:
              mWowVertices[i]._vertex.y += change / (1.0f + dist / radius);
            break;
          case eTerrainType_Polynom:
              mWowVertices[i]._vertex.y += change*((dist / radius)*(dist / radius) + dist / radius + 1.0f);
            break;
          case eTerrainType_Trigo:
              mWowVertices[i]._vertex.y += change*cos(dist / radius);
            break;
          case eTerrainType_Gaussian:
              mWowVertices[i]._vertex.y += dist < radius * inner_radius ? change * std::exp(-(std::pow(radius * inner_radius / radius, 2) / (2 * std::pow(0.39f, 2)))) : change * std::exp(-(std::pow(dist / radius, 2) / (2 * std::pow(0.39f, 2))));

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
        mWowVertices[i]._mcvv.r = 1.0f; // set default shaders
        mWowVertices[i]._mcvv.g = 1.0f;
        mWowVertices[i]._mcvv.b = 1.0f;
    }

    changed = true;
    header_flags.flags.has_mccv = 1;
    hasMCCV = true;
  }

  for (int i = 0; i < mapbufsize; ++i)
  {
    dist = misc::dist(mWowVertices[i]._vertex, pos);
    if (dist <= radius)
    {
      float edit = change * (1.0f - dist / radius);
      
    mWowVertices[i]._mcvv.r += (1.0f - mWowVertices[i]._mcvv.r) * edit;
    mWowVertices[i]._mcvv.g += (1.0f - mWowVertices[i]._mcvv.g) * edit;
    mWowVertices[i]._mcvv.b += (1.0f - mWowVertices[i]._mcvv.b) * edit;

      mWowVertices[i]._mcvv.r = std::min(std::max(mWowVertices[i]._mcvv.r, 0.0f), 2.0f);
      mWowVertices[i]._mcvv.g = std::min(std::max(mWowVertices[i]._mcvv.g, 0.0f), 2.0f);
      mWowVertices[i]._mcvv.b = std::min(std::max(mWowVertices[i]._mcvv.b, 0.0f), 2.0f);

      changed = true;
    }
  }


  return changed;
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
    float h = chunk->mWowVertices[i + 8]._vertex.y;
    if (mWowVertices[i]._vertex.y != h)
    {
        mWowVertices[i]._vertex.y = h;
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
    float h = chunk->mWowVertices[i + 136]._vertex.y;
    if (mWowVertices[i]._vertex.y != h)
    {
        mWowVertices[i]._vertex.y = h;
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
    if (misc::dist(pos.x, pos.z, mWowVertices[i]._vertex.x, mWowVertices[i]._vertex.z) <= radius)
    {
      vertices.emplace(&mWowVertices[i]._vertex);
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
      if (selected.find(&mWowVertices[index]._vertex) == selected.end())
      {
        not_selected = index;
      }
      else
      {
        count++;
      }
      h += mWowVertices[index]._vertex.y;
      index += (((i+1) % 8) == 0) ? 10 : 1;
    }

    if (count == 2)
    {
        mWowVertices[mid_vertex]._vertex.y = h * 0.25f;
    }
    else if (count == 3)
    {
        mWowVertices[mid_vertex]._vertex.y = (h - mWowVertices[not_selected]._vertex.y) / 3.0f;
    }
  }
}

bool MapChunk::isBorderChunk(std::set<Ogre::Vector3*>& selected)
{
  for (int i = 0; i < mapbufsize; ++i)
  {
    // border chunk if at least a vertex isn't selected
    if (selected.find(&mWowVertices[i]._vertex) == selected.end())
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
