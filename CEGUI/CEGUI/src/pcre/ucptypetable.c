

#include "ucp.h"



typedef struct {
  const char *name;
  int value;
} ucp_type_table;

static ucp_type_table utt[] = {
  { "C",  128 + ucp_C },
  { "Cc", ucp_Cc },
  { "Cf", ucp_Cf },
  { "Cn", ucp_Cn },
  { "Co", ucp_Co },
  { "Cs", ucp_Cs },
  { "L",  128 + ucp_L },
  { "Ll", ucp_Ll },
  { "Lm", ucp_Lm },
  { "Lo", ucp_Lo },
  { "Lt", ucp_Lt },
  { "Lu", ucp_Lu },
  { "M",  128 + ucp_M },
  { "Mc", ucp_Mc },
  { "Me", ucp_Me },
  { "Mn", ucp_Mn },
  { "N",  128 + ucp_N },
  { "Nd", ucp_Nd },
  { "Nl", ucp_Nl },
  { "No", ucp_No },
  { "P",  128 + ucp_P },
  { "Pc", ucp_Pc },
  { "Pd", ucp_Pd },
  { "Pe", ucp_Pe },
  { "Pf", ucp_Pf },
  { "Pi", ucp_Pi },
  { "Po", ucp_Po },
  { "Ps", ucp_Ps },
  { "S",  128 + ucp_S },
  { "Sc", ucp_Sc },
  { "Sk", ucp_Sk },
  { "Sm", ucp_Sm },
  { "So", ucp_So },
  { "Z",  128 + ucp_Z },
  { "Zl", ucp_Zl },
  { "Zp", ucp_Zp },
  { "Zs", ucp_Zs }
};


