// This file is part of Noggit3, licensed under GNU General Public License (version 3).
#include "OgreHeader.h"
#include <alphamap.hpp>
#include <optional>
#include "OgreDataStream.h"

Alphamap::Alphamap()
{
  createNew();
}


void Alphamap::load(std::shared_ptr<DataStream>& stream,
    unsigned int flags,
    bool use_big_alphamaps,
    bool do_not_fix_alpha_map)
{
    createNew();

    if (use_big_alphamaps)
    {
        // can only compress big alpha
        if (flags & 0x200)
        {
            readCompressed(stream);
        }
        else
        {
            readBigAlpha(stream);
        }
    }
    else
    {
        readNotCompressed(stream, do_not_fix_alpha_map);
    }
}

namespace
{
  struct compressed_mcal_entry
  {
    enum mode_t
    {
      copy = 0,              // append value[0..count - 1]
      fill = 1,              // append value[0] count times
    };
    uint8_t count : 7;
    uint8_t mode : 1;

    uint8_t value[];
  };
}

void Alphamap::readCompressed(std::shared_ptr<DataStream>& stream)
{
  // compressed
  char const* input = stream->getCurrentStreamData();

  for (std::size_t offset_output(0); offset_output < 4096;)
  {
    compressed_mcal_entry const* e = reinterpret_cast<compressed_mcal_entry const*>(input);

    int count = e->count;

    if (offset_output + count > 4096)
    {
      count = 4096 - offset_output;
    }

    ++input;

    if (count == 0)
    {
      continue;
    }

    if (e->mode == compressed_mcal_entry::fill)
    {
      memset(&amap[offset_output], e->value[0], count);
      ++input;
    }
    else
    {
      memcpy(&amap[offset_output], e->value, count);
      input += count;
    }

    offset_output += count;
  }
}

void Alphamap::readBigAlpha(std::shared_ptr<DataStream>& stream)
{
  memcpy(amap, stream->getCurrentStreamData(), 64 * 64);
  stream->seekRelative(0x1000);
}

void Alphamap::readNotCompressed(std::shared_ptr<DataStream>& stream, bool do_not_fix_alpha_map)
{
  char const* abuf = stream->getCurrentStreamData();

  for (std::size_t x(0); x < 64; ++x)
  {
    for (std::size_t y(0); y < 64; y += 2)
    {
      amap[x * 64 + y + 0] = ((*abuf & 0x0f) << 4) | (*abuf & 0x0f);
      amap[x * 64 + y + 1] = ((*abuf & 0xf0) >> 4) | (*abuf & 0xf0);
      ++abuf;
    }
  }

  if (!do_not_fix_alpha_map)
  {
    for (std::size_t i(0); i < 64; ++i)
    {
      amap[i * 64 + 63] = amap[i * 64 + 62];
      amap[63 * 64 + i] = amap[62 * 64 + i];
    }
    amap[63 * 64 + 63] = amap[62 * 64 + 62];
  }
  stream->seekRelative(0x800);
}

void Alphamap::createNew()
{
  memset(amap, 0, 64 * 64);
}

void Alphamap::setAlpha(size_t offset, unsigned char value)
{
  amap[offset] = value;
}

void Alphamap::setAlpha(unsigned char *pAmap)
{
  memcpy(amap, pAmap, 64*64);
}

unsigned char Alphamap::getAlpha(size_t offset) const
{
  return amap[offset];
}

const unsigned char *Alphamap::getAlpha()
{
  return amap;
}

std::vector<uint8_t> Alphamap::compress() const
{
  std::vector<uint8_t> data(amap, amap+4096);
  auto current (data.begin());
  auto const end (data.end());
  int column_pos = 0;

  auto const consume_fill
  ( 
    [&]
    {
      int8_t count (0);
      column_pos %= 64;

      while ((current + 1 < end) && *current == *(current + 1) && column_pos < 63)
      {
        ++current;
        ++count;
        ++column_pos;
      }

      // include current (current is incremented in the for loop)
      if (count)
      {
        ++count;
        ++column_pos;
      }

      return count;
    }
  );

  std::vector<uint8_t> result;
  std::optional<std::size_t> current_copy_entry_offset;
  auto const current_copy_entry
  ( 
    [&]
    {
      return reinterpret_cast<compressed_mcal_entry*> (&*(result.begin() + *current_copy_entry_offset));
    }
  );

  for (; current != end; ++current)
  {
    auto const fill (consume_fill());
    if (fill)
    {

      result.emplace_back();
      result.emplace_back(*current);

      compressed_mcal_entry* e (reinterpret_cast<compressed_mcal_entry*> (&*(result.rbegin() + 1)));
      e->mode = compressed_mcal_entry::fill;
      e->count = fill;

      column_pos %= 64;
    }
    else
    {
      if ( !current_copy_entry_offset.has_value()
          || column_pos == 64
          )
      {
        current_copy_entry_offset = result.size();
        result.emplace_back();
        result.emplace_back(*current);
        current_copy_entry()->mode = compressed_mcal_entry::copy;
        current_copy_entry()->count = 1;

        column_pos %= 64;
      }
      else
      {
        result.emplace_back(*current);
        current_copy_entry()->count++;
      }

      column_pos++;
    }
  }

  return result;
}
