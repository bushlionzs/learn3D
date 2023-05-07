// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#pragma once

#include "MapHeaders.h"
#include "MapTile.h"
#include "tool_enums.hpp"
#include "OgreColourValue.h"
#include "OgreMoveObject.h"

#include <map>
#include <memory>
#include <optional>
#include <functional>
class Brush;
class ChunkWater;
class sExtendableArray;
class MapTile;
class TextureSet;
using StripType = uint16_t;
static const uint32_t mapbufsize = 9 * 9 + 8 * 8; // chunk size

class WowTerrainVertex
{
public:
    Ogre::Vector3 _vertex;
    Ogre::Vector3 _normal;
    Ogre::Vector2 _texCoord;
    Ogre::ColourValue _mcvv;
};
class MapChunk: public MoveObject
{
private:
  tile_mode _mode;

  bool hasMCCV;

  int holes;

  unsigned int areaID;

  void update_shadows();

  uint8_t _shadow_map[64 * 64];

  std::vector<StripType> strip_with_holes;
  std::vector<StripType> strip_without_holes;
  std::map<int, std::vector<StripType>> strip_lods;


  std::vector<uint8_t> compressed_shadow_map() const;
  bool has_shadows() const;

  void initStrip();

  int indexNoLoD(int x, int y);
  int indexLoD(int x, int y);

  std::vector<Ogre::Vector3> _intersect_points;

  void update_intersect_points();

  std::optional<int> get_lod_level(Ogre::Vector3 const& camera_pos
                                    , display_mode display
                                    ) const;

  bool _uploaded = false;
  bool _need_indice_buffer_update = true;
  bool _need_vao_update = true;

  void upload();
  void update_indices_buffer();


public:
  MapChunk(MapTile* mt, std::shared_ptr<DataStream>& stream, bool bigAlpha, tile_mode mode);
  virtual const AxisAlignedBox& getBoundingBox(void) const;

  MapTile *mt;
  Ogre::Vector3 vmin, vmax, vcenter;
  int px, py;

  MapChunkHeader header;

  float xbase, ybase, zbase;

  mcnk_flags header_flags;
  bool use_big_alphamap;
  std::unique_ptr<TextureSet> texture_set;

  WowTerrainVertex mWowVertices[mapbufsize];
  mutable Ogre::AxisAlignedBox mAABB;
  static Ogre::Vector2 mTexCorrd[mapbufsize];

private:


  bool _is_visible = true; // visible by default
  bool _need_visibility_update = true;
  std::optional<int> _lod_level; // none = no lod
  size_t _lod_level_indice_count = 0;
public:

  
  //! \todo only this function should be public, all others should be called from it


    bool ChangeMCCV(
        Ogre::Vector3 const& pos,
        Ogre::ColourValue const& color,
      float change, float radius, bool editMode);
    //Ogre::Vector3 pickMCCV(Ogre::Vector3 const& pos);

  ChunkWater* liquid_chunk() const;

  void updateVerticesData();
  void recalcNorms (std::function<std::optional<float> (float, float)> height);

  //! \todo implement Action stack for these
  bool changeTerrain(Ogre::Vector3 const& pos, float change, float radius, int BrushType, float inner_radius);
  bool flattenTerrain(
      Ogre::Vector3 const& pos,
      float remain,
      float radius,
      int BrushType,
      flatten_mode const& mode,
      const Ogre::Vector3& origin,
      Ogre::Radian angle,
      Ogre::Radian orientation);
  bool blurTerrain (
      Ogre::Vector3 const& pos, 
      float remain, float radius, int BrushType, flatten_mode const& mode
                   , std::function<std::optional<float> (float, float)> height
                   );

  void selectVertex(Ogre::Vector3 const& pos, float radius, std::set<Ogre::Vector3*>& vertices);
  void fixVertices(std::set<Ogre::Vector3*>& selected);
  // for the vertex tool
  bool isBorderChunk(std::set<Ogre::Vector3*>& selected);

  void clear_shadows();

  //! \todo implement Action stack for these
  bool isHole(int i, int j);
  void setHole(Ogre::Vector3 const& pos, bool big, bool add);

  void setFlag(bool value, uint32_t);

  int getAreaID();
  void setAreaID(int ID);

  bool GetVertex(float x, float z, Ogre::Vector3*V);
  float getHeight(int x, int z);
  float getHeight(int index);
  float getMinHeight();

  void clearHeight();

  // fix the gaps with the chunk to the left
  bool fixGapLeft(const MapChunk* chunk);
  // fix the gaps with the chunk above
  bool fixGapAbove(const MapChunk* chunk);
};
