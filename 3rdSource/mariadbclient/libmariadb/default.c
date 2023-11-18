/* Copyright (C) 2000 MySQL AB & MySQL Finland AB & TCX DataKonsult AB
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public
   License along with this library; if not, write to the Free
   Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02111-1301, USA */

/****************************************************************************
** Add all options from files named "group".cnf from the default_directories
** before the command line arguments.
** On Windows defaults will also search in the Windows directory for a file
** called 'group'.ini
** As long as the program uses the last argument for conflicting
** options one only have to add a call to "load_defaults" to enable
** use of default values.
** pre- and end 'blank space' are removed from options and values. The
** following escape sequences are recognized in values:  \b \t \n \r \\
**
** The following arguments are handled automaticly;  If used, they must be
** first argument on the command line!
** --no-defaults	; no options are read.
** --defaults-file=full-path-to-default-file	; Only this file will be read.
** --defaults-extra-file=full-path-to-default-file ; Read this file before ~/
** --print-defaults	; Print the modified command line and exit
****************************************************************************/

#undef SAFEMALLOC		/* safe_malloc is not yet initailized */

#include "mysys_priv.h"
#include "m_string.h"
#include <ctype.h>
#include "m_ctype.h"
#include <my_dir.h>

char *defaults_extra_file=0;

/* Which directories are searched for options (and in which order) */

const char *default_directories[]= {
#ifdef _WIN32
"C:/",
#else
"/etc/",
#endif
#ifdef DATADIR
DATADIR,
#endif
"",					/* Place for defaults_extra_dir */
#ifndef _WIN32
"~/",
#endif
NullS,
};

#define default_ext	".cnf"		/* extension for config file */
#ifdef _WIN32
#include <winbase.h>
#define windows_ext	".ini"
#endif

static my_bool search_default_file(DYNAMIC_ARRAY *args,MEM_ROOT *alloc,
				   const char *dir, const char *config_file,
				   const char *ext, TYPELIB *group);


void load_defaults(const char *conf_file, const char **groups,
		   int *argc, char ***argv)
{
  DYNAMIC_ARRAY args;
  const char **dirs, *forced_default_file;
  TYPELIB group;
  my_bool found_print_defaults=0;
  uint args_used=0;
  MEM_ROOT alloc;
  char *ptr,**res;
  DBUG_ENTER("load_defaults");

  init_alloc_root(&alloc,128,0);
  if (*argc >= 2 && !strcmp(argv[0][1],"--no-defaults"))
  {
    /* remove the --no-defaults argument and return only the other arguments */
    uint i;
    if (!(ptr=(char*) alloc_root(&alloc,sizeof(alloc)+
				 (*argc + 1)*sizeof(char*))))
      goto err;
    res= (char**) (ptr+sizeof(alloc));
    res[0]= **argv;				/* Copy program name */
    for (i=2 ; i < (uint) *argc ; i++)
      res[i-1]=argv[0][i];
    (*argc)--;
    *argv=res;
    *(MEM_ROOT*) ptr= alloc;			/* Save alloc root for free */
    DBUG_VOID_RETURN;
  }

  /* Check if we want to force the use a specific default file */
  forced_default_file=0;
  if (*argc >= 2)
  {
    if (is_prefix(argv[0][1],"--defaults-file="))
    {
      forced_default_file=strchr(argv[0][1],'=')+1;
      args_used++;
    }
    else if (is_prefix(argv[0][1],"--defaults-extra-file="))
    {
      defaults_extra_file=strchr(argv[0][1],'=')+1;
      args_used++;
    }
  }

  group.count=0;
  group.name= "defaults";
  group.type_names= groups;
  for (; *groups ; groups++)
    group.count++;

  if (my_init_dynamic_array(&args, sizeof(char*),*argc, 32))
    goto err;
  if (forced_default_file)
  {
    if (search_default_file(&args, &alloc, "", forced_default_file, "",
			    &group))
      goto err;
  }
  else if (dirname_length(conf_file))
  {
    if (search_default_file(&args, &alloc, NullS, conf_file, default_ext,
			    &group))
      goto err;
  }
  else
  {
#ifdef _WIN32
    char system_dir[FN_REFLEN];
    GetWindowsDirectory(system_dir,sizeof(system_dir));
    if (search_default_file(&args, &alloc, system_dir, conf_file, windows_ext,
			    &group))
      goto err;
#endif
#if defined(__EMX__) || defined(OS2)
    if (getenv("ETC") &&
        search_default_file(&args, &alloc, getenv("ETC"), conf_file, 
                            default_ext, &group))
      goto err;
#endif
    for (dirs=default_directories ; *dirs; dirs++)
    {
      int error=0;
      if (**dirs)
	error=search_default_file(&args, &alloc, *dirs, conf_file,
				  default_ext, &group);
      else if (defaults_extra_file)
	error=search_default_file(&args, &alloc, NullS, defaults_extra_file,
				  default_ext, &group);
      if (error)
	goto err;
    }
  }
  if (!(ptr=(char*) alloc_root(&alloc,sizeof(alloc)+
			       (args.elements + *argc +1) *sizeof(char*))))
    goto err;
  res= (char**) (ptr+sizeof(alloc));

  /* copy name + found arguments + command line arguments to new array */
  res[0]=argv[0][0];
  memcpy((gptr) (res+1), args.buffer, args.elements*sizeof(char*));
  /* Skipp --defaults-file and --defaults-extra-file */
  (*argc)-= args_used;
  (*argv)+= args_used;

  /* Check if we wan't to see the new argument list */
  if (*argc >= 2 && !strcmp(argv[0][1],"--print-defaults"))
  {
    found_print_defaults=1;
    --*argc; ++*argv;				/* skipp argument */
  }

  memcpy((gptr) (res+1+args.elements), (char*) ((*argv)+1),
	 (*argc-1)*sizeof(char*));
  res[args.elements+ *argc]=0;			/* last null */

  (*argc)+=args.elements;
  *argv= (char**) res;
  *(MEM_ROOT*) ptr= alloc;			/* Save alloc root for free */
  delete_dynamic(&args);
  if (found_print_defaults)
  {
    int i;
    printf("%s would have been started with the following arguments:\n",
	   **argv);
    for (i=1 ; i < *argc ; i++)
      printf("%s ", (*argv)[i]);
    puts("");
    exit(1);
  }
  DBUG_VOID_RETURN;

 err:
  fprintf(stderr,"Program aborted\n");
  exit(1);
}


void free_defaults(char **argv)
{
  MEM_ROOT ptr;
  memcpy_fixed((char*) &ptr,(char *) argv - sizeof(ptr), sizeof(ptr));
  free_root(&ptr,MYF(0));
}


static my_bool search_default_file(DYNAMIC_ARRAY *args, MEM_ROOT *alloc,
				   const char *dir, const char *config_file,
				   const char *ext, TYPELIB *group)
{
  char name[FN_REFLEN+10],buff[4096],*ptr,*end,*value,*tmp;
  FILE *fp;
  uint line=0;
  my_bool read_values= 0, found_group= 0, is_escaped= 0, is_quoted= 0;

  if ((dir ? strlen(dir) : 0 )+strlen(config_file) >= FN_REFLEN-3)
    return 0;					/* Ignore wrong paths */
  if (dir)
  {
    strmov(name,dir);
    convert_dirname(name);
    if (dir[0] == FN_HOMELIB)		/* Add . to filenames in home */
      strcat(name,".");
    strxmov(strend(name),config_file,ext,NullS);
  }
  else
  {
    strmov(name,config_file);
  }
  fn_format(name,name,"","",4);
#if !defined(_WIN32) && !defined(OS2)
  {
    MY_STAT stat_info;
    if (!my_stat(name,&stat_info,MYF(0)))
      return 0;
    if (stat_info.st_mode & S_IWOTH) /* ignore world-writeable files */
    {
      fprintf(stderr, "warning: World-writeable config file %s is ignored\n",
              name);
      return 0;
    }
  }
#endif
  if (!(fp = my_fopen(fn_format(name,name,"","",4),O_RDONLY,MYF(0))))
    return 0;					/* Ignore wrong files */

  while (fgets(buff,sizeof(buff)-1,fp))
  {
    line++;
    /* Ignore comment and empty lines */
    for (ptr=buff ; isspace(*ptr) ; ptr++ );
    if (!is_escaped && (*ptr == '\"' || *ptr== '\''))
    {
      is_quoted= !is_quoted;
      continue;
    }
    if (*ptr == '#' || *ptr == ';' || !*ptr)
      continue;
    is_escaped= (*ptr == '\\');
    if (*ptr == '[')				/* Group name */
    {
      found_group=1;
      if (!(end=(char *) strchr(++ptr,']')))
      {
	fprintf(stderr,
		"error: Wrong group definition in config file: %s at line %d\n",
		name,line);
	goto err;
      }
      for ( ; isspace(end[-1]) ; end--) ;	/* Remove end space */
      end[0]=0;
      read_values=find_type(ptr,group,3) > 0;
      continue;
    }
    if (!found_group)
    {
      fprintf(stderr,
	      "error: Found option without preceding group in config file: %s at line: %d\n",
	      name,line);
      goto err;
    }
    if (!read_values)
      continue;
    if (!(end=value=strchr(ptr,'=')))
      end=strend(ptr);				/* Option without argument */
    for ( ; isspace(end[-1]) ; end--) ;
    if (!value)
    {
      if (!(tmp=alloc_root(alloc,(uint) (end-ptr)+3)))
	goto err;
      strmake(strmov(tmp,"--"),ptr,(uint) (end-ptr));
      if (insert_dynamic(args,(gptr) &tmp))
	goto err;
    }
    else
    {
      /* Remove pre- and end space */
      char *value_end;
      for (value++ ; isspace(*value); value++) ;
      value_end=strend(value);
      for ( ; isspace(value_end[-1]) ; value_end--) ;
      /* remove possible quotes */
      if (*value == '\'' || *value == '\"')
      {
        value++;
        if (value_end[-1] == '\'' || value_end[-1] == '\"')
          value_end--;
      }
      if (value_end < value)			/* Empty string */
	value_end=value;
      if (!(tmp=alloc_root(alloc,(uint) (end-ptr)+3 +
			   (uint) (value_end-value)+1)))
	goto err;
      if (insert_dynamic(args,(gptr) &tmp))
	goto err;
      ptr=strnmov(strmov(tmp,"--"),ptr,(uint) (end-ptr));
      *ptr++= '=';
      for ( ; value != value_end; value++)
      {
	if (*value == '\\' && value != value_end-1)
	{
	  switch(*++value) {
	  case 'n':
	    *ptr++='\n';
	    break;
	  case 't':
	    *ptr++= '\t';
	    break;
	  case 'r':
	    *ptr++ = '\r';
	    break;
	  case 'b':
	    *ptr++ = '\b';
	    break;
	  case 's':
	    *ptr++= ' ';			/* space */
	    break;
    case '\"':
      *ptr++= '\"';
      break;
    case '\'':
      *ptr++= '\'';
      break;
	  case '\\':
	    *ptr++= '\\';
	    break;
	  default:				/* Unknown; Keep '\' */
	    *ptr++= '\\';
	    *ptr++= *value;
	    break;
	  }
	}
	else
	  *ptr++= *value;
      }
      *ptr=0;
    }
  }
  my_fclose(fp,MYF(0));
  return(0);

 err:
  my_fclose(fp,MYF(0));
  return 1;
}


void print_defaults(const char *conf_file, const char **groups)
{
#ifdef _WIN32
  bool have_ext=fn_ext(conf_file)[0] != 0;
#endif
  char name[FN_REFLEN];
  const char **dirs;
  puts("\nDefault options are read from the following files in the given order:");

  if (dirname_length(conf_file))
    fputs(conf_file,stdout);
  else
  {
#ifdef _WIN32
    GetWindowsDirectory(name,sizeof(name));
    printf("%s\\%s%s ",name,conf_file,have_ext ? "" : windows_ext);
#endif
#if defined(__EMX__) || defined(OS2)
    if (getenv("ETC"))
      printf("%s\\%s%s ", getenv("ETC"), conf_file, default_ext);
#endif
    for (dirs=default_directories ; *dirs; dirs++)
    {
      if (**dirs)
	strmov(name,*dirs);
      else if (defaults_extra_file)
	strmov(name,defaults_extra_file);
      else
	continue;
      convert_dirname(name);
      if (name[0] == FN_HOMELIB)	/* Add . to filenames in home */
	strcat(name,".");
      strxmov(strend(name),conf_file,default_ext," ",NullS);
      fputs(name,stdout);
    }
    puts("");
  }
  fputs("The following groups are read:",stdout);
  for ( ; *groups ; groups++)
  {
    fputc(' ',stdout);
    fputs(*groups,stdout);
  }
  puts("\nThe following options may be given as the first argument:\n\
--print-defaults	Print the program argument list and exit\n\
--no-defaults		Don't read default options from any options file\n\
--defaults-file=#	Only read default options from the given file #\n\
--defaults-extra-file=# Read this file after the global files are read");
}

