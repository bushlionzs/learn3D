








#include "internal.h"






int
pcre_get_stringnumber(const pcre *code, const char *stringname)
{
int rc;
int entrysize;
int top, bot;
uschar *nametable;

if ((rc = pcre_fullinfo(code, NULL, PCRE_INFO_NAMECOUNT, &top)) != 0)
  return rc;
if (top <= 0) return PCRE_ERROR_NOSUBSTRING;

if ((rc = pcre_fullinfo(code, NULL, PCRE_INFO_NAMEENTRYSIZE, &entrysize)) != 0)
  return rc;
if ((rc = pcre_fullinfo(code, NULL, PCRE_INFO_NAMETABLE, &nametable)) != 0)
  return rc;

bot = 0;
while (top > bot)
  {
  int mid = (top + bot) / 2;
  uschar *entry = nametable + entrysize*mid;
  int c = strcmp(stringname, (char *)(entry + 2));
  if (c == 0) return (entry[0] << 8) + entry[1];
  if (c > 0) bot = mid + 1; else top = mid;
  }

return PCRE_ERROR_NOSUBSTRING;
}







int
pcre_copy_substring(const char *subject, int *ovector, int stringcount,
  int stringnumber, char *buffer, int size)
{
int yield;
if (stringnumber < 0 || stringnumber >= stringcount)
  return PCRE_ERROR_NOSUBSTRING;
stringnumber *= 2;
yield = ovector[stringnumber+1] - ovector[stringnumber];
if (size < yield + 1) return PCRE_ERROR_NOMEMORY;
memcpy(buffer, subject + ovector[stringnumber], yield);
buffer[yield] = 0;
return yield;
}







int
pcre_copy_named_substring(const pcre *code, const char *subject, int *ovector,
  int stringcount, const char *stringname, char *buffer, int size)
{
int n = pcre_get_stringnumber(code, stringname);
if (n <= 0) return n;
return pcre_copy_substring(subject, ovector, stringcount, n, buffer, size);
}







int
pcre_get_substring_list(const char *subject, int *ovector, int stringcount,
  const char ***listptr)
{
int i;
int size = sizeof(char *);
int double_count = stringcount * 2;
char **stringlist;
char *p;

for (i = 0; i < double_count; i += 2)
  size += sizeof(char *) + ovector[i+1] - ovector[i] + 1;

stringlist = (char **)(pcre_malloc)(size);
if (stringlist == NULL) return PCRE_ERROR_NOMEMORY;

*listptr = (const char **)stringlist;
p = (char *)(stringlist + stringcount + 1);

for (i = 0; i < double_count; i += 2)
  {
  int len = ovector[i+1] - ovector[i];
  memcpy(p, subject + ovector[i], len);
  *stringlist++ = p;
  p += len;
  *p++ = 0;
  }

*stringlist = NULL;
return 0;
}







void
pcre_free_substring_list(const char **pointer)
{
(pcre_free)((void *)pointer);
}







int
pcre_get_substring(const char *subject, int *ovector, int stringcount,
  int stringnumber, const char **stringptr)
{
int yield;
char *substring;
if (stringnumber < 0 || stringnumber >= stringcount)
  return PCRE_ERROR_NOSUBSTRING;
stringnumber *= 2;
yield = ovector[stringnumber+1] - ovector[stringnumber];
substring = (char *)(pcre_malloc)(yield + 1);
if (substring == NULL) return PCRE_ERROR_NOMEMORY;
memcpy(substring, subject + ovector[stringnumber], yield);
substring[yield] = 0;
*stringptr = substring;
return yield;
}







int
pcre_get_named_substring(const pcre *code, const char *subject, int *ovector,
  int stringcount, const char *stringname, const char **stringptr)
{
int n = pcre_get_stringnumber(code, stringname);
if (n <= 0) return n;
return pcre_get_substring(subject, ovector, stringcount, n, stringptr);
}








void
pcre_free_substring(const char *pointer)
{
(pcre_free)((void *)pointer);
}


