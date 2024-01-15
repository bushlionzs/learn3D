



#include "internal.h"
#include "pcreposix.h"
#include "stdlib.h"





static const char *const estring[] = {
  ERR1,  ERR2,  ERR3,  ERR4,  ERR5,  ERR6,  ERR7,  ERR8,  ERR9,  ERR10,
  ERR11, ERR12, ERR13, ERR14, ERR15, ERR16, ERR17, ERR18, ERR19, ERR20,
  ERR21, ERR22, ERR23, ERR24, ERR25, ERR26, ERR27, ERR29, ERR29, ERR30,
  ERR31, ERR32, ERR33, ERR34, ERR35, ERR36, ERR37, ERR38, ERR39, ERR40,
  ERR41, ERR42, ERR43, ERR44, ERR45, ERR46, ERR47 };

static const int eint[] = {
  REG_EESCAPE, 
  REG_EESCAPE, 
  REG_EESCAPE, 
  REG_BADBR,   
  REG_BADBR,   
  REG_EBRACK,  
  REG_ECTYPE,  
  REG_ERANGE,  
  REG_BADRPT,  
  REG_BADRPT,  
  REG_ASSERT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_EPAREN,  
  REG_ESUBREG, 
  REG_INVARG,  
  REG_INVARG,  
  REG_EPAREN,  
  REG_ESIZE,   
  REG_ESIZE,   
  REG_ESPACE,  
  REG_EPAREN,  
  REG_ASSERT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_ECTYPE,  
  REG_BADPAT,  
  REG_INVARG,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_EESCAPE, 
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT,  
  REG_BADPAT   
};



static const char *const pstring[] = {
  "",                                
  "internal error",                  
  "invalid repeat counts in {}",     
  "pattern error",                   
  "? * + invalid",                   
  "unbalanced {}",                   
  "unbalanced []",                   
  "collation error - not relevant",  
  "bad class",                       
  "bad escape sequence",             
  "empty expression",                
  "unbalanced ()",                   
  "bad range inside []",             
  "expression too big",              
  "failed to get memory",            
  "bad back reference",              
  "bad argument",                    
  "match failed"                     
};








static int
pcre_posix_error_code(const char *s)
{
size_t i;
for (i = 0; i < sizeof(estring)/sizeof(char *); i++)
  if (strcmp(s, estring[i]) == 0) return eint[i];
return REG_ASSERT;
}





EXPORT size_t
regerror(int errcode, const regex_t *preg, char *errbuf, size_t errbuf_size)
{
const char *message, *addmessage;
size_t length, addlength;

message = (errcode >= (int)(sizeof(pstring)/sizeof(char *)))?
  "unknown error code" : pstring[errcode];
length = strlen(message) + 1;

addmessage = " at offset ";
addlength = (preg != NULL && (int)preg->re_erroffset != -1)?
  strlen(addmessage) + 6 : 0;

if (errbuf_size > 0)
  {
  if (addlength > 0 && errbuf_size >= length + addlength)
    sprintf(errbuf, "%s%s%-6d", message, addmessage, (int)preg->re_erroffset);
  else
    {
    strncpy(errbuf, message, errbuf_size - 1);
    errbuf[errbuf_size-1] = 0;
    }
  }

return length + addlength;
}






EXPORT void
regfree(regex_t *preg)
{
(pcre_free)(preg->re_pcre);
}








EXPORT int
regcomp(regex_t *preg, const char *pattern, int cflags)
{
const char *errorptr;
int erroffset;
int options = 0;

if ((cflags & REG_ICASE) != 0) options |= PCRE_CASELESS;
if ((cflags & REG_NEWLINE) != 0) options |= PCRE_MULTILINE;

preg->re_pcre = pcre_compile(pattern, options, &errorptr, &erroffset, NULL);
preg->re_erroffset = erroffset;

if (preg->re_pcre == NULL) return pcre_posix_error_code(errorptr);

preg->re_nsub = pcre_info((const pcre *)preg->re_pcre, NULL, NULL);
return 0;
}








EXPORT int
regexec(const regex_t *preg, const char *string, size_t nmatch,
  regmatch_t pmatch[], int eflags)
{
int rc;
int options = 0;
int *ovector = NULL;
int small_ovector[POSIX_MALLOC_THRESHOLD * 3];
BOOL allocated_ovector = FALSE;

if ((eflags & REG_NOTBOL) != 0) options |= PCRE_NOTBOL;
if ((eflags & REG_NOTEOL) != 0) options |= PCRE_NOTEOL;

((regex_t *)preg)->re_erroffset = (size_t)(-1);  

if (nmatch > 0)
  {
  if (nmatch <= POSIX_MALLOC_THRESHOLD)
    {
    ovector = &(small_ovector[0]);
    }
  else
    {
    ovector = (int *)malloc(sizeof(int) * nmatch * 3);
    if (ovector == NULL) return REG_ESPACE;
    allocated_ovector = TRUE;
    }
  }

rc = pcre_exec((const pcre *)preg->re_pcre, NULL, string, (int)strlen(string),
  0, options, ovector, nmatch * 3);

if (rc == 0) rc = nmatch;    

if (rc >= 0)
  {
  size_t i;
  for (i = 0; i < (size_t)rc; i++)
    {
    pmatch[i].rm_so = ovector[i*2];
    pmatch[i].rm_eo = ovector[i*2+1];
    }
  if (allocated_ovector) free(ovector);
  for (; i < nmatch; i++) pmatch[i].rm_so = pmatch[i].rm_eo = -1;
  return 0;
  }

else
  {
  if (allocated_ovector) free(ovector);
  switch(rc)
    {
    case PCRE_ERROR_NOMATCH: return REG_NOMATCH;
    case PCRE_ERROR_NULL: return REG_INVARG;
    case PCRE_ERROR_BADOPTION: return REG_INVARG;
    case PCRE_ERROR_BADMAGIC: return REG_INVARG;
    case PCRE_ERROR_UNKNOWN_NODE: return REG_ASSERT;
    case PCRE_ERROR_NOMEMORY: return REG_ESPACE;
    case PCRE_ERROR_MATCHLIMIT: return REG_ESPACE;
    case PCRE_ERROR_BADUTF8: return REG_INVARG;
    case PCRE_ERROR_BADUTF8_OFFSET: return REG_INVARG;
    default: return REG_ASSERT;
    }
  }
}


