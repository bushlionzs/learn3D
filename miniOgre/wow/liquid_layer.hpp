// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#pragma once


#include "MapHeaders.h"



class MapChunk;
class sExtendableArray;


// handle liquids like oceans, lakes, rivers, slime, magma
class liquid_layer
{
public:
  liquid_layer() = delete;
  liquid_layer(Ogre::Vector3 const& base, float height, int liquid_id);
  liquid_layer(Ogre::Vector3 const& base, mclq& liquid, int liquid_id);
  liquid_layer(
      std::shared_ptr<DataStream>& stream, 
      std::size_t base_pos, 
      Ogre::Vector3 const& base,
      MH2O_Information const& info, 
      std::uint64_t infomask);

  liquid_layer(liquid_layer const& other);
  liquid_layer (liquid_layer&&);

  liquid_layer& operator=(liquid_layer&&);
  liquid_layer& operator=(liquid_layer const& other);

  void save(sExtendableArray& adt, int base_pos, int& info_pos, int& current_pos) const;

  void update_indices();
  void changeLiquidID(int id);

  void crop(MapChunk* chunk);
  void update_opacity(MapChunk* chunk, float factor);


  float min() const { return _minimum; }
  float max() const { return _maximum; }
  int liquidID() const { return _liquid_id; }

  bool hasSubchunk(int x, int z, int size = 1) const;
  void setSubchunk(int x, int z, bool water);

  bool empty() const { return !_subchunks; }
  bool full() const { return _subchunks == std::uint64_t(-1); }
  void clear() { _subchunks = std::uint64_t(0); }


  void copy_subchunk_height(int x, int z, liquid_layer const& from);

private:
  void update_min_max();
  void update_vertex_opacity(int x, int z, MapChunk* chunk, float factor);
  int get_lod_level(Ogre::Vector3 const& camera_pos) const;
  void set_lod_level(int lod_level);

  static int const lod_count = 4;

  int _current_lod_level = -1;
  int _current_lod_indices_count = 0;



  int _liquid_id;
  int _liquid_vertex_format;
  float _minimum;
  float _maximum;
  std::uint64_t _subchunks;
  std::vector<Ogre::Vector3> _vertices;
  std::vector<float> _depth;
  std::vector<Ogre::Vector2> _tex_coords;
  std::map<int, std::vector<std::uint16_t>> _indices_by_lod;

  bool _need_buffer_update = true;
  bool _vao_need_update = true;
  bool _uploaded = false;

  void upload();
  void update_buffers();


private:
    Ogre::Vector3 pos;
};
