// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#pragma once


#include <WMO.h>
#include <Misc.h>
#include <cstdint>
#include <set>
#include <vector>
#include <Selection.h>
class MPQFile;
struct ENTRY_MODF;

class WMOInstance
{
public:
  Ogre::Vector3 pos;
  Ogre::Vector3  extents[2];
  std::map<int, std::pair<Ogre::Vector3, Ogre::Vector3>> group_extents;
  Ogre::Vector3  dir;
  unsigned int mUniqueID;
  uint16_t mFlags;
  uint16_t mUnknown;
  uint16_t mNameset; 

  uint16_t doodadset() const { return _doodadset; }
  void change_doodadset(uint16_t doodad_set);

private:
  void update_doodads();
  
  uint16_t _doodadset;

  bool _need_doodadset_update = true;

  Ogre::Matrix4 _transform_mat = Ogre::Matrix4::IDENTITY;
  Ogre::Matrix4 _transform_mat_inverted = Ogre::Matrix4::IDENTITY;
  Ogre::Matrix4 _transform_mat_transposed = Ogre::Matrix4::IDENTITY;

public:
  WMOInstance(std::string const& filename, ENTRY_MODF const* d);
  explicit WMOInstance(std::string const& filename);

  WMOInstance(WMOInstance const& other) = default;
  WMOInstance& operator=(WMOInstance const& other) = default;

  WMOInstance (WMOInstance&& other)
    :pos (other.pos)
    , group_extents(other.group_extents)
    , dir (other.dir)
    , mUniqueID (other.mUniqueID)
    , mFlags (other.mFlags)
    , mUnknown (other.mUnknown)
    , mNameset (other.mNameset)
    , _doodadset (other._doodadset)
    , _need_doodadset_update(other._need_doodadset_update)
    , _transform_mat(other._transform_mat)
    , _transform_mat_inverted(other._transform_mat_inverted)
    , _transform_mat_transposed(other._transform_mat_transposed)
  {
    std::swap (extents, other.extents);
  }

  WMOInstance& operator= (WMOInstance&& other)
  {
    std::swap(pos, other.pos);
    std::swap(extents, other.extents);
    std::swap(group_extents, other.group_extents);
    std::swap(dir, other.dir);
    std::swap(mUniqueID, other.mUniqueID);
    std::swap(mFlags, other.mFlags);
    std::swap(mUnknown, other.mUnknown);
    std::swap(mNameset, other.mNameset);
    std::swap(_doodadset, other._doodadset);
    std::swap(_need_doodadset_update, other._need_doodadset_update);
    std::swap(_transform_mat, other._transform_mat);
    std::swap(_transform_mat_inverted, other._transform_mat_inverted);
    std::swap(_transform_mat_transposed, other._transform_mat_transposed);
    return *this;
  }
  /*
  bool operator==(WMOInstance&& other) const
  {
      return this->mUniqueID == other.mUniqueID;
  }*/

  bool is_a_duplicate_of(WMOInstance const& other);

  

  void update_transform_matrix();

  Ogre::Matrix4 transform_matrix() const { return _transform_mat; }
  Ogre::Matrix4 transform_matrix_inverted() const { return _transform_mat_inverted; }
  Ogre::Matrix4 transform_matrix_transposed() const { return _transform_mat_transposed; }

  void intersect (Ogre::Ray const&, selection_result*);

  void recalcExtents();
  void resetDirection();

  bool isInsideRect(Ogre::Vector3 rect[2]) const;

};
