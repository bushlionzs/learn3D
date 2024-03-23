---------------------------------------------------
-- File: 700022_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700022_CSP_FUBENTYPE				= 	0
x700022_CSP_SCRIPTID				=	1
x700022_CSP_TICKCOUNT				= 	2
x700022_CSP_FROMSCENEID				= 	3
x700022_CSP_ISCLOSING				= 	4
x700022_CSP_LEAVECOUNTDOWN			= 	5
x700022_CSP_TEAMID					=	6
x700022_CSP_BACKSCENEX       		=   7
x700022_CSP_BACKSCENEZ      		=   8
x700022_CSP_FUBENLEVEL				=	9
x700022_CSP_FUBEN_KIND				=	16  --现仅针对轮回台副本
x700022_CSP_XINSHOU_FLAG			=	17 --是否为新手副本
x700022_CSP_KILLCOUNT				=	20
x700022_CSP_FUBEN_SCENE_ID			=	21

x700022_CSP_NPC_ID					=	22
x700022_CSP_CURRENTSTEP				=	23
x700022_CSP_CURRENTSTEP_TICKCOUNT	=	24
x700022_CSP_MONSTER_COUNT			=	25

x700022_CSP_FUBENLEVEL_DUP			=	27

x700022_CSP_TWO_TYPE_START			=	30
x700022_CSP_THREE_TYPE_START		=	35

x700022_CSP_BOSS_ID					=	40
x700022_CSP_BOSS_ID2				=	41
x700022_CSP_BOSS_ID3				=	42
x700022_CSP_BOSS_ID4				=	43
x700022_CSP_DELMON_NUM				=	50	--删除怪的数目

x700022_CSP_RAPID_MONSTER_START		=	60	--快捷怪的起始ID
x700022_CSP_RAPID_MONSTER_END		=	63	--共四个快捷怪

x700022_CSP_GATHER_START_ID		=	200	--是否已采集 6个


x700022_CSP_XINSHOU_LEVEL			=	221 --是否为新手副本等级

x700022_CSP_FINISH	=					229

x700022_CSP_HUMAN_TALKPARAM_START	=	230
x700022_CSP_HUMAN_COUNT				=	240
x700022_CSP_OBJID_START				=	241

x700022_CSP_NEXT_SCENE				=   247
x700022_CSP_GUID_START              =   248
x700022_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型
x700022_CSP_FUBEN_MODE				=   255 --0-轮回台（经验）、1-轮回台（声望）、2-轮回台（天赋80级以上）!!
------------------------Scene System Setting -----------------------------------

x700022_g_ScriptId 					= 700022 
---------------------------- special for fuben -----------------------------
x700022_g_nTextCount				= 4
x700022_g_NpcTalkText				= { "它们会从四面八方涌来","出现的怪物要及时杀掉","不要手软，勇士！","它们的出现威胁到王国的安危！"}

x700022_g_TimeDriverList			= {2,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,1,1}

x700022_g_nGrowpointType			=   548

x700022_Min_HelpLevel				=	30
x700022_Max_HelpLevel				=	49

x700022_g_MonsterTab				=	{ }  --1 tick 为 5秒
------------------------- Output Text ----------------------------------
--11150	1级增加EXP获得	领取经验的倍数	5
--11151	2级增加EXP获得	领取经验的倍数	7
--11152	3级增加EXP获得	领取经验的倍数	9
--11153	4级增加EXP获得	领取经验的倍数	11
--11154	5级增加EXP获得	领取经验的倍数	13
--11155	6级增加EXP获得	领取经验的倍数	15
--11156	7级增加EXP获得	领取经验的倍数	17
--11157	8级增加EXP获得	领取经验的倍数	19
--11158	9级增加EXP获得	领取经验的倍数	21
--11159	10级增加EXP获得	领取经验的倍数	23

x700022_g_WuxingBuffExp           	= 	{  	--悟性BUFF增加的经验权数
											{ buffId =11150, weight = 0.05},
											{ buffId =11151, weight = 0.07},
											{ buffId =11152, weight = 0.09},
											{ buffId =11153, weight = 0.11},
											{ buffId =11154, weight = 0.13},
											{ buffId =11155, weight = 0.15},
											{ buffId =11156, weight = 0.17},
											{ buffId =11157, weight = 0.19},
											{ buffId =11158, weight = 0.21},
											{ buffId =11159, weight = 0.23},
										}
										
x700022_g_LevelExpMulti           	= 	{  	--等级对应的经验倍数
											{ level =49, 	multi = 1 },
											{ level =74, 	multi = 3 },
											{ level =84, 	multi = 4 },
											{ level =160, 	multi = 5 },
										}										

x700022_g_SubmitNPC                 =   { type =25024,guid= 150525,x = 78, z=71, facedir =0, title="" }

x700022_g_GameNPCTab            ={ 
									{ type =25024,guid= 150525,x = 57, z=49, facedir =0, title="" },
									{ type =25024,guid= 150525,x = 49, z=57, facedir =0, title="" },
									{ type =25024,guid= 150525,x = 49, z=71, facedir =0, title="" },
									{ type =25024,guid= 150525,x = 57, z=79, facedir =0, title="" },
									{ type =25024,guid= 150525,x = 71, z=79, facedir =0, title="" },
									{ type =25024,guid= 150525,x = 79, z=71, facedir =0, title="" },
									{ type =25024,guid= 150525,x = 79, z=57, facedir =0, title="" },
									{ type =25024,guid= 150525,x = 71, z=49, facedir =0, title="" },
								}	
											
											
											
x700022_g_AllPointList	=	{
								{ dtype = 1, x = 63.2016, z = 13.9039, patrolid = 1, }, 	 --北	
								{ dtype = 1, x = 63.2016, z = 13.2039, patrolid = 0, },
								{ dtype = 1, x = 63.2016, z = 12.5039, patrolid = 1, },
								{ dtype = 1, x = 63.2016, z = 11.8039, patrolid = 0, },
								{ dtype = 1, x = 63.2016, z = 11.1039, patrolid = 1, },
								{ dtype = 1, x = 63.2016, z = 10.4039, patrolid = 0, },
								{ dtype = 1, x = 64.7478, z = 13.9039, patrolid = 1, },
								{ dtype = 1, x = 64.7478, z = 13.2039, patrolid = 0, },
								{ dtype = 1, x = 64.7478, z = 12.5039, patrolid = 1, },
								{ dtype = 1, x = 64.7478, z = 11.8039, patrolid = 0, },
								{ dtype = 1, x = 64.7478, z = 11.1039, patrolid = 1, },
								{ dtype = 1, x = 64.7478, z = 10.4039, patrolid = 0, },
								{ dtype = 2, x =  13.7493, z = 64.6766, patrolid = 2, },    --西	
								{ dtype = 2, x =  12.8493, z = 64.6766, patrolid = 3, }, 
								{ dtype = 2, x =  11.9493, z = 64.6766, patrolid = 2, }, 
								{ dtype = 2, x =  11.0493, z = 64.6766, patrolid = 3, }, 
								{ dtype = 2, x =  10.1493, z = 64.6766, patrolid = 2, }, 
								{ dtype = 2, x =  9.2493 , z = 64.6766, patrolid = 3, }, 
								{ dtype = 2, x =  13.7493, z = 63.1653, patrolid = 2, }, 
								{ dtype = 2, x =  12.8493, z = 63.1653, patrolid = 3, }, 
								{ dtype = 2, x =  11.9493, z = 63.1653, patrolid = 2, }, 
								{ dtype = 2, x =  11.0493, z = 63.1653, patrolid = 3, }, 
								{ dtype = 2, x =  10.1493, z = 63.1653, patrolid = 2, }, 
								{ dtype = 2, x =  9.2493 , z = 63.1653, patrolid = 3, }, 
								{ dtype = 3, x =  63.1985, z = 114.2253, patrolid = 4, },   --南	
								{ dtype = 3, x =  63.1985, z = 114.7253, patrolid = 5, }, 
								{ dtype = 3, x =  63.1985, z = 115.2253, patrolid = 4, }, 
								{ dtype = 3, x =  63.1985, z = 115.7253, patrolid = 5, }, 
								{ dtype = 3, x =  63.1985, z = 116.2253, patrolid = 4, }, 
								{ dtype = 3, x =  63.1985, z = 116.7253, patrolid = 5, }, 
								{ dtype = 3, x =  64.7336, z = 114.2253, patrolid = 4, }, 
								{ dtype = 3, x =  64.7336, z = 114.7253, patrolid = 5, }, 
								{ dtype = 3, x =  64.7336, z = 115.2253, patrolid = 4, }, 
								{ dtype = 3, x =  64.7336, z = 115.7253, patrolid = 5, }, 
								{ dtype = 3, x =  64.7336, z = 116.2253, patrolid = 4, }, 
								{ dtype = 3, x =  64.7336, z = 116.7253, patrolid = 5, }, 
							 	{ dtype = 4, x =  114.1351, z = 64.6161, patrolid = 6,  },    --东	
								{ dtype = 4, x =  114.6351, z = 64.6161, patrolid = 7,  }, 
								{ dtype = 4, x =  115.1351, z = 64.6161, patrolid = 6,  }, 
								{ dtype = 4, x =  115.6351, z = 64.6161, patrolid = 7,  }, 
								{ dtype = 4, x =  116.1351, z = 64.6161, patrolid = 6,  }, 
								{ dtype = 4, x =  116.6351, z = 64.6161, patrolid = 7,  }, 
								{ dtype = 4, x =  114.1413, z = 63.1222, patrolid = 6,  }, 
								{ dtype = 4, x =  114.6413, z = 63.1222, patrolid = 7,  }, 
								{ dtype = 4, x =  115.1413, z = 63.1222, patrolid = 6,  }, 
								{ dtype = 4, x =  115.6413, z = 63.1222, patrolid = 7,  }, 
								{ dtype = 4, x =  116.1413, z = 63.1222, patrolid = 6,  }, 
								{ dtype = 4, x =  116.6413, z = 63.1222, patrolid = 7,  }, 
							
							}

--12个坐标点和对应路径id
x700022_g_PointList	=		{
								{flag=1,	x=66, 	z= 12 ,	patrolid = 1 , playEffectId = -1 , stopEffectId = -1 , playEffectId1 = 42 , stopEffectId1 = 48 , playEffectId2 = 43 , stopEffectId2 = 49},
								{flag=2,	x=62, 	z= 12 ,	patrolid = 2 , playEffectId = -1 , stopEffectId = -1 , playEffectId1 = 42 , stopEffectId1 = 48 , playEffectId2 = 43 , stopEffectId2 = 49},
								{flag=3,	x=64, 	z= 14 ,	patrolid = 0 , playEffectId = 38 , stopEffectId = 41 , playEffectId1 = 42 , stopEffectId1 = 48 , playEffectId2 = 43 , stopEffectId2 = 49},
								{flag=4,	x=12, 	z= 66 ,	patrolid = 5 , playEffectId = -1 , stopEffectId = -1 , playEffectId1 = 44 , stopEffectId1 = 46 , playEffectId2 = 45 , stopEffectId2 = 47},
								{flag=5,	x=12, 	z= 62 ,	patrolid = 4 , playEffectId = -1 , stopEffectId = -1 , playEffectId1 = 44 , stopEffectId1 = 46 , playEffectId2 = 45 , stopEffectId2 = 47},
								{flag=6,	x=14, 	z= 64 ,	patrolid = 3 , playEffectId = 39 , stopEffectId = 40 , playEffectId1 = 44 , stopEffectId1 = 46 , playEffectId2 = 45 , stopEffectId2 = 47},
								{flag=7,	x=62, 	z= 116,	patrolid = 2 , playEffectId = -1 , stopEffectId = -1 , playEffectId1 = 46 , stopEffectId1 = 44 , playEffectId2 = 47 , stopEffectId2 = 45},
								{flag=8,	x=66, 	z= 116,	patrolid = 1 , playEffectId = -1 , stopEffectId = -1 , playEffectId1 = 46 , stopEffectId1 = 44 , playEffectId2 = 47 , stopEffectId2 = 45},
								{flag=9,	x=64, 	z= 114,	patrolid = 0 , playEffectId = 40 , stopEffectId = 39 , playEffectId1 = 46 , stopEffectId1 = 44 , playEffectId2 = 47 , stopEffectId2 = 45},
								{flag=10,	x=114, 	z= 64 ,	patrolid = 3 , playEffectId = -1 , stopEffectId = -1 , playEffectId1 = 48 , stopEffectId1 = 42 , playEffectId2 = 49 , stopEffectId2 = 43},
								{flag=11,	x=116, 	z= 66 ,	patrolid = 5 , playEffectId = -1 , stopEffectId = -1 , playEffectId1 = 48 , stopEffectId1 = 42 , playEffectId2 = 49 , stopEffectId2 = 43},
								{flag=12,	x=116, 	z= 62 ,	patrolid = 4 , playEffectId = 41 , stopEffectId = 38 , playEffectId1 = 48 , stopEffectId1 = 42 , playEffectId2 = 49 , stopEffectId2 = 43},
							}

--4个中随机2种可能的组合
x700022_g_C42 = {{1,2},{1,3},{1,4},{2,3},{2,4},{3,4}}
--4各种随机3种可能的组合
x700022_g_C43 = {{1,2,3},{2,3,4},{1,3,4},{1,2,4}};	

--四种怪物ObjId 表
x700022_g_Monster_ObjList = {
								{flag=1, levelmin =1,  levelmax=160,type= 35020, ai=9, aiscript=-1, flag3=1},
                                {flag=1, levelmin =20, levelmax=24, type= 25532, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =25, levelmax=29, type= 25533, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =30, levelmax=34, type= 25534, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =35, levelmax=39, type= 25535, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =40, levelmax=44, type= 25536, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =45, levelmax=49, type= 25537, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =50, levelmax=54, type= 25538, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =55, levelmax=59, type= 25539, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =60, levelmax=64, type= 25540, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =65, levelmax=69, type= 25541, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =70, levelmax=74, type= 25542, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =75, levelmax=79, type= 25543, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =80, levelmax=84, type= 25544, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =85, levelmax=89, type= 25545, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =90, levelmax=94, type= 25546, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =95, levelmax=99, type= 25547, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =100, levelmax=104,type= 44000, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =105, levelmax=109,type= 44001, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =110, levelmax=114,type= 44002, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =115, levelmax=119,type= 44003, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =120, levelmax=124,type= 44004, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =125, levelmax=129,type= 44005, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =130, levelmax=134,type= 44006, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =135, levelmax=139,type= 44007, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =140, levelmax=144,type= 44008, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =145, levelmax=149,type= 44009, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =150, levelmax=154,type= 44010, ai=9, aiscript=-1, flag3=0},
                                {flag=1, levelmin =155, levelmax=160,type= 44011, ai=9, aiscript=-1, flag3=0},
                                
								{flag=2, levelmin =1,  levelmax=160,type= 35021, ai=9, aiscript=-1, flag3=1},
                                {flag=2, levelmin =20, levelmax=24, type= 25548, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =25, levelmax=29, type= 25549, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =30, levelmax=34, type= 25550, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =35, levelmax=39, type= 25551, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =40, levelmax=44, type= 25552, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =45, levelmax=49, type= 25553, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =50, levelmax=54, type= 25554, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =55, levelmax=59, type= 25555, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =60, levelmax=64, type= 25556, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =65, levelmax=69, type= 25557, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =70, levelmax=74, type= 25558, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =75, levelmax=79, type= 25559, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =80, levelmax=84, type= 25560, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =85, levelmax=89, type= 25561, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =90, levelmax=94, type= 25562, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =95, levelmax=100,type= 25563, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =100, levelmax=104,type= 44024, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =105, levelmax=109,type= 44025, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =110, levelmax=114,type= 44026, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =115, levelmax=119,type= 44027, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =120, levelmax=124,type= 44028, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =125, levelmax=129,type= 44029, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =130, levelmax=134,type= 44030, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =135, levelmax=139,type= 44031, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =140, levelmax=144,type= 44032, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =145, levelmax=149,type= 44033, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =150, levelmax=154,type= 44034, ai=9, aiscript=-1, flag3=0},
                                {flag=2, levelmin =155, levelmax=160,type= 44035, ai=9, aiscript=-1, flag3=0},
                                                                           
								{flag=3, levelmin =1,  levelmax=160,type= 35022, ai=9, aiscript=-1, flag3=1},
                                {flag=3, levelmin =20, levelmax=24, type= 25564, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =25, levelmax=29, type= 25565, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =30, levelmax=34, type= 25566, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =35, levelmax=39, type= 25567, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =40, levelmax=44, type= 25568, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =45, levelmax=49, type= 25569, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =50, levelmax=54, type= 25570, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =55, levelmax=59, type= 25571, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =60, levelmax=64, type= 25572, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =65, levelmax=69, type= 25573, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =70, levelmax=74, type= 25574, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =75, levelmax=79, type= 25575, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =80, levelmax=84, type= 25576, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =85, levelmax=89, type= 25577, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =90, levelmax=94, type= 25578, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =95, levelmax=100,type= 25579, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =100, levelmax=104,type= 44012, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =105, levelmax=109,type= 44013, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =110, levelmax=114,type= 44014, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =115, levelmax=119,type= 44015, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =120, levelmax=124,type= 44016, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =125, levelmax=129,type= 44017, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =130, levelmax=134,type= 44018, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =135, levelmax=139,type= 44019, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =140, levelmax=144,type= 44020, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =145, levelmax=149,type= 44021, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =150, levelmax=154,type= 44022, ai=9, aiscript=-1, flag3=0},
                                {flag=3, levelmin =155, levelmax=160,type= 44023, ai=9, aiscript=-1, flag3=0},
                                
								{flag=4, levelmin =1,  levelmax=160,type= 35023, ai=9, aiscript=-1, flag3=1},
                                {flag=4, levelmin =20, levelmax=24, type= 25580, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =25, levelmax=29, type= 25581, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =30, levelmax=34, type= 25582, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =35, levelmax=39, type= 25583, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =40, levelmax=44, type= 25584, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =45, levelmax=49, type= 25585, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =50, levelmax=54, type= 25586, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =55, levelmax=59, type= 25587, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =60, levelmax=64, type= 25588, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =65, levelmax=69, type= 25589, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =70, levelmax=74, type= 25590, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =75, levelmax=79, type= 25591, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =80, levelmax=84, type= 25592, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =85, levelmax=89, type= 25593, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =90, levelmax=94, type= 25594, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =95, levelmax=100,type= 25595, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =100, levelmax=104,type= 44036, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =105, levelmax=109,type= 44037, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =110, levelmax=114,type= 44038, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =115, levelmax=119,type= 44039, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =120, levelmax=124,type= 44040, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =125, levelmax=129,type= 44041, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =130, levelmax=134,type= 44042, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =135, levelmax=139,type= 44043, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =140, levelmax=144,type= 44044, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =145, levelmax=149,type= 44045, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =150, levelmax=154,type= 44046, ai=9, aiscript=-1, flag3=0},
                                {flag=4, levelmin =155, levelmax=160,type= 44047, ai=9, aiscript=-1, flag3=0},
                                

							}

	
--创建怪物的信息
x700022_g_MonsterCreate =	{
								--第1波
								{timeflag=1, pointlist = {1,2,3}, 		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 1},
								{timeflag=2, pointlist = {7,8,9}, 		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 1},
								{timeflag=3, pointlist = {1,2,3}, 		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 1},
								{timeflag=4, pointlist = {7,8,9}, 		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 1},

								--第2波
								{timeflag=5, pointlist = {4,5,6},		ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 2},
								{timeflag=6, pointlist = {10,11,12},	ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 2},
								{timeflag=7, pointlist = {4,5,6},		ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 2},
								{timeflag=8, pointlist = {10,11,12},	ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 2},

								--第3波
								{timeflag=9,  pointlist = {1,2,3},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 3},
								{timeflag=10, pointlist = {7,8,9},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 3},
								{timeflag=11, pointlist = {1,2,3},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 3},
								{timeflag=12, pointlist = {7,8,9},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 3},

								--第4波
								{timeflag=13, pointlist = {4,5,6},		ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 4},
								{timeflag=14, pointlist = {10,11,12},	ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 4},
								{timeflag=15, pointlist = {4,5,6},		ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 4},
								{timeflag=16, pointlist = {10,11,12},	ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 4},

								--第5波
								{timeflag=17,  pointlist = {1,2,3},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 5},
								{timeflag=18, pointlist = {7,8,9},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 5},
								{timeflag=19, pointlist = {1,2,3},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 5},
								{timeflag=20, pointlist = {7,8,9},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 5},

								--第6波
								{timeflag=21, pointlist = {4,5,6},		ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 6},
								{timeflag=22, pointlist = {10,11,12},	ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 6},
								{timeflag=23, pointlist = {4,5,6},		ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 6},
								{timeflag=24, pointlist = {10,11,12},	ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 6},

								--第7波
								{timeflag=25, pointlist = {1,2,3},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 7},
								{timeflag=26, pointlist = {7,8,9},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 7},
								{timeflag=27, pointlist = {1,2,3},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 7},
								{timeflag=28, pointlist = {7,8,9},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 7},

								--第8波
								{timeflag=29, pointlist = {4,5,6},		ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 8},
								{timeflag=30, pointlist = {10,11,12},	ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 8},
								{timeflag=31, pointlist = {4,5,6},		ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 8},
								{timeflag=32, pointlist = {10,11,12},	ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 8},

								--第9波
								{timeflag=33, pointlist = {1,2,3},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 9},
								{timeflag=34, pointlist = {7,8,9},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 9},
								{timeflag=35, pointlist = {1,2,3},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 9},
								{timeflag=36, pointlist = {7,8,9},	    ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 9},

								--第10波
								{timeflag=37, pointlist = {4,5,6},		ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 10},
								{timeflag=38, pointlist = {10,11,12},	ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 10},
								{timeflag=39, pointlist = {4,5,6},		ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 10},
								{timeflag=40, pointlist = {10,11,12},	ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 10},

								--第11波
								{timeflag=41, pointlist = {1,2,3},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 11},
								{timeflag=42, pointlist = {7,8,9},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 11},
								{timeflag=43, pointlist = {1,2,3},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 11},
								{timeflag=44, pointlist = {7,8,9},		ef1={38,40,42,49,45,46}, ef2={39,41,43,44,47,48},objflag = 11},

								--第12波
								{timeflag=45, pointlist = {4,5,6},		ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 12},
								{timeflag=46, pointlist = {10,11,12},	ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 12},
								{timeflag=47, pointlist = {4,5,6},		ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 12},
								{timeflag=48, pointlist = {10,11,12},	ef1={39,41,43,44,47,48}, ef2={38,40,42,49,45,46},objflag = 12},
								


							}	



x700022_g_BonusTab	= 	{
							{exp = 80 , shenwang = 0.2 , inh = 0.5 , },		--小怪
							{exp = 800, shenwang = 2,    inh = 5.0, },       --boss
						}

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------
function x700022_GetWuxingBuffMulti( sceneId, objId )
	
end

function x700022_ProcEnumEvent(sceneId, selfId, NPCId,nScriptId, nFlag)
	
end

function x700022_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
	
end

function x700022_DelRapidMonster( sceneId )
	for i=x700022_CSP_RAPID_MONSTER_START, x700022_CSP_RAPID_MONSTER_END do
		local monId = GetFubenData_Param(sceneId, i)
		if monId ~= -1 and monId ~= -2 then
			if IsObjValid(sceneId,monId) == 1 and GetHp(sceneId,monId) > 0 then
				
				local x,z = GetWorldPos(sceneId, monId)
				if x >= 60 and x <= 68 and z >= 60 and z <= 68 then
					DeleteMonster(sceneId, monId)
					local nRemainCount = GetFubenData_Param(sceneId, x700022_CSP_MONSTER_COUNT) 
					SetFubenData_Param(sceneId, x700022_CSP_MONSTER_COUNT, nRemainCount - 1 ) 
					SetFubenData_Param(sceneId, i, -2 ) 
					
					local nDelMonsterCount = GetFubenData_Param(sceneId, x700022_CSP_DELMON_NUM) + 1
					SetFubenData_Param( sceneId, x700022_CSP_DELMON_NUM,nDelMonsterCount)
					
					local msg = format("当前已消失%d个怪。",nDelMonsterCount)
					x700022_ShowTipsToAll(sceneId, msg)
						
					if nDelMonsterCount >= 10 then
						--x700022_OnFubenFail(sceneId)
						return
					end	
				end
			end
		end
	end
end	

-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700022_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	SetFubenData_Param(sceneId, x700022_CSP_CURRENTSTEP, 1)
	
	SetFubenData_Param( sceneId, x700022_CSP_BOSS_ID, -1)
	SetFubenData_Param( sceneId, x700022_CSP_BOSS_ID2, -1)
	SetFubenData_Param( sceneId, x700022_CSP_BOSS_ID3, -1)
	SetFubenData_Param( sceneId, x700022_CSP_BOSS_ID4, -1)

	SetFubenData_Param( sceneId, x700022_CSP_DELMON_NUM,0)
	SetFubenData_Param( sceneId, x700022_CSP_FINISH,0)

	local fubenlevel = GetFubenData_Param(sceneId, x700022_CSP_FUBENLEVEL ) ;
	SetFubenData_Param( sceneId, x700022_CSP_FUBENLEVEL_DUP, fubenlevel)
	
	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local guid = GetPlayerGUID( sceneId,humanId )
		guid = format("%u", guid)
		SetFubenData_Param(sceneId, x700022_CSP_GUID_START+i, guid);
	end
	--x700022_CancelEffect(sceneId)	
	x700022_g_MonsterTab[sceneId] = {}
	x700022_g_MonsterTab[sceneId][1] = {}
	x700022_g_MonsterTab[sceneId][1][1] = {tick = 0, monid =0, isboss = 0,}
	--x700022_g_MonsterTab[sceneId][1][1].tick = 0
	--x700022_g_MonsterTab[sceneId][1][1].monid = 0
	

	for i=x700022_CSP_RAPID_MONSTER_START, x700022_CSP_RAPID_MONSTER_END do
		SetFubenData_Param( sceneId, i,-1)
	end
	--获得轮回台的MODE
	local kind = GetFubenData_Param(sceneId, x700022_CSP_FUBEN_KIND )
	--local objid = Guid2ObjId(sceneId,guid)
	--local nFubenMode = GetPlayerRuntimeData(sceneId,objid,RD_FUBENPARAM_MODE)
	--print("kind",kind)
	
	--x700022_ValidateXinshouMode(sceneId)
	    
	x700022_InitRandomType(sceneId)

    x700022_CreateNpc(sceneId)

	x700022_CreateHelpNpc(sceneId)
	
end

function x700022_InitRandomType(sceneId)
	local objList={random(1,6)};

	for i=2, 4 do
		local j = random(1,6)

		while j== objList[i-1] do
			j = random(1,6)
		end
		
		objList[i] = j
	end

	for i=1, 4 do
		SetFubenData_Param(sceneId, x700022_CSP_TWO_TYPE_START+i, objList[i]);
	end

	objList={random(1,4)};

	for i=2, 4 do
		local j = random(1,4)

		while j== objList[i-1] do
			j = random(1,4)
		end
		
		objList[i] = j
	end

	for i=1, 4 do
		SetFubenData_Param(sceneId, x700022_CSP_THREE_TYPE_START+i, objList[i]);
	end

end

function x700022_GetRandomNpcTab(sceneId,arr_answer)

	--local arr_answer = { 0,1,2,3,4,5,6,7,8,9,10,11 }
	for j = 1, 6 do
		local n = random(1, 12)
		local m =  random(1, 12)
		if n ~= m then
			local t = arr_answer[n]
			arr_answer[n] = arr_answer[m]
			arr_answer[m] = t
		end
	end
	return arr_answer
end


function x700022_CreateHelpNpc(sceneId)
	local fubenlevel = GetFubenData_Param(sceneId, x700022_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700022_CSP_FUBEN_TYPE)
	if fubenlevel>=x700022_Min_HelpLevel and fubenlevel<=x700022_Max_HelpLevel then
		local nIndexFrom = GetFubenDataPosByScriptID(x700022_g_ScriptId)
		
		local nDataCount = GetFubenDataCountByScriptID( x700022_g_ScriptId )

		local arr_answer = {0,1,2,3,4,5,6,7,8,9,10,11}
		arr_answer = x700022_GetRandomNpcTab(sceneId,arr_answer)	
		local num = 0
		for i=0 ,nDataCount-1 do
		
			local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700022_g_ScriptId,nIndexFrom,i)			
			for j = 1, 6 do
				
				local nCurrentMonsterFlag = arr_answer[j] + 110		
				if monsterFlag >= 110 and monsterFlag == nCurrentMonsterFlag then 
					if idScript == x700022_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
						local nObjId = -1 
						if title~="" then
							nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 24, -1, facedir, "", title)
						else
							nObjId = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 24, -1, facedir)
						end
						num = num + 1			
						if num == 6 then
							x700022_ShowTipsToAll(sceneId,"#G王城护卫六人组前来支援！");
							return
						end
					end
				end
			end
			
		end

		
	end

	
	
end

function x700022_CreateNpc( sceneId)
	
	local nRet = 0
	for i, item in x700022_g_GameNPCTab do
       	if x700022_g_GameNPCTab[i].title~="" then
			nRet = CreateMonster(sceneId, x700022_g_GameNPCTab[i].type, x700022_g_GameNPCTab[i].x, x700022_g_GameNPCTab[i].z, 3, 0, -1, x700022_g_GameNPCTab[i].guid, -1,-1,x700022_g_GameNPCTab[i].facedir,  "",x700022_g_GameNPCTab[i].title)
		else
			nRet = CreateMonster(sceneId, x700022_g_GameNPCTab[i].type, x700022_g_GameNPCTab[i].x, x700022_g_GameNPCTab[i].z, 3, 0, -1, x700022_g_GameNPCTab[i].guid, -1,-1,x700022_g_GameNPCTab[i].facedir)
		end
    end
    
    
    
    
--	 local nRet = 0;
--	 if x700022_g_GameNPC.title~="" then
--		nRet = CreateMonster(sceneId, x700022_g_GameNPC.type, x700022_g_GameNPC.x, x700022_g_GameNPC.z, 3, 0, -1, x700022_g_GameNPC.guid, -1,-1,x700022_g_GameNPC.facedir,  "",x700022_g_GameNPC.title)
--	 else
--		nRet = CreateMonster(sceneId, x700022_g_GameNPC.type, x700022_g_GameNPC.x, x700022_g_GameNPC.z, 3, 0, -1, x700022_g_GameNPC.guid, -1,-1,x700022_g_GameNPC.facedir)
--	 end

	 SetFubenData_Param(sceneId, x700022_CSP_NPC_ID, nRet )
end


function x700022_CancelEffect(sceneId)
		
					--通知玩家
					local humancount = GetFuben_PlayerCount(sceneId);
					for ii = 0, humancount - 1 do
						local humanId = GetFuben_PlayerObjId(sceneId, ii);
					--	CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,playEffectId )
						CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,humanId,38 )
					--	CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,playEffectId1 )
						CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,humanId,39 )
					--	CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,playEffectId2 )
						CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,humanId,40 )
						CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,humanId,41 )
						
					end	

					
				
end
function x700022_OnPlayerEnter( sceneId, playerId )
	
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,38 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,40 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,39 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,41 )
		
	x700022_PlayEffectByCurrentStep(sceneId,playerId,0)
end

function x700022_PlayEffectByCurrentStep(sceneId,playerId,IsAll)
	
	local nCurrentStep = GetFubenData_Param(sceneId, x700022_CSP_CURRENTSTEP);
	nCurrentStep = nCurrentStep -1
	if nCurrentStep <= 0 then
		return
	end
	
	if IsAll == 1 then	--如果为BOSS，则所有水晶特效开
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,38 )
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,40 )
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,39 )
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,41 )
		
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,43 )
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,44 )
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,47 )
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,48 )
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,42 )
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,49 )
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,45 )
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,46 )
	else
		if mod(nCurrentStep,2) == 1 then
			CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,39 )
			CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,41 )
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,38 )
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,40 )
			
			CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,43 )
			CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,44 )
			CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,47 )
			CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,48 )
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,42 )
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,49 )
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,45 )
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,46 )
			
			--print("north")
			
		else
			CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,38 )
			CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,40 )
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,39 )
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,41 )
			
			
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,43 )
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,44 )
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,47 )
			CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,playerId,48 )
			CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,42 )
			CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,49 )
			CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,45 )
			CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,46 )
			--print("east")
		end
	end

	
--	for i,itm in item.ef2 do
--		print("============>1",nCurrentStep,itm)
--		CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,itm )
--	end
	
end


function x700022_BroadcastPlayEffectByCurrentStep(sceneId, IsAllRight)
	local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		x700022_PlayEffectByCurrentStep(sceneId,humanId,IsAllRight)
	end	
	
	
end
function x700022_StopAllEffect( sceneId, playerId )
	--print("x700022_StopAllEffect==============")
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,38 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,39 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,40 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,41 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,42 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,43 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,44 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,45 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,46 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,47 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,48 )
	CallScriptFunction(UTILITY_SCRIPT,"StopEffect",sceneId,playerId,49 )
	
	
end
function x700022_OnPlayerLeave( sceneId, playerId )
	x700022_StopAllEffect( sceneId, playerId )
end

function x700022_OnFubenFail(sceneId)
	--print("x700022_OnFubenFail =======================================================")
	--SetFubenData_Param( sceneId, x700022_CSP_FINISH,1)
	
--	for i,item in x700022_g_MonsterTab[sceneId] do 
--		for j,s in item do
--			--print("s.tick",s.tick)
--			if s ~= nil then
--				DeleteMonster(sceneId, s.monid)
--				local nCurMonsterCount = GetFubenData_Param(sceneId, x700022_CSP_MONSTER_COUNT)-1 
--				SetFubenData_Param(sceneId, x700022_CSP_MONSTER_COUNT, nCurMonsterCount)    
--				s = nil
--				x700022_g_MonsterTab[sceneId][i][j] = nil
--			end
--		end
--	end
	
	--x700022_ShowTipsToAll(sceneId,"副本失败，请退出副本。")
end

function x700022_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId);

	--通知玩家
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId,str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, humanId);
		
		Msg2Player(sceneId, humanId, str, 0, 2)
	end
end
---------------
function x700022_ValidateXinshouMode(sceneId)  --是否为新手副本，如果是则返回最低玩家等级

	--local kind = GetFubenData_Param(sceneId, x700022_CSP_FUBEN_KIND )
	--if kind ~= 0 then
	--	return 0
	--end
	
	local maxLevel = 0
	local minLevel = 160
	local humancount = GetFuben_PlayerCount(sceneId);

	--通知玩家
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local level =GetLevel( sceneId, humanId)
		if level < minLevel then
			minLevel = level
		end
		if level > maxLevel then
			maxLevel = level
		end
	end
	
	if maxLevel - minLevel >= 15 then	--开启新手副本模式
		SetFubenData_Param( sceneId, x700022_CSP_XINSHOU_FLAG, 1)
		SetFubenData_Param( sceneId, x700022_CSP_XINSHOU_LEVEL, minLevel)
		SetFubenData_Param(sceneId, x700022_CSP_FUBENLEVEL, minLevel )
		return minLevel
	end
	return 0
end


function x700022_EnterTick(sceneId, nowTickCount)
	
	local fin = GetFubenData_Param( sceneId, x700022_CSP_FINISH)
	if fin == 1 then
		return
	end
	
	x700022_DelRapidMonster( sceneId )

--	local nRemain = 0
--	for i,item in x700022_g_MonsterTab[sceneId] do
--		for j,s in item do
--			if s ~= nil and s.tick <= 0 then
--				nRemain = nRemain + 1
--			 	if nRemain >= 10 then
--			 		x700022_OnFubenFail(sceneId)
--			 		return
--			 	end
--			end
--		end
--	end

	local bossid = GetFubenData_Param(sceneId, x700022_CSP_BOSS_ID)
	local bossid2 = GetFubenData_Param(sceneId, x700022_CSP_BOSS_ID2)
	local bossid3 = GetFubenData_Param(sceneId, x700022_CSP_BOSS_ID3)
	local bossid4 = GetFubenData_Param(sceneId, x700022_CSP_BOSS_ID4)
	
	for i,item in x700022_g_MonsterTab[sceneId] do 
		for j,s in item do
			if s ~= nil and s.tick > 0 then
				
				s.tick = s.tick - 1
				if s.tick == 0 then
					if s.monid == bossid then
						SetFubenData_Param(sceneId, x700022_CSP_BOSS_ID, -2)
						x700022_OnFubenFail(sceneId)
						return
					elseif bossid2 == s.monid then
						SetFubenData_Param(sceneId, x700022_CSP_BOSS_ID2, -2)
					elseif bossid3 == s.monid then
						SetFubenData_Param(sceneId, x700022_CSP_BOSS_ID3, -2)
					elseif bossid4 == s.monid then
						SetFubenData_Param(sceneId, x700022_CSP_BOSS_ID4, -2)
						
					end

					DeleteMonster(sceneId, s.monid)
					--print("x700022_EnterTick DeleteMonster")
					local nCurMonsterCount = GetFubenData_Param(sceneId, x700022_CSP_MONSTER_COUNT)-1 
					--print("DeleteMonster----------->",nCurMonsterCount)
					SetFubenData_Param(sceneId, x700022_CSP_MONSTER_COUNT, nCurMonsterCount)    
					
					local nDelMonsterCount = 0
					if s.isboss == 1 then
					 	nDelMonsterCount = GetFubenData_Param(sceneId, x700022_CSP_DELMON_NUM) + 2
					else
						nDelMonsterCount = GetFubenData_Param(sceneId, x700022_CSP_DELMON_NUM) + 1
					end
					
					SetFubenData_Param( sceneId, x700022_CSP_DELMON_NUM,nDelMonsterCount)
					
					local msg = format("当前已消失%d个怪！",nDelMonsterCount)
					x700022_ShowTipsToAll(sceneId, msg)
	
	
					s = nil
					x700022_g_MonsterTab[sceneId][i][j] = nil
					
					if nDelMonsterCount >= 10 then
						--x700022_OnFubenFail(sceneId)
						return
					end
					
					if nCurMonsterCount == 0 then
						x700022_OnAllMonsterDead( sceneId)
					end
				end
			end
		end
	end

	bossid = GetFubenData_Param(sceneId, x700022_CSP_BOSS_ID)
	bossid2 = GetFubenData_Param(sceneId, x700022_CSP_BOSS_ID2)
	bossid3 = GetFubenData_Param(sceneId, x700022_CSP_BOSS_ID3)
	bossid4 = GetFubenData_Param(sceneId, x700022_CSP_BOSS_ID4)
	
	if bossid== -2 and bossid2== -2 and bossid3== -2 and bossid4== -2 then
		SetFubenData_Param( sceneId, x700022_CSP_FINISH,1)
		x700022_OnFubenFail(sceneId)
		return
	end
	
	
	local humancount = GetFuben_PlayerCount(sceneId);
	if humancount<= 0 then
	--	x700022_CancelEffect(sceneId)
	end

	if nowTickCount >= 2 and  nowTickCount<= x700022_g_nTextCount+1 then
		local nNpcId = GetFubenData_Param(sceneId, x700022_CSP_NPC_ID )
		NpcTalk(sceneId, nNpcId, x700022_g_NpcTalkText[nowTickCount-1],  -1)
	end

	local nCurrentStep = GetFubenData_Param(sceneId, x700022_CSP_CURRENTSTEP);

	if nCurrentStep<=0 then
		return
	end

	local nLen = 0;
	for i,item in x700022_g_TimeDriverList do
		nLen = nLen+1
	end

	if nCurrentStep> nLen then
		return
	end

	local nCurrentStepTickCount = GetFubenData_Param(sceneId, x700022_CSP_CURRENTSTEP_TICKCOUNT)+1;
	SetFubenData_Param(sceneId, x700022_CSP_CURRENTSTEP_TICKCOUNT, nCurrentStepTickCount)
	
	local nNextStepTime = x700022_g_TimeDriverList[nCurrentStep];
	--print(nCurrentStepTickCount,nNextStepTime)
	if nCurrentStepTickCount>=nNextStepTime then
		SetFubenData_Param(sceneId, x700022_CSP_CURRENTSTEP_TICKCOUNT, 0)
		SetFubenData_Param(sceneId, x700022_CSP_CURRENTSTEP,nCurrentStep+1 );
		
		
		if nCurrentStep < nLen then   --最后两波为BOSS
			x700022_CreateMonster( sceneId, nCurrentStep )
		else
			x700022_CreateBoss(sceneId, nCurrentStep)
		end
    
	end
end


function x700022_CreateBoss(sceneId, nStep)
	--print("x700022_CreateBoss", nStep)
	local fubenlevel = GetFubenData_Param(sceneId, x700022_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700022_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700022_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700022_g_ScriptId )
	local nRemainCount = GetFubenData_Param(sceneId, x700022_CSP_MONSTER_COUNT ) 
	local kind = GetFubenData_Param(sceneId, x700022_CSP_FUBEN_KIND )
	local xinshouFlag = GetFubenData_Param( sceneId, x700022_CSP_XINSHOU_FLAG)
	x700022_g_MonsterTab[sceneId][nStep] = {}
	local index = 1
	if mod(nStep,2) == 1 then
		indexStart = 0
	else
		indexStart = 1
	end
	
	local monflag = 0
	if kind == 0 then		
		monflag = 1 	
	else
		monflag = 0
	end
	
	--第一个方向
	indexStart = indexStart * 12 
	
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700022_g_ScriptId,nIndexFrom,i)
		if idScript == x700022_g_ScriptId and monsterFlag == nStep and levelmin <= fubenlevel and levelmax >= fubenlevel and xinshouFlag == flag and nFubenType == flag3 then
		    local nRet = 0;
		    
		    local nMonID = 0
	        x = x700022_g_AllPointList[indexStart+index].x
	        z = x700022_g_AllPointList[indexStart+index].z
	        patrolid = x700022_g_AllPointList[indexStart+index].patrolid
	           	
			if title~="" then
				nMonID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700022_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nMonID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700022_g_ScriptId, -1, 21,-1,facedir)
			end
			
			local monCount = getn(x700022_g_MonsterTab[sceneId][nStep])
			monCount =  monCount + 1
			--print("monCount",monCount)
			x700022_g_MonsterTab[sceneId][nStep][monCount] = {}
			x700022_g_MonsterTab[sceneId][nStep][monCount].monid = nMonID
			x700022_g_MonsterTab[sceneId][nStep][monCount].tick = flag1
			x700022_g_MonsterTab[sceneId][nStep][monCount].isboss = 1
			--print("flag1",flag1)
			nRemainCount = nRemainCount + 1
			if patrolid>=0 then
				SetPatrolId(sceneId, nMonID, patrolid)
			end
			
			local nLen = getn(x700022_g_TimeDriverList)
			
			if nStep == nLen then
				SetFubenData_Param( sceneId, x700022_CSP_BOSS_ID, nMonID)
			end
--			if nStep == nLen - 1 then
--				SetFubenData_Param( sceneId, x700022_CSP_BOSS_ID, nMonID)
--			elseif nStep == nLen then
--				SetFubenData_Param( sceneId, x700022_CSP_BOSS_ID3, nMonID)
--			end
			--print("x700022_CreateBoss bossid", nStep,nLen)
			
			index = index + 1	
			
        end
	end

	if nStep ~= getn(x700022_g_TimeDriverList) then  --最后一个BOSS
	
		--第二个方向
		index = 1
		indexStart = indexStart + 24
		for i = 0,nDataCount-1 do
			
			local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700022_g_ScriptId,nIndexFrom,i)
			if idScript == x700022_g_ScriptId and monsterFlag == nStep and levelmin <= fubenlevel and levelmax >= fubenlevel and xinshouFlag == flag and nFubenType == flag3 then
		        --print("x700022_CreateMonster2",count,indexStart,index,flag1)
		        for j=0,count -1 do
						
					local nMonID = 0
		           	x = x700022_g_AllPointList[indexStart+index].x
		           	z = x700022_g_AllPointList[indexStart+index].z
		           	patrolid = x700022_g_AllPointList[indexStart+index].patrolid
		           	
					if title~="" then
						nMonID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700022_g_ScriptId, -1, 21,-1,facedir, "",title)
					else
						nMonID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700022_g_ScriptId, -1, 21,-1,facedir)
					end
					local monCount = getn(x700022_g_MonsterTab[sceneId][nStep])      
					monCount =  monCount + 1
					--print("monCount2",monCount)
					x700022_g_MonsterTab[sceneId][nStep][monCount] = {}
					x700022_g_MonsterTab[sceneId][nStep][monCount].monid = nMonID
					x700022_g_MonsterTab[sceneId][nStep][monCount].tick = flag1
					x700022_g_MonsterTab[sceneId][nStep][monCount].isboss = 1
					--print("flag1",flag1)
					nRemainCount = nRemainCount + 1
					if patrolid>=0 then
						SetPatrolId(sceneId, nMonID, patrolid)
					end
					
					local nLen = getn(x700022_g_TimeDriverList)
					if nStep == nLen - 1 then
						SetFubenData_Param( sceneId, x700022_CSP_BOSS_ID2, nMonID)
						--print("SetFubenData_Param 2")
					elseif nStep == nLen then
						SetFubenData_Param( sceneId, x700022_CSP_BOSS_ID4, nMonID)
						--print("SetFubenData_Param 4")
					end
				
					--print("x700022_CreateBoss bossid1", nStep,nLen)
					index = index + 1
		        end
		    end
		end
	end
	----------------

	x700022_BroadcastPlayEffectByCurrentStep(sceneId, 1)

	SetFubenData_Param(sceneId, x700022_CSP_MONSTER_COUNT, nRemainCount ) 

	--37,38,39,40
	if nStep ~= 38 and nStep ~= 40 then
		x700022_ShowTipsToAll(sceneId,"#G恭喜进入最后一关，大量经验等待着您。");
		local nNpcId = GetFubenData_Param(sceneId, x700022_CSP_NPC_ID )
		NpcTalk(sceneId, nNpcId, "我听到了那恐怖的嚎叫，一定有凶恶的巨兽出现了！",  -1)
	end

end



---------------------------------------------------------------------------------------------------
--创建一小波怪物
---------------------------------------------------------------------------------------------------
function x700022_CreateMonster(sceneId, nStep)
	local msg = format("出现第%d波怪.总共39波！",nStep)
	x700022_ShowTipsToAll(sceneId, msg)

	local nRemainCount = GetFubenData_Param(sceneId, x700022_CSP_MONSTER_COUNT ) 
    
    local fubenlevel = GetFubenData_Param(sceneId, x700022_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700022_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700022_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700022_g_ScriptId )
	local kind = GetFubenData_Param(sceneId, x700022_CSP_FUBEN_KIND )
	local xinshouFlag = GetFubenData_Param( sceneId, x700022_CSP_XINSHOU_FLAG)
	x700022_g_MonsterTab[sceneId][nStep] = {}
	--print("x700022_CreateMonster nIndexFrom",nIndexFrom)


	local index = 1
	if mod(nStep,2) == 1 then
		indexStart = 0
	else
		indexStart = 1
	end
	
	local monflag = 0
	if kind == 0 then		
		monflag = 1 	
	else
		monflag = 0
	end
	--第一个方向
	indexStart = indexStart * 12 
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700022_g_ScriptId,nIndexFrom,i)
		if idScript == x700022_g_ScriptId and monsterFlag == nStep and levelmin <= fubenlevel and levelmax >= fubenlevel and xinshouFlag == flag and nFubenType == flag3 then
			--print("x700022_CreateMonster",count,indexStart,index,flag1)
		
				
	        for j=0,count -1 do
					
				local nMonID = 0
	           	x = x700022_g_AllPointList[indexStart+index].x
	           	z = x700022_g_AllPointList[indexStart+index].z
	           	patrolid = x700022_g_AllPointList[indexStart+index].patrolid
	           	
				if title~="" then
					nMonID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700022_g_ScriptId, -1, 21,-1,facedir, "",title)
				else
					nMonID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700022_g_ScriptId, -1, 21,-1,facedir)
				end
				
				if nStep == getn(x700022_g_TimeDriverList) - 2 or nStep == getn(x700022_g_TimeDriverList) - 1 then	--记录快速怪ID
					for i=x700022_CSP_RAPID_MONSTER_START, x700022_CSP_RAPID_MONSTER_END do
						if GetFubenData_Param(sceneId, i ) == -1 then 
							SetFubenData_Param( sceneId, i,nMonID)
							break
						end
					end
				end
				
				
				local monCount = getn(x700022_g_MonsterTab[sceneId][nStep])
				monCount =  monCount + 1
				x700022_g_MonsterTab[sceneId][nStep][monCount] = {}
				x700022_g_MonsterTab[sceneId][nStep][monCount].monid = nMonID
				x700022_g_MonsterTab[sceneId][nStep][monCount].tick = flag1
				--print("x700022_CreateMonster flag1",flag1)
				if mod(nStep,3) ~= 0 then    --3的倍数为BOSS
					x700022_g_MonsterTab[sceneId][nStep][monCount].isboss = 0
				else
					x700022_g_MonsterTab[sceneId][nStep][monCount].isboss = 1
				end
				nRemainCount = nRemainCount + 1
				if patrolid>=0 then
					SetPatrolId(sceneId, nMonID, patrolid)
				end
				index = index + 1
				
		    end
	    end
	end
	
	
	--第二个方向
	index = 1
	if mod(nStep,3) ~= 0 then    --3的倍数为BOSS
		indexStart = indexStart + 24
		for i = 0,nDataCount-1 do
			
			local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700022_g_ScriptId,nIndexFrom,i)
			if idScript == x700022_g_ScriptId and monsterFlag == nStep and levelmin <= fubenlevel and levelmax >= fubenlevel and xinshouFlag == flag and nFubenType == flag3 then
		        --print("x700022_CreateMonster2",count,indexStart,index,flag1)
		        for j=0,count -1 do
						
					local nMonID = 0
		           	x = x700022_g_AllPointList[indexStart+index].x
		           	z = x700022_g_AllPointList[indexStart+index].z
		           	patrolid = x700022_g_AllPointList[indexStart+index].patrolid
		           	
					if title~="" then
						nMonID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700022_g_ScriptId, -1, 21,-1,facedir, "",title)
					else
						nMonID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700022_g_ScriptId, -1, 21,-1,facedir)
					end
					
					if nStep == getn(x700022_g_TimeDriverList) - 2 or nStep == getn(x700022_g_TimeDriverList) - 1 then 	--记录快速怪ID
						for i=x700022_CSP_RAPID_MONSTER_START, x700022_CSP_RAPID_MONSTER_END do
							if GetFubenData_Param(sceneId, i ) == -1 then 
								SetFubenData_Param( sceneId, i,nMonID)
								break
							end
						end
					end
				
					local monCount = getn(x700022_g_MonsterTab[sceneId][nStep])      
					monCount =  monCount + 1
					x700022_g_MonsterTab[sceneId][nStep][monCount] = {}
					x700022_g_MonsterTab[sceneId][nStep][monCount].monid = nMonID
					x700022_g_MonsterTab[sceneId][nStep][monCount].tick = flag1
					x700022_g_MonsterTab[sceneId][nStep][monCount].isboss = 0
					nRemainCount = nRemainCount + 1
					if patrolid>=0 then
						SetPatrolId(sceneId, nMonID, patrolid)
					end
					index = index + 1
		        end
		    end
		end
	end

	if mod(nStep,3) == 0 then    
		x700022_BroadcastPlayEffectByCurrentStep(sceneId, 1)
	else
		x700022_BroadcastPlayEffectByCurrentStep(sceneId, 0)
	end

	
	if mod(nStep,4) ==1 then
		local str = ""
		if nStep==1 then
			str = "#G第一批怪兽出现了！"
		else
			local strList = {	"#G又一批怪兽蜂拥而出……",
								"#G四周同时出现了怪物的身影……",
								"#G四面都传来沉重的脚步声……"}

			str = strList[random(1,3)]

		end

		x700022_ShowTipsToAll(sceneId,str);
	end
	SetFubenData_Param(sceneId, x700022_CSP_MONSTER_COUNT, nRemainCount ) 

end

---------------------------------------------------------------------------------------------------
--得到怪物的位置和patrol
---------------------------------------------------------------------------------------------------
function x700022_GetPointInfo(sceneId, pointIndex)
	return x700022_g_PointList[pointIndex].x,x700022_g_PointList[pointIndex].z,x700022_g_PointList[pointIndex].patrolid
--	for i,item in x700022_g_PointList do
--		if item.flag == pointIndex then
--			return item.x, item.z, item.patrolid;
--		end
--	end

	--return -1;
end
--------------------------------------------------------------------------------------------------
--得到大门特效的位置
--------------------------------------------------------------------------------------------------

function x700022_PlayEffectId(sceneId,pointIndex)
	return x700022_g_PointList[pointIndex].playEffectId
--	for i,item in x700022_g_PointList do
--		if item.flag == pointIndex then
--			return item.playEffectId
--		end
--	end
	
	--return -1;
end
		
		
		
function x700022_stopEffectId(sceneId,pointIndex)
	return x700022_g_PointList[pointIndex].stopEffectId
--	for i,item in x700022_g_PointList do
--		if item.flag == pointIndex then
--			return item.stopEffectId
--		end
--	end
	
	--return -1;
end
		
--------------------------------------------------------------------------------------------------
--得到灯柱1特效的位置
--------------------------------------------------------------------------------------------------
function x700022_PlayEffectId1(sceneId,pointIndex)
	return x700022_g_PointList[pointIndex].playEffectId1
--	for i,item in x700022_g_PointList do
--		if item.flag == pointIndex then
--			return item.playEffectId1
--		end
--	end
	
	--return -1;
end
		
		
		
function x700022_stopEffectId1(sceneId,pointIndex)
	return x700022_g_PointList[pointIndex].stopEffectId1
--	for i,item in x700022_g_PointList do
--		if item.flag == pointIndex then
--			return item.stopEffectId1
--		end
--	end
	
	--return -1;
end

-------------------------------------------------------------------------------------------------
--得到灯柱2特效的位置
-------------------------------------------------------------------------------------------------
function x700022_PlayEffectId2(sceneId,pointIndex)
	return x700022_g_PointList[pointIndex].playEffectId2
--	for i,item in x700022_g_PointList do
--		if item.flag == pointIndex then
--			return item.playEffectId2
--		end
--	end
	
	--return -1;
end
		
		
		
function x700022_stopEffectId2(sceneId,pointIndex)
	return x700022_g_PointList[pointIndex].stopEffectId2
--	for i,item in x700022_g_PointList do
--		if item.flag == pointIndex then
--			return item.stopEffectId2
--		end
--	end
	
	--return -1;
end

function x700022_IsBoss(sceneId, selfId)
	local type = GetMonsterDataID(sceneId, selfId)
	--轮回台小怪区间：45300～45635，46084～46419
	--轮回台boss区间：45636～46083
	if type >= 45636 and type<=46083 then
		return 1
	elseif  type >= 55636 and  type <= 56083 then
		return 1
	end
	return 0
end

function x700022_GetLevelExpMulti(sceneId, objId)
	local level =GetLevel( sceneId, objId)
	for i,item in x700022_g_LevelExpMulti do
		if level <= item.level then
			return item.multi
		end
	end
	return 1
end

function x700022_GetWuxingExpWeight(sceneId, objId)
	
	for i,item in x700022_g_WuxingBuffExp do
		if IsHaveSpecificImpact( sceneId, objId, item.buffId) == 1 then
			return item.weight
		end
	end
	return 0
end

function x700022_AddFactBouns(sceneId, isboss, kind)
	--if GetFubenData_Param( sceneId, x700022_CSP_XINSHOU_FLAG) == 1 then  --新手经验模式
	--	return
	--end
	local expParam = GetExpParam()
	if isboss == 1 then  --boss
		local nHumanCount = GetScenePlayerCount( sceneId)
	    if nHumanCount > 0 then
	        for i = 0, nHumanCount do
	            local objId = GetScenePlayerObjId( sceneId,i)
	            if objId >= 0 then
	            	local level =GetLevel( sceneId, objId)
	            	--if IsHaveSpecificImpact( sceneId, objId, 9011) == 1 or IsHaveSpecificImpact( sceneId, objId, 9013) == 1 then --江湖请柬
	            	if IsHaveSpecificImpact( sceneId, objId, 7510) == 1 or IsHaveSpecificImpact( sceneId, objId, 7511) == 1  or IsHaveSpecificImpact( sceneId, objId, 9007) == 1 then --双倍经验
	            		if kind == 0 then
	            			local baseexp = x700022_g_BonusTab[2].exp*level*x700022_GetLevelExpMulti(sceneId, objId)
	            			local exp = baseexp
	            			local weight = x700022_GetWuxingExpWeight(sceneId, objId)
	            			exp = exp  + baseexp*weight
	            			if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --朝迋请柬
	            				exp = exp  + baseexp*0.35
							end
							if IsHaveSpecificImpact( sceneId, objId, 9011) == 1 or IsHaveSpecificImpact( sceneId, objId, 9013) == 1 then --请柬
								exp = exp  + baseexp*0.25
							end
	            			local suit = GetSuitExpWeight(sceneId,objId)
	            			if suit > 0 then
	            				exp = exp  + baseexp*(suit/100)
	            			end
							exp = floor(exp + baseexp)
							ExecShituExpAddition(sceneId, objId, baseexp)
							if expParam > 1.0 then
								exp = exp * expParam
							end
							exp = floor(exp)
						
							if baseexp*2.80 < exp then	
								local playerName = GetName(sceneId, objId)
								local msg = "FUBENERR "..playerName.." level "..level.." baseexp "..baseexp.." exp "..exp
								WriteLog(1,msg)
							end
							AddExp(sceneId, objId, exp)
							AddActiveHorseExp(sceneId,objId,exp,1 )
						elseif kind == 1 then
							local sw = floor(level*x700022_g_BonusTab[2].shenwang*2)
							SetShengWang( sceneId, objId, GetShengWang( sceneId, objId) + sw)
							local msg = format("你获得了%d点声望值。",sw)
							Msg2Player(sceneId, objId, msg, 0, 2)
        					Msg2Player(sceneId, objId, msg, 0, 3)
						elseif kind == 2 then
							local multi = 2
							if IsHaveSpecificImpact( sceneId, objId, 9015) == 1 then --天赋丹
		            			multi = multi + 1
		            		end
		            		if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --朝迋请柬
								multi = multi + 0.20
							end
							local inh =  floor(level*x700022_g_BonusTab[2].inh*multi)
							if level >= 80 then
								local refixInh = AddInherenceExp(sceneId, objId, inh)
								local msg = format("你获得了%d点天赋值。",refixInh)
								Msg2Player(sceneId, objId, msg, 0, 2)
	        					Msg2Player(sceneId, objId, msg, 0, 3)
	        				else
		        				local baseexp = x700022_g_BonusTab[2].exp*level*x700022_GetLevelExpMulti(sceneId, objId)
		            			local exp = baseexp
		            			local weight = x700022_GetWuxingExpWeight(sceneId, objId)
		            			exp = exp  + baseexp*weight
		            			if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --朝迋请柬
		            				exp = exp  + baseexp*0.35
								end
								if IsHaveSpecificImpact( sceneId, objId, 9011) == 1 or IsHaveSpecificImpact( sceneId, objId, 9013) == 1 then --请柬
									exp = exp  + baseexp*0.25
								end
		            			local suit = GetSuitExpWeight(sceneId,objId)
		            			if suit > 0 then
		            				exp = exp  + baseexp*(suit/100)
		            			end
								exp = floor(exp + baseexp)
								if expParam > 1.0 then
									exp = exp * expParam
								end
								exp = floor(exp)
								AddExp(sceneId, objId, exp)
								ExecShituExpAddition(sceneId, objId, baseexp)
								AddActiveHorseExp(sceneId,objId,exp,1 )
							end	
						end
					else
						if kind == 0 then
							local baseexp = x700022_g_BonusTab[2].exp*level*x700022_GetLevelExpMulti(sceneId, objId)
	            			local exp = baseexp
	            			local weight = x700022_GetWuxingExpWeight(sceneId, objId)
	            			exp = exp  + baseexp*weight
	            			if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --朝迋请柬
	            				exp = exp  + baseexp*0.35
							end
							if IsHaveSpecificImpact( sceneId, objId, 9011) == 1 or IsHaveSpecificImpact( sceneId, objId, 9013) == 1 then --请柬
								exp = exp  + baseexp*0.25
							end
	            			local suit = GetSuitExpWeight(sceneId,objId)
	            			if suit > 0 then
	            				exp = exp  + baseexp*(suit/100)
	            			end
							if expParam > 1.0 then
								exp = exp * expParam
							end
							exp = floor(exp)
							if baseexp*2.80 < exp then	
								local playerName = GetName(sceneId, objId)
								local msg = "FUBENERR "..playerName.." level "..level.." baseexp "..baseexp.." exp "..exp
								WriteLog(1,msg)
							end
							AddExp(sceneId, objId, exp)
							ExecShituExpAddition(sceneId, objId, baseexp)
							AddActiveHorseExp(sceneId,objId,exp,1 )
						elseif kind == 1 then
							local sw = floor(level*x700022_g_BonusTab[2].shenwang)
							SetShengWang( sceneId, objId, GetShengWang( sceneId, objId) + sw)
							local msg = format("你获得了%d点声望值。",sw)
							Msg2Player(sceneId, objId, msg, 0, 2)
        					Msg2Player(sceneId, objId, msg, 0, 3)
						elseif kind == 2 then
							local multi = 1
							if IsHaveSpecificImpact( sceneId, objId, 9015) == 1 then --天赋丹
		            			multi = multi + 1
		            		end
		            		if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --朝迋请柬
								multi = multi + 0.20
							end
							local inh =  floor(level*x700022_g_BonusTab[2].inh*multi)
							if level >= 80 then
								local refixInh = AddInherenceExp(sceneId, objId, inh)
								local msg = format("你获得了%d点天赋值。",refixInh)
								Msg2Player(sceneId, objId, msg, 0, 2)
	        					Msg2Player(sceneId, objId, msg, 0, 3)
	        				else
	        					local baseexp = x700022_g_BonusTab[2].exp*level*x700022_GetLevelExpMulti(sceneId, objId)
		            			local exp = baseexp
		            			local weight = x700022_GetWuxingExpWeight(sceneId, objId)
		            			exp = exp  + baseexp*weight
		            			if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --朝迋请柬
		            				exp = exp  + baseexp*0.35
								end
								if IsHaveSpecificImpact( sceneId, objId, 9011) == 1 or IsHaveSpecificImpact( sceneId, objId, 9013) == 1 then --请柬
									exp = exp  + baseexp*0.25
								end
		            			local suit = GetSuitExpWeight(sceneId,objId)
		            			if suit > 0 then
		            				exp = exp  + baseexp*(suit/100)
		            			end
								if expParam > 1.0 then
									exp = exp * expParam
								end
								exp = floor(exp)
								AddExp(sceneId, objId, exp)
								ExecShituExpAddition(sceneId, objId, baseexp)
								AddActiveHorseExp(sceneId,objId,exp,1 )
							end	
						end
					end
					
					
	            end
	        end
	    end
    else  --小怪
    	local nHumanCount = GetScenePlayerCount( sceneId)
	    if nHumanCount > 0 then
	        for i = 0, nHumanCount do
	            local objId = GetScenePlayerObjId( sceneId,i)
	            if objId >= 0 then
	            	local level =GetLevel( sceneId, objId)
	            	--if IsHaveSpecificImpact( sceneId, objId, 9011) == 1 or IsHaveSpecificImpact( sceneId, objId, 9013) == 1 then --江湖请柬
	            	if IsHaveSpecificImpact( sceneId, objId, 7510) == 1 or IsHaveSpecificImpact( sceneId, objId, 7511) == 1  or IsHaveSpecificImpact( sceneId, objId, 9007) == 1 then --双倍经验
	            		if kind == 0 then
	            			local baseexp = x700022_g_BonusTab[1].exp*level*x700022_GetLevelExpMulti(sceneId, objId)
	            			local exp = baseexp
	            			local weight = x700022_GetWuxingExpWeight(sceneId, objId)
	            			exp = exp  + baseexp*weight
	            			if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --朝迋请柬
	            				exp = exp  + baseexp*0.35
							end
							if IsHaveSpecificImpact( sceneId, objId, 9011) == 1 or IsHaveSpecificImpact( sceneId, objId, 9013) == 1 then --请柬
								exp = exp  + baseexp*0.25
							end
	            			local suit = GetSuitExpWeight(sceneId,objId)
	            			if suit > 0 then
	            				exp = exp  + baseexp*(suit/100)
	            			end
							exp = floor(exp + baseexp)
							if expParam > 1.0 then
								exp = exp * expParam
							end
							exp = floor(exp)
							if baseexp*2.80 < exp then	
								local playerName = GetName(sceneId, objId)
								local msg = "FUBENERR "..playerName.." level "..level.." baseexp "..baseexp.." exp "..exp
								WriteLog(1,msg)
							end
							AddExp(sceneId, objId, exp)
							ExecShituExpAddition(sceneId, objId, baseexp)
							AddActiveHorseExp(sceneId,objId,exp,1 )
						elseif kind == 1 then
							local sw = floor(level*x700022_g_BonusTab[1].shenwang*2)
							SetShengWang( sceneId, objId, GetShengWang( sceneId, objId) + sw)
							local msg = format("你获得了%d点声望值。",sw)
							Msg2Player(sceneId, objId, msg, 0, 2)
        					Msg2Player(sceneId, objId, msg, 0, 3)
						elseif kind == 2 then
							local multi = 2
							if IsHaveSpecificImpact( sceneId, objId, 9015) == 1 then --天赋丹
		            			multi = multi + 1
		            		end
		            		if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --朝迋请柬
								multi = multi + 0.20
							end
							local inh =  floor(level*x700022_g_BonusTab[1].inh*multi)
							
							if level >= 80 then
								local refixInh = AddInherenceExp(sceneId, objId, inh)
								local msg = format("你获得了%d点天赋值。",refixInh)
								Msg2Player(sceneId, objId, msg, 0, 2)
	        					Msg2Player(sceneId, objId, msg, 0, 3)
							else
								local baseexp = x700022_g_BonusTab[1].exp*level*x700022_GetLevelExpMulti(sceneId, objId)
		            			local exp = baseexp
		            			local weight = x700022_GetWuxingExpWeight(sceneId, objId)
		            			exp = exp  + baseexp*weight
		            			if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --朝迋请柬
		            				exp = exp  + baseexp*0.35
								end
								if IsHaveSpecificImpact( sceneId, objId, 9011) == 1 or IsHaveSpecificImpact( sceneId, objId, 9013) == 1 then --请柬
									exp = exp  + baseexp*0.25
								end
		            			local suit = GetSuitExpWeight(sceneId,objId)
		            			if suit > 0 then
		            				exp = exp  + baseexp*(suit/100)
		            			end
								exp = floor(exp + baseexp)
								if expParam > 1.0 then
									exp = exp * expParam
								end
								exp = floor(exp)
								AddExp(sceneId, objId, exp)
								ExecShituExpAddition(sceneId, objId, baseexp)
								AddActiveHorseExp(sceneId,objId,exp,1 )
							end
						end
					else
						if kind == 0 then
							local baseexp = x700022_g_BonusTab[1].exp*level*x700022_GetLevelExpMulti(sceneId, objId)
	            			local exp = baseexp
	            			local weight = x700022_GetWuxingExpWeight(sceneId, objId)
	            			exp = exp  + baseexp*weight
	            			if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --朝迋请柬
	            				exp = exp  + baseexp*0.35
							end
							if IsHaveSpecificImpact( sceneId, objId, 9011) == 1 or IsHaveSpecificImpact( sceneId, objId, 9013) == 1 then --请柬
								exp = exp  + baseexp*0.25
							end
	            			local suit = GetSuitExpWeight(sceneId,objId)
	            			if suit > 0 then
	            				exp = exp  + baseexp*(suit/100)
	            			end
							if expParam > 1.0 then
								exp = exp * expParam
							end
							exp = floor(exp)
							if baseexp*2.80 < exp then	
								local playerName = GetName(sceneId, objId)
								local msg = "FUBENERR "..playerName.." level "..level.." baseexp "..baseexp.." exp "..exp
								WriteLog(1,msg)
							end
							AddExp(sceneId, objId, exp)
							ExecShituExpAddition(sceneId, objId, baseexp)
							AddActiveHorseExp(sceneId,objId,exp,1 )
						elseif kind == 1 then
							local sw = floor(level*x700022_g_BonusTab[1].shenwang)
							SetShengWang( sceneId, objId, GetShengWang( sceneId, objId) + sw)
							local msg = format("你获得了%d点声望值。",sw)
							Msg2Player(sceneId, objId, msg, 0, 2)
        					Msg2Player(sceneId, objId, msg, 0, 3)
						elseif kind == 2 then
							local multi = 1
							if IsHaveSpecificImpact( sceneId, objId, 9015) == 1 then --天赋丹
		            			multi = multi + 1
		            		end
		            		if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --朝迋请柬
								multi = multi + 0.20
							end
							local inh =  floor(level*x700022_g_BonusTab[1].inh*multi)
							if level >= 80 then
								local refixInh = AddInherenceExp(sceneId, objId, inh)
								local msg = format("你获得了%d点天赋值。",refixInh)
								Msg2Player(sceneId, objId, msg, 0, 2)
	        					Msg2Player(sceneId, objId, msg, 0, 3)
	        				else
	        					local baseexp = x700022_g_BonusTab[1].exp*level*x700022_GetLevelExpMulti(sceneId, objId)
		            			local exp = baseexp
		            			local weight = x700022_GetWuxingExpWeight(sceneId, objId)
		            			exp = exp  + baseexp*weight
		            			if IsHaveSpecificImpact( sceneId, objId, 9012) == 1 then --朝迋请柬
		            				exp = exp  + baseexp*0.35
								end
								if IsHaveSpecificImpact( sceneId, objId, 9011) == 1 or IsHaveSpecificImpact( sceneId, objId, 9013) == 1 then --请柬
									exp = exp  + baseexp*0.25
								end
		            			local suit = GetSuitExpWeight(sceneId,objId)
		            			if suit > 0 then
		            				exp = exp  + baseexp*(suit/100)
		            			end
								if expParam > 1.0 then
									exp = exp * expParam
								end
								exp = floor(exp)
								AddExp(sceneId, objId, exp)
								ExecShituExpAddition(sceneId, objId, baseexp)
								AddActiveHorseExp(sceneId,objId,exp,1 )
	        				end
						end
					end
	            end
	        end
	    end
	end
end


function x700022_AddBouns(sceneId, selfId)

	local kind = GetFubenData_Param(sceneId, x700022_CSP_FUBEN_KIND )
	x700022_AddFactBouns(sceneId, x700022_IsBoss(sceneId, selfId), kind)
			
end


function x700022_OnDie(sceneId, selfId, killerId)
	local fin = GetFubenData_Param( sceneId, x700022_CSP_FINISH)
	if fin == 1 then
		return
	end
	
	x700022_AddBouns(sceneId, selfId)
	
	
	for i,item in x700022_g_MonsterTab[sceneId] do 
		for j,s in item do
			--print("s.tick",s.tick)
			if s ~= nil and s.monid == selfId then
				s = nil
				x700022_g_MonsterTab[sceneId][i][j] = nil
				--break
			end
		end
	end----------------------
	
	
	
	local nDieCount = GetFubenData_Param(sceneId, x700022_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700022_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	----------------------------------- 周卡 ----------------------------------
    local fubenlevel = GetFubenData_Param(sceneId, x700022_CSP_FUBENLEVEL ) ;
   if fubenlevel >= 0 then 
	local buffId1 =9011
	local buffId2 =9013
	local buffId3 =9012

	local humancount = GetFuben_PlayerCount(sceneId);

	--通知玩家
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		local bHaveImpact1 = IsHaveSpecificImpact( sceneId, humanId, buffId1 )
		local bHaveImpact2 = IsHaveSpecificImpact( sceneId, humanId, buffId2 )
		local bHaveImpact3 = IsHaveSpecificImpact( sceneId, humanId, buffId3 )
			
		local nLevel = GetLevel(sceneId, humanId)

		if bHaveImpact1 == 1 or bHaveImpact2 == 1 or bHaveImpact3 == 1 then
			local nMoney = nLevel*2

			local strMoney = x700022_GetMoneyName(sceneId,nMoney)
			local str = format("请柬使您额外获得%s的现银",strMoney)
			AddMoney(sceneId, humanId, 0, nMoney)--银卡为1
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId,str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, humanId);
		else
			local nMoney = nLevel*2

			local strMoney = x700022_GetMoneyName(sceneId,nMoney)
			local str = format("杀死怪物使您额外获得%s的银卡",strMoney)
			AddMoney(sceneId, humanId, 1, nMoney)--银卡为1
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId,str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, humanId);
		end
		
	end
	end


	----------------------------------- 周卡end ----------------------------------


	local bossid = GetFubenData_Param(sceneId, x700022_CSP_BOSS_ID)
	--local bossid2 = GetFubenData_Param(sceneId, x700022_CSP_BOSS_ID2)
	--local bossid3 = GetFubenData_Param(sceneId, x700022_CSP_BOSS_ID3)
	--local bossid4 = GetFubenData_Param(sceneId, x700022_CSP_BOSS_ID4)
	if bossid == selfId then
		SetFubenData_Param(sceneId, x700022_CSP_BOSS_ID, -2)
		bossid = -2
--	elseif bossid2 == selfId then
--		SetFubenData_Param(sceneId, x700022_CSP_BOSS_ID2, -2)
--		bossid2 = -2
--	elseif bossid3 == selfId then
--		SetFubenData_Param(sceneId, x700022_CSP_BOSS_ID3, -2)
--		bossid3 = -2
--	elseif bossid4 == selfId then
--		SetFubenData_Param(sceneId, x700022_CSP_BOSS_ID4, -2)
--		bossid4 = -2
	end

	local country = GetCurCountry(sceneId, selfId)	
	
	--print("x700022_OnDie",selfId,bossid,bossid2,bossid3,bossid4)
	--if bossid== -2 and bossid2== -2 and bossid3== -2 and bossid4== -2 then
	if bossid== -2 then
		SetFubenData_Param( sceneId, x700022_CSP_FINISH,1)
		x700022_ShowTipsToAll(sceneId, "随着魔君陆续倒下，轮回台渐渐恢复了平静。")

		local nNpcId = GetFubenData_Param(sceneId, x700022_CSP_NPC_ID )
		NpcTalk(sceneId, nNpcId, "来我这里，我帮你们回到王城！",  -1)
					
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)
		
		if GetFubenData_Param( sceneId, x700022_CSP_XINSHOU_FLAG) == 1 then
			SetGrowPointIntervalContainer( sceneId, x700022_g_nGrowpointType, 1000)
		end
--		--//--------------------------- 世界喊话 Start--------------------
--		--杀死所有 boss
--		local nowTickCount = GetFubenData_Param(sceneId, x700022_CSP_TICKCOUNT)
--
--		local nowTime = x700022_g_TickTime* nowTickCount;
--
--		local nMinute = floor(nowTime/60)
--		local nSec = mod(nowTime,60)
--
--			
--		local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--		-------- if killed by pet -----------------
--		local nKillerType = GetObjType(sceneId, killerId)
--		--PrintStr(nKillerType)
--		if nKillerType== 3 then
--			local nOwnerId = GetOwnerID(sceneId, killerId)
--			strPlayerName = GetName(sceneId, nOwnerId)
--		end
--		--------- end -------------------------------
--
--		local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--		local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件
--
--		
--		
--		LuaAllScenceM2Wrold (sceneId,"#G"..strPlayerName.."#R和他的队友用了#G"..strKillTime.."#R击败了巨掌玄冰！轮回台，又恢复了以往的平静……", 0, 1)
--		
--
--		
		
		--//--------------------------- 世界喊话 end----------------------

	else
		local nCurMonsterCount = GetFubenData_Param(sceneId, x700022_CSP_MONSTER_COUNT)-1 
		--print("OnDie=============>",nCurMonsterCount)
		SetFubenData_Param(sceneId, x700022_CSP_MONSTER_COUNT, nCurMonsterCount)
		if nCurMonsterCount == 0 then
			x700022_OnAllMonsterDead( sceneId)
		end
	end

	

	
end

function x700022_OnAllMonsterDead( sceneId)
	local nCurrentStep = GetFubenData_Param(sceneId, x700022_CSP_CURRENTSTEP);

	
	if nCurrentStep<=0 then
		return
	end



	local nLen = 0;
	for i,item in x700022_g_TimeDriverList do
		nLen = nLen+1
	end

	if nCurrentStep> nLen then
		return
	end
	
	local nNextStepTime = x700022_g_TimeDriverList[nCurrentStep];
	
	SetFubenData_Param(sceneId, x700022_CSP_CURRENTSTEP_TICKCOUNT, nNextStepTime-1)
	
	


end

function x700022_CreateSubmitNpc( sceneId)
	 if x700022_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700022_g_SubmitNPC.type, x700022_g_SubmitNPC.x, x700022_g_SubmitNPC.z, 3, 0, -1, x700022_g_SubmitNPC.guid, -1,-1,x700022_g_SubmitNPC.facedir,  "", x700022_g_SubmitNPC.title)
	 else
		CreateMonster(sceneId, x700022_g_SubmitNPC.type, x700022_g_SubmitNPC.x, x700022_g_SubmitNPC.z, 3, 0, -1, x700022_g_SubmitNPC.guid, -1,-1,x700022_g_SubmitNPC.facedir)
	 end
	 
end



function x700022_GetMoneyName(sceneId,nMoney)
	local ding = floor(nMoney/(1000*1000))
	local liang = floor((nMoney-ding*1000*1000)/1000)
	local wen = nMoney-(ding*1000*1000+liang*1000)

	local str=""
	if ding>0 then
		str = str..format("%d锭",ding)
	end

	if liang>0 then
		str = str..format("%d两",liang)
	end

	if wen>0 then
		str = str..format("%d文",wen)
	end

	return str;
	
end

