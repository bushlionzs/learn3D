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

/* password checking routines */
/*****************************************************************************
  The main idea is that no password are sent between client & server on
  connection and that no password are saved in mysql in a decodable form.

  On connection a random string is generated and sent to the client.
  The client generates a new string with a random generator inited with
  the hash values from the password and the sent string.
  This 'check' string is sent to the server where it is compared with
  a string generated from the stored hash_value of the password and the
  random string.

  The password is saved (in user.password) by using the PASSWORD() function in
  mysql.

  Example:
    update user set password=PASSWORD("hello") where user="test"
  This saves a hashed number as a string in the password field.
*****************************************************************************/

#include <my_global.h>
#include <my_sys.h>
#include <m_string.h>
#include <sha1.h>
#include "mysql.h"


void randominit(struct rand_struct *rand_st,ulong seed1, ulong seed2)
{						/* For mysql 3.21.# */
#ifdef HAVE_purify
  bzero((char*) rand_st,sizeof(*rand_st));		/* Avoid UMC varnings */
#endif
  rand_st->max_value= 0x3FFFFFFFL;
  rand_st->max_value_dbl=(double) rand_st->max_value;
  rand_st->seed1=seed1%rand_st->max_value ;
  rand_st->seed2=seed2%rand_st->max_value;
}

static void old_randominit(struct rand_struct *rand_st,ulong seed1)
{						/* For mysql 3.20.# */
  rand_st->max_value= 0x01FFFFFFL;
  rand_st->max_value_dbl=(double) rand_st->max_value;
  seed1%=rand_st->max_value;
  rand_st->seed1=seed1 ; rand_st->seed2=seed1/2;
}

double rnd(struct rand_struct *rand_st)
{
  rand_st->seed1=(rand_st->seed1*3+rand_st->seed2) % rand_st->max_value;
  rand_st->seed2=(rand_st->seed1+rand_st->seed2+33) % rand_st->max_value;
  return (((double) rand_st->seed1)/rand_st->max_value_dbl);
}

void hash_password(ulong *result, const char *password, size_t len)
{
  register ulong nr=1345345333L, add=7, nr2=0x12345671L;
  ulong tmp;
  const char *password_end= password + len;
  for (; password < password_end; password++)
  {
    if (*password == ' ' || *password == '\t')
      continue;			/* skipp space in password */
    tmp= (ulong) (uchar) *password;
    nr^= (((nr & 63)+add)*tmp)+ (nr << 8);
    nr2+=(nr2 << 8) ^ nr;
    add+=tmp;
  }
  result[0]=nr & (((ulong) 1L << 31) -1L); /* Don't use sign bit (str2int) */;
  result[1]=nr2 & (((ulong) 1L << 31) -1L);
  return;
}

static inline unsigned int char_val(char X)
{
  return (uint) (X >= '0' && X <= '9' ? X-'0' :
		 X >= 'A' && X <= 'Z' ? X-'A'+10 :
		 X-'a'+10);
}

/*
 * Genererate a new message based on message and password
 * The same thing is done in client and server and the results are checked.
 */

/* scramble for 4.1 servers
 * Code based on php_nysqlnd_scramble function from PHP's mysqlnd extension,
 * written by Andrey Hristov (andrey@php.net)
 * License: PHP License 3.0
 */
void my_crypt(unsigned char *buffer, const unsigned char *s1, const unsigned char *s2, size_t len)
{
	const unsigned char *s1_end= s1 + len;
	while (s1 < s1_end) {
		*buffer++= *s1++ ^ *s2++;
	}
}

void my_scramble_41(const unsigned char *buffer, const char *scramble, const char *password)
{
	MYSQL_SHA1_CTX context;
	unsigned char sha1[SHA1_MAX_LENGTH];
	unsigned char sha2[SHA1_MAX_LENGTH];
	

	/* Phase 1: hash password */
	MYSQL_SHA1Init(&context);
	MYSQL_SHA1Update(&context, (unsigned char *)password, strlen((char *)password));
	MYSQL_SHA1Final(sha1, &context);

	/* Phase 2: hash sha1 */
	MYSQL_SHA1Init(&context);
	MYSQL_SHA1Update(&context, (unsigned char*)sha1, SHA1_MAX_LENGTH);
	MYSQL_SHA1Final(sha2, &context);

	/* Phase 3: hash scramble + sha2 */
	MYSQL_SHA1Init(&context);
	MYSQL_SHA1Update(&context, (unsigned char *)scramble, SCRAMBLE_LENGTH);
	MYSQL_SHA1Update(&context, (unsigned char*)sha2, SHA1_MAX_LENGTH);
	MYSQL_SHA1Final((unsigned char *)buffer, &context);

	/* let's crypt buffer now */
	my_crypt((uchar *)buffer, (const unsigned char *)buffer, (const unsigned  char *)sha1, SHA1_MAX_LENGTH);
}
/* }}} */

void make_scrambled_password(char *to,const char *password)
{
  ulong hash_res[2];
  hash_password(hash_res,password, strlen(password));
  sprintf(to,"%08lx%08lx",hash_res[0],hash_res[1]);
}

/*
** This code assumes that len(password) is divideable with 8 and that
** res is big enough (2 in mysql)
*/

void get_salt_from_password(ulong *res,const char *password)
{
  res[0]=res[1]=0;
  if (password)
  {
    while (*password)
    {
      ulong val=0;
      uint i;
      for (i=0 ; i < 8 ; i++)
	val=(val << 4)+char_val(*password++);
      *res++=val;
    }
  }
  return;
}

void make_password_from_salt(char *to, ulong *hash_res)
{
  sprintf(to,"%08lx%08lx",hash_res[0],hash_res[1]);
}


/*
 * Genererate a new message based on message and password
 * The same thing is done in client and server and the results are checked.
 */
char *scramble_323(char *to, const char *message, const char *password)
{
  struct rand_struct rand_st;
  ulong hash_pass[2], hash_message[2];

  if (password && password[0])
  {
    char extra, *to_start=to;
    const char *end_scramble323= message + SCRAMBLE_LENGTH_323;
    hash_password(hash_pass,password, (uint) strlen(password));
    /* Don't use strlen, could be > SCRAMBLE_LENGTH_323 ! */
    hash_password(hash_message, message, SCRAMBLE_LENGTH_323);
    randominit(&rand_st, hash_pass[0] ^ hash_message[0],
               hash_pass[1] ^ hash_message[1]);
    for (; message < end_scramble323; message++)
      *to++= (char) (floor(rnd(&rand_st) * 31) + 64);
    extra=(char) (floor(rnd(&rand_st) * 31));
    while (to_start != to)
      *(to_start++)^= extra;
  }
  *to= 0;
  return to;
}

my_bool check_scramble(const char *scrambled, const char *message,
		       ulong *hash_pass, my_bool old_ver)
{
  struct rand_struct rand_st;
  ulong hash_message[2];
  char buff[16],*to,extra;			/* Big enough for check */
  const char *pos;

  hash_password(hash_message,message, strlen(message));
  if (old_ver)
    old_randominit(&rand_st,hash_pass[0] ^ hash_message[0]);
  else
    randominit(&rand_st,hash_pass[0] ^ hash_message[0],
	       hash_pass[1] ^ hash_message[1]);
  to=buff;
  for (pos=scrambled ; *pos ; pos++)
    *to++=(char) (floor(rnd(&rand_st)*31)+64);
  if (old_ver)
    extra=0;
  else
    extra=(char) (floor(rnd(&rand_st)*31));
  to=buff;
  while (*scrambled)
  {
    if (*scrambled++ != (char) (*to++ ^ extra))
      return 1;					/* Wrong password */
  }
  return 0;
}
