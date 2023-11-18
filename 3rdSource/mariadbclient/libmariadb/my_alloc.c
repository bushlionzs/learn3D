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

/* Routines to handle mallocing of results which will be freed the same time */

#include <my_global.h>
#include <my_sys.h>
#include <m_string.h>

void init_alloc_root(MEM_ROOT *mem_root, size_t block_size, size_t pre_alloc_size)
{
  mem_root->free= mem_root->used= mem_root->pre_alloc= 0;
  mem_root->min_malloc=32;
  mem_root->block_size= (block_size-MALLOC_OVERHEAD-sizeof(USED_MEM)+8);
  mem_root->error_handler=0;
  mem_root->block_num= 4;
  mem_root->first_block_usage= 0;
#if !(defined(HAVE_purify) && defined(EXTRA_DEBUG))
  if (pre_alloc_size)
  {
    if ((mem_root->free = mem_root->pre_alloc=
	 (USED_MEM*) my_malloc(pre_alloc_size+ ALIGN_SIZE(sizeof(USED_MEM)),
			       MYF(0))))
    {
      mem_root->free->size=pre_alloc_size+ALIGN_SIZE(sizeof(USED_MEM));
      mem_root->free->left=pre_alloc_size;
      mem_root->free->next=0;
    }
  }
#endif
}

gptr alloc_root(MEM_ROOT *mem_root, size_t Size)
{
#if defined(HAVE_purify) && defined(EXTRA_DEBUG)
  reg1 USED_MEM *next;
  Size+=ALIGN_SIZE(sizeof(USED_MEM));

  if (!(next = (USED_MEM*) my_malloc(Size,MYF(MY_WME))))
  {
    if (mem_root->error_handler)
      (*mem_root->error_handler)();
    return((gptr) 0);				/* purecov: inspected */
  }
  next->next=mem_root->used;
  mem_root->used=next;
  return (gptr) (((char*) next)+ALIGN_SIZE(sizeof(USED_MEM)));
#else
  size_t get_size,max_left;
  gptr point;
  reg1 USED_MEM *next= 0;
  reg2 USED_MEM **prev;

  Size= ALIGN_SIZE(Size);
  max_left=0;

  if ((*(prev= &mem_root->free)))
  {
    if ((*prev)->left < Size &&
        mem_root->first_block_usage++ >= 16 &&
        (*prev)->left < 4096)
    {
      next= *prev;
      *prev= next->next;
      next->next= mem_root->used;
      mem_root->used= next;
      mem_root->first_block_usage= 0;
    }
    for (next= *prev; next && next->left < Size; next= next->next)
      prev= &next->next;
  }

  if (! next)
  {						/* Time to alloc new block */
    get_size= MAX(Size+ALIGN_SIZE(sizeof(USED_MEM)),
              (mem_root->block_size & ~1) * (mem_root->block_num >> 2));

    if (!(next = (USED_MEM*) my_malloc(get_size,MYF(MY_WME))))
    {
      if (mem_root->error_handler)
	(*mem_root->error_handler)();
      return((gptr) 0);				/* purecov: inspected */
    }
    mem_root->block_num++;
    next->next= *prev;
    next->size= get_size;
    next->left= get_size-ALIGN_SIZE(sizeof(USED_MEM));
    *prev=next;
  }
  point= (gptr) ((char*) next+ (next->size-next->left));
  if ((next->left-= Size) < mem_root->min_malloc)
  {						/* Full block */
    *prev=next->next;				/* Remove block from list */
    next->next=mem_root->used;
    mem_root->used=next;
    mem_root->first_block_usage= 0;
  }
  return(point);
#endif
}

	/* deallocate everything used by alloc_root */

void free_root(MEM_ROOT *root, myf MyFlags)
{
  reg1 USED_MEM *next,*old;
  DBUG_ENTER("free_root");

  if (!root)
    DBUG_VOID_RETURN; /* purecov: inspected */
  if (!(MyFlags & MY_KEEP_PREALLOC))
    root->pre_alloc=0;

  for ( next=root->used; next ;)
  {
    old=next; next= next->next ;
    if (old != root->pre_alloc)
      my_free(old);
  }
  for (next= root->free ; next ; )
  {
    old=next; next= next->next ;
    if (old != root->pre_alloc)
      my_free(old);
  }
  root->used=root->free=0;
  if (root->pre_alloc)
  {
    root->free=root->pre_alloc;
    root->free->left=root->pre_alloc->size-ALIGN_SIZE(sizeof(USED_MEM));
    root->free->next=0;
  }
  root->block_num= 4;
  root->first_block_usage= 0;
  DBUG_VOID_RETURN;
}


char *strdup_root(MEM_ROOT *root,const char *str)
{
  size_t len= strlen(str)+1;
  char *pos;
  if ((pos=alloc_root(root,len)))
    memcpy(pos,str,len);
  return pos;
}


char *memdup_root(MEM_ROOT *root, const char *str, size_t len)
{
  char *pos;
  if ((pos=alloc_root(root,len)))
    memcpy(pos,str,len);
  return pos;
}
