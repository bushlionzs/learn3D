




#include "ucp.h"               
#include "ucpinternal.h"       
#include "ucptable.c"          







static int
ucp_findchar(const int c, int *type_ptr, int *case_ptr)
{
cnode *node = ucp_table;
register int cc = c;
int case_offset;

for (;;)
  {
  register int d = node->f1 | ((node->f0 & f0_chhmask) << 16);
  if (cc == d) break;
  if (cc < d)
    {
    if ((node->f0 & f0_leftexists) == 0) return -1;
    node ++;
    }
  else
    {
    register int roffset = (node->f2 & f2_rightmask) >> f2_rightshift;
    if (roffset == 0) return -1;
    node += 1 << (roffset - 1);
    }
  }

switch ((*type_ptr = ((node->f0 & f0_typemask) >> f0_typeshift)))
  {
  case ucp_Cc:
  case ucp_Cf:
  case ucp_Cn:
  case ucp_Co:
  case ucp_Cs:
  return ucp_C;
  break;

  case ucp_Ll:
  case ucp_Lu:
  case_offset = node->f2 & f2_casemask;
  if ((case_offset & 0x0100) != 0) case_offset |= 0xfffff000;
  *case_ptr = (case_offset == 0)? 0 : cc + case_offset;
  return ucp_L;

  case ucp_Lm:
  case ucp_Lo:
  case ucp_Lt:
  *case_ptr = 0;
  return ucp_L;
  break;

  case ucp_Mc:
  case ucp_Me:
  case ucp_Mn:
  return ucp_M;
  break;

  case ucp_Nd:
  case ucp_Nl:
  case ucp_No:
  return ucp_N;
  break;

  case ucp_Pc:
  case ucp_Pd:
  case ucp_Pe:
  case ucp_Pf:
  case ucp_Pi:
  case ucp_Ps:
  case ucp_Po:
  return ucp_P;
  break;

  case ucp_Sc:
  case ucp_Sk:
  case ucp_Sm:
  case ucp_So:
  return ucp_S;
  break;

  case ucp_Zl:
  case ucp_Zp:
  case ucp_Zs:
  return ucp_Z;
  break;

  default:         
  return -1;
  break;
  }
}


