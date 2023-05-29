// This file is part of Noggit3, licensed under GNU General Public License (version 3).

#include "OgreHeader.h"
#include <WMO.h>
#include "OgreResourceManager.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>


WMO::WMO(const std::string& filenameArg)
  : AsyncObject(filenameArg)
  , _finished_upload(false)
{
}

void WMO::finishLoading ()
{
    std::shared_ptr<DataStream> stream = ResourceManager::getSingleton().openResource(filename);
    if (!stream) {
    return;
    }

  uint32_t fourcc;
  uint32_t size;

  float ff[3];

  char const* ddnames = nullptr;
  char const* groupnames = nullptr;

  // - MVER ----------------------------------------------

  uint32_t version;

  stream->read (&fourcc, 4);
  stream->seekRelative (4);
  stream->read (&version, 4);

  assert (fourcc == 'MVER' && version == 17);

  // - MOHD ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->seekRelative (4);

  assert (fourcc == 'MOHD');

  CArgb ambient_color;
  unsigned int nTextures, nGroups, nP, nLights, nModels, nDoodads, nDoodadSets, nX;
  // header
  stream->read (&nTextures, 4);
  stream->read (&nGroups, 4);
  stream->read (&nP, 4);
  stream->read (&nLights, 4);
  stream->read (&nModels, 4);
  stream->read (&nDoodads, 4);
  stream->read (&nDoodadSets, 4);
  stream->read (&ambient_color, 4);
  stream->read (&nX, 4);
  stream->read (ff, 12);
  extents[0] = Ogre::Vector3(ff[0], ff[1], ff[2]);
  stream->read (ff, 12);
  extents[1] = Ogre::Vector3(ff[0], ff[1], ff[2]);
  stream->read(&flags, 2);

  stream->seekRelative (2);

  ambient_light_color.r = static_cast<float>(ambient_color.r) / 255.f;
  ambient_light_color.g = static_cast<float>(ambient_color.g) / 255.f;
  ambient_light_color.b = static_cast<float>(ambient_color.b) / 255.f;
  ambient_light_color.a = static_cast<float>(ambient_color.a) / 255.f;

  // - MOTX ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->read (&size, 4);

  assert (fourcc == 'MOTX');

  std::vector<char> texbuf (size);
  stream->read (texbuf.data(), texbuf.size());

  // - MOMT ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->read (&size, 4);

  assert (fourcc == 'MOMT');

  std::size_t const num_materials (size / 0x40);
  materials.resize (num_materials);

  std::map<std::uint32_t, std::size_t> texture_offset_to_inmem_index;

  auto load_texture
    ( [&] (std::uint32_t ofs)
      {
      return 0;
      }
    );

  for (size_t i(0); i < num_materials; ++i)
  {
      stream->read(&materials[i], sizeof(WMOMaterial));

    uint32_t shader = materials[i].shader;
    bool use_second_texture = (shader == 6 || shader == 5 || shader == 3);

    materials[i].texture1 = load_texture(materials[i].texture_offset_1);
    if (use_second_texture)
    {
      materials[i].texture2 = load_texture(materials[i].texture_offset_2);
    }
  }

  // - MOGN ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->read (&size, 4);

  assert (fourcc == 'MOGN');

  groupnames = reinterpret_cast<char const*> (stream->getCurrentStreamData());

  stream->seekRelative (size);

  // - MOGI ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->read (&size, 4);

  assert (fourcc == 'MOGI');

  for (size_t i (0); i < nGroups; ++i) {
    groups.emplace_back (this, stream, i, groupnames);
  }

  // - MOSB ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->read (&size, 4);

  assert (fourcc == 'MOSB');

  if (size > 4)
  {
    
  }

  stream->seekRelative (size);

  // - MOPV ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->read(&size, 4);

  assert (fourcc == 'MOPV');

  std::vector<Ogre::Vector3> portal_vertices;

  for (size_t i (0); i < size / 12; ++i) {
      stream->read (ff, 12);
    portal_vertices.push_back(Ogre::Vector3(ff[0], ff[2], -ff[1]));
  }

  // - MOPT ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->read (&size, 4);

  assert (fourcc == 'MOPT');

  stream->seekRelative (size);

  // - MOPR ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->read (&size, 4);

  assert(fourcc == 'MOPR');

  stream->seekRelative (size);

  // - MOVV ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->read (&size, 4);

  assert (fourcc == 'MOVV');

  stream->seekRelative (size);

  // - MOVB ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->read (&size, 4);

  assert (fourcc == 'MOVB');

  stream->seekRelative (size);

  // - MOLT ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->seekRelative (4);

  assert (fourcc == 'MOLT');

  for (size_t i (0); i < nLights; ++i) {
    WMOLight l;
    l.init (stream);
    lights.push_back (l);
  }

  // - MODS ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->seekRelative (4);

  assert (fourcc == 'MODS');

  for (size_t i (0); i < nDoodadSets; ++i) {
    WMODoodadSet dds;
    stream->read (&dds, 32);
    doodadsets.push_back (dds);
  }

  // - MODN ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->read (&size, 4);

  assert (fourcc == 'MODN');

  if (size)
  {
    ddnames = reinterpret_cast<char const*> (stream->getCurrentStreamData());
    stream->seekRelative (size);
  }

  // - MODD ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->read (&size, 4);

  assert (fourcc == 'MODD');

  for (size_t i (0); i < size / 0x28; ++i) {
    struct
    {
      uint32_t name_offset : 24;
      uint32_t flag_AcceptProjTex : 1;
      uint32_t flag_0x2 : 1;
      uint32_t flag_0x4 : 1;
      uint32_t flag_0x8 : 1;
      uint32_t flags_unused : 4;
    } x;

    stream->read (&x, sizeof (x));


    model_nearest_light_vector.emplace_back();

    stream->seekRelative(0x28);
  }

  // - MFOG ----------------------------------------------

  stream->read (&fourcc, 4);
  stream->read (&size, 4);

  assert (fourcc == 'MFOG');

  int nfogs = size / 0x30;
  for (size_t i (0); i < nfogs; ++i) {
    WMOFog fog;
    fog.init (stream);
    fogs.push_back (fog);
  }

  for (auto& group : groups)
    group.load();

  finished = true;
  _state_changed.notify_all();
}



std::vector<float> WMO::intersect (Ogre::Ray const& ray) const
{
  std::vector<float> results;

  if (!finishedLoading() || loading_failed())
  {
    return results;
  }

  for (auto& group : groups)
  {
    group.intersect (ray, &results);
  }

  return results;
}





void WMOLight::init(std::shared_ptr<DataStream>& stream)
{
  char type[4];
  stream->read(&type, 4);
  stream->read(&color, 4);
  stream->read(&pos, 12);
  stream->read(&intensity, 4);
  stream->read(unk, 4 * 5);
  stream->read(&r, 4);

  pos = Ogre::Vector3(pos.x, pos.z, -pos.y);

  // rgb? bgr? hm
  float fa = ((color & 0xff000000) >> 24) / 255.0f;
  float fr = ((color & 0x00ff0000) >> 16) / 255.0f;
  float fg = ((color & 0x0000ff00) >> 8) / 255.0f;
  float fb = ((color & 0x000000ff)) / 255.0f;

  fcolor = Ogre::ColourValue(fr, fg, fb, fa);
  fcolor *= intensity;
  fcolor.a = 1.0f;

  /*
  // light logging
  gLog("Light %08x @ (%4.2f,%4.2f,%4.2f)\t %4.2f, %4.2f, %4.2f, %4.2f, %4.2f, %4.2f, %4.2f\t(%d,%d,%d,%d)\n",
  color, pos.x, pos.y, pos.z, intensity,
  unk[0], unk[1], unk[2], unk[3], unk[4], r,
  type[0], type[1], type[2], type[3]);
  */
}


void WMOLight::setupOnce(uint32_t, Ogre::Vector3, Ogre::Vector3)
{
  //math::vector_4d position(dir, 0);
  //math::vector_4d position(0,1,0,0);

  //math::vector_4d ambient = math::vector_4d(light_color * 0.3f, 1);
  //math::vector_4d diffuse = math::vector_4d(light_color, 1);


  //gl.enable(light);
}



WMOGroup::WMOGroup(WMO *_wmo, std::shared_ptr<DataStream>& stream, int _num, char const* names)
  :num(_num)
{
  // extract group info from f
  std::uint32_t flags; // not used, the flags are in the group header
  stream->read(&flags, 4);
  float ff[3];
  stream->read(ff, 12);
  VertexBoxMax = Ogre::Vector3(ff[0], ff[1], ff[2]);
  stream->read(ff, 12);
  VertexBoxMin = Ogre::Vector3(ff[0], ff[1], ff[2]);
  int nameOfs;
  stream->read(&nameOfs, 4);

  //! \todo  get proper name from group header and/or dbc?
  if (nameOfs > 0) {
    name = std::string(names + nameOfs);
  }
  else name = "(no name)";
}

WMOGroup::WMOGroup(WMOGroup const& other)
  : BoundingBoxMin(other.BoundingBoxMin)
  , BoundingBoxMax(other.BoundingBoxMax)
  , VertexBoxMin(other.VertexBoxMin)
  , VertexBoxMax(other.VertexBoxMax)
  , use_outdoor_lights(other.use_outdoor_lights)
  , name(other.name)
  , wmo(other.wmo)
  , header(other.header)
  , center(other.center)
  , rad(other.rad)
  , num(other.num)
  , fog(other.fog)
  , _doodad_ref(other._doodad_ref)
  , _batches(other._batches)
  , _vertices(other._vertices)
  , _normals(other._normals)
  , _texcoords(other._texcoords)
  , _texcoords_2(other._texcoords_2)
  , _vertex_colors(other._vertex_colors)
  , _indices(other._indices)
{
  if (other.lq)
  {
    lq = std::make_unique<wmo_liquid>(*other.lq.get());
  }
}

namespace
{
  Ogre::ColourValue colorFromInt(unsigned int col)
  {
    uint8_t r, g, b, a;
    a = (col & 0xFF000000) >> 24;
    r = (col & 0x00FF0000) >> 16;
    g = (col & 0x0000FF00) >> 8;
    b = (col & 0x000000FF);
    return Ogre::ColourValue(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
  }
}

void WMOGroup::upload()
{
  
}



void WMOGroup::load()
{
  // open group file
  std::stringstream curNum;
  curNum << "_" << std::setw (3) << std::setfill ('0') << num;

  std::string fname = wmo->filename;
  fname.insert (fname.find (".wmo"), curNum.str ());

  std::shared_ptr<DataStream> wmostream = ResourceManager::getSingleton().openResource(fname);

  if (!wmostream) {
    return;
  }

  uint32_t fourcc;
  uint32_t size;

  // - MVER ----------------------------------------------

  wmostream->read (&fourcc, 4);
  wmostream->seekRelative (4);

  uint32_t version;

  wmostream->read (&version, 4);

  assert (fourcc == 'MVER' && version == 17);

  // - MOGP ----------------------------------------------

  wmostream->read (&fourcc, 4);
  wmostream->seekRelative (4);

  assert (fourcc == 'MOGP');

  wmostream->read (&header, sizeof (wmo_group_header));

  WMOFog &wf = wmo->fogs[header.fogs[0]];
  if (wf.r2 <= 0) fog = -1; // default outdoor fog..?
  else fog = header.fogs[0];

  BoundingBoxMin = Ogre::Vector3(header.box1[0], header.box1[2], -header.box1[1]);
  BoundingBoxMax = Ogre::Vector3(header.box2[0], header.box2[2], -header.box2[1]);

  // - MOPY ----------------------------------------------

  wmostream->read (&fourcc, 4);
  wmostream->read (&size, 4);

  assert (fourcc == 'MOPY');

  wmostream->seekRelative (size);

  // - MOVI ----------------------------------------------

  wmostream->read (&fourcc, 4);
  wmostream->read (&size, 4);

  assert (fourcc == 'MOVI');

  _indices.resize (size / sizeof (uint16_t));

  wmostream->read (_indices.data (), size);

  // - MOVT ----------------------------------------------

  wmostream->read (&fourcc, 4);
  wmostream->read (&size, 4);

  assert (fourcc == 'MOVT');

  // let's hope it's padded to 12 bytes, not 16...
  Ogre::Vector3 const* vertices = reinterpret_cast<Ogre::Vector3 const*>(wmostream->getCurrentStreamData());

  VertexBoxMin = Ogre::Vector3(9999999.0f, 9999999.0f, 9999999.0f);
  VertexBoxMax = Ogre::Vector3(-9999999.0f, -9999999.0f, -9999999.0f);

  rad = 0;

  for (size_t i = 0; i < size / sizeof (Ogre::Vector3); ++i) {
      Ogre::Vector3 v (vertices[i].x, vertices[i].z, -vertices[i].y);

    if (v.x < VertexBoxMin.x) VertexBoxMin.x = v.x;
    if (v.y < VertexBoxMin.y) VertexBoxMin.y = v.y;
    if (v.z < VertexBoxMin.z) VertexBoxMin.z = v.z;
    if (v.x > VertexBoxMax.x) VertexBoxMax.x = v.x;
    if (v.y > VertexBoxMax.y) VertexBoxMax.y = v.y;
    if (v.z > VertexBoxMax.z) VertexBoxMax.z = v.z;

    _vertices.push_back (v);
  }

  center = (VertexBoxMax + VertexBoxMin) * 0.5f;
  rad = (VertexBoxMax - center).length () + 300.0f;;

  wmostream->seekRelative (size);

  // - MONR ----------------------------------------------

  wmostream->read (&fourcc, 4);
  wmostream->read (&size, 4);

  assert (fourcc == 'MONR');

  _normals.resize (size / sizeof (Ogre::Vector3));

  wmostream->read (_normals.data (), size);

  for (auto& n : _normals)
  {
    n = {n.x, n.z, -n.y};
  }

  // - MOTV ----------------------------------------------

  wmostream->read (&fourcc, 4);
  wmostream->read (&size, 4);

  assert (fourcc == 'MOTV');

  _texcoords.resize (size / sizeof (Ogre::Vector2));

  wmostream->read (_texcoords.data (), size);

  // - MOBA ----------------------------------------------

  wmostream->read (&fourcc, 4);
  wmostream->read (&size, 4);

  assert (fourcc == 'MOBA');

  _batches.resize (size / sizeof (wmo_batch));
  wmostream->read (_batches.data (), size);

  // - MOLR ----------------------------------------------
  if (header.flags.has_light)
  {
      wmostream->read (&fourcc, 4);
      wmostream->read (&size, 4);

    assert (fourcc == 'MOLR');

    wmostream->seekRelative (size);
  }
  // - MODR ----------------------------------------------
  if (header.flags.has_doodads)
  {
      wmostream->read (&fourcc, 4);
      wmostream->read (&size, 4);

    assert (fourcc == 'MODR');

    _doodad_ref.resize (size / sizeof (int16_t));

    wmostream->read (_doodad_ref.data (), size);
  }
  // - MOBN ----------------------------------------------
  if (header.flags.has_bsp_tree)
  {
      wmostream->read (&fourcc, 4);
      wmostream->read (&size, 4);

    assert (fourcc == 'MOBN');

    wmostream->seekRelative (size);
  }
  // - MOBR ----------------------------------------------
  if (header.flags.has_bsp_tree)
  {
      wmostream->read (&fourcc, 4);
      wmostream->read (&size, 4);

    assert (fourcc == 'MOBR');

    wmostream->seekRelative (size);
  }
  
  if (header.flags.flag_0x400)
  {
    // - MPBV ----------------------------------------------
      wmostream->read (&fourcc, 4);
      wmostream->read (&size, 4);

    assert (fourcc == 'MPBV');

    wmostream->seekRelative (size);

    // - MPBP ----------------------------------------------
    wmostream->read (&fourcc, 4);
    wmostream->read (&size, 4);

    assert (fourcc == 'MPBP');

    wmostream->seekRelative (size);

    // - MPBI ----------------------------------------------
    wmostream->read (&fourcc, 4);
    wmostream->read (&size, 4);

    assert (fourcc == 'MPBI');

    wmostream->seekRelative (size);

    // - MPBG ----------------------------------------------
    wmostream->read (&fourcc, 4);
    wmostream->read (&size, 4);

    assert (fourcc == 'MPBG');

    wmostream->seekRelative (size);
  }
  // - MOCV ----------------------------------------------
  if (header.flags.has_vertex_color)
  {
      wmostream->read (&fourcc, 4);
      wmostream->read (&size, 4);

    assert (fourcc == 'MOCV');

    load_mocv(wmostream, size);
  }
  // - MLIQ ----------------------------------------------
  if (header.flags.has_water)
  {
      wmostream->read (&fourcc, 4);
      wmostream->read (&size, 4);

    assert (fourcc == 'MLIQ');

    WMOLiquidHeader hlq;
    wmostream->read(&hlq, 0x1E);

    lq = std::make_unique<wmo_liquid> (wmostream
                                      , hlq
                                      , wmo->materials[hlq.material_id]
                                      , header.group_liquid
                                      , (bool)wmo->flags.use_liquid_type_dbc_id
                                      , (bool)header.flags.ocean
                                      );

    // creating the wmo liquid doesn't move the position
    wmostream->seekRelative(size - 0x1E);
  }
  if (header.flags.has_mori_morb)
  {
    // - MORI ----------------------------------------------
      wmostream->read (&fourcc, 4);
      wmostream->read (&size, 4);

    assert (fourcc == 'MORI');

    wmostream->seekRelative (size);

    // - MORB ----------------------------------------------
    wmostream->read(&fourcc, 4);
    wmostream->read(&size, 4);

    assert(fourcc == 'MORB');

    wmostream->seekRelative(size);
  }

  // - MOTV ----------------------------------------------
  if (header.flags.has_two_motv)
  {
      wmostream->read (&fourcc, 4);
      wmostream->read (&size, 4);

    assert (fourcc == 'MOTV');

    _texcoords_2.resize(size / sizeof(Ogre::Vector2));
    wmostream->read(_texcoords_2.data(), size);
  }
  // - MOCV ----------------------------------------------
  if (header.flags.use_mocv2_for_texture_blending)
  {
      wmostream->read (&fourcc, 4);
      wmostream->read (&size, 4);

    assert (fourcc == 'MOCV');

    std::vector<CImVector> mocv_2(size / sizeof(CImVector));
    wmostream->read(mocv_2.data(), size);

    for (int i = 0; i < mocv_2.size(); ++i)
    {
      float alpha = static_cast<float>(mocv_2[i].a) / 255.f;

      // the second mocv is used for texture blending only
      if (header.flags.has_vertex_color)
      {
        _vertex_colors[i].a = alpha;
      }
      else // no vertex coloring, only texture blending with the alpha
      {
        _vertex_colors.emplace_back(0.f, 0.f, 0.f, alpha);
      }
    }
  }

  //dl_light = 0;
  // "real" lighting?
  if (header.flags.indoor && header.flags.has_vertex_color)
  {
      Ogre::Vector3 dirmin(1, 1, 1);
    float lenmin;

    

    use_outdoor_lights = false;
  }
  else
  {
    use_outdoor_lights = true;
  }
}

void WMOGroup::load_mocv(std::shared_ptr<DataStream>& stream, uint32_t size)
{
  uint32_t const* colors = reinterpret_cast<uint32_t const*> (stream->getCurrentStreamData());
  _vertex_colors.resize(size / sizeof(uint32_t));

  for (size_t i(0); i < size / sizeof(uint32_t); ++i)
  {
    _vertex_colors[i] = colorFromInt(colors[i]);
  }

  if (wmo->flags.do_not_fix_vertex_color_alpha)
  {
    int interior_batchs_start = 0;

    if (header.transparency_batches_count > 0)
    {
      interior_batchs_start = _batches[header.transparency_batches_count - 1].vertex_end + 1;
    }

    for (int n = interior_batchs_start; n < _vertex_colors.size(); ++n)
    {
      _vertex_colors[n].a = header.flags.exterior ? 1.f : 0.f;
    }
  }
  else
  {
    fix_vertex_color_alpha();
  }

  // there's no read so this is required
  stream->seekRelative(size);
}

void WMOGroup::fix_vertex_color_alpha()
{
  int interior_batchs_start = 0;
  
  if (header.transparency_batches_count > 0)
  {
    interior_batchs_start = _batches[header.transparency_batches_count - 1].vertex_end + 1;
  }

  Ogre::ColourValue wmo_ambient_color;

  if (wmo->flags.use_unified_render_path)
  {
    wmo_ambient_color = Ogre::ColourValue(0.f, 0.f, 0.f, 0.f);
  }
  else
  {
    wmo_ambient_color = wmo->ambient_light_color;
    // w is not used, set it to 0 to avoid changing the vertex color alpha
    wmo_ambient_color.a = 0.f;
  }

  for (int i = 0; i < _vertex_colors.size(); ++i)
  {
    auto& color = _vertex_colors[i];
    float r = color.r;
    float g = color.g;
    float b = color.b;
    float a = color.a;

    // I removed the color = color/2 because it's just multiplied by 2 in the shader afterward in blizzard's code
    if (i >= interior_batchs_start)
    {
      r += ((r * a / 64.f) - wmo_ambient_color.r);
      g += ((g * a / 64.f) - wmo_ambient_color.g);
      r += ((b * a / 64.f) - wmo_ambient_color.b);
    }
    else
    {
      r -= wmo_ambient_color.r;
      g -= wmo_ambient_color.g;
      b -= wmo_ambient_color.b;

      r = (r * (1.f - a));
      g = (g * (1.f - a));
      b = (b * (1.f - a));
    }

    color.r = std::min(255.f, std::max(0.f, r));
    color.g = std::min(255.f, std::max(0.f, g));
    color.b = std::min(255.f, std::max(0.f, b));
    color.a = 1.f; // default value used in the shader so I simplified it here,
                   // it can be overriden by the 2nd mocv chunk
  }
}

void WMOGroup::intersect (Ogre::Ray const& ray, std::vector<float>* results) const
{
  
}

void WMOGroup::setupFog (bool draw_fog, std::function<void (bool)> setup_fog)
{
  if (use_outdoor_lights || fog == -1) {
    setup_fog (draw_fog);
  }
  else {
    wmo->fogs[fog].setup();
  }
}

void WMOFog::init(std::shared_ptr<DataStream>& stream)
{
    stream->read(this, 0x30);
  color = Ogre::ColourValue(((color1 & 0x00FF0000) >> 16) / 255.0f, ((color1 & 0x0000FF00) >> 8) / 255.0f,
    (color1 & 0x000000FF) / 255.0f, ((color1 & 0xFF000000) >> 24) / 255.0f);
  float temp;
  temp = pos.y;
  pos.y = pos.z;
  pos.z = -temp;
  fogstart = fogstart * fogend * 1.5f;
  fogend *= 1.5;
}

void WMOFog::setup()
{

}

