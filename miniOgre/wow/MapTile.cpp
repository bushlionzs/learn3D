// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#include "OgreHeader.h"
#include "MapTile.h"
#include "OgreResourceManager.h"
#include "OgreDataStream.h"
#include "myutils.h"
#include "Misc.h"
#include "M2Loader.h"
#include "OgreSceneManager.h"
#include "OgreMeshManager.h"
#include "OgreEntity.h"
#include "OgreRoot.h"
#include <algorithm>
#include <cassert>
#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>

MapTile::MapTile( int pX
                , int pZ
                , std::string const& pFilename
                , bool pBigAlpha
                , bool pLoadModels
                , bool use_mclq_green_lava
                , bool reloading_tile
                , World* world
                , tile_mode mode
                )
  :AsyncObject(pFilename)
  ,index(tile_index(pX, pZ))
  , xbase(pX * TILESIZE)
  , zbase(pZ * TILESIZE)
  , changed(false)
  , Water (this, xbase, zbase, use_mclq_green_lava)
  , _mode(mode)
  , _tile_is_being_reloaded(reloading_tile)
  , mBigAlpha(pBigAlpha)
  , _load_models(pLoadModels)
  , _world(world)
{
}

MapTile::~MapTile()
{
 
}

void MapTile::finishLoading()
{

    auto stream = ResourceManager::getSingleton().openResource(filename);
  //MPQFile theFile(filename);

 
  // - Parsing the file itself. --------------------------

  // We store this data to load it at the end.
  uint32_t lMCNKOffsets[256];
  std::vector<ENTRY_MDDF> lModelInstances;
  std::vector<ENTRY_MODF> lWMOInstances;

  uint32_t fourcc;
  uint32_t size;

  MHDR Header;

  // - MVER ----------------------------------------------

  uint32_t version;

  stream->read(&fourcc, 4);
  stream->seekRelative(4);
  stream->read(&version, 4);

  assert(fourcc == 'MVER' && version == 18);

  // - MHDR ----------------------------------------------

  stream->read(&fourcc, 4);
  stream->seekRelative(4);

  assert(fourcc == 'MHDR');

  stream->read(&Header, sizeof(MHDR));

  mFlags = Header.flags;

  // - MCIN ----------------------------------------------

  stream->seek(Header.mcin + 0x14);
  stream->read(&fourcc, 4);
  stream->seekRelative(4);

  assert(fourcc == 'MCIN');

  for (int i = 0; i < 256; ++i)
  {
     stream->read(&lMCNKOffsets[i], 4);
     stream->seekRelative(0xC);
  }

  // - MTEX ----------------------------------------------

  stream->seek(Header.mtex + 0x14);
  stream->read(&fourcc, 4);
  stream->read(&size, 4);

  assert(fourcc == 'MTEX');
  std::string name;
  {
    char const* lCurPos = reinterpret_cast<char const*>(stream->getCurrentStreamData());
    char const* lEnd = lCurPos + size;
    
    while (lCurPos < lEnd)
    {
        name = lCurPos;
        stringToUpper(name);
        mTextureFilenames.push_back(name);
        lCurPos += strlen(lCurPos) + 1;
    }
  }

  if (_load_models)
  {
    // - MMDX ----------------------------------------------

      stream->seek(Header.mmdx + 0x14);
      stream->read(&fourcc, 4);
      stream->read(&size, 4);

    assert(fourcc == 'MMDX');

    {
      char const* lCurPos = reinterpret_cast<char const*>(stream->getCurrentStreamData());
      char const* lEnd = lCurPos + size;

      while (lCurPos < lEnd)
      {
          name = lCurPos;
          std::size_t found;
          if ((found = name.rfind(".mdx")) != std::string::npos)
          {
              name.replace(found, 4, ".m2");
          }
          stringToUpper(name);
          
        mModelFilenames.push_back(name);
        lCurPos += strlen(lCurPos) + 1;
      }
    }

    // - MWMO ----------------------------------------------

    stream->seek(Header.mwmo + 0x14);
    stream->read(&fourcc, 4);
    stream->read(&size, 4);

    assert(fourcc == 'MWMO');

    {
      char const* lCurPos = reinterpret_cast<char const*>(stream->getCurrentStreamData());
      char const* lEnd = lCurPos + size;

      while (lCurPos < lEnd)
      {
          name = lCurPos;
          stringToUpper(name);
        mWMOFilenames.push_back(name);
        lCurPos += strlen(lCurPos) + 1;
      }
    }

    // - MDDF ----------------------------------------------

    stream->seek(Header.mddf + 0x14);
    stream->read(&fourcc, 4);
    stream->read(&size, 4);

    assert(fourcc == 'MDDF');

    ENTRY_MDDF const* mddf_ptr = reinterpret_cast<ENTRY_MDDF const*>(stream->getCurrentStreamData());
    for (unsigned int i = 0; i < size / sizeof(ENTRY_MDDF); ++i)
    {
      lModelInstances.push_back(mddf_ptr[i]);
    }

    // - MODF ----------------------------------------------

    stream->seek(Header.modf + 0x14);
    stream->read(&fourcc, 4);
    stream->read(&size, 4);

    assert(fourcc == 'MODF');

    ENTRY_MODF const* modf_ptr = reinterpret_cast<ENTRY_MODF const*>(stream->getCurrentStreamData());
    for (unsigned int i = 0; i < size / sizeof(ENTRY_MODF); ++i)
    {
      lWMOInstances.push_back(modf_ptr[i]);
    }
  }

  // - MISC ----------------------------------------------

  //! \todo  Parse all chunks in the new style!

  // - MH2O ----------------------------------------------
  if (Header.mh2o != 0) {
      stream->seek(Header.mh2o + 0x14);
      stream->read(&fourcc, 4);
      stream->read(&size, 4);

    int ofsW = Header.mh2o + 0x14 + 0x8;
    assert(fourcc == 'MH2O');

    Water.readFromFile(stream, ofsW);
  }

  // - MFBO ----------------------------------------------

  if (mFlags & 1)
  {
      stream->seek(Header.mfbo + 0x14);
      stream->read(&fourcc, 4);
      stream->read(&size, 4);

    assert(fourcc == 'MFBO');

    int16_t mMaximum[9], mMinimum[9];
    stream->read(mMaximum, sizeof(mMaximum));
    stream->read(mMinimum, sizeof(mMinimum));

    const float xPositions[] = { this->xbase, this->xbase + 266.0f, this->xbase + 533.0f };
    const float yPositions[] = { this->zbase, this->zbase + 266.0f, this->zbase + 533.0f };

    for (int y = 0; y < 3; y++)
    {
      for (int x = 0; x < 3; x++)
      {
        int pos = x + y * 3;
        // fix bug with old noggit version inverting values
        auto&& z{ std::minmax (mMinimum[pos], mMaximum[pos]) };

        mMinimumValues[pos] = { xPositions[x], static_cast<float>(z.first), yPositions[y] };
        mMaximumValues[pos] = { xPositions[x], static_cast<float>(z.second), yPositions[y] };
      }
    }
  }

  

  // - Load textures -------------------------------------

  //! \note We no longer pre load textures but the chunks themselves do.

  if (_load_models)
  {
    // - Load WMOs -----------------------------------------

    for (auto const& object : lWMOInstances)
    {
      
    }

    // - Load M2s ------------------------------------------

    for (auto const& model : lModelInstances)
    {
        createModel(model);
    }

   
  }

  // - Load chunks ---------------------------------------

  for (int nextChunk = 0; nextChunk < 256; ++nextChunk)
  {
      stream->seek(lMCNKOffsets[nextChunk]);
    mChunks[nextChunk / 16][nextChunk % 16] = std::make_unique<MapChunk> (this, stream, mBigAlpha, _mode);
  }


  // - Really done. --------------------------------------

  finished = true;
  _tile_is_being_reloaded = false;
}

bool MapTile::isTile(int pX, int pZ)
{
  return pX == index.x && pZ == index.z;
}

float MapTile::getMaxHeight()
{
  float maxHeight = -99999.0f;
  for (int nextChunk = 0; nextChunk < 256; ++nextChunk)
  {
    maxHeight = std::max((float)mChunks[nextChunk / 16][nextChunk % 16]->vmax.y, maxHeight);
  }
  return maxHeight;
}

void MapTile::convert_alphamap(bool to_big_alpha)
{
  mBigAlpha = true;
  for (size_t i = 0; i < 16; i++)
  {
    for (size_t j = 0; j < 16; j++)
    {
      mChunks[i][j]->use_big_alphamap = to_big_alpha;
    }
  }
}




MapChunk* MapTile::getChunk(unsigned int x, unsigned int z)
{
  if (x < 16 && z < 16)
  {
    return mChunks[z][x].get();
  }
  else
  {
    return nullptr;
  }
}

std::vector<MapChunk*> MapTile::chunks_in_range (Ogre::Vector3 const& pos, float radius) const
{
  std::vector<MapChunk*> chunks;

  for (size_t ty (0); ty < 16; ++ty)
  {
    for (size_t tx (0); tx < 16; ++tx)
    {
      if (misc::getShortestDist (pos.x, pos.z, mChunks[ty][tx]->xbase, mChunks[ty][tx]->zbase, CHUNKSIZE) <= radius)
      {
        chunks.emplace_back (mChunks[ty][tx].get());
      }
    }
  }

  return chunks;
}


bool MapTile::GetVertex(float x, float z, Ogre::Vector3 *V)
{
  int xcol = (int)((x - xbase) / CHUNKSIZE);
  int ycol = (int)((z - zbase) / CHUNKSIZE);

  return xcol >= 0 && xcol <= 15 && ycol >= 0 && ycol <= 15 && mChunks[ycol][xcol]->GetVertex(x, z, V);
}



void MapTile::saveTile(World* world)
{
 
}


void MapTile::CropWater()
{
  for (int z = 0; z < 16; ++z)
  {
    for (int x = 0; x < 16; ++x)
    {
      Water.CropMiniChunk(x, z, mChunks[z][x].get());
    }
  }
}

void MapTile::remove_model(uint32_t uid)
{
  std::lock_guard<std::mutex> const lock (_mutex);

  auto it = std::find(uids.begin(), uids.end(), uid);

  if (it != uids.end())
  {
    uids.erase(it);
  }
}

void MapTile::add_model(uint32_t uid)
{
  std::lock_guard<std::mutex> const lock(_mutex);

  if (std::find(uids.begin(), uids.end(), uid) == uids.end())
  {
    uids.push_back(uid);
  }
}

inline float normalize_degrees(float deg)
{
    return deg - std::floor((deg + 180.f) / 360.f) * 360.f;
}

void MapTile::createModel(const ENTRY_MDDF& entry)
{
    std::string& modelname = mModelFilenames[entry.nameID];

    auto mesh = MeshManager::getSingleton().load(modelname);

    Ogre::SceneManager* sceneMgr = Ogre::Root::getSingleton().getSceneManager(MAIN_SCENE_MANAGER);

    std::string entryname = modelname + std::to_string(entry.uniqueID);
    Entity* entity = sceneMgr->createEntity(entryname, mesh);
    SceneNode* root = sceneMgr->getRoot();
    SceneNode* node = root->createChildSceneNode(entryname);
    node->attachObject(entity);

    node->setPosition(Ogre::Vector3(entry.pos[0], entry.pos[1], entry.pos[2]));

    Ogre::Vector3 dir = Ogre::Vector3(
        normalize_degrees(entry.rot[0]),
        normalize_degrees(entry.rot[1]),
        normalize_degrees(entry.rot[2]));


    Matrix3 rotMatrix;
    rotMatrix.FromEulerAnglesXYZ(Ogre::Radian(Ogre::Degree(-dir.z)), Ogre::Radian(Ogre::Degree(dir.y - 90.0f)), Ogre::Radian(Ogre::Degree(dir.x)));
    Ogre::Quaternion q(rotMatrix);
    node->setOrientation(q);
    float scale = entry.scale / 1024.0f;

    node->setScale(Ogre::Vector3(scale, scale, scale));

}

void MapTile::createWMO(const ENTRY_MODF& entry)
{

}
