---------------------------------------------------
-- File: 700207_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700207_CSP_FUBENTYPE				= 	0
x700207_CSP_SCRIPTID				=	1
x700207_CSP_TICKCOUNT				= 	2
x700207_CSP_FROMSCENEID				= 	3
x700207_CSP_ISCLOSING				= 	4
x700207_CSP_LEAVECOUNTDOWN			= 	5
x700207_CSP_TEAMID					=	6
x700207_CSP_BACKSCENEX       		=   7
x700207_CSP_BACKSCENEZ      		=   8
x700207_CSP_FUBENLEVEL			=	9
x700207_CSP_KILLCOUNT				=	20
x700207_CSP_HP_BOSS1				= 	21
x700207_CSP_OBJID_BOSS1				=   22
x700207_CSP_FIND_NPC				=	23    --// 设是否找到范文虎 NPC
x700207_CSP_CREATEFLAG              =   24
x700207_CSP_AREA_TIMER				=	25
x700207_CSP_MONSTERCREATE			= 	26
x700207_CSP_BOSS2_ID				=	27
x700207_CSP_BOSS3_ID				=	28
x700207_CSP_BOSS4_ID				=	29
x700207_CSP_FUBEN_SCENE_ID			=	30

x700207_CSP_RANDBOSS_ID				=	31

x700207_CSP_OBJID_AREA				=	40


x700207_CSP_B_GETBUFF_START			=	234
x700207_CSP_HUMAN_COUNT				=	240
x700207_CSP_OBJID_START				=	241
x700207_CSP_GUID_START              =   248



------------------------Scene System Setting -----------------------------------

x700207_g_ScriptId 					= 700207

x700207_g_BackScene					=	{50,150,250,350}
---------------------------- specail for fuben ------------
x700207_g_Buff1						=	13500 					--火防
x700207_g_Buff2						=	13501                   --恝性半小时

x700207_g_BuffImpact1				=	450                     --火伤害减少
x700207_g_AreaTimer                 =   3*1000                    --事件区定时器

x700207_g_RandomBossRate			=	0


------------------------- list -----------------------------------------                                        }

x700207_g_SubmitNPC                 =   { type =25029,guid= 150529,x = 44, z=55, facedir =0, title="" }

--BOSS类型
x700207_g_BossCreate				=	{
											{levelmin =50, levelmax=100, name ="黄河帮主陈友详",  type= 27758,  x=101, z=16, r=0,  ai=5, aiscript=545, count=0, facedir = 0, title = "", patrolid = -1,flag = 0},
											
                                            {levelmin =50, levelmax=100, name ="盐帮坛主秦方云",   type= 27759,  x=22, z=102, r=0,  ai=5, aiscript=546, count=1, facedir = 0, title = "", patrolid = -1,flag = 1},
                                           
                                            {levelmin =50, levelmax=100, name ="明教红螺堂主楚元",  type= 27760,  x=92, z=78,  r=0,  ai=9, aiscript=547, count=1, facedir = 0, title = "", patrolid = 0,flag = 2},
                                          
                                            {levelmin =50, levelmax=100, name ="独眼石人",          type= 27761,  x=48, z=55,  r=0,  ai=18, aiscript=548, count=1, facedir = 0, title = "", patrolid = -1,flag = 3},
                                           
											

										}

x700207_g_MonsterCreate				=	{
											{levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=68.58,  z=8.19,   r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=68.55,  z=13.45,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=68.28,  z=19.41,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=64.38,  z=8.06,   r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=64.42,  z=13.54,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=64.31,  z=19.27,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=59.77,  z=8.39,   r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=59.47,  z=13.52,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=59.56,  z=19.26,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=55.37,  z=8.45,   r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=55.16,  z=13.62,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=55.04,  z=19.29,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=18.95,  z=12.28,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=13.63,  z=12.61,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=8.87,   z=12.68,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=18.56,  z=17.61,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=18.56,  z=22.78,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=13.37,  z=17.25,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=13.22,  z=22.56,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=8.94,   z=17.44,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=9.11,   z=22.86,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=17.74,  z=95.51,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=14.21,  z=99.66,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=12.68,  z=105.32, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=14.54,  z=109.12, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=16.88,  z=113.2,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=21.63,  z=113.76, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=26.29,  z=113.37, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=28.6,   z=109.31, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=29.86,  z=105.16, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=28.42,  z=100.68, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=26.68,  z=96.52,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=22.2,   z=95.97,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=63.83,  z=113.83, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=63.73,  z=117.67, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=67.64,  z=118.09, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=68.07,  z=114.01, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=72,     z=118.07, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=75.87,  z=118.04, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=75.84,  z=113.74, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=79.8,   z=114.09, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=79.73,  z=117.93, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=83.98,  z=117.95, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=105.65, z=112.74, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=105.75, z=117.39, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=109.73, z=117.05, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=109.94, z=112.77, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=113.83, z=117.11, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=113.94, z=113.53, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=117.44, z=116.72, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=117.55, z=113.41, r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=112.22, z=73.1,   r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=117.92, z=73.39,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=112.24, z=67,     r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=117.58, z=66.96,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=112.44, z=61.78,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=117.6,  z=61.96,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=117.51, z=56.13,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=112.42, z=55.96,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=112.28, z=51.32,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=118.07, z=51.43,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=117.68, z=45.65,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=112.05, z=45.82,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=88.8,   z=44.47,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=90.15,  z=50.97,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=93.02,  z=58.56,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=95.93,  z=66.6,   r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=75.34,  z=72.33,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=77.5,   z=78.29,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=85.11,  z=77.27,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=91.9,   z=74.98,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=98.08,  z=72.67,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=72.24,  z=65,     r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=69.39,  z=57.82,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=66.76,  z=50.68,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=69.96,  z=44.9,   r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=77.4,   z=41.42,  r=0,  ai=9, aiscript=543, count=1, facedir = 0, title = ""},
                                                                       
                                           
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=42.02,  z=14.06,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=28.46,  z=14.58,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=34.51,  z=22.59,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=18.22,  z=39.7,   r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=10.25,  z=39.88,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=18.17,  z=51.57,  r=0,  ai=9, aiscript=-1,  count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=9.69,   z=51.9,   r=0,  ai=9, aiscript=-1,  count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=18.87,  z=64.12,  r=0,  ai=9, aiscript=-1,  count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=10.37,  z=64.8,   r=0,  ai=9, aiscript=-1,  count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=19.27,  z=101.13, r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=19.69,  z=109.1,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=25.83,  z=104.66, r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=71.66,  z=113.57, r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=83.97,  z=113.9,  r=0,  ai=9, aiscript=-1,  count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=111.4,  z=94.87,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=115.06, z=94.76,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=118.93, z=94.92,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=118.78, z=87.24,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=115.34, z=87.19,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=111.52, z=87.69,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=114.98, z=70.18,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=114.96, z=59.16,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="黄河帮众",   type= 27755,  x=115.03, z=48.28,  r=0,  ai=9, aiscript=-1,  count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=72.47,  z=50.61,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=84.19,  z=46.62,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=90.93,  z=65.13,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                            {levelmin =50, levelmax=100, name ="盐帮",       type= 27756,  x=79.96,  z=71.72,  r=0,  ai=9, aiscript=544, count=1, facedir = 0, title = ""},
                                                                       
                                          
										}

x700207_g_MonsterCreate2            =   {
                                            {levelmin =50, levelmax=100, name ="小忍者",   type= 27757,  x=101, z=16, r=4,  ai=9, aiscript=-1, count=10, facedir = 0, title = ""},
                                           
                                        }



-- 随机最终boss
x700207_g_Boss_Random_Create		=	{
                                            {levelmin =20, levelmax=100, name ="隐藏boss6",   type= 25140, x = 41, z=44, ai=9, aiscript=634,  facedir = 0, title = "",flag=0},
                                           

										}




x700207_g_NpcType					=   25050					--范文虎

x700207_g_NpcCreate					=	{
											{	hash=1, type=x700207_g_NpcType,	 	x=69,	z=97,	ai=3, aiscript=-1,objid = 150004,campid = -1,facedir =0, title="" },
										}
-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700207_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

end


-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700207_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id

	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700207_CSP_HUMAN_COUNT, humancount);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		SetFubenData_Param(sceneId, x700207_CSP_OBJID_START+i, humanId);
	end

	SetFubenData_Param(sceneId, x700207_CSP_RANDBOSS_ID, -1 )
	
	local nCreateFlag = GetFubenData_Param(sceneId, x700207_CSP_CREATEFLAG )
    
	if nCreateFlag == 0 then

		x700207_CreateBoss( sceneId )
		x700207_CreateMonster( sceneId )
		x700207_CreateNpc( sceneId )

		SetFubenData_Param(sceneId, x700207_CSP_CREATEFLAG,1 )

	end
	
		
end


-----------------------------------------------------------
--*********************************************************
--_EnterTick  :  副本心跳
--*********************************************************
-----------------------------------------------------------

function x700207_EnterTick(sceneId, nowTickCount)

	if nowTickCount >= 2 then
		--检查BOSS1是否半血
		local MonsterCreated = GetFubenData_Param(sceneId,x700207_CSP_MONSTERCREATE)
		if MonsterCreated == 0 then
			local nHalfHP = GetFubenData_Param(sceneId, x700207_CSP_HP_BOSS1 )
			local nObjId = GetFubenData_Param(sceneId, x700207_CSP_OBJID_BOSS1 )
			nHalfHP = nHalfHP / 2
			local nMonsterCount = GetMonsterCount( sceneId )
			for i=0,nMonsterCount -1 do
				local objId = GetMonsterObjID( sceneId, i )
				if objId == nObjId then
					local hp = GetHp( sceneId, objId )
					if hp < nHalfHP then
						local x,z = GetMonsterPosition(sceneId,objId)
						x700207_CreateMonster2(sceneId,x,z)
						SetFubenData_Param(sceneId,x700207_CSP_MONSTERCREATE,1)
					end

				end
			end
		else
			local nHalfHP = GetFubenData_Param(sceneId, x700207_CSP_HP_BOSS1 )
			local nObjId = GetFubenData_Param(sceneId, x700207_CSP_OBJID_BOSS1 )
			nHalfHP = nHalfHP / 2
			local nMonsterCount = GetMonsterCount( sceneId )
			for i=0,nMonsterCount -1 do
				local objId = GetMonsterObjID( sceneId, i )
				if objId == nObjId then
					local hp = GetHp( sceneId, objId )
					if hp > nHalfHP then
						SetFubenData_Param(sceneId,x700207_CSP_MONSTERCREATE,0)
					end

				end
			end
		end
	end

end	




---------------------------------------------------------------------------------------------------
--创建BOSS
---------------------------------------------------------------------------------------------------
function x700207_CreateBoss(sceneId)

    local copyscenelevel = GetFubenData_Param(sceneId, x700207_CSP_FUBENLEVEL ) ;

	for i, item in x700207_g_BossCreate do --创建Boss

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		    local objid = 0
			if item.title~="" then
				objid = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700207_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
			else
				objid = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700207_g_ScriptId, -1, 21,-1,item.facedir)
			
			end
			if item.patrolid>=0 then
				SetPatrolId(sceneId, objid, item.patrolid)
				
			end

            if item.flag == 0  then
			    local nFullHp = GetHp( sceneId, objid )
			    SetFubenData_Param(sceneId, x700207_CSP_HP_BOSS1, nFullHp)
			    SetFubenData_Param(sceneId, x700207_CSP_OBJID_BOSS1, objid)
		    elseif item.flag == 1  then
				 SetFubenData_Param(sceneId, x700207_CSP_BOSS2_ID, objid)
		    elseif item.flag == 2  then
				 SetFubenData_Param(sceneId, x700207_CSP_BOSS3_ID, objid)
		    elseif item.flag == 3  then
				 SetFubenData_Param(sceneId, x700207_CSP_BOSS4_ID, objid)
			end

        end
	end

end

---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700207_CreateMonster(sceneId)

    local copyscenelevel = GetFubenData_Param(sceneId, x700207_CSP_FUBENLEVEL ) ;

	for i, item in x700207_g_MonsterCreate do  --创建普通小怪

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz

				if item.title~="" then
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir,  "",item.title)
				else
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				
				end
			end
        end
	end

end


---------------------------------------------------------------------------------------------------
--创建Monster2
---------------------------------------------------------------------------------------------------
function x700207_CreateMonster2(sceneId,x,z)  --创建召唤小怪

    local copyscenelevel = GetFubenData_Param(sceneId, x700207_CSP_FUBENLEVEL ) ;

	for i, item in x700207_g_MonsterCreate2 do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do
				if item.title~="" then
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir, "", item.title)
				else
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
				
				end
			end
        end
	end

end

function x700207_CreateNpc( sceneId )
	for i, item in x700207_g_NpcCreate do
		if item.title~="" then
			CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, item.objid,-1,-1,item.facedir,  "",item.title);
		else
			CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, item.objid,-1,-1,item.facedir);
		
		end
	end
end


function x700207_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700207_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700207_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	if nDieCount== x700207_NeedKillMonster_Count then
		--x700207_OnAllMonsterDead( sceneId) 
	end


	local objId2 = GetFubenData_Param(sceneId, x700207_CSP_BOSS2_ID)
	local objId4 = GetFubenData_Param(sceneId, x700207_CSP_BOSS4_ID)

	if objId2 == selfId then
		SetFubenData_Param(sceneId, x700207_CSP_BOSS2_ID, -1)
		local humancount = GetFuben_PlayerCount(sceneId);

		for i = 0, humancount - 1 do


			local humanId = GetFuben_PlayerObjId(sceneId, i);	--取得当前场景里人的objId
			SendSpecificImpactToUnit(sceneId, humanId,humanId,humanId, x700207_g_Buff1,0 )
			
		end
	end

	if objId4 == selfId then
		--x700207_CreateSubmitNpc( sceneId)
		SetFubenData_Param(sceneId, x700207_CSP_BOSS4_ID, -1)
		local bCreateRandom = x700207_CreateRandomBoss(sceneId)
		if bCreateRandom==0 then
			x700207_OnGameCompleted(sceneId)
		end

--		--//--------------------------- 世界喊话 Start--------------------
--			--杀死boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700207_CSP_TICKCOUNT)
--
--			local nowTime = x700207_g_TickTime* nowTickCount;
--
--			local nMinute = floor(nowTime/60)
--			local nSec = mod(nowTime,60)
--
--				
--			local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--			-------- if killed by pet -----------------
--			local nKillerType = GetObjType(sceneId, killerId)
--			--PrintStr(nKillerType)
--			if nKillerType== 3 then
--				local nOwnerId = GetOwnerID(sceneId, killerId)
--				strPlayerName = GetName(sceneId, nOwnerId)
--			end
--			--------- end -------------------------------
--
--			local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--			local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件
--
--			
--			
--			--LuaAllScenceM2Wrold (sceneId,"#R武林震惊，#G"..strPlayerName.."#R带领的队伍仅用了#G"..strKillTime.."#R就击败了黄河坞中的各路武林人士，见到了传说中的“财宝”！", 0, 1)
--			
--			
--			--//--------------------------- 世界喊话 end----------------------
	end

	local objRandomBossId = GetFubenData_Param(sceneId, x700207_CSP_RANDBOSS_ID ) ; 

	if objRandomBossId>=0 then
		if objRandomBossId== selfId then
			SetFubenData_Param(sceneId, x700207_CSP_RANDBOSS_ID, -1 )
			x700207_OnGameCompleted(sceneId)
		end
	end



	
end

function x700207_OnGameCompleted(sceneId)
	
	local humancount = GetFuben_PlayerCount(sceneId);
	for	j = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, j);
		local str = "勇士们，你们获得了最终的胜利！回到王城接受大家赞许的目光吧！";
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end

	x700207_CreateSubmitNpc( sceneId)
end

function x700207_CreateRandomBoss(sceneId)


	local rate = random(0,100)/100;
	if rate>= x700207_g_RandomBossRate then
		return 0;
	end

	local nFlag = random(0,0)

	

	local copyscenelevel = GetFubenData_Param(sceneId, x700207_CSP_FUBENLEVEL ) ;


	
	local bCreated =0;
	
	for i, item in x700207_g_Boss_Random_Create do  --创建随机Boss
		if item.flag == nFlag then
			if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
				
				local nRet = 0
				
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, item.x,item.z, item.ai, item.aiscript, x700207_g_ScriptId, -1, 21,-1,item.facedir, "", item.title)
				else
					nRet = CreateMonster(sceneId, item.type, item.x,item.z, item.ai, item.aiscript, x700207_g_ScriptId, -1, 21,-1,item.facedir)
				
				end

				SetFubenData_Param(sceneId, x700207_CSP_RANDBOSS_ID, nRet ) ; 
				bCreated = 1;
			end
		end
	end

	if bCreated>0 then
		local humancount = GetFuben_PlayerCount(sceneId);
		for	i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
			local str = "隐藏Boss出现";
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId, humanId);
		end
	end

	return bCreated;

end

function x700207_OnAllMonsterDead( sceneId)
	x700207_CreateSubmitNpc( sceneId)
end

function x700207_CreateSubmitNpc( sceneId)
	if x700207_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700207_g_SubmitNPC.type, x700207_g_SubmitNPC.x, x700207_g_SubmitNPC.z, 3, -1, -1, x700207_g_SubmitNPC.guid, -1,-1,x700207_g_SubmitNPC.facedir,  "",x700207_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700207_g_SubmitNPC.type, x700207_g_SubmitNPC.x, x700207_g_SubmitNPC.z, 3, -1, -1, x700207_g_SubmitNPC.guid, -1,-1,x700207_g_SubmitNPC.facedir)
	
	end
end



---------------------------------------------------------------------------------------------------
--任务完成
---------------------------------------------------------------------------------------------------
function x700207_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
end

---------------------------------------------------------------------------------------------------
--物品改变
---------------------------------------------------------------------------------------------------
function x700207_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end

---------------------------------------------------------------------------------------------------
--进入区域事件
---------------------------------------------------------------------------------------------------


---------------------------------------------------------------------------------------------------
function x700207_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )


     --检查玩家GUID
    local nFind = 1
    local guid = GetPlayerGUID( sceneId,selfId )

    --SetFubenData_Param(sceneId,x700207_CSP_GUID_START+6,guid)
    --guid = GetFubenData_Param(sceneId,x700207_CSP_GUID_START+6)

   -- for n=0, 5 do
    --    local paramidx = x700207_CSP_GUID_START + n
    --    local nGUID = GetFubenData_Param(sceneId, paramidx  )
--
     --   if nGUID == guid then
      --      nFind = 1
      --      break
     --   end
    --end


    --not player
    if nFind == 0 then
        return
    end



	local index = x700207_CSP_OBJID_AREA
	for i=0,5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    if objid == selfId then

	    	SetFubenData_Param(sceneId, idx, selfId )
			SetFubenData_Param(sceneId, idx+1, zoneId )

	    	return
	    elseif objid == -1 then

	        SetFubenData_Param(sceneId, idx, selfId )
	        SetFubenData_Param(sceneId, idx+1, zoneId )
	        return
	    end
	end

end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700207_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )


    local index = x700207_CSP_OBJID_AREA
	for i=0,5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    local zoneId = GetFubenData_Param(sceneId, idx + 1 )
	    if objid == selfId then
	        SetFubenData_Param(sceneId, idx, -1 )
	        SetFubenData_Param(sceneId, idx+1, -1 )
	    end
	end
end

---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
function x700207_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	
end



function x700207_OnAreaTimer( sceneId )

--	local ct = GetCurrentTime()
-- 	if ct - x700207_g_PROTECTINFO.StartTime >= 1000  then
-- 	    x700207_g_PROTECTINFO.StartTime  = ct
-- 	else
-- 	    return
-- 	end

	

--	local bAreaTimer = GetFubenData_Param(sceneId, x700207_CSP_AREA_TIMER)
--	if bAreaTimer == -1 then
--	    return
--	end

	

    local index = x700207_CSP_OBJID_AREA
	for i=0,5 do
		local idx = index+i*2
	    local objid = GetFubenData_Param(sceneId, idx )
	    local zoneid = GetFubenData_Param(sceneId, idx + 1 )
		
	    if objid ~= -1 then

            --检查玩家是否在线或是玩家是否死亡，如果都不是，那么，执行火烧减血逻辑CZG 2008-12-1
            local ErrorCode = CallScriptFunction( FUBEN_COMMON_SCRIPT_CALL, "IsPlayerErrorState", sceneId, objid)
            if ErrorCode == 0 then

				local nLevel  = GetLevel( sceneId, objid )
                local hurt = 20
				if nLevel>=60 then
					hurt =40
				end
                if zoneid ~= 0 then
					
                    hurt = 50

					if nLevel>=60 then
						hurt =100
					end
                end

                local haveImpact = IsHaveSpecificImpact( sceneId, objid, x700207_g_Buff1 )
				
                if haveImpact == 1 then
                    --hurt = hurt - x700207_g_BuffImpact1
					hurt = floor(hurt*0.1)	
                end

                local havehp = GetHp( sceneId, objid )
                local hp = havehp - hurt
                if hp < 0 then
                    hp = havehp -1
                    hp = -hp
                else
                    hp = -hurt
                end

                SetHp(sceneId,objid, hp )
            end
        end
	end
end


---------------------------------------------------------------------------------------------------
--定点使用物品任务
---------------------------------------------------------------------------------------------------
function x700207_PositionUseItem( sceneId, selfId, BagIndex, impactId )
end


---------------------------------------------------------------------------------------------------
--采集任务，打开采集点事件
---------------------------------------------------------------------------------------------------
function x700207_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
end

---------------------------------------------------------------------------------------------------
--回收
---------------------------------------------------------------------------------------------------
function x700207_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
end

---------------------------------------------------------------------------------------------------
--打开
---------------------------------------------------------------------------------------------------
function x700207_OnProcOver( sceneId, selfId, targetId )
end

---------------------------------------------------------------------------------------------------
--打开后检查
---------------------------------------------------------------------------------------------------
function x700207_OpenCheck( sceneId, selfId, targetId )
end

function x700207_CloseTimer( sceneId, TimerIndex )
--	if TimerIndex ~= -1 then
--		StopTimer(sceneId, TimerIndex)
--	end
--	SetFubenData_Param(sceneId, x700207_CSP_AREA_TIMER, -1) ;
end







