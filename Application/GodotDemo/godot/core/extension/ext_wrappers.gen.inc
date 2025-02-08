
#ifndef GDEXTENSION_WRAPPERS_GEN_H
#define GDEXTENSION_WRAPPERS_GEN_H

/* Extension Wrapper 0 Arguments */

#define EXBIND0( m_name) \
GDVIRTUAL0_REQUIRED(_##m_name)\
virtual void m_name()  override { \
    \
    GDVIRTUAL_CALL(_##m_name);\
    return;\
}

#define EXBIND0R(m_ret,  m_name) \
GDVIRTUAL0R_REQUIRED(m_ret, _##m_name)\
virtual m_ret m_name()  override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, ret);\
    return ret;\
\
}

#define EXBIND0C( m_name) \
GDVIRTUAL0C_REQUIRED(_##m_name)\
virtual void m_name() const override { \
    \
    GDVIRTUAL_CALL(_##m_name);\
    return;\
}

#define EXBIND0RC(m_ret,  m_name) \
GDVIRTUAL0RC_REQUIRED(m_ret, _##m_name)\
virtual m_ret m_name() const override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, ret);\
    return ret;\
\
}

/* Extension Wrapper 1 Arguments */

#define EXBIND1( m_name, m_type1) \
GDVIRTUAL1_REQUIRED(_##m_name, m_type1)\
virtual void m_name(m_type1 arg1)  override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1);\
    return;\
}

#define EXBIND1R(m_ret,  m_name, m_type1) \
GDVIRTUAL1R_REQUIRED(m_ret, _##m_name, m_type1)\
virtual m_ret m_name(m_type1 arg1)  override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, ret);\
    return ret;\
\
}

#define EXBIND1C( m_name, m_type1) \
GDVIRTUAL1C_REQUIRED(_##m_name, m_type1)\
virtual void m_name(m_type1 arg1) const override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1);\
    return;\
}

#define EXBIND1RC(m_ret,  m_name, m_type1) \
GDVIRTUAL1RC_REQUIRED(m_ret, _##m_name, m_type1)\
virtual m_ret m_name(m_type1 arg1) const override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, ret);\
    return ret;\
\
}

/* Extension Wrapper 2 Arguments */

#define EXBIND2( m_name, m_type1, m_type2) \
GDVIRTUAL2_REQUIRED(_##m_name, m_type1, m_type2)\
virtual void m_name(m_type1 arg1, m_type2 arg2)  override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2);\
    return;\
}

#define EXBIND2R(m_ret,  m_name, m_type1, m_type2) \
GDVIRTUAL2R_REQUIRED(m_ret, _##m_name, m_type1, m_type2)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2)  override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, ret);\
    return ret;\
\
}

#define EXBIND2C( m_name, m_type1, m_type2) \
GDVIRTUAL2C_REQUIRED(_##m_name, m_type1, m_type2)\
virtual void m_name(m_type1 arg1, m_type2 arg2) const override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2);\
    return;\
}

#define EXBIND2RC(m_ret,  m_name, m_type1, m_type2) \
GDVIRTUAL2RC_REQUIRED(m_ret, _##m_name, m_type1, m_type2)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2) const override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, ret);\
    return ret;\
\
}

/* Extension Wrapper 3 Arguments */

#define EXBIND3( m_name, m_type1, m_type2, m_type3) \
GDVIRTUAL3_REQUIRED(_##m_name, m_type1, m_type2, m_type3)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3)  override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3);\
    return;\
}

#define EXBIND3R(m_ret,  m_name, m_type1, m_type2, m_type3) \
GDVIRTUAL3R_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3)  override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, ret);\
    return ret;\
\
}

#define EXBIND3C( m_name, m_type1, m_type2, m_type3) \
GDVIRTUAL3C_REQUIRED(_##m_name, m_type1, m_type2, m_type3)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3) const override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3);\
    return;\
}

#define EXBIND3RC(m_ret,  m_name, m_type1, m_type2, m_type3) \
GDVIRTUAL3RC_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3) const override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, ret);\
    return ret;\
\
}

/* Extension Wrapper 4 Arguments */

#define EXBIND4( m_name, m_type1, m_type2, m_type3, m_type4) \
GDVIRTUAL4_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4)  override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4);\
    return;\
}

#define EXBIND4R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4) \
GDVIRTUAL4R_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4)  override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, ret);\
    return ret;\
\
}

#define EXBIND4C( m_name, m_type1, m_type2, m_type3, m_type4) \
GDVIRTUAL4C_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4) const override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4);\
    return;\
}

#define EXBIND4RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4) \
GDVIRTUAL4RC_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4) const override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, ret);\
    return ret;\
\
}

/* Extension Wrapper 5 Arguments */

#define EXBIND5( m_name, m_type1, m_type2, m_type3, m_type4, m_type5) \
GDVIRTUAL5_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5)  override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5);\
    return;\
}

#define EXBIND5R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5) \
GDVIRTUAL5R_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5)  override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, ret);\
    return ret;\
\
}

#define EXBIND5C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5) \
GDVIRTUAL5C_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5) const override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5);\
    return;\
}

#define EXBIND5RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5) \
GDVIRTUAL5RC_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5) const override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, ret);\
    return ret;\
\
}

/* Extension Wrapper 6 Arguments */

#define EXBIND6( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6) \
GDVIRTUAL6_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6)  override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6);\
    return;\
}

#define EXBIND6R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6) \
GDVIRTUAL6R_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6)  override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, ret);\
    return ret;\
\
}

#define EXBIND6C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6) \
GDVIRTUAL6C_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6) const override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6);\
    return;\
}

#define EXBIND6RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6) \
GDVIRTUAL6RC_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6) const override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, ret);\
    return ret;\
\
}

/* Extension Wrapper 7 Arguments */

#define EXBIND7( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7) \
GDVIRTUAL7_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7)  override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7);\
    return;\
}

#define EXBIND7R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7) \
GDVIRTUAL7R_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7)  override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, ret);\
    return ret;\
\
}

#define EXBIND7C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7) \
GDVIRTUAL7C_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7) const override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7);\
    return;\
}

#define EXBIND7RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7) \
GDVIRTUAL7RC_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7) const override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, ret);\
    return ret;\
\
}

/* Extension Wrapper 8 Arguments */

#define EXBIND8( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8) \
GDVIRTUAL8_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8)  override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);\
    return;\
}

#define EXBIND8R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8) \
GDVIRTUAL8R_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8)  override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, ret);\
    return ret;\
\
}

#define EXBIND8C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8) \
GDVIRTUAL8C_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8) const override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);\
    return;\
}

#define EXBIND8RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8) \
GDVIRTUAL8RC_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8) const override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, ret);\
    return ret;\
\
}

/* Extension Wrapper 9 Arguments */

#define EXBIND9( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9) \
GDVIRTUAL9_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9)  override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);\
    return;\
}

#define EXBIND9R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9) \
GDVIRTUAL9R_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9)  override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, ret);\
    return ret;\
\
}

#define EXBIND9C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9) \
GDVIRTUAL9C_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9) const override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);\
    return;\
}

#define EXBIND9RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9) \
GDVIRTUAL9RC_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9) const override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, ret);\
    return ret;\
\
}

/* Extension Wrapper 10 Arguments */

#define EXBIND10( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10) \
GDVIRTUAL10_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10)  override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);\
    return;\
}

#define EXBIND10R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10) \
GDVIRTUAL10R_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10)  override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, ret);\
    return ret;\
\
}

#define EXBIND10C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10) \
GDVIRTUAL10C_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10) const override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);\
    return;\
}

#define EXBIND10RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10) \
GDVIRTUAL10RC_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10) const override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, ret);\
    return ret;\
\
}

/* Extension Wrapper 11 Arguments */

#define EXBIND11( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11) \
GDVIRTUAL11_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11)  override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);\
    return;\
}

#define EXBIND11R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11) \
GDVIRTUAL11R_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11)  override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, ret);\
    return ret;\
\
}

#define EXBIND11C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11) \
GDVIRTUAL11C_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11) const override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);\
    return;\
}

#define EXBIND11RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11) \
GDVIRTUAL11RC_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11) const override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, ret);\
    return ret;\
\
}

/* Extension Wrapper 12 Arguments */

#define EXBIND12( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12) \
GDVIRTUAL12_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12)  override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);\
    return;\
}

#define EXBIND12R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12) \
GDVIRTUAL12R_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12)  override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, ret);\
    return ret;\
\
}

#define EXBIND12C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12) \
GDVIRTUAL12C_REQUIRED(_##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12)\
virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12) const override { \
    \
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);\
    return;\
}

#define EXBIND12RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12) \
GDVIRTUAL12RC_REQUIRED(m_ret, _##m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12)\
virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12) const override { \
    m_ret ret; ZeroInitializer<m_ret>::initialize(ret);\
\
    GDVIRTUAL_CALL(_##m_name, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, ret);\
    return ret;\
\
}

/* Module Wrapper 0 Arguments */

#define MODBIND0( m_name) \
virtual void _##m_name() ; \
_FORCE_INLINE_ virtual void m_name()  override { \
     _##m_name();\
}

#define MODBIND0R(m_ret,  m_name) \
virtual m_ret _##m_name() ; \
_FORCE_INLINE_ virtual m_ret m_name()  override { \
    return _##m_name();\
}

#define MODBIND0C( m_name) \
virtual void _##m_name() const; \
_FORCE_INLINE_ virtual void m_name() const override { \
     _##m_name();\
}

#define MODBIND0RC(m_ret,  m_name) \
virtual m_ret _##m_name() const; \
_FORCE_INLINE_ virtual m_ret m_name() const override { \
    return _##m_name();\
}

/* Module Wrapper 1 Arguments */

#define MODBIND1( m_name, m_type1) \
virtual void _##m_name(m_type1 arg1) ; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1)  override { \
     _##m_name(arg1);\
}

#define MODBIND1R(m_ret,  m_name, m_type1) \
virtual m_ret _##m_name(m_type1 arg1) ; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1)  override { \
    return _##m_name(arg1);\
}

#define MODBIND1C( m_name, m_type1) \
virtual void _##m_name(m_type1 arg1) const; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1) const override { \
     _##m_name(arg1);\
}

#define MODBIND1RC(m_ret,  m_name, m_type1) \
virtual m_ret _##m_name(m_type1 arg1) const; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1) const override { \
    return _##m_name(arg1);\
}

/* Module Wrapper 2 Arguments */

#define MODBIND2( m_name, m_type1, m_type2) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2) ; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2)  override { \
     _##m_name(arg1, arg2);\
}

#define MODBIND2R(m_ret,  m_name, m_type1, m_type2) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2) ; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2)  override { \
    return _##m_name(arg1, arg2);\
}

#define MODBIND2C( m_name, m_type1, m_type2) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2) const; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2) const override { \
     _##m_name(arg1, arg2);\
}

#define MODBIND2RC(m_ret,  m_name, m_type1, m_type2) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2) const; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2) const override { \
    return _##m_name(arg1, arg2);\
}

/* Module Wrapper 3 Arguments */

#define MODBIND3( m_name, m_type1, m_type2, m_type3) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3) ; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3)  override { \
     _##m_name(arg1, arg2, arg3);\
}

#define MODBIND3R(m_ret,  m_name, m_type1, m_type2, m_type3) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3) ; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3)  override { \
    return _##m_name(arg1, arg2, arg3);\
}

#define MODBIND3C( m_name, m_type1, m_type2, m_type3) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3) const; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3) const override { \
     _##m_name(arg1, arg2, arg3);\
}

#define MODBIND3RC(m_ret,  m_name, m_type1, m_type2, m_type3) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3) const; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3) const override { \
    return _##m_name(arg1, arg2, arg3);\
}

/* Module Wrapper 4 Arguments */

#define MODBIND4( m_name, m_type1, m_type2, m_type3, m_type4) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4) ; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4)  override { \
     _##m_name(arg1, arg2, arg3, arg4);\
}

#define MODBIND4R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4) ; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4)  override { \
    return _##m_name(arg1, arg2, arg3, arg4);\
}

#define MODBIND4C( m_name, m_type1, m_type2, m_type3, m_type4) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4) const; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4) const override { \
     _##m_name(arg1, arg2, arg3, arg4);\
}

#define MODBIND4RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4) const; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4) const override { \
    return _##m_name(arg1, arg2, arg3, arg4);\
}

/* Module Wrapper 5 Arguments */

#define MODBIND5( m_name, m_type1, m_type2, m_type3, m_type4, m_type5) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5) ; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5)  override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5);\
}

#define MODBIND5R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5) ; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5)  override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5);\
}

#define MODBIND5C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5) const; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5) const override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5);\
}

#define MODBIND5RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5) const; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5) const override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5);\
}

/* Module Wrapper 6 Arguments */

#define MODBIND6( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6) ; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6)  override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6);\
}

#define MODBIND6R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6) ; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6)  override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6);\
}

#define MODBIND6C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6) const; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6) const override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6);\
}

#define MODBIND6RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6) const; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6) const override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6);\
}

/* Module Wrapper 7 Arguments */

#define MODBIND7( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7) ; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7)  override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7);\
}

#define MODBIND7R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7) ; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7)  override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7);\
}

#define MODBIND7C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7) const; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7) const override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7);\
}

#define MODBIND7RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7) const; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7) const override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7);\
}

/* Module Wrapper 8 Arguments */

#define MODBIND8( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8) ; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8)  override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);\
}

#define MODBIND8R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8) ; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8)  override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);\
}

#define MODBIND8C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8) const; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8) const override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);\
}

#define MODBIND8RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8) const; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8) const override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);\
}

/* Module Wrapper 9 Arguments */

#define MODBIND9( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9) ; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9)  override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);\
}

#define MODBIND9R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9) ; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9)  override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);\
}

#define MODBIND9C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9) const; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9) const override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);\
}

#define MODBIND9RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9) const; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9) const override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);\
}

/* Module Wrapper 10 Arguments */

#define MODBIND10( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10) ; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10)  override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);\
}

#define MODBIND10R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10) ; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10)  override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);\
}

#define MODBIND10C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10) const; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10) const override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);\
}

#define MODBIND10RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10) const; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10) const override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);\
}

/* Module Wrapper 11 Arguments */

#define MODBIND11( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11) ; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11)  override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);\
}

#define MODBIND11R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11) ; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11)  override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);\
}

#define MODBIND11C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11) const; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11) const override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);\
}

#define MODBIND11RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11) const; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11) const override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11);\
}

/* Module Wrapper 12 Arguments */

#define MODBIND12( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12) ; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12)  override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);\
}

#define MODBIND12R(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12) ; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12)  override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);\
}

#define MODBIND12C( m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12) \
virtual void _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12) const; \
_FORCE_INLINE_ virtual void m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12) const override { \
     _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);\
}

#define MODBIND12RC(m_ret,  m_name, m_type1, m_type2, m_type3, m_type4, m_type5, m_type6, m_type7, m_type8, m_type9, m_type10, m_type11, m_type12) \
virtual m_ret _##m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12) const; \
_FORCE_INLINE_ virtual m_ret m_name(m_type1 arg1, m_type2 arg2, m_type3 arg3, m_type4 arg4, m_type5 arg5, m_type6 arg6, m_type7 arg7, m_type8 arg8, m_type9 arg9, m_type10 arg10, m_type11 arg11, m_type12 arg12) const override { \
    return _##m_name(arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12);\
}

#endif
