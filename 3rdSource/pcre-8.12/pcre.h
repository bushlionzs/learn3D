#ifndef _PCRE_H
#define _PCRE_H



#define PCRE_MAJOR      5
#define PCRE_MINOR      0
#define PCRE_DATE       13-Sep-2004





#ifndef PCRE_DATA_SCOPE
#  define PCRE_DATA_SCOPE     extern
#endif



#include <stdlib.h>



#ifdef __cplusplus
extern "C" {
#endif



#define PCRE_CASELESS           0x0001
#define PCRE_MULTILINE          0x0002
#define PCRE_DOTALL             0x0004
#define PCRE_EXTENDED           0x0008
#define PCRE_ANCHORED           0x0010
#define PCRE_DOLLAR_ENDONLY     0x0020
#define PCRE_EXTRA              0x0040
#define PCRE_NOTBOL             0x0080
#define PCRE_NOTEOL             0x0100
#define PCRE_UNGREEDY           0x0200
#define PCRE_NOTEMPTY           0x0400
#define PCRE_UTF8               0x0800
#define PCRE_NO_AUTO_CAPTURE    0x1000
#define PCRE_NO_UTF8_CHECK      0x2000
#define PCRE_AUTO_CALLOUT       0x4000
#define PCRE_PARTIAL            0x8000



#define PCRE_ERROR_NOMATCH         (-1)
#define PCRE_ERROR_NULL            (-2)
#define PCRE_ERROR_BADOPTION       (-3)
#define PCRE_ERROR_BADMAGIC        (-4)
#define PCRE_ERROR_UNKNOWN_NODE    (-5)
#define PCRE_ERROR_NOMEMORY        (-6)
#define PCRE_ERROR_NOSUBSTRING     (-7)
#define PCRE_ERROR_MATCHLIMIT      (-8)
#define PCRE_ERROR_CALLOUT         (-9)  
#define PCRE_ERROR_BADUTF8        (-10)
#define PCRE_ERROR_BADUTF8_OFFSET (-11)
#define PCRE_ERROR_PARTIAL        (-12)
#define PCRE_ERROR_BADPARTIAL     (-13)
#define PCRE_ERROR_INTERNAL       (-14)
#define PCRE_ERROR_BADCOUNT       (-15)



#define PCRE_INFO_OPTIONS            0
#define PCRE_INFO_SIZE               1
#define PCRE_INFO_CAPTURECOUNT       2
#define PCRE_INFO_BACKREFMAX         3
#define PCRE_INFO_FIRSTBYTE          4
#define PCRE_INFO_FIRSTCHAR          4  
#define PCRE_INFO_FIRSTTABLE         5
#define PCRE_INFO_LASTLITERAL        6
#define PCRE_INFO_NAMEENTRYSIZE      7
#define PCRE_INFO_NAMECOUNT          8
#define PCRE_INFO_NAMETABLE          9
#define PCRE_INFO_STUDYSIZE         10
#define PCRE_INFO_DEFAULT_TABLES    11



#define PCRE_CONFIG_UTF8                    0
#define PCRE_CONFIG_NEWLINE                 1
#define PCRE_CONFIG_LINK_SIZE               2
#define PCRE_CONFIG_POSIX_MALLOC_THRESHOLD  3
#define PCRE_CONFIG_MATCH_LIMIT             4
#define PCRE_CONFIG_STACKRECURSE            5
#define PCRE_CONFIG_UNICODE_PROPERTIES      6



#define PCRE_EXTRA_STUDY_DATA          0x0001
#define PCRE_EXTRA_MATCH_LIMIT         0x0002
#define PCRE_EXTRA_CALLOUT_DATA        0x0004
#define PCRE_EXTRA_TABLES              0x0008



struct real_pcre;                 
typedef struct real_pcre pcre;



typedef struct pcre_extra {
  unsigned long int flags;        
  void *study_data;               
  unsigned long int match_limit;  
  void *callout_data;             
  const unsigned char *tables;    
} pcre_extra;



typedef struct pcre_callout_block {
  int          version;           
  
  int          callout_number;    
  int         *offset_vector;     
  const char  *subject;           
  int          subject_length;    
  int          start_match;       
  int          current_position;  
  int          capture_top;       
  int          capture_last;      
  void        *callout_data;      
  
  int          pattern_position;  
  int          next_item_length;  
  
} pcre_callout_block;



#ifndef VPCOMPAT
PCRE_DATA_SCOPE void *(*pcre_malloc)(size_t);
PCRE_DATA_SCOPE void  (*pcre_free)(void *);
PCRE_DATA_SCOPE void *(*pcre_stack_malloc)(size_t);
PCRE_DATA_SCOPE void  (*pcre_stack_free)(void *);
PCRE_DATA_SCOPE int   (*pcre_callout)(pcre_callout_block *);
#else   
extern void *pcre_malloc(size_t);
extern void  pcre_free(void *);
extern void *pcre_stack_malloc(size_t);
extern void  pcre_stack_free(void *);
extern int   pcre_callout(pcre_callout_block *);
#endif  



 pcre * pcre_compile(const char*, int, const char**,
              int *, const unsigned char *);
extern int  pcre_config(int, void *);
extern int  pcre_copy_named_substring(const pcre *, const char *,
              int *, int, const char *, char *, int);
extern int  pcre_copy_substring(const char *, int *, int, int,
              char *, int);
extern int  pcre_exec(const pcre *, const pcre_extra *,
              const char *, int, int, int, int *, int);
extern void pcre_free_substring(const char *);
extern void pcre_free_substring_list(const char **);
extern int  pcre_fullinfo(const pcre *, const pcre_extra *, int,
              void *);
extern int  pcre_get_named_substring(const pcre *, const char *,
              int *, int,  const char *, const char **);
extern int  pcre_get_stringnumber(const pcre *, const char *);
extern int  pcre_get_substring(const char *, int *, int, int,
              const char **);
extern int  pcre_get_substring_list(const char *, int *, int,
              const char ***);
extern int  pcre_info(const pcre *, int *, int *);
extern const unsigned char *pcre_maketables(void);
extern pcre_extra *pcre_study(const pcre *, int, const char **);
extern const char *pcre_version(void);

#ifdef __cplusplus
}  
#endif

#endif 
