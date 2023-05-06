// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#include "OgreHeader.h"
#include "Misc.h"

#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <vector>


namespace misc
{
  void find_and_replace(std::string& source, const std::string& find, const std::string& replace)
  {
    size_t found = source.rfind(find);
    while (found != std::string::npos) //fixed unknown letters replace. Now it works correctly and replace all found symbold instead of only one at previous versions
    {
      source.replace(found, find.length(), replace);
      found = source.rfind(find);
    }
  }

  float frand()
  {
    return rand() / static_cast<float>(RAND_MAX);
  }

  float randfloat(float lower, float upper)
  {
    return lower + (upper - lower) * frand();
  }

  int randint(int lower, int upper)
  {
    return lower + static_cast<int>((upper + 1 - lower) * frand());
  }

  float dist(float x1, float z1, float x2, float z2)
  {
    float xdiff = x2 - x1, zdiff = z2 - z1;
    return std::sqrt(xdiff*xdiff + zdiff*zdiff);
  }

  float dist(Ogre::Vector3 const& p1, Ogre::Vector3 const& p2)
  {
    return dist(p1.x, p1.z, p2.x, p2.z);
  }

  // return the shortest distance between the point (x, z)
  // and square at (squareX, squareZ) with a size of unitSize
  float getShortestDist(float x, float z, float squareX, float squareZ, float unitSize)
  {
    float px, pz;

    if (x >= squareX && x < squareX + unitSize)
    {
      px = x;
    }
    else
    {
      px = (squareX < x) ? squareX + unitSize : squareX;
    }

    if (z >= squareZ && z < squareZ + unitSize)
    {
      pz = z;
    }
    else
    {
      pz = (squareZ < z) ? squareZ + unitSize : squareZ;
    }

    return (px == x && pz == z) ? 0.0f : dist(x, z, px, pz);
  }

  float getShortestDist(Ogre::Vector3 const& pos, Ogre::Vector3 const& square_pos, float unitSize)
  {
    return getShortestDist(pos.x, pos.z, square_pos.x, square_pos.z, unitSize);
  }

  bool square_is_in_circle(float x, float z, float radius, float square_x, float square_z, float square_size)
  {
    float px, pz;

    if (std::abs(square_x - x) < std::abs(square_x + square_size - x))
    {
      px = square_x + square_size;
    }
    else
    {
      px = square_x;
    }

    if (std::abs(square_z - z) < std::abs(square_z + square_size - z))
    {
      pz = square_z + square_size;
    }
    else
    {
      pz = square_z;
    }

    // check if the furthest is in the circle
    float d = dist(x, z, px, pz);
    return d <= radius;
  }

  bool rectOverlap(Ogre::Vector3 const* r1, Ogre::Vector3 const* r2)
  {
    return r1[0].x <= r2[1].x
      && r2[0].x <= r1[1].x
      && r1[0].z <= r2[1].z
      && r2[0].z <= r1[1].z;
  }

  float angledHeight(
      Ogre::Vector3 const& origin, 
      Ogre::Vector3 const& pos,
      Ogre::Radian const& angle,
      Ogre::Radian const& orientation)
  {
    return ( origin.y
           + (  (pos.x - origin.x) * Ogre::Math::Cos(orientation)
              + (pos.z - origin.z) * Ogre::Math::Sin(orientation)
             ) * Ogre::Math::Tan(angle));
  }

  void extract_v3d_min_max(
      Ogre::Vector3 const& point,
      Ogre::Vector3& min,
      Ogre::Vector3& max)
  {
    min.x = std::min(min.x, point.x);
    max.x = std::max(max.x, point.x);
    min.y = std::min(min.y, point.y);
    max.y = std::max(max.y, point.y);
    min.z = std::min(min.z, point.z);
    max.z = std::max(max.z, point.z);
  }

  std::vector<Ogre::Vector3> intersection_points(
      Ogre::Vector3 const& vmin, 
      Ogre::Vector3 const& vmax)
  {
    std::vector<Ogre::Vector3> points;

    points.emplace_back (vmin.x, vmin.y, vmin.z);
    points.emplace_back (vmin.x, vmin.y, vmax.z);
    points.emplace_back (vmin.x, vmax.y, vmin.z);
    points.emplace_back (vmin.x, vmax.y, vmax.z);
    points.emplace_back (vmax.x, vmin.y, vmin.z);
    points.emplace_back (vmax.x, vmin.y, vmax.z);
    points.emplace_back (vmax.x, vmax.y, vmin.z);
    points.emplace_back (vmax.x, vmax.y, vmax.z);

    return points;
  }

  Ogre::Vector3 transform_model_box_coords(Ogre::Vector3 const& pos)
  {
    return {pos.x, pos.z, -pos.y};
  }

  std::string normalize_adt_filename(std::string filename)
  {
    std::transform (filename.begin(), filename.end(), filename.begin(), ::toupper);
    std::transform ( filename.begin(), filename.end(), filename.begin()
                   , [](char c)
                     {
                       return c == '/' ? '\\' : c;
                     }
                   );
    return filename;
  }

  bool vec3d_equals(Ogre::Vector3 const& v1, Ogre::Vector3 const& v2)
  {
    return float_equals(v1.x, v2.x) && float_equals(v1.y, v2.y) && float_equals(v1.z, v2.z);
  }
}

void SetChunkHeader(sExtendableArray& pArray, int pPosition, int pMagix, int pSize)
{
  sChunkHeader* Header = pArray.GetPointer<sChunkHeader>(pPosition);
  Header->mMagic = pMagix;
  Header->mSize = pSize;
}

bool pointInside(Ogre::Vector3 point, Ogre::Vector3 extents[2])
{
  minmax(&extents[0], &extents[1]);

  return point.x >= extents[0].x && point.z >= extents[0].z &&
    point.x <= extents[1].x && point.z <= extents[1].z;
}

void minmax(Ogre::Vector3* a, Ogre::Vector3* b)
{
  if (a->x > b->x)
  {
    std::swap(a->x, b->x);
  }
  if (a->y > b->y)
  {
    std::swap(a->y, b->y);
  }
  if (a->z > b->z)
  {
    std::swap(a->z, b->z);
  }
}
