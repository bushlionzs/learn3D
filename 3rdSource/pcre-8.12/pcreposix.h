

#ifndef _PCREPOSIX_H
#define _PCREPOSIX_H





#include <stdlib.h>



#ifdef __cplusplus
extern "C" {
#endif



#define REG_ICASE     0x01
#define REG_NEWLINE   0x02
#define REG_NOTBOL    0x04
#define REG_NOTEOL    0x08



#define REG_EXTENDED  0
#define REG_NOSUB     0



enum {
  REG_ASSERT = 1,  
  REG_BADBR,       
  REG_BADPAT,      
  REG_BADRPT,      
  REG_EBRACE,      
  REG_EBRACK,      
  REG_ECOLLATE,    
  REG_ECTYPE,      
  REG_EESCAPE,     
  REG_EMPTY,       
  REG_EPAREN,      
  REG_ERANGE,      
  REG_ESIZE,       
  REG_ESPACE,      
  REG_ESUBREG,     
  REG_INVARG,      
  REG_NOMATCH      
};




typedef struct {
  void *re_pcre;
  size_t re_nsub;
  size_t re_erroffset;
} regex_t;



typedef int regoff_t;

typedef struct {
  regoff_t rm_so;
  regoff_t rm_eo;
} regmatch_t;



extern int regcomp(regex_t *, const char *, int);
extern int regexec(const regex_t *, const char *, size_t, regmatch_t *, int);
extern size_t regerror(int, const regex_t *, char *, size_t);
extern void regfree(regex_t *);

#ifdef __cplusplus
}   
#endif

#endif 
