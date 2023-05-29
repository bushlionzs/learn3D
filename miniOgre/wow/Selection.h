// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#pragma once

#include "OgreHeader.h"
#include <variant>

#include <string>
#include <vector>

class ModelInstance;
class WMOInstance;
class MapChunk;

struct selected_chunk_type
{
  selected_chunk_type(MapChunk* _chunk, int _triangle, Ogre::Vector3 _position)
    : chunk(_chunk)
    , triangle(_triangle)
    , position(_position)
  {}

  MapChunk* chunk;
  int triangle;
  Ogre::Vector3 position;

  bool operator== (selected_chunk_type const& other) const
  {
    return chunk == other.chunk;
  }
};

using selected_model_type = ModelInstance*;
using selected_wmo_type = WMOInstance*;
using selection_type = std::variant < selected_model_type
                                      , selected_wmo_type
                                      , selected_chunk_type
                                      >;
//! \note Keep in same order as variant!
enum eSelectionEntryTypes
{
  eEntry_Model,
  eEntry_WMO,
  eEntry_MapChunk
};

using selection_entry = std::pair<float, selection_type>;
using selection_result = std::vector<selection_entry>;
