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

/*
  Defines: llstr();

  llstr(value, buff);

  This function saves a longlong value in a buffer and returns the pointer to
  the buffer.  This is useful when trying to portable print longlong
  variables with printf() as there is no usable printf() standard one can use.
*/


#include <my_global.h>
#include "m_string.h"

char *llstr(longlong value,char *buff)
{
  longlong2str(value,buff,-10);
  return buff;
}
