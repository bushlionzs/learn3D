








#include "pcreconfig.h"



#include <ctype.h>
#include <limits.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PCRE_SPY
#define PCRE_DEFINITION       
#endif



#if USHRT_MAX == 65535
  typedef unsigned short pcre_uint16;
#elif UINT_MAX == 65535
  typedef unsigned int pcre_uint16;
#else
  #error Cannot determine a type for 16-bit unsigned integers
#endif

#if UINT_MAX == 4294967295
  typedef unsigned int pcre_uint32;
#elif ULONG_MAX == 4294967295
  typedef unsigned long int pcre_uint32;
#else
  #error Cannot determine a type for 32-bit unsigned integers
#endif



typedef unsigned char uschar;



#include "pcre.h"



#ifdef VPCOMPAT
#define strncmp(s1,s2,m) _strncmp(s1,s2,m)
#define memcpy(d,s,n)    _memcpy(d,s,n)
#define memmove(d,s,n)   _memmove(d,s,n)
#define memset(s,c,n)    _memset(s,c,n)
#else  



#if ! HAVE_MEMMOVE
#undef  memmove        
#if HAVE_BCOPY
#define memmove(a, b, c) bcopy(b, a, c)
#else  
void *
pcre_memmove(unsigned char *dest, const unsigned char *src, size_t n)
{
int i;
dest += n;
src += n;
for (i = 0; i < n; ++i) *(--dest) =  *(--src);
return dest;
}
#define memmove(a, b, c) pcre_memmove(a, b, c)
#endif   
#endif   
#endif   




#if LINK_SIZE == 2

#define PUT(a,n,d)   \
  (a[n] = (d) >> 8), \
  (a[(n)+1] = (d) & 255)

#define GET(a,n) \
  (((a)[n] << 8) | (a)[(n)+1])

#define MAX_PATTERN_SIZE (1 << 16)


#elif LINK_SIZE == 3

#define PUT(a,n,d)       \
  (a[n] = (d) >> 16),    \
  (a[(n)+1] = (d) >> 8), \
  (a[(n)+2] = (d) & 255)

#define GET(a,n) \
  (((a)[n] << 16) | ((a)[(n)+1] << 8) | (a)[(n)+2])

#define MAX_PATTERN_SIZE (1 << 24)


#elif LINK_SIZE == 4

#define PUT(a,n,d)        \
  (a[n] = (d) >> 24),     \
  (a[(n)+1] = (d) >> 16), \
  (a[(n)+2] = (d) >> 8),  \
  (a[(n)+3] = (d) & 255)

#define GET(a,n) \
  (((a)[n] << 24) | ((a)[(n)+1] << 16) | ((a)[(n)+2] << 8) | (a)[(n)+3])

#define MAX_PATTERN_SIZE (1 << 30)   


#else
#error LINK_SIZE must be either 2, 3, or 4
#endif




#define PUTINC(a,n,d)   PUT(a,n,d), a += LINK_SIZE




#define PUT2(a,n,d)   \
  a[n] = (d) >> 8; \
  a[(n)+1] = (d) & 255

#define GET2(a,n) \
  (((a)[n] << 8) | (a)[(n)+1])

#define PUT2INC(a,n,d)  PUT2(a,n,d), a += 2




#ifndef offsetof
#define offsetof(p_type,field) ((size_t)&(((p_type *)0)->field))
#endif




#define PCRE_IMS (PCRE_CASELESS|PCRE_MULTILINE|PCRE_DOTALL)



#define PCRE_FIRSTSET      0x40000000  
#define PCRE_REQCHSET      0x20000000  
#define PCRE_STARTLINE     0x10000000  
#define PCRE_ICHANGED      0x08000000  
#define PCRE_NOPARTIAL     0x04000000  



#define PCRE_STUDY_MAPPED   0x01     



#define PUBLIC_OPTIONS \
  (PCRE_CASELESS|PCRE_EXTENDED|PCRE_ANCHORED|PCRE_MULTILINE| \
   PCRE_DOTALL|PCRE_DOLLAR_ENDONLY|PCRE_EXTRA|PCRE_UNGREEDY|PCRE_UTF8| \
   PCRE_NO_AUTO_CAPTURE|PCRE_NO_UTF8_CHECK|PCRE_AUTO_CALLOUT)

#define PUBLIC_EXEC_OPTIONS \
  (PCRE_ANCHORED|PCRE_NOTBOL|PCRE_NOTEOL|PCRE_NOTEMPTY|PCRE_NO_UTF8_CHECK| \
   PCRE_PARTIAL)

#define PUBLIC_STUDY_OPTIONS 0   



#define MAGIC_NUMBER  0x50435245UL   



#define REQ_UNSET (-2)
#define REQ_NONE  (-1)



#define REQ_CASELESS 0x0100    
#define REQ_VARY     0x0200    



typedef int BOOL;

#define FALSE   0
#define TRUE    1



#ifndef ESC_e
#define ESC_e 27
#endif

#ifndef ESC_f
#define ESC_f '\f'
#endif

#ifndef ESC_n
#define ESC_n NEWLINE
#endif

#ifndef ESC_r
#define ESC_r '\r'
#endif



#ifndef ESC_tee
#define ESC_tee '\t'
#endif



enum { ESC_A = 1, ESC_G, ESC_B, ESC_b, ESC_D, ESC_d, ESC_S, ESC_s, ESC_W,
       ESC_w, ESC_dum1, ESC_C, ESC_P, ESC_p, ESC_X, ESC_Z, ESC_z, ESC_E,
       ESC_Q, ESC_REF };



#define XCL_NOT    0x01    
#define XCL_MAP    0x02    

#define XCL_END       0    
#define XCL_SINGLE    1    
#define XCL_RANGE     2    
#define XCL_PROP      3    
#define XCL_NOTPROP   4    




enum {
  OP_END,            

  

  OP_SOD,            
  OP_SOM,            
  OP_NOT_WORD_BOUNDARY,  
  OP_WORD_BOUNDARY,      
  OP_NOT_DIGIT,          
  OP_DIGIT,              
  OP_NOT_WHITESPACE,     
  OP_WHITESPACE,         
  OP_NOT_WORDCHAR,       
  OP_WORDCHAR,           
  OP_ANY,            
  OP_ANYBYTE,        
  OP_NOTPROP,        
  OP_PROP,           
  OP_EXTUNI,         
  OP_EODN,           
  OP_EOD,            

  OP_OPT,            
  OP_CIRC,           
  OP_DOLL,           
  OP_CHAR,           
  OP_CHARNC,         
  OP_NOT,            

  OP_STAR,           
  OP_MINSTAR,        
  OP_PLUS,           
  OP_MINPLUS,        
  OP_QUERY,          
  OP_MINQUERY,       
  OP_UPTO,           
  OP_MINUPTO,        
  OP_EXACT,          

  OP_NOTSTAR,        
  OP_NOTMINSTAR,     
  OP_NOTPLUS,        
  OP_NOTMINPLUS,     
  OP_NOTQUERY,       
  OP_NOTMINQUERY,    
  OP_NOTUPTO,        
  OP_NOTMINUPTO,     
  OP_NOTEXACT,       

  OP_TYPESTAR,       
  OP_TYPEMINSTAR,    
  OP_TYPEPLUS,       
  OP_TYPEMINPLUS,    
  OP_TYPEQUERY,      
  OP_TYPEMINQUERY,   
  OP_TYPEUPTO,       
  OP_TYPEMINUPTO,    
  OP_TYPEEXACT,      

  OP_CRSTAR,         
  OP_CRMINSTAR,      
  OP_CRPLUS,         
  OP_CRMINPLUS,      
  OP_CRQUERY,        
  OP_CRMINQUERY,     
  OP_CRRANGE,        
  OP_CRMINRANGE,     

  OP_CLASS,          
  OP_NCLASS,         

  OP_XCLASS,         

  OP_REF,            
  OP_RECURSE,        
  OP_CALLOUT,        

  OP_ALT,            
  OP_KET,            
  OP_KETRMAX,        
  OP_KETRMIN,        

  

  OP_ASSERT,         
  OP_ASSERT_NOT,     
  OP_ASSERTBACK,     
  OP_ASSERTBACK_NOT, 
  OP_REVERSE,        

  

  OP_ONCE,           
  OP_COND,           
  OP_CREF,           

  OP_BRAZERO,        
  OP_BRAMINZERO,     

  OP_BRANUMBER,      

  OP_BRA             
};





#define EXTRACT_BASIC_MAX  100




#define OP_NAME_LIST \
  "End", "\\A", "\\G", "\\B", "\\b", "\\D", "\\d",                \
  "\\S", "\\s", "\\W", "\\w", "Any", "Anybyte",                   \
  "notprop", "prop", "extuni",                                    \
  "\\Z", "\\z",                                                   \
  "Opt", "^", "$", "char", "charnc", "not",                       \
  "*", "*?", "+", "+?", "?", "??", "{", "{", "{",                 \
  "*", "*?", "+", "+?", "?", "??", "{", "{", "{",                 \
  "*", "*?", "+", "+?", "?", "??", "{", "{", "{",                 \
  "*", "*?", "+", "+?", "?", "??", "{", "{",                      \
  "class", "nclass", "xclass", "Ref", "Recurse", "Callout",       \
  "Alt", "Ket", "KetRmax", "KetRmin", "Assert", "Assert not",     \
  "AssertB", "AssertB not", "Reverse", "Once", "Cond", "Cond ref",\
  "Brazero", "Braminzero", "Branumber", "Bra"




#define OP_LENGTHS \
  1,                              \
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   \
  1, 1,                           \
  2, 2, 1,                        \
  1, 1, 2, 1, 1,                  \
  2,                              \
  2,                              \
  2,                              \
   \
  2, 2, 2, 2, 2, 2,               \
  4, 4, 4,                        \
   \
  2, 2, 2, 2, 2, 2,               \
  4, 4, 4,                        \
   \
  2, 2, 2, 2, 2, 2,               \
  4, 4, 4,                        \
   \
  1, 1, 1, 1, 1, 1,               \
  5, 5,                           \
 33,                              \
 33,                              \
  0,                              \
  3,                              \
  1+LINK_SIZE,                    \
  2+2*LINK_SIZE,                  \
  1+LINK_SIZE,                    \
  1+LINK_SIZE,                    \
  1+LINK_SIZE,                    \
  1+LINK_SIZE,                    \
  1+LINK_SIZE,                    \
  1+LINK_SIZE,                    \
  1+LINK_SIZE,                    \
  1+LINK_SIZE,                    \
  1+LINK_SIZE,                    \
  1+LINK_SIZE,                    \
  1+LINK_SIZE,                    \
  3,                              \
  1, 1,                           \
  3,                              \
  1+LINK_SIZE                     \




#define CREF_RECURSE  0xffff



#define ERR1  "\\ at end of pattern"
#define ERR2  "\\c at end of pattern"
#define ERR3  "unrecognized character follows \\"
#define ERR4  "numbers out of order in {} quantifier"
#define ERR5  "number too big in {} quantifier"
#define ERR6  "missing terminating ] for character class"
#define ERR7  "invalid escape sequence in character class"
#define ERR8  "range out of order in character class"
#define ERR9  "nothing to repeat"
#define ERR10 "operand of unlimited repeat could match the empty string"
#define ERR11 "internal error: unexpected repeat"
#define ERR12 "unrecognized character after (?"
#define ERR13 "POSIX named classes are supported only within a class"
#define ERR14 "missing )"
#define ERR15 "reference to non-existent subpattern"
#define ERR16 "erroffset passed as NULL"
#define ERR17 "unknown option bit(s) set"
#define ERR18 "missing ) after comment"
#define ERR19 "parentheses nested too deeply"
#define ERR20 "regular expression too large"
#define ERR21 "failed to get memory"
#define ERR22 "unmatched parentheses"
#define ERR23 "internal error: code overflow"
#define ERR24 "unrecognized character after (?<"
#define ERR25 "lookbehind assertion is not fixed length"
#define ERR26 "malformed number after (?("
#define ERR27 "conditional group contains more than two branches"
#define ERR28 "assertion expected after (?("
#define ERR29 "(?R or (?digits must be followed by )"
#define ERR30 "unknown POSIX class name"
#define ERR31 "POSIX collating elements are not supported"
#define ERR32 "this version of PCRE is not compiled with PCRE_UTF8 support"
#define ERR33 "spare error"
#define ERR34 "character value in \\x{...} sequence is too large"
#define ERR35 "invalid condition (?(0)"
#define ERR36 "\\C not allowed in lookbehind assertion"
#define ERR37 "PCRE does not support \\L, \\l, \\N, \\U, or \\u"
#define ERR38 "number after (?C is > 255"
#define ERR39 "closing ) for (?C expected"
#define ERR40 "recursive call could loop indefinitely"
#define ERR41 "unrecognized character after (?P"
#define ERR42 "syntax error after (?P"
#define ERR43 "two named groups have the same name"
#define ERR44 "invalid UTF-8 string"
#define ERR45 "support for \\P, \\p, and \\X has not been compiled"
#define ERR46 "malformed \\P or \\p sequence"
#define ERR47 "unknown property name after \\P or \\p"



typedef struct real_pcre {
  pcre_uint32 magic_number;
  pcre_uint32 size;               
  pcre_uint32 options;
  pcre_uint32 dummy1;             

  pcre_uint16 top_bracket;
  pcre_uint16 top_backref;
  pcre_uint16 first_byte;
  pcre_uint16 req_byte;
  pcre_uint16 name_table_offset;  
  pcre_uint16 name_entry_size;    
  pcre_uint16 name_count;         
  pcre_uint16 dummy2;             

  const unsigned char *tables;    
  const unsigned char *nullpad;   
} real_pcre;



typedef struct pcre_study_data {
  pcre_uint32 size;               
  pcre_uint32 options;
  uschar start_bits[32];
} pcre_study_data;



typedef struct compile_data {
  const uschar *lcc;            
  const uschar *fcc;            
  const uschar *cbits;          
  const uschar *ctypes;         
  const uschar *start_code;     
  const uschar *start_pattern;  
  uschar *name_table;           
  int  names_found;             
  int  name_entry_size;         
  int  top_backref;             
  unsigned int backref_map;     
  int  req_varyopt;             
  BOOL nopartial;               
} compile_data;



typedef struct branch_chain {
  struct branch_chain *outer;
  uschar *current;
} branch_chain;



typedef struct recursion_info {
  struct recursion_info *prevrec; 
  int group_num;                
  const uschar *after_call;     
  const uschar *save_start;     
  int *offset_save;             
  int saved_max;                
} recursion_info;



struct heapframe;



typedef struct match_data {
  unsigned long int match_call_count; 
  unsigned long int match_limit;
  int   *offset_vector;         
  int    offset_end;            
  int    offset_max;            
  const uschar *lcc;            
  const uschar *ctypes;         
  BOOL   offset_overflow;       
  BOOL   notbol;                
  BOOL   noteol;                
  BOOL   utf8;                  
  BOOL   endonly;               
  BOOL   notempty;              
  BOOL   partial;               
  BOOL   hitend;                
  const uschar *start_code;     
  const uschar *start_subject;  
  const uschar *end_subject;    
  const uschar *start_match;    
  const uschar *end_match_ptr;  
  int    end_offset_top;        
  int    capture_last;          
  int    start_offset;          
  recursion_info *recursive;    
  void  *callout_data;          
  struct heapframe *thisframe;  
} match_data;



#define ctype_space   0x01
#define ctype_letter  0x02
#define ctype_digit   0x04
#define ctype_xdigit  0x08
#define ctype_word    0x10   
#define ctype_meta    0x80   



#define cbit_space     0      
#define cbit_xdigit   32      
#define cbit_digit    64      
#define cbit_upper    96      
#define cbit_lower   128      
#define cbit_word    160      
#define cbit_graph   192      
#define cbit_print   224      
#define cbit_punct   256      
#define cbit_cntrl   288      
#define cbit_length  320      



#define lcc_offset      0
#define fcc_offset    256
#define cbits_offset  512
#define ctypes_offset (cbits_offset + cbit_length)
#define tables_length (ctypes_offset + 256)


