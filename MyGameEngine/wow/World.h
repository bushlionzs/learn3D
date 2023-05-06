// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#pragma once

#include <optional>
#include <map>
#include <string>
#include <unordered_set>
#include <vector>
#include <Selection.h>
#include "tile_index.hpp"
#include "map_index.hpp"

namespace noggit
{
  struct object_paste_params;
}

class Brush;
class MapTile;
class ModelInstance;
static const float detail_size = 8.0f;
static const float highresdistance = 384.0f;
static const float modeldrawdistance = 384.0f;
static const float doodaddrawdistance = 64.0f;

using StripType = uint16_t;

class World
{
private:
  std::unordered_map<std::string, std::vector<ModelInstance*>> _models_by_filename;

public:
  MapIndex mapIndex;

  // Temporary variables for loading a WMO, if we have a global WMO.
  std::string mWmoFilename;
  ENTRY_MODF mWmoEntry;

  // Vertex Buffer Objects for coordinates used for drawing.
  uint32_t detailtexcoords;
  uint32_t alphatexcoords;

  unsigned int getMapID();
  // Time of the day.
  float animtime;
  float time;

  //! \brief Name of this map.
  std::string basename;

  // Dynamic distances for rendering. Actually, these should be the same..
  float fogdistance;
  float culldistance;

  explicit World(const std::string& name, int map_id);

  void initDisplay();

  void update_models_emitters(float dt);
 

  unsigned int getAreaID (Ogre::Vector3 const&);
  void setAreaID(Ogre::Vector3 const& pos, int id, bool adt);

  

private:
  // Information about the currently selected model / WMO / triangle.
  std::vector<selection_type> _current_selection;
  std::optional<Ogre::Vector3> _multi_select_pivot;
  int _selected_model_count = 0;
  void update_selection_pivot();
public:

  std::optional<Ogre::Vector3> const& multi_select_pivot() const { return _multi_select_pivot; }

  // Selection related methods.
  bool is_selected(selection_type selection) const;
  bool is_selected(std::uint32_t uid) const;
  std::vector<selection_type> const& current_selection() const { return _current_selection; }
  std::optional<selection_type> get_last_selected_model() const;
  bool has_selection() const { return !_current_selection.empty(); }
  bool has_multiple_model_selected() const { return _selected_model_count > 1; }
  void set_current_selection(selection_type entry);
  void add_to_selection(selection_type entry);
  void remove_from_selection(selection_type entry);
  void remove_from_selection(std::uint32_t uid);
  void reset_selection();
  void delete_selected_models();

  enum class m2_scaling_type
  {
    set,
    add,
    mult
  };

  void snap_selected_models_to_the_ground();
  void scale_selected_models(float v, m2_scaling_type type);
  void move_selected_models(float dx, float dy, float dz);
  void move_selected_models(Ogre::Vector3 const& delta)
  {
    move_selected_models(delta.x, delta.y, delta.z);
  }
  void set_selected_models_pos(float x, float y, float z, bool change_height = true)
  {
    return set_selected_models_pos({x,y,z}, change_height);
  }
  void set_selected_models_pos(Ogre::Vector3 const& pos, bool change_height = true);
  void rotate_selected_models(Ogre::Degree rx, Ogre::Degree ry, Ogre::Degree rz, bool use_pivot);
  void set_selected_models_rotation(Ogre::Degree rx, Ogre::Degree ry, Ogre::Degree rz);

  bool GetVertex(float x, float z, Ogre::Vector3 *V) const;

  // check if the cursor is under map or in an unloaded tile
  bool isUnderMap(Ogre::Vector3 const& pos);

  template<typename Fun>
    bool for_all_chunks_in_range ( Ogre::Vector3 const& pos
                                 , float radius
                                 , Fun&& /* MapChunk* -> bool changed */
                                 );
  template<typename Fun, typename Post>
    bool for_all_chunks_in_range ( Ogre::Vector3 const& pos
                                 , float radius
                                 , Fun&& /* MapChunk* -> bool changed */
                                 , Post&& /* MapChunk* -> void; called for all changed chunks */
                                 );
  template<typename Fun>
    void for_all_chunks_on_tile (Ogre::Vector3 const& pos, Fun&&);

  template<typename Fun>
    void for_chunk_at(Ogre::Vector3 const& pos, Fun&& fun);
  template<typename Fun>
    auto for_maybe_chunk_at (Ogre::Vector3 const& pos, Fun&& fun) -> std::optional<decltype (fun (nullptr))>;

  template<typename Fun>
    void for_tile_at(const tile_index& pos, Fun&&);

  void changeTerrain(
      Ogre::Vector3 const& pos, 
      float change, float radius, int BrushType, float inner_radius);
  void changeShader(Ogre::Vector3 const& pos, Ogre::ColourValue const& color, float change, float radius, bool editMode);
  Ogre::Vector3 pickShaderColor(Ogre::Vector3 const& pos);
  void flattenTerrain(Ogre::Vector3 const& pos, float remain, float radius, int BrushType, flatten_mode const& mode, const Ogre::Vector3& origin, Ogre::Degree angle, Ogre::Degree orientation);
  void blurTerrain(Ogre::Vector3 const& pos, float remain, float radius, int BrushType, flatten_mode const& mode);

  void eraseTextures(Ogre::Vector3 const& pos);
 void setBaseTexture(Ogre::Vector3 const& pos);
  void clear_shadows(Ogre::Vector3 const& pos);
  void clearTextures(Ogre::Vector3 const& pos);

  void removeTexDuplicateOnADT(Ogre::Vector3 const& pos);

  void setHole(Ogre::Vector3 const& pos, bool big, bool hole);
  void setHoleADT(Ogre::Vector3 const& pos, bool hole);

  void addM2 ( std::string const& filename
             , Ogre::Vector3 newPos
             , float scale, Ogre::Vector3 rotation
             , noggit::object_paste_params*
             );
  void addWMO ( std::string const& filename
              , Ogre::Vector3 newPos
              , Ogre::Vector3 rotation
              );

  // add a m2 instance to the world (needs to be positioned already), return the uid
  std::uint32_t add_model_instance(Ogre::Entity* entity, bool from_reloading);
  // add a wmo instance to the world (needs to be positioned already), return the uid
  std::uint32_t add_wmo_instance(Ogre::Entity* entity, bool from_reloading);

  std::optional<selection_type> get_model(std::uint32_t uid);
  void remove_models_if_needed(std::vector<uint32_t> const& uids);

  void reload_tile(tile_index const& tile);

  void updateTilesEntry(selection_type const& entry, model_update type);
  void updateTilesWMO(WMOInstance* wmo, model_update type, bool from_reloading = false);
  void updateTilesModel(ModelInstance* m2, model_update type, bool from_reloading = false);
  void wait_for_all_tile_updates();

  void saveMap (int width, int height);

  void deleteModelInstance(int pUniqueID);
  void deleteWMOInstance(int pUniqueID);

  bool uid_duplicates_found() const;
  void delete_duplicate_model_and_wmo_instances();
  // used after the uid fix all
  void unload_every_model_and_wmo_instance();

	static bool IsEditableWorld(int pMapId);

  void clearHeight(Ogre::Vector3 const& pos);
  void clearAllModelsOnADT(tile_index const& tile);

 
  void CropWaterADT(const tile_index& pos);
  void setWaterType(const tile_index& pos, int type, int layer);
  int getWaterType(const tile_index& tile, int layer);
  void autoGenWaterTrans(const tile_index&, float factor);


  void fixAllGaps();

  void convert_alphamap(bool to_big_alpha);

  bool deselectVertices(Ogre::Vector3 const& pos, float radius);
  void selectVertices(Ogre::Vector3 const& pos, float radius);

  void moveVertices(float h);
  void orientVertices ( Ogre::Vector3 const& ref_pos
                      , Ogre::Degree vertex_angle
                      , Ogre::Degree vertex_orientation
                      );
  void flattenVertices (float height);

  void updateSelectedVertices();
  void updateVertexCenter();
  void clearVertexSelection();

  Ogre::Vector3 const& vertexCenter();

  void recalc_norms (MapChunk*) const;

  bool need_model_updates = false;

private:
  void update_models_by_filename();

  std::set<MapChunk*>& vertexBorderChunks();

  std::set<MapTile*> _vertex_tiles;
  std::set<MapChunk*> _vertex_chunks;
  std::set<MapChunk*> _vertex_border_chunks;
  std::set<Ogre::Vector3*> _vertices_selected;
  Ogre::Vector3 _vertex_center;
  bool _vertex_center_updated = false;
  bool _vertex_border_updated = false;

  bool _display_initialized = false;

  float _view_distance;
};
