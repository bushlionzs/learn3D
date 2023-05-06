// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#pragma once


#include <tool_enums.hpp>
#include <wmo_liquid.hpp>
#include <AsyncObject.h>
#include "OgreColourValue.h"
#include <optional>

#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <optional>

class WMO;
class WMOGroup;
class WMOInstance;
class WMOManager;
class wmo_liquid;
class Model;

struct wmo_batch
{
  int8_t unused[12];

  uint32_t index_start;
  uint16_t index_count;
  uint16_t vertex_start;
  uint16_t vertex_end;

  uint8_t flags;
  uint8_t texture;
};

union wmo_group_flags
{
  uint32_t value;
  struct
  {
    uint32_t has_bsp_tree : 1; // 0x1
    uint32_t has_light_map : 1; // 0x2
    uint32_t has_vertex_color : 1; // 0x4
    uint32_t exterior : 1; // 0x8
    uint32_t flag_0x10 : 1;
    uint32_t flag_0x20 : 1;
    uint32_t exterior_lit : 1; // 0x40
    uint32_t unreacheable : 1; // 0x80
    uint32_t flag_0x100: 1;
    uint32_t has_light : 1; // 0x200
    uint32_t flag_0x400 : 1;
    uint32_t has_doodads : 1; // 0x800
    uint32_t has_water : 1; // 0x1000
    uint32_t indoor : 1; // 0x2000
    uint32_t flag_0x4000 : 1;
    uint32_t flag_0x8000 : 1;
    uint32_t always_draw : 1; // 0x10000
    uint32_t has_mori_morb : 1; // 0x20000, cata+ only (?)
    uint32_t skybox : 1; // 0x40000
    uint32_t ocean : 1; // 0x80000
    uint32_t flag_0x100000 : 1;
    uint32_t mount_allowed : 1; // 0x200000
    uint32_t flag_0x400000 : 1;
    uint32_t flag_0x800000 : 1;
    uint32_t use_mocv2_for_texture_blending : 1; // 0x1000000
    uint32_t has_two_motv : 1; // 0x2000000
    uint32_t antiportal : 1; // 0x4000000
    uint32_t unk : 1; // 0x8000000 requires intBatchCount == 0, extBatchCount == 0, UNREACHABLE. 
    uint32_t unused : 4;
  };
};
static_assert ( sizeof (wmo_group_flags) == sizeof (std::uint32_t)
              , "bitfields shall be implemented packed"
              );

struct wmo_group_header
{
  uint32_t group_name; // offset into MOGN
  uint32_t descriptive_group_name; // offset into MOGN
  wmo_group_flags flags;
  float box1[3];
  float box2[3];
  uint16_t portal_start;
  uint16_t portal_count;
  uint16_t transparency_batches_count;
  uint16_t interior_batch_count;
  uint16_t exterior_batch_count;
  uint16_t padding_or_batch_type_d; // probably padding, but might be data?
  uint8_t fogs[4];
  uint32_t group_liquid; // used for MLIQ
  uint32_t id;
  int32_t unk2, unk3;
};

class WMOGroup 
{
public:
  WMOGroup(WMO *wmo, std::shared_ptr<DataStream>& stream, int num, char const* names);
  WMOGroup(WMOGroup const&);

  void load();

  

  void setupFog (bool draw_fog, std::function<void (bool)> setup_fog);

  void intersect (Ogre::Ray const&, std::vector<float>* results) const;


  std::vector<uint16_t> doodad_ref() const { return _doodad_ref; }

  Ogre::Vector3 BoundingBoxMin;
  Ogre::Vector3 BoundingBoxMax;
  Ogre::Vector3 VertexBoxMin;
  Ogre::Vector3 VertexBoxMax;

  bool use_outdoor_lights;
  std::string name;

  bool has_skybox() const { return header.flags.skybox; }

private:
  void load_mocv(std::shared_ptr<DataStream>& stream, uint32_t size);
  void fix_vertex_color_alpha();

  WMO *wmo;
  wmo_group_header header;
  Ogre::Vector3 center;
  float rad;
  int32_t num;
  int32_t fog;
  std::vector<uint16_t> _doodad_ref;
  std::unique_ptr<wmo_liquid> lq;

  std::vector<wmo_batch> _batches;

  std::vector<Ogre::Vector3> _vertices;
  std::vector<Ogre::Vector3> _normals;
  std::vector<Ogre::Vector2> _texcoords;
  std::vector<Ogre::Vector2> _texcoords_2;
  std::vector<Ogre::ColourValue> _vertex_colors;
  std::vector<uint16_t> _indices;



  bool _uploaded = false;
  bool _vao_is_setup = false;

  void upload();

};

struct WMOLight {
  uint32_t flags, color;
  Ogre::Vector3 pos;
  float intensity;
  float unk[5];
  float r;

  Ogre::ColourValue fcolor;

  void init(std::shared_ptr<DataStream>& stream);


  static void setupOnce(uint32_t, Ogre::Vector3, Ogre::Vector3);
};

struct WMOPV {
    Ogre::Vector3 a, b, c, d;
};

struct WMOPR {
  int16_t portal, group, dir, reserved;
};

struct WMODoodadSet {
  char name[0x14];
  int32_t start;
  int32_t size;
  int32_t unused;
};

struct WMOFog {
  unsigned int flags;
  Ogre::Vector3 pos;
  float r1, r2, fogend, fogstart;
  unsigned int color1;
  float f2;
  float f3;
  unsigned int color2;
  // read to here (0x30 bytes)
  Ogre::ColourValue color;
  void init(std::shared_ptr<DataStream>& stream);
  void setup();
};

union mohd_flags
{
  std::uint16_t flags;
  struct
  {
    std::uint16_t do_not_attenuate_vertices_based_on_distance_to_portal : 1;
    std::uint16_t use_unified_render_path : 1;
    std::uint16_t use_liquid_type_dbc_id : 1;
    std::uint16_t do_not_fix_vertex_color_alpha : 1;
    std::uint16_t unused : 12;
  };
};
static_assert ( sizeof (mohd_flags) == sizeof (std::uint16_t)
              , "bitfields shall be implemented packed"
              );

class WMO : public AsyncObject
{
public:
  explicit WMO(const std::string& name);

  std::vector<float> intersect (Ogre::Ray const&) const;

  void finishLoading();

  bool draw_group_boundingboxes;

  bool _finished_upload;

  std::vector<WMOGroup> groups;
  std::vector<WMOMaterial> materials;
  Ogre::Vector3 extents[2];
  std::vector<std::string> models;
  std::vector<Ogre::Vector3> model_nearest_light_vector;

  std::vector<WMOLight> lights;
  Ogre::ColourValue ambient_light_color;

  mohd_flags flags;

  std::vector<WMOFog> fogs;

  std::vector<WMODoodadSet> doodadsets;


  bool is_hidden() const { return _hidden; }
  void toggle_visibility() { _hidden = !_hidden; }
  void show() { _hidden = false ; }

  virtual bool is_required_when_saving() const
  {
    return true;
  }

private:
  bool _hidden = false;
};
