#ifndef __TAB_DEFINE_H__
#define __TAB_DEFINE_H__


#include "TypeDefine.h"

#ifdef __GLSERVER__

#include "TabDefine_GL.h"
#include "TabDefine_Share.h"

#elif defined __MAPSERVER__

#include "TabDefine_Map.h"
#include "TabDefine_Map_Misc.h"
#include "TabDefine_Map_Monster.h"
#include "TabDefine_Map_Pet.h"
#include "TabDefine_Map_Quest.h"
#include "TabDefine_Map_Skill.h"
#include "TabDefine_Share.h"

#endif


#endif