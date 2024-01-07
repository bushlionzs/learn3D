









#ifdef DEBUG
#define DPRINTF(p) printf p
#else
#define DPRINTF(p) 
#endif



#include "internal.h"



#ifdef SUPPORT_UCP
#include "ucp.c"
#include "ucptypetable.c"
#endif



#define BRASTACK_SIZE 200




#define REC_STACK_SAVE_MAX 30




#define REQ_BYTE_MAX 1000




static const uschar OP_lengths[] = { OP_LENGTHS };



static const char rep_min[] = { 0, 0, 1, 1, 0, 0 };
static const char rep_max[] = { 0, 0, 0, 0, 1, 1 };



#if !EBCDIC   
static const short int escapes[] = {
     0,      0,      0,      0,      0,      0,      0,      0,   
     0,      0,    ':',    ';',    '<',    '=',    '>',    '?',   
   '@', -ESC_A, -ESC_B, -ESC_C, -ESC_D, -ESC_E,      0, -ESC_G,   
     0,      0,      0,      0,      0,      0,      0,      0,   
-ESC_P, -ESC_Q,      0, -ESC_S,      0,      0,      0, -ESC_W,   
-ESC_X,      0, -ESC_Z,    '[',   '\\',    ']',    '^',    '_',   
   '`',      7, -ESC_b,      0, -ESC_d,  ESC_e,  ESC_f,      0,   
     0,      0,      0,      0,      0,      0,  ESC_n,      0,   
-ESC_p,      0,  ESC_r, -ESC_s,  ESC_tee,    0,      0, -ESC_w,   
     0,      0, -ESC_z                                            
};

#else         
static const short int escapes[] = {
     0,     0,      0,     '.',    '<',   '(',    '+',    '|',
   '&',     0,      0,       0,      0,     0,      0,      0,
     0,     0,    '!',     '$',    '*',   ')',    ';',    '~',
   '-',   '/',      0,       0,      0,     0,      0,      0,
     0,     0,    '|',     ',',    '%',   '_',    '>',    '?',
     0,     0,      0,       0,      0,     0,      0,      0,
     0,   '`',    ':',     '#',    '@',  '\'',    '=',    '"',
     0,     7, -ESC_b,       0, -ESC_d, ESC_e,  ESC_f,      0,
     0,     0,      0,     '{',      0,     0,      0,      0,
     0,     0,      0,     'l',      0, ESC_n,      0, -ESC_p,
     0, ESC_r,      0,     '}',      0,     0,      0,      0,
     0,   '~', -ESC_s, ESC_tee,      0,     0, -ESC_w,      0,
     0,-ESC_z,      0,       0,      0,   '[',      0,      0,
     0,     0,      0,       0,      0,     0,      0,      0,
     0,     0,      0,       0,      0,   ']',    '=',    '-',
   '{',-ESC_A, -ESC_B,  -ESC_C, -ESC_D,-ESC_E,      0, -ESC_G,
     0,     0,      0,       0,      0,     0,      0,      0,
   '}',     0,      0,       0,      0,     0,      0, -ESC_P,
-ESC_Q,     0,      0,       0,      0,     0,      0,      0,
  '\\',     0, -ESC_S,       0,      0,     0, -ESC_W, -ESC_X,
     0,-ESC_Z,      0,       0,      0,     0,      0,      0,
     0,     0,      0,       0,      0,     0,      0,      0,
     0,     0,      0,       0,      0,     0,      0,      0
};
#endif




static const char *const posix_names[] = {
  "alpha", "lower", "upper",
  "alnum", "ascii", "blank", "cntrl", "digit", "graph",
  "print", "punct", "space", "word",  "xdigit" };

static const uschar posix_name_lengths[] = {
  5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4, 6, 0 };



static const int posix_class_maps[] = {
  cbit_lower, cbit_upper, -1,             
  cbit_lower, -1,         -1,             
  cbit_upper, -1,         -1,             
  cbit_digit, cbit_lower, cbit_upper,     
  cbit_print, cbit_cntrl, -1,             
  cbit_space, -1,         -1,             
  cbit_cntrl, -1,         -1,             
  cbit_digit, -1,         -1,             
  cbit_graph, -1,         -1,             
  cbit_print, -1,         -1,             
  cbit_punct, -1,         -1,             
  cbit_space, -1,         -1,             
  cbit_word,  -1,         -1,             
  cbit_xdigit,-1,         -1              
};



#if !EBCDIC    
static const unsigned char digitab[] =
  {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c, 
  0x0c,0x0c,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

#else          
static const unsigned char digitab[] =
  {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c,0x0c, 
  0x0c,0x0c,0x00,0x00,0x00,0x00,0x00,0x00};

static const unsigned char ebcdic_chartab[] = { 
  0x80,0x00,0x00,0x00,0x00,0x01,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x01,0x01,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x80,0x00,0x80,0x80,0x80, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x80,0x80,0x80,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x80, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x12, 
  0x12,0x12,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x12,0x12,0x12,0x12,0x12,0x12,0x12, 
  0x12,0x12,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x12,0x12,0x12,0x12,0x12,0x12, 
  0x12,0x12,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00, 
  0x80,0x1a,0x1a,0x1a,0x1a,0x1a,0x1a,0x12, 
  0x12,0x12,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x12,0x12,0x12,0x12,0x12,0x12,0x12, 
  0x12,0x12,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x00,0x00,0x12,0x12,0x12,0x12,0x12,0x12, 
  0x12,0x12,0x00,0x00,0x00,0x00,0x00,0x00, 
  0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c, 
  0x1c,0x1c,0x00,0x00,0x00,0x00,0x00,0x00};
#endif




static BOOL
  compile_regex(int, int, int *, uschar **, const uschar **, const char **,
    BOOL, int, int *, int *, branch_chain *, compile_data *);



typedef struct eptrblock {
  struct eptrblock *epb_prev;
  const uschar *epb_saved_eptr;
} eptrblock;



#define match_condassert   0x01    
#define match_isgroup      0x02    



#define MATCH_MATCH        1
#define MATCH_NOMATCH      0







#ifndef VPCOMPAT
#ifdef __cplusplus
extern "C" void *(*pcre_malloc)(size_t) = malloc;
extern "C" void  (*pcre_free)(void *) = free;
extern "C" void *(*pcre_stack_malloc)(size_t) = malloc;
extern "C" void  (*pcre_stack_free)(void *) = free;
extern "C" int   (*pcre_callout)(pcre_callout_block *) = NULL;
#else
void *(*pcre_malloc)(size_t) = malloc;
void  (*pcre_free)(void *) = free;
void *(*pcre_stack_malloc)(size_t) = malloc;
void  (*pcre_stack_free)(void *) = free;
int   (*pcre_callout)(pcre_callout_block *) = NULL;
#endif
#endif






#ifndef SUPPORT_UTF8
#define GETCHAR(c, eptr) c = *eptr;
#define GETCHARINC(c, eptr) c = *eptr++;
#define GETCHARINCTEST(c, eptr) c = *eptr++;
#define GETCHARLEN(c, eptr, len) c = *eptr;
#define BACKCHAR(eptr)

#else   



#define GETCHAR(c, eptr) \
  c = *eptr; \
  if ((c & 0xc0) == 0xc0) \
    { \
    int gcii; \
    int gcaa = utf8_table4[c & 0x3f];   \
    int gcss = 6*gcaa; \
    c = (c & utf8_table3[gcaa]) << gcss; \
    for (gcii = 1; gcii <= gcaa; gcii++) \
      { \
      gcss -= 6; \
      c |= (eptr[gcii] & 0x3f) << gcss; \
      } \
    }



#define GETCHARINC(c, eptr) \
  c = *eptr++; \
  if ((c & 0xc0) == 0xc0) \
    { \
    int gcaa = utf8_table4[c & 0x3f];   \
    int gcss = 6*gcaa; \
    c = (c & utf8_table3[gcaa]) << gcss; \
    while (gcaa-- > 0) \
      { \
      gcss -= 6; \
      c |= (*eptr++ & 0x3f) << gcss; \
      } \
    }



#define GETCHARINCTEST(c, eptr) \
  c = *eptr++; \
  if (md->utf8 && (c & 0xc0) == 0xc0) \
    { \
    int gcaa = utf8_table4[c & 0x3f];   \
    int gcss = 6*gcaa; \
    c = (c & utf8_table3[gcaa]) << gcss; \
    while (gcaa-- > 0) \
      { \
      gcss -= 6; \
      c |= (*eptr++ & 0x3f) << gcss; \
      } \
    }



#define GETCHARLEN(c, eptr, len) \
  c = *eptr; \
  if ((c & 0xc0) == 0xc0) \
    { \
    int gcii; \
    int gcaa = utf8_table4[c & 0x3f];   \
    int gcss = 6*gcaa; \
    c = (c & utf8_table3[gcaa]) << gcss; \
    for (gcii = 1; gcii <= gcaa; gcii++) \
      { \
      gcss -= 6; \
      c |= (eptr[gcii] & 0x3f) << gcss; \
      } \
    len += gcaa; \
    }



#define BACKCHAR(eptr) while((*eptr & 0xc0) == 0x80) eptr--;

#endif







#include "chartables.c"



#ifdef SUPPORT_UTF8




static const int utf8_table1[] =
  { 0x7f, 0x7ff, 0xffff, 0x1fffff, 0x3ffffff, 0x7fffffff};



static const int utf8_table2[] = { 0,    0xc0, 0xe0, 0xf0, 0xf8, 0xfc};
static const int utf8_table3[] = { 0xff, 0x1f, 0x0f, 0x07, 0x03, 0x01};



static const uschar utf8_table4[] = {
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
  3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5 };






static int
ord2utf8(int cvalue, uschar *buffer)
{
register int i, j;
for (i = 0; i < sizeof(utf8_table1)/sizeof(int); i++)
  if (cvalue <= utf8_table1[i]) break;
buffer += i;
for (j = i; j > 0; j--)
 {
 *buffer-- = 0x80 | (cvalue & 0x3f);
 cvalue >>= 6;
 }
*buffer = utf8_table2[i] | cvalue;
return i + 1;
}
#endif







#ifdef DEBUG
#include "printint.c"
#endif





#define STRING(a)  # a
#define XSTRING(s) STRING(s)

EXPORT const char *
pcre_version(void)
{
return XSTRING(PCRE_MAJOR) "." XSTRING(PCRE_MINOR) " " XSTRING(PCRE_DATE);
}








static long int
byteflip(long int value, int n)
{
if (n == 2) return ((value & 0x00ff) << 8) | ((value & 0xff00) >> 8);
return ((value & 0x000000ff) << 24) |
       ((value & 0x0000ff00) <<  8) |
       ((value & 0x00ff0000) >>  8) |
       ((value & 0xff000000) >> 24);
}







static real_pcre *
try_flipped(const real_pcre *re, real_pcre *internal_re,
  const pcre_study_data *study, pcre_study_data *internal_study)
{
if (byteflip(re->magic_number, sizeof(re->magic_number)) != MAGIC_NUMBER)
  return NULL;

*internal_re = *re;           
internal_re->size = byteflip(re->size, sizeof(re->size));
internal_re->options = byteflip(re->options, sizeof(re->options));
internal_re->top_bracket = (pcre_uint16)byteflip(re->top_bracket, sizeof(re->top_bracket));
internal_re->top_backref = (pcre_uint16)byteflip(re->top_backref, sizeof(re->top_backref));
internal_re->first_byte = (pcre_uint16)byteflip(re->first_byte, sizeof(re->first_byte));
internal_re->req_byte = (pcre_uint16)byteflip(re->req_byte, sizeof(re->req_byte));
internal_re->name_table_offset = (pcre_uint16)byteflip(re->name_table_offset,
  sizeof(re->name_table_offset));
internal_re->name_entry_size = (pcre_uint16)byteflip(re->name_entry_size,
  sizeof(re->name_entry_size));
internal_re->name_count = (pcre_uint16)byteflip(re->name_count, sizeof(re->name_count));

if (study != NULL)
  {
  *internal_study = *study;   
  internal_study->size = byteflip(study->size, sizeof(study->size));
  internal_study->options = byteflip(study->options, sizeof(study->options));
  }

return internal_re;
}







EXPORT int
pcre_info(const pcre *argument_re, int *optptr, int *first_byte)
{
real_pcre internal_re;
const real_pcre *re = (const real_pcre *)argument_re;
if (re == NULL) return PCRE_ERROR_NULL;
if (re->magic_number != MAGIC_NUMBER)
  {
  re = try_flipped(re, &internal_re, NULL, NULL);
  if (re == NULL) return PCRE_ERROR_BADMAGIC;
  }
if (optptr != NULL) *optptr = (int)(re->options & PUBLIC_OPTIONS);
if (first_byte != NULL)
  *first_byte = ((re->options & PCRE_FIRSTSET) != 0)? re->first_byte :
     ((re->options & PCRE_STARTLINE) != 0)? -1 : -2;
return re->top_bracket;
}







EXPORT int
pcre_fullinfo(const pcre *argument_re, const pcre_extra *extra_data, int what,
  void *where)
{
real_pcre internal_re;
pcre_study_data internal_study;
const real_pcre *re = (const real_pcre *)argument_re;
const pcre_study_data *study = NULL;

if (re == NULL || where == NULL) return PCRE_ERROR_NULL;

if (extra_data != NULL && (extra_data->flags & PCRE_EXTRA_STUDY_DATA) != 0)
  study = (const pcre_study_data *)extra_data->study_data;

if (re->magic_number != MAGIC_NUMBER)
  {
  re = try_flipped(re, &internal_re, study, &internal_study);
  if (re == NULL) return PCRE_ERROR_BADMAGIC;
  if (study != NULL) study = &internal_study;
  }

switch (what)
  {
  case PCRE_INFO_OPTIONS:
  *((unsigned long int *)where) = re->options & PUBLIC_OPTIONS;
  break;

  case PCRE_INFO_SIZE:
  *((size_t *)where) = re->size;
  break;

  case PCRE_INFO_STUDYSIZE:
  *((size_t *)where) = (study == NULL)? 0 : study->size;
  break;

  case PCRE_INFO_CAPTURECOUNT:
  *((int *)where) = re->top_bracket;
  break;

  case PCRE_INFO_BACKREFMAX:
  *((int *)where) = re->top_backref;
  break;

  case PCRE_INFO_FIRSTBYTE:
  *((int *)where) =
    ((re->options & PCRE_FIRSTSET) != 0)? re->first_byte :
    ((re->options & PCRE_STARTLINE) != 0)? -1 : -2;
  break;

  

  case PCRE_INFO_FIRSTTABLE:
  *((const uschar **)where) =
    (study != NULL && (study->options & PCRE_STUDY_MAPPED) != 0)?
      ((const pcre_study_data *)extra_data->study_data)->start_bits : NULL;
  break;

  case PCRE_INFO_LASTLITERAL:
  *((int *)where) =
    ((re->options & PCRE_REQCHSET) != 0)? re->req_byte : -1;
  break;

  case PCRE_INFO_NAMEENTRYSIZE:
  *((int *)where) = re->name_entry_size;
  break;

  case PCRE_INFO_NAMECOUNT:
  *((int *)where) = re->name_count;
  break;

  case PCRE_INFO_NAMETABLE:
  *((const uschar **)where) = (const uschar *)re + re->name_table_offset;
  break;

  case PCRE_INFO_DEFAULT_TABLES:
  *((const uschar **)where) = (const uschar *)pcre_default_tables;
  break;

  default: return PCRE_ERROR_BADOPTION;
  }

return 0;
}







EXPORT int
pcre_config(int what, void *where)
{
switch (what)
  {
  case PCRE_CONFIG_UTF8:
#ifdef SUPPORT_UTF8
  *((int *)where) = 1;
#else
  *((int *)where) = 0;
#endif
  break;

  case PCRE_CONFIG_UNICODE_PROPERTIES:
#ifdef SUPPORT_UCP
  *((int *)where) = 1;
#else
  *((int *)where) = 0;
#endif
  break;

  case PCRE_CONFIG_NEWLINE:
  *((int *)where) = NEWLINE;
  break;

  case PCRE_CONFIG_LINK_SIZE:
  *((int *)where) = LINK_SIZE;
  break;

  case PCRE_CONFIG_POSIX_MALLOC_THRESHOLD:
  *((int *)where) = POSIX_MALLOC_THRESHOLD;
  break;

  case PCRE_CONFIG_MATCH_LIMIT:
  *((unsigned int *)where) = MATCH_LIMIT;
  break;

  case PCRE_CONFIG_STACKRECURSE:
#ifdef NO_RECURSE
  *((int *)where) = 0;
#else
  *((int *)where) = 1;
#endif
  break;

  default: return PCRE_ERROR_BADOPTION;
  }

return 0;
}



#ifdef DEBUG




static void
pchars(const uschar *p, int length, BOOL is_subject, match_data *md)
{
int c;
if (is_subject && length > md->end_subject - p) length = md->end_subject - p;
while (length-- > 0)
  if (isprint(c = *(p++))) printf("%c", c); else printf("\\x%02x", c);
}
#endif








static int
check_escape(const uschar **ptrptr, const char **errorptr, int bracount,
  int options, BOOL isclass)
{
const uschar *ptr = *ptrptr;
int c, i;



c = *(++ptr);
if (c == 0) *errorptr = ERR1;



#if !EBCDIC    
else if (c < '0' || c > 'z') {}                           
else if ((i = escapes[c - '0']) != 0) c = i;

#else          
else if (c < 'a' || (ebcdic_chartab[c] & 0x0E) == 0) {}   
else if ((i = escapes[c - 0x48]) != 0)  c = i;
#endif



else
  {
  const uschar *oldptr;
  switch (c)
    {
    

    case 'l':
    case 'L':
    case 'N':
    case 'u':
    case 'U':
    *errorptr = ERR37;
    break;

    

    case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9':

    if (!isclass)
      {
      oldptr = ptr;
      c -= '0';
      while ((digitab[ptr[1]] & ctype_digit) != 0)
        c = c * 10 + *(++ptr) - '0';
      if (c < 10 || c <= bracount)
        {
        c = -(ESC_REF + c);
        break;
        }
      ptr = oldptr;      
      }

    

    if ((c = *ptr) >= '8')
      {
      ptr--;
      c = 0;
      break;
      }

    

    case '0':
    c -= '0';
    while(i++ < 2 && ptr[1] >= '0' && ptr[1] <= '7')
        c = c * 8 + *(++ptr) - '0';
    c &= 255;     
    break;

    

    case 'x':
#ifdef SUPPORT_UTF8
    if (ptr[1] == '{' && (options & PCRE_UTF8) != 0)
      {
      const uschar *pt = ptr + 2;
      register int count = 0;
      c = 0;
      while ((digitab[*pt] & ctype_xdigit) != 0)
        {
        int cc = *pt++;
        count++;
#if !EBCDIC    
        if (cc >= 'a') cc -= 32;               
        c = c * 16 + cc - ((cc < 'A')? '0' : ('A' - 10));
#else          
        if (cc >= 'a' && cc <= 'z') cc += 64;  
        c = c * 16 + cc - ((cc >= '0')? '0' : ('A' - 10));
#endif
        }
      if (*pt == '}')
        {
        if (c < 0 || count > 8) *errorptr = ERR34;
        ptr = pt;
        break;
        }
      
      }
#endif

    

    c = 0;
    while (i++ < 2 && (digitab[ptr[1]] & ctype_xdigit) != 0)
      {
      int cc;                               
      cc = *(++ptr);                        
#if !EBCDIC    
      if (cc >= 'a') cc -= 32;              
      c = c * 16 + cc - ((cc < 'A')? '0' : ('A' - 10));
#else          
      if (cc <= 'z') cc += 64;              
      c = c * 16 + cc - ((cc >= '0')? '0' : ('A' - 10));
#endif
      }
    break;

    

    case 'c':
    c = *(++ptr);
    if (c == 0)
      {
      *errorptr = ERR2;
      return 0;
      }

    

#if !EBCDIC    
    if (c >= 'a' && c <= 'z') c -= 32;
    c ^= 0x40;
#else          
    if (c >= 'a' && c <= 'z') c += 64;
    c ^= 0xC0;
#endif
    break;

    

    default:
    if ((options & PCRE_EXTRA) != 0) switch(c)
      {
      default:
      *errorptr = ERR3;
      break;
      }
    break;
    }
  }

*ptrptr = ptr;
return c;
}



#ifdef SUPPORT_UCP




static int
get_ucp(const uschar **ptrptr, BOOL *negptr, const char **errorptr)
{
int c, i, bot, top;
const uschar *ptr = *ptrptr;
char name[4];

c = *(++ptr);
if (c == 0) goto ERROR_RETURN;

*negptr = FALSE;



if (c == '{')
  {
  if (ptr[1] == '^')
    {
    *negptr = TRUE;
    ptr++;
    }
  for (i = 0; i <= 2; i++)
    {
    c = *(++ptr);
    if (c == 0) goto ERROR_RETURN;
    if (c == '}') break;
    name[i] = c;
    }
  if (c !='}')   
    {
    while (*(++ptr) != 0 && *ptr != '}');
    if (*ptr == '}') goto UNKNOWN_RETURN; else goto ERROR_RETURN;
    }
  name[i] = 0;
  }



else
  {
  name[0] = c;
  name[1] = 0;
  }

*ptrptr = ptr;



bot = 0;
top = sizeof(utt)/sizeof(ucp_type_table);

while (bot < top)
  {
  i = (bot + top)/2;
  c = strcmp(name, utt[i].name);
  if (c == 0) return utt[i].value;
  if (c > 0) bot = i + 1; else top = i;
  }

UNKNOWN_RETURN:
*errorptr = ERR47;
*ptrptr = ptr;
return -1;

ERROR_RETURN:
*errorptr = ERR46;
*ptrptr = ptr;
return -1;
}
#endif








static BOOL
is_counted_repeat(const uschar *p)
{
if ((digitab[*p++] & ctype_digit) == 0) return FALSE;
while ((digitab[*p] & ctype_digit) != 0) p++;
if (*p == '}') return TRUE;

if (*p++ != ',') return FALSE;
if (*p == '}') return TRUE;

if ((digitab[*p++] & ctype_digit) == 0) return FALSE;
while ((digitab[*p] & ctype_digit) != 0) p++;

return (*p == '}');
}







static const uschar *
read_repeat_counts(const uschar *p, int *minp, int *maxp, const char **errorptr)
{
int min = 0;
int max = -1;

while ((digitab[*p] & ctype_digit) != 0) min = min * 10 + *p++ - '0';

if (*p == '}') max = min; else
  {
  if (*(++p) != '}')
    {
    max = 0;
    while((digitab[*p] & ctype_digit) != 0) max = max * 10 + *p++ - '0';
    if (max < min)
      {
      *errorptr = ERR4;
      return p;
      }
    }
  }



if (min > 65535 || max > 65535)
  *errorptr = ERR5;
else
  {
  *minp = min;
  *maxp = max;
  }
return p;
}







static const uschar*
first_significant_code(const uschar *code, int *options, int optbit,
  BOOL skipassert)
{
for (;;)
  {
  switch ((int)*code)
    {
    case OP_OPT:
    if (optbit > 0 && ((int)code[1] & optbit) != (*options & optbit))
      *options = (int)code[1];
    code += 2;
    break;

    case OP_ASSERT_NOT:
    case OP_ASSERTBACK:
    case OP_ASSERTBACK_NOT:
    if (!skipassert) return code;
    do code += GET(code, 1); while (*code == OP_ALT);
    code += OP_lengths[*code];
    break;

    case OP_WORD_BOUNDARY:
    case OP_NOT_WORD_BOUNDARY:
    if (!skipassert) return code;
    

    case OP_CALLOUT:
    case OP_CREF:
    case OP_BRANUMBER:
    code += OP_lengths[*code];
    break;

    default:
    return code;
    }
  }

}








static int
find_fixedlength(uschar *code, int options)
{
int length = -1;

register int branchlength = 0;
register uschar *cc = code + 1 + LINK_SIZE;



for (;;)
  {
  int d;
  register int op = *cc;
  if (op >= OP_BRA) op = OP_BRA;

  switch (op)
    {
    case OP_BRA:
    case OP_ONCE:
    case OP_COND:
    d = find_fixedlength(cc, options);
    if (d < 0) return d;
    branchlength += d;
    do cc += GET(cc, 1); while (*cc == OP_ALT);
    cc += 1 + LINK_SIZE;
    break;

    

    case OP_ALT:
    case OP_KET:
    case OP_KETRMAX:
    case OP_KETRMIN:
    case OP_END:
    if (length < 0) length = branchlength;
      else if (length != branchlength) return -1;
    if (*cc != OP_ALT) return length;
    cc += 1 + LINK_SIZE;
    branchlength = 0;
    break;

    

    case OP_ASSERT:
    case OP_ASSERT_NOT:
    case OP_ASSERTBACK:
    case OP_ASSERTBACK_NOT:
    do cc += GET(cc, 1); while (*cc == OP_ALT);
    

    

    case OP_REVERSE:
    case OP_BRANUMBER:
    case OP_CREF:
    case OP_OPT:
    case OP_CALLOUT:
    case OP_SOD:
    case OP_SOM:
    case OP_EOD:
    case OP_EODN:
    case OP_CIRC:
    case OP_DOLL:
    case OP_NOT_WORD_BOUNDARY:
    case OP_WORD_BOUNDARY:
    cc += OP_lengths[*cc];
    break;

    

    case OP_CHAR:
    case OP_CHARNC:
    branchlength++;
    cc += 2;
#ifdef SUPPORT_UTF8
    if ((options & PCRE_UTF8) != 0)
      {
      while ((*cc & 0xc0) == 0x80) cc++;
      }
#endif
    break;

    

    case OP_EXACT:
    branchlength += GET2(cc,1);
    cc += 4;
#ifdef SUPPORT_UTF8
    if ((options & PCRE_UTF8) != 0)
      {
      while((*cc & 0x80) == 0x80) cc++;
      }
#endif
    break;

    case OP_TYPEEXACT:
    branchlength += GET2(cc,1);
    cc += 4;
    break;

    

    case OP_PROP:
    case OP_NOTPROP:
    cc++;
    

    case OP_NOT_DIGIT:
    case OP_DIGIT:
    case OP_NOT_WHITESPACE:
    case OP_WHITESPACE:
    case OP_NOT_WORDCHAR:
    case OP_WORDCHAR:
    case OP_ANY:
    branchlength++;
    cc++;
    break;

    

    case OP_ANYBYTE:
    return -2;

    

#ifdef SUPPORT_UTF8
    case OP_XCLASS:
    cc += GET(cc, 1) - 33;
    
#endif

    case OP_CLASS:
    case OP_NCLASS:
    cc += 33;

    switch (*cc)
      {
      case OP_CRSTAR:
      case OP_CRMINSTAR:
      case OP_CRQUERY:
      case OP_CRMINQUERY:
      return -1;

      case OP_CRRANGE:
      case OP_CRMINRANGE:
      if (GET2(cc,1) != GET2(cc,3)) return -1;
      branchlength += GET2(cc,1);
      cc += 5;
      break;

      default:
      branchlength++;
      }
    break;

    

    default:
    return -1;
    }
  }

}








static const uschar *
find_bracket(const uschar *code, BOOL utf8, int number)
{
#ifndef SUPPORT_UTF8
utf8 = utf8;               
#endif

for (;;)
  {
  register int c = *code;
  if (c == OP_END) return NULL;
  else if (c > OP_BRA)
    {
    int n = c - OP_BRA;
    if (n > EXTRACT_BASIC_MAX) n = GET2(code, 2+LINK_SIZE);
    if (n == number) return (uschar *)code;
    code += OP_lengths[OP_BRA];
    }
  else
    {
    code += OP_lengths[c];

#ifdef SUPPORT_UTF8

    

    if (utf8) switch(c)
      {
      case OP_CHAR:
      case OP_CHARNC:
      case OP_EXACT:
      case OP_UPTO:
      case OP_MINUPTO:
      case OP_STAR:
      case OP_MINSTAR:
      case OP_PLUS:
      case OP_MINPLUS:
      case OP_QUERY:
      case OP_MINQUERY:
      while ((*code & 0xc0) == 0x80) code++;
      break;

      

      case OP_XCLASS:
      code += GET(code, 1) + 1;
      break;
      }
#endif
    }
  }
}







static const uschar *
find_recurse(const uschar *code, BOOL utf8)
{
#ifndef SUPPORT_UTF8
utf8 = utf8;               
#endif

for (;;)
  {
  register int c = *code;
  if (c == OP_END) return NULL;
  else if (c == OP_RECURSE) return code;
  else if (c > OP_BRA)
    {
    code += OP_lengths[OP_BRA];
    }
  else
    {
    code += OP_lengths[c];

#ifdef SUPPORT_UTF8

    

    if (utf8) switch(c)
      {
      case OP_CHAR:
      case OP_CHARNC:
      case OP_EXACT:
      case OP_UPTO:
      case OP_MINUPTO:
      case OP_STAR:
      case OP_MINSTAR:
      case OP_PLUS:
      case OP_MINPLUS:
      case OP_QUERY:
      case OP_MINQUERY:
      while ((*code & 0xc0) == 0x80) code++;
      break;

      

      case OP_XCLASS:
      code += GET(code, 1) + 1;
      break;
      }
#endif
    }
  }
}







static BOOL
could_be_empty_branch(const uschar *code, const uschar *endcode, BOOL utf8)
{
register int c;
for (code = first_significant_code(code + 1 + LINK_SIZE, NULL, 0, TRUE);
     code < endcode;
     code = first_significant_code(code + OP_lengths[c], NULL, 0, TRUE))
  {
  const uschar *ccode;

  c = *code;

  if (c >= OP_BRA)
    {
    BOOL empty_branch;
    if (GET(code, 1) == 0) return TRUE;    

    

    empty_branch = FALSE;
    do
      {
      if (!empty_branch && could_be_empty_branch(code, endcode, utf8))
        empty_branch = TRUE;
      code += GET(code, 1);
      }
    while (*code == OP_ALT);
    if (!empty_branch) return FALSE;   
    code += 1 + LINK_SIZE;
    c = *code;
    }

  else switch (c)
    {
    

#ifdef SUPPORT_UTF8
    case OP_XCLASS:
    ccode = code + GET(code, 1);
    goto CHECK_CLASS_REPEAT;
#endif

    case OP_CLASS:
    case OP_NCLASS:
    ccode = code + 33;

#ifdef SUPPORT_UTF8
    CHECK_CLASS_REPEAT:
#endif

    switch (*ccode)
      {
      case OP_CRSTAR:            
      case OP_CRMINSTAR:
      case OP_CRQUERY:
      case OP_CRMINQUERY:
      break;

      default:                   
      case OP_CRPLUS:            
      case OP_CRMINPLUS:
      return FALSE;

      case OP_CRRANGE:
      case OP_CRMINRANGE:
      if (GET2(ccode, 1) > 0) return FALSE;  
      break;
      }
    break;

    

    case OP_PROP:
    case OP_NOTPROP:
    case OP_EXTUNI:
    case OP_NOT_DIGIT:
    case OP_DIGIT:
    case OP_NOT_WHITESPACE:
    case OP_WHITESPACE:
    case OP_NOT_WORDCHAR:
    case OP_WORDCHAR:
    case OP_ANY:
    case OP_ANYBYTE:
    case OP_CHAR:
    case OP_CHARNC:
    case OP_NOT:
    case OP_PLUS:
    case OP_MINPLUS:
    case OP_EXACT:
    case OP_NOTPLUS:
    case OP_NOTMINPLUS:
    case OP_NOTEXACT:
    case OP_TYPEPLUS:
    case OP_TYPEMINPLUS:
    case OP_TYPEEXACT:
    return FALSE;

    

    case OP_KET:
    case OP_KETRMAX:
    case OP_KETRMIN:
    case OP_ALT:
    return TRUE;

    

#ifdef SUPPORT_UTF8
    case OP_STAR:
    case OP_MINSTAR:
    case OP_QUERY:
    case OP_MINQUERY:
    case OP_UPTO:
    case OP_MINUPTO:
    if (utf8) while ((code[2] & 0xc0) == 0x80) code++;
    break;
#endif
    }
  }

return TRUE;
}







static BOOL
could_be_empty(const uschar *code, const uschar *endcode, branch_chain *bcptr,
  BOOL utf8)
{
while (bcptr != NULL && bcptr->current >= code)
  {
  if (!could_be_empty_branch(bcptr->current, endcode, utf8)) return FALSE;
  bcptr = bcptr->outer;
  }
return TRUE;
}







static BOOL
check_posix_syntax(const uschar *ptr, const uschar **endptr, compile_data *cd)
{
int terminator;          
terminator = *(++ptr);   
if (*(++ptr) == '^') ptr++;
while ((cd->ctypes[*ptr] & ctype_letter) != 0) ptr++;
if (*ptr == terminator && ptr[1] == ']')
  {
  *endptr = ptr;
  return TRUE;
  }
return FALSE;
}








static int
check_posix_name(const uschar *ptr, int len)
{
register int yield = 0;
while (posix_name_lengths[yield] != 0)
  {
  if (len == posix_name_lengths[yield] &&
    strncmp((const char *)ptr, posix_names[yield], len) == 0) return yield;
  yield++;
  }
return -1;
}






static void
adjust_recurse(uschar *group, int adjust, BOOL utf8, compile_data *cd)
{
uschar *ptr = group;
while ((ptr = (uschar *)find_recurse(ptr, utf8)) != NULL)
  {
  int offset = GET(ptr, 1);
  if (cd->start_code + offset >= group) PUT(ptr, 1, offset + adjust);
  ptr += 1 + LINK_SIZE;
  }
}







static uschar *
auto_callout(uschar *code, const uschar *ptr, compile_data *cd)
{
*code++ = OP_CALLOUT;
*code++ = 255;
PUT(code, 0, ptr - cd->start_pattern);  
PUT(code, LINK_SIZE, 0);                
return code + 2*LINK_SIZE;
}







static void
complete_callout(uschar *previous_callout, const uschar *ptr, compile_data *cd)
{
int length = ptr - cd->start_pattern - GET(previous_callout, 2);
PUT(previous_callout, 2 + LINK_SIZE, length);
}



#ifdef SUPPORT_UCP




static BOOL
get_othercase_range(int *cptr, int d, int *ocptr, int *odptr)
{
int c, chartype, othercase, next;

for (c = *cptr; c <= d; c++)
  {
  if (ucp_findchar(c, &chartype, &othercase) == ucp_L && othercase != 0) break;
  }

if (c > d) return FALSE;

*ocptr = othercase;
next = othercase + 1;

for (++c; c <= d; c++)
  {
  if (ucp_findchar(c, &chartype, &othercase) != ucp_L || othercase != next)
    break;
  next++;
  }

*odptr = next - 1;
*cptr = c;

return TRUE;
}
#endif  






static BOOL
compile_branch(int *optionsptr, int *brackets, uschar **codeptr,
  const uschar **ptrptr, const char **errorptr, int *firstbyteptr,
  int *reqbyteptr, branch_chain *bcptr, compile_data *cd)
{
int repeat_type, op_type;
int repeat_min = 0, repeat_max = 0;      
int bravalue = 0;
int greedy_default, greedy_non_default;
int firstbyte, reqbyte;
int zeroreqbyte, zerofirstbyte;
int req_caseopt, reqvary, tempreqvary;
int condcount = 0;
int options = *optionsptr;
int after_manual_callout = 0;
register int c;
register uschar *code = *codeptr;
uschar *tempcode;
BOOL inescq = FALSE;
BOOL groupsetfirstbyte = FALSE;
const uschar *ptr = *ptrptr;
const uschar *tempptr;
uschar *previous = NULL;
uschar *previous_callout = NULL;
uschar classbits[32];

#ifdef SUPPORT_UTF8
BOOL class_utf8;
BOOL utf8 = (options & PCRE_UTF8) != 0;
uschar *class_utf8data;
uschar utf8_char[6];
#else
BOOL utf8 = FALSE;
#endif



greedy_default = ((options & PCRE_UNGREEDY) != 0);
greedy_non_default = greedy_default ^ 1;



firstbyte = reqbyte = zerofirstbyte = zeroreqbyte = REQ_UNSET;



req_caseopt = ((options & PCRE_CASELESS) != 0)? REQ_CASELESS : 0;



for (;; ptr++)
  {
  BOOL negate_class;
  BOOL possessive_quantifier;
  BOOL is_quantifier;
  int class_charcount;
  int class_lastchar;
  int newoptions;
  int recno;
  int skipbytes;
  int subreqbyte;
  int subfirstbyte;
  int mclength;
  uschar mcbuffer[8];

  

  c = *ptr;

  

  if (inescq && c != 0)
    {
    if (c == '\\' && ptr[1] == 'E')
      {
      inescq = FALSE;
      ptr++;
      continue;
      }
    else
      {
      if (previous_callout != NULL)
        {
        complete_callout(previous_callout, ptr, cd);
        previous_callout = NULL;
        }
      if ((options & PCRE_AUTO_CALLOUT) != 0)
        {
        previous_callout = code;
        code = auto_callout(code, ptr, cd);
        }
      goto NORMAL_CHAR;
      }
    }

  

  is_quantifier = c == '*' || c == '+' || c == '?' ||
    (c == '{' && is_counted_repeat(ptr+1));

  if (!is_quantifier && previous_callout != NULL &&
       after_manual_callout-- <= 0)
    {
    complete_callout(previous_callout, ptr, cd);
    previous_callout = NULL;
    }

  

  if ((options & PCRE_EXTENDED) != 0)
    {
    if ((cd->ctypes[c] & ctype_space) != 0) continue;
    if (c == '#')
      {
      
      while ((c = *(++ptr)) != 0 && c != NEWLINE) ;
      if (c != 0) continue;   
      }
    }

  

  if ((options & PCRE_AUTO_CALLOUT) != 0 && !is_quantifier)
    {
    previous_callout = code;
    code = auto_callout(code, ptr, cd);
    }

  switch(c)
    {
    

    case 0:
    case '|':
    case ')':
    *firstbyteptr = firstbyte;
    *reqbyteptr = reqbyte;
    *codeptr = code;
    *ptrptr = ptr;
    return TRUE;

    

    case '^':
    if ((options & PCRE_MULTILINE) != 0)
      {
      if (firstbyte == REQ_UNSET) firstbyte = REQ_NONE;
      }
    previous = NULL;
    *code++ = OP_CIRC;
    break;

    case '$':
    previous = NULL;
    *code++ = OP_DOLL;
    break;

    

    case '.':
    if (firstbyte == REQ_UNSET) firstbyte = REQ_NONE;
    zerofirstbyte = firstbyte;
    zeroreqbyte = reqbyte;
    previous = code;
    *code++ = OP_ANY;
    break;

    

    case '[':
    previous = code;

    

    if ((ptr[1] == ':' || ptr[1] == '.' || ptr[1] == '=') &&
        check_posix_syntax(ptr, &tempptr, cd))
      {
      *errorptr = (ptr[1] == ':')? ERR13 : ERR31;
      goto FAILED;
      }

    

    if ((c = *(++ptr)) == '^')
      {
      negate_class = TRUE;
      c = *(++ptr);
      }
    else
      {
      negate_class = FALSE;
      }

    

    class_charcount = 0;
    class_lastchar = -1;

#ifdef SUPPORT_UTF8
    class_utf8 = FALSE;                       
    class_utf8data = code + LINK_SIZE + 34;   
#endif

    

    memset(classbits, 0, 32 * sizeof(uschar));

    

    do
      {
#ifdef SUPPORT_UTF8
      if (utf8 && c > 127)
        {                           
        GETCHARLEN(c, ptr, ptr);    
        }
#endif

      

      if (inescq)
        {
        if (c == '\\' && ptr[1] == 'E')
          {
          inescq = FALSE;
          ptr++;
          continue;
          }
        else goto LONE_SINGLE_CHARACTER;
        }

      

      if (c == '[' &&
          (ptr[1] == ':' || ptr[1] == '.' || ptr[1] == '=') &&
          check_posix_syntax(ptr, &tempptr, cd))
        {
        BOOL local_negate = FALSE;
        int posix_class, i;
        register const uschar *cbits = cd->cbits;

        if (ptr[1] != ':')
          {
          *errorptr = ERR31;
          goto FAILED;
          }

        ptr += 2;
        if (*ptr == '^')
          {
          local_negate = TRUE;
          ptr++;
          }

        posix_class = check_posix_name(ptr, tempptr - ptr);
        if (posix_class < 0)
          {
          *errorptr = ERR30;
          goto FAILED;
          }

        

        if ((options & PCRE_CASELESS) != 0 && posix_class <= 2)
          posix_class = 0;

        

        posix_class *= 3;
        for (i = 0; i < 3; i++)
          {
          BOOL blankclass = strncmp((char *)ptr, "blank", 5) == 0;
          int taboffset = posix_class_maps[posix_class + i];
          if (taboffset < 0) break;
          if (local_negate)
            {
            if (i == 0)
              for (c = 0; c < 32; c++) classbits[c] |= ~cbits[c+taboffset];
            else
              for (c = 0; c < 32; c++) classbits[c] &= ~cbits[c+taboffset];
            if (blankclass) classbits[1] |= 0x3c;
            }
          else
            {
            for (c = 0; c < 32; c++) classbits[c] |= cbits[c+taboffset];
            if (blankclass) classbits[1] &= ~0x3c;
            }
          }

        ptr = tempptr + 1;
        class_charcount = 10;  
        continue;    
        }

      

      if (c == '\\')
        {
        c = check_escape(&ptr, errorptr, *brackets, options, TRUE);

        if (-c == ESC_b) c = '\b';       
        else if (-c == ESC_X) c = 'X';   
        else if (-c == ESC_Q)            
          {
          if (ptr[1] == '\\' && ptr[2] == 'E')
            {
            ptr += 2; 
            }
          else inescq = TRUE;
          continue;
          }

        if (c < 0)
          {
          register const uschar *cbits = cd->cbits;
          class_charcount += 2;     
          switch (-c)
            {
            case ESC_d:
            for (c = 0; c < 32; c++) classbits[c] |= cbits[c+cbit_digit];
            continue;

            case ESC_D:
            for (c = 0; c < 32; c++) classbits[c] |= ~cbits[c+cbit_digit];
            continue;

            case ESC_w:
            for (c = 0; c < 32; c++) classbits[c] |= cbits[c+cbit_word];
            continue;

            case ESC_W:
            for (c = 0; c < 32; c++) classbits[c] |= ~cbits[c+cbit_word];
            continue;

            case ESC_s:
            for (c = 0; c < 32; c++) classbits[c] |= cbits[c+cbit_space];
            classbits[1] &= ~0x08;   
            continue;

            case ESC_S:
            for (c = 0; c < 32; c++) classbits[c] |= ~cbits[c+cbit_space];
            classbits[1] |= 0x08;    
            continue;

#ifdef SUPPORT_UCP
            case ESC_p:
            case ESC_P:
              {
              BOOL negated;
              int property = get_ucp(&ptr, &negated, errorptr);
              if (property < 0) goto FAILED;
              class_utf8 = TRUE;
              *class_utf8data++ = ((-c == ESC_p) != negated)?
                XCL_PROP : XCL_NOTPROP;
              *class_utf8data++ = property;
              class_charcount -= 2;   
              }
            continue;
#endif

            

            default:
            if ((options & PCRE_EXTRA) != 0)
              {
              *errorptr = ERR7;
              goto FAILED;
              }
            c = *ptr;              
            class_charcount -= 2;  
            }
          }

        

        }   

      

      if (ptr[1] == '-' && ptr[2] != ']')
        {
        int d;
        ptr += 2;

#ifdef SUPPORT_UTF8
        if (utf8)
          {                           
          GETCHARLEN(d, ptr, ptr);    
          }
        else
#endif
        d = *ptr;  

        

        if (d == '\\')
          {
          const uschar *oldptr = ptr;
          d = check_escape(&ptr, errorptr, *brackets, options, TRUE);

          

          if (d < 0)
            {
            if (d == -ESC_b) d = '\b';
            else if (d == -ESC_X) d = 'X'; else
              {
              ptr = oldptr - 2;
              goto LONE_SINGLE_CHARACTER;  
              }
            }
          }

        

        if (d == c) goto LONE_SINGLE_CHARACTER;  

        

#ifdef SUPPORT_UTF8
        if (utf8 && (d > 255 || ((options & PCRE_CASELESS) != 0 && d > 127)))
          {
          class_utf8 = TRUE;

          

#ifdef SUPPORT_UCP
          if ((options & PCRE_CASELESS) != 0)
            {
            int occ, ocd;
            int cc = c;
            int origd = d;
            while (get_othercase_range(&cc, origd, &occ, &ocd))
              {
              if (occ >= c && ocd <= d) continue;  

              if (occ < c  && ocd >= c - 1)        
                {                                  
                c = occ;                           
                continue;                          
                }                                  
              if (ocd > d && occ <= d + 1)         
                {                                  
                d = ocd;
                continue;
                }

              if (occ == ocd)
                {
                *class_utf8data++ = XCL_SINGLE;
                }
              else
                {
                *class_utf8data++ = XCL_RANGE;
                class_utf8data += ord2utf8(occ, class_utf8data);
                }
              class_utf8data += ord2utf8(ocd, class_utf8data);
              }
            }
#endif  

          

          *class_utf8data++ = XCL_RANGE;
          class_utf8data += ord2utf8(c, class_utf8data);
          class_utf8data += ord2utf8(d, class_utf8data);

          

#ifdef SUPPORT_UCP
          continue;    
#else
          if ((options & PCRE_CASELESS) == 0 || c > 127) continue;

          

          d = 127;

#endif  
          }
#endif  

        

        for (; c <= d; c++)
          {
          classbits[c/8] |= (1 << (c&7));
          if ((options & PCRE_CASELESS) != 0)
            {
            int uc = cd->fcc[c];           
            classbits[uc/8] |= (1 << (uc&7));
            }
          class_charcount++;                
          class_lastchar = c;
          }

        continue;   
        }

      

      LONE_SINGLE_CHARACTER:

      

#ifdef SUPPORT_UTF8
      if (utf8 && (c > 255 || ((options & PCRE_CASELESS) != 0 && c > 127)))
        {
        class_utf8 = TRUE;
        *class_utf8data++ = XCL_SINGLE;
        class_utf8data += ord2utf8(c, class_utf8data);

#ifdef SUPPORT_UCP
        if ((options & PCRE_CASELESS) != 0)
          {
          int chartype;
          int othercase;
          if (ucp_findchar(c, &chartype, &othercase) >= 0 && othercase > 0)
            {
            *class_utf8data++ = XCL_SINGLE;
            class_utf8data += ord2utf8(othercase, class_utf8data);
            }
          }
#endif  

        }
      else
#endif  

      
        {
        classbits[c/8] |= (1 << (c&7));
        if ((options & PCRE_CASELESS) != 0)
          {
          c = cd->fcc[c];   
          classbits[c/8] |= (1 << (c&7));
          }
        class_charcount++;
        class_lastchar = c;
        }
      }

    

    while ((c = *(++ptr)) != ']' || inescq);

    

#ifdef SUPPORT_UTF8
    if (class_charcount == 1 &&
          (!utf8 ||
          (!class_utf8 && (!negate_class || class_lastchar < 128))))

#else
    if (class_charcount == 1)
#endif
      {
      zeroreqbyte = reqbyte;

      

      if (negate_class)
        {
        if (firstbyte == REQ_UNSET) firstbyte = REQ_NONE;
        zerofirstbyte = firstbyte;
        *code++ = OP_NOT;
        *code++ = class_lastchar;
        break;
        }

      

#ifdef SUPPORT_UTF8
      if (utf8 && class_lastchar > 127)
        mclength = ord2utf8(class_lastchar, mcbuffer);
      else
#endif
        {
        mcbuffer[0] = class_lastchar;
        mclength = 1;
        }
      goto ONE_CHAR;
      }       

    

    if (firstbyte == REQ_UNSET) firstbyte = REQ_NONE;
    zerofirstbyte = firstbyte;
    zeroreqbyte = reqbyte;

    

#ifdef SUPPORT_UTF8
    if (class_utf8)
      {
      *class_utf8data++ = XCL_END;    
      *code++ = OP_XCLASS;
      code += LINK_SIZE;
      *code = negate_class? XCL_NOT : 0;

      

      if (class_charcount > 0)
        {
        *code++ |= XCL_MAP;
        memcpy(code, classbits, 32);
        code = class_utf8data;
        }

      

      else
        {
        int len = class_utf8data - (code + 33);
        memmove(code + 1, code + 33, len);
        code += len + 1;
        }

      

      PUT(previous, 1, code - previous);
      break;   
      }
#endif

    

    if (negate_class)
      {
      *code++ = OP_NCLASS;
      for (c = 0; c < 32; c++) code[c] = ~classbits[c];
      }
    else
      {
      *code++ = OP_CLASS;
      memcpy(code, classbits, 32);
      }
    code += 32;
    break;

    

    case '{':
    if (!is_quantifier) goto NORMAL_CHAR;
    ptr = read_repeat_counts(ptr+1, &repeat_min, &repeat_max, errorptr);
    if (*errorptr != NULL) goto FAILED;
    goto REPEAT;

    case '*':
    repeat_min = 0;
    repeat_max = -1;
    goto REPEAT;

    case '+':
    repeat_min = 1;
    repeat_max = -1;
    goto REPEAT;

    case '?':
    repeat_min = 0;
    repeat_max = 1;

    REPEAT:
    if (previous == NULL)
      {
      *errorptr = ERR9;
      goto FAILED;
      }

    if (repeat_min == 0)
      {
      firstbyte = zerofirstbyte;    
      reqbyte = zeroreqbyte;        
      }

    

    reqvary = (repeat_min == repeat_max)? 0 : REQ_VARY;

    op_type = 0;                    
    possessive_quantifier = FALSE;  

    

    tempcode = previous;

    

    if (ptr[1] == '+')
      {
      repeat_type = 0;                  
      possessive_quantifier = TRUE;
      ptr++;
      }
    else if (ptr[1] == '?')
      {
      repeat_type = greedy_non_default;
      ptr++;
      }
    else repeat_type = greedy_default;

    

    if (*previous == OP_RECURSE)
      {
      memmove(previous + 1 + LINK_SIZE, previous, 1 + LINK_SIZE);
      code += 1 + LINK_SIZE;
      *previous = OP_BRA;
      PUT(previous, 1, code - previous);
      *code = OP_KET;
      PUT(code, 1, code - previous);
      code += 1 + LINK_SIZE;
      }

    

    if (*previous == OP_CHAR || *previous == OP_CHARNC)
      {
      

#ifdef SUPPORT_UTF8
      if (utf8 && (code[-1] & 0x80) != 0)
        {
        uschar *lastchar = code - 1;
        while((*lastchar & 0xc0) == 0x80) lastchar--;
        c = code - lastchar;            
        memcpy(utf8_char, lastchar, c); 
        c |= 0x80;                      
        }
      else
#endif

      

        {
        c = code[-1];
        if (repeat_min > 1) reqbyte = c | req_caseopt | cd->req_varyopt;
        }

      goto OUTPUT_SINGLE_REPEAT;   
      }

    

    else if (*previous == OP_NOT)
      {
      op_type = OP_NOTSTAR - OP_STAR;  
      c = previous[1];
      goto OUTPUT_SINGLE_REPEAT;
      }

    

    else if (*previous < OP_EODN)
      {
      uschar *oldcode;
      int prop_type;
      op_type = OP_TYPESTAR - OP_STAR;  
      c = *previous;

      OUTPUT_SINGLE_REPEAT:
      prop_type = (*previous == OP_PROP || *previous == OP_NOTPROP)?
        previous[1] : -1;

      oldcode = code;
      code = previous;                  

      

      if (repeat_max == 0) goto END_REPEAT;

      

      if (repeat_max != 1) cd->nopartial = TRUE;

      

      repeat_type += op_type;

      

      if (repeat_min == 0)
        {
        if (repeat_max == -1) *code++ = OP_STAR + repeat_type;
          else if (repeat_max == 1) *code++ = OP_QUERY + repeat_type;
        else
          {
          *code++ = OP_UPTO + repeat_type;
          PUT2INC(code, 0, repeat_max);
          }
        }

      

      else if (repeat_min == 1)
        {
        if (repeat_max == -1)
          *code++ = OP_PLUS + repeat_type;
        else
          {
          code = oldcode;                 
          if (repeat_max == 1) goto END_REPEAT;
          *code++ = OP_UPTO + repeat_type;
          PUT2INC(code, 0, repeat_max - 1);
          }
        }

      

      else
        {
        *code++ = OP_EXACT + op_type;  
        PUT2INC(code, 0, repeat_min);

        

        if (repeat_max < 0)
          {
#ifdef SUPPORT_UTF8
          if (utf8 && c >= 128)
            {
            memcpy(code, utf8_char, c & 7);
            code += c & 7;
            }
          else
#endif
            {
            *code++ = c;
            if (prop_type >= 0) *code++ = prop_type;
            }
          *code++ = OP_STAR + repeat_type;
          }

        

        else if (repeat_max != repeat_min)
          {
#ifdef SUPPORT_UTF8
          if (utf8 && c >= 128)
            {
            memcpy(code, utf8_char, c & 7);
            code += c & 7;
            }
          else
#endif
          *code++ = c;
          if (prop_type >= 0) *code++ = prop_type;
          repeat_max -= repeat_min;
          *code++ = OP_UPTO + repeat_type;
          PUT2INC(code, 0, repeat_max);
          }
        }

      

#ifdef SUPPORT_UTF8
      if (utf8 && c >= 128)
        {
        memcpy(code, utf8_char, c & 7);
        code += c & 7;
        }
      else
#endif
      *code++ = c;

      

#ifdef SUPPORT_UCP
      if (prop_type >= 0) *code++ = prop_type;
#endif
      }

    

    else if (*previous == OP_CLASS ||
             *previous == OP_NCLASS ||
#ifdef SUPPORT_UTF8
             *previous == OP_XCLASS ||
#endif
             *previous == OP_REF)
      {
      if (repeat_max == 0)
        {
        code = previous;
        goto END_REPEAT;
        }

      

      if (repeat_max != 1) cd->nopartial = TRUE;

      if (repeat_min == 0 && repeat_max == -1)
        *code++ = OP_CRSTAR + repeat_type;
      else if (repeat_min == 1 && repeat_max == -1)
        *code++ = OP_CRPLUS + repeat_type;
      else if (repeat_min == 0 && repeat_max == 1)
        *code++ = OP_CRQUERY + repeat_type;
      else
        {
        *code++ = OP_CRRANGE + repeat_type;
        PUT2INC(code, 0, repeat_min);
        if (repeat_max == -1) repeat_max = 0;  
        PUT2INC(code, 0, repeat_max);
        }
      }

    

    else if (*previous >= OP_BRA || *previous == OP_ONCE ||
             *previous == OP_COND)
      {
      register int i;
      int ketoffset = 0;
      int len = code - previous;
      uschar *bralink = NULL;

      

      if (repeat_max == -1)
        {
        register uschar *ket = previous;
        do ket += GET(ket, 1); while (*ket != OP_KET);
        ketoffset = code - ket;
        }

      

      if (repeat_min == 0)
        {
        

        if (repeat_max == 0)
          {
          code = previous;
          goto END_REPEAT;
          }

        

        if (repeat_max <= 1)
          {
          *code = OP_END;
          adjust_recurse(previous, 1, utf8, cd);
          memmove(previous+1, previous, len);
          code++;
          *previous++ = OP_BRAZERO + repeat_type;
          }

        

        else
          {
          int offset;
          *code = OP_END;
          adjust_recurse(previous, 2 + LINK_SIZE, utf8, cd);
          memmove(previous + 2 + LINK_SIZE, previous, len);
          code += 2 + LINK_SIZE;
          *previous++ = OP_BRAZERO + repeat_type;
          *previous++ = OP_BRA;

          

          offset = (bralink == NULL)? 0 : previous - bralink;
          bralink = previous;
          PUTINC(previous, 0, offset);
          }

        repeat_max--;
        }

      

      else
        {
        if (repeat_min > 1)
          {
          if (groupsetfirstbyte && reqbyte < 0) reqbyte = firstbyte;
          for (i = 1; i < repeat_min; i++)
            {
            memcpy(code, previous, len);
            code += len;
            }
          }
        if (repeat_max > 0) repeat_max -= repeat_min;
        }

      

      if (repeat_max >= 0)
        {
        for (i = repeat_max - 1; i >= 0; i--)
          {
          *code++ = OP_BRAZERO + repeat_type;

          

          if (i != 0)
            {
            int offset;
            *code++ = OP_BRA;
            offset = (bralink == NULL)? 0 : code - bralink;
            bralink = code;
            PUTINC(code, 0, offset);
            }

          memcpy(code, previous, len);
          code += len;
          }

        

        while (bralink != NULL)
          {
          int oldlinkoffset;
          int offset = code - bralink + 1;
          uschar *bra = code - offset;
          oldlinkoffset = GET(bra, 1);
          bralink = (oldlinkoffset == 0)? NULL : bralink - oldlinkoffset;
          *code++ = OP_KET;
          PUTINC(code, 0, offset);
          PUT(bra, 1, offset);
          }
        }

      

      else code[-ketoffset] = OP_KETRMAX + repeat_type;
      }

    

    else
      {
      *errorptr = ERR11;
      goto FAILED;
      }

    

    if (possessive_quantifier)
      {
      int len = code - tempcode;
      memmove(tempcode + 1+LINK_SIZE, tempcode, len);
      code += 1 + LINK_SIZE;
      len += 1 + LINK_SIZE;
      tempcode[0] = OP_ONCE;
      *code++ = OP_KET;
      PUTINC(code, 0, len);
      PUT(tempcode, 1, len);
      }

    

    END_REPEAT:
    previous = NULL;
    cd->req_varyopt |= reqvary;
    break;


    

    case '(':
    newoptions = options;
    skipbytes = 0;

    if (*(++ptr) == '?')
      {
      int set, unset;
      int *optset;

      switch (*(++ptr))
        {
        case '#':                 
        ptr++;
        while (*ptr != ')') ptr++;
        continue;

        case ':':                 
        bravalue = OP_BRA;
        ptr++;
        break;

        case '(':
        bravalue = OP_COND;       

        

        if (ptr[1] == 'R')
          {
          code[1+LINK_SIZE] = OP_CREF;
          PUT2(code, 2+LINK_SIZE, CREF_RECURSE);
          skipbytes = 3;
          ptr += 3;
          }

        

        else if ((digitab[ptr[1]] && ctype_digit) != 0)
          {
          int condref;                 
          condref = *(++ptr) - '0';    
          while (*(++ptr) != ')') condref = condref*10 + *ptr - '0';
          if (condref == 0)
            {
            *errorptr = ERR35;
            goto FAILED;
            }
          ptr++;
          code[1+LINK_SIZE] = OP_CREF;
          PUT2(code, 2+LINK_SIZE, condref);
          skipbytes = 3;
          }
        
        break;

        case '=':                 
        bravalue = OP_ASSERT;
        ptr++;
        break;

        case '!':                 
        bravalue = OP_ASSERT_NOT;
        ptr++;
        break;

        case '<':                 
        switch (*(++ptr))
          {
          case '=':               
          bravalue = OP_ASSERTBACK;
          ptr++;
          break;

          case '!':               
          bravalue = OP_ASSERTBACK_NOT;
          ptr++;
          break;
          }
        break;

        case '>':                 
        bravalue = OP_ONCE;
        ptr++;
        break;

        case 'C':                 
        previous_callout = code;  
        after_manual_callout = 1; 
        *code++ = OP_CALLOUT;     
          {                       
          int n = 0;
          while ((digitab[*(++ptr)] & ctype_digit) != 0)
            n = n * 10 + *ptr - '0';
          if (n > 255)
            {
            *errorptr = ERR38;
            goto FAILED;
            }
          *code++ = n;
          PUT(code, 0, ptr - cd->start_pattern + 1);  
          PUT(code, LINK_SIZE, 0);                    
          code += 2 * LINK_SIZE;
          }
        previous = NULL;
        continue;

        case 'P':                 
        if (*(++ptr) == '<')      
          {
          int i, namelen;
          uschar *slot = cd->name_table;
          const uschar *name;     
          name = ++ptr;           

          while (*ptr++ != '>');
          namelen = ptr - name - 1;

          for (i = 0; i < cd->names_found; i++)
            {
            int crc = memcmp(name, slot+2, namelen);
            if (crc == 0)
              {
              if (slot[2+namelen] == 0)
                {
                *errorptr = ERR43;
                goto FAILED;
                }
              crc = -1;             
              }
            if (crc < 0)
              {
              memmove(slot + cd->name_entry_size, slot,
                (cd->names_found - i) * cd->name_entry_size);
              break;
              }
            slot += cd->name_entry_size;
            }

          PUT2(slot, 0, *brackets + 1);
          memcpy(slot + 2, name, namelen);
          slot[2+namelen] = 0;
          cd->names_found++;
          goto NUMBERED_GROUP;
          }

        if (*ptr == '=' || *ptr == '>')  
          {
          int i, namelen;
          int type = *ptr++;
          const uschar *name = ptr;
          uschar *slot = cd->name_table;

          while (*ptr != ')') ptr++;
          namelen = ptr - name;

          for (i = 0; i < cd->names_found; i++)
            {
            if (strncmp((char *)name, (char *)slot+2, namelen) == 0) break;
            slot += cd->name_entry_size;
            }
          if (i >= cd->names_found)
            {
            *errorptr = ERR15;
            goto FAILED;
            }

          recno = GET2(slot, 0);

          if (type == '>') goto HANDLE_RECURSION;  

          

          previous = code;
          *code++ = OP_REF;
          PUT2INC(code, 0, recno);
          cd->backref_map |= (recno < 32)? (1 << recno) : 1;
          if (recno > cd->top_backref) cd->top_backref = recno;
          continue;
          }

        
        break;

        case 'R':                 
        ptr++;                    
        

        

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
          {
          const uschar *called;
          recno = 0;
          while((digitab[*ptr] & ctype_digit) != 0)
            recno = recno * 10 + *ptr++ - '0';

          

          HANDLE_RECURSION:

          previous = code;

          

          *code = OP_END;
          called = (recno == 0)?
            cd->start_code : find_bracket(cd->start_code, utf8, recno);

          if (called == NULL)
            {
            *errorptr = ERR15;
            goto FAILED;
            }

          

          if (GET(called, 1) == 0 && could_be_empty(called, code, bcptr, utf8))
            {
            *errorptr = ERR40;
            goto FAILED;
            }

          

          *code = OP_RECURSE;
          PUT(code, 1, called - cd->start_code);
          code += 1 + LINK_SIZE;
          }
        continue;

        

        default:                  
        set = unset = 0;
        optset = &set;

        while (*ptr != ')' && *ptr != ':')
          {
          switch (*ptr++)
            {
            case '-': optset = &unset; break;

            case 'i': *optset |= PCRE_CASELESS; break;
            case 'm': *optset |= PCRE_MULTILINE; break;
            case 's': *optset |= PCRE_DOTALL; break;
            case 'x': *optset |= PCRE_EXTENDED; break;
            case 'U': *optset |= PCRE_UNGREEDY; break;
            case 'X': *optset |= PCRE_EXTRA; break;
            }
          }

        

        newoptions = (options | set) & (~unset);

        

        if (*ptr == ')')
          {
          if ((options & PCRE_IMS) != (newoptions & PCRE_IMS))
            {
            *code++ = OP_OPT;
            *code++ = newoptions & PCRE_IMS;
            }

          

          *optionsptr = options = newoptions;
          greedy_default = ((newoptions & PCRE_UNGREEDY) != 0);
          greedy_non_default = greedy_default ^ 1;
          req_caseopt = ((options & PCRE_CASELESS) != 0)? REQ_CASELESS : 0;

          previous = NULL;       
          continue;              
          }

        

        bravalue = OP_BRA;
        ptr++;
        }
      }

    

    else if ((options & PCRE_NO_AUTO_CAPTURE) != 0)
      {
      bravalue = OP_BRA;
      }

    

    else
      {
      NUMBERED_GROUP:
      if (++(*brackets) > EXTRACT_BASIC_MAX)
        {
        bravalue = OP_BRA + EXTRACT_BASIC_MAX + 1;
        code[1+LINK_SIZE] = OP_BRANUMBER;
        PUT2(code, 2+LINK_SIZE, *brackets);
        skipbytes = 3;
        }
      else bravalue = OP_BRA + *brackets;
      }

    

    previous = (bravalue >= OP_ONCE)? code : NULL;
    *code = bravalue;
    tempcode = code;
    tempreqvary = cd->req_varyopt;     

    if (!compile_regex(
         newoptions,                   
         options & PCRE_IMS,           
         brackets,                     
         &tempcode,                    
         &ptr,                         
         errorptr,                     
         (bravalue == OP_ASSERTBACK ||
          bravalue == OP_ASSERTBACK_NOT), 
         skipbytes,                    
         &subfirstbyte,                
         &subreqbyte,                  
         bcptr,                        
         cd))                          
      goto FAILED;

    

    

    else if (bravalue == OP_COND)
      {
      uschar *tc = code;
      condcount = 0;

      do {
         condcount++;
         tc += GET(tc,1);
         }
      while (*tc != OP_KET);

      if (condcount > 2)
        {
        *errorptr = ERR27;
        goto FAILED;
        }

      

      if (condcount == 1) subfirstbyte = subreqbyte = REQ_NONE;
      }

    

    zeroreqbyte = reqbyte;
    zerofirstbyte = firstbyte;
    groupsetfirstbyte = FALSE;

    if (bravalue >= OP_BRA || bravalue == OP_ONCE || bravalue == OP_COND)
      {
      

      if (firstbyte == REQ_UNSET)
        {
        if (subfirstbyte >= 0)
          {
          firstbyte = subfirstbyte;
          groupsetfirstbyte = TRUE;
          }
        else firstbyte = REQ_NONE;
        zerofirstbyte = REQ_NONE;
        }

      

      else if (subfirstbyte >= 0 && subreqbyte < 0)
        subreqbyte = subfirstbyte | tempreqvary;

      

      if (subreqbyte >= 0) reqbyte = subreqbyte;
      }

    

    else if (bravalue == OP_ASSERT && subreqbyte >= 0) reqbyte = subreqbyte;

    

    code = tempcode;

    

    if (*ptr != ')')
      {
      *errorptr = ERR14;
      goto FAILED;
      }
    break;

    

    case '\\':
    tempptr = ptr;
    c = check_escape(&ptr, errorptr, *brackets, options, FALSE);

    

    if (c < 0)
      {
      if (-c == ESC_Q)            
        {
        if (ptr[1] == '\\' && ptr[2] == 'E') ptr += 2; 
          else inescq = TRUE;
        continue;
        }

      

      if (firstbyte == REQ_UNSET && -c > ESC_b && -c < ESC_Z)
        firstbyte = REQ_NONE;

      

      zerofirstbyte = firstbyte;
      zeroreqbyte = reqbyte;

      

      if (-c >= ESC_REF)
        {
        int number = -c - ESC_REF;
        previous = code;
        *code++ = OP_REF;
        PUT2INC(code, 0, number);
        }

      

#ifdef SUPPORT_UCP
      else if (-c == ESC_P || -c == ESC_p)
        {
        BOOL negated;
        int value = get_ucp(&ptr, &negated, errorptr);
        previous = code;
        *code++ = ((-c == ESC_p) != negated)? OP_PROP : OP_NOTPROP;
        *code++ = value;
        }
#endif

      

      else
        {
        previous = (-c > ESC_b && -c < ESC_Z)? code : NULL;
        *code++ = -c;
        }
      continue;
      }

    

#ifdef SUPPORT_UTF8
    if (utf8 && c > 127)
      mclength = ord2utf8(c, mcbuffer);
    else
#endif

     {
     mcbuffer[0] = c;
     mclength = 1;
     }

    goto ONE_CHAR;

    

    default:
    NORMAL_CHAR:
    mclength = 1;
    mcbuffer[0] = c;

#ifdef SUPPORT_UTF8
    if (utf8 && (c & 0xc0) == 0xc0)
      {
      while ((ptr[1] & 0xc0) == 0x80)
        mcbuffer[mclength++] = *(++ptr);
      }
#endif

    

    ONE_CHAR:
    previous = code;
    *code++ = ((options & PCRE_CASELESS) != 0)? OP_CHARNC : OP_CHAR;
    for (c = 0; c < mclength; c++) *code++ = mcbuffer[c];

    

    if (firstbyte == REQ_UNSET)
      {
      zerofirstbyte = REQ_NONE;
      zeroreqbyte = reqbyte;

      

      if (mclength == 1 || req_caseopt == 0)
        {
        firstbyte = mcbuffer[0] | req_caseopt;
        if (mclength != 1) reqbyte = code[-1] | cd->req_varyopt;
        }
      else firstbyte = reqbyte = REQ_NONE;
      }

    

    else
      {
      zerofirstbyte = firstbyte;
      zeroreqbyte = reqbyte;
      if (mclength == 1 || req_caseopt == 0)
        reqbyte = code[-1] | req_caseopt | cd->req_varyopt;
      }

    break;            
    }
  }                   



FAILED:
*ptrptr = ptr;
return FALSE;
}








static BOOL
compile_regex(int options, int oldims, int *brackets, uschar **codeptr,
  const uschar **ptrptr, const char **errorptr, BOOL lookbehind, int skipbytes,
  int *firstbyteptr, int *reqbyteptr, branch_chain *bcptr, compile_data *cd)
{
const uschar *ptr = *ptrptr;
uschar *code = *codeptr;
uschar *last_branch = code;
uschar *start_bracket = code;
uschar *reverse_count = NULL;
int firstbyte, reqbyte;
int branchfirstbyte, branchreqbyte;
branch_chain bc;

bc.outer = bcptr;
bc.current = code;

firstbyte = reqbyte = REQ_UNSET;



PUT(code, 1, 0);
code += 1 + LINK_SIZE + skipbytes;



for (;;)
  {
  

  if ((options & PCRE_IMS) != oldims)
    {
    *code++ = OP_OPT;
    *code++ = options & PCRE_IMS;
    }

  

  if (lookbehind)
    {
    *code++ = OP_REVERSE;
    reverse_count = code;
    PUTINC(code, 0, 0);
    }

  

  if (!compile_branch(&options, brackets, &code, &ptr, errorptr,
        &branchfirstbyte, &branchreqbyte, &bc, cd))
    {
    *ptrptr = ptr;
    return FALSE;
    }

  

  if (*last_branch != OP_ALT)
    {
    firstbyte = branchfirstbyte;
    reqbyte = branchreqbyte;
    }

  

  else
    {
    

    if (firstbyte >= 0 && firstbyte != branchfirstbyte)
      {
      if (reqbyte < 0) reqbyte = firstbyte;
      firstbyte = REQ_NONE;
      }

    

    if (firstbyte < 0 && branchfirstbyte >= 0 && branchreqbyte < 0)
        branchreqbyte = branchfirstbyte;

    

    if ((reqbyte & ~REQ_VARY) != (branchreqbyte & ~REQ_VARY))
      reqbyte = REQ_NONE;
    else reqbyte |= branchreqbyte;   
    }

  

  if (lookbehind)
    {
    int length;
    *code = OP_END;
    length = find_fixedlength(last_branch, options);
    DPRINTF(("fixed length = %d\n", length));
    if (length < 0)
      {
      *errorptr = (length == -2)? ERR36 : ERR25;
      *ptrptr = ptr;
      return FALSE;
      }
    PUT(reverse_count, 0, length);
    }

  

  if (*ptr != '|')
    {
    int length = code - last_branch;
    do
      {
      int prev_length = GET(last_branch, 1);
      PUT(last_branch, 1, length);
      length = prev_length;
      last_branch -= length;
      }
    while (length > 0);

    

    *code = OP_KET;
    PUT(code, 1, code - start_bracket);
    code += 1 + LINK_SIZE;

    

    if ((options & PCRE_IMS) != oldims && *ptr == ')')
      {
      *code++ = OP_OPT;
      *code++ = oldims;
      }

    

    *codeptr = code;
    *ptrptr = ptr;
    *firstbyteptr = firstbyte;
    *reqbyteptr = reqbyte;
    return TRUE;
    }

  

  *code = OP_ALT;
  PUT(code, 1, code - last_branch);
  bc.current = last_branch = code;
  code += 1 + LINK_SIZE;
  ptr++;
  }

}








static BOOL
is_anchored(register const uschar *code, int *options, unsigned int bracket_map,
  unsigned int backref_map)
{
do {
   const uschar *scode =
     first_significant_code(code + 1+LINK_SIZE, options, PCRE_MULTILINE, FALSE);
   register int op = *scode;

   

   if (op > OP_BRA)
     {
     int new_map;
     op -= OP_BRA;
     if (op > EXTRACT_BASIC_MAX) op = GET2(scode, 2+LINK_SIZE);
     new_map = bracket_map | ((op < 32)? (1 << op) : 1);
     if (!is_anchored(scode, options, new_map, backref_map)) return FALSE;
     }

   

   else if (op == OP_BRA || op == OP_ASSERT || op == OP_ONCE || op == OP_COND)
     {
     if (!is_anchored(scode, options, bracket_map, backref_map)) return FALSE;
     }

   

   else if ((op == OP_TYPESTAR || op == OP_TYPEMINSTAR) &&
            (*options & PCRE_DOTALL) != 0)
     {
     if (scode[1] != OP_ANY || (bracket_map & backref_map) != 0) return FALSE;
     }

   

   else if (op != OP_SOD && op != OP_SOM &&
           ((*options & PCRE_MULTILINE) != 0 || op != OP_CIRC))
     return FALSE;
   code += GET(code, 1);
   }
while (*code == OP_ALT);   
return TRUE;
}







static BOOL
is_startline(const uschar *code, unsigned int bracket_map,
  unsigned int backref_map)
{
do {
   const uschar *scode = first_significant_code(code + 1+LINK_SIZE, NULL, 0,
     FALSE);
   register int op = *scode;

   

   if (op > OP_BRA)
     {
     int new_map;
     op -= OP_BRA;
     if (op > EXTRACT_BASIC_MAX) op = GET2(scode, 2+LINK_SIZE);
     new_map = bracket_map | ((op < 32)? (1 << op) : 1);
     if (!is_startline(scode, new_map, backref_map)) return FALSE;
     }

   

   else if (op == OP_BRA || op == OP_ASSERT || op == OP_ONCE || op == OP_COND)
     { if (!is_startline(scode, bracket_map, backref_map)) return FALSE; }

   

   else if (op == OP_TYPESTAR || op == OP_TYPEMINSTAR)
     {
     if (scode[1] != OP_ANY || (bracket_map & backref_map) != 0) return FALSE;
     }

   

   else if (op != OP_CIRC) return FALSE;

   

   code += GET(code, 1);
   }
while (*code == OP_ALT);  
return TRUE;
}







static int
find_firstassertedchar(const uschar *code, int *options, BOOL inassert)
{
register int c = -1;
do {
   int d;
   const uschar *scode =
     first_significant_code(code + 1+LINK_SIZE, options, PCRE_CASELESS, TRUE);
   register int op = *scode;

   if (op >= OP_BRA) op = OP_BRA;

   switch(op)
     {
     default:
     return -1;

     case OP_BRA:
     case OP_ASSERT:
     case OP_ONCE:
     case OP_COND:
     if ((d = find_firstassertedchar(scode, options, op == OP_ASSERT)) < 0)
       return -1;
     if (c < 0) c = d; else if (c != d) return -1;
     break;

     case OP_EXACT:       
     scode += 2;

     case OP_CHAR:
     case OP_CHARNC:
     case OP_PLUS:
     case OP_MINPLUS:
     if (!inassert) return -1;
     if (c < 0)
       {
       c = scode[1];
       if ((*options & PCRE_CASELESS) != 0) c |= REQ_CASELESS;
       }
     else if (c != scode[1]) return -1;
     break;
     }

   code += GET(code, 1);
   }
while (*code == OP_ALT);
return c;
}




#ifdef SUPPORT_UTF8




static int
valid_utf8(const uschar *string, int length)
{
register const uschar *p;

if (length < 0)
  {
  for (p = string; *p != 0; p++);
  length = p - string;
  }

for (p = string; length-- > 0; p++)
  {
  register int ab;
  register int c = *p;
  if (c < 128) continue;
  if ((c & 0xc0) != 0xc0) return p - string;
  ab = utf8_table4[c & 0x3f];  
  if (length < ab) return p - string;
  length -= ab;

  
  if ((*(++p) & 0xc0) != 0x80) return p - string;

  
  switch (ab)
    {
    
    case 1:
    if ((c & 0x3e) == 0) return p - string;
    continue;   

    
    case 2:
    if (c == 0xe0 && (*p & 0x20) == 0) return p - string;
    break;

    
    case 3:
    if (c == 0xf0 && (*p & 0x30) == 0) return p - string;
    break;

    
    case 4:
    if (c == 0xf8 && (*p & 0x38) == 0) return p - string;
    break;

    
    case 5:
    if (c == 0xfe || c == 0xff ||
       (c == 0xfc && (*p & 0x3c) == 0)) return p - string;
    break;
    }

  
  while (--ab > 0)
    {
    if ((*(++p) & 0xc0) != 0x80) return p - string;
    }
  }

return -1;
}
#endif







EXPORT pcre *
pcre_compile(const char *pattern, int options, const char **errorptr,
  int *erroroffset, const unsigned char *tables)
{
real_pcre *re;
int length = 1 + LINK_SIZE;      
int c, firstbyte, reqbyte;
int bracount = 0;
int branch_extra = 0;
int branch_newextra;
int item_count = -1;
int name_count = 0;
int max_name_size = 0;
int lastitemlength = 0;
#ifdef SUPPORT_UTF8
BOOL utf8;
BOOL class_utf8;
#endif
BOOL inescq = FALSE;
unsigned int brastackptr = 0;
size_t size;
uschar *code;
const uschar *codestart;
const uschar *ptr;
compile_data compile_block;
int brastack[BRASTACK_SIZE];
uschar bralenstack[BRASTACK_SIZE];



if (errorptr == NULL) return NULL;
*errorptr = NULL;



if (erroroffset == NULL)
  {
  *errorptr = ERR16;
  return NULL;
  }
*erroroffset = 0;



#ifdef SUPPORT_UTF8
utf8 = (options & PCRE_UTF8) != 0;
if (utf8 && (options & PCRE_NO_UTF8_CHECK) == 0 &&
     (*erroroffset = valid_utf8((uschar *)pattern, -1)) >= 0)
  {
  *errorptr = ERR44;
  return NULL;
  }
#else
if ((options & PCRE_UTF8) != 0)
  {
  *errorptr = ERR32;
  return NULL;
  }
#endif

if ((options & ~PUBLIC_OPTIONS) != 0)
  {
  *errorptr = ERR17;
  return NULL;
  }



if (tables == NULL) tables = pcre_default_tables;
compile_block.lcc = tables + lcc_offset;
compile_block.fcc = tables + fcc_offset;
compile_block.cbits = tables + cbits_offset;
compile_block.ctypes = tables + ctypes_offset;



compile_block.top_backref = 0;
compile_block.backref_map = 0;



DPRINTF(("------------------------------------------------------------------\n"));
DPRINTF(("%s\n", pattern));



ptr = (const uschar *)(pattern - 1);
while ((c = *(++ptr)) != 0)
  {
  int min, max;
  int class_optcount;
  int bracket_length;
  int duplength;

  

  if (inescq)
    {
    if ((options & PCRE_AUTO_CALLOUT) != 0) length += 2 + 2*LINK_SIZE;
    goto NORMAL_CHAR;
    }

  

  if ((options & PCRE_EXTENDED) != 0)
    {
    if ((compile_block.ctypes[c] & ctype_space) != 0) continue;
    if (c == '#')
      {
      
      while ((c = *(++ptr)) != 0 && c != NEWLINE) ;
      if (c == 0) break;
      continue;
      }
    }

  item_count++;    

  

  if ((options & PCRE_AUTO_CALLOUT) != 0 &&
       c != '*' && c != '+' && c != '?' &&
       (c != '{' || !is_counted_repeat(ptr + 1)))
    length += 2 + 2*LINK_SIZE;

  switch(c)
    {
    

    case '\\':
    c = check_escape(&ptr, errorptr, bracount, options, FALSE);
    if (*errorptr != NULL) goto PCRE_ERROR_RETURN;

    lastitemlength = 1;     

    if (c >= 0)             
      {
      length += 2;          

#ifdef SUPPORT_UTF8
      if (utf8 && c > 127)
        {
        int i;
        for (i = 0; i < sizeof(utf8_table1)/sizeof(int); i++)
          if (c <= utf8_table1[i]) break;
        length += i;
        lastitemlength += i;
        }
#endif

      continue;
      }

    

    if (-c == ESC_Q)
      {
      inescq = TRUE;
      continue;
      }

    

#ifndef SUPPORT_UCP
    if (-c == ESC_X)
      {
      *errorptr = ERR45;
      goto PCRE_ERROR_RETURN;
      }
#endif

    

    else if (-c == ESC_P || -c == ESC_p)
      {
#ifdef SUPPORT_UCP
      BOOL negated;
      length += 2;
      lastitemlength = 2;
      if (get_ucp(&ptr, &negated, errorptr) < 0) goto PCRE_ERROR_RETURN;
      continue;
#else
      *errorptr = ERR45;
      goto PCRE_ERROR_RETURN;
#endif
      }

    

    length++;

    

    if (c <= -ESC_REF)
      {
      int refnum = -c - ESC_REF;
      compile_block.backref_map |= (refnum < 32)? (1 << refnum) : 1;
      if (refnum > compile_block.top_backref)
        compile_block.top_backref = refnum;
      length += 2;   
      if (ptr[1] == '{' && is_counted_repeat(ptr+2))
        {
        ptr = read_repeat_counts(ptr+2, &min, &max, errorptr);
        if (*errorptr != NULL) goto PCRE_ERROR_RETURN;
        if ((min == 0 && (max == 1 || max == -1)) ||
          (min == 1 && max == -1))
            length++;
        else length += 5;
        if (ptr[1] == '?') ptr++;
        }
      }
    continue;

    case '^':     
    case '.':
    case '$':
    length++;
    lastitemlength = 1;
    continue;

    case '*':            
    case '+':            
    case '?':
    length++;
    goto POSESSIVE;      

    

    case '{':
    if (!is_counted_repeat(ptr+1)) goto NORMAL_CHAR;
    ptr = read_repeat_counts(ptr+1, &min, &max, errorptr);
    if (*errorptr != NULL) goto PCRE_ERROR_RETURN;

    

    if ((min == 0 && (max == 1 || max == -1)) ||
      (min == 1 && max == -1))
        length++;

    

    else
      {
      if (min != 1)
        {
        length -= lastitemlength;   
        if (min > 0) length += 3 + lastitemlength;
        }
      length += lastitemlength + ((max > 0)? 3 : 1);
      }

    if (ptr[1] == '?') ptr++;      

    POSESSIVE:                     
    if (ptr[1] == '+')
      {
      ptr++;
      length += 2 + 2*LINK_SIZE;   
      }
    continue;

    

    case '|':
    length += 1 + LINK_SIZE + branch_extra;
    continue;

    

    case '[':
    if (*(++ptr) == '^')
      {
      class_optcount = 10;  
      ptr++;
      }
    else class_optcount = 0;

#ifdef SUPPORT_UTF8
    class_utf8 = FALSE;
#endif

    

    if (*ptr != 0) do
      {
      

      if (inescq)
        {
        if (*ptr != '\\' || ptr[1] != 'E') goto GET_ONE_CHARACTER;
        inescq = FALSE;
        ptr += 1;
        continue;
        }

      

      if (*ptr == '\\')
        {
        c = check_escape(&ptr, errorptr, bracount, options, TRUE);
        if (*errorptr != NULL) goto PCRE_ERROR_RETURN;

        

        if (-c == ESC_b) c = '\b';
        else if (-c == ESC_X) c = 'X';

        

        else if (-c == ESC_Q)
          {
          inescq = TRUE;
          continue;
          }

        

        if (c >= 0) goto NON_SPECIAL_CHARACTER;

        

        else
          {
          class_optcount = 10;         
#ifdef SUPPORT_UTF8
          if (-c == ESC_p || -c == ESC_P)
            {
            if (!class_utf8)
              {
              class_utf8 = TRUE;
              length += LINK_SIZE + 2;
              }
            length += 2;
            }
#endif
          }
        }

      

      else if (*ptr == '[' && check_posix_syntax(ptr, &ptr, &compile_block))
        {
        ptr++;
        class_optcount = 10;    
        }

      

      else
        {
        int d;

        GET_ONE_CHARACTER:

#ifdef SUPPORT_UTF8
        if (utf8)
          {
          int extra = 0;
          GETCHARLEN(c, ptr, extra);
          ptr += extra;
          }
        else c = *ptr;
#else
        c = *ptr;
#endif

        

        NON_SPECIAL_CHARACTER:
        class_optcount++;

        d = -1;
        if (ptr[1] == '-')
          {
          uschar const *hyptr = ptr++;
          if (ptr[1] == '\\')
            {
            ptr++;
            d = check_escape(&ptr, errorptr, bracount, options, TRUE);
            if (*errorptr != NULL) goto PCRE_ERROR_RETURN;
            if (-d == ESC_b) d = '\b';        
            else if (-d == ESC_X) d = 'X';    
            }
          else if (ptr[1] != 0 && ptr[1] != ']')
            {
            ptr++;
#ifdef SUPPORT_UTF8
            if (utf8)
              {
              int extra = 0;
              GETCHARLEN(d, ptr, extra);
              ptr += extra;
              }
            else
#endif
            d = *ptr;
            }
          if (d < 0) ptr = hyptr;      
          }

        

        if (d >= 0)
          {
          class_optcount = 10;     
          if (d < c)
            {
            *errorptr = ERR8;
            goto PCRE_ERROR_RETURN;
            }

#ifdef SUPPORT_UTF8
          if (utf8 && (d > 255 || ((options & PCRE_CASELESS) != 0 && d > 127)))
            {
            uschar buffer[6];
            if (!class_utf8)         
              {
              class_utf8 = TRUE;
              length += LINK_SIZE + 2;
              }

#ifdef SUPPORT_UCP
            

            if ((options & PCRE_CASELESS) != 0)
              {
              int occ, ocd;
              int cc = c;
              int origd = d;
              while (get_othercase_range(&cc, origd, &occ, &ocd))
                {
                if (occ >= c && ocd <= d) continue;   

                if (occ < c  && ocd >= c - 1)  
                  {                            
                  c = occ;                     
                  continue;                    
                  }                            
                if (ocd > d && occ <= d + 1)   
                  {                            
                  d = ocd;
                  continue;
                  }

                

                length += 1 + ord2utf8(occ, buffer) +
                  ((occ == ocd)? 0 : ord2utf8(ocd, buffer));
                }
              }
#endif  

            

            length += 1 + ord2utf8(c, buffer) + ord2utf8(d, buffer);
            }
#endif  

          }

        

        else
          {
#ifdef SUPPORT_UTF8
          if (utf8 && (c > 255 || ((options & PCRE_CASELESS) != 0 && c > 127)))
            {
            uschar buffer[6];
            class_optcount = 10;     
            if (!class_utf8)         
              {
              class_utf8 = TRUE;
              length += LINK_SIZE + 2;
              }
#ifdef SUPPORT_UCP
            length += (((options & PCRE_CASELESS) != 0)? 2 : 1) *
              (1 + ord2utf8(c, buffer));
#else   
            length += 1 + ord2utf8(c, buffer);
#endif  
            }
#endif  
          }
        }
      }
    while (*(++ptr) != 0 && (inescq || *ptr != ']')); 

    if (*ptr == 0)                          
      {
      *errorptr = ERR6;
      goto PCRE_ERROR_RETURN;
      }

    

    if (class_optcount == 1) length += 3; else
      {
      length += 33;

      

      if (*ptr != 0 && ptr[1] == '{' && is_counted_repeat(ptr+2))
        {
        ptr = read_repeat_counts(ptr+2, &min, &max, errorptr);
        if (*errorptr != NULL) goto PCRE_ERROR_RETURN;
        if ((min == 0 && (max == 1 || max == -1)) ||
          (min == 1 && max == -1))
            length++;
        else length += 5;
        if (ptr[1] == '+')
          {
          ptr++;
          length += 2 + 2*LINK_SIZE;
          }
        else if (ptr[1] == '?') ptr++;
        }
      }
    continue;

    

    case '(':
    branch_newextra = 0;
    bracket_length = 1 + LINK_SIZE;

    

    if (ptr[1] == '?')
      {
      int set, unset;
      int *optset;

      switch (c = ptr[2])
        {
        
        case '#':
        ptr += 3;
        while (*ptr != 0 && *ptr != ')') ptr++;
        if (*ptr == 0)
          {
          *errorptr = ERR18;
          goto PCRE_ERROR_RETURN;
          }
        continue;

        

        case ':':
        case '=':
        case '!':
        case '>':
        ptr += 2;
        break;

        

        case 'R':
        ptr++;

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        ptr += 2;
        if (c != 'R')
          while ((digitab[*(++ptr)] & ctype_digit) != 0);
        if (*ptr != ')')
          {
          *errorptr = ERR29;
          goto PCRE_ERROR_RETURN;
          }
        length += 1 + LINK_SIZE;

        

        if (ptr[1] == '+' || ptr[1] == '*' || ptr[1] == '?' || ptr[1] == '{')
          {
          length += 2 + 2 * LINK_SIZE;       
          duplength = 5 + 3 * LINK_SIZE;
          goto HANDLE_QUANTIFIED_BRACKETS;
          }
        continue;

        

        case 'C':
        ptr += 2;
        while ((digitab[*(++ptr)] & ctype_digit) != 0);
        if (*ptr != ')')
          {
          *errorptr = ERR39;
          goto PCRE_ERROR_RETURN;
          }
        length += 2 + 2*LINK_SIZE;
        continue;

        

        case 'P':
        ptr += 3;
        if (*ptr == '<')
          {
          const uschar *p;    
          p = ++ptr;          
          while ((compile_block.ctypes[*ptr] & ctype_word) != 0) ptr++;
          if (*ptr != '>')
            {
            *errorptr = ERR42;
            goto PCRE_ERROR_RETURN;
            }
          name_count++;
          if (ptr - p > max_name_size) max_name_size = (ptr - p);
          break;
          }

        if (*ptr == '=' || *ptr == '>')
          {
          while ((compile_block.ctypes[*(++ptr)] & ctype_word) != 0);
          if (*ptr != ')')
            {
            *errorptr = ERR42;
            goto PCRE_ERROR_RETURN;
            }
          break;
          }

        

        *errorptr = ERR41;
        goto PCRE_ERROR_RETURN;

        

        case '<':
        ptr += 3;
        if (*ptr == '=' || *ptr == '!')
          {
          branch_newextra = 1 + LINK_SIZE;
          length += 1 + LINK_SIZE;         
          break;
          }
        *errorptr = ERR24;
        goto PCRE_ERROR_RETURN;

        

        case '(':
        if (ptr[3] == 'R' && ptr[4] == ')')
          {
          ptr += 4;
          length += 3;
          }
        else if ((digitab[ptr[3]] & ctype_digit) != 0)
          {
          ptr += 4;
          length += 3;
          while ((digitab[*ptr] & ctype_digit) != 0) ptr++;
          if (*ptr != ')')
            {
            *errorptr = ERR26;
            goto PCRE_ERROR_RETURN;
            }
          }
        else   
          {
          ptr++;   
          if (ptr[2] != '?' ||
             (ptr[3] != '=' && ptr[3] != '!' && ptr[3] != '<') )
            {
            ptr += 2;    
            *errorptr = ERR28;
            goto PCRE_ERROR_RETURN;
            }
          }
        break;

        

        default:
        set = unset = 0;
        optset = &set;
        ptr += 2;

        for (;; ptr++)
          {
          c = *ptr;
          switch (c)
            {
            case 'i':
            *optset |= PCRE_CASELESS;
            continue;

            case 'm':
            *optset |= PCRE_MULTILINE;
            continue;

            case 's':
            *optset |= PCRE_DOTALL;
            continue;

            case 'x':
            *optset |= PCRE_EXTENDED;
            continue;

            case 'X':
            *optset |= PCRE_EXTRA;
            continue;

            case 'U':
            *optset |= PCRE_UNGREEDY;
            continue;

            case '-':
            optset = &unset;
            continue;

            

            case ')':
            if (item_count == 0)
              {
              options = (options | set) & (~unset);
              set = unset = 0;     
              item_count--;        
              }

            

            

            case ':':
            if (((set|unset) & PCRE_IMS) != 0)
              {
              length += 4;
              branch_newextra = 2;
              if (((set|unset) & PCRE_CASELESS) != 0) options |= PCRE_ICHANGED;
              }
            goto END_OPTIONS;

            

            default:
            *errorptr = ERR12;
            goto PCRE_ERROR_RETURN;
            }
          }

        

        END_OPTIONS:
        if (c == ')')
          {
          if (branch_newextra == 2 &&
              (branch_extra == 0 || branch_extra == 1+LINK_SIZE))
            branch_extra += branch_newextra;
          continue;
          }

        
        }
      }

    

    else if ((options & PCRE_NO_AUTO_CAPTURE) == 0)
      {
      bracount++;
      if (bracount > EXTRACT_BASIC_MAX) bracket_length += 3;
      }

    

    if (brastackptr >= sizeof(brastack)/sizeof(int))
      {
      *errorptr = ERR19;
      goto PCRE_ERROR_RETURN;
      }

    bralenstack[brastackptr] = branch_extra;
    branch_extra = branch_newextra;

    brastack[brastackptr++] = length;
    length += bracket_length;
    continue;

    

    case ')':
    length += 1 + LINK_SIZE;
    if (brastackptr > 0)
      {
      duplength = length - brastack[--brastackptr];
      branch_extra = bralenstack[brastackptr];
      }
    else duplength = 0;

    

    HANDLE_QUANTIFIED_BRACKETS:

    

    if ((c = ptr[1]) == '{' && is_counted_repeat(ptr+2))
      {
      ptr = read_repeat_counts(ptr+2, &min, &max, errorptr);
      if (*errorptr != NULL) goto PCRE_ERROR_RETURN;
      }
    else if (c == '*') { min = 0; max = -1; ptr++; }
    else if (c == '+') { min = 1; max = -1; ptr++; }
    else if (c == '?') { min = 0; max = 1;  ptr++; }
    else { min = 1; max = 1; }

    

    if (min == 0)
      {
      length++;
      if (max > 0) length += (max - 1) * (duplength + 3 + 2*LINK_SIZE);
      }

    

    else
      {
      length += (min - 1) * duplength;
      if (max > min)   
        length += (max - min) * (duplength + 3 + 2*LINK_SIZE)
          - (2 + 2*LINK_SIZE);
      }

    

    if (ptr[1] == '+')
      {
      ptr++;
      length += 2 + 2*LINK_SIZE;
      }
    continue;

    

    default:
    NORMAL_CHAR:

    if (inescq && c == '\\' && ptr[1] == 'E')
      {
      inescq = FALSE;
      ptr++;
      continue;
      }

    length += 2;          
    lastitemlength = 1;   

    

#ifdef SUPPORT_UTF8
    if (utf8 && (c & 0xc0) == 0xc0)
      {
      while ((ptr[1] & 0xc0) == 0x80)         
        {                                     
        lastitemlength++;                     
        length++;
        ptr++;
        }
      }
#endif

    continue;
    }
  }

length += 2 + LINK_SIZE;    

if ((options & PCRE_AUTO_CALLOUT) != 0)
  length += 2 + 2*LINK_SIZE;  

if (length > MAX_PATTERN_SIZE)
  {
  *errorptr = ERR20;
  return NULL;
  }



size = length + sizeof(real_pcre) + name_count * (max_name_size + 3);
re = (real_pcre *)(pcre_malloc)(size);

if (re == NULL)
  {
  *errorptr = ERR21;
  return NULL;
  }



re->magic_number = MAGIC_NUMBER;
re->size = size;
re->options = options;
re->dummy1 = re->dummy2 = 0;
re->name_table_offset = sizeof(real_pcre);
re->name_entry_size = max_name_size + 3;
re->name_count = name_count;
re->tables = (tables == pcre_default_tables)? NULL : tables;
re->nullpad = NULL;



compile_block.names_found = 0;
compile_block.name_entry_size = max_name_size + 3;
compile_block.name_table = (uschar *)re + re->name_table_offset;
codestart = compile_block.name_table + re->name_entry_size * re->name_count;
compile_block.start_code = codestart;
compile_block.start_pattern = (const uschar *)pattern;
compile_block.req_varyopt = 0;
compile_block.nopartial = FALSE;



ptr = (const uschar *)pattern;
code = (uschar *)codestart;
*code = OP_BRA;
bracount = 0;
(void)compile_regex(options, options & PCRE_IMS, &bracount, &code, &ptr,
  errorptr, FALSE, 0, &firstbyte, &reqbyte, NULL, &compile_block);
re->top_bracket = bracount;
re->top_backref = compile_block.top_backref;

if (compile_block.nopartial) re->options |= PCRE_NOPARTIAL;



if (*errorptr == NULL && *ptr != 0) *errorptr = ERR22;



*code++ = OP_END;

#ifndef DEBUG
if (code - codestart > length) *errorptr = ERR23;
#endif



if (re->top_backref > re->top_bracket) *errorptr = ERR15;



if (*errorptr != NULL)
  {
  (pcre_free)(re);
  PCRE_ERROR_RETURN:
  *erroroffset = ptr - (const uschar *)pattern;
  return NULL;
  }



if ((options & PCRE_ANCHORED) == 0)
  {
  int temp_options = options;
  if (is_anchored(codestart, &temp_options, 0, compile_block.backref_map))
    re->options |= PCRE_ANCHORED;
  else
    {
    if (firstbyte < 0)
      firstbyte = find_firstassertedchar(codestart, &temp_options, FALSE);
    if (firstbyte >= 0)   
      {
      int ch = firstbyte & 255;
      re->first_byte = ((firstbyte & REQ_CASELESS) != 0 &&
         compile_block.fcc[ch] == ch)? ch : firstbyte;
      re->options |= PCRE_FIRSTSET;
      }
    else if (is_startline(codestart, 0, compile_block.backref_map))
      re->options |= PCRE_STARTLINE;
    }
  }



if (reqbyte >= 0 &&
     ((re->options & PCRE_ANCHORED) == 0 || (reqbyte & REQ_VARY) != 0))
  {
  int ch = reqbyte & 255;
  re->req_byte = ((reqbyte & REQ_CASELESS) != 0 &&
    compile_block.fcc[ch] == ch)? (reqbyte & ~REQ_CASELESS) : reqbyte;
  re->options |= PCRE_REQCHSET;
  }



#ifdef DEBUG

printf("Length = %d top_bracket = %d top_backref = %d\n",
  length, re->top_bracket, re->top_backref);

if (re->options != 0)
  {
  printf("%s%s%s%s%s%s%s%s%s%s\n",
    ((re->options & PCRE_NOPARTIAL) != 0)? "nopartial " : "",
    ((re->options & PCRE_ANCHORED) != 0)? "anchored " : "",
    ((re->options & PCRE_CASELESS) != 0)? "caseless " : "",
    ((re->options & PCRE_ICHANGED) != 0)? "case state changed " : "",
    ((re->options & PCRE_EXTENDED) != 0)? "extended " : "",
    ((re->options & PCRE_MULTILINE) != 0)? "multiline " : "",
    ((re->options & PCRE_DOTALL) != 0)? "dotall " : "",
    ((re->options & PCRE_DOLLAR_ENDONLY) != 0)? "endonly " : "",
    ((re->options & PCRE_EXTRA) != 0)? "extra " : "",
    ((re->options & PCRE_UNGREEDY) != 0)? "ungreedy " : "");
  }

if ((re->options & PCRE_FIRSTSET) != 0)
  {
  int ch = re->first_byte & 255;
  const char *caseless = ((re->first_byte & REQ_CASELESS) == 0)? "" : " (caseless)";
  if (isprint(ch)) printf("First char = %c%s\n", ch, caseless);
    else printf("First char = \\x%02x%s\n", ch, caseless);
  }

if ((re->options & PCRE_REQCHSET) != 0)
  {
  int ch = re->req_byte & 255;
  const char *caseless = ((re->req_byte & REQ_CASELESS) == 0)? "" : " (caseless)";
  if (isprint(ch)) printf("Req char = %c%s\n", ch, caseless);
    else printf("Req char = \\x%02x%s\n", ch, caseless);
  }

print_internals(re, stdout);



if (code - codestart > length)
  {
  *errorptr = ERR23;
  (pcre_free)(re);
  *erroroffset = ptr - (uschar *)pattern;
  return NULL;
  }
#endif

return (pcre *)re;
}







static BOOL
match_ref(int offset, register const uschar *eptr, int length, match_data *md,
  unsigned long int ims)
{
const uschar *p = md->start_subject + md->offset_vector[offset];

#ifdef DEBUG
if (eptr >= md->end_subject)
  printf("matching subject <null>");
else
  {
  printf("matching subject ");
  pchars(eptr, length, TRUE, md);
  }
printf(" against backref ");
pchars(p, length, FALSE, md);
printf("\n");
#endif



if (length > md->end_subject - eptr) return FALSE;



if ((ims & PCRE_CASELESS) != 0)
  {
  while (length-- > 0)
    if (md->lcc[*p++] != md->lcc[*eptr++]) return FALSE;
  }
else
  { while (length-- > 0) if (*p++ != *eptr++) return FALSE; }

return TRUE;
}


#ifdef SUPPORT_UTF8




static BOOL
match_xclass(int c, const uschar *data)
{
int t;
BOOL negated = (*data & XCL_NOT) != 0;



if (c < 256)
  {
  if ((*data & XCL_MAP) != 0 && (data[1 + c/8] & (1 << (c&7))) != 0)
    return !negated;   
  }



if ((*data++ & XCL_MAP) != 0) data += 32;

while ((t = *data++) != XCL_END)
  {
  int x, y;
  if (t == XCL_SINGLE)
    {
    GETCHARINC(x, data);
    if (c == x) return !negated;
    }
  else if (t == XCL_RANGE)
    {
    GETCHARINC(x, data);
    GETCHARINC(y, data);
    if (c >= x && c <= y) return !negated;
    }

#ifdef SUPPORT_UCP
  else  
    {
    int chartype, othercase;
    int rqdtype = *data++;
    int category = ucp_findchar(c, &chartype, &othercase);
    if (rqdtype >= 128)
      {
      if ((rqdtype - 128 == category) == (t == XCL_PROP)) return !negated;
      }
    else
      {
      if ((rqdtype == chartype) == (t == XCL_PROP)) return !negated;
      }
    }
#endif  
  }

return negated;   
}
#endif







#ifndef NO_RECURSE
#define REGISTER register
#define RMATCH(rx,ra,rb,rc,rd,re,rf,rg) rx = match(ra,rb,rc,rd,re,rf,rg)
#define RRETURN(ra) return ra
#else




#define REGISTER

#define RMATCH(rx,ra,rb,rc,rd,re,rf,rg)\
  {\
  heapframe *newframe = (pcre_stack_malloc)(sizeof(heapframe));\
  if (setjmp(frame->Xwhere) == 0)\
    {\
    newframe->Xeptr = ra;\
    newframe->Xecode = rb;\
    newframe->Xoffset_top = rc;\
    newframe->Xims = re;\
    newframe->Xeptrb = rf;\
    newframe->Xflags = rg;\
    newframe->Xprevframe = frame;\
    frame = newframe;\
    DPRINTF(("restarting from line %d\n", __LINE__));\
    goto HEAP_RECURSE;\
    }\
  else\
    {\
    DPRINTF(("longjumped back to line %d\n", __LINE__));\
    frame = md->thisframe;\
    rx = frame->Xresult;\
    }\
  }

#define RRETURN(ra)\
  {\
  heapframe *newframe = frame;\
  frame = newframe->Xprevframe;\
  (pcre_stack_free)(newframe);\
  if (frame != NULL)\
    {\
    frame->Xresult = ra;\
    md->thisframe = frame;\
    longjmp(frame->Xwhere, 1);\
    }\
  return ra;\
  }




typedef struct heapframe {
  struct heapframe *Xprevframe;

  

  const uschar *Xeptr;
  const uschar *Xecode;
  int Xoffset_top;
  long int Xims;
  eptrblock *Xeptrb;
  int Xflags;

  

  const uschar *Xcallpat;
  const uschar *Xcharptr;
  const uschar *Xdata;
  const uschar *Xnext;
  const uschar *Xpp;
  const uschar *Xprev;
  const uschar *Xsaved_eptr;

  recursion_info Xnew_recursive;

  BOOL Xcur_is_word;
  BOOL Xcondition;
  BOOL Xminimize;
  BOOL Xprev_is_word;

  unsigned long int Xoriginal_ims;

#ifdef SUPPORT_UCP
  int Xprop_type;
  int Xprop_fail_result;
  int Xprop_category;
  int Xprop_chartype;
  int Xprop_othercase;
  int Xprop_test_against;
  int *Xprop_test_variable;
#endif

  int Xctype;
  int Xfc;
  int Xfi;
  int Xlength;
  int Xmax;
  int Xmin;
  int Xnumber;
  int Xoffset;
  int Xop;
  int Xsave_capture_last;
  int Xsave_offset1, Xsave_offset2, Xsave_offset3;
  int Xstacksave[REC_STACK_SAVE_MAX];

  eptrblock Xnewptrb;

  

  int  Xresult;
  jmp_buf Xwhere;

} heapframe;

#endif










static int
match(REGISTER const uschar *eptr, REGISTER const uschar *ecode,
  int offset_top, match_data *md, unsigned long int ims, eptrblock *eptrb,
  int flags)
{


register int rrc;    
register int i;      
register int c;      



#ifdef NO_RECURSE
heapframe *frame = (pcre_stack_malloc)(sizeof(heapframe));
frame->Xprevframe = NULL;            



frame->Xeptr = eptr;
frame->Xecode = ecode;
frame->Xoffset_top = offset_top;
frame->Xims = ims;
frame->Xeptrb = eptrb;
frame->Xflags = flags;



HEAP_RECURSE:



#define eptr               frame->Xeptr
#define ecode              frame->Xecode
#define offset_top         frame->Xoffset_top
#define ims                frame->Xims
#define eptrb              frame->Xeptrb
#define flags              frame->Xflags



#ifdef SUPPORT_UTF8
#define charptr            frame->Xcharptr
#endif
#define callpat            frame->Xcallpat
#define data               frame->Xdata
#define next               frame->Xnext
#define pp                 frame->Xpp
#define prev               frame->Xprev
#define saved_eptr         frame->Xsaved_eptr

#define new_recursive      frame->Xnew_recursive

#define cur_is_word        frame->Xcur_is_word
#define condition          frame->Xcondition
#define minimize           frame->Xminimize
#define prev_is_word       frame->Xprev_is_word

#define original_ims       frame->Xoriginal_ims

#ifdef SUPPORT_UCP
#define prop_type          frame->Xprop_type
#define prop_fail_result   frame->Xprop_fail_result
#define prop_category      frame->Xprop_category
#define prop_chartype      frame->Xprop_chartype
#define prop_othercase     frame->Xprop_othercase
#define prop_test_against  frame->Xprop_test_against
#define prop_test_variable frame->Xprop_test_variable
#endif

#define ctype              frame->Xctype
#define fc                 frame->Xfc
#define fi                 frame->Xfi
#define length             frame->Xlength
#define max                frame->Xmax
#define min                frame->Xmin
#define number             frame->Xnumber
#define offset             frame->Xoffset
#define op                 frame->Xop
#define save_capture_last  frame->Xsave_capture_last
#define save_offset1       frame->Xsave_offset1
#define save_offset2       frame->Xsave_offset2
#define save_offset3       frame->Xsave_offset3
#define stacksave          frame->Xstacksave

#define newptrb            frame->Xnewptrb



#else
#define fi i
#define fc c


#ifdef SUPPORT_UTF8                
const uschar *charptr;             
#endif                             
const uschar *callpat;             
const uschar *data;                
const uschar *next;                
const uschar *pp;                  
const uschar *prev;                
const uschar *saved_eptr;          
                                   
recursion_info new_recursive;      
                                   
BOOL cur_is_word;                  
BOOL condition;                    
BOOL minimize;
BOOL prev_is_word;

unsigned long int original_ims;

#ifdef SUPPORT_UCP
int prop_type;
int prop_fail_result;
int prop_category;
int prop_chartype;
int prop_othercase;
int prop_test_against;
int *prop_test_variable;
#endif

int ctype;
int length;
int max;
int min;
int number;
int offset;
int op;
int save_capture_last;
int save_offset1, save_offset2, save_offset3;
int stacksave[REC_STACK_SAVE_MAX];

eptrblock newptrb;
#endif



#ifdef SUPPORT_UCP
prop_fail_result = 0;
prop_test_against = 0;
prop_test_variable = NULL;
#endif



if (md->match_call_count++ >= md->match_limit) RRETURN(PCRE_ERROR_MATCHLIMIT);

original_ims = ims;    



if ((flags & match_isgroup) != 0)
  {
  newptrb.epb_prev = eptrb;
  newptrb.epb_saved_eptr = eptr;
  eptrb = &newptrb;
  }



for (;;)
  {
  op = *ecode;
  minimize = FALSE;

  

  if (md->partial &&
      eptr >= md->end_subject &&
      eptr > md->start_match)
    md->hitend = TRUE;

  

  if (op > OP_BRA)
    {
    number = op - OP_BRA;

    

    if (number > EXTRACT_BASIC_MAX)
      number = GET2(ecode, 2+LINK_SIZE);
    offset = number << 1;

#ifdef DEBUG
    printf("start bracket %d subject=", number);
    pchars(eptr, 16, TRUE, md);
    printf("\n");
#endif

    if (offset < md->offset_max)
      {
      save_offset1 = md->offset_vector[offset];
      save_offset2 = md->offset_vector[offset+1];
      save_offset3 = md->offset_vector[md->offset_end - number];
      save_capture_last = md->capture_last;

      DPRINTF(("saving %d %d %d\n", save_offset1, save_offset2, save_offset3));
      md->offset_vector[md->offset_end - number] = eptr - md->start_subject;

      do
        {
        RMATCH(rrc, eptr, ecode + 1 + LINK_SIZE, offset_top, md, ims, eptrb,
          match_isgroup);
        if (rrc != MATCH_NOMATCH) RRETURN(rrc);
        md->capture_last = save_capture_last;
        ecode += GET(ecode, 1);
        }
      while (*ecode == OP_ALT);

      DPRINTF(("bracket %d failed\n", number));

      md->offset_vector[offset] = save_offset1;
      md->offset_vector[offset+1] = save_offset2;
      md->offset_vector[md->offset_end - number] = save_offset3;

      RRETURN(MATCH_NOMATCH);
      }

    

    else op = OP_BRA;
    }

  

  switch(op)
    {
    case OP_BRA:     
    DPRINTF(("start bracket 0\n"));
    do
      {
      RMATCH(rrc, eptr, ecode + 1 + LINK_SIZE, offset_top, md, ims, eptrb,
        match_isgroup);
      if (rrc != MATCH_NOMATCH) RRETURN(rrc);
      ecode += GET(ecode, 1);
      }
    while (*ecode == OP_ALT);
    DPRINTF(("bracket 0 failed\n"));
    RRETURN(MATCH_NOMATCH);

    

    case OP_COND:
    if (ecode[LINK_SIZE+1] == OP_CREF) 
      {
      offset = GET2(ecode, LINK_SIZE+2) << 1;  
      condition = (offset == CREF_RECURSE * 2)?
        (md->recursive != NULL) :
        (offset < offset_top && md->offset_vector[offset] >= 0);
      RMATCH(rrc, eptr, ecode + (condition?
        (LINK_SIZE + 4) : (LINK_SIZE + 1 + GET(ecode, 1))),
        offset_top, md, ims, eptrb, match_isgroup);
      RRETURN(rrc);
      }

    

    else
      {
      RMATCH(rrc, eptr, ecode + 1 + LINK_SIZE, offset_top, md, ims, NULL,
          match_condassert | match_isgroup);
      if (rrc == MATCH_MATCH)
        {
        ecode += 1 + LINK_SIZE + GET(ecode, LINK_SIZE+2);
        while (*ecode == OP_ALT) ecode += GET(ecode, 1);
        }
      else if (rrc != MATCH_NOMATCH)
        {
        RRETURN(rrc);         
        }
      else ecode += GET(ecode, 1);
      RMATCH(rrc, eptr, ecode + 1 + LINK_SIZE, offset_top, md, ims, eptrb,
        match_isgroup);
      RRETURN(rrc);
      }
    

    

    case OP_CREF:
    case OP_BRANUMBER:
    ecode += 3;
    break;

    

    case OP_END:
    if (md->recursive != NULL && md->recursive->group_num == 0)
      {
      recursion_info *rec = md->recursive;
      DPRINTF(("Hit the end in a (?0) recursion\n"));
      md->recursive = rec->prevrec;
      memmove(md->offset_vector, rec->offset_save,
        rec->saved_max * sizeof(int));
      md->start_match = rec->save_start;
      ims = original_ims;
      ecode = rec->after_call;
      break;
      }

    

    if (md->notempty && eptr == md->start_match) RRETURN(MATCH_NOMATCH);
    md->end_match_ptr = eptr;          
    md->end_offset_top = offset_top;   
    RRETURN(MATCH_MATCH);

    

    case OP_OPT:
    ims = ecode[1];
    ecode += 2;
    DPRINTF(("ims set to %02lx\n", ims));
    break;

    

    case OP_ASSERT:
    case OP_ASSERTBACK:
    do
      {
      RMATCH(rrc, eptr, ecode + 1 + LINK_SIZE, offset_top, md, ims, NULL,
        match_isgroup);
      if (rrc == MATCH_MATCH) break;
      if (rrc != MATCH_NOMATCH) RRETURN(rrc);
      ecode += GET(ecode, 1);
      }
    while (*ecode == OP_ALT);
    if (*ecode == OP_KET) RRETURN(MATCH_NOMATCH);

    

    if ((flags & match_condassert) != 0) RRETURN(MATCH_MATCH);

    

    do ecode += GET(ecode,1); while (*ecode == OP_ALT);
    ecode += 1 + LINK_SIZE;
    offset_top = md->end_offset_top;
    continue;

    

    case OP_ASSERT_NOT:
    case OP_ASSERTBACK_NOT:
    do
      {
      RMATCH(rrc, eptr, ecode + 1 + LINK_SIZE, offset_top, md, ims, NULL,
        match_isgroup);
      if (rrc == MATCH_MATCH) RRETURN(MATCH_NOMATCH);
      if (rrc != MATCH_NOMATCH) RRETURN(rrc);
      ecode += GET(ecode,1);
      }
    while (*ecode == OP_ALT);

    if ((flags & match_condassert) != 0) RRETURN(MATCH_MATCH);

    ecode += 1 + LINK_SIZE;
    continue;

    

    case OP_REVERSE:
#ifdef SUPPORT_UTF8
    if (md->utf8)
      {
      c = GET(ecode,1);
      for (i = 0; i < c; i++)
        {
        eptr--;
        if (eptr < md->start_subject) RRETURN(MATCH_NOMATCH);
        BACKCHAR(eptr)
        }
      }
    else
#endif

    

      {
      eptr -= GET(ecode,1);
      if (eptr < md->start_subject) RRETURN(MATCH_NOMATCH);
      }

    

    ecode += 1 + LINK_SIZE;
    break;

    

    case OP_CALLOUT:
    if (pcre_callout != NULL)
      {
      pcre_callout_block cb;
      cb.version          = 1;   
      cb.callout_number   = ecode[1];
      cb.offset_vector    = md->offset_vector;
      cb.subject          = (const char *)md->start_subject;
      cb.subject_length   = md->end_subject - md->start_subject;
      cb.start_match      = md->start_match - md->start_subject;
      cb.current_position = eptr - md->start_subject;
      cb.pattern_position = GET(ecode, 2);
      cb.next_item_length = GET(ecode, 2 + LINK_SIZE);
      cb.capture_top      = offset_top/2;
      cb.capture_last     = md->capture_last;
      cb.callout_data     = md->callout_data;
      if ((rrc = (*pcre_callout)(&cb)) > 0) RRETURN(MATCH_NOMATCH);
      if (rrc < 0) RRETURN(rrc);
      }
    ecode += 2 + 2*LINK_SIZE;
    break;

    

    case OP_RECURSE:
      {
      callpat = md->start_code + GET(ecode, 1);
      new_recursive.group_num = *callpat - OP_BRA;

      

      if (new_recursive.group_num > EXTRACT_BASIC_MAX)
        new_recursive.group_num = GET2(callpat, 2+LINK_SIZE);

      

      new_recursive.prevrec = md->recursive;
      md->recursive = &new_recursive;

      

      ecode += 1 + LINK_SIZE;
      new_recursive.after_call = ecode;

      

      new_recursive.saved_max = md->offset_end;
      if (new_recursive.saved_max <= REC_STACK_SAVE_MAX)
        new_recursive.offset_save = stacksave;
      else
        {
        new_recursive.offset_save =
          (int *)(pcre_malloc)(new_recursive.saved_max * sizeof(int));
        if (new_recursive.offset_save == NULL) RRETURN(PCRE_ERROR_NOMEMORY);
        }

      memcpy(new_recursive.offset_save, md->offset_vector,
            new_recursive.saved_max * sizeof(int));
      new_recursive.save_start = md->start_match;
      md->start_match = eptr;

      

      DPRINTF(("Recursing into group %d\n", new_recursive.group_num));
      do
        {
        RMATCH(rrc, eptr, callpat + 1 + LINK_SIZE, offset_top, md, ims,
            eptrb, match_isgroup);
        if (rrc == MATCH_MATCH)
          {
          md->recursive = new_recursive.prevrec;
          if (new_recursive.offset_save != stacksave)
            (pcre_free)(new_recursive.offset_save);
          RRETURN(MATCH_MATCH);
          }
        else if (rrc != MATCH_NOMATCH) RRETURN(rrc);

        md->recursive = &new_recursive;
        memcpy(md->offset_vector, new_recursive.offset_save,
            new_recursive.saved_max * sizeof(int));
        callpat += GET(callpat, 1);
        }
      while (*callpat == OP_ALT);

      DPRINTF(("Recursion didn't match\n"));
      md->recursive = new_recursive.prevrec;
      if (new_recursive.offset_save != stacksave)
        (pcre_free)(new_recursive.offset_save);
      RRETURN(MATCH_NOMATCH);
      }
    

    

    case OP_ONCE:
      {
      prev = ecode;
      saved_eptr = eptr;

      do
        {
        RMATCH(rrc, eptr, ecode + 1 + LINK_SIZE, offset_top, md, ims,
          eptrb, match_isgroup);
        if (rrc == MATCH_MATCH) break;
        if (rrc != MATCH_NOMATCH) RRETURN(rrc);
        ecode += GET(ecode,1);
        }
      while (*ecode == OP_ALT);

      

      if (*ecode != OP_ONCE && *ecode != OP_ALT) RRETURN(MATCH_NOMATCH);

      

      do ecode += GET(ecode,1); while (*ecode == OP_ALT);

      offset_top = md->end_offset_top;
      eptr = md->end_match_ptr;

      

      if (*ecode == OP_KET || eptr == saved_eptr)
        {
        ecode += 1+LINK_SIZE;
        break;
        }

      

      if (ecode[1+LINK_SIZE] == OP_OPT)
        {
        ims = (ims & ~PCRE_IMS) | ecode[4];
        DPRINTF(("ims set to %02lx at group repeat\n", ims));
        }

      if (*ecode == OP_KETRMIN)
        {
        RMATCH(rrc, eptr, ecode + 1 + LINK_SIZE, offset_top, md, ims, eptrb, 0);
        if (rrc != MATCH_NOMATCH) RRETURN(rrc);
        RMATCH(rrc, eptr, prev, offset_top, md, ims, eptrb, match_isgroup);
        if (rrc != MATCH_NOMATCH) RRETURN(rrc);
        }
      else  
        {
        RMATCH(rrc, eptr, prev, offset_top, md, ims, eptrb, match_isgroup);
        if (rrc != MATCH_NOMATCH) RRETURN(rrc);
        RMATCH(rrc, eptr, ecode + 1+LINK_SIZE, offset_top, md, ims, eptrb, 0);
        if (rrc != MATCH_NOMATCH) RRETURN(rrc);
        }
      }
    RRETURN(MATCH_NOMATCH);

    

    case OP_ALT:
    do ecode += GET(ecode,1); while (*ecode == OP_ALT);
    break;

    

    case OP_BRAZERO:
      {
      next = ecode+1;
      RMATCH(rrc, eptr, next, offset_top, md, ims, eptrb, match_isgroup);
      if (rrc != MATCH_NOMATCH) RRETURN(rrc);
      do next += GET(next,1); while (*next == OP_ALT);
      ecode = next + 1+LINK_SIZE;
      }
    break;

    case OP_BRAMINZERO:
      {
      next = ecode+1;
      do next += GET(next,1); while (*next == OP_ALT);
      RMATCH(rrc, eptr, next + 1+LINK_SIZE, offset_top, md, ims, eptrb,
        match_isgroup);
      if (rrc != MATCH_NOMATCH) RRETURN(rrc);
      ecode++;
      }
    break;

    

    case OP_KET:
    case OP_KETRMIN:
    case OP_KETRMAX:
      {
      prev = ecode - GET(ecode, 1);
      saved_eptr = eptrb->epb_saved_eptr;

      

      eptrb = eptrb->epb_prev;

      if (*prev == OP_ASSERT || *prev == OP_ASSERT_NOT ||
          *prev == OP_ASSERTBACK || *prev == OP_ASSERTBACK_NOT ||
          *prev == OP_ONCE)
        {
        md->end_match_ptr = eptr;      
        md->end_offset_top = offset_top;
        RRETURN(MATCH_MATCH);
        }

      

      if (*prev != OP_COND)
        {
        number = *prev - OP_BRA;

        

        if (number > EXTRACT_BASIC_MAX) number = GET2(prev, 2+LINK_SIZE);
        offset = number << 1;

#ifdef DEBUG
        printf("end bracket %d", number);
        printf("\n");
#endif

        

        if (number > 0)
          {
          md->capture_last = number;
          if (offset >= md->offset_max) md->offset_overflow = TRUE; else
            {
            md->offset_vector[offset] =
              md->offset_vector[md->offset_end - number];
            md->offset_vector[offset+1] = eptr - md->start_subject;
            if (offset_top <= offset) offset_top = offset + 2;
            }

          

          if (md->recursive != NULL && md->recursive->group_num == number)
            {
            recursion_info *rec = md->recursive;
            DPRINTF(("Recursion (%d) succeeded - continuing\n", number));
            md->recursive = rec->prevrec;
            md->start_match = rec->save_start;
            memcpy(md->offset_vector, rec->offset_save,
              rec->saved_max * sizeof(int));
            ecode = rec->after_call;
            ims = original_ims;
            break;
            }
          }
        }

      

      ims = original_ims;
      DPRINTF(("ims reset to %02lx\n", ims));

      

      if (*ecode == OP_KET || eptr == saved_eptr)
        {
        ecode += 1 + LINK_SIZE;
        break;
        }

      

      if (*ecode == OP_KETRMIN)
        {
        RMATCH(rrc, eptr, ecode + 1+LINK_SIZE, offset_top, md, ims, eptrb, 0);
        if (rrc != MATCH_NOMATCH) RRETURN(rrc);
        RMATCH(rrc, eptr, prev, offset_top, md, ims, eptrb, match_isgroup);
        if (rrc != MATCH_NOMATCH) RRETURN(rrc);
        }
      else  
        {
        RMATCH(rrc, eptr, prev, offset_top, md, ims, eptrb, match_isgroup);
        if (rrc != MATCH_NOMATCH) RRETURN(rrc);
        RMATCH(rrc, eptr, ecode + 1+LINK_SIZE, offset_top, md, ims, eptrb, 0);
        if (rrc != MATCH_NOMATCH) RRETURN(rrc);
        }
      }

    RRETURN(MATCH_NOMATCH);

    

    case OP_CIRC:
    if (md->notbol && eptr == md->start_subject) RRETURN(MATCH_NOMATCH);
    if ((ims & PCRE_MULTILINE) != 0)
      {
      if (eptr != md->start_subject && eptr[-1] != NEWLINE)
        RRETURN(MATCH_NOMATCH);
      ecode++;
      break;
      }
    

    

    case OP_SOD:
    if (eptr != md->start_subject) RRETURN(MATCH_NOMATCH);
    ecode++;
    break;

    

    case OP_SOM:
    if (eptr != md->start_subject + md->start_offset) RRETURN(MATCH_NOMATCH);
    ecode++;
    break;

    

    case OP_DOLL:
    if ((ims & PCRE_MULTILINE) != 0)
      {
      if (eptr < md->end_subject)
        { if (*eptr != NEWLINE) RRETURN(MATCH_NOMATCH); }
      else
        { if (md->noteol) RRETURN(MATCH_NOMATCH); }
      ecode++;
      break;
      }
    else
      {
      if (md->noteol) RRETURN(MATCH_NOMATCH);
      if (!md->endonly)
        {
        if (eptr < md->end_subject - 1 ||
           (eptr == md->end_subject - 1 && *eptr != NEWLINE))
          RRETURN(MATCH_NOMATCH);
        ecode++;
        break;
        }
      }
    

    

    case OP_EOD:
    if (eptr < md->end_subject) RRETURN(MATCH_NOMATCH);
    ecode++;
    break;

    

    case OP_EODN:
    if (eptr < md->end_subject - 1 ||
       (eptr == md->end_subject - 1 && *eptr != NEWLINE)) RRETURN(MATCH_NOMATCH);
    ecode++;
    break;

    

    case OP_NOT_WORD_BOUNDARY:
    case OP_WORD_BOUNDARY:
      {

      

#ifdef SUPPORT_UTF8
      if (md->utf8)
        {
        if (eptr == md->start_subject) prev_is_word = FALSE; else
          {
          const uschar *lastptr = eptr - 1;
          while((*lastptr & 0xc0) == 0x80) lastptr--;
          GETCHAR(c, lastptr);
          prev_is_word = c < 256 && (md->ctypes[c] & ctype_word) != 0;
          }
        if (eptr >= md->end_subject) cur_is_word = FALSE; else
          {
          GETCHAR(c, eptr);
          cur_is_word = c < 256 && (md->ctypes[c] & ctype_word) != 0;
          }
        }
      else
#endif

      

        {
        prev_is_word = (eptr != md->start_subject) &&
          ((md->ctypes[eptr[-1]] & ctype_word) != 0);
        cur_is_word = (eptr < md->end_subject) &&
          ((md->ctypes[*eptr] & ctype_word) != 0);
        }

      

      if ((*ecode++ == OP_WORD_BOUNDARY)?
           cur_is_word == prev_is_word : cur_is_word != prev_is_word)
        RRETURN(MATCH_NOMATCH);
      }
    break;

    

    case OP_ANY:
    if ((ims & PCRE_DOTALL) == 0 && eptr < md->end_subject && *eptr == NEWLINE)
      RRETURN(MATCH_NOMATCH);
    if (eptr++ >= md->end_subject) RRETURN(MATCH_NOMATCH);
#ifdef SUPPORT_UTF8
    if (md->utf8)
      while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
#endif
    ecode++;
    break;

    

    case OP_ANYBYTE:
    if (eptr++ >= md->end_subject) RRETURN(MATCH_NOMATCH);
    ecode++;
    break;

    case OP_NOT_DIGIT:
    if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
    GETCHARINCTEST(c, eptr);
    if (
#ifdef SUPPORT_UTF8
       c < 256 &&
#endif
       (md->ctypes[c] & ctype_digit) != 0
       )
      RRETURN(MATCH_NOMATCH);
    ecode++;
    break;

    case OP_DIGIT:
    if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
    GETCHARINCTEST(c, eptr);
    if (
#ifdef SUPPORT_UTF8
       c >= 256 ||
#endif
       (md->ctypes[c] & ctype_digit) == 0
       )
      RRETURN(MATCH_NOMATCH);
    ecode++;
    break;

    case OP_NOT_WHITESPACE:
    if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
    GETCHARINCTEST(c, eptr);
    if (
#ifdef SUPPORT_UTF8
       c < 256 &&
#endif
       (md->ctypes[c] & ctype_space) != 0
       )
      RRETURN(MATCH_NOMATCH);
    ecode++;
    break;

    case OP_WHITESPACE:
    if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
    GETCHARINCTEST(c, eptr);
    if (
#ifdef SUPPORT_UTF8
       c >= 256 ||
#endif
       (md->ctypes[c] & ctype_space) == 0
       )
      RRETURN(MATCH_NOMATCH);
    ecode++;
    break;

    case OP_NOT_WORDCHAR:
    if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
    GETCHARINCTEST(c, eptr);
    if (
#ifdef SUPPORT_UTF8
       c < 256 &&
#endif
       (md->ctypes[c] & ctype_word) != 0
       )
      RRETURN(MATCH_NOMATCH);
    ecode++;
    break;

    case OP_WORDCHAR:
    if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
    GETCHARINCTEST(c, eptr);
    if (
#ifdef SUPPORT_UTF8
       c >= 256 ||
#endif
       (md->ctypes[c] & ctype_word) == 0
       )
      RRETURN(MATCH_NOMATCH);
    ecode++;
    break;

#ifdef SUPPORT_UCP
    

    case OP_PROP:
    case OP_NOTPROP:
    if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
    GETCHARINCTEST(c, eptr);
      {
      int chartype, rqdtype;
      int othercase;
      int category = ucp_findchar(c, &chartype, &othercase);

      rqdtype = *(++ecode);
      ecode++;

      if (rqdtype >= 128)
        {
        if ((rqdtype - 128 != category) == (op == OP_PROP))
          RRETURN(MATCH_NOMATCH);
        }
      else
        {
        if ((rqdtype != chartype) == (op == OP_PROP))
          RRETURN(MATCH_NOMATCH);
        }
      }
    break;

    

    case OP_EXTUNI:
    if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
    GETCHARINCTEST(c, eptr);
      {
      int chartype;
      int othercase;
      int category = ucp_findchar(c, &chartype, &othercase);
      if (category == ucp_M) RRETURN(MATCH_NOMATCH);
      while (eptr < md->end_subject)
        {
        int len = 1;
        if (!md->utf8) c = *eptr; else
          {
          GETCHARLEN(c, eptr, len);
          }
        category = ucp_findchar(c, &chartype, &othercase);
        if (category != ucp_M) break;
        eptr += len;
        }
      }
    ecode++;
    break;
#endif


    

    case OP_REF:
      {
      offset = GET2(ecode, 1) << 1;               
      ecode += 3;                                 

      

      length = (offset >= offset_top || md->offset_vector[offset] < 0)?
        md->end_subject - eptr + 1 :
        md->offset_vector[offset+1] - md->offset_vector[offset];

      

      switch (*ecode)
        {
        case OP_CRSTAR:
        case OP_CRMINSTAR:
        case OP_CRPLUS:
        case OP_CRMINPLUS:
        case OP_CRQUERY:
        case OP_CRMINQUERY:
        c = *ecode++ - OP_CRSTAR;
        minimize = (c & 1) != 0;
        min = rep_min[c];                 
        max = rep_max[c];                 
        if (max == 0) max = INT_MAX;
        break;

        case OP_CRRANGE:
        case OP_CRMINRANGE:
        minimize = (*ecode == OP_CRMINRANGE);
        min = GET2(ecode, 1);
        max = GET2(ecode, 3);
        if (max == 0) max = INT_MAX;
        ecode += 5;
        break;

        default:               
        if (!match_ref(offset, eptr, length, md, ims)) RRETURN(MATCH_NOMATCH);
        eptr += length;
        continue;              
        }

      

      if (length == 0) continue;

      

      for (i = 1; i <= min; i++)
        {
        if (!match_ref(offset, eptr, length, md, ims)) RRETURN(MATCH_NOMATCH);
        eptr += length;
        }

      

      if (min == max) continue;

      

      if (minimize)
        {
        for (fi = min;; fi++)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (fi >= max || !match_ref(offset, eptr, length, md, ims))
            RRETURN(MATCH_NOMATCH);
          eptr += length;
          }
        
        }

      

      else
        {
        pp = eptr;
        for (i = min; i < max; i++)
          {
          if (!match_ref(offset, eptr, length, md, ims)) break;
          eptr += length;
          }
        while (eptr >= pp)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          eptr -= length;
          }
        RRETURN(MATCH_NOMATCH);
        }
      }
    



    

    case OP_NCLASS:
    case OP_CLASS:
      {
      data = ecode + 1;                
      ecode += 33;                     

      switch (*ecode)
        {
        case OP_CRSTAR:
        case OP_CRMINSTAR:
        case OP_CRPLUS:
        case OP_CRMINPLUS:
        case OP_CRQUERY:
        case OP_CRMINQUERY:
        c = *ecode++ - OP_CRSTAR;
        minimize = (c & 1) != 0;
        min = rep_min[c];                 
        max = rep_max[c];                 
        if (max == 0) max = INT_MAX;
        break;

        case OP_CRRANGE:
        case OP_CRMINRANGE:
        minimize = (*ecode == OP_CRMINRANGE);
        min = GET2(ecode, 1);
        max = GET2(ecode, 3);
        if (max == 0) max = INT_MAX;
        ecode += 5;
        break;

        default:               
        min = max = 1;
        break;
        }

      

#ifdef SUPPORT_UTF8
      
      if (md->utf8)
        {
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
          GETCHARINC(c, eptr);
          if (c > 255)
            {
            if (op == OP_CLASS) RRETURN(MATCH_NOMATCH);
            }
          else
            {
            if ((data[c/8] & (1 << (c&7))) == 0) RRETURN(MATCH_NOMATCH);
            }
          }
        }
      else
#endif
      
        {
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
          c = *eptr++;
          if ((data[c/8] & (1 << (c&7))) == 0) RRETURN(MATCH_NOMATCH);
          }
        }

      

      if (min == max) continue;

      

      if (minimize)
        {
#ifdef SUPPORT_UTF8
        
        if (md->utf8)
          {
          for (fi = min;; fi++)
            {
            RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max || eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
            GETCHARINC(c, eptr);
            if (c > 255)
              {
              if (op == OP_CLASS) RRETURN(MATCH_NOMATCH);
              }
            else
              {
              if ((data[c/8] & (1 << (c&7))) == 0) RRETURN(MATCH_NOMATCH);
              }
            }
          }
        else
#endif
        
          {
          for (fi = min;; fi++)
            {
            RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max || eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
            c = *eptr++;
            if ((data[c/8] & (1 << (c&7))) == 0) RRETURN(MATCH_NOMATCH);
            }
          }
        
        }

      

      else
        {
        pp = eptr;

#ifdef SUPPORT_UTF8
        
        if (md->utf8)
          {
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (c > 255)
              {
              if (op == OP_CLASS) break;
              }
            else
              {
              if ((data[c/8] & (1 << (c&7))) == 0) break;
              }
            eptr += len;
            }
          for (;;)
            {
            RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (eptr-- == pp) break;        
            BACKCHAR(eptr);
            }
          }
        else
#endif
          
          {
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject) break;
            c = *eptr;
            if ((data[c/8] & (1 << (c&7))) == 0) break;
            eptr++;
            }
          while (eptr >= pp)
            {
            RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
            eptr--;
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            }
          }

        RRETURN(MATCH_NOMATCH);
        }
      }
    


    

#ifdef SUPPORT_UTF8
    case OP_XCLASS:
      {
      data = ecode + 1 + LINK_SIZE;                
      ecode += GET(ecode, 1);                      

      switch (*ecode)
        {
        case OP_CRSTAR:
        case OP_CRMINSTAR:
        case OP_CRPLUS:
        case OP_CRMINPLUS:
        case OP_CRQUERY:
        case OP_CRMINQUERY:
        c = *ecode++ - OP_CRSTAR;
        minimize = (c & 1) != 0;
        min = rep_min[c];                 
        max = rep_max[c];                 
        if (max == 0) max = INT_MAX;
        break;

        case OP_CRRANGE:
        case OP_CRMINRANGE:
        minimize = (*ecode == OP_CRMINRANGE);
        min = GET2(ecode, 1);
        max = GET2(ecode, 3);
        if (max == 0) max = INT_MAX;
        ecode += 5;
        break;

        default:               
        min = max = 1;
        break;
        }

      

      for (i = 1; i <= min; i++)
        {
        if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
        GETCHARINC(c, eptr);
        if (!match_xclass(c, data)) RRETURN(MATCH_NOMATCH);
        }

      

      if (min == max) continue;

      

      if (minimize)
        {
        for (fi = min;; fi++)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (fi >= max || eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
          GETCHARINC(c, eptr);
          if (!match_xclass(c, data)) RRETURN(MATCH_NOMATCH);
          }
        
        }

      

      else
        {
        pp = eptr;
        for (i = min; i < max; i++)
          {
          int len = 1;
          if (eptr >= md->end_subject) break;
          GETCHARLEN(c, eptr, len);
          if (!match_xclass(c, data)) break;
          eptr += len;
          }
        for(;;)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (eptr-- == pp) break;        
          BACKCHAR(eptr)
          }
        RRETURN(MATCH_NOMATCH);
        }

      
      }
#endif    

    

    case OP_CHAR:
#ifdef SUPPORT_UTF8
    if (md->utf8)
      {
      length = 1;
      ecode++;
      GETCHARLEN(fc, ecode, length);
      if (length > md->end_subject - eptr) RRETURN(MATCH_NOMATCH);
      while (length-- > 0) if (*ecode++ != *eptr++) RRETURN(MATCH_NOMATCH);
      }
    else
#endif

    
      {
      if (md->end_subject - eptr < 1) RRETURN(MATCH_NOMATCH);
      if (ecode[1] != *eptr++) RRETURN(MATCH_NOMATCH);
      ecode += 2;
      }
    break;

    

    case OP_CHARNC:
#ifdef SUPPORT_UTF8
    if (md->utf8)
      {
      length = 1;
      ecode++;
      GETCHARLEN(fc, ecode, length);

      if (length > md->end_subject - eptr) RRETURN(MATCH_NOMATCH);

      

      if (fc < 128)
        {
        if (md->lcc[*ecode++] != md->lcc[*eptr++]) RRETURN(MATCH_NOMATCH);
        }

      

      else
        {
        int dc;
        GETCHARINC(dc, eptr);
        ecode += length;

        

        if (fc != dc)
          {
#ifdef SUPPORT_UCP
          int chartype;
          int othercase;
          if (ucp_findchar(fc, &chartype, &othercase) < 0 || dc != othercase)
#endif
            RRETURN(MATCH_NOMATCH);
          }
        }
      }
    else
#endif   

    
      {
      if (md->end_subject - eptr < 1) RRETURN(MATCH_NOMATCH);
      if (md->lcc[ecode[1]] != md->lcc[*eptr++]) RRETURN(MATCH_NOMATCH);
      ecode += 2;
      }
    break;

    

    case OP_EXACT:
    min = max = GET2(ecode, 1);
    ecode += 3;
    goto REPEATCHAR;

    case OP_UPTO:
    case OP_MINUPTO:
    min = 0;
    max = GET2(ecode, 1);
    minimize = *ecode == OP_MINUPTO;
    ecode += 3;
    goto REPEATCHAR;

    case OP_STAR:
    case OP_MINSTAR:
    case OP_PLUS:
    case OP_MINPLUS:
    case OP_QUERY:
    case OP_MINQUERY:
    c = *ecode++ - OP_STAR;
    minimize = (c & 1) != 0;
    min = rep_min[c];                 
    max = rep_max[c];                 
    if (max == 0) max = INT_MAX;

    

    REPEATCHAR:
#ifdef SUPPORT_UTF8
    if (md->utf8)
      {
      length = 1;
      charptr = ecode;
      GETCHARLEN(fc, ecode, length);
      if (min * length > md->end_subject - eptr) RRETURN(MATCH_NOMATCH);
      ecode += length;

      

      if (length > 1)
        {
        int oclength = 0;
        uschar occhars[8];

#ifdef SUPPORT_UCP
        int othercase;
        int chartype;
        if ((ims & PCRE_CASELESS) != 0 &&
             ucp_findchar(fc, &chartype, &othercase) >= 0 &&
             othercase > 0)
          oclength = ord2utf8(othercase, occhars);
#endif  

        for (i = 1; i <= min; i++)
          {
          if (memcmp(eptr, charptr, length) == 0) eptr += length;
          
          else if (oclength == 0) { RRETURN(MATCH_NOMATCH); }
          else
            {
            if (memcmp(eptr, occhars, oclength) != 0) RRETURN(MATCH_NOMATCH);
            eptr += oclength;
            }
          }

        if (min == max) continue;

        if (minimize)
          {
          for (fi = min;; fi++)
            {
            RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max || eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
            if (memcmp(eptr, charptr, length) == 0) eptr += length;
            
            else if (oclength == 0) { RRETURN(MATCH_NOMATCH); }
            else
              {
              if (memcmp(eptr, occhars, oclength) != 0) RRETURN(MATCH_NOMATCH);
              eptr += oclength;
              }
            }
          
          }
        else
          {
          pp = eptr;
          for (i = min; i < max; i++)
            {
            if (eptr > md->end_subject - length) break;
            if (memcmp(eptr, charptr, length) == 0) eptr += length;
            else if (oclength == 0) break;
            else
              {
              if (memcmp(eptr, occhars, oclength) != 0) break;
              eptr += oclength;
              }
            }
          while (eptr >= pp)
           {
           RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
           if (rrc != MATCH_NOMATCH) RRETURN(rrc);
           eptr -= length;
           }
          RRETURN(MATCH_NOMATCH);
          }
        
        }

      
      }
    else
#endif  

    
      {
      if (min > md->end_subject - eptr) RRETURN(MATCH_NOMATCH);
      fc = *ecode++;
      }

    

    DPRINTF(("matching %c{%d,%d} against subject %.*s\n", fc, min, max,
      max, eptr));

    if ((ims & PCRE_CASELESS) != 0)
      {
      fc = md->lcc[fc];
      for (i = 1; i <= min; i++)
        if (fc != md->lcc[*eptr++]) RRETURN(MATCH_NOMATCH);
      if (min == max) continue;
      if (minimize)
        {
        for (fi = min;; fi++)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (fi >= max || eptr >= md->end_subject ||
              fc != md->lcc[*eptr++])
            RRETURN(MATCH_NOMATCH);
          }
        
        }
      else
        {
        pp = eptr;
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject || fc != md->lcc[*eptr]) break;
          eptr++;
          }
        while (eptr >= pp)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          eptr--;
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          }
        RRETURN(MATCH_NOMATCH);
        }
      
      }

    

    else
      {
      for (i = 1; i <= min; i++) if (fc != *eptr++) RRETURN(MATCH_NOMATCH);
      if (min == max) continue;
      if (minimize)
        {
        for (fi = min;; fi++)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (fi >= max || eptr >= md->end_subject || fc != *eptr++)
            RRETURN(MATCH_NOMATCH);
          }
        
        }
      else
        {
        pp = eptr;
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject || fc != *eptr) break;
          eptr++;
          }
        while (eptr >= pp)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          eptr--;
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          }
        RRETURN(MATCH_NOMATCH);
        }
      }
    

    

    case OP_NOT:
    if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
    ecode++;
    GETCHARINCTEST(c, eptr);
    if ((ims & PCRE_CASELESS) != 0)
      {
#ifdef SUPPORT_UTF8
      if (c < 256)
#endif
      c = md->lcc[c];
      if (md->lcc[*ecode++] == c) RRETURN(MATCH_NOMATCH);
      }
    else
      {
      if (*ecode++ == c) RRETURN(MATCH_NOMATCH);
      }
    break;

    

    case OP_NOTEXACT:
    min = max = GET2(ecode, 1);
    ecode += 3;
    goto REPEATNOTCHAR;

    case OP_NOTUPTO:
    case OP_NOTMINUPTO:
    min = 0;
    max = GET2(ecode, 1);
    minimize = *ecode == OP_NOTMINUPTO;
    ecode += 3;
    goto REPEATNOTCHAR;

    case OP_NOTSTAR:
    case OP_NOTMINSTAR:
    case OP_NOTPLUS:
    case OP_NOTMINPLUS:
    case OP_NOTQUERY:
    case OP_NOTMINQUERY:
    c = *ecode++ - OP_NOTSTAR;
    minimize = (c & 1) != 0;
    min = rep_min[c];                 
    max = rep_max[c];                 
    if (max == 0) max = INT_MAX;

    

    REPEATNOTCHAR:
    if (min > md->end_subject - eptr) RRETURN(MATCH_NOMATCH);
    fc = *ecode++;

    

    DPRINTF(("negative matching %c{%d,%d} against subject %.*s\n", fc, min, max,
      max, eptr));

    if ((ims & PCRE_CASELESS) != 0)
      {
      fc = md->lcc[fc];

#ifdef SUPPORT_UTF8
      
      if (md->utf8)
        {
        register int d;
        for (i = 1; i <= min; i++)
          {
          GETCHARINC(d, eptr);
          if (d < 256) d = md->lcc[d];
          if (fc == d) RRETURN(MATCH_NOMATCH);
          }
        }
      else
#endif

      
        {
        for (i = 1; i <= min; i++)
          if (fc == md->lcc[*eptr++]) RRETURN(MATCH_NOMATCH);
        }

      if (min == max) continue;

      if (minimize)
        {
#ifdef SUPPORT_UTF8
        
        if (md->utf8)
          {
          register int d;
          for (fi = min;; fi++)
            {
            RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            GETCHARINC(d, eptr);
            if (d < 256) d = md->lcc[d];
            if (fi >= max || eptr >= md->end_subject || fc == d)
              RRETURN(MATCH_NOMATCH);
            }
          }
        else
#endif
        
          {
          for (fi = min;; fi++)
            {
            RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max || eptr >= md->end_subject || fc == md->lcc[*eptr++])
              RRETURN(MATCH_NOMATCH);
            }
          }
        
        }

      

      else
        {
        pp = eptr;

#ifdef SUPPORT_UTF8
        
        if (md->utf8)
          {
          register int d;
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(d, eptr, len);
            if (d < 256) d = md->lcc[d];
            if (fc == d) break;
            eptr += len;
            }
          for(;;)
            {
            RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (eptr-- == pp) break;        
            BACKCHAR(eptr);
            }
          }
        else
#endif
        
          {
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || fc == md->lcc[*eptr]) break;
            eptr++;
            }
          while (eptr >= pp)
            {
            RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            eptr--;
            }
          }

        RRETURN(MATCH_NOMATCH);
        }
      
      }

    

    else
      {
#ifdef SUPPORT_UTF8
      
      if (md->utf8)
        {
        register int d;
        for (i = 1; i <= min; i++)
          {
          GETCHARINC(d, eptr);
          if (fc == d) RRETURN(MATCH_NOMATCH);
          }
        }
      else
#endif
      
        {
        for (i = 1; i <= min; i++)
          if (fc == *eptr++) RRETURN(MATCH_NOMATCH);
        }

      if (min == max) continue;

      if (minimize)
        {
#ifdef SUPPORT_UTF8
        
        if (md->utf8)
          {
          register int d;
          for (fi = min;; fi++)
            {
            RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            GETCHARINC(d, eptr);
            if (fi >= max || eptr >= md->end_subject || fc == d)
              RRETURN(MATCH_NOMATCH);
            }
          }
        else
#endif
        
          {
          for (fi = min;; fi++)
            {
            RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (fi >= max || eptr >= md->end_subject || fc == *eptr++)
              RRETURN(MATCH_NOMATCH);
            }
          }
        
        }

      

      else
        {
        pp = eptr;

#ifdef SUPPORT_UTF8
        
        if (md->utf8)
          {
          register int d;
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(d, eptr, len);
            if (fc == d) break;
            eptr += len;
            }
          for(;;)
            {
            RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            if (eptr-- == pp) break;        
            BACKCHAR(eptr);
            }
          }
        else
#endif
        
          {
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || fc == *eptr) break;
            eptr++;
            }
          while (eptr >= pp)
            {
            RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
            if (rrc != MATCH_NOMATCH) RRETURN(rrc);
            eptr--;
            }
          }

        RRETURN(MATCH_NOMATCH);
        }
      }
    

    

    case OP_TYPEEXACT:
    min = max = GET2(ecode, 1);
    minimize = TRUE;
    ecode += 3;
    goto REPEATTYPE;

    case OP_TYPEUPTO:
    case OP_TYPEMINUPTO:
    min = 0;
    max = GET2(ecode, 1);
    minimize = *ecode == OP_TYPEMINUPTO;
    ecode += 3;
    goto REPEATTYPE;

    case OP_TYPESTAR:
    case OP_TYPEMINSTAR:
    case OP_TYPEPLUS:
    case OP_TYPEMINPLUS:
    case OP_TYPEQUERY:
    case OP_TYPEMINQUERY:
    c = *ecode++ - OP_TYPESTAR;
    minimize = (c & 1) != 0;
    min = rep_min[c];                 
    max = rep_max[c];                 
    if (max == 0) max = INT_MAX;

    

    REPEATTYPE:
    ctype = *ecode++;      

#ifdef SUPPORT_UCP
    if (ctype == OP_PROP || ctype == OP_NOTPROP)
      {
      prop_fail_result = ctype == OP_NOTPROP;
      prop_type = *ecode++;
      if (prop_type >= 128)
        {
        prop_test_against = prop_type - 128;
        prop_test_variable = &prop_category;
        }
      else
        {
        prop_test_against = prop_type;
        prop_test_variable = &prop_chartype;
        }
      }
    else prop_type = -1;
#endif

    

    if (min > md->end_subject - eptr) RRETURN(MATCH_NOMATCH);
    if (min > 0)
      {
#ifdef SUPPORT_UCP
      if (prop_type > 0)
        {
        for (i = 1; i <= min; i++)
          {
          GETCHARINC(c, eptr);
          prop_category = ucp_findchar(c, &prop_chartype, &prop_othercase);
          if ((*prop_test_variable == prop_test_against) == prop_fail_result)
            RRETURN(MATCH_NOMATCH);
          }
        }

      

      else if (ctype == OP_EXTUNI)
        {
        for (i = 1; i <= min; i++)
          {
          GETCHARINCTEST(c, eptr);
          prop_category = ucp_findchar(c, &prop_chartype, &prop_othercase);
          if (prop_category == ucp_M) RRETURN(MATCH_NOMATCH);
          while (eptr < md->end_subject)
            {
            int len = 1;
            if (!md->utf8) c = *eptr; else
              {
              GETCHARLEN(c, eptr, len);
              }
            prop_category = ucp_findchar(c, &prop_chartype, &prop_othercase);
            if (prop_category != ucp_M) break;
            eptr += len;
            }
          }
        }

      else
#endif     



#ifdef SUPPORT_UTF8
      if (md->utf8) switch(ctype)
        {
        case OP_ANY:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject ||
             (*eptr++ == NEWLINE && (ims & PCRE_DOTALL) == 0))
            RRETURN(MATCH_NOMATCH);
          while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
          }
        break;

        case OP_ANYBYTE:
        eptr += min;
        break;

        case OP_NOT_DIGIT:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
          GETCHARINC(c, eptr);
          if (c < 128 && (md->ctypes[c] & ctype_digit) != 0)
            RRETURN(MATCH_NOMATCH);
          }
        break;

        case OP_DIGIT:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject ||
             *eptr >= 128 || (md->ctypes[*eptr++] & ctype_digit) == 0)
            RRETURN(MATCH_NOMATCH);
          
          }
        break;

        case OP_NOT_WHITESPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject ||
             (*eptr < 128 && (md->ctypes[*eptr++] & ctype_space) != 0))
            RRETURN(MATCH_NOMATCH);
          while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
          }
        break;

        case OP_WHITESPACE:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject ||
             *eptr >= 128 || (md->ctypes[*eptr++] & ctype_space) == 0)
            RRETURN(MATCH_NOMATCH);
          
          }
        break;

        case OP_NOT_WORDCHAR:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject ||
             (*eptr < 128 && (md->ctypes[*eptr++] & ctype_word) != 0))
            RRETURN(MATCH_NOMATCH);
          while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
          }
        break;

        case OP_WORDCHAR:
        for (i = 1; i <= min; i++)
          {
          if (eptr >= md->end_subject ||
             *eptr >= 128 || (md->ctypes[*eptr++] & ctype_word) == 0)
            RRETURN(MATCH_NOMATCH);
          
          }
        break;

        default:
        RRETURN(PCRE_ERROR_INTERNAL);
        }  

      else
#endif     

      

      switch(ctype)
        {
        case OP_ANY:
        if ((ims & PCRE_DOTALL) == 0)
          {
          for (i = 1; i <= min; i++)
            if (*eptr++ == NEWLINE) RRETURN(MATCH_NOMATCH);
          }
        else eptr += min;
        break;

        case OP_ANYBYTE:
        eptr += min;
        break;

        case OP_NOT_DIGIT:
        for (i = 1; i <= min; i++)
          if ((md->ctypes[*eptr++] & ctype_digit) != 0) RRETURN(MATCH_NOMATCH);
        break;

        case OP_DIGIT:
        for (i = 1; i <= min; i++)
          if ((md->ctypes[*eptr++] & ctype_digit) == 0) RRETURN(MATCH_NOMATCH);
        break;

        case OP_NOT_WHITESPACE:
        for (i = 1; i <= min; i++)
          if ((md->ctypes[*eptr++] & ctype_space) != 0) RRETURN(MATCH_NOMATCH);
        break;

        case OP_WHITESPACE:
        for (i = 1; i <= min; i++)
          if ((md->ctypes[*eptr++] & ctype_space) == 0) RRETURN(MATCH_NOMATCH);
        break;

        case OP_NOT_WORDCHAR:
        for (i = 1; i <= min; i++)
          if ((md->ctypes[*eptr++] & ctype_word) != 0)
            RRETURN(MATCH_NOMATCH);
        break;

        case OP_WORDCHAR:
        for (i = 1; i <= min; i++)
          if ((md->ctypes[*eptr++] & ctype_word) == 0)
            RRETURN(MATCH_NOMATCH);
        break;

        default:
        RRETURN(PCRE_ERROR_INTERNAL);
        }
      }

    

    if (min == max) continue;

    

    if (minimize)
      {
#ifdef SUPPORT_UCP
      if (prop_type > 0)
        {
        for (fi = min;; fi++)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (fi >= max || eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
          GETCHARINC(c, eptr);
          prop_category = ucp_findchar(c, &prop_chartype, &prop_othercase);
          if ((*prop_test_variable == prop_test_against) == prop_fail_result)
            RRETURN(MATCH_NOMATCH);
          }
        }

      

      else if (ctype == OP_EXTUNI)
        {
        for (fi = min;; fi++)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (fi >= max || eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
          GETCHARINCTEST(c, eptr);
          prop_category = ucp_findchar(c, &prop_chartype, &prop_othercase);
          if (prop_category == ucp_M) RRETURN(MATCH_NOMATCH);
          while (eptr < md->end_subject)
            {
            int len = 1;
            if (!md->utf8) c = *eptr; else
              {
              GETCHARLEN(c, eptr, len);
              }
            prop_category = ucp_findchar(c, &prop_chartype, &prop_othercase);
            if (prop_category != ucp_M) break;
            eptr += len;
            }
          }
        }

      else
#endif     

#ifdef SUPPORT_UTF8
      
      if (md->utf8)
        {
        for (fi = min;; fi++)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (fi >= max || eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);

          GETCHARINC(c, eptr);
          switch(ctype)
            {
            case OP_ANY:
            if ((ims & PCRE_DOTALL) == 0 && c == NEWLINE) RRETURN(MATCH_NOMATCH);
            break;

            case OP_ANYBYTE:
            break;

            case OP_NOT_DIGIT:
            if (c < 256 && (md->ctypes[c] & ctype_digit) != 0)
              RRETURN(MATCH_NOMATCH);
            break;

            case OP_DIGIT:
            if (c >= 256 || (md->ctypes[c] & ctype_digit) == 0)
              RRETURN(MATCH_NOMATCH);
            break;

            case OP_NOT_WHITESPACE:
            if (c < 256 && (md->ctypes[c] & ctype_space) != 0)
              RRETURN(MATCH_NOMATCH);
            break;

            case OP_WHITESPACE:
            if  (c >= 256 || (md->ctypes[c] & ctype_space) == 0)
              RRETURN(MATCH_NOMATCH);
            break;

            case OP_NOT_WORDCHAR:
            if (c < 256 && (md->ctypes[c] & ctype_word) != 0)
              RRETURN(MATCH_NOMATCH);
            break;

            case OP_WORDCHAR:
            if (c >= 256 && (md->ctypes[c] & ctype_word) == 0)
              RRETURN(MATCH_NOMATCH);
            break;

            default:
            RRETURN(PCRE_ERROR_INTERNAL);
            }
          }
        }
      else
#endif
      
        {
        for (fi = min;; fi++)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (fi >= max || eptr >= md->end_subject) RRETURN(MATCH_NOMATCH);
          c = *eptr++;
          switch(ctype)
            {
            case OP_ANY:
            if ((ims & PCRE_DOTALL) == 0 && c == NEWLINE) RRETURN(MATCH_NOMATCH);
            break;

            case OP_ANYBYTE:
            break;

            case OP_NOT_DIGIT:
            if ((md->ctypes[c] & ctype_digit) != 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_DIGIT:
            if ((md->ctypes[c] & ctype_digit) == 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_NOT_WHITESPACE:
            if ((md->ctypes[c] & ctype_space) != 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_WHITESPACE:
            if  ((md->ctypes[c] & ctype_space) == 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_NOT_WORDCHAR:
            if ((md->ctypes[c] & ctype_word) != 0) RRETURN(MATCH_NOMATCH);
            break;

            case OP_WORDCHAR:
            if ((md->ctypes[c] & ctype_word) == 0) RRETURN(MATCH_NOMATCH);
            break;

            default:
            RRETURN(PCRE_ERROR_INTERNAL);
            }
          }
        }
      
      }

    

    else
      {
      pp = eptr;  

#ifdef SUPPORT_UCP
      if (prop_type > 0)
        {
        for (i = min; i < max; i++)
          {
          int len = 1;
          if (eptr >= md->end_subject) break;
          GETCHARLEN(c, eptr, len);
          prop_category = ucp_findchar(c, &prop_chartype, &prop_othercase);
          if ((*prop_test_variable == prop_test_against) == prop_fail_result)
            break;
          eptr+= len;
          }

        

        for(;;)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (eptr-- == pp) break;        
          BACKCHAR(eptr);
          }
        }

      

      else if (ctype == OP_EXTUNI)
        {
        for (i = min; i < max; i++)
          {
          if (eptr >= md->end_subject) break;
          GETCHARINCTEST(c, eptr);
          prop_category = ucp_findchar(c, &prop_chartype, &prop_othercase);
          if (prop_category == ucp_M) break;
          while (eptr < md->end_subject)
            {
            int len = 1;
            if (!md->utf8) c = *eptr; else
              {
              GETCHARLEN(c, eptr, len);
              }
            prop_category = ucp_findchar(c, &prop_chartype, &prop_othercase);
            if (prop_category != ucp_M) break;
            eptr += len;
            }
          }

        

        for(;;)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (eptr-- == pp) break;        
          for (;;)                        
            {
            int len = 1;
            BACKCHAR(eptr);
            if (!md->utf8) c = *eptr; else
              {
              GETCHARLEN(c, eptr, len);
              }
            prop_category = ucp_findchar(c, &prop_chartype, &prop_othercase);
            if (prop_category != ucp_M) break;
            eptr--;
            }
          }
        }

      else
#endif   

#ifdef SUPPORT_UTF8
      

      if (md->utf8)
        {
        switch(ctype)
          {
          case OP_ANY:

          

          if (max < INT_MAX)
            {
            if ((ims & PCRE_DOTALL) == 0)
              {
              for (i = min; i < max; i++)
                {
                if (eptr >= md->end_subject || *eptr == NEWLINE) break;
                eptr++;
                while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
                }
              }
            else
              {
              for (i = min; i < max; i++)
                {
                eptr++;
                while (eptr < md->end_subject && (*eptr & 0xc0) == 0x80) eptr++;
                }
              }
            }

          

          else
            {
            if ((ims & PCRE_DOTALL) == 0)
              {
              for (i = min; i < max; i++)
                {
                if (eptr >= md->end_subject || *eptr == NEWLINE) break;
                eptr++;
                }
              break;
              }
            else
              {
              c = max - min;
              if (c > md->end_subject - eptr) c = md->end_subject - eptr;
              eptr += c;
              }
            }
          break;

          

          case OP_ANYBYTE:
          c = max - min;
          if (c > md->end_subject - eptr) c = md->end_subject - eptr;
          eptr += c;
          break;

          case OP_NOT_DIGIT:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (c < 256 && (md->ctypes[c] & ctype_digit) != 0) break;
            eptr+= len;
            }
          break;

          case OP_DIGIT:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (c >= 256 ||(md->ctypes[c] & ctype_digit) == 0) break;
            eptr+= len;
            }
          break;

          case OP_NOT_WHITESPACE:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (c < 256 && (md->ctypes[c] & ctype_space) != 0) break;
            eptr+= len;
            }
          break;

          case OP_WHITESPACE:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (c >= 256 ||(md->ctypes[c] & ctype_space) == 0) break;
            eptr+= len;
            }
          break;

          case OP_NOT_WORDCHAR:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (c < 256 && (md->ctypes[c] & ctype_word) != 0) break;
            eptr+= len;
            }
          break;

          case OP_WORDCHAR:
          for (i = min; i < max; i++)
            {
            int len = 1;
            if (eptr >= md->end_subject) break;
            GETCHARLEN(c, eptr, len);
            if (c >= 256 || (md->ctypes[c] & ctype_word) == 0) break;
            eptr+= len;
            }
          break;

          default:
          RRETURN(PCRE_ERROR_INTERNAL);
          }

        

        for(;;)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          if (eptr-- == pp) break;        
          BACKCHAR(eptr);
          }
        }
      else
#endif

      
        {
        switch(ctype)
          {
          case OP_ANY:
          if ((ims & PCRE_DOTALL) == 0)
            {
            for (i = min; i < max; i++)
              {
              if (eptr >= md->end_subject || *eptr == NEWLINE) break;
              eptr++;
              }
            break;
            }
          

          case OP_ANYBYTE:
          c = max - min;
          if (c > md->end_subject - eptr) c = md->end_subject - eptr;
          eptr += c;
          break;

          case OP_NOT_DIGIT:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_digit) != 0)
              break;
            eptr++;
            }
          break;

          case OP_DIGIT:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_digit) == 0)
              break;
            eptr++;
            }
          break;

          case OP_NOT_WHITESPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_space) != 0)
              break;
            eptr++;
            }
          break;

          case OP_WHITESPACE:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_space) == 0)
              break;
            eptr++;
            }
          break;

          case OP_NOT_WORDCHAR:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_word) != 0)
              break;
            eptr++;
            }
          break;

          case OP_WORDCHAR:
          for (i = min; i < max; i++)
            {
            if (eptr >= md->end_subject || (md->ctypes[*eptr] & ctype_word) == 0)
              break;
            eptr++;
            }
          break;

          default:
          RRETURN(PCRE_ERROR_INTERNAL);
          }

        

        while (eptr >= pp)
          {
          RMATCH(rrc, eptr, ecode, offset_top, md, ims, eptrb, 0);
          eptr--;
          if (rrc != MATCH_NOMATCH) RRETURN(rrc);
          }
        }

      

      RRETURN(MATCH_NOMATCH);
      }
    

    

    default:
    DPRINTF(("Unknown opcode %d\n", *ecode));
    RRETURN(PCRE_ERROR_UNKNOWN_NODE);
    }

  

  }             

}




#ifdef NO_RECURSE
#undef eptr
#undef ecode
#undef offset_top
#undef ims
#undef eptrb
#undef flags

#undef callpat
#undef charptr
#undef data
#undef next
#undef pp
#undef prev
#undef saved_eptr

#undef new_recursive

#undef cur_is_word
#undef condition
#undef minimize
#undef prev_is_word

#undef original_ims

#undef ctype
#undef length
#undef max
#undef min
#undef number
#undef offset
#undef op
#undef save_capture_last
#undef save_offset1
#undef save_offset2
#undef save_offset3
#undef stacksave

#undef newptrb

#endif



#undef fc
#undef fi









EXPORT int
pcre_exec(const pcre *argument_re, const pcre_extra *extra_data,
  const char *subject, int length, int start_offset, int options, int *offsets,
  int offsetcount)
{
int rc, resetcount, ocount;
int first_byte = -1;
int req_byte = -1;
int req_byte2 = -1;
unsigned long int ims = 0;
BOOL using_temporary_offsets = FALSE;
BOOL anchored;
BOOL startline;
BOOL first_byte_caseless = FALSE;
BOOL req_byte_caseless = FALSE;
match_data match_block;
const uschar *tables;
const uschar *start_bits = NULL;
const uschar *start_match = (const uschar *)subject + start_offset;
const uschar *end_subject;
const uschar *req_byte_ptr = start_match - 1;

pcre_study_data internal_study;
const pcre_study_data *study;

real_pcre internal_re;
const real_pcre *external_re = (const real_pcre *)argument_re;
const real_pcre *re = external_re;



if ((options & ~PUBLIC_EXEC_OPTIONS) != 0) return PCRE_ERROR_BADOPTION;
if (re == NULL || subject == NULL ||
   (offsets == NULL && offsetcount > 0)) return PCRE_ERROR_NULL;
if (offsetcount < 0) return PCRE_ERROR_BADCOUNT;



study = NULL;
match_block.match_limit = MATCH_LIMIT;
match_block.callout_data = NULL;



tables = external_re->tables;

if (extra_data != NULL)
  {
  register unsigned int flags = extra_data->flags;
  if ((flags & PCRE_EXTRA_STUDY_DATA) != 0)
    study = (const pcre_study_data *)extra_data->study_data;
  if ((flags & PCRE_EXTRA_MATCH_LIMIT) != 0)
    match_block.match_limit = extra_data->match_limit;
  if ((flags & PCRE_EXTRA_CALLOUT_DATA) != 0)
    match_block.callout_data = extra_data->callout_data;
  if ((flags & PCRE_EXTRA_TABLES) != 0) tables = extra_data->tables;
  }



if (tables == NULL) tables = pcre_default_tables;



if (re->magic_number != MAGIC_NUMBER)
  {
  re = try_flipped(re, &internal_re, study, &internal_study);
  if (re == NULL) return PCRE_ERROR_BADMAGIC;
  if (study != NULL) study = &internal_study;
  }



anchored = ((re->options | options) & PCRE_ANCHORED) != 0;
startline = (re->options & PCRE_STARTLINE) != 0;



match_block.start_code = (const uschar *)external_re + re->name_table_offset +
  re->name_count * re->name_entry_size;

match_block.start_subject = (const uschar *)subject;
match_block.start_offset = start_offset;
match_block.end_subject = match_block.start_subject + length;
end_subject = match_block.end_subject;

match_block.endonly = (re->options & PCRE_DOLLAR_ENDONLY) != 0;
match_block.utf8 = (re->options & PCRE_UTF8) != 0;

match_block.notbol = (options & PCRE_NOTBOL) != 0;
match_block.noteol = (options & PCRE_NOTEOL) != 0;
match_block.notempty = (options & PCRE_NOTEMPTY) != 0;
match_block.partial = (options & PCRE_PARTIAL) != 0;
match_block.hitend = FALSE;

match_block.recursive = NULL;                   

match_block.lcc = tables + lcc_offset;
match_block.ctypes = tables + ctypes_offset;



if (match_block.partial && (re->options & PCRE_NOPARTIAL) != 0)
  return PCRE_ERROR_BADPARTIAL;



#ifdef SUPPORT_UTF8
if (match_block.utf8 && (options & PCRE_NO_UTF8_CHECK) == 0)
  {
  if (valid_utf8((uschar *)subject, length) >= 0)
    return PCRE_ERROR_BADUTF8;
  if (start_offset > 0 && start_offset < length)
    {
    int tb = ((uschar *)subject)[start_offset];
    if (tb > 127)
      {
      tb &= 0xc0;
      if (tb != 0 && tb != 0xc0) return PCRE_ERROR_BADUTF8_OFFSET;
      }
    }
  }
#endif



ims = re->options & (PCRE_CASELESS|PCRE_MULTILINE|PCRE_DOTALL);



ocount = offsetcount - (offsetcount % 3);

if (re->top_backref > 0 && re->top_backref >= ocount/3)
  {
  ocount = re->top_backref * 3 + 3;
  match_block.offset_vector = (int *)(pcre_malloc)(ocount * sizeof(int));
  if (match_block.offset_vector == NULL) return PCRE_ERROR_NOMEMORY;
  using_temporary_offsets = TRUE;
  DPRINTF(("Got memory to hold back references\n"));
  }
else match_block.offset_vector = offsets;

match_block.offset_end = ocount;
match_block.offset_max = (2*ocount)/3;
match_block.offset_overflow = FALSE;
match_block.capture_last = -1;



resetcount = 2 + re->top_bracket * 2;
if (resetcount > offsetcount) resetcount = ocount;



if (match_block.offset_vector != NULL)
  {
  register int *iptr = match_block.offset_vector + ocount;
  register int *iend = iptr - resetcount/2 + 1;
  while (--iptr >= iend) *iptr = -1;
  }



if (!anchored)
  {
  if ((re->options & PCRE_FIRSTSET) != 0)
    {
    first_byte = re->first_byte & 255;
    if ((first_byte_caseless = ((re->first_byte & REQ_CASELESS) != 0)) == TRUE)
      first_byte = match_block.lcc[first_byte];
    }
  else
    if (!startline && study != NULL &&
      (study->options & PCRE_STUDY_MAPPED) != 0)
        start_bits = study->start_bits;
  }



if ((re->options & PCRE_REQCHSET) != 0)
  {
  req_byte = re->req_byte & 255;
  req_byte_caseless = (re->req_byte & REQ_CASELESS) != 0;
  req_byte2 = (tables + fcc_offset)[req_byte];  
  }



do
  {
  

  if (match_block.offset_vector != NULL)
    {
    register int *iptr = match_block.offset_vector;
    register int *iend = iptr + resetcount;
    while (iptr < iend) *iptr++ = -1;
    }

  

  if (first_byte >= 0)
    {
    if (first_byte_caseless)
      while (start_match < end_subject &&
             match_block.lcc[*start_match] != first_byte)
        start_match++;
    else
      while (start_match < end_subject && *start_match != first_byte)
        start_match++;
    }

  

  else if (startline)
    {
    if (start_match > match_block.start_subject + start_offset)
      {
      while (start_match < end_subject && start_match[-1] != NEWLINE)
        start_match++;
      }
    }

  

  else if (start_bits != NULL)
    {
    while (start_match < end_subject)
      {
      register unsigned int c = *start_match;
      if ((start_bits[c/8] & (1 << (c&7))) == 0) start_match++; else break;
      }
    }

#ifdef DEBUG  
  printf(">>>> Match against: ");
  pchars(start_match, end_subject - start_match, TRUE, &match_block);
  printf("\n");
#endif

  

  if (req_byte >= 0 &&
      end_subject - start_match < REQ_BYTE_MAX &&
      !match_block.partial)
    {
    register const uschar *p = start_match + ((first_byte >= 0)? 1 : 0);

    

    if (p > req_byte_ptr)
      {
      if (req_byte_caseless)
        {
        while (p < end_subject)
          {
          register int pp = *p++;
          if (pp == req_byte || pp == req_byte2) { p--; break; }
          }
        }
      else
        {
        while (p < end_subject)
          {
          if (*p++ == req_byte) { p--; break; }
          }
        }

      

      if (p >= end_subject) break;

      

      req_byte_ptr = p;
      }
    }

  

  match_block.start_match = start_match;
  match_block.match_call_count = 0;

  rc = match(start_match, match_block.start_code, 2, &match_block, ims, NULL,
    match_isgroup);

  if (rc == MATCH_NOMATCH)
    {
    start_match++;
#ifdef SUPPORT_UTF8
    if (match_block.utf8)
      while(start_match < end_subject && (*start_match & 0xc0) == 0x80)
        start_match++;
#endif
    continue;
    }

  if (rc != MATCH_MATCH)
    {
    DPRINTF((">>>> error: returning %d\n", rc));
    return rc;
    }

  

  if (using_temporary_offsets)
    {
    if (offsetcount >= 4)
      {
      memcpy(offsets + 2, match_block.offset_vector + 2,
        (offsetcount - 2) * sizeof(int));
      DPRINTF(("Copied offsets from temporary memory\n"));
      }
    if (match_block.end_offset_top > offsetcount)
      match_block.offset_overflow = TRUE;

    DPRINTF(("Freeing temporary memory\n"));
    (pcre_free)(match_block.offset_vector);
    }

  rc = match_block.offset_overflow? 0 : match_block.end_offset_top/2;

  if (offsetcount < 2) rc = 0; else
    {
    offsets[0] = start_match - match_block.start_subject;
    offsets[1] = match_block.end_match_ptr - match_block.start_subject;
    }

  DPRINTF((">>>> returning %d\n", rc));
  return rc;
  }



while (!anchored && start_match <= end_subject);

if (using_temporary_offsets)
  {
  DPRINTF(("Freeing temporary memory\n"));
  (pcre_free)(match_block.offset_vector);
  }

if (match_block.partial && match_block.hitend)
  {
  DPRINTF((">>>> returning PCRE_ERROR_PARTIAL\n"));
  return PCRE_ERROR_PARTIAL;
  }
else
  {
  DPRINTF((">>>> returning PCRE_ERROR_NOMATCH\n"));
  return PCRE_ERROR_NOMATCH;
  }
}


