---------------------------------------------------
-- File: 700203_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700203_CSP_FUBENTYPE				= 	0
x700203_CSP_SCRIPTID				=	1
x700203_CSP_TICKCOUNT				= 	2
x700203_CSP_BACKSCENEID				= 	3
x700203_CSP_ISCLOSING				= 	4
x700203_CSP_LEAVECOUNTDOWN			= 	5
x700203_CSP_TEAMID					=	6
x700203_CSP_TICKTIME       			=   7
x700203_CSP_HOLDTIME      			=   8
x700203_CSP_FUBENLEVEL				=	9

x700203_CSP_KILLCOUNT				=	20
x700203_CSP_BOSS1_ID				=	21
x700203_CSP_BOSS2_ID				=	22
x700203_CSP_NPC_ID					=	23
x700203_CSP_B_PAO_OVER				=	24
x700203_CSP_PAO_STATUS				=	25
x700203_CSP_FUBEN_SCENE_ID			=	26
x700203_CSP_PAO_TICKCOUNT			=	27



x700203_CSP_B_GETBONUS_START		=	230
x700203_CSP_HUMAN_COUNT				=	240
x700203_CSP_OBJID_START				=	241
x700203_CSP_GUID_START              =   248


------------------------Scene System Setting -----------------------------------

x700203_g_ScriptId 					= 700203
x700203_g_PaoTaiHoldTime			=	15*12					-- 蘿怢奀潔
x700203_g_LimitTotalHoldTime        =   720                    	--萵掛褫眕湔魂腔奀潔ㄗ等弇ㄩ棒杅ㄘ,�蝜�森奀潔善賸ㄛ寀�恄鬅姣慲妍�

------------------------- list -----------------------------------------


x700203_g_SubmitNPC                 =   { type =25071,guid= 150549,x = 35, z=31, facedir =0, title="" }     -- 淕ょ腔npc
x700203_g_SubmitNPC1                =   { type =25072,guid= 150549,x = 35, z=31, facedir =0, title="" }	 -- ぢ擭腔朻勀��npc	
x700203_g_NpcGroup                  =   {
                                            {   type = 25034,x=22,z=107,ai=3,aiscript = 0,guid=150534,facedir =0, title=""},
                                        }

--BOSS濬倰
--BOSS濬倰
x700203_g_BossCreate                =   {
                                            {levelmin =40, levelmax=100, name ="鳶蘿",   type= 27765,   x=63, z=60, r=0,  ai=7, aiscript=0,   facedir = 0, title = "",flag =0},
                                          

                                            {levelmin =40, levelmax=100, name ="陳祂蔚濂",   type= 27766,   x=37, z=32,  r=0,  ai=18, aiscript=503, facedir = 0, title = "",flag =1},
                                           

                                        }

--ぱ籵墅斐膘陓洘ㄛ婦漪弇离ㄛ摯呴儂毓峓
x700203_g_MonsterCreate1              =   {
                                            
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=30.48, z=89.44,  r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=31.83, z=90.09,  r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=28.85, z=91.83,  r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=30,    z=92.26,  r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=36.25, z=84,     r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=36.52, z=87,     r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=37.46, z=81.38,  r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=34.97, z=84.26,  r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                                                       
                                           
                                                                       
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=37.78, z=43.43,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=41.34, z=44.57,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=35.91, z=49.08,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=39.1,  z=48.01,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=29.62, z=61.33,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=33.65, z=61.77,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=30.76, z=67.4,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=33.21, z=65.59,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=47.24, z=92.59,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=48.1,  z=91.01,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=49.13, z=89.42,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=51.43, z=94.84,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=52.5,  z=93.21,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=53.28, z=91.62,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=67.21, z=99.7,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=68.01, z=97.03,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=70.89, z=100.65,  r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=71.38, z=98.93,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=72.32, z=96.65,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=83.5,  z=89.47,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=85.54, z=89.35,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=83.83, z=86.8,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=86.77, z=85.21,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=86.08, z=83.6,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=92.6,  z=72.53,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=89.46, z=72.05,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=92.33, z=69.02,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=89.5,  z=68.65,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=92.44, z=66.3,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=89.62, z=65.91,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=81.89, z=54.74,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=82.74, z=53.2,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=82.68, z=51.31,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=79.95, z=53.26,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=56.67, z=48.05,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=58.41, z=48.98,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=56.88, z=50.99,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=54.7,  z=49.18,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=54.78, z=51.42,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=48.37, z=61.43,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=48.28, z=63.87,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=48.53, z=58.34,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=47.04, z=60.28,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=47.15, z=64.39,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=54.6,  z=73.38,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=54.88, z=76.58,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=56.44, z=78.56,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=55.35, z=71.56,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=56.79, z=76.23,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=56.46, z=74.1,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=57.2,  z=70.6,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=58.43, z=79.27,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂祭條",   type= 27762,  x=53.08, z=74.89,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                                                       
                                           
                                            {levelmin =39, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=55.89, z=75.18, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=57.7,  z=72.49, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=58.02, z=77.14, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=47.23, z=62.62, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=56.06, z=49.71, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=90.97, z=67.74, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=85.67, z=87.07, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=69.74, z=98.61, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=50.06, z=92.44, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=31.21, z=63.83, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =39, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=38.49, z=46.13, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                                                       
                                           
										}

										
x700203_g_MonsterCreate2	=			{
                                            
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=37.78, z=43.43,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=41.34, z=44.57,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=35.91, z=49.08,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=39.1,  z=48.01,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=29.62, z=61.33,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=33.65, z=61.77,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=30.76, z=67.4,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=33.21, z=65.59,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=47.24, z=92.59,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=48.1,  z=91.01,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=49.13, z=89.42,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=51.43, z=94.84,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=52.5,  z=93.21,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=53.28, z=91.62,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=67.21, z=99.7,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=68.01, z=97.03,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=70.89, z=100.65,  r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=71.38, z=98.93,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=72.32, z=96.65,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=83.5,  z=89.47,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=85.54, z=89.35,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=83.83, z=86.8,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=86.77, z=85.21,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=86.08, z=83.6,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=92.6,  z=72.53,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=89.46, z=72.05,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=92.33, z=69.02,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=89.5,  z=68.65,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=92.44, z=66.3,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=89.62, z=65.91,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=81.89, z=54.74,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=82.74, z=53.2,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=82.68, z=51.31,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=79.95, z=53.26,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=56.67, z=48.05,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=58.41, z=48.98,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=56.88, z=50.99,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=54.7,  z=49.18,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=54.78, z=51.42,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=48.37, z=61.43,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=48.28, z=63.87,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=48.53, z=58.34,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=47.04, z=60.28,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=47.15, z=64.39,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=54.6,  z=73.38,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=54.88, z=76.58,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=56.44, z=78.56,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=55.35, z=71.56,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=56.79, z=76.23,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=56.46, z=74.1,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=57.2,  z=70.6,    r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=58.43, z=79.27,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂祭條",   type= 27762,  x=53.08, z=74.89,   r=0,  ai=9, aiscript=501, count=1, facedir = 0, title = ""},


                                            {levelmin =40, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=55.89, z=75.18, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=57.7,  z=72.49, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=58.02, z=77.14, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=47.23, z=62.62, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=56.06, z=49.71, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=90.97, z=67.74, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=85.67, z=87.07, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=69.74, z=98.61, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=50.06, z=92.44, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=31.21, z=63.83, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂楊呇",   type= 27763,  x=38.49, z=46.13, r=0,  ai=9, aiscript=502, count=1, facedir = 0, title = ""},

                                          
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=30.48, z=89.44,  r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=31.83, z=90.09,  r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=28.85, z=91.83,  r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=30,    z=92.26,  r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=36.25, z=84,     r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=36.52, z=87,     r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=37.46, z=81.38,  r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},
                                            {levelmin =40, levelmax=100, name ="陳祂鳶Л條",   type= 27764,  x=34.97, z=84.26,  r=0,  ai=9, aiscript=500, count=1, facedir = 0, title = ""},

                                        }

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700203_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

end



-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  絞萵掛斐膘傖髡奀ㄛ 羲宎芃墅睿npc
--*********************************************************
-----------------------------------------------------------
function x700203_OnFubenSceneCreated( sceneId )
	
	x700203_CreateBoss( sceneId,0 )
    x700203_CreateMonster1( sceneId )
	x700203_CreateNpc(sceneId )
		
end

function x700203_EnterTick( sceneId,nowTickCount)
-------------------------------------
	if nowTickCount == 2 then
	    local nTalkNpcId = GetFubenData_Param(sceneId, x700203_CSP_NPC_ID ) ;
			if nTalkNpcId>0 then
				NpcTalk(sceneId, nTalkNpcId, "饒�瘍挩�婓刓階殤扢賸鳶蘿ㄛ斕蠅辦�打搎椊�ㄐ",  -1)
			end
	end

	--萵掛數奀ん
	local bPaoTimeOver = GetFubenData_Param(sceneId, x700203_CSP_B_PAO_OVER ) ;
	if bPaoTimeOver==0 then
		-- �蝜�蘿怢奀潔善
		if nowTickCount >= x700203_g_PaoTaiHoldTime then
			
			bPaoTimeOver = 1;
			
			x700203_OnHuoPaoOver(sceneId, 1)
		end
	end

	if bPaoTimeOver==0 then
		SetFubenData_Param(sceneId, x700203_CSP_HOLDTIME,x700203_g_PaoTaiHoldTime)
	else
		SetFubenData_Param(sceneId, x700203_CSP_HOLDTIME,x700203_g_LimitTotalHoldTime)
	end
end

function x700203_OnHuoPaoOver(sceneId, nStatus)
	if nStatus ~= 1 and nStatus~=2  then
		return -1;
	
	end

	local objId1 = GetFubenData_Param(sceneId, x700203_CSP_BOSS1_ID);
	if objId1>=0 then
		DeleteMonster( sceneId, objId1);
	--else
		--return
	end

	SetFubenData_Param(sceneId, x700203_CSP_PAO_STATUS, nStatus )  --// 1:閉奀, 2: 俇傖
	SetFubenData_Param(sceneId, x700203_CSP_B_PAO_OVER, 1 ) ;
	
	local nowTick = GetFubenData_Param(sceneId, x700203_CSP_TICKCOUNT);
	SetFubenData_Param(sceneId,x700203_CSP_PAO_TICKCOUNT,nowTick);

	local str="";

	if nStatus==1 then
		str	= "斕帤夔傖髡郯砦鳶蘿馴僻ㄐ"
		x700203_CreateBoss(sceneId, 1)
	else
		str = "鳶蘿傖髡腔掩殘障賸ㄐ"
		x700203_CreateMonster2(sceneId)
		x700203_CreateBoss(sceneId, 1)

	end

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
		if nStatus==1 then
			CallScriptFunction(UTILITY_SCRIPT, "PlayEffect", sceneId, humanId, 7 )
		end
	end
end




---------------------------------------------------------------------------------------------------
--斐膘BOSS
---------------------------------------------------------------------------------------------------
function x700203_CreateBoss(sceneId, flag)

    local copyscenelevel = GetFubenData_Param(sceneId, x700203_CSP_FUBENLEVEL ) ;

	for i, item in x700203_g_BossCreate do --斐膘Boss

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		    if item.flag == flag then
				local nRet = 0
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700203_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700203_g_ScriptId, -1, 21,-1,item.facedir)
				
				end

				if item.flag ==0 then
					SetFubenData_Param(sceneId, x700203_CSP_BOSS1_ID,nRet  )
				elseif item.flag ==1 then
					SetFubenData_Param(sceneId, x700203_CSP_BOSS2_ID,nRet  )
				end
			end
        end
	end

end

---------------------------------------------------------------------------------------------------
--斐膘蘿怢秏囮眳ヶMonster
---------------------------------------------------------------------------------------------------
function x700203_CreateMonster1(sceneId)

    local copyscenelevel = GetFubenData_Param(sceneId, x700203_CSP_FUBENLEVEL ) ;

	for i, item in x700203_g_MonsterCreate1 do

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
--斐膘蘿怢苤奀眳綴Monster
---------------------------------------------------------------------------------------------------
function x700203_CreateMonster2(sceneId)

    local copyscenelevel = GetFubenData_Param(sceneId, x700203_CSP_FUBENLEVEL ) ;

	for i, item in x700203_g_MonsterCreate2 do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz

				if item.title~="" then
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir, "",item.title)
				else
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, -1, -1, 21,-1,item.facedir)
					
				end
			end
        end
	end

end

-------------------------
--***********************
--CreateNpc
--***********************
-------------------------
function x700203_CreateNpc(sceneId )

    for i, item in x700203_g_NpcGroup do
        local nRet = 0
		if item.title~="" then
			nRet = CreateMonster( sceneId,item.type,item.x,item.z,item.ai,item.aiscript,-1,item.guid,-1,-1,item.facedir, "",item.title)
		else
			nRet = CreateMonster( sceneId,item.type,item.x,item.z,item.ai,item.aiscript,-1,item.guid,-1,-1,item.facedir)
		
		end
		SetFubenData_Param(sceneId, x700203_CSP_NPC_ID,nRet ) ;
    end
end


function x700203_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700203_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700203_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	

	if nDieCount== x700203_NeedKillMonster_Count then
		--x700203_OnAllMonsterDead( sceneId) 
	end

	local objId1 = GetFubenData_Param(sceneId, x700203_CSP_BOSS1_ID);
	local objId2 = GetFubenData_Param(sceneId, x700203_CSP_BOSS2_ID);

	

	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700203_CSP_BOSS1_ID, -1);

		x700203_OnHuoPaoOver(sceneId,2)
		return
	end

	if objId2>0 then
		if objId2 == selfId then
			SetFubenData_Param(sceneId, x700203_CSP_BOSS2_ID, -1);
			
			x700203_CreateSubmitNpc( sceneId)
			x700203_ShowTipsToAll(sceneId, "萵掛俇傖")

			--//--------------------------- 岍賜滌趕 Start--------------------
			--伀侚boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700203_CSP_TICKCOUNT)
--
--			local nowTime = x700203_g_TickTime* nowTickCount;
--
--			local nMinute = floor(nowTime/60)
--			local nSec = mod(nowTime,60)
--
--				
--			local strPlayerName = GetName(sceneId, killerId)     -- 伀侚墅昜腔俙模靡趼
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
--			local strKillTime = format("%d煦%d鏃", nMinute, nSec) -- 伀侚壽昢腔岈璃
--
--			
--			
--			--LuaAllScenceM2Wrold (sceneId,"#R俙模#G"..strPlayerName.."#R睿坻腔勦衭蚚奀#G"..strKillTime.."#R伀侚賸"..strBossName, 0, 1)
			
			
			
			--//--------------------------- 岍賜滌趕 end----------------------

		end
	end
end

function x700203_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId);

	--籵眭俙模
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId,str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, humanId);
	end
end

function x700203_OnAllMonsterDead( sceneId)
	
end

function x700203_CreateSubmitNpc( sceneId)

	 local nStatus = GetFubenData_Param(sceneId, x700203_CSP_PAO_STATUS )
	 if nStatus== 1 then
		if x700203_g_SubmitNPC1.title~="" then
			CreateMonster(sceneId, x700203_g_SubmitNPC1.type, x700203_g_SubmitNPC1.x, x700203_g_SubmitNPC1.z, 3, 0, -1, x700203_g_SubmitNPC1.guid, -1,-1,x700203_g_SubmitNPC1.facedir,  "",x700203_g_SubmitNPC1.title)
		else
			CreateMonster(sceneId, x700203_g_SubmitNPC1.type, x700203_g_SubmitNPC1.x, x700203_g_SubmitNPC1.z, 3, 0, -1, x700203_g_SubmitNPC1.guid, -1,-1,x700203_g_SubmitNPC1.facedir)
		
		end
	 elseif nStatus==2 then
		if x700203_g_SubmitNPC.title~="" then
			CreateMonster(sceneId, x700203_g_SubmitNPC.type, x700203_g_SubmitNPC.x, x700203_g_SubmitNPC.z, 3, 0, -1, x700203_g_SubmitNPC.guid, -1,-1,x700203_g_SubmitNPC.facedir,  "",x700203_g_SubmitNPC.title)
		else
			CreateMonster(sceneId, x700203_g_SubmitNPC.type, x700203_g_SubmitNPC.x, x700203_g_SubmitNPC.z, 3, 0, -1, x700203_g_SubmitNPC.guid, -1,-1,x700203_g_SubmitNPC.facedir)
		
		end
	 end
end

