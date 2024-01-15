






#ifndef DFTABLES
#include "internal.h"
#endif







const unsigned char *
pcre_maketables(void)
{
unsigned char *yield, *p;
int i;

#ifndef DFTABLES
yield = (unsigned char*)(pcre_malloc)(tables_length);
#else
yield = (unsigned char*)malloc(tables_length);
#endif

if (yield == NULL) return NULL;
p = yield;



for (i = 0; i < 256; i++) *p++ = tolower(i);



for (i = 0; i < 256; i++) *p++ = islower(i)? toupper(i) : tolower(i);



memset(p, 0, cbit_length);
for (i = 0; i < 256; i++)
  {
  if (isdigit(i))
    {
    p[cbit_digit  + i/8] |= 1 << (i&7);
    p[cbit_word   + i/8] |= 1 << (i&7);
    }
  if (isupper(i))
    {
    p[cbit_upper  + i/8] |= 1 << (i&7);
    p[cbit_word   + i/8] |= 1 << (i&7);
    }
  if (islower(i))
    {
    p[cbit_lower  + i/8] |= 1 << (i&7);
    p[cbit_word   + i/8] |= 1 << (i&7);
    }
  if (i == '_')   p[cbit_word   + i/8] |= 1 << (i&7);
  if (isspace(i)) p[cbit_space  + i/8] |= 1 << (i&7);
  if (isxdigit(i))p[cbit_xdigit + i/8] |= 1 << (i&7);
  if (isgraph(i)) p[cbit_graph  + i/8] |= 1 << (i&7);
  if (isprint(i)) p[cbit_print  + i/8] |= 1 << (i&7);
  if (ispunct(i)) p[cbit_punct  + i/8] |= 1 << (i&7);
  if (iscntrl(i)) p[cbit_cntrl  + i/8] |= 1 << (i&7);
  }
p += cbit_length;



for (i = 0; i < 256; i++)
  {
  int x = 0;
  if (i != 0x0b && isspace(i)) x += ctype_space;
  if (isalpha(i)) x += ctype_letter;
  if (isdigit(i)) x += ctype_digit;
  if (isxdigit(i)) x += ctype_xdigit;
  if (isalnum(i) || i == '_') x += ctype_word;

  

  if (strchr("*+?{^.$|()[", i) != 0) x += ctype_meta; *p++ = x; }

return yield;
}


