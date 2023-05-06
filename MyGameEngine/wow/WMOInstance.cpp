// This file is part of Noggit3, licensed under GNU General Public License (version 3).


#include "OgreHeader.h"
#include <MapHeaders.h>
#include <Misc.h> // checkinside
#include <WMO.h> // WMO
#include <WMOInstance.h>


WMOInstance::WMOInstance(std::string const& filename, ENTRY_MODF const* d)
  :pos(Ogre::Vector3(d->pos[0], d->pos[1], d->pos[2]))
  , dir(Ogre::Vector3(d->rot[0], d->rot[1], d->rot[2]))
  , mUniqueID(d->uniqueID), mFlags(d->flags)
  , mUnknown(d->unknown), mNameset(d->nameSet)
  , _doodadset(d->doodadSet)
{
  extents[0] = Ogre::Vector3(d->extents[0][0], d->extents[0][1], d->extents[0][2]);
  extents[1] = Ogre::Vector3(d->extents[1][0], d->extents[1][1], d->extents[1][2]);

  update_transform_matrix();
  change_doodadset(_doodadset);
}

WMOInstance::WMOInstance(std::string const& filename)
  : pos(Ogre::Vector3(0.0f, 0.0f, 0.0f))
  , dir(Ogre::Vector3(0.0f, 0.0f, 0.0f))
  , mUniqueID(0)
  , mFlags(0)
  , mUnknown(0)
  , mNameset(0)
  , _doodadset(0)
{
  change_doodadset(_doodadset);
}

bool WMOInstance::is_a_duplicate_of(WMOInstance const& other)
{
    return false;
}



void WMOInstance::update_transform_matrix()
{
 
}

void WMOInstance::intersect (Ogre::Ray const& ray, selection_result* results)
{
  
}

void WMOInstance::recalcExtents()
{
  
}

bool WMOInstance::isInsideRect(Ogre::Vector3 rect[2]) const
{
  return misc::rectOverlap(extents, rect);
}

void WMOInstance::change_doodadset(uint16_t doodad_set)
{


 
}

void WMOInstance::update_doodads()
{
 
}

void WMOInstance::resetDirection()
{
  dir = Ogre::Vector3(0.0f, dir.y, 0.0f);
  recalcExtents();
}

