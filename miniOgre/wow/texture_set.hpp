// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#pragma once


#include <alphamap.hpp>
#include <MapHeaders.h>

#include <optional>
#include <cstdint>
#include <array>

class Brush;
class MapTile;

struct tmp_edit_alpha_values
{
  using alpha_layer = std::array<float, 64 * 64>;
  // use 4 "alphamaps" for an easier editing
  std::array<alpha_layer, 4> map;

  alpha_layer& operator[](std::size_t i)
  {
    return map.at(i);
  }
};

class TextureSet
{
public:
  TextureSet() = delete;
  TextureSet(
      MapChunkHeader const& header,
      std::shared_ptr<DataStream>& stream,
      size_t base, 
      MapTile* tile, 
      bool use_big_alphamaps, 
      bool do_not_fix_alpha_map, 
      bool do_not_convert_alphamaps);

  std::shared_ptr<OgreTexture> createAlphaMapTexture(const std::string& name);

  Ogre::Vector2 anim_uv_offset(int id, int animtime) const;

  const std::string& filename(size_t id);

  size_t const& num() const { return nTextures; }
  unsigned int flag(size_t id);
  unsigned int effect(size_t id);
  bool is_animated(std::size_t id) const;
  void change_texture_flag(std::string const& tex, std::size_t flag, bool add);

  void convertToBigAlpha();
  void convertToOldAlpha();

  std::string texture(size_t id);

  void bind_alpha(std::size_t id);

  std::vector<uint8_t> lod_texture_map();

private:
  int get_texture_index_or_add (std::string texture, float target);

  uint8_t sum_alpha(size_t offset) const;

  void alphas_to_big_alpha(uint8_t* dest);
  void alphas_to_old_alpha(uint8_t* dest);

  void update_lod_texture_map();

  std::vector<std::string> textures;
  std::array<std::optional<Alphamap>, 3> alphamaps;
  bool _need_amap_update = true;
  size_t nTextures;

  std::vector<uint8_t> _lod_texture_map;
  bool _need_lod_texture_map_update = false;

  ENTRY_MCLY _layers_info[4];


  void create_temporary_alphamaps_if_needed();

  bool _do_not_convert_alphamaps;
};
