x303006_g_scriptId 					=   303006

-------------------------------------------------------------
--队伍A的信息
-------------------------------------------------------------
x303006_TeamInfoA					= {}

x303006_TeamInfoA_MemberCount		= {}
x303006_TeamInfoA_Score				= {}
x303006_TeamInfoA_Power				= {}

-------------------------------------------------------------
--队伍B的信息
-------------------------------------------------------------									  
x303006_TeamInfoB					= {}
									  
x303006_TeamInfoB_MemberCount		= {}
x303006_TeamInfoB_Score				= {}
x303006_TeamInfoB_Power				= {}
									  
-------------------------------------------------------------
--其他信息
-------------------------------------------------------------									  									  
x303006_LevelFlag					= {}
x303006_BattleFlag					= {}
x303006_MatchLevel					= {}
x303006_MinMatchLevel				= 60				--自适应级别最小级别限制
x303006_MaxMatchLevel				= 160				--自适应级别最大级别限制
x303006_AutoLevelEnableFlag			= 1					--自适应级别开关

-------------------------------------------------------------
--野外怪物信息
-------------------------------------------------------------
x303006_Monster_MF4					= {}				--野外怪信息,这个会定时刷新,创建的时候会设置相应位置的数据,死亡会清空相应位置的数据
x303006_Monster_MF5					= {}				--唯一一个野外BOSS,创建的时候会设置这个数据,死亡的时候会清空这个数据

-------------------------------------------------------------
--基地标记
-------------------------------------------------------------
x303006_BossDieFlag					= {}   				-- 0:双方都在  1:A方Boss死亡 2:B方Boss死亡

--储存怪物的ID
x303006_BossLftID1					= {}			--左路BOSS1  0 100
x303006_BossMidID1					= {}			--中路BOSS1 10 110
x303006_BossRhtID1					= {}			--右路BOSS1 20 120

x303006_BossLftID2					= {}			--左路BOSS2  1 101
x303006_BossMidID2					= {}			--中路BOSS2 11 111
x303006_BossRhtID2					= {}			--右路BOSS2 21 121

x303006_BossLftID3					= {}			--左路BOSS3  2 102
x303006_BossMidID3					= {}			--中路BOSS3 12 112
x303006_BossRhtID3					= {}			--右路BOSS3 22 122

x303006_BossLftID4					= {}			--左路BOSS4  3 103
x303006_BossMidID4					= {}	--中路BOSS4 13 13 113 113
x303006_BossRhtID4					= {}			--右路BOSS4 23 123

x303006_BossMidID5					= {}	--中路BOSS5 31 31 131 131

x303006_BossMidID6					= {}			--中路BOSS3 50 150

x303006_BossMid5DieFlag				= {}			--中路BOSS5死亡标记


--影子建筑
x303006_BossLftID1_Attack			= {}			--左路BOSS1  0 100
x303006_BossMidID1_Attack			= {}			--中路BOSS1 10 110
x303006_BossRhtID1_Attack			= {}			--右路BOSS1 20 120

x303006_BossLftID2_Attack			= {}			--左路BOSS2  1 101
x303006_BossMidID2_Attack			= {}			--中路BOSS2 11 111
x303006_BossRhtID2_Attack			= {}			--右路BOSS2 21 121

x303006_BossLftID3_Attack			= {}			--左路BOSS3  2 102
x303006_BossMidID3_Attack			= {}			--中路BOSS3 12 112
x303006_BossRhtID3_Attack			= {}			--右路BOSS3 22 122

x303006_BossLftID4_Attack			= {}			--左路BOSS4  3 103
x303006_BossMidID4_Attack			= {}	--中路BOSS4 13 13 113 113
x303006_BossRhtID4_Attack			= {}			--右路BOSS4 23 123

x303006_BossMidID5_Attack			= {}	--中路BOSS5 31 31 131 131


--箭塔或基地血量信息
x303006_BossLftID1_HP				= {}			--左路BOSS1  0 100
x303006_BossMidID1_HP				= {}			--中路BOSS1 10 110
x303006_BossRhtID1_HP				= {}			--右路BOSS1 20 120

x303006_BossLftID2_HP				= {}			--左路BOSS2  1 101
x303006_BossMidID2_HP				= {}			--中路BOSS2 11 111
x303006_BossRhtID2_HP				= {}			--右路BOSS2 21 121

x303006_BossLftID3_HP				= {}			--左路BOSS3  2 102
x303006_BossMidID3_HP				= {}			--中路BOSS3 12 112
x303006_BossRhtID3_HP				= {}			--右路BOSS3 22 122

x303006_BossLftID4_HP				= {}			--左路BOSS4  3 103
x303006_BossMidID4_HP				= {}	--中路BOSS4 13 13 113 113
x303006_BossRhtID4_HP				= {}			--右路BOSS4 23 123

x303006_BossMidID5_HP				= {}	--中路BOSS5 31 31 131 131

x303006_BossMidID6_HP				= {}			--中路BOSS3 50 150


x303006_g_Player					= {}			-- 小地图显示用
x303006_g_Ta						= {}			-- 小地图显示用
x303006_g_Texiao					= {}			-- 小地图被攻击特效显示间隔

--箭塔传送信息
x303006_TransPos					= {
										--札木合军
										{guid=170006,x=61, z= 36,objType=0,objName="【传送】上路前锋箭塔",objMsg="上路前锋箭塔告急"},	--上路
										{guid=170007,x=135,z= 30,objType=0,objName="【传送】上路中部箭塔",objMsg="上路中部箭塔告急"},
										{guid=170008,x=184,z= 32,objType=0,objName="【传送】上路后卫箭塔",objMsg="上路后卫箭塔告急"},
										                                                                        
										{guid=170009,x=144,z=103,objType=0,objName="【传送】中路前锋箭塔",objMsg="中路前锋箭塔告急"},	--中路
										{guid=170010,x=163,z= 75,objType=0,objName="【传送】中路中部箭塔",objMsg="中路中部箭塔告急"},
										{guid=170011,x=190,z= 62,objType=0,objName="【传送】中路后卫箭塔",objMsg="中路后卫箭塔告急"},
										                                                                        
										{guid=170012,x=228,z=170,objType=0,objName="【传送】下路前锋箭塔",objMsg="下路前锋箭塔告急"},	--下路
										{guid=170013,x=227,z=109,objType=0,objName="【传送】下路中部箭塔",objMsg="下路中部箭塔告急"},
										{guid=170014,x=227,z=76 ,objType=0,objName="【传送】下路后卫箭塔",objMsg="下路后卫箭塔告急"},
										
										{guid=170015,x=-1, z=-1,objType=1,objName="【传送】大帐主箭塔",objMsg="大帐主箭塔告急"},	--第五排基地箭塔
										{guid=170016,x=-1, z=-1,objType=1,objName="【传送】大帐主箭塔",objMsg="大帐主箭塔告急"},
										
										
										--铁木真军										                                                                        
										{guid=170017,x= 29, z=97, objType=0,objName="【传送】上路前锋箭塔",objMsg="上路前锋箭塔告急"},	--上路
										{guid=170018,x= 27, z=152,objType=0,objName="【传送】上路中部箭塔",objMsg="上路中部箭塔告急"},
										{guid=170019,x= 29, z=186,objType=0,objName="【传送】上路后卫箭塔",objMsg="上路后卫箭塔告急"},
										                                                                        
										{guid=170020,x=126,z=154,objType=0,objName="【传送】中路前锋箭塔",objMsg="中路前锋箭塔告急"},	--中路
										{guid=170021,x= 90,z=176,objType=0,objName="【传送】中路中部箭塔",objMsg="中路中部箭塔告急"},
										{guid=170022,x= 65,z=194,objType=0,objName="【传送】中路后卫箭塔",objMsg="中路后卫箭塔告急"},
										                                                                        
										{guid=170023,x=198,z=226,objType=0,objName="【传送】下路前锋箭塔",objMsg="下路前锋箭塔告急"},	--下路
										{guid=170024,x=126,z=228,objType=0,objName="【传送】下路中部箭塔",objMsg="下路中部箭塔告急"},
										{guid=170025,x= 74,z=229,objType=0,objName="【传送】下路后卫箭塔",objMsg="下路后卫箭塔告急"},
										
										{guid=170026,x=-1, z=-1,objType=1,objName="【传送】大帐主箭塔",objMsg="大帐主箭塔告急"},	--第五排基地箭塔
										{guid=170027,x=-1, z=-1,objType=1,objName="【传送】大帐主箭塔",objMsg="大帐主箭塔告急"},
									  }


--怪物创建信息
x303006_MonsterLftCreateFlag		= {}		--左路Monster创建信息
x303006_MonsterMidCreateFlag		= {}		--中路Monster创建信息
x303006_MonsterRhtCreateFlag		= {}		--右路Monster创建信息

-------------------------------------------------------------
--场景相关信息
-------------------------------------------------------------									  
x303006_SceneInfo					= {}

-------------------------------------------------------------
--场景启用相关信息
-------------------------------------------------------------
x303006_g_SceneMapNavPath			= 	{	
											{"zhanchang_liurenzhanchang/zhanchang_liurenzhanchang.scn",	1,1},	--场景1
										}
										
										
-------------------------------------------------------------
--轮空提示
-------------------------------------------------------------										
									

-------------------------------------------------------------
--战场进入位置信息
-------------------------------------------------------------
x303006_g_EnterScenePos				=	{
											{ 	
												{ 27,231},{ 27,231},{ 27,231},{ 27,231},{ 27,231},{ 27,231},
												{ 231,27},{ 231,27},{ 231,27},{ 231,27},{ 231,27},{ 231,27},
											},														--进入场景的坐标，与上面的场景相对应
										}
										
x303006_g_CloseTick					= 	10															--关闭场景倒计时
x303006_g_LimitTotalHoldTime		=	60*60														--战场最大时间
x303006_g_MaxScore					=	200															--战场最大积分
x303006_g_FirstGiveMoney			=	750															--刚进战场时给的钱
x303006_g_FirstGiveBufList			=	{7987}														--刚进战场时加给玩家的BUF列表
x303006_g_Kick_Down					=	4															--踢人倒计时
x303006_g_RefreshMonsterTick		=	60															--刷怪间隔(单位:秒)
x303006_g_RefreshSceneMapJT			=	5															--间隔(单位:秒)
x303006_g_MaxMonsterLimit			=	170															--怪物数量最多限定,即当前场景里的怪物不允许超过这个数量
x303006_g_Monster_MF4_CreatTick		= 	3*60														--10分钟创建一批野外怪物和BOSS,如果已经存在则不创建
x303006_g_BattleMatchOODMsg			=	"您或您的队伍报名参加的【战场】六人战场本次轮空！"		--轮空提示
x303006_g_GrowPointRefreshTick		=	2*60														--刷怪间隔(单位:秒)
x303006_g_GrowPointType				=	542															--战场中唯一的采集点
x303006_g_GrowPointPosList			=	{{171,158},{97,96}}											--采集点随机坐标列表
x303006_g_PowerGoodBuf				=	{7974,7975,7976}											--增益BUF
x303006_g_PowerBadBuf				=	{7981,7982,7983}											--减益BUF
x303006_g_HT_Time					=	10															--箭血被攻击警报提示时间间隔(单位:秒)
x303006_g_Trans_Money				=	100															--传送一次所扣的钱
x303006_g_GameId					=	1261														--玩法ID,记日志用

x303006_g_RoadType					=	{"下","中","上"}
x303006_g_RoadType_Name				=	{"前锋","中部","后卫","备用1","备用2"}

x303006_g_BossTa					=	{
											{"铁木真军%s路的一座箭塔被摧毁了！","铁木真军%s路的一座箭塔被摧毁了！","铁木真军%s路的一座箭塔被摧毁了！"},
											{"札木合军%s路的一座箭塔被摧毁了！","札木合军%s路的一座箭塔被摧毁了！","札木合军%s路的一座箭塔被摧毁了！"}
										}
										
x303006_g_BossTa2					=	{"铁木真军一座大帐主箭塔被摧毁了！","札木合军一座大帐主箭塔被摧毁了！",}

x303006_g_GrowPoint					=	{ "#G玩家#R%s#G夺得了神秘的补给物资,获得了#R%s#G增益效果！","#G玩家#R%s#G夺得了神秘的补给物资,获得了#R%s#G战场货币！","#G玩家#R%s#G夺得了神秘的补给物资,帮助己方在#R%s#G路召来了一波#R援军#G！"}

x303006_g_BossFix_Bekilled			=	{"#R铁木真军#Y的勇士击败了#R妖兽#Y！","#R札木合军#Y的勇士击败了#R妖兽#Y！"}
x303006_g_BossFix_Bonus				=	"#R妖兽#Y出现在#R%s#Y路，帮助他的新主人！"

x303006_g_PowerTips					= 	{
											{"#G铁木真军将士得到了忽必烈皇帝的赏识，士气大增！","#R札木合军将领被杀得丢盔卸甲，兵士们士气大减！","#Y铁木真军将士的勇猛，使得#R%s#Y路出现一批#R增援部队#Y！"},
											{"#G札木合军将士得到了忽必烈皇帝的赏识，士气大增！","#R铁木真军将领被杀得丢盔卸甲，兵士们士气大减！","#Y札木合军将士的勇猛，使得#R%s#Y路出现一批#R增援部队#Y！"},
										}
										
x303006_g_BossTaBeAttached			=	{
											{"#R%s#Y路#R%s箭塔#Y正受到札木合军将士们的猛烈攻击！","#R%s#Y路#R%s箭塔#Y正受到札木合军将士们的猛烈攻击！","#R%s#Y路#R%s箭塔#Y正受到札木合军将士们的猛烈攻击！"},
											{"#R%s#Y路#R%s箭塔#Y正受到铁木真军将士们的猛烈攻击！","#R%s#Y路#R%s箭塔#Y正受到铁木真军将士们的猛烈攻击！","#R%s#Y路#R%s箭塔#Y正受到铁木真军将士们的猛烈攻击！"}
										}
										
x303006_g_BossTaBeAttached2			=	{"#R铁木真军一座大帐主箭塔被攻击了！","#R札木合军一座大帐主箭塔被攻击了！",}
										
x303006_g_BossBaseBeAttached		=	{
											{"#Y铁木真军#R%s#Y路的一座#R兵营#Y被攻击了！","#Y铁木真军#R%s#Y路的一座#R兵营#Y被攻击了！","#Y铁木真军#R%s#Y路的一座#R兵营#Y被攻击了！"},
											{"#Y札木合军#R%s#Y路的一座#R兵营#Y被攻击了！","#Y札木合军#R%s#Y路的一座#R兵营#Y被攻击了！","#Y札木合军#R%s#Y路的一座#R兵营#Y被攻击了！"}
										}
x303006_g_BossBaseMainBeAttached	=   {"#R铁木真军九旄大帐被攻击了！","#R札木合军九旄大帐被攻击了！",}

x303006_g_DangrousText				=	"告急发布"
x303006_g_GohomeText				=	"返回九旄大帐"
x303006_g_TransMoneyError			=	"金钱不足,不能使用"
x303006_g_GrowpointRelive			=	"军需官刚刚从河道经过，并留下了一件神秘的补给物资！"
x303006_g_PlayerDieByPK				=	"英勇的将领%s成功地击杀了%s！"
x303006_g_PlayerDieByNPC			=	{"铁木真军的%s被击落于马下，看来还要勤练身体！","札木合军的%s被击落于马下，看来还要勤练身体！"}
x303006_g_FirstCreateMonster		=	"战鼓已经擂动，初级军营的大门已经打开，演武大赛正式开始！"
x303006_g_OnMonsterFlagChangedTips1	=	{"札木合军节节胜利，%s路已经打开了中级兵营的大门。","铁木真军节节胜利，%s路已经打开了中级兵营的大门。"}
x303006_g_OnMonsterFlagChangedTips2	=	{"札木合军势如破竹，已经打开了高级兵营的大门。","铁木真军势如破竹，已经打开了高级兵营的大门。"}


-------------------------------------------------------------
--战场士气相关数据
-------------------------------------------------------------
x303006_g_PowerRandomList			= {
										{randval = 40,power = 30,},									--己方增益BUF
										{randval = 35,power = 40,},									--敌方减益BUF
										{randval = 25,power = 50 },									--乙方新增攻击兵
									  }
									  
x303006_g_Power_BoilVal				= 50

-------------------------------------------------------------
--玩家基本阵营信息
-------------------------------------------------------------										
x303006_g_CampFlag					= { 5, 6 }														--基础阵营号


-------------------------------------------------------------
--奖励相关
-------------------------------------------------------------
x303006_g_Winner_Bonus_Mark			= 400
x303006_g_Loser_Bonus_Mark			= 100
x303006_g_Other_Bonus_Mark			= 200


-------------------------------------------------------------
--测试变量
-------------------------------------------------------------
--x303006_g_Test						= 1


-------------------------------------------------------------
--相关状态
-------------------------------------------------------------
x303006_g_State_Invalid				= -1
x303006_g_State_Signup				=  0
x303006_g_State_SignupFinished		=  1
x303006_g_State_Begin				=  2
x303006_g_State_End					=  3

x303006_g_CurrentState				= {}


----------------------------------------------------------------------------------------------
--检查级别区域
----------------------------------------------------------------------------------------------
function x303006_OnMapInit(sceneId)
	
	x303006_TeamInfoA[sceneId]					= {	
													{GUID=-1,ENTER=0},
													{GUID=-1,ENTER=0},
													{GUID=-1,ENTER=0},
													{GUID=-1,ENTER=0},
													{GUID=-1,ENTER=0},
													{GUID=-1,ENTER=0},
												  }

	x303006_TeamInfoA_MemberCount[sceneId]			= 0
	x303006_TeamInfoA_Score[sceneId]				= 0
	x303006_TeamInfoA_Power[sceneId]				= 0
	
	--队伍B的信息
	x303006_TeamInfoB[sceneId]					= {	
														{GUID=-1,ENTER=0},
														{GUID=-1,ENTER=0},
														{GUID=-1,ENTER=0},
														{GUID=-1,ENTER=0},
														{GUID=-1,ENTER=0},
														{GUID=-1,ENTER=0},
												  }
										  
	x303006_TeamInfoB_MemberCount[sceneId]		= 0
	x303006_TeamInfoB_Score[sceneId]			= 0
	x303006_TeamInfoB_Power[sceneId]			= 0
	
	
	
	x303006_LevelFlag[sceneId]					= 0
	x303006_BattleFlag[sceneId]					= 0
	x303006_MatchLevel[sceneId]					= 0
	
	
	--野外怪物信息
	x303006_Monster_MF4[sceneId]				= {}				--野外怪信息,这个会定时刷新,创建的时候会设置相应位置的数据,死亡会清空相应位置的数据
	x303006_Monster_MF5[sceneId]				= -1				--唯一一个野外BOSS,创建的时候会设置这个数据,死亡的时候会清空这个数据
	
	--基地标记
	x303006_BossDieFlag[sceneId]				= 0   				-- 0:双方都在  1:A方Boss死亡 2:B方Boss死亡
	
	--储存怪物的ID
	x303006_BossLftID1[sceneId]					= { -1,-1 }			--左路BOSS1  0 100
	x303006_BossMidID1[sceneId]					= { -1,-1 }			--中路BOSS1 10 110
	x303006_BossRhtID1[sceneId]					= { -1,-1 }			--右路BOSS1 20 120
	
	x303006_BossLftID2[sceneId]					= { -1,-1 }			--左路BOSS2  1 101
	x303006_BossMidID2[sceneId]					= { -1,-1 }			--中路BOSS2 11 111
	x303006_BossRhtID2[sceneId]					= { -1,-1 }			--右路BOSS2 21 121
	
	x303006_BossLftID3[sceneId]					= { -1,-1 }			--左路BOSS3  2 102
	x303006_BossMidID3[sceneId]					= { -1,-1 }			--中路BOSS3 12 112
	x303006_BossRhtID3[sceneId]					= { -1,-1 }			--右路BOSS3 22 122
	
	x303006_BossLftID4[sceneId]					= { -1,-1 }			--左路BOSS4  3 103
	x303006_BossMidID4[sceneId]					= { -1,-1,-1,-1 }	--中路BOSS4 13 13 113 113
	x303006_BossRhtID4[sceneId]					= { -1,-1 }			--右路BOSS4 23 123
	
	x303006_BossMidID5[sceneId]					= { -1,-1,-1,-1 }	--中路BOSS5 31 31 131 131
	
	x303006_BossMidID6[sceneId]					= { -1,-1 }			--中路BOSS3 50 150
	
	x303006_BossMid5DieFlag[sceneId]			= { 0,0,}		--中路BOSS5死亡标记
	
	
	--影子建筑
	x303006_BossLftID1_Attack[sceneId]			= { -1,-1 }			--左路BOSS1  0 100
	x303006_BossMidID1_Attack[sceneId]			= { -1,-1 }			--中路BOSS1 10 110
	x303006_BossRhtID1_Attack[sceneId]			= { -1,-1 }			--右路BOSS1 20 120
	
	x303006_BossLftID2_Attack[sceneId]			= { -1,-1 }			--左路BOSS2  1 101
	x303006_BossMidID2_Attack[sceneId]			= { -1,-1 }			--中路BOSS2 11 111
	x303006_BossRhtID2_Attack[sceneId]			= { -1,-1 }			--右路BOSS2 21 121
	
	x303006_BossLftID3_Attack[sceneId]			= { -1,-1 }			--左路BOSS3  2 102
	x303006_BossMidID3_Attack[sceneId]			= { -1,-1 }			--中路BOSS3 12 112
	x303006_BossRhtID3_Attack[sceneId]			= { -1,-1 }			--右路BOSS3 22 122
	
	x303006_BossLftID4_Attack[sceneId]			= { -1,-1 }			--左路BOSS4  3 103
	x303006_BossMidID4_Attack[sceneId]			= { -1,-1,-1,-1 }	--中路BOSS4 13 13 113 113
	x303006_BossRhtID4_Attack[sceneId]			= { -1,-1 }			--右路BOSS4 23 123
	
	x303006_BossMidID5_Attack[sceneId]			= { -1,-1,-1,-1 }	--中路BOSS5 31 31 131 131
	
	
	--箭塔或基地血量信息
	x303006_BossLftID1_HP[sceneId]				= { -1,-1 }			--左路BOSS1  0 100
	x303006_BossMidID1_HP[sceneId]				= { -1,-1 }			--中路BOSS1 10 110
	x303006_BossRhtID1_HP[sceneId]				= { -1,-1 }			--右路BOSS1 20 120
	
	x303006_BossLftID2_HP[sceneId]				= { -1,-1 }			--左路BOSS2  1 101
	x303006_BossMidID2_HP[sceneId]				= { -1,-1 }			--中路BOSS2 11 111
	x303006_BossRhtID2_HP[sceneId]				= { -1,-1 }			--右路BOSS2 21 121
	
	x303006_BossLftID3_HP[sceneId]				= { -1,-1 }			--左路BOSS3  2 102
	x303006_BossMidID3_HP[sceneId]				= { -1,-1 }			--中路BOSS3 12 112
	x303006_BossRhtID3_HP[sceneId]				= { -1,-1 }			--右路BOSS3 22 122
	
	x303006_BossLftID4_HP[sceneId]				= { -1,-1 }			--左路BOSS4  3 103
	x303006_BossMidID4_HP[sceneId]				= { -1,-1,-1,-1 }	--中路BOSS4 13 13 113 113
	x303006_BossRhtID4_HP[sceneId]				= { -1,-1 }			--右路BOSS4 23 123
	
	x303006_BossMidID5_HP[sceneId]				= { -1,-1,-1,-1 }	--中路BOSS5 31 31 131 131
	
	x303006_BossMidID6_HP[sceneId]				= { -1,-1 }			--中路BOSS3 50 150
	
	
	--怪物创建信息
	x303006_MonsterLftCreateFlag[sceneId]		= { 0, 100 }		--左路Monster创建信息
	x303006_MonsterMidCreateFlag[sceneId]		= { 10,110 }		--中路Monster创建信息
	x303006_MonsterRhtCreateFlag[sceneId]		= { 20,120 }		--右路Monster创建信息
	
	--场景相关信息
	x303006_SceneInfo[sceneId]					= {
													TICKCOUNT = 0,
													ISCLOSING = 0,
													LEAVECOUNTDOWN = 0,
													RESULT = 0,
													LIMITHOLDTIME = x303006_g_LimitTotalHoldTime,
													FIRSTCREATE = 0,
													FIRSTCREATE30 = 0,
												  }
										  
	x303006_g_CurrentState[sceneId]				= x303006_g_State_Invalid
	
	-- 小地图显示
	x303006_g_Player[sceneId]					= { 
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0, oldx = 0, oldz = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0, oldx = 0, oldz = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0, oldx = 0, oldz = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0, oldx = 0, oldz = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0, oldx = 0, oldz = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0, oldx = 0, oldz = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0, oldx = 0, oldz = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0, oldx = 0, oldz = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0, oldx = 0, oldz = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0, oldx = 0, oldz = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0, oldx = 0, oldz = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0, oldx = 0, oldz = 0}
												  }
	x303006_g_Ta[sceneId]						= {
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0},
													{camp = -1, id = -1, oldid = -1, hp = 0, oldhp = 0, x = 0, z = 0}
												  }
	x303006_g_Texiao[sceneId] = 0
end

----------------------------------------------------------------------------------------------
--检查级别区域
----------------------------------------------------------------------------------------------
function x303006_CheckLevelRange(sceneId, nMinLevel,nMaxLevel)

	if x303006_AutoLevelEnableFlag == 0 then
		return 1
	end
	
	if x303006_MatchLevel[sceneId] >= nMinLevel and x303006_MatchLevel[sceneId] <= nMaxLevel then
		return 1
	end
	
	return 0
end


----------------------------------------------------------------------------------------------
--检查传送NPC与玩家有效性
----------------------------------------------------------------------------------------------
function x303006_CheckTransNpcAndPlayer(sceneId,selfId,targetId)
	
	--验证NPC是否有效
	if IsObjValid(sceneId,targetId) ~= 1 or GetHp(sceneId,targetId ) <= 0 then
		return 0
	end

	--验证玩家是否有效
	if x303006_CheckPlayerValid( sceneId,selfId ) ~= 1 then
		return 0
	end
	
	
	local nSelfCamp   = GetCurCamp(sceneId,selfId )
	local nTargetCamp = GetMonsterCamp(sceneId,targetId)
	
	if nSelfCamp ~= nTargetCamp then
		
		if nSelfCamp == 5 and nTargetCamp == 28 then
			return 1
		end
		
		if nSelfCamp == 6 and nTargetCamp == 29 then
			return 1
		end
	else
		return 1
	end
	
	return 0
end


----------------------------------------------------------------------------------------------
--查找传送NPC
----------------------------------------------------------------------------------------------
function x303006_FindTransNpc( sceneId,targetId)
	
	--先验证NPC是否是传送列表中的
	local nFind = -1
	local nGUID = GetMonsterGUID(sceneId,targetId)
	for i,item in x303006_TransPos do
		if item.guid == nGUID then
			nFind = i
			break
		end		
	end
	
	return nFind
	
end


----------------------------------------------------------------------------------------------
--显示传送列表
----------------------------------------------------------------------------------------------
function x303006_OnShowTransEvent( sceneId, selfId, targetId)
	
	--检查NPC与玩家有效性
	if x303006_CheckTransNpcAndPlayer(sceneId,selfId,targetId) ~= 1 then
		return
	end
	
	--查找传送NPC
	local nFind = x303006_FindTransNpc( sceneId,targetId)
	if nFind == -1 then
		return
	end
	
	--取得当前NPC信息
	local nNpcInfo = x303006_TransPos[nFind]
	if nNpcInfo.objType == 0 then

		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"\t一座坚固的箭塔。\n\t#G箭塔间传送需要消耗100战场货币！")
		--AddQuestNumText(sceneId,x303006_g_scriptId,x303006_g_DangrousText,3,nFind + 100000)		--基数放大到十万以上
		AddQuestNumText(sceneId,x303006_g_scriptId,x303006_g_GohomeText,  3,x303006_g_scriptId)	--传回基地
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId)
		
	elseif nNpcInfo.objType == 1 then
		
		local nSelfCamp = GetCurCamp(sceneId,selfId)	
		
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"\t一座守卫着大帐的箭塔，异常坚固。\n\t#G箭塔间传送需要消耗100战场货币！")
		for i,item in x303006_TransPos do
			
			if item.objType ~= 1 then
				
				--检查OBJ是否存在
				local objId = FindMonsterByGUID(sceneId,item.guid)
				if IsObjValid(sceneId,objId) == 1 and GetHp(sceneId,objId) > 0 then
					
					local objCamp = GetMonsterCamp(sceneId,objId)
					
					if nSelfCamp == 5 and ( objCamp == 5 or objCamp == 28 ) then
						AddQuestNumText(sceneId,x303006_g_scriptId,item.objName, 3,i)					
					end
					
					if nSelfCamp == 6 and ( objCamp == 6 or objCamp == 29 ) then
						AddQuestNumText(sceneId,x303006_g_scriptId,item.objName, 3,i)
					end					
				end
			end
		end
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId)
	end
end

----------------------------------------------------------------------------------------------
--默认处理
----------------------------------------------------------------------------------------------
function x303006_ProcEventEntry( sceneId, selfId, targetId, MissionId,nExtId )

	
	if nExtId == nil or nExtId <= 0 then
		x303006_OnShowTransEvent(sceneId,selfId,targetId)
		return		
	end

	--检查NPC与玩家有效性
	if x303006_CheckTransNpcAndPlayer(sceneId,selfId,targetId) ~= 1 then
		return
	end
	
	--检查玩家身上的钱是否足够
	if x303006_GetBattleMoney(sceneId,selfId) < x303006_g_Trans_Money then
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x303006_g_TransMoneyError)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId)
		return
	end
	
	--查找传送NPC
	local nFind = x303006_FindTransNpc( sceneId,targetId)
	if nFind == -1 then
		return
	end
	
	--开始正式处理	
	if nExtId == x303006_g_scriptId then
	
		
		x303006_SubBattleMoney(sceneId,selfId,x303006_g_Trans_Money);
		
		--传回主基地
		local x,z = x303006_GetPlayerPos( sceneId,selfId)
		SetPos(sceneId,selfId,x,z)
		
	elseif nExtId > 100000 then
		--告急信息
		
		local nCurCamp = GetCurCamp(sceneId,selfId)
		local nIndex = nExtId - 100000
		
		if nIndex <= 0 or nIndex > getn(x303006_TransPos) then
			return
		end
		
		
		x303006_SubBattleMoney(sceneId,selfId,x303006_g_Trans_Money);
		
		local item = x303006_TransPos[nIndex]
		
		local humancount = GetScenePlayerCount(sceneId);
		for	i = 0, humancount - 1 do
			local humanId = GetScenePlayerObjId(sceneId, i);
			if IsPlayerStateNormal( sceneId,humanId ) == 1 and GetCurCamp(sceneId,humanId) == nCurCamp then
				LuaScenceM2Player(sceneId,humanId,item.objMsg,GetName(sceneId,humanId),2,1)
			end
		end
		
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,item.objMsg)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId)
		
	elseif nExtId > 0 and nExtId <= getn(x303006_TransPos) then
	
		x303006_SubBattleMoney(sceneId,selfId,x303006_g_Trans_Money);
		
		--基地箭塔传送到其他箭塔
		local item = x303006_TransPos[nExtId]
		SetPos(sceneId,selfId,item.x,item.z)
	end
	
end

----------------------------------------------------------------------------------------------
--显示塔被推毁的提示
----------------------------------------------------------------------------------------------
function x303006_ShowTips_BossTa(sceneId,camp,roadtype)
	
	if camp < 1 or camp > 2 then
		return
	end
	
	if roadtype < 1 or roadtype > 3 then
		return
	end
	
	local msg = format(  x303006_g_BossTa[camp][roadtype],x303006_g_RoadType[roadtype])
	LuaThisScenceM2Wrold(sceneId,msg,5,1)
	
end

----------------------------------------------------------------------------------------------
--显示主基地塔被推毁的信息
----------------------------------------------------------------------------------------------
function x303006_ShowTips_BossTa2(sceneId,camp )
	
	if camp < 1 or camp > 2 then
		return
	end
	
	local msg =   x303006_g_BossTa2[camp]
	LuaThisScenceM2Wrold(sceneId,msg,5,1)
	
end

----------------------------------------------------------------------------------------------
--显示塔被攻击的提示
----------------------------------------------------------------------------------------------
function x303006_ShowTips_BossTaBeAttched(sceneId,camp,roadtype,id )
	
	if camp < 1 or camp > 2 then
		return
	end
	
	if roadtype < 1 or roadtype > 3 then
		return
	end
	
	if id < 1 or id > 5  then
		return
	end
	
	if id == 4 then
		return
	end
	
	local msg
	if id ~= 5 then
		msg = format(  x303006_g_BossTaBeAttached[camp][roadtype],x303006_g_RoadType[roadtype],x303006_g_RoadType_Name[id])
	elseif id == 5 then
		msg = x303006_g_BossTaBeAttached2[camp]
	end
	
	local nCamp = camp + 4
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 and GetCurCamp(sceneId,humanId) == nCamp then
			LuaScenceM2Player(sceneId,humanId,msg,GetName(sceneId,humanId),2,1)
		end
	end
end

----------------------------------------------------------------------------------------------
--显示基地被攻击的提示
----------------------------------------------------------------------------------------------
function x303006_ShowTips_BossBaseBeAttched(sceneId,camp,roadtype )
	
	if camp < 1 or camp > 2 then
		return
	end
	
	if roadtype < 1 or roadtype > 3 then
		return
	end
	
	local msg = format(  x303006_g_BossBaseBeAttached[camp][roadtype],x303006_g_RoadType[roadtype])
	local nCamp = camp + 4
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 and GetCurCamp(sceneId,humanId) == nCamp then
			LuaScenceM2Player(sceneId,humanId,msg,GetName(sceneId,humanId),2,1)
		end
	end
end

----------------------------------------------------------------------------------------------
--显示主基地被攻击的提示
----------------------------------------------------------------------------------------------
function x303006_ShowTips_BossBaseMainBeAttched(sceneId,camp )
	
	if camp < 1 or camp > 2 then
		return
	end
	
	local msg = x303006_g_BossBaseMainBeAttached[camp]
	local nCamp = camp + 4
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 and GetCurCamp(sceneId,humanId) == nCamp then
			LuaScenceM2Player(sceneId,humanId,msg,GetName(sceneId,humanId),2,1)
		end
	end
end

----------------------------------------------------------------------------------------------
--显示采集的提示
----------------------------------------------------------------------------------------------
function x303006_ShowTips_GrowPoint(sceneId,selfId,bonustype,val)

	if bonustype < 1 or bonustype > 3 then
		return
	end

	local name = GetName(sceneId,selfId)
	local camp = GetCurCamp(sceneId,selfId)
	local msg = format(  x303006_g_GrowPoint[bonustype],name,tostring(val))	
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 and GetCurCamp(sceneId,humanId) == camp then
			LuaScenceM2Player(sceneId,humanId,msg,GetName(sceneId,humanId),2,1)
		end
	end
end

----------------------------------------------------------------------------------------------
--野外BOSS被杀提示
----------------------------------------------------------------------------------------------
function x303006_ShowTips_BossKilled(sceneId,selfId,tipsType)

	if tipsType < 1 or tipsType > 2 then
		return
	end

	local name = GetName(sceneId,selfId)
	local msg = format(  x303006_g_BossFix_Bekilled[tipsType],name)
	LuaThisScenceM2Wrold(sceneId,msg,2,1)
end

----------------------------------------------------------------------------------------------
--野外BOSS被杀奖励
----------------------------------------------------------------------------------------------
function x303006_ShowTips_BossKilledBonus(sceneId,roadtype)

	if roadtype < 1 or roadtype > 3 then
		return
	end

	if roadtype == 3 then 
		roadtype = 1 
	elseif roadtype == 1 then
		roadtype = 3
	end

	local msg = format(  x303006_g_BossFix_Bonus,x303006_g_RoadType[roadtype])
	LuaThisScenceM2Wrold(sceneId,msg,2,1)
end

----------------------------------------------------------------------------------------------
--野外BOSS被杀奖励
----------------------------------------------------------------------------------------------
function x303006_ShowTips_PowerTips(sceneId,camp,bonstype,val)

	if camp < 1 or camp > 2 then
		return
	end
	
	if bonstype < 1 or bonstype > 3 then
		return
	end
	
	local str = ""
	if val~= nil then
		str = val
	end

	local msg = format(  x303006_g_PowerTips[camp][bonstype],str)
	LuaThisScenceM2Wrold(sceneId,msg,2,1)
end

----------------------------------------------------------------------------------------------
--第一次创建怪物显示提示
----------------------------------------------------------------------------------------------
function x303006_ShowTips_FirstCreateMonster( sceneId)
	
	LuaThisScenceM2Wrold(sceneId,x303006_g_FirstCreateMonster,2,1)
	
end

----------------------------------------------------------------------------------------------
--显示怪物创建改变提示
----------------------------------------------------------------------------------------------
function x303006_ShowTips_MonsterFlagChanged_1(sceneId,camp,roadtype )

	if camp < 1 or camp > 2 then
		return
	end
	
	if roadtype < 1 or roadtype > 3 then
		return
	end
	
	--if roadtype == 3 then 
	--	roadtype = 1 
	--elseif roadtype == 1 then
	--	roadtype = 3
	--end
	
	local msg = format(x303006_g_OnMonsterFlagChangedTips1[camp],x303006_g_RoadType[roadtype])
	LuaThisScenceM2Wrold(sceneId,msg,2,1)
	
end

----------------------------------------------------------------------------------------------
--显示怪物创建改变提示
----------------------------------------------------------------------------------------------
function x303006_ShowTips_MonsterFlagChanged_2(sceneId,camp )
	
	if camp < 1 or camp > 2 then
		return
	end
	LuaThisScenceM2Wrold(sceneId,x303006_g_OnMonsterFlagChangedTips2[camp],2,1)
end


----------------------------------------------------------------------------------------------
--取得2V2战场类型
----------------------------------------------------------------------------------------------
function x303006_GetBattleSceneType(sceneId)

    local name = GetBattleSceneName(sceneId)
    for i,item in x303006_g_SceneMapNavPath do
        if name == item[1] then
            return item[2]
        end
    end

    return -1
	
end

----------------------------------------------------------------------------------------------
--战场是否被启用
----------------------------------------------------------------------------------------------
function x303006_IsBattleSceneValid(sceneId)

    local name = GetBattleSceneName(sceneId)
    for i,item in x303006_g_SceneMapNavPath do
        if name == item[1] then
            return item[3]
        end
    end

    return 0
	
end

----------------------------------------------------------------------------------------------
--普通场景状态处理
----------------------------------------------------------------------------------------------
function x303006_OnBattleState_NormalScene(sceneId,state)

	--限定为大都和王城
	if sceneId ~= 0 and sceneId ~= 50 and sceneId ~= 150 and sceneId ~= 250 and sceneId ~= 350 then
		return
	end

	--相关状态处理
	if state == x303006_g_State_Signup then

        if x303006_g_CurrentState[sceneId] ~= x303006_g_State_Signup then
            WriteLog(1,format("P6BL:x303006_g_State_Signup,SceneId=%d ",sceneId  ))
        end
        
        x303006_g_CurrentState[sceneId] = x303006_g_State_Signup
        
    elseif state == x303006_g_State_SignupFinished then

        if x303006_g_CurrentState[sceneId] ~= x303006_g_State_SignupFinished then
            WriteLog(1,format("P6BL:x303006_g_State_SignupFinished,SceneId=%d ",sceneId ))
        end
        
        x303006_g_CurrentState[sceneId] = x303006_g_State_SignupFinished

    end
    
end

----------------------------------------------------------------------------------------------
--战场场景状态处理
----------------------------------------------------------------------------------------------
function x303006_OnBattleState_BattleScene(sceneId,state)

	--检查是否是PVP6v6竞技场
    local nBattleScene = x303006_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303006_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end

    if state == x303006_g_State_Signup then
    	
    	--如果已经开始，特殊处理一下
    	if x303006_g_CurrentState[sceneId] == x303006_g_State_Begin then
    		return
    	end
    	
        if x303006_g_CurrentState[sceneId] ~= x303006_g_State_Signup then
            WriteLog(1,format("P6BL:x303006_g_State_Signup,SceneId=%d,2 ",sceneId  ))
        end
        
        x303006_g_CurrentState[sceneId] = x303006_g_State_Signup
        PVP6v6RegisterScene( sceneId )

    elseif state == x303006_g_State_Begin then

        --检查状态是否已经置过
        if x303006_g_CurrentState[sceneId] ~= x303006_g_State_Begin then
            WriteLog(1,format("P6BL:x303006_g_State_Begin,SceneId=%d,2",sceneId ))
        end

        --设置基本数据            
        x303006_g_CurrentState[sceneId] = x303006_g_State_Begin
        x303006_OnBattleSceneReady( sceneId,x303006_g_LimitTotalHoldTime )

    elseif state == x303006_g_State_End then

        if x303006_g_CurrentState[sceneId] > x303006_g_State_Begin or x303006_g_CurrentState[sceneId] < x303006_g_State_Signup then
            
            --记录日志
            WriteLog(1,format("P6BL:x303006_g_State_End,Result:nState > x303006_g_State_Begin or nState < x303006_g_State_Signup  SceneId=%d,state=%d,2",sceneId, x303006_g_CurrentState[sceneId] ))

            --根据玩法的脚本的不同，进行相关初始化回调
            x303006_OnBattleSceneClose( sceneId,0 )

            --记录日志
            WriteLog(1,format("P6BL:x303006_g_State_End, SceneId=%d,2",sceneId ))
            return
        end

        --设置状态，活动结束
		x303006_g_CurrentState[sceneId] = x303006_g_State_End
        x303006_OnBattleSceneClose( sceneId,1 )

        --记录日志
        WriteLog(1,format("P6BL:x303006_g_State_End, SceneId=%d,2",sceneId ))
    end
end

----------------------------------------------------------------------------------------------
--战场状态
----------------------------------------------------------------------------------------------
function x303006_OnBattleState(sceneId,state)

	local sceneType = GetSceneType(sceneId);
	if sceneType == 0 then
		x303006_OnBattleState_NormalScene(sceneId,state)
	elseif sceneType == 2 then
		x303006_OnBattleState_BattleScene(sceneId,state)
	end
end


----------------------------------------------------------------------------------------------
--战场是否正在报名
----------------------------------------------------------------------------------------------
function x303006_IsBattleSignup( sceneId )

	if sceneId == 0  or sceneId == 50 or sceneId == 150 or sceneId == 250 or sceneId == 350 then
		if x303006_g_CurrentState[sceneId] == x303006_g_State_Signup then
			return 1
		end
	end
	
	return 0
	
end

----------------------------------------------------------------------------------------------
--初始化队伍A
----------------------------------------------------------------------------------------------
function x303006_OnPVP6v6SetTeamA( sceneId,memcount, ta1,ta2,ta3,ta4,ta5,ta6 )
	
	--队伍A的信息
	x303006_TeamInfoA[sceneId]					= {	
											{GUID=NumberCastIntToUInt(ta1),ENTER=0},
											{GUID=NumberCastIntToUInt(ta2),ENTER=0},
											{GUID=NumberCastIntToUInt(ta3),ENTER=0},
											{GUID=NumberCastIntToUInt(ta4),ENTER=0},
											{GUID=NumberCastIntToUInt(ta5),ENTER=0},
											{GUID=NumberCastIntToUInt(ta6),ENTER=0},
										  }
	
	x303006_TeamInfoA_MemberCount[sceneId] = memcount
	x303006_TeamInfoA_Score[sceneId] = 0
	x303006_TeamInfoA_Power[sceneId] = 0
	
	if memcount > 0 then
		WriteLog(1,format("x303006_OnPVP6v6SetTeamA setmemcount = %d",memcount))
	end
	
	for i,itm in x303006_TeamInfoA[sceneId] do
		WriteLog(1,format("x303006_OnPVP6v6SetTeamA i=%d GUID=%X",i,itm.GUID))
	end

end

----------------------------------------------------------------------------------------------
--初始化队伍B
----------------------------------------------------------------------------------------------
function x303006_OnPVP6v6SetTeamB( sceneId,memcount, tb1,tb2,tb3,tb4,tb5,tb6 )

	--队伍B的信息								  
	x303006_TeamInfoB[sceneId]					= {	
											{GUID=NumberCastIntToUInt(tb1),ENTER=0},
											{GUID=NumberCastIntToUInt(tb2),ENTER=0},
											{GUID=NumberCastIntToUInt(tb3),ENTER=0},
											{GUID=NumberCastIntToUInt(tb4),ENTER=0},
											{GUID=NumberCastIntToUInt(tb5),ENTER=0},
											{GUID=NumberCastIntToUInt(tb6),ENTER=0},
										  }
										  
	x303006_TeamInfoB_MemberCount[sceneId] = memcount
	x303006_TeamInfoB_Score[sceneId] = 0
	x303006_TeamInfoB_Power[sceneId] = 0
	
	if memcount > 0 then
		WriteLog(1,format("x303006_OnPVP6v6SetTeamB setmemcount = %d",memcount))
	end
	
	for i,itm in x303006_TeamInfoB[sceneId] do
		WriteLog(1,format("x303006_OnPVP6v6SetTeamB i=%d GUID=%X",i,itm.GUID))
	end

end

----------------------------------------------------------------------------------------------
--初始化等级标记
----------------------------------------------------------------------------------------------
function x303006_OnPVP6v6SetLevelFlag(sceneId,nLevelFlag,nMatchLevel)

	--等级差标记
	x303006_LevelFlag[sceneId] 	= nLevelFlag
	x303006_BattleFlag[sceneId] 	= 1
	
	--自适应级别处理
	if x303006_AutoLevelEnableFlag == 1 then
		x303006_MatchLevel[sceneId]  = nMatchLevel
		if x303006_MatchLevel[sceneId] < x303006_MinMatchLevel then
			x303006_MatchLevel[sceneId] = x303006_MinMatchLevel
		elseif x303006_MatchLevel[sceneId] > x303006_MaxMatchLevel then
			x303006_MatchLevel[sceneId] = x303006_MaxMatchLevel
		end
	end
	
	x303006_Monster_MF4[sceneId] = {}
	x303006_Monster_MF5[sceneId]	= -1
	
	x303006_ResetAllGrowpoint( sceneId )
	
end


---------------------------------------------------------------------------------------------------
--取得玩家阵营
---------------------------------------------------------------------------------------------------
function x303006_GetPlayerCampFlag( sceneId,selfId)
	
	local GUID = GetPlayerGUID(sceneId,selfId)
	
	--判断是否是A队
	for i,itm in x303006_TeamInfoA[sceneId] do
		if GUID == itm.GUID then
			return 0
		end
	end
	
	--判断是否是B队
	for i,itm in x303006_TeamInfoB[sceneId] do
		if GUID == itm.GUID then
			return 1
		end
	end
	
	return -1
	
end

---------------------------------------------------------------------------------------------------
--设置玩家位置
---------------------------------------------------------------------------------------------------
function x303006_GetPlayerPos( sceneId,selfId )
	
	local GUID = GetPlayerGUID(sceneId,selfId)
	local nIndex = x303006_GetBattleSceneType(sceneId)
	
	--如果无效
	if nIndex < 1 or nIndex > getn(x303006_g_EnterScenePos) then
		return 100,100
	end
	
	--A队
	for i,itm in x303006_TeamInfoA[sceneId] do
		
		if GUID == itm.GUID then
			local x = x303006_g_EnterScenePos[nIndex][i][1]
			local z = x303006_g_EnterScenePos[nIndex][i][2]
			return x,z
		end
	end
	
	--B队
	local n = getn(x303006_TeamInfoA[sceneId])
	for i,itm in x303006_TeamInfoB[sceneId] do
		
		if GUID == itm.GUID then
			local x = x303006_g_EnterScenePos[nIndex][i+n][1]
			local z = x303006_g_EnterScenePos[nIndex][i+n][2]
			return x,z
		end
	end
	
	return 100,100
end


----------------------------------------------------------------------------------------------
--请求进入场景
----------------------------------------------------------------------------------------------
function x303006_AskBattleSceneEnter( sceneId,selfId)

	--向GLServer请求进入战场
	PVP6v6AskBattleSceneEnter(sceneId,selfId)
	
end

---------------------------------------------------------------------------------------------------
--玩家进入战场时的处理
---------------------------------------------------------------------------------------------------
function x303006_OnPlayerEnter(sceneId, selfId)

	--检查是否是PVP6v6竞技场
    local nBattleScene = x303006_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303006_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
	
	--对玩家原先的场景进行备份
    local scenePre = GetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE ) - 1
    if scenePre >= 0 then
        
        local CurX = GetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE)
        local CurZ = GetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE)

        SetPlayerBakSceneInfo(sceneId,selfId,scenePre,CurX,CurZ)

        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_SCENE_PRE,0)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSX_PRE,0)
        SetPlayerRuntimeData(sceneId,selfId,RD_HUMAN_POSZ_PRE,0)

    end
    
	--如果开始关闭，则玩家进入也要踢出去
	local leaveFlag = x303006_SceneInfo[sceneId].ISCLOSING
	if leaveFlag > 0 then
		
		x303006_SetPlayerNeedKick(sceneId,selfId)
		WriteLog(1,format("P6BL:x303006_OnPlayerEnterFinished kick 0 SceneId=%d ",sceneId  ))
		return
	end
	
	--如果玩家无效
	if x303006_CheckPlayerValid(sceneId,selfId ) == 0 then
		
		x303006_SetPlayerNeedKick(sceneId,selfId)
		WriteLog(1,format("P6BL:x303006_OnPlayerEnterFinished kick 1 SceneId=%d ",sceneId  ))
		return
	end
	
	--如果玩家已经进过场景了
	if x303006_GetPlayerEnterSceneFlag( sceneId,selfId ) == 1 then
		
		--给玩家加沉默BUF
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,7985,0)
		
	--	x303006_SetPlayerNeedKick(sceneId,selfId)
	--	WriteLog(1,format("P6BL:x303006_OnPlayerEnterFinished kick 2 SceneId=%d ",sceneId  ))
	--	return
	end
	
	--设置玩家阵营
	local nCampFlag = x303006_GetPlayerCampFlag( sceneId,selfId)
	if nCampFlag < 0 or nCampFlag > 1 then
		
		x303006_SetPlayerNeedKick(sceneId,selfId)
		WriteLog(1,format("P6BL:x303006_OnPlayerEnterFinished kick 3 SceneId=%d ",sceneId  ))
		return
	end
	
	SetCurCamp(sceneId,selfId,x303006_g_CampFlag[nCampFlag+1])

	--设置玩家位置
	local x,z = x303006_GetPlayerPos( sceneId,selfId)
	SetPos(sceneId,selfId,x,z)
	
	--记录一下坐标
	local name = GetName(sceneId,selfId)
	WriteLog(1,format("P6BL:x303006_OnPlayerEnterFinished playerEnter SceneId=%d x = %d, z = %d flag = %d name=%s",sceneId,x,z,nCampFlag ,name ))
	
	--设置客户端相关信息
	SetPVP6v6BattleDisable( sceneId,selfId,0,nCampFlag)
	
	--发送当前积分
	SendPVP6v6BattleScore(sceneId,selfId,x303006_TeamInfoA_Score[sceneId],x303006_TeamInfoB_Score[sceneId])
	
	--发送当前战场里的士气值
	x303006_SendPowerToPlayer(sceneId,selfId)
	
	--添加初始化BUF
	for i,itm in x303006_g_FirstGiveBufList do
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,itm,0)
	end
	
	--初始化战场货币
	x303006_InitBattleMoney(sceneId,selfId)
	
	--设置玩家进入场景标记
	x303006_SetPlayerEnterSceneFlag( sceneId,selfId)
		
	--记录玩法日志
	GamePlayScriptLog(sceneId,selfId,x303006_g_GameId)
	
end

---------------------------------------------------------------------------------------------------
--玩家离开场景
---------------------------------------------------------------------------------------------------
function x303006_OnPlayerLeave( sceneId,selfId)

	local nDebug = 1
	if nDebug == 1 then
		
		local n2v2LevelPre = GetPVP2V2Level(sceneId,selfId)
		local name = GetName(sceneId,selfId)
        WriteLog(1,format("P6BL:x303006_OnPlayerLeave 0 SceneId=%d Name=%s 2v2LevelPre = %d", sceneId, name, n2v2LevelPre  ))
	end

	--检查是否是PVP2v2竞技场
    local nBattleScene = x303006_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303006_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
	
	--如果开始关闭，则玩家离开不处理
	local leaveFlag = x303006_SceneInfo[sceneId].ISCLOSING
	if leaveFlag > 0 then
		return
	end
end

---------------------------------------------------------------------------------------------------
--战场定时器
---------------------------------------------------------------------------------------------------
function x303006_ProcTiming(sceneId, nowTime)

	--检查是否是PVP2v2竞技场
    local nBattleScene = x303006_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303006_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end

	x303006_UpdatePlayerKickState(sceneId)
	x303006_UpdatePVP6v6PlayerReliveDownCount(sceneId)

	local leaveFlag = x303006_SceneInfo[sceneId].ISCLOSING
	if leaveFlag > 0 then

		--提示xx秒后将退出副本
		local leaveCountDown = x303006_SceneInfo[sceneId].LEAVECOUNTDOWN + 1
		x303006_SceneInfo[sceneId].LEAVECOUNTDOWN = leaveCountDown

		if leaveCountDown >= x303006_g_CloseTick then
			
			local humancount = GetScenePlayerCount(sceneId);
			for	i = 0, humancount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i);
                TimerCommand( sceneId, humanId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303006_g_scriptId, -1, -1 );	--发送定时器，做定时器同步

                --调用踢人函数
                x303006_SetPlayerNeedKick(sceneId,humanId)
                WriteLog(1,format("P6BL:x303006_ProcTiming kick 1 SceneId=%d ",sceneId  ))
			end
			
		elseif leaveCountDown < x303006_g_CloseTick then
			
			local kickDown = x303006_g_CloseTick - leaveCountDown
			local nMod = mod(kickDown,5)
			if nMod == 0 then
				local humancount = GetScenePlayerCount(sceneId);
				for	i = 0, humancount - 1 do
					local humanId = GetScenePlayerObjId(sceneId, i);
	 				LuaScenceM2Player( sceneId,humanId,format("本场战斗将在%d秒后关闭", kickDown),GetName(sceneId,humanId),3,1)
				end
			end
		end

	else
		
		if x303006_g_CurrentState[sceneId] ~= x303006_g_State_Begin then
			return
		end
		
		--检查是否可以创建新怪物
		if x303006_BattleFlag[sceneId] == 1 then
		
			--第一个Tick创建BOSS
			if x303006_SceneInfo[sceneId].TICKCOUNT >= 0 and x303006_SceneInfo[sceneId].FIRSTCREATE ~= 1 then				
				
				--置创建标记为TRUE
				x303006_SceneInfo[sceneId].FIRSTCREATE = 1
				
				--先做一些清除操作,防止上次因为某种原因而导致怪物没有被清除
				x303006_OnMonsterDestroy(sceneId,0)
				
				--进行怪物和NPC创建操作				
				x303006_OnCreateShopNPC(sceneId)		--创建商店NPC
				x303006_OnCreateTripNPC(sceneId)		--创建传送NPC
				x303006_OnCreateBoss(sceneId)			--创建主要箭塔及基地
				x303006_OnCreateBossAttack(sceneId)		--创建主要箭塔影子(攻击用)
				x303006_OnCreateMonster_MF4(sceneId,1)	--创建野外怪
				x303006_OnCreateMonster_MF5(sceneId,1)	--创建野外BOSS
			end

			if x303006_SceneInfo[sceneId].TICKCOUNT < 60  then
				--第一批怪30秒创建
				if x303006_SceneInfo[sceneId].TICKCOUNT >= 30 and x303006_SceneInfo[sceneId].FIRSTCREATE30 ~= 1 then
					x303006_SceneInfo[sceneId].FIRSTCREATE30 = 1
					x303006_OnCreateMonster(sceneId)		--创建流程怪
				end
			else
				--以后每批怪间隔x303006_g_RefreshMonsterTick创建
				local nMod = mod(x303006_SceneInfo[sceneId].TICKCOUNT, x303006_g_RefreshMonsterTick)
				if nMod == 0 then
					x303006_OnCreateMonster(sceneId)		--创建流程怪
				end
				
				--每隔x303006_g_Monster_MF4_CreatTick创建一批怪
				nMod = mod(x303006_SceneInfo[sceneId].TICKCOUNT,x303006_g_Monster_MF4_CreatTick)
				if nMod == 0 then
					x303006_OnCreateMonster_MF4(sceneId,0)	--创建野外怪
					x303006_OnCreateMonster_MF5(sceneId,0)	--创建野外BOSS
				end
			end
			
			--每隔x303006_g_GrowPointRefreshTick刷新生长点
			local nMod = mod(x303006_SceneInfo[sceneId].TICKCOUNT,x303006_g_GrowPointRefreshTick)
			if nMod == 0 then
				x303006_ResetAllGrowpoint( sceneId )
			end
			
			--战场BOSS血和时间更新
			x303006_OnUpdateBossHP( sceneId )
			
			--更新地图信息
			x303006_UpdateSceneMap( sceneId )
		end
		
		--战场计时增加
		local nowTickCount = x303006_SceneInfo[sceneId].TICKCOUNT + 1;
		x303006_SceneInfo[sceneId].TICKCOUNT = nowTickCount
		
		--当超过一分钟后，开始检胜利
		if nowTickCount >= 60 then
			if x303006_CheckBattleFinished( sceneId ) == 1 then
				x303006_OnBattleSceneClose( sceneId,2 )
                WriteLog(1,format("P6BL:x303006_ProcTiming sceneId=%d,nowTickCount=%d 000 ",sceneId ,nowTickCount ))
			end
		end
		
		--战场玩家事件	
		x303006_OnPlayerEvent(sceneId,x303006_SceneInfo[sceneId].TICKCOUNT)

		--计时器
		if nowTickCount >= x303006_g_LimitTotalHoldTime then
			local humancount = GetScenePlayerCount(sceneId);
			for i = 0, humancount - 1 do
				local humanId = GetScenePlayerObjId(sceneId, i);
				BeginQuestEvent(sceneId);
					AddQuestText(sceneId, format("本场战斗时间已到，将于%d秒后关闭！",x303006_g_CloseTick));
				EndQuestEvent();
				DispatchQuestTips(sceneId, humanId);
			end
		end

        if nowTickCount == x303006_g_LimitTotalHoldTime then
            x303006_OnBattleSceneClose( sceneId,3 )
            WriteLog(1,format("P6BL:x303006_ProcTiming sceneId=%d,nowTickCount=%d 001 ",sceneId ,nowTickCount ))
        end
	end
end

---------------------------------------------------------------------------------------------------
--玩家死亡
---------------------------------------------------------------------------------------------------
function x303006_OnPlayerDie(sceneId, selfId, killerId)	

	--如果是宠物杀死,需要取得主人的信息
	local ObjType = GetObjType(sceneId, killerId)
	if ObjType == 3 then
		ObjType = 1
		killerId = GetOwnerID(sceneId, killerId)
	end
	
	--检查是否是PVP2v2竞技场
    local nBattleScene = x303006_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303006_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
    
    --设置玩家死亡倒计时
	x303006_SetPVP6v6PlayerReliveDownCount( sceneId ,selfId)
	
	local nPlayerCamp = x303006_GetPlayerCampFlag( sceneId,selfId )
	
	--是哪个队的玩家死亡
	if nPlayerCamp == 0 then
		x303006_TeamInfoB_Score[sceneId] = x303006_TeamInfoB_Score[sceneId] + 1
		if x303006_TeamInfoB_Score[sceneId] > x303006_g_MaxScore then
			x303006_TeamInfoB_Score[sceneId] = x303006_g_MaxScore 
		end
		x303006_OnPVP6v6BattleScoreChanged(sceneId)
		x303006_AddBattlePower(sceneId,killerId,1)
	elseif nPlayerCamp == 1 then
		x303006_TeamInfoA_Score[sceneId] = x303006_TeamInfoA_Score[sceneId] + 1
		if x303006_TeamInfoA_Score[sceneId] > x303006_g_MaxScore then
			x303006_TeamInfoA_Score[sceneId] = x303006_g_MaxScore 
		end
		x303006_OnPVP6v6BattleScoreChanged(sceneId)
		x303006_AddBattlePower(sceneId,killerId,1)
	end
	
	if x303006_CheckBattleFinished( sceneId ) == 1 then
		x303006_OnBattleSceneClose( sceneId,4 )
        WriteLog(1,format("P6BL:x303006_OnPlayerDie sceneId=%d  002 ",sceneId ))
	end
	
	 --判断杀死怪物的是不是玩家
    local nLevel = GetLevel(sceneId,selfId)
	if IsPlayerStateNormal(sceneId,killerId) == 1 then
		
		--给奖励
		local nBonus = nLevel + 130
		x303006_AddBattleMoney(sceneId,killerId,nBonus)
		AddPVP2V2Mark(sceneId,killerId,1)
		local selfName = GetName(sceneId,selfId)
		local killerName = GetName(sceneId,killerId)
		LuaScenceM2Player( sceneId,killerId,format("#G杀死敌方玩家,获得战场货币#R%d#G点和战场积分#R1#G点的奖励",nBonus),killerName,2,1)
		
		local msg = format("英勇的将领%s成功地击杀了%s！",killerName,selfName)
		LuaThisScenceM2Wrold(sceneId,msg,5,1)
		
	else
		
		if nPlayerCamp == 0 or nPlayerCamp == 1 then
			local selfName = GetName(sceneId,selfId)
			local msg = format(x303006_g_PlayerDieByNPC[nPlayerCamp+1],selfName,killerName)
			LuaThisScenceM2Wrold(sceneId,msg,5,1)
		end
		
	end
	
	--对方附近玩家获得一定比例的奖励
	local nSelfCamp   = GetCurCamp(sceneId,selfId)
	local nBonusCamp = -1
	if nSelfCamp == 5 then nBonusCamp = 6 end
	if nSelfCamp == 6 then nBonusCamp = 5 end
	
	local x,z = GetWorldPos(sceneId,selfId)
	local humancount = GetNearPlayerCount(sceneId,selfId,x,z,10);
	if humancount <= 0 then
		return
	end
	for	i = 0, humancount - 1 do
		local humanId = GetNearPlayerMember(sceneId,selfId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			local nCamp = GetCurCamp( sceneId,humanId )
			if nCamp == nBonusCamp then
				local nBonus = (nLevel + 130)/6
				x303006_AddBattleMoney(sceneId,humanId,nBonus)				
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--玩家复活
---------------------------------------------------------------------------------------------------
function x303006_OnPlayerRelive(sceneId, selfId, ReliveType)
	
	--检查是否是PVP2v2竞技场
    local nBattleScene = x303006_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303006_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
	
	local leaveFlag = x303006_SceneInfo[sceneId].ISCLOSING;
	if leaveFlag > 0 then
		return
	end
	
	local nCount = x303006_GetPVP6v6PlayerReliveDownCount(sceneId,selfId)
	if nCount > 0 then
		
		--提示多少秒之后可以复活
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, format("%s秒之后自动复活",nCount));
		EndQuestEvent();
		DispatchQuestTips(sceneId, selfId);
	else
		
		--复活玩家,并且让玩家回到起始位置
		x303006_DoPlayerRelive( sceneId, selfId, 100 )
		
		--设置玩家位置
		local x,z = x303006_GetPlayerPos( sceneId,selfId)
		SetPos(sceneId,selfId,x,z)
	end
end

---------------------------------------------------------------------------------------------------
--场景关闭
---------------------------------------------------------------------------------------------------
function x303006_OnSceneClose( sceneId )
	--向GlServer通知，本场景已经关闭
	PVP6v6SendMakeBattleSceneClose(sceneId)
end

---------------------------------------------------------------------------------------------------
--复活
---------------------------------------------------------------------------------------------------
function x303006_DoPlayerRelive( sceneId, selfId, value )
	
	if GetHp(sceneId,selfId) <= 0 then
	
		ClearRageRecoverTick(sceneId, selfId)
		RestoreHp(sceneId, selfId,value)
		RestoreRage(sceneId, selfId,value)
		ClearMutexState(sceneId, selfId, 6)
		SendReliveResult(sceneId, selfId,1)	
	end
	
	LastMount(sceneId, selfId )
	RestoreHp(sceneId, selfId,0)
end

---------------------------------------------------------------------------------------------------
--踢人
---------------------------------------------------------------------------------------------------
function x303006_KickPlayer(sceneId,selfId)

	--清除死亡状态
    x303006_DoPlayerRelive( sceneId, selfId, 100 )
    x303006_RestorePlayerCamp(sceneId,selfId)
    SetPlayerRuntimeData(sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,0)
    SetPlayerRuntimeData(sceneId,selfId,RD_PVP6V6_RELIVE_DOWNCOUNT ,0) 
    
    SetPVP6v6BattleDisable( sceneId,selfId,1,0)
    
    x303006_ResetBattleMoney( sceneId,selfId)


    --如果存在BakScene信息，则以BakScene信息为准
    local nBakSceneId,x,z = GetPlayerBakSceneInfo(sceneId,selfId )
    if nBakSceneId >= 0 then
        NewWorld(sceneId,selfId,nBakSceneId,x,z,x303006_g_scriptId)
        return
    end

    --如果没有BakScene信息，则传送到王城新手村
    local nCountry = GetCurCountry(sceneId,selfId)
    if nCountry == 0 then
        NewWorld(sceneId,selfId,50,123,57,x303006_g_scriptId)
    elseif nCountry == 1 then
        NewWorld(sceneId,selfId,150,123,57,x303006_g_scriptId)
    elseif nCountry == 2 then
        NewWorld(sceneId,selfId,250,123,57,x303006_g_scriptId)
    elseif nCountry == 3 then
        NewWorld(sceneId,selfId,350,123,57,x303006_g_scriptId)
    end
end


---------------------------------------------------------------------------------------------------
--恢复阵营
---------------------------------------------------------------------------------------------------
function x303006_RestorePlayerCamp(sceneId,selfId)

	local nCountryId = GetCurCountry( sceneId,selfId )
    SetCurCamp(sceneId,selfId,nCountryId )
    
end

---------------------------------------------------------------------------------------------------
--时间同步，先暂时不用管
---------------------------------------------------------------------------------------------------
function x303006_SyncBattleTimeToAllPlayer(sceneId,nTime)
	
	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then

            TimerCommand( sceneId, objId, 1, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303006_g_scriptId,-1,-1)

            if nTime > 0 then
                TimerCommand( sceneId, objId, 2, GUILDBATTLE_TIMERID, GUILDBATTLE_TIMERTYPE, x303006_g_scriptId, nTime, nTime );
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--从GLServer过来的同步国王争夺战时间的东东
----------------------------------------------------------------------------------------------
function x303006_OnSyncBattleTime( sceneId,nTime )
    
    --检查是否是PVP2v2竞技场
    local nBattleScene = x303006_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303006_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
    
    x303006_SceneInfo[sceneId].TICKCOUNT = NumberCastIntToUInt( nTime )
    local DownTickCount = x303006_g_LimitTotalHoldTime - NumberCastIntToUInt( nTime )
    x303006_SyncBattleTimeToAllPlayer( sceneId, DownTickCount )
end

---------------------------------------------------------------------------------------------------
--检查战场结束
---------------------------------------------------------------------------------------------------
function x303006_CheckBattleFinished( sceneId )

	---------------------------------------------------------------------------------------------------	
	--1、只有一方玩家或是双方都不在了
	---------------------------------------------------------------------------------------------------
	if  x303006_CheckTeamA_AllLeave( sceneId ) == 1 or x303006_CheckTeamB_AllLeave( sceneId ) == 1 then
		return 1
	end
	
	---------------------------------------------------------------------------------------------------	
	--2、双方有一方到达满分,则认定已经结束
	---------------------------------------------------------------------------------------------------
	if x303006_TeamInfoA_Score[sceneId] == x303006_g_MaxScore or x303006_TeamInfoB_Score[sceneId] == x303006_g_MaxScore then
		return 1
	end
	
	---------------------------------------------------------------------------------------------------
	--3.当敌方某个标志性建筑被推毁
	---------------------------------------------------------------------------------------------------
	if x303006_BossDieFlag[sceneId] > 0 then
		return 1
	end
	
	return 0
end

---------------------------------------------------------------------------------------------------
--给战场奖励
---------------------------------------------------------------------------------------------------
function x303006_GiveBattleBonus( sceneId,nResult )
	
	if nResult == -1 then
		
		LuaThisScenceM2Wrold( sceneId,"平局",5,1)
		
		x303006_OnGiveTeamA(sceneId,-1)
		x303006_OnGiveTeamB(sceneId,-1)
		
	elseif nResult == 0 then
		
		LuaThisScenceM2Wrold( sceneId,"铁木真军获胜",5,1)
		
		x303006_OnGiveTeamA(sceneId,0)
		x303006_OnGiveTeamB(sceneId,0)
		
	elseif nResult == 1 then
		
		LuaThisScenceM2Wrold( sceneId,"札木合军获胜",5,1)
		
		x303006_OnGiveTeamA(sceneId,1)
		x303006_OnGiveTeamB(sceneId,1)
	end
end

---------------------------------------------------------------------------------------------------
--队伍A的获奖
---------------------------------------------------------------------------------------------------
function x303006_OnGiveTeamA( sceneId, nBonusType )
		
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			for j,itm in x303006_TeamInfoA[sceneId] do
				if GUID == itm.GUID then
					local name = GetName(sceneId,humanId)
					if name == nil then
						name = "Error "
					end
					
					if nBonusType == -1 then
						
						AddPVP2V2Mark(sceneId,humanId,x303006_g_Other_Bonus_Mark)
						LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303006_g_Other_Bonus_Mark),name,2,1)

					elseif nBonusType == 0 then					
						
						AddPVP2V2Mark(sceneId,humanId,x303006_g_Winner_Bonus_Mark)	
						LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303006_g_Winner_Bonus_Mark),name,2,1)
						
					elseif nBonusType == 1 then
						
						AddPVP2V2Mark(sceneId,humanId,x303006_g_Loser_Bonus_Mark)
						LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303006_g_Loser_Bonus_Mark),name,2,1)							
					end
					
					break
				end
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--队伍B的获奖
---------------------------------------------------------------------------------------------------
function x303006_OnGiveTeamB( sceneId, nBonusType )

	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			for j,itm in x303006_TeamInfoB[sceneId] do
				if GUID == itm.GUID then
					
					local name = GetName(sceneId,humanId)
					if name == nil then
						name = "Error "
					end
					
					if nBonusType == -1 then
						
						AddPVP2V2Mark(sceneId,humanId,x303006_g_Other_Bonus_Mark)
						LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303006_g_Other_Bonus_Mark),name,2,1)
						
					elseif nBonusType == 0 then
						
						AddPVP2V2Mark(sceneId,humanId,x303006_g_Loser_Bonus_Mark)
						LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303006_g_Loser_Bonus_Mark),name,2,1)
						
					elseif nBonusType == 1 then
						
						AddPVP2V2Mark(sceneId,humanId,x303006_g_Winner_Bonus_Mark)	
						LuaScenceM2Player( sceneId,humanId,format("#G获得#R%d#G点战场积分",x303006_g_Winner_Bonus_Mark),name,2,1)
					end
					
					break
				end
			end
		end
	end
	
end

---------------------------------------------------------------------------------------------------
--生成战场结果
---------------------------------------------------------------------------------------------------
function x303006_GenBattleResult( sceneId )

	--如果已经开始关闭，则不允许给奖励
	if x303006_SceneInfo[sceneId].ISCLOSING == 1 then
		return
	end
	
	local nResult = -1 

	---------------------------------------------------------------------------------------------------	
	--1.只有一方玩家
	---------------------------------------------------------------------------------------------------
	
	--当A组玩家在，B组玩家不在，认为A组赢	
	if  x303006_CheckTeamA_AllLeave( sceneId ) == 0 and x303006_CheckTeamB_AllLeave( sceneId ) == 1 then
		nResult = 0
		x303006_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	--当A组玩家不在，B组玩家在，认为B组赢
	if  x303006_CheckTeamA_AllLeave( sceneId ) == 1 and x303006_CheckTeamB_AllLeave( sceneId ) == 0 then
		nResult = 1
		x303006_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--2.当双方有一方超过满分
	---------------------------------------------------------------------------------------------------	
	if x303006_TeamInfoA_Score[sceneId] == x303006_g_MaxScore and x303006_TeamInfoB_Score[sceneId] < x303006_g_MaxScore then
		nResult = 0
		x303006_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	if x303006_TeamInfoA_Score[sceneId] < x303006_g_MaxScore and x303006_TeamInfoB_Score[sceneId] == x303006_g_MaxScore then
		nResult = 1
		x303006_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--3.当敌方某个标志性建筑被推毁
	---------------------------------------------------------------------------------------------------
	if x303006_BossDieFlag[sceneId] == 1 then
		--A方标记性建筑被推 ,B赢了
		nResult = 1
		x303006_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	if x303006_BossDieFlag[sceneId] == 2 then
		--B方标记性建筑被推 ,A赢了
		nResult = 0
		x303006_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--4.其他情况(没有一方推毁对方标志性建筑)
	---------------------------------------------------------------------------------------------------
	if x303006_TeamInfoA_Score[sceneId] == x303006_g_MaxScore and x303006_TeamInfoB_Score[sceneId] == x303006_g_MaxScore then
		nResult = -1
		x303006_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	if x303006_TeamInfoA_Score[sceneId] > x303006_TeamInfoB_Score[sceneId]  then
		nResult = 0
		x303006_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	if x303006_TeamInfoA_Score[sceneId] < x303006_TeamInfoB_Score[sceneId] then
		nResult = 1
		x303006_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	if x303006_TeamInfoA_Score[sceneId] == x303006_TeamInfoB_Score[sceneId] then
		nResult = -1
		x303006_GiveBattleBonus( sceneId,nResult )
		return
	end
	
	---------------------------------------------------------------------------------------------------
	--5、不满足1,2,3,4
	---------------------------------------------------------------------------------------------------
	if  x303006_CheckTeamA_AllLeave( sceneId ) == 0 and x303006_CheckTeamB_AllLeave( sceneId ) == 0 then
		nResult = -1
		x303006_GiveBattleBonus( sceneId,nResult )
		return
	end
		
end


---------------------------------------------------------------------------------------------------
--检查队伍A是否全部离开
---------------------------------------------------------------------------------------------------
function x303006_CheckTeamA_AllLeave( sceneId )

	local nCount = 0

	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			
			for j,itm in x303006_TeamInfoA[sceneId] do
				if GUID == itm.GUID then
					nCount = nCount + 1
				end				
			end
		end
	end
	
	if nCount == 0 then
		return 1
	end
	
	return 0

end

---------------------------------------------------------------------------------------------------
--检查队伍A是否全部离开
---------------------------------------------------------------------------------------------------
function x303006_CheckTeamB_AllLeave( sceneId )
	
	local nCount = 0
	
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local GUID = GetPlayerGUID( sceneId,humanId )
			for j,itm in x303006_TeamInfoB[sceneId] do
				if GUID == itm.GUID then
					nCount = nCount + 1
				end				
			end
		end
	end
	
	if nCount == 0 then
		return 1
	end
	
	return 0
	
end


---------------------------------------------------------------------------------------------------
--检查玩家有效性
---------------------------------------------------------------------------------------------------
function x303006_CheckPlayerValid( sceneId,selfId )
	
	local GUID = GetPlayerGUID(sceneId,selfId)
	
	--A组
	for i,itm in x303006_TeamInfoA[sceneId] do
		if GUID == itm.GUID then
			return 1
		end
	end
	
	--B组
	for i,itm in x303006_TeamInfoB[sceneId] do
		if GUID == itm.GUID then
			return 1
		end
	end
	
	return 0

end

---------------------------------------------------------------------------------------------------
--取得玩家进入战场标记
---------------------------------------------------------------------------------------------------
function x303006_GetPlayerEnterSceneFlag( sceneId,selfId)

	local GUID = GetPlayerGUID(sceneId,selfId)

	--A组
	for i,itm in x303006_TeamInfoA[sceneId] do
		if GUID == itm.GUID then
			return itm.ENTER
		end
	end
	
	--B组
	for i,itm in x303006_TeamInfoB[sceneId] do
		if GUID == itm.GUID then
			return itm.ENTER
		end
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--设置玩家进入战场标记
---------------------------------------------------------------------------------------------------
function x303006_SetPlayerEnterSceneFlag( sceneId,selfId)

	--设置玩家进入标记
	local GUID = GetPlayerGUID(sceneId,selfId)

	--A组
	for i,itm in x303006_TeamInfoA[sceneId] do
		if GUID == itm.GUID then
			itm.ENTER = 1
			return
		end
	end
	
	--B组
	for i,itm in x303006_TeamInfoB[sceneId] do
		if GUID == itm.GUID then
			itm.ENTER = 1
			return
		end
	end
end

---------------------------------------------------------------------------------------------------
--战场准备好了
---------------------------------------------------------------------------------------------------
function x303006_OnBattleSceneReady(sceneId,nTotalTime)
	
	--场景相关信息							  
	x303006_SceneInfo[sceneId]				={
										TICKCOUNT = 0,
										ISCLOSING = 0,
										LEAVECOUNTDOWN = 0,
										RESULT = 0,
										LIMITHOLDTIME = nTotalTime,
										FIRSTCREATE = 0,
										FIRSTCREATE30 = 0
								  	  }
								  	  
	x303006_BossDieFlag[sceneId]				= 0
	WriteLog(1,format("P6BL:x303006_OnBattleSceneReady SceneId=%d ",sceneId  ))
		
end

---------------------------------------------------------------------------------------------------
--战场关闭
---------------------------------------------------------------------------------------------------
function x303006_OnBattleSceneClose(sceneId,flag )
	
	x303006_GenBattleResult( sceneId )
	
	if x303006_SceneInfo[sceneId].ISCLOSING == 1	then
		return
	end
	
	x303006_TeamInfoA[sceneId]				= {	
												{GUID=-1,ENTER=0},
												{GUID=-1,ENTER=0},
												{GUID=-1,ENTER=0},
												{GUID=-1,ENTER=0},
												{GUID=-1,ENTER=0},
												{GUID=-1,ENTER=0},
											  }

	x303006_TeamInfoA_MemberCount[sceneId]	= 0
	x303006_TeamInfoA_Score[sceneId]		= 0
								  
	x303006_TeamInfoB[sceneId]				= {	
												{GUID=-1,ENTER=0},
												{GUID=-1,ENTER=0},
												{GUID=-1,ENTER=0},
												{GUID=-1,ENTER=0},
												{GUID=-1,ENTER=0},
												{GUID=-1,ENTER=0},
											  }
									  
	x303006_TeamInfoB_MemberCount[sceneId]	= 0
	x303006_TeamInfoB_Score[sceneId]		= 0
									  								  									  
	x303006_LevelFlag[sceneId]				= 0
	x303006_BattleFlag[sceneId]				= 0
	x303006_MatchLevel[sceneId]				= 0
	
	x303006_Monster_MF4[sceneId]			= {}
	x303006_Monster_MF5[sceneId]			= -1

							  
	x303006_SceneInfo[sceneId]				= {
												TICKCOUNT = 0,
												ISCLOSING = 0,
												LEAVECOUNTDOWN = 0,
												RESULT = 0,
												LIMITHOLDTIME = x303006_g_LimitTotalHoldTime,
												FIRSTCREATE = 0,
												FIRSTCREATE30 = 0,
											  }
	
	--场景相关信息							  
	x303006_SceneInfo[sceneId].ISCLOSING 	= 1	
	x303006_SceneInfo[sceneId].TICKCOUNT 	= 0
	
	--回收生长点
	RecycleGrowPointByType(sceneId,x303006_g_GrowPointType,-1)
	
	--删除所有的怪物
	x303006_OnMonsterDestroy(sceneId,1)
	WriteLog(1,format("P6BL:x303006_OnBattleSceneClose SceneId=%d flag=%d",sceneId,flag  ))
	
end

---------------------------------------------------------------------------------------------------
--战场关闭
---------------------------------------------------------------------------------------------------
function x303006_OnBattleMatchOOD(sceneId,selfId)
	
	local name = GetName(sceneId,selfId)
	LuaScenceM2Player( sceneId,selfId,x303006_g_BattleMatchOODMsg,name,2,1)	
	LuaScenceM2Player( sceneId,selfId,x303006_g_BattleMatchOODMsg,name,3,1)	
	
end

---------------------------------------------------------------------------------------------------
--设置玩家需要踢出去
---------------------------------------------------------------------------------------------------
function x303006_SetPlayerNeedKick( sceneId,selfId)
	
	local KickDown = GetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ) 
    if KickDown <= 0 or KickDown > x303006_g_Kick_Down then                
        SetPlayerRuntimeData( sceneId,selfId,RD_BATTLE_SCENE_KICK_DOWN ,x303006_g_Kick_Down) 
    end
	
end

----------------------------------------------------------------------------------------------
--设置所有玩家需要踢掉
----------------------------------------------------------------------------------------------
function x303006_SetAllPlayerNeedKick( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown <= 0 or KickDown > x303006_g_Kick_Down then                
                SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,x303006_g_Kick_Down) 
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--更新玩家踢掉状态
----------------------------------------------------------------------------------------------
function x303006_UpdatePlayerKickState( sceneId )
    
    local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local KickDown = GetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ) 
            if KickDown > 0 then                
                KickDown = KickDown - 1 
                if KickDown == 0 then
                    --倒计时为零，踢掉
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,-1) 
                    x303006_KickPlayer( sceneId,objId )                    
                else
                    --否则，继续倒计时
                    SetPlayerRuntimeData( sceneId,objId,RD_BATTLE_SCENE_KICK_DOWN ,KickDown) 
                end
            end
        end
    end
end

----------------------------------------------------------------------------------------------
--设置玩家死亡状态更新
----------------------------------------------------------------------------------------------
function x303006_SetPVP6v6PlayerReliveDownCount( sceneId ,selfId)
	
	--如果战场已经关闭,则不设置
	if x303006_SceneInfo[sceneId].ISCLOSING == 1	then
		return
	end
	
	--设置死亡复活倒计时信息
	if x303006_SceneInfo[sceneId].TICKCOUNT >= 30*60 then
		SetPlayerRuntimeData( sceneId,selfId,RD_PVP6V6_RELIVE_DOWNCOUNT,120 )
	elseif x303006_SceneInfo[sceneId].TICKCOUNT >= 20*60 then
		SetPlayerRuntimeData( sceneId,selfId,RD_PVP6V6_RELIVE_DOWNCOUNT,60 )
	elseif x303006_SceneInfo[sceneId].TICKCOUNT >= 10*60 then
		SetPlayerRuntimeData( sceneId,selfId,RD_PVP6V6_RELIVE_DOWNCOUNT,30 )
	elseif x303006_SceneInfo[sceneId].TICKCOUNT > 0 then
		SetPlayerRuntimeData( sceneId,selfId,RD_PVP6V6_RELIVE_DOWNCOUNT,10 )
	end
end

----------------------------------------------------------------------------------------------
--检查玩家是否可以复活
----------------------------------------------------------------------------------------------
function x303006_GetPVP6v6PlayerReliveDownCount( sceneId,selfId)
	
	--如果战场已经关闭,则不设置
	if x303006_SceneInfo[sceneId].ISCLOSING == 1	then
		return 0
	end
	
	return GetPlayerRuntimeData( sceneId,selfId,RD_PVP6V6_RELIVE_DOWNCOUNT );
end


----------------------------------------------------------------------------------------------
--更新玩家死亡倒计时
----------------------------------------------------------------------------------------------
function x303006_UpdatePVP6v6PlayerReliveDownCount( sceneId,selfId)
	
	--如果战场已经关闭,则不设置
	if x303006_SceneInfo[sceneId].ISCLOSING == 1	then
		return
	end
	
	--更新玩家数据
	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
            local nReliveDownCount = GetPlayerRuntimeData( sceneId,objId,RD_PVP6V6_RELIVE_DOWNCOUNT ) 
            if nReliveDownCount > 0 then                
                nReliveDownCount = nReliveDownCount - 1 
                SetPlayerRuntimeData( sceneId,objId,RD_PVP6V6_RELIVE_DOWNCOUNT ,nReliveDownCount) 
                
                --自动复活玩家
                x303006_PlayerAutoRelive(sceneId,objId,0)
            end
        end
    end
	
	return 0
	
end

----------------------------------------------------------------------------------------------
--分数改变
----------------------------------------------------------------------------------------------
function x303006_OnPVP6v6BattleScoreChanged( sceneId )
	
	--如果战场已经关闭,则不设置
	if x303006_SceneInfo[sceneId].ISCLOSING == 1	then
		return
	end
	
	--更新玩家数据
	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 then
        	SendPVP6v6BattleScore(sceneId,objId,x303006_TeamInfoA_Score[sceneId],x303006_TeamInfoB_Score[sceneId])
        end
    end
    
end


---------------------------------------------------------------------------------------------------
--玩家复活
---------------------------------------------------------------------------------------------------
function x303006_PlayerAutoRelive(sceneId, selfId, ReliveType)
	
	--检查是否是PVP2v2竞技场
    local nBattleScene = x303006_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return
    end
    
    --检查场景是否有效
    local nBattleSceneValid = x303006_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return	
    end
	
	local leaveFlag = x303006_SceneInfo[sceneId].ISCLOSING;
	if leaveFlag > 0 then
		return
	end
	
	local nCount = x303006_GetPVP6v6PlayerReliveDownCount(sceneId,selfId)
	if nCount <= 0 then
		
		--复活玩家,并且让玩家回到起始位置
		x303006_DoPlayerRelive( sceneId, selfId, 100 )
		
		--设置玩家位置
		local x,z = x303006_GetPlayerPos( sceneId,selfId)
		SetPos(sceneId,selfId,x,z)
	end
end

---------------------------------------------------------------------------------------------------
--创建怪物
---------------------------------------------------------------------------------------------------
function x303006_OnCreateMonster(sceneId)

	--怪物数量限定,以保证服务器稳定
	local nCurMonsterCount = GetMonsterCount(sceneId)	
	if nCurMonsterCount >= x303006_g_MaxMonsterLimit then
		return
	end

	--如果不超过指定数量,则认为可以创建新的怪物
	local nIndexFrom = GetFubenDataPosByScriptID( x303006_g_scriptId )
	local nDataCount = GetFubenDataCountByScriptID( x303006_g_scriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x303006_g_scriptId,nIndexFrom,i)
		if idScript == x303006_g_scriptId and monsterFlag == 1 and x303006_IsMonsterCanCreate(sceneId,flag1) == 1 and x303006_CheckLevelRange(sceneId,levelmin,levelmax) == 1  then
			
            for j=0,count -1 do
            
            	local lx = x + random(-r,r)
            	local lz = z + random(-r,r)
            	
				if title~="" then
					local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir, "", title)
					SetPatrolId(sceneId,objId,patrolid)		--设置寻路
					SetPatrolNoBreak(sceneId,objId,1) 		--禁用交互
				else
					local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir)
					SetPatrolId(sceneId,objId,patrolid)		--设置寻路
					SetPatrolNoBreak(sceneId,objId,1) 		--禁用交互
				end
			end
        end
	end
end



---------------------------------------------------------------------------------------------------
--创建怪物,野外怪,MonsterFlag=4
---------------------------------------------------------------------------------------------------
function x303006_OnCreateMonster_MF4(sceneId,firstcreate)

	WriteLog(1,format("x303006_OnCreateMonster_MF4 %d,%d",sceneId,firstcreate))

	--如果不超过指定数量,则认为可以创建新的怪物
	local nIndexFrom = GetFubenDataPosByScriptID( x303006_g_scriptId )
	local nDataCount = GetFubenDataCountByScriptID( x303006_g_scriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x303006_g_scriptId,nIndexFrom,i)
		if idScript == x303006_g_scriptId and monsterFlag == 4 and x303006_CheckLevelRange(sceneId, levelmin,levelmax) == 1 then
			
            for j=0,count -1 do
            
            	local lx = x + random(-r,r)
            	local lz = z + random(-r,r)
            	
            	if firstcreate == 1 then
            	
            		--如果是第一次创建
					if title~="" then
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir, "", title)
						x303006_Monster_MF4[sceneId][flag] = objId
					else
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir)
						x303006_Monster_MF4[sceneId][flag] = objId
					end
				
				elseif x303006_Monster_MF4[sceneId][flag] == -1 then
					
					--如果是刷新
					if title~="" then
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir, "", title)
						x303006_Monster_MF4[sceneId][flag] = objId
						
					else
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir)
						x303006_Monster_MF4[sceneId][flag] = objId
					end	
				end
			end
        end
	end
end

---------------------------------------------------------------------------------------------------
--创建怪物,野外BOSS一个,MonsterFlag=5
---------------------------------------------------------------------------------------------------
function x303006_OnCreateMonster_MF5(sceneId,firstcreate)

	--如果不超过指定数量,则认为可以创建新的怪物
	local nIndexFrom = GetFubenDataPosByScriptID( x303006_g_scriptId )
	local nDataCount = GetFubenDataCountByScriptID( x303006_g_scriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x303006_g_scriptId,nIndexFrom,i)
		if idScript == x303006_g_scriptId and monsterFlag == 5 and x303006_CheckLevelRange(sceneId, levelmin,levelmax) == 1 then
			
            for j=0,count -1 do
            
            	if firstcreate == 1 then
            	
            		--如果是第一次创建
	            	local lx = x + random(-r,r)
	            	local lz = z + random(-r,r)
	            	
					if title~="" then
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir, "", title)
						x303006_Monster_MF5[sceneId] = objId
					else
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir)
						x303006_Monster_MF5[sceneId] = objId
					end
				elseif x303006_Monster_MF5[sceneId] == -1 then
					
					--如果是刷新
					local lx = x + random(-r,r)
	            	local lz = z + random(-r,r)
	            	
					if title~="" then
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir, "", title)
						x303006_Monster_MF5[sceneId] = objId
					else
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir)
						x303006_Monster_MF5[sceneId] = objId
					end
					
				end
			end
        end
	end
end

---------------------------------------------------------------------------------------------------
--创建怪物,击杀野外boss触发的怪物6个,MonsterFlag=6,随机创建一个
---------------------------------------------------------------------------------------------------
function x303006_OnCreateMonster_MF6(sceneId,campFlag)

	--做阵营检查
	if campFlag ~=5 and campFlag ~= 6 then
		return
	end
	
	local nRand = random(1,3)
	local nCur  = 0

	--如果不超过指定数量,则认为可以创建新的怪物
	local nIndexFrom = GetFubenDataPosByScriptID( x303006_g_scriptId )
	local nDataCount = GetFubenDataCountByScriptID( x303006_g_scriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x303006_g_scriptId,nIndexFrom,i)
		if idScript == x303006_g_scriptId and monsterFlag == 6 and flag == campFlag and x303006_CheckLevelRange(sceneId, levelmin,levelmax) == 1 then
		
			nCur = nCur + 1 
			if nCur == nRand then
	            
	            --如果正确随机进来,那么创建怪物,并且退出
	            for j=0,count -1 do
	            
	            	local lx = x + random(-r,r)
	            	local lz = z + random(-r,r)
	            	
					if title~="" then
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir, "", title)
						SetPatrolId(sceneId,objId,patrolid)
					else
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir)
						SetPatrolId(sceneId,objId,patrolid)
					end
				end
				
				--提示
				x303006_ShowTips_BossKilledBonus(sceneId,nRand)
				
				return
			end
        end
	end
end


---------------------------------------------------------------------------------------------------
--创建怪物,采集触发的怪物6个,MonsterFlag=7
---------------------------------------------------------------------------------------------------
function x303006_OnCreateMonster_MF7(sceneId,selfId )
	
	--做阵营检查
	local campFlag = GetCurCamp(sceneId,selfId)
	if campFlag ~=5 and campFlag ~= 6 then
		return 0
	end

	--其他情况,阵营有效
	local nRand = random(1,3)
	local nCur  = 0

	--如果不超过指定数量,则认为可以创建新的怪物
	local nIndexFrom = GetFubenDataPosByScriptID( x303006_g_scriptId )
	local nDataCount = GetFubenDataCountByScriptID( x303006_g_scriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x303006_g_scriptId,nIndexFrom,i)
		if idScript == x303006_g_scriptId and monsterFlag == 7 and flag == campFlag and x303006_CheckLevelRange(sceneId, levelmin,levelmax) == 1 then
		
			nCur = nCur + 1 
			if nCur == nRand then
	            
	            --如果正确随机进来,那么创建怪物,并且退出
	            for j=0,count -1 do
	            
	            	local lx = x + random(-r,r)
	            	local lz = z + random(-r,r)
	            	
					if title~="" then
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir, "", title)
						SetPatrolId(sceneId,objId,patrolid)
					else
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir)
						SetPatrolId(sceneId,objId,patrolid)
					end
				end
				
				--给出相关提示
				
				--上下路对调
				if nRand == 1 then 
					nRand = 3
				elseif nRand == 3 then 
					nRand = 1 
				end
				
				x303006_ShowTips_GrowPoint(sceneId,selfId,3,x303006_g_RoadType[nRand])
				return 1
			end
        end
	end
	
	return 1
end


---------------------------------------------------------------------------------------------------
--创建怪物,士气触发的怪物6个,MonsterFlag=8
---------------------------------------------------------------------------------------------------
function x303006_OnCreateMonster_MF8(sceneId,campFlag)

	--做阵营检查
	if campFlag ~=5 and campFlag ~= 6 then
		return
	end

	local nRand = random(1,3)
	local nCur  = 0
	
	--如果不超过指定数量,则认为可以创建新的怪物
	local nIndexFrom = GetFubenDataPosByScriptID( x303006_g_scriptId )
	local nDataCount = GetFubenDataCountByScriptID( x303006_g_scriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x303006_g_scriptId,nIndexFrom,i)
		if idScript == x303006_g_scriptId and monsterFlag == 8 and flag == campFlag and x303006_CheckLevelRange(sceneId, levelmin,levelmax) == 1 then
			nCur = nCur + 1 
			if nCur == nRand then
	            
	            --如果正确随机进来,那么创建怪物,并且退出
	            for j=0,count -1 do
	            	local lx = x + random(-r,r)
	            	local lz = z + random(-r,r)
	            	
					if title~="" then
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir, "", title)
						SetPatrolId(sceneId,objId,patrolid)
					else
						local objId = CreateMonster(sceneId, type, lx, lz, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir)
						SetPatrolId(sceneId,objId,patrolid)
					end
				end
				
				local nFlag = -1
				if campFlag == 5 then 
					nFlag = 1
				else
					nFlag = 2
				end
				
				--上下路对调
				if nRand == 1 then 
					nRand = 3
				elseif nRand == 3 then 
					nRand = 1 
				end
				
				--显示相关提示
				x303006_ShowTips_PowerTips(sceneId,nFlag,3,x303006_g_RoadType[nRand])
				
				return
			end
        end
	end
end

---------------------------------------------------------------------------------------------------
--检查是否可以创建怪物
---------------------------------------------------------------------------------------------------
function x303006_IsMonsterCanCreate(sceneId,flag)
	
	--确定一下是铁木真军还是札木合军
	local nIndex = 1
	if flag >= 100 then
		nIndex = 2
	end
	
	if x303006_MonsterLftCreateFlag[sceneId][nIndex] == flag or x303006_MonsterMidCreateFlag[sceneId][nIndex] == flag or x303006_MonsterRhtCreateFlag[sceneId][nIndex] == flag then
		return 1
	end
	
	return 0
end

---------------------------------------------------------------------------------------------------
--创建相关商店NPC
---------------------------------------------------------------------------------------------------
function x303006_OnCreateShopNPC(sceneId)
	
	local nIndexFrom = GetFubenDataPosByScriptID( x303006_g_scriptId )
	local nDataCount = GetFubenDataCountByScriptID( x303006_g_scriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x303006_g_scriptId,nIndexFrom,i)
		if idScript == x303006_g_scriptId and monsterFlag == 2 then
            for j=0,count -1 do
            	
				if title~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, guid, camp, -1,facedir, "", title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, guid, camp, -1,facedir)
				end
			end
        end
	end
end

---------------------------------------------------------------------------------------------------
--创建传送NPC
---------------------------------------------------------------------------------------------------
function x303006_OnCreateTripNPC(sceneId)
	
	local nIndexFrom = GetFubenDataPosByScriptID( x303006_g_scriptId )
	local nDataCount = GetFubenDataCountByScriptID( x303006_g_scriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x303006_g_scriptId,nIndexFrom,i)
		if idScript == x303006_g_scriptId and monsterFlag == 3 then
            for j=0,count -1 do
            	
				if title~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, guid, camp, -1,facedir, "", title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, guid, camp, -1,facedir)
				end
			end
        end
	end
end

---------------------------------------------------------------------------------------------------
--创建建筑,即BOSS,死亡是有特殊处理的
---------------------------------------------------------------------------------------------------
function x303006_OnCreateBoss(sceneId)

	--初始化BOSS数据	
	x303006_BossLftID1[sceneId] = { -1,-1 }			
	x303006_BossMidID1[sceneId] = { -1,-1 }			
	x303006_BossRhtID1[sceneId] = { -1,-1 }			
	                   
	x303006_BossLftID2[sceneId] = { -1,-1 }			
	x303006_BossMidID2[sceneId] = { -1,-1 }			
	x303006_BossRhtID2[sceneId] = { -1,-1 }			
	                   
	x303006_BossLftID3[sceneId] = { -1,-1 }			
	x303006_BossMidID3[sceneId] = { -1,-1 }			
	x303006_BossRhtID3[sceneId] = { -1,-1 }			
	                   
	x303006_BossLftID4[sceneId] = { -1,-1 }			
	x303006_BossMidID4[sceneId] = { -1,-1,-1,-1 }	
	x303006_BossRhtID4[sceneId] = { -1,-1 }			
	                   
	x303006_BossMidID5[sceneId] = { -1,-1,-1,-1 }
	
	x303006_BossMidID6[sceneId] = { -1,-1 }	
	
	--初始化血量
	x303006_BossLftID1_HP[sceneId] = { -1,-1 }
	x303006_BossMidID1_HP[sceneId] = { -1,-1 }
	x303006_BossRhtID1_HP[sceneId] = { -1,-1 }
	
	x303006_BossLftID2_HP[sceneId] = { -1,-1 }
	x303006_BossMidID2_HP[sceneId] = { -1,-1 }
	x303006_BossRhtID2_HP[sceneId] = { -1,-1 }
	
	x303006_BossLftID3_HP[sceneId] = { -1,-1 }
	x303006_BossMidID3_HP[sceneId] = { -1,-1 }
	x303006_BossRhtID3_HP[sceneId] = { -1,-1 }

	x303006_BossLftID4_HP[sceneId] = { -1,-1 }
	x303006_BossMidID4_HP[sceneId] = { -1,-1,-1,-1 }
	x303006_BossRhtID4_HP[sceneId] = { -1,-1 }

	x303006_BossMidID5_HP[sceneId] = { -1,-1,-1,-1 }

	x303006_BossMidID6_HP[sceneId] = { -1,-1 }
	
	x303006_BossMid5DieFlag[sceneId]= { 0,0,}
	
	--怪物创建信息
	x303006_MonsterLftCreateFlag[sceneId]		= { 0, 100 }	--左路Monster创建信息
	x303006_MonsterMidCreateFlag[sceneId]		= { 10,110 }	--中路Monster创建信息
	x303006_MonsterRhtCreateFlag[sceneId]		= { 20,120 }	--右路Monster创建信息		
	
	
	--开始创建BOSS
	local nIndexFrom = GetFubenDataPosByScriptID( x303006_g_scriptId )
	local nDataCount = GetFubenDataCountByScriptID( x303006_g_scriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x303006_g_scriptId,nIndexFrom,i)
		if idScript == x303006_g_scriptId and monsterFlag == 0 and x303006_CheckLevelRange(sceneId,levelmin,levelmax) == 1 then
            for j=0,count -1 do
            	
				if title~="" then
					local objId = CreateMonster(sceneId, type, x, z, ai, aiscript, x303006_g_scriptId, guid, camp, -1,facedir, "", title)
					x303006_SetBossID(sceneId,objId,flag)
					if flag1 == 1 then
						SendSpecificImpactToUnit(sceneId,objId,objId,objId,7762,0);
					end
				else
					local objId = CreateMonster(sceneId, type, x, z, ai, aiscript, x303006_g_scriptId, guid, camp, -1,facedir)
					x303006_SetBossID(sceneId,objId,flag)
					if flag1 == 1 then
						SendSpecificImpactToUnit(sceneId,objId,objId,objId,7762,0);
					end
				end
			end
        end
	end
end

---------------------------------------------------------------------------------------------------
--设置BOSSID
---------------------------------------------------------------------------------------------------
function x303006_SetBossID(sceneId,objId,flag)

	--第一排
	if flag == 0 then
		x303006_BossLftID1[sceneId][1] = objId
		x303006_BossLftID1_HP[sceneId][1] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossLftID1[sceneId][1]=%d",sceneId,objId))
	elseif flag == 100 then
		x303006_BossLftID1[sceneId][2] = objId
		x303006_BossLftID1_HP[sceneId][2] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossLftID1[sceneId][2]=%d",sceneId,objId))
	elseif flag == 10 then
		x303006_BossMidID1[sceneId][1] = objId
		x303006_BossMidID1_HP[sceneId][1] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID1[sceneId][1]=%d",sceneId,objId))
	elseif flag == 110 then
		x303006_BossMidID1[sceneId][2] = objId
		x303006_BossMidID1_HP[sceneId][2] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID1[sceneId][2]=%d",sceneId,objId))
	elseif flag == 20 then
		x303006_BossRhtID1[sceneId][1] = objId
		x303006_BossRhtID1_HP[sceneId][1] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossRhtID1[sceneId][1]=%d",sceneId,objId))
	elseif flag == 120 then
		x303006_BossRhtID1[sceneId][2] = objId	
		x303006_BossRhtID1_HP[sceneId][2] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossRhtID1[sceneId][2]=%d",sceneId,objId))
	end
	
	--第二批
	if flag == 1 then
		x303006_BossLftID2[sceneId][1] = objId
		x303006_BossLftID2_HP[sceneId][1] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossLftID2[sceneId][1]=%d",sceneId,objId))
	elseif flag == 101 then
		x303006_BossLftID2[sceneId][2] = objId
		x303006_BossLftID2_HP[sceneId][2] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossLftID2[sceneId][2]=%d",sceneId,objId))
	elseif flag == 11 then
		x303006_BossMidID2[sceneId][1] = objId
		x303006_BossMidID2_HP[sceneId][1] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID2[sceneId][1]=%d",sceneId,objId))
	elseif flag == 111 then
		x303006_BossMidID2[sceneId][2] = objId
		x303006_BossMidID2_HP[sceneId][2] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID2[sceneId][2]=%d",sceneId,objId))
	elseif flag == 21 then
		x303006_BossRhtID2[sceneId][1] = objId
		x303006_BossRhtID2_HP[sceneId][1] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossRhtID2[sceneId][1]=%d",sceneId,objId))
	elseif flag == 121 then
		x303006_BossRhtID2[sceneId][2] = objId
		x303006_BossRhtID2_HP[sceneId][2] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossRhtID2[sceneId][2]=%d",sceneId,objId))
	end
	
	--第三批
	if flag == 2 then
		x303006_BossLftID3[sceneId][1] = objId
		x303006_BossLftID3_HP[sceneId][1] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossLftID3[sceneId][1]=%d",sceneId,objId))
	elseif flag == 102 then
		x303006_BossLftID3[sceneId][2] = objId
		x303006_BossLftID3_HP[sceneId][2] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossLftID3[sceneId][2]=%d",sceneId,objId))
	elseif flag == 12 then
		x303006_BossMidID3[sceneId][1] = objId
		x303006_BossMidID3_HP[sceneId][1] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID3[sceneId][1]=%d",sceneId,objId))
	elseif flag == 112 then
		x303006_BossMidID3[sceneId][2] = objId
		x303006_BossMidID3_HP[sceneId][2] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID3[sceneId][2]=%d",sceneId,objId))
	elseif flag == 22 then
		x303006_BossRhtID3[sceneId][1] = objId
		x303006_BossRhtID3_HP[sceneId][1] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossRhtID3[sceneId][1]=%d",sceneId,objId))
	elseif flag == 122 then
		x303006_BossRhtID3[sceneId][2] = objId
		x303006_BossRhtID3_HP[sceneId][2] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossRhtID3[sceneId][2]=%d",sceneId,objId))
	end
	
	--第四批
	if flag == 3 then
		x303006_BossLftID4[sceneId][1] = objId
		x303006_BossLftID4_HP[sceneId][1] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossLftID4[sceneId][1]=%d",sceneId,objId))
	elseif flag == 103 then
		x303006_BossLftID4[sceneId][2] = objId
		x303006_BossLftID4_HP[sceneId][2] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossLftID4[sceneId][2]=%d",sceneId,objId))
	elseif flag == 13 then
		if x303006_BossMidID4[sceneId][1] == -1 then
			x303006_BossMidID4[sceneId][1] = objId
			x303006_BossMidID4_HP[sceneId][1] = GetHp(sceneId,objId)
			WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID4[sceneId][1]=%d",sceneId,objId))
		elseif x303006_BossMidID4[sceneId][2] == -1 then
			x303006_BossMidID4[sceneId][2] = objId
			x303006_BossMidID4_HP[sceneId][2] = GetHp(sceneId,objId)
			WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID4[sceneId][2]=%d",sceneId,objId))
		end
	elseif flag == 113 then
		if x303006_BossMidID4[sceneId][3] == -1 then
			x303006_BossMidID4[sceneId][3] = objId
			x303006_BossMidID4_HP[sceneId][3] = GetHp(sceneId,objId)
			WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID4[sceneId][3]=%d",sceneId,objId))
		elseif x303006_BossMidID4[sceneId][4] == -1 then
			x303006_BossMidID4[sceneId][4] = objId
			x303006_BossMidID4_HP[sceneId][4] = GetHp(sceneId,objId)
			WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID4[sceneId][4]=%d",sceneId,objId))
		end
	elseif flag == 23 then
		x303006_BossRhtID4[sceneId][1] = objId
		x303006_BossRhtID4_HP[sceneId][1] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossRhtID4[sceneId][1]=%d",sceneId,objId))
	elseif flag == 123 then
		x303006_BossRhtID4[sceneId][2] = objId
		x303006_BossRhtID4_HP[sceneId][2] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossRhtID4[sceneId][2]=%d",sceneId,objId))
	end
	
	--第五批
	if flag == 31 then
		if x303006_BossMidID5[sceneId][1] == -1 then
			x303006_BossMidID5[sceneId][1] = objId
			x303006_BossMidID5_HP[sceneId][1] = GetHp(sceneId,objId)
			WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID5[sceneId][1]=%d",sceneId,objId))
		elseif x303006_BossMidID5[sceneId][2] == -1 then
			x303006_BossMidID5[sceneId][2] = objId
			x303006_BossMidID5_HP[sceneId][2] = GetHp(sceneId,objId)
			WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID5[sceneId][2]=%d",sceneId,objId))
		end
	elseif flag == 131 then
		if x303006_BossMidID5[sceneId][3] == -1 then
			x303006_BossMidID5[sceneId][3] = objId
			x303006_BossMidID5_HP[sceneId][3] = GetHp(sceneId,objId)
			WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID5[sceneId][3]=%d",sceneId,objId))
		elseif x303006_BossMidID5[sceneId][4] == -1 then
			x303006_BossMidID5[sceneId][4] = objId
			x303006_BossMidID5_HP[sceneId][4] = GetHp(sceneId,objId)
			WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID5[sceneId][4]=%d",sceneId,objId))
		end
	end
	
	--第六批
	if flag == 50 then
		x303006_BossMidID6[sceneId][1] = objId
		x303006_BossMidID6_HP[sceneId][1] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID6[sceneId][1]=%d",sceneId,objId))
	elseif flag == 150 then
		x303006_BossMidID6[sceneId][2] = objId
		x303006_BossMidID6_HP[sceneId][2] = GetHp(sceneId,objId)
		WriteLog(1,format("P6BL:x303006_SetBossID sceneId=%d,x303006_BossMidID6[sceneId][2]=%d",sceneId,objId))
	end
end


---------------------------------------------------------------------------------------------------
--更新BOSS的血和以及时间信息
---------------------------------------------------------------------------------------------------
function x303006_OnUpdateBossHP( sceneId )
	
	local nMode = mod(x303006_SceneInfo[sceneId].TICKCOUNT,x303006_g_HT_Time)
	if nMode ~= 0 then
		return
	end
	
	--第一批 第一批箭塔
	for i,itm in x303006_BossLftID1[sceneId] do
		local itm2 = x303006_BossLftID1_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossLftID1_HP[sceneId][i] = hp
				x303006_ShowTips_BossTaBeAttched(sceneId,i,3,1)
			end
		end
	end
	
	for i,itm in x303006_BossMidID1[sceneId] do
		local itm2 = x303006_BossMidID1_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossMidID1_HP[sceneId][i] = hp
				x303006_ShowTips_BossTaBeAttched(sceneId,i,2,1)
			end
		end
	end
	
	for i,itm in x303006_BossRhtID1[sceneId] do
		local itm2 = x303006_BossRhtID1_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossRhtID1_HP[sceneId][i] = hp
				x303006_ShowTips_BossTaBeAttched(sceneId,i,1,1)
			end
		end
	end
	
	--第二批 第二批箭塔
	for i,itm in x303006_BossLftID2[sceneId] do
		local itm2 = x303006_BossLftID2_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossLftID2_HP[sceneId][i] = hp
				x303006_ShowTips_BossTaBeAttched(sceneId,i,3,2)
			end
		end
	end
	
	for i,itm in x303006_BossMidID2[sceneId] do
		local itm2 = x303006_BossMidID2_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossMidID2_HP[sceneId][i] = hp
				x303006_ShowTips_BossTaBeAttched(sceneId,i,2,2)
			end
		end
	end
	
	for i,itm in x303006_BossRhtID2[sceneId] do
		local itm2 = x303006_BossRhtID2_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossRhtID2_HP[sceneId][i] = hp
				x303006_ShowTips_BossTaBeAttched(sceneId,i,1,2)
			end
		end
	end

	--第三批 第三批箭塔
	for i,itm in x303006_BossLftID3[sceneId] do
		local itm2 = x303006_BossLftID3_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossLftID3_HP[sceneId][i] = hp
				x303006_ShowTips_BossTaBeAttched(sceneId,i,3,3)
			end
		end
	end
	
	for i,itm in x303006_BossMidID3[sceneId] do
		local itm2 = x303006_BossMidID3_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossMidID3_HP[sceneId][i] = hp
				x303006_ShowTips_BossTaBeAttched(sceneId,i,2,3)
			end
		end
	end
	
	for i,itm in x303006_BossRhtID3[sceneId] do
		local itm2 = x303006_BossRhtID3_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossRhtID3_HP[sceneId][i] = hp
				x303006_ShowTips_BossTaBeAttched(sceneId,i,1,3)
			end
		end
	end
	
	--第四批 这个是基地,一共四个
	for i,itm in x303006_BossLftID4[sceneId] do
		local itm2 = x303006_BossLftID4_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossLftID4_HP[sceneId][i] = hp
				x303006_ShowTips_BossBaseBeAttched(sceneId,i,3)
			end
		end
	end
	
	for i,itm in x303006_BossMidID4[sceneId] do
		local itm2 = x303006_BossMidID4_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossMidID4_HP[sceneId][i] = hp
				if i < 3 then
					x303006_ShowTips_BossBaseBeAttched(sceneId,1,2)
				else
					x303006_ShowTips_BossBaseBeAttched(sceneId,2,2)
				end
			end
		end
	end
	
	for i,itm in x303006_BossRhtID4[sceneId] do
		local itm2 = x303006_BossRhtID4_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossRhtID4_HP[sceneId][i] = hp
				x303006_ShowTips_BossBaseBeAttched(sceneId,i,1)
			end
		end
	end
	
	--第五批 主基地前的两个塔
	for i,itm in x303006_BossMidID5[sceneId] do
		local itm2 = x303006_BossMidID5_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossMidID5_HP[sceneId][i] = hp
				if i < 3 then
					x303006_ShowTips_BossTaBeAttched(sceneId,1,2,5)
				else
					x303006_ShowTips_BossTaBeAttched(sceneId,2,2,5)
				end
			end
		end
	end
	
	--第六批 这个是主基地
	for i,itm in x303006_BossMidID6[sceneId] do
		local itm2 = x303006_BossMidID6_HP[sceneId][i]
		if IsObjValid(sceneId,itm) == 1 then
			local hp = GetHp(sceneId,itm)
			if hp > 0 and itm2 ~= hp then
				x303006_BossMidID6_HP[sceneId][i] = hp
				x303006_ShowTips_BossBaseMainBeAttched( sceneId,i )
			end
		end
	end
end


---------------------------------------------------------------------------------------------------
--创建攻击的BOSS
---------------------------------------------------------------------------------------------------
function x303006_OnCreateBossAttack(sceneId)
	
	--初始化攻击BOSS的数据
	x303006_BossLftID1_Attack[sceneId] = { -1,-1 }
	x303006_BossMidID1_Attack[sceneId] = { -1,-1 }
	x303006_BossRhtID1_Attack[sceneId] = { -1,-1 }
	                          
	x303006_BossLftID2_Attack[sceneId] = { -1,-1 }
	x303006_BossMidID2_Attack[sceneId] = { -1,-1 }
	x303006_BossRhtID2_Attack[sceneId] = { -1,-1 }
	                          
	x303006_BossLftID3_Attack[sceneId] = { -1,-1 }
	x303006_BossMidID3_Attack[sceneId] = { -1,-1 }
	x303006_BossRhtID3_Attack[sceneId] = { -1,-1 }
	
	x303006_BossLftID4_Attack[sceneId] = { -1,-1 }			
	x303006_BossMidID4_Attack[sceneId] = { -1,-1,-1,-1 }	
	x303006_BossRhtID4_Attack[sceneId] = { -1,-1 }			
	                          
	x303006_BossMidID5_Attack[sceneId] = { -1,-1,-1,-1 }
	
	--开始创建BOSS
	local nIndexFrom = GetFubenDataPosByScriptID( x303006_g_scriptId )
	local nDataCount = GetFubenDataCountByScriptID( x303006_g_scriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x303006_g_scriptId,nIndexFrom,i)
		if idScript == x303006_g_scriptId and monsterFlag == 1000 and x303006_CheckLevelRange(sceneId, levelmin,levelmax) == 1 then
            for j=0,count -1 do
            	
				if title~="" then
					local objId = CreateMonster(sceneId, type, x, z, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir, "", title)
					x303006_SetBossIDAttack(sceneId,objId,flag)
				else
					local objId = CreateMonster(sceneId, type, x, z, ai, aiscript, x303006_g_scriptId, -1, camp, -1,facedir)
					x303006_SetBossIDAttack(sceneId,objId,flag)
				end
			end
        end
	end

end


---------------------------------------------------------------------------------------------------
--设置BOSSID
---------------------------------------------------------------------------------------------------
function x303006_SetBossIDAttack(sceneId,objId,flag)

	--第一排
	if flag == 0 then
		x303006_BossLftID1_Attack[sceneId][1] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossLftID1_Attack[sceneId][1]=%d",sceneId,objId))
	elseif flag == 100 then
		x303006_BossLftID1_Attack[sceneId][2] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossLftID1_Attack[sceneId][2]=%d",sceneId,objId))
	elseif flag == 10 then
		x303006_BossMidID1_Attack[sceneId][1] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID1_Attack[sceneId][1]=%d",sceneId,objId))
	elseif flag == 110 then
		x303006_BossMidID1_Attack[sceneId][2] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID1_Attack[sceneId][2]=%d",sceneId,objId))
	elseif flag == 20 then
		x303006_BossRhtID1_Attack[sceneId][1] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossRhtID1_Attack[sceneId][1]=%d",sceneId,objId))
	elseif flag == 120 then
		x303006_BossRhtID1_Attack[sceneId][2] = objId	
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossRhtID1_Attack[sceneId][2]=%d",sceneId,objId))
	end
	
	--第二批
	if flag == 1 then
		x303006_BossLftID2_Attack[sceneId][1] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossLftID2_Attack[sceneId][1]=%d",sceneId,objId))
	elseif flag == 101 then
		x303006_BossLftID2_Attack[sceneId][2] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossLftID2_Attack[sceneId][2]=%d",sceneId,objId))
	elseif flag == 11 then
		x303006_BossMidID2_Attack[sceneId][1] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID2_Attack[sceneId][1]=%d",sceneId,objId))
	elseif flag == 111 then
		x303006_BossMidID2_Attack[sceneId][2] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID2_Attack[sceneId][2]=%d",sceneId,objId))
	elseif flag == 21 then
		x303006_BossRhtID2_Attack[sceneId][1] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossRhtID2_Attack[sceneId][1]=%d",sceneId,objId))
	elseif flag == 121 then
		x303006_BossRhtID2_Attack[sceneId][2] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossRhtID2_Attack[sceneId][2]=%d",sceneId,objId))
	end
	
	--第三批
	if flag == 2 then
		x303006_BossLftID3_Attack[sceneId][1] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossLftID3_Attack[sceneId][1]=%d",sceneId,objId))
	elseif flag == 102 then
		x303006_BossLftID3_Attack[sceneId][2] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossLftID3_Attack[sceneId][2]=%d",sceneId,objId))
	elseif flag == 12 then
		x303006_BossMidID3_Attack[sceneId][1] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID3_Attack[sceneId][1]=%d",sceneId,objId))
	elseif flag == 112 then
		x303006_BossMidID3_Attack[sceneId][2] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID3_Attack[sceneId][2]=%d",sceneId,objId))
	elseif flag == 22 then
		x303006_BossRhtID3_Attack[sceneId][1] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossRhtID3_Attack[sceneId][1]=%d",sceneId,objId))
	elseif flag == 122 then
		x303006_BossRhtID3_Attack[sceneId][2] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossRhtID3_Attack[sceneId][2]=%d",sceneId,objId))
	end
	
	--第四批
	if flag == 3 then
		x303006_BossLftID4_Attack[sceneId][1] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossLftID4_Attack[sceneId][1]=%d",sceneId,objId))
	elseif flag == 103 then
		x303006_BossLftID4_Attack[sceneId][2] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossLftID4_Attack[sceneId][2]=%d",sceneId,objId))
	elseif flag == 13 then
		if x303006_BossMidID4_Attack[sceneId][1] == -1 then
			x303006_BossMidID4_Attack[sceneId][1] = objId
			WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID4_Attack[sceneId][1]=%d",sceneId,objId))
		elseif x303006_BossMidID4_Attack[sceneId][2] == -1 then
			x303006_BossMidID4_Attack[sceneId][2] = objId
			WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID4_Attack[sceneId][2]=%d",sceneId,objId))
		end
	elseif flag == 113 then
		if x303006_BossMidID4_Attack[sceneId][3] == -1 then
			x303006_BossMidID4_Attack[sceneId][3] = objId
			WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID4_Attack[sceneId][3]=%d",sceneId,objId))
		elseif x303006_BossMidID4_Attack[sceneId][4] == -1 then
			x303006_BossMidID4_Attack[sceneId][4] = objId
			WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID4_Attack[sceneId][4]=%d",sceneId,objId))
		end
	elseif flag == 23 then
		x303006_BossRhtID4_Attack[sceneId][1] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossRhtID4_Attack[sceneId][1]=%d",sceneId,objId))
	elseif flag == 123 then
		x303006_BossRhtID4_Attack[sceneId][2] = objId
		WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossRhtID4_Attack[sceneId][2]=%d",sceneId,objId))
	end
	
	--第五批
	if flag == 31 then
		if x303006_BossMidID5_Attack[sceneId][1] == -1 then
			x303006_BossMidID5_Attack[sceneId][1] = objId
			WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID5_Attack[sceneId][1]=%d",sceneId,objId))
		elseif x303006_BossMidID5_Attack[sceneId][2] == -1 then
			x303006_BossMidID5_Attack[sceneId][2] = objId
			WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID5_Attack[sceneId][2]=%d",sceneId,objId))
		end
	elseif flag == 131 then
		if x303006_BossMidID5_Attack[sceneId][3] == -1 then
			x303006_BossMidID5_Attack[sceneId][3] = objId
			WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID5_Attack[sceneId][3]=%d",sceneId,objId))
		elseif x303006_BossMidID5_Attack[sceneId][4] == -1 then
			x303006_BossMidID5_Attack[sceneId][4] = objId
			WriteLog(1,format("P6BL:x303006_SetBossIDAttack sceneId=%d,x303006_BossMidID5_Attack[sceneId][4]=%d",sceneId,objId))
		end
	end
end

---------------------------------------------------------------------------------------------------
--删除所有怪物
---------------------------------------------------------------------------------------------------
function x303006_OnMonsterDestroy(sceneId,why)

	--销毁BOSS数据	
	x303006_BossLftID1[sceneId] = { -1,-1 }			
	x303006_BossMidID1[sceneId] = { -1,-1 }			
	x303006_BossRhtID1[sceneId] = { -1,-1 }			
	                   
	x303006_BossLftID2[sceneId] = { -1,-1 }			
	x303006_BossMidID2[sceneId] = { -1,-1 }			
	x303006_BossRhtID2[sceneId] = { -1,-1 }			
	                   
	x303006_BossLftID3[sceneId] = { -1,-1 }			
	x303006_BossMidID3[sceneId] = { -1,-1 }			
	x303006_BossRhtID3[sceneId] = { -1,-1 }			
	                   
	x303006_BossLftID4[sceneId] = { -1,-1 }			
	x303006_BossMidID4[sceneId] = { -1,-1,-1,-1 }	
	x303006_BossRhtID4[sceneId] = { -1,-1 }			
	                   
	x303006_BossMidID5[sceneId] = { -1,-1,-1,-1 }	
	
	x303006_BossMidID6[sceneId] = { -1,-1 }	
	
	x303006_BossMid5DieFlag[sceneId]= { 0,0,}
	
	--销毁影子数据
	x303006_BossLftID1_Attack[sceneId] = { -1,-1 }
	x303006_BossMidID1_Attack[sceneId] = { -1,-1 }
	x303006_BossRhtID1_Attack[sceneId] = { -1,-1 }
	                          
	x303006_BossLftID2_Attack[sceneId] = { -1,-1 }
	x303006_BossMidID2_Attack[sceneId] = { -1,-1 }
	x303006_BossRhtID2_Attack[sceneId] = { -1,-1 }
	                          
	x303006_BossLftID3_Attack[sceneId] = { -1,-1 }
	x303006_BossMidID3_Attack[sceneId] = { -1,-1 }
	x303006_BossRhtID3_Attack[sceneId] = { -1,-1 }
	
	x303006_BossLftID4_Attack[sceneId] = { -1,-1 }			
	x303006_BossMidID4_Attack[sceneId] = { -1,-1,-1,-1 }	
	x303006_BossRhtID4_Attack[sceneId] = { -1,-1 }	
	                          
	x303006_BossMidID5_Attack[sceneId] = { -1,-1,-1,-1 }
	
	--销毁怪物血的数据
	x303006_BossLftID1_HP[sceneId] = { -1,-1 }
	x303006_BossMidID1_HP[sceneId] = { -1,-1 }
	x303006_BossRhtID1_HP[sceneId] = { -1,-1 }
	
	x303006_BossLftID2_HP[sceneId] = { -1,-1 }
	x303006_BossMidID2_HP[sceneId] = { -1,-1 }
	x303006_BossRhtID2_HP[sceneId] = { -1,-1 }
	
	x303006_BossLftID3_HP[sceneId] = { -1,-1 }
	x303006_BossMidID3_HP[sceneId] = { -1,-1 }
	x303006_BossRhtID3_HP[sceneId] = { -1,-1 }

	x303006_BossLftID4_HP[sceneId] = { -1,-1 }
	x303006_BossMidID4_HP[sceneId] = { -1,-1,-1,-1 }
	x303006_BossRhtID4_HP[sceneId] = { -1,-1 }

	x303006_BossMidID5_HP[sceneId] = { -1,-1,-1,-1 }

	x303006_BossMidID6_HP[sceneId] = { -1,-1 }
	
	--怪物创建信息
	x303006_MonsterLftCreateFlag[sceneId]		= { 0, 100 }	--左路Monster创建信息
	x303006_MonsterMidCreateFlag[sceneId]		= { 10,110 }	--中路Monster创建信息
	x303006_MonsterRhtCreateFlag[sceneId]		= { 20,120 }	--右路Monster创建信息	
	
	--删除以前创建的怪物数据
	local nMonsterCount = GetMonsterCount(sceneId)
	for i=0,nMonsterCount-1 do
		local objId = GetMonsterObjID(sceneId,i)
		if IsObjValid(sceneId,objId) == 1 and GetHp(sceneId,objId) > 0 then
			DeleteMonster(sceneId,objId)
		end
	end
	
	WriteLog(1,format("P6BL:x303006_OnMonsterDestroy sceneId=%d,Count=%d why=%d",sceneId,nMonsterCount,why))
end

---------------------------------------------------------------------------------------------------
--BOSS死亡奖励
---------------------------------------------------------------------------------------------------
function x303006_OnBossDieBonus( sceneId,nLevel,nBonusFlag )

	local nBonusCamp = -1
	if nBonusFlag == 1 then nBonusCamp = 6 end
	if nBonusFlag == 2 then nBonusCamp = 5 end
	
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			local nCamp = GetCurCamp( sceneId,humanId )
			if nCamp == nBonusCamp then
				local nBonus = (nLevel*4 - 270)
				x303006_AddBattleMoney(sceneId,humanId,nBonus)				
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--给周围玩家战场货币
---------------------------------------------------------------------------------------------------
function x303006_GiveAroundPlayerBattleMoney(sceneId,selfId,nBouns)

	local nBounsCamp = GetMonsterCamp(sceneId,selfId)
	if nBounsCamp ~= 5 and nBounsCamp ~= 6 then
		return
	end
	
	if nBounsCamp == 5 then 
		nBounsCamp = 6
	elseif nBounsCamp == 6 then 
		nBounsCamp = 5 
	end
	
	local playerTB = {}
	local playerCount = 0
	
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);

		--玩家有效,并且不能处于死亡状态		
		if IsPlayerStateNormal( sceneId,humanId ) == 1 and GetHp(sceneId,humanId) > 0  then
		
			
			local nDist = GetDist(sceneId,selfId,humanId,20)
			if  nDist <= 20 then
				
				local nCamp = GetCurCamp( sceneId,humanId )
				if nCamp == nBounsCamp then
					playerCount = playerCount + 1
					playerTB[playerCount] = humanId
				end
			end
			
			
		end
	end
	
	if playerCount <= 0 then
		return
	end
	
	local nResultBouns = nBouns / playerCount
	for i = 1,playerCount do
		x303006_AddBattleMoney(sceneId,playerTB[i],nResultBouns)
	end
end


function x303006_OnBossDieBonusBattleScore(sceneId,selfId)
	
	local nCamp = GetMonsterCamp(sceneId,selfId)
	if nCamp == 5 then
	
		--死的是铁木真军的箭塔或基地
		x303006_TeamInfoB_Score[sceneId] = x303006_TeamInfoB_Score[sceneId] + 3
		if x303006_TeamInfoB_Score[sceneId] > x303006_g_MaxScore then
			x303006_TeamInfoB_Score[sceneId] = x303006_g_MaxScore 
		end
		x303006_OnPVP6v6BattleScoreChanged(sceneId)
	elseif nCamp == 6 then
		
		--死的是札木合军的箭塔或基地
		x303006_TeamInfoA_Score[sceneId] = x303006_TeamInfoA_Score[sceneId] + 3
		if x303006_TeamInfoA_Score[sceneId] > x303006_g_MaxScore then
			x303006_TeamInfoA_Score[sceneId] = x303006_g_MaxScore 
		end
		x303006_OnPVP6v6BattleScoreChanged(sceneId)
		
	end
end

---------------------------------------------------------------------------------------------------
--怪物死亡事件
---------------------------------------------------------------------------------------------------
function x303006_OnDie(sceneId,selfId,killerId)
	
	--如果是宠物杀死,需要取得主人的信息
	local ObjType = GetObjType(sceneId, killerId)
	if ObjType == 3 then
		ObjType = 1
		killerId = GetOwnerID(sceneId, killerId)
	end
	
--	local nDebugStep = 0
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))

	--判断杀死怪物的是不是玩家
	local nBonus = 4*GetLevel(sceneId,selfId) - 270
	if IsPlayerStateNormal(sceneId,killerId) == 1 then
		
		--给奖励
		x303006_AddBattleMoney(sceneId,killerId,nBonus)
	end
	
	--nDebugStep = 2
	--WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	--野外BOSS
	if x303006_Monster_MF5[sceneId] == selfId then
		x303006_Monster_MF5[sceneId] = -1
		
		--如果是有效的玩家杀死的,取其阵营,创建怪物
		if IsPlayerStateNormal(sceneId,killerId) == 1 then
		
			local nCamp = GetCurCamp(sceneId,killerId)
			
			if nCamp == 5 then
				x303006_ShowTips_BossKilled(sceneId,selfId,1)
			elseif nCamp == 6 then
				x303006_ShowTips_BossKilled(sceneId,selfId,2)
			end
		
			x303006_OnCreateMonster_MF6(sceneId,nCamp)
		end
		WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_Monster_MF5[sceneId],objId=%d",sceneId,selfId))
		return
	end
	
--	nDebugStep = 3
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	--野外怪物
	for i,itm in x303006_Monster_MF4[sceneId] do
		if itm == selfId then
			x303006_Monster_MF4[sceneId][i] = -1
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_Monster_MF4[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
--	nDebugStep = 4
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	--第一批BOSS处理
	for i,itm in x303006_BossLftID1[sceneId] do
		if itm == selfId then
			x303006_MonsterLftCreateFlag[sceneId][i] =  x303006_MonsterLftCreateFlag[sceneId][i] + 1
			x303006_OnMonsterCreateFlagChanged(sceneId)
			SetMonsterCamp(sceneId,x303006_BossLftID2[sceneId][i],x303006_g_CampFlag[i])
			x303006_DelMonsterByID(sceneId,x303006_BossLftID1_Attack[sceneId][i])
			x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),i)
			x303006_AddBattlePower(sceneId,killerId,10)
			x303006_ShowTips_BossTa(sceneId,i,3)
			x303006_OnBossDieBonusBattleScore(sceneId,selfId)
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_BossLftID1[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
	
--	nDebugStep = 5
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	for i,itm in x303006_BossMidID1[sceneId] do
		if itm == selfId then
			x303006_MonsterMidCreateFlag[sceneId][i] =  x303006_MonsterMidCreateFlag[sceneId][i] + 1
			x303006_OnMonsterCreateFlagChanged(sceneId)
			SetMonsterCamp(sceneId,x303006_BossMidID2[sceneId][i],x303006_g_CampFlag[i])
			x303006_DelMonsterByID(sceneId,x303006_BossMidID1_Attack[sceneId][i])
			x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),i)
			x303006_AddBattlePower(sceneId,killerId,10)
			x303006_ShowTips_BossTa(sceneId,i,2)
			x303006_OnBossDieBonusBattleScore(sceneId,selfId)
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_BossMidID1[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
--	nDebugStep = 6
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	for i,itm in x303006_BossRhtID1[sceneId] do
		if itm == selfId then
			x303006_MonsterRhtCreateFlag[sceneId][i] =  x303006_MonsterRhtCreateFlag[sceneId][i] + 1
			x303006_OnMonsterCreateFlagChanged(sceneId)
			SetMonsterCamp(sceneId,x303006_BossRhtID2[sceneId][i],x303006_g_CampFlag[i])
			x303006_DelMonsterByID(sceneId,x303006_BossRhtID1_Attack[sceneId][i])
			x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),i)
			x303006_AddBattlePower(sceneId,killerId,10)
			x303006_ShowTips_BossTa(sceneId,i,1)
			x303006_OnBossDieBonusBattleScore(sceneId,selfId)
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_BossRhtID1[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
--	nDebugStep = 7
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	
	--第二批BOSS处理
	for i,itm in x303006_BossLftID2[sceneId] do
		if itm == selfId then
			x303006_MonsterLftCreateFlag[sceneId][i] =  x303006_MonsterLftCreateFlag[sceneId][i] + 1
			x303006_OnMonsterCreateFlagChanged(sceneId)
			SetMonsterCamp(sceneId,x303006_BossLftID3[sceneId][i],x303006_g_CampFlag[i])
			x303006_DelMonsterByID(sceneId,x303006_BossLftID2_Attack[sceneId][i])
			x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),i)
			x303006_AddBattlePower(sceneId,killerId,10)
			x303006_ShowTips_BossTa(sceneId,i,3)
			x303006_OnBossDieBonusBattleScore(sceneId,selfId)
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_BossLftID2[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
--	nDebugStep = 8
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	for i,itm in x303006_BossMidID2[sceneId] do
		if itm == selfId then
			x303006_MonsterMidCreateFlag[sceneId][i] =  x303006_MonsterMidCreateFlag[sceneId][i] + 1
			x303006_OnMonsterCreateFlagChanged(sceneId)
			SetMonsterCamp(sceneId,x303006_BossMidID3[sceneId][i],x303006_g_CampFlag[i])
			x303006_DelMonsterByID(sceneId,x303006_BossMidID2_Attack[sceneId][i])
			x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),i)
			x303006_AddBattlePower(sceneId,killerId,10)
			x303006_ShowTips_BossTa(sceneId,i,2)
			x303006_OnBossDieBonusBattleScore(sceneId,selfId)
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_BossMidID2[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
--	nDebugStep = 9
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	for i,itm in x303006_BossRhtID2[sceneId] do
		if itm == selfId then
			x303006_MonsterRhtCreateFlag[sceneId][i] =  x303006_MonsterRhtCreateFlag[sceneId][i] + 1
			x303006_OnMonsterCreateFlagChanged(sceneId)
			SetMonsterCamp(sceneId,x303006_BossRhtID3[sceneId][i],x303006_g_CampFlag[i])
			x303006_DelMonsterByID(sceneId,x303006_BossRhtID2_Attack[sceneId][i])
			x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),i)
			x303006_AddBattlePower(sceneId,killerId,10)
			x303006_ShowTips_BossTa(sceneId,i,1)
			x303006_OnBossDieBonusBattleScore(sceneId,selfId)
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_BossRhtID2[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
--	nDebugStep = 10
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	--第三批BOSS处理
	for i,itm in x303006_BossLftID3[sceneId] do
		if itm == selfId then
			x303006_MonsterLftCreateFlag[sceneId][i] =  x303006_MonsterLftCreateFlag[sceneId][i] + 1
			x303006_OnMonsterCreateFlagChanged(sceneId)
			SetMonsterCamp(sceneId,x303006_BossLftID4[sceneId][i],x303006_g_CampFlag[i])
			x303006_DelMonsterByID(sceneId,x303006_BossLftID3_Attack[sceneId][i])
			x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),i)
			x303006_AddBattlePower(sceneId,killerId,10)
			x303006_ShowTips_BossTa(sceneId,i,3)
			x303006_OnBossDieBonusBattleScore(sceneId,selfId)
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_BossLftID3[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
--	nDebugStep = 11
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	for i,itm in x303006_BossMidID3[sceneId] do
		if itm == selfId then
			x303006_MonsterMidCreateFlag[sceneId][i] =  x303006_MonsterMidCreateFlag[sceneId][i] + 1
			x303006_OnMonsterCreateFlagChanged(sceneId)
			if i < 2 then
				SetMonsterCamp(sceneId,x303006_BossMidID4[sceneId][1],x303006_g_CampFlag[1])
				SetMonsterCamp(sceneId,x303006_BossMidID4[sceneId][2],x303006_g_CampFlag[1])
				x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),1)
				x303006_ShowTips_BossTa(sceneId,1,2)
			else
				SetMonsterCamp(sceneId,x303006_BossMidID4[sceneId][3],x303006_g_CampFlag[2])
				SetMonsterCamp(sceneId,x303006_BossMidID4[sceneId][4],x303006_g_CampFlag[2])
				x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),2)
				x303006_ShowTips_BossTa(sceneId,2,2)
			end
			
			x303006_DelMonsterByID(sceneId,x303006_BossMidID3_Attack[sceneId][i])
			x303006_AddBattlePower(sceneId,killerId,10)
			x303006_OnBossDieBonusBattleScore(sceneId,selfId)
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_BossMidID3[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
--	nDebugStep = 12
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	for i,itm in x303006_BossRhtID3[sceneId] do
		if itm == selfId then
			x303006_MonsterRhtCreateFlag[sceneId][i] =  x303006_MonsterRhtCreateFlag[sceneId][i] + 1
			x303006_OnMonsterCreateFlagChanged(sceneId)
			SetMonsterCamp(sceneId,x303006_BossRhtID4[sceneId][i],x303006_g_CampFlag[i])
			x303006_DelMonsterByID(sceneId,x303006_BossRhtID3_Attack[sceneId][i])
			x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),i)
			x303006_AddBattlePower(sceneId,killerId,10)
			x303006_ShowTips_BossTa(sceneId,i,1)
			x303006_OnBossDieBonusBattleScore(sceneId,selfId)
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_BossRhtID3[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
--	nDebugStep = 13
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	--第四批BOSS处理,这个主要是建筑,不是箭塔,所以这里不加士气
	--此部分处理为特殊处理,当其中任何一个3 13 23 103 113 123阵营死亡,则开启31号BOSS可攻击
	for i,itm in x303006_BossLftID4[sceneId] do
		if itm == selfId then
			x303006_MonsterLftCreateFlag[sceneId][i] =  x303006_MonsterLftCreateFlag[sceneId][i] + 2
			x303006_OnMonsterCreateFlagChanged(sceneId)
			if i < 2 then
				if IsObjValid(sceneId,x303006_BossMidID5[sceneId][1]) == 1 then
					SetMonsterCamp(sceneId,x303006_BossMidID5[sceneId][1],x303006_g_CampFlag[1])
				end
				if IsObjValid(sceneId,x303006_BossMidID5[sceneId][2]) == 1 then
					SetMonsterCamp(sceneId,x303006_BossMidID5[sceneId][2],x303006_g_CampFlag[1])
				end
				
				x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),1)
				x303006_ShowTips_MonsterFlagChanged_1(sceneId,1,3)
			else
				if IsObjValid(sceneId,x303006_BossMidID5[sceneId][3]) == 1 then
					SetMonsterCamp(sceneId,x303006_BossMidID5[sceneId][3],x303006_g_CampFlag[2])
				end
				if IsObjValid(sceneId,x303006_BossMidID5[sceneId][4]) == 1 then
					SetMonsterCamp(sceneId,x303006_BossMidID5[sceneId][4],x303006_g_CampFlag[2])
				end
				
				x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),2)
				x303006_ShowTips_MonsterFlagChanged_1(sceneId,2,3)
			end
			
			x303006_DelMonsterByID(sceneId,x303006_BossLftID4_Attack[sceneId][i])
			x303006_OnBossDieBonusBattleScore(sceneId,selfId)
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_BossLftID4[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
--	nDebugStep = 14
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	for i,itm in x303006_BossMidID4[sceneId] do
		if itm == selfId then
			if i < 3 then
				x303006_MonsterMidCreateFlag[sceneId][1] =  x303006_MonsterMidCreateFlag[sceneId][1] + 1
				x303006_OnMonsterCreateFlagChanged(sceneId)
				if x303006_MonsterMidCreateFlag[sceneId][1] == 15 then
					if IsObjValid(sceneId,x303006_BossMidID5[sceneId][1]) == 1 then
						SetMonsterCamp(sceneId,x303006_BossMidID5[sceneId][1],x303006_g_CampFlag[1])
					end
					if IsObjValid(sceneId,x303006_BossMidID5[sceneId][2]) == 1 then
						SetMonsterCamp(sceneId,x303006_BossMidID5[sceneId][2],x303006_g_CampFlag[1])
					end
				end
				
				x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),1)
				
				--检查两个怪是否都已死
				if ( IsObjValid(sceneId,x303006_BossMidID4[sceneId][1]) ~= 1  or GetHp(sceneId,x303006_BossMidID4[sceneId][1]) <= 0 ) and
				   ( IsObjValid(sceneId,x303006_BossMidID4[sceneId][2]) ~= 1  or GetHp(sceneId,x303006_BossMidID4[sceneId][2]) <= 0 ) then
					x303006_ShowTips_MonsterFlagChanged_1(sceneId,1,2)
				end
				
			else
				x303006_MonsterMidCreateFlag[sceneId][2] =  x303006_MonsterMidCreateFlag[sceneId][2] + 1
				x303006_OnMonsterCreateFlagChanged(sceneId)
				if x303006_MonsterMidCreateFlag[sceneId][2] == 115 then
					if IsObjValid(sceneId,x303006_BossMidID5[sceneId][3]) == 1 then
						SetMonsterCamp(sceneId,x303006_BossMidID5[sceneId][3],x303006_g_CampFlag[2])
					end
					if IsObjValid(sceneId,x303006_BossMidID5[sceneId][4]) == 1 then
						SetMonsterCamp(sceneId,x303006_BossMidID5[sceneId][4],x303006_g_CampFlag[2])
					end
				end
				
				x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),2)
				
				--检查两个怪是否都已死
				if ( IsObjValid(sceneId,x303006_BossMidID4[sceneId][3]) ~= 1  or GetHp(sceneId,x303006_BossMidID4[sceneId][3]) <= 0 ) and
				   ( IsObjValid(sceneId,x303006_BossMidID4[sceneId][4]) ~= 1  or GetHp(sceneId,x303006_BossMidID4[sceneId][4]) <= 0 ) then
					x303006_ShowTips_MonsterFlagChanged_1(sceneId,2,2)
				end
			end
			x303006_DelMonsterByID(sceneId,x303006_BossMidID4_Attack[sceneId][i])
			x303006_OnBossDieBonusBattleScore(sceneId,selfId)
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_BossMidID4[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
--	nDebugStep = 16
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	for i,itm in x303006_BossRhtID4[sceneId] do
		if itm == selfId then
			if i < 2 then
				x303006_MonsterRhtCreateFlag[sceneId][1] =  x303006_MonsterRhtCreateFlag[sceneId][1] + 2
				x303006_OnMonsterCreateFlagChanged(sceneId)
			
				if IsObjValid(sceneId,x303006_BossMidID5[sceneId][1]) == 1 then
					SetMonsterCamp(sceneId,x303006_BossMidID5[sceneId][1],x303006_g_CampFlag[1])
				end
				if IsObjValid(sceneId,x303006_BossMidID5[sceneId][2]) == 1 then
					SetMonsterCamp(sceneId,x303006_BossMidID5[sceneId][2],x303006_g_CampFlag[1])
				end
				
				x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),1)
				x303006_ShowTips_MonsterFlagChanged_1(sceneId,1,1)
			else
				x303006_MonsterRhtCreateFlag[sceneId][2] =  x303006_MonsterRhtCreateFlag[sceneId][2] + 2
				x303006_OnMonsterCreateFlagChanged(sceneId)
				if IsObjValid(sceneId,x303006_BossMidID5[sceneId][3]) == 1 then
					SetMonsterCamp(sceneId,x303006_BossMidID5[sceneId][3],x303006_g_CampFlag[2])
				end
				if IsObjValid(sceneId,x303006_BossMidID5[sceneId][4]) == 1 then
					SetMonsterCamp(sceneId,x303006_BossMidID5[sceneId][4],x303006_g_CampFlag[2])
				end
				
				x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),2)
				x303006_ShowTips_MonsterFlagChanged_1(sceneId,2,1)
			end
			x303006_DelMonsterByID(sceneId,x303006_BossRhtID4_Attack[sceneId][i])
			x303006_OnBossDieBonusBattleScore(sceneId,selfId)
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_BossRhtID4[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
--	nDebugStep = 17
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	--第五批BOSS处理
	for i,itm in x303006_BossMidID5[sceneId] do
		if itm == selfId then
			if i < 3 then
				x303006_BossMid5DieFlag[sceneId][1] = x303006_BossMid5DieFlag[sceneId][1] + 1
				if x303006_BossMid5DieFlag[sceneId][1] == 2 then
					if IsObjValid(sceneId,x303006_BossMidID6[sceneId][1]) == 1 then
						SetMonsterCamp(sceneId,x303006_BossMidID6[sceneId][1],x303006_g_CampFlag[1])
					end
				end
				
				x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),1)
				x303006_ShowTips_BossTa2(sceneId,1)
			else
				x303006_BossMid5DieFlag[sceneId][2] = x303006_BossMid5DieFlag[sceneId][2] + 1
				if x303006_BossMid5DieFlag[sceneId][2] == 2 then
					if IsObjValid(sceneId,x303006_BossMidID6[sceneId][2]) == 1 then
						SetMonsterCamp(sceneId,x303006_BossMidID6[sceneId][2],x303006_g_CampFlag[2])
					end
				end
				
				x303006_OnBossDieBonus(sceneId,GetLevel(sceneId,selfId),2)
				x303006_ShowTips_BossTa2(sceneId,2)
			end
			x303006_DelMonsterByID(sceneId,x303006_BossMidID5_Attack[sceneId][i])
			x303006_AddBattlePower(sceneId,killerId,10)
			x303006_OnBossDieBonusBattleScore(sceneId,selfId)
			WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d, x303006_BossMidID5[sceneId][%d],objId=%d",sceneId,i,selfId))
			return
		end
	end
	
--	nDebugStep = 18
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	--第六批BOSS处理(主基地BOSS死亡处理)
	for i,itm in x303006_BossMidID6[sceneId] do
		if itm == selfId then
			x303006_BossDieFlag[sceneId] = i
			
			--战场结束
            x303006_OnBattleSceneClose( sceneId,5 )
            WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d  boss die! ",sceneId ))
            return
		end		
	end
	
--	nDebugStep = 19
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	--增加己方士气
	x303006_AddBattlePower(sceneId,killerId,1)
	
--	nDebugStep =  1
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
	
	x303006_GiveAroundPlayerBattleMoney(sceneId,selfId,nBonus)	--给周围玩家的ID
	
--	nDebugStep = 20
--	WriteLog(1,format("P6BL:x303006_OnDie sceneId=%d,step = %d",sceneId,nDebugStep))
end

---------------------------------------------------------------------------------------------------
--怪物创建参数改变事件
---------------------------------------------------------------------------------------------------
function x303006_OnMonsterCreateFlagChanged(sceneId)

	WriteLog(1,format("P6BL:x303006_OnMonsterCreateFlagChanged L:%d,%d M:%d,%d R:%d,%d",x303006_MonsterLftCreateFlag[sceneId][1],x303006_MonsterLftCreateFlag[sceneId][2],x303006_MonsterMidCreateFlag[sceneId][1],x303006_MonsterMidCreateFlag[sceneId][2],x303006_MonsterRhtCreateFlag[sceneId][1],x303006_MonsterRhtCreateFlag[sceneId][2]))
	
	if x303006_MonsterLftCreateFlag[sceneId][1] == 5 and x303006_MonsterMidCreateFlag[sceneId][1] == 15 and x303006_MonsterRhtCreateFlag[sceneId][1] == 25 then
	   
	   x303006_MonsterLftCreateFlag[sceneId][1] = 9
	   x303006_MonsterMidCreateFlag[sceneId][1] = 19
	   x303006_MonsterRhtCreateFlag[sceneId][1] = 29
	   
	   x303006_ShowTips_MonsterFlagChanged_2(sceneId,1)
	end
	
	if x303006_MonsterLftCreateFlag[sceneId][2] == 105 and x303006_MonsterMidCreateFlag[sceneId][2] == 115 and x303006_MonsterRhtCreateFlag[sceneId][2] == 125 then
	   
	   x303006_MonsterLftCreateFlag[sceneId][2] = 109
	   x303006_MonsterMidCreateFlag[sceneId][2] = 119
	   x303006_MonsterRhtCreateFlag[sceneId][2] = 129
	   
	   x303006_ShowTips_MonsterFlagChanged_2(sceneId,2)
	end	
end

---------------------------------------------------------------------------------------------------
--初始化战场货币
---------------------------------------------------------------------------------------------------
function x303006_InitBattleMoney( sceneId,selfId)
	if x303006_GetPlayerEnterSceneFlag( sceneId,selfId ) == 0 then
		x303006_SetBattleMoney( sceneId,selfId ,x303006_g_FirstGiveMoney) 
	else
		x303006_SetBattleMoney( sceneId,selfId ,0)
	end 
end

---------------------------------------------------------------------------------------------------
--重置战场货币
---------------------------------------------------------------------------------------------------
function x303006_ResetBattleMoney( sceneId,selfId)
	x303006_SetBattleMoney( sceneId,selfId ,0) 
end

---------------------------------------------------------------------------------------------------
--取得战场货币
---------------------------------------------------------------------------------------------------
function x303006_GetBattleMoney(sceneId,selfId)
	return GetPlayerRuntimeData( sceneId,selfId,RD_PVP6V6_BATTLE_MONEY) 
end

---------------------------------------------------------------------------------------------------
--设置战场货币
---------------------------------------------------------------------------------------------------
function x303006_SetBattleMoney(sceneId,selfId,nMoney)
	if nMoney < 0 then
		nMoney = 0
	end
	
	
	SetPlayerRuntimeData( sceneId,selfId,RD_PVP6V6_BATTLE_MONEY ,nMoney) 
	
	--当战场货币改变了,需要通知客户端
	SendPVP6v6BattleMoney(sceneId,selfId,x303006_GetBattleMoney(sceneId,selfId))
end

---------------------------------------------------------------------------------------------------
--添加战场货币
---------------------------------------------------------------------------------------------------
function x303006_AddBattleMoney(sceneId,selfId,nMoney)
	local nCalcMoney = nMoney + GetPlayerRuntimeData( sceneId,selfId,RD_PVP6V6_BATTLE_MONEY) 
	x303006_SetBattleMoney(sceneId,selfId,nCalcMoney)
end

---------------------------------------------------------------------------------------------------
--减少战场货币
---------------------------------------------------------------------------------------------------
function x303006_SubBattleMoney(sceneId,selfId,nMoney)
	local nCalcMoney = GetPlayerRuntimeData( sceneId,selfId,RD_PVP6V6_BATTLE_MONEY) - nMoney 
	x303006_SetBattleMoney(sceneId,selfId,nCalcMoney)
end

---------------------------------------------------------------------------------------------------
--删除怪物
---------------------------------------------------------------------------------------------------
function x303006_DelMonsterByID(sceneId,objId)
	if IsObjValid(sceneId,objId) == 1 then
		DeleteMonster(sceneId,objId)
	end
end

---------------------------------------------------------------------------------------------------
--玩家事件响应
---------------------------------------------------------------------------------------------------
function x303006_OnPlayerEvent(sceneId,nTickCount)	
	
	local flag1 = 0
	if mod(nTickCount, 5) == 0 then flag1 = 1 end 	
	
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			--事件1:每五秒钟给五点战场货币
			if flag1 == 1 then
				x303006_AddBattleMoney(sceneId,humanId,5)
			end
		end
	end	
end

---------------------------------------------------------------------------------------------------
--添加战场方士气
---------------------------------------------------------------------------------------------------
function x303006_AddBattlePower(sceneId,killerId,nPower)
	
	if IsPlayerStateNormal(sceneId,killerId) ~= 1 then
		return
	end
	
	local nCampFlag = GetCurCamp(sceneId,killerId)
	if nCampFlag ~= 5 and nCampFlag ~= 6 then
		return
	end
	
	if nCampFlag == 5 then
		x303006_AddBattlePowerA(sceneId,nPower)
	else
		x303006_AddBattlePowerB(sceneId,nPower)
	end
	
end

---------------------------------------------------------------------------------------------------
--添加战场A方士气
---------------------------------------------------------------------------------------------------
function x303006_AddBattlePowerA(sceneId,nPower)
	x303006_TeamInfoA_Power[sceneId] = x303006_TeamInfoA_Power[sceneId] + nPower
	if x303006_TeamInfoA_Power[sceneId] >= x303006_g_Power_BoilVal then
		
		local flag,power = x303006_GetPowerBoilFlag()
		
		--减少增加的值
		x303006_TeamInfoA_Power[sceneId] = x303006_TeamInfoA_Power[sceneId] - power
		
		--触发事件
		x303006_OnPowerBoilEvent(sceneId,flag,5)
	end
	
	--通知所有玩家,Power值发生变化
	x303006_SyncPowerToPlayer(sceneId,5)
end


---------------------------------------------------------------------------------------------------
--添加战场B方士气
---------------------------------------------------------------------------------------------------
function x303006_AddBattlePowerB(sceneId,nPower)
	x303006_TeamInfoB_Power[sceneId] = x303006_TeamInfoB_Power[sceneId] + nPower
	if x303006_TeamInfoB_Power[sceneId] >= x303006_g_Power_BoilVal then
		
		local flag,power = x303006_GetPowerBoilFlag()
		
		--减少增加的值
		x303006_TeamInfoB_Power[sceneId] = x303006_TeamInfoB_Power[sceneId] - power
		
		--触发事件
		x303006_OnPowerBoilEvent(sceneId,flag,6)
	end
	
	--通知所有玩家,Power值发生变化
	x303006_SyncPowerToPlayer(sceneId,6)
end

---------------------------------------------------------------------------------------------------
--取得Boil事件
---------------------------------------------------------------------------------------------------
function x303006_GetPowerBoilFlag()
	
	local nCurFlag = 1
	local nMaxRand = -1
	
	for i,itm in x303006_g_PowerRandomList do
		
		local nRand = random(1,itm.randval)
		if nRand > nMaxRand then
			nCurFlag = i
			nMaxRand = nRand
		end
	end
	
	
	--做容错处理
	if nCurFlag <= 0 then
		nCurFlag = 1
	end
	
	if nCurFlag > getn(x303006_g_PowerRandomList) then
		nCurFlag = getn(x303006_g_PowerRandomList)
	end
	
	return nCurFlag,x303006_g_PowerRandomList[nCurFlag].power
end

---------------------------------------------------------------------------------------------------
--士气达到事件值的时候,触发事件
---------------------------------------------------------------------------------------------------
function x303006_OnPowerBoilEvent(sceneId,nPowerFlag,nCampFlag)
	
	--测试
--	if x303006_g_Test == 1 then
--		x303006_OnCreateMonster_MF8(sceneId,nCampFlag)
--		return
--	end
	
	--给己方添加增益BUF
	if nPowerFlag == 1 then
		x303006_OnPowerBoilGiveGoodBuf(sceneId,nCampFlag)
		return
	end
	
	--给敌方添加减益BUF
	if nPowerFlag == 2 then
		x303006_OnPowerBoilGiveBadBuf(sceneId,nCampFlag)
		--x303006_ShowTips_PowerTips(sceneId,nFlag,nPowerFlag)
		return
	end
	
	--随机创建一路己方阵营的怪物
	if nPowerFlag == 3 then
		x303006_OnCreateMonster_MF8(sceneId,nCampFlag)
		return
	end
end

---------------------------------------------------------------------------------------------------
--士气达到事件值的时候,给BUF
---------------------------------------------------------------------------------------------------
function x303006_OnPowerBoilGiveGoodBuf(sceneId,nCampFlag)

	local nFlag = -1
	if nCampFlag == 5 then
		nFlag = 1
	else
		nFlag = 2
	end

	local n = getn(x303006_g_PowerGoodBuf)
	local nRandVal = random(1,n)
	
	--容错处理
	if nRandVal <= 0 then
		nRandVal = 1
	end
	
	if nRandVal > n then
		nRandVal = 1
	end
	
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 and GetCurCamp(sceneId,humanId) == nCampFlag then
			SendSpecificImpactToUnit(sceneId,humanId,humanId,humanId,x303006_g_PowerGoodBuf[nRandVal],0) 
		end
	end
	
	x303006_ShowTips_PowerTips(sceneId,nFlag,1)
end

---------------------------------------------------------------------------------------------------
--士气达到事件值的时候,给BUF
---------------------------------------------------------------------------------------------------
function x303006_OnPowerBoilGiveBadBuf(sceneId,nCampFlag)
	
	local n = getn(x303006_g_PowerBadBuf)
	local nRandVal = random(1,n)
	
	--容错处理
	if nRandVal <= 0 then
		nRandVal = 1
	end
	
	if nRandVal > n then
		nRandVal = 1
	end
	
	local nFlag = -1
	local camp = -1 
	if nCampFlag == 5 then
		camp = 6
		nFlag = 1
	else
		camp = 5
		nFlag = 2
	end	
	
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 and GetCurCamp(sceneId,humanId) == camp then
			SendSpecificImpactToUnit(sceneId,humanId,humanId,humanId,x303006_g_PowerBadBuf[nRandVal],0) 
		end
	end
	
	x303006_ShowTips_PowerTips(sceneId,nFlag,2)
end

---------------------------------------------------------------------------------------------------
--更新某个玩家的士气值
---------------------------------------------------------------------------------------------------
function x303006_SendPowerToPlayer(sceneId,selfId)
	
	local nSelfCamp = GetCurCamp(sceneId,selfId)
	if nSelfCamp == 5 then
		SendPVP6v6BattlePower(sceneId,selfId,x303006_TeamInfoA_Power[sceneId])
	elseif nSelfCamp == 6 then
		SendPVP6v6BattlePower(sceneId,selfId,x303006_TeamInfoB_Power[sceneId])
	end
end

---------------------------------------------------------------------------------------------------
--通知相关阵营的玩家,己方士气值改变
---------------------------------------------------------------------------------------------------
function x303006_SyncPowerToPlayer(sceneId,nCampFlag)
	
	--检查阵营
	if nCampFlag ~= 5 and nCampFlag ~= 6 then
		return
	end
	
	--设置要发送的士气值
	local nPower = 0
	if nCampFlag == 5 then nPower = x303006_TeamInfoA_Power[sceneId] end
	if nCampFlag == 6 then nPower = x303006_TeamInfoB_Power[sceneId] end
	
	--遍历并且过滤相关玩家
	local humancount = GetScenePlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetScenePlayerObjId(sceneId, i);
		if IsPlayerStateNormal( sceneId,humanId ) == 1 then
			
			--事件1:每五秒钟给五点战场货币
			local nSelfCamp = GetCurCamp(sceneId,humanId)
			if nCampFlag == nSelfCamp then
				SendPVP6v6BattlePower(sceneId,humanId,nPower)
			end
		end
	end
end

---------------------------------------------------------------------------------------------------
--重置采集点
---------------------------------------------------------------------------------------------------
function x303006_ResetAllGrowpoint( sceneId )
	
	WriteLog(1,format("P6BL:x303006_ResetAllGrowpoint 0 sceneId=%d",sceneId))
	
	local n = getn(x303006_g_GrowPointPosList)
	if n <= 0 then
		return
	end
	
	WriteLog(1,format("P6BL:x303006_ResetAllGrowpoint 1 sceneId=%d",sceneId))
	
	local nIdx = random(1,n)
	local x = x303006_g_GrowPointPosList[nIdx][1]
	local z = x303006_g_GrowPointPosList[nIdx][2]
    
    
    --SetGrowPointIntervalContainer(sceneId,x303006_g_GrowPointType,1000)
    RecycleGrowPointByType(sceneId,x303006_g_GrowPointType,1000)
    SetGrowPointPos(sceneId,x303006_g_GrowPointType,x,z)
    
    --采集点重生
	LuaThisScenceM2Wrold(sceneId,x303006_g_GrowpointRelive,2,1)
    
	WriteLog(1,format("P6BL:x303006_ResetAllGrowpoint 2 sceneId=%d x =%f,z=%f",sceneId,x,z))
end

---------------------------------------------------------------------------------------------------
--采集点事件响应
---------------------------------------------------------------------------------------------------
function x303006_OnGrowpointEvent_CB(sceneId,selfId,growpointType)
	
	local name = GetName(sceneId,selfId)
	WriteLog(1,format("P6BL:x303006_OnGrowpointEvent_CB step=0 sceneId=%d,name=%s",sceneId,name))
	
	--检查是否是PVP6v6竞技场
    local nBattleScene = x303006_GetBattleSceneType( sceneId )
    if  nBattleScene <= 0 then
        return 0
    end
    
    WriteLog(1,format("P6BL:x303006_OnGrowpointEvent_CB step=1 sceneId=%d,name=%s",sceneId,name))
    
    --检查场景是否有效
    local nBattleSceneValid = x303006_IsBattleSceneValid(sceneId)
    if nBattleSceneValid ~= 1 then
    	return 0
    end
    
    WriteLog(1,format("P6BL:x303006_OnGrowpointEvent_CB step=2 sceneId=%d,name=%s",sceneId,name))
    
	--如果开始关闭
	local leaveFlag = x303006_SceneInfo[sceneId].ISCLOSING
	if leaveFlag > 0 then
		return 0
	end
	
	WriteLog(1,format("P6BL:x303006_OnGrowpointEvent_CB step=3 sceneId=%d,name=%s",sceneId,name))
	
	--如果玩家无效
	if x303006_CheckPlayerValid(sceneId,selfId ) == 0 then
		return 0
	end
	
	WriteLog(1,format("P6BL:x303006_OnGrowpointEvent_CB step=4 sceneId=%d,name=%s",sceneId,name))
	
	--删除生长点
	SetGrowPointIntervalContainer(sceneId,growpointType,-1)
	
	--测试
--	if x303006_g_Test == 1 then
--		return x303006_OnCreateMonster_MF7(sceneId,selfId )
--	end
	
	--设置玩家获得得采集奖励
	local nRandVal = random(1,9)
	if nRandVal >= 1 and nRandVal <= 7  then
		WriteLog(1,format("P6BL:x303006_OnGrowpointEvent_CB step=5 sceneId=%d,name=%s",sceneId,name))
		return x303006_OnGrowpointGiveBuf(sceneId,selfId,nRandVal)
	elseif nRandVal == 8 then
		WriteLog(1,format("P6BL:x303006_OnGrowpointEvent_CB step=6 sceneId=%d,name=%s",sceneId,name))
		return x303006_OnGrowpointGiveBattleMoney(sceneId,selfId)
	elseif nRandVal == 9 then
		WriteLog(1,format("P6BL:x303006_OnGrowpointEvent_CB step=7 sceneId=%d,name=%s",sceneId,name))
		return x303006_OnCreateMonster_MF7(sceneId,selfId )
	end
	
	WriteLog(1,format("P6BL:x303006_OnGrowpointEvent_CB step=8 sceneId=%d,name=%s",sceneId,name))
	return 0
end

---------------------------------------------------------------------------------------------------
--采集点事件给BUF
---------------------------------------------------------------------------------------------------
function x303006_OnGrowpointGiveBuf(sceneId,selfId,bufIdx)
	
	if bufIdx == 1 then 
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,7974,0) 
		x303006_ShowTips_GrowPoint(sceneId,selfId,1,"长生天的力量")
	elseif bufIdx == 2 then
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,7975,0) 
		x303006_ShowTips_GrowPoint(sceneId,selfId,1,"长生天的守护")
	elseif bufIdx == 3 then
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,7976,0) 
		x303006_ShowTips_GrowPoint(sceneId,selfId,1,"长生天的庇护")
	elseif bufIdx == 4 then
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,7977,0) 
		x303006_ShowTips_GrowPoint(sceneId,selfId,1,"长生天的神速")
	elseif bufIdx == 5 then
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,7978,0) 
		x303006_ShowTips_GrowPoint(sceneId,selfId,1,"长生天的匿迹")
	elseif bufIdx == 6 then
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,7979,0) 
		x303006_ShowTips_GrowPoint(sceneId,selfId,1,"长生天的爆发")
	elseif bufIdx == 7 then
		SendSpecificImpactToUnit(sceneId,selfId,selfId,selfId,7980,0) 
		x303006_ShowTips_GrowPoint(sceneId,selfId,1,"长生天的神力")
	end
	
	return 1
end

---------------------------------------------------------------------------------------------------
--采集点事件给Money
---------------------------------------------------------------------------------------------------
function x303006_OnGrowpointGiveBattleMoney(sceneId,selfId)
	x303006_AddBattleMoney(sceneId,selfId,100)
	x303006_ShowTips_GrowPoint(sceneId,selfId,2,100)
	return 1
end

---------------------------------------------------------------------------------------------------
--更新玩家信息,区分阵营
---------------------------------------------------------------------------------------------------
function x303006_UpdateSceneMap_SendPlayerPosToPlayer( sceneId )
	
	local ta = {}
	local tb = {}
	local na = 0
	local nb = 0
	
	--区分两队玩家
	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 and GetHp(sceneId,objId ) > 0 then
        
        	local nCamp = GetCurCamp(sceneId,objId )
        	if nCamp == 5 then
        		
        		local x,z = GetWorldPos(sceneId,objId)
        		na = na + 1
				ta[na] = {}
				ta[na].id = objId
        		ta[na].name = GetName(sceneId,objId)
        		ta[na].x = x
        		ta[na].z = z
        	elseif nCamp == 6 then
        		
        		local x,z = GetWorldPos(sceneId,objId)
        		nb = nb + 1
				tb[nb] = {}
				tb[nb].id = objId
        		tb[nb].name = GetName(sceneId,objId)
        		tb[nb].x = x
        		tb[nb].z = z
        	end
        end
    end
	
	--向两队玩家广播各自队员信息
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 and GetHp(sceneId,objId ) > 0  then
        
        	local nCamp = GetCurCamp(sceneId,objId )
        	if nCamp == 5 then

        		for j,itm in ta do
					if itm.id ~= objId then
	        			SetSceneMapDataFlagToPlayer( sceneId,objId,itm.id,6,itm.name,itm.x,itm.z,-1)
					end
        		end
        		
        	elseif nCamp == 6 then

        		for j,itm in tb do
					if itm.id ~= objId then
	        			SetSceneMapDataFlagToPlayer( sceneId,objId,itm.id,5,itm.name,itm.x,itm.z,-1)
					end
        		end
        	end        	
        
        end
    end	
end

---------------------------------------------------------------------------------------------------
--更新队伍信息
---------------------------------------------------------------------------------------------------
function x303006_updateTeamA( sceneId,selfId,team,teamcount )
	
	--查找活着的玩家,敌方阵营
	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 and GetHp(sceneId,objId ) > 0 and GetDist(sceneId,selfId,objId,20) <= 20 then
        	local nCamp = GetCurCamp(sceneId,objId )
        	if nCamp == 6 then
        		local x,z = GetWorldPos(sceneId,objId)
        		teamcount = teamcount + 1
        		team[teamcount] = {}
        		team[teamcount].id = objId
        		team[teamcount].name = GetName(sceneId,objId)
        		team[teamcount].x = x
        		team[teamcount].z = z
        		team[teamcount].t = 5
        	end
        end
    end
end


---------------------------------------------------------------------------------------------------
--更新队伍信息
---------------------------------------------------------------------------------------------------
function x303006_updateTeamB( sceneId,selfId,team,teamcount )
	
	--查找活着的玩家,敌方阵营
	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 and GetHp(sceneId,objId ) > 0 and GetDist(sceneId,selfId,objId,20) <= 20 then
        	local nCamp = GetCurCamp(sceneId,objId )
        	if nCamp == 5 then
        		local x,z = GetWorldPos(sceneId,objId)
        		teamcount = teamcount + 1
        		team[teamcount] = {}
        		team[teamcount].id = objId
        		team[teamcount].name = GetName(sceneId,objId)
        		team[teamcount].x = x
        		team[teamcount].z = z
        		team[teamcount].t = 6
        	end
        end
    end
end

---------------------------------------------------------------------------------------------------
--更新战况信息给玩家,区分阵营
---------------------------------------------------------------------------------------------------
function x303006_UpdateSceneMap_SendBattleInfoToPlayer( sceneId )

	local BattleInfo = {}
	local BattleInfoCount = 0
	
	local TeamA = {}
	local TeamACount = 0
	
	local TeamB = {}
	local TeamBCount = 0

	--第一批BOSS处理
	for i,item in x303006_BossLftID1[sceneId] do
		if IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0  then
			
			BattleInfoCount = BattleInfoCount + 1
			BattleInfo[BattleInfoCount] = {}
			BattleInfo[BattleInfoCount].id = item
			BattleInfo[BattleInfoCount].name = GetName(sceneId,item)
			local x,z = GetWorldPos(sceneId,item)
			BattleInfo[BattleInfoCount].x = x
			BattleInfo[BattleInfoCount].z = z
			if i  == 1 then				
				BattleInfo[BattleInfoCount].camp = 5
				x303006_updateTeamA(sceneId,item,TeamB,TeamBCount)
			else
				BattleInfo[BattleInfoCount].camp = 6
				x303006_updateTeamB(sceneId,item,TeamA,TeamACount)
			end	
			BattleInfo[BattleInfoCount].type = 0
		end
	end
	
	for i,item in x303006_BossMidID1[sceneId] do
		if IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0  then
			
			BattleInfoCount = BattleInfoCount + 1
			BattleInfo[BattleInfoCount] = {}
			BattleInfo[BattleInfoCount].id = item
			BattleInfo[BattleInfoCount].name = GetName(sceneId,item)
			local x,z = GetWorldPos(sceneId,item)
			BattleInfo[BattleInfoCount].x = x
			BattleInfo[BattleInfoCount].z = z
			if i  == 1 then
				BattleInfo[BattleInfoCount].camp = 5
				x303006_updateTeamA(sceneId,item,TeamB,TeamBCount)
			else
				BattleInfo[BattleInfoCount].camp = 6
				x303006_updateTeamB(sceneId,item,TeamA,TeamACount)
			end
			BattleInfo[BattleInfoCount].type = 0
		end
	end
	
	for i,item in x303006_BossRhtID1[sceneId] do
		if IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0  then
			
			BattleInfoCount = BattleInfoCount + 1
			BattleInfo[BattleInfoCount] = {}
			BattleInfo[BattleInfoCount].id = item
			BattleInfo[BattleInfoCount].name = GetName(sceneId,item)
			local x,z = GetWorldPos(sceneId,item)
			BattleInfo[BattleInfoCount].x = x
			BattleInfo[BattleInfoCount].z = z
			if i  == 1 then
				BattleInfo[BattleInfoCount].camp = 5
				x303006_updateTeamA(sceneId,item,TeamB,TeamBCount)
			else
				BattleInfo[BattleInfoCount].camp = 6
				x303006_updateTeamB(sceneId,item,TeamA,TeamACount)
			end
			BattleInfo[BattleInfoCount].type = 0
		end
	end
	
	--第二批BOSS处理
	for i,item in x303006_BossLftID2[sceneId] do
		if IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0  then
			
			BattleInfoCount = BattleInfoCount + 1
			BattleInfo[BattleInfoCount] = {}
			BattleInfo[BattleInfoCount].id = item
			BattleInfo[BattleInfoCount].name = GetName(sceneId,item)
			local x,z = GetWorldPos(sceneId,item)
			BattleInfo[BattleInfoCount].x = x
			BattleInfo[BattleInfoCount].z = z
			if i  == 1 then
				BattleInfo[BattleInfoCount].camp = 5
				x303006_updateTeamA(sceneId,item,TeamB,TeamBCount)
			else
				BattleInfo[BattleInfoCount].camp = 6
				x303006_updateTeamB(sceneId,item,TeamA,TeamACount)
			end
			BattleInfo[BattleInfoCount].type = 0
		end
	end
	
	for i,item in x303006_BossMidID2[sceneId] do
		if IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0  then
			
			BattleInfoCount = BattleInfoCount + 1
			BattleInfo[BattleInfoCount] = {}
			BattleInfo[BattleInfoCount].id = item
			BattleInfo[BattleInfoCount].name = GetName(sceneId,item)
			local x,z = GetWorldPos(sceneId,item)
			BattleInfo[BattleInfoCount].x = x
			BattleInfo[BattleInfoCount].z = z
			if i  == 1 then
				BattleInfo[BattleInfoCount].camp = 5
				x303006_updateTeamA(sceneId,item,TeamB,TeamBCount)
			else
				BattleInfo[BattleInfoCount].camp = 6
				x303006_updateTeamB(sceneId,item,TeamA,TeamACount)
			end
			BattleInfo[BattleInfoCount].type = 0
		end
	end
	
	for i,item in x303006_BossRhtID2[sceneId] do
		if IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0  then
			
			BattleInfoCount = BattleInfoCount + 1
			BattleInfo[BattleInfoCount] = {}
			BattleInfo[BattleInfoCount].id = item
			BattleInfo[BattleInfoCount].name = GetName(sceneId,item)
			local x,z = GetWorldPos(sceneId,item)
			BattleInfo[BattleInfoCount].x = x
			BattleInfo[BattleInfoCount].z = z
			if i  == 1 then
				BattleInfo[BattleInfoCount].camp = 5
				x303006_updateTeamA(sceneId,item,TeamB,TeamBCount)
			else
				BattleInfo[BattleInfoCount].camp = 6
				x303006_updateTeamB(sceneId,item,TeamA,TeamACount)
			end
			BattleInfo[BattleInfoCount].type = 0
		end
	end
	
	--第三批BOSS处理
	for i,item in x303006_BossLftID3[sceneId] do
		if IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0  then
			
			BattleInfoCount = BattleInfoCount + 1
			BattleInfo[BattleInfoCount] = {}
			BattleInfo[BattleInfoCount].id = item
			BattleInfo[BattleInfoCount].name = GetName(sceneId,item)
			local x,z = GetWorldPos(sceneId,item)
			BattleInfo[BattleInfoCount].x = x
			BattleInfo[BattleInfoCount].z = z
			if i  == 1 then
				BattleInfo[BattleInfoCount].camp = 5
				x303006_updateTeamA(sceneId,item,TeamB,TeamBCount)
			else
				BattleInfo[BattleInfoCount].camp = 6
				x303006_updateTeamB(sceneId,item,TeamA,TeamACount)
			end	
			BattleInfo[BattleInfoCount].type = 0
		end
	end
	
	for i,item in x303006_BossMidID3[sceneId] do
		if IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0  then
			
			BattleInfoCount = BattleInfoCount + 1
			BattleInfo[BattleInfoCount] = {}
			BattleInfo[BattleInfoCount].id = item
			BattleInfo[BattleInfoCount].name = GetName(sceneId,item)
			local x,z = GetWorldPos(sceneId,item)
			BattleInfo[BattleInfoCount].x = x
			BattleInfo[BattleInfoCount].z = z
			if i  == 1 then
				BattleInfo[BattleInfoCount].camp = 5
				x303006_updateTeamA(sceneId,item,TeamB,TeamBCount)
			else
				BattleInfo[BattleInfoCount].camp = 6
				x303006_updateTeamB(sceneId,item,TeamA,TeamACount)
			end
			BattleInfo[BattleInfoCount].type = 0
		end
	end
	
	for i,item in x303006_BossRhtID3[sceneId] do
		if IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0  then
			
			BattleInfoCount = BattleInfoCount + 1
			BattleInfo[BattleInfoCount] = {}
			BattleInfo[BattleInfoCount].id = item
			BattleInfo[BattleInfoCount].name = GetName(sceneId,item)
			local x,z = GetWorldPos(sceneId,item)
			BattleInfo[BattleInfoCount].x = x
			BattleInfo[BattleInfoCount].z = z
			if i  == 1 then
				BattleInfo[BattleInfoCount].camp = 5
				x303006_updateTeamA(sceneId,item,TeamB,TeamBCount)
			else
				BattleInfo[BattleInfoCount].camp = 6
				x303006_updateTeamB(sceneId,item,TeamA,TeamACount)
			end	
			BattleInfo[BattleInfoCount].type = 0
		end
	end
	
	--第五批BOSS处理
	for i,item in x303006_BossMidID5[sceneId] do
		if IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0  then
			
			BattleInfoCount = BattleInfoCount + 1
			BattleInfo[BattleInfoCount] = {}
			BattleInfo[BattleInfoCount].id = item
			BattleInfo[BattleInfoCount].name = GetName(sceneId,item)
			local x,z = GetWorldPos(sceneId,item)
			BattleInfo[BattleInfoCount].x = x
			BattleInfo[BattleInfoCount].z = z
			if i  < 3 then
				BattleInfo[BattleInfoCount].camp = 5
				x303006_updateTeamA(sceneId,item,TeamB,TeamBCount)
			else
				BattleInfo[BattleInfoCount].camp = 6
				x303006_updateTeamB(sceneId,item,TeamA,TeamACount)
			end
			BattleInfo[BattleInfoCount].type = 0
		end
	end
	
	--第六批BOSS处理
	for i,item in x303006_BossMidID6[sceneId] do
		if IsObjValid(sceneId,item) == 1 and GetHp(sceneId,item) > 0  then
			
			BattleInfoCount = BattleInfoCount + 1
			BattleInfo[BattleInfoCount] = {}
			BattleInfo[BattleInfoCount].id = item
			BattleInfo[BattleInfoCount].name = GetName(sceneId,item)
			local x,z = GetWorldPos(sceneId,item)
			BattleInfo[BattleInfoCount].x = x
			BattleInfo[BattleInfoCount].z = z
			if i == 1 then
				BattleInfo[BattleInfoCount].camp = 5
				x303006_updateTeamA(sceneId,item,TeamB,TeamBCount)
			else
				BattleInfo[BattleInfoCount].camp = 6
				x303006_updateTeamB(sceneId,item,TeamA,TeamACount)
			end
			BattleInfo[BattleInfoCount].type = 1
		end
	end

	local nJT = -1
	local nJD = -1
	--区分两队玩家
	local nHumanCount = GetScenePlayerCount( sceneId )
    local i = 0
    for i = 0,nHumanCount-1 do
        local objId = GetScenePlayerObjId( sceneId,i)
        if objId >= 0 and IsPlayerStateNormal(sceneId,objId) == 1 and GetHp(sceneId,objId ) > 0 then
        
        	--发送建筑相关信息
			for j ,item in BattleInfo do
				if item.camp == 5 then
					nJT = 2
					nJD = 4
				else
					nJT = 1
					nJD = 3
				end

				if item.type == 0 then
					SetSceneMapDataFlagToPlayer( sceneId,objId,item.id,nJT,item.name,item.x,item.z,-1)
				else
					SetSceneMapDataFlagToPlayer( sceneId,objId,item.id,nJD,item.name,item.x,item.z,-1)
				end
			end
			
			--发送塔附近相关玩家信息
			local camp = GetCurCamp(sceneId,objId )
			local tm = nil
			if camp == 5 then
				tm = TeamB
			elseif camp == 6 then
				tm = TeamA				
			end
			
			--如果不为空
			if tm then
				for j,item in tm do
					SetSceneMapDataFlagToPlayer( sceneId,objId,item.id,item.t,item.name,item.x,item.z,-1)
				end
			end
			
        end
	end	
end

---------------------------------------------------------------------------------------------------
--更新场景地图显示
---------------------------------------------------------------------------------------------------
function x303006_UpdateSceneMap( sceneId )
	
	--清空当前地图信息显示
	ClearSceneMapDataFlag(sceneId)	
	
	--更新玩家信息
	x303006_UpdateSceneMap_SendPlayerPosToPlayer( sceneId )
	
	--更新建筑以及箭塔
	x303006_UpdateSceneMap_SendBattleInfoToPlayer( sceneId )
	
	x303006_UpdateBattleMap(sceneId)
end

---------------------------------------------------------------------------------
-- 更新小地图
function x303006_UpdateBattleMap( sceneId )
	local player = x303006_g_Player[sceneId]
	local ta = x303006_g_Ta[sceneId]
	
	-- 得到玩家最新状态
	local humancount = GetScenePlayerCount(sceneId)
	for	i = 0, humancount - 1 do
		player[i+1].id = GetScenePlayerObjId(sceneId, i)
		if player[i+1].id ~= -1 and IsPlayerStateNormal(sceneId,player[i+1].id) ~= 1 then
			player[i+1].id = -1
		end
		if player[i+1].id ~= -1 then
			local hp = GetHp(sceneId,player[i+1].id )
			if hp <= 0 then
				player[i+1].id = -1
			else
				player[i+1].hp = hp
			end
		end
		if player[i+1].id ~= -1 then
			player[i+1].camp = GetCurCamp(sceneId, player[i+1].id)
			player[i+1].x, player[i+1].z = GetWorldPos(sceneId, player[i+1].id)
			
			--print ("player:", player[i+1].x, player[i+1].z)
		end
	end
	
	-- 得到塔最新状态
	ta[1].id, ta[1].hp	= x303006_BossLftID1_Attack[sceneId][1], x303006_BossLftID1_HP[sceneId][1]
	ta[2].id, ta[2].hp	= x303006_BossLftID1_Attack[sceneId][2], x303006_BossLftID1_HP[sceneId][2]
	ta[3].id, ta[3].hp	= x303006_BossMidID1_Attack[sceneId][1], x303006_BossMidID1_HP[sceneId][1]
	ta[4].id, ta[4].hp	= x303006_BossMidID1_Attack[sceneId][2], x303006_BossMidID1_HP[sceneId][2]
	ta[5].id, ta[5].hp	= x303006_BossRhtID1_Attack[sceneId][1], x303006_BossRhtID1_HP[sceneId][1]
	ta[6].id, ta[6].hp	= x303006_BossRhtID1_Attack[sceneId][2], x303006_BossRhtID1_HP[sceneId][2]
	ta[7].id, ta[7].hp	= x303006_BossLftID2_Attack[sceneId][1], x303006_BossLftID2_HP[sceneId][1]
	ta[8].id, ta[8].hp	= x303006_BossLftID2_Attack[sceneId][2], x303006_BossLftID2_HP[sceneId][2]
	ta[9].id, ta[9].hp	= x303006_BossMidID2_Attack[sceneId][1], x303006_BossMidID2_HP[sceneId][1]
	ta[10].id, ta[10].hp= x303006_BossMidID2_Attack[sceneId][2], x303006_BossMidID2_HP[sceneId][2]
	ta[11].id, ta[11].hp= x303006_BossRhtID2_Attack[sceneId][1], x303006_BossRhtID2_HP[sceneId][1]
	ta[12].id, ta[12].hp= x303006_BossRhtID2_Attack[sceneId][2], x303006_BossRhtID2_HP[sceneId][2]
	ta[13].id, ta[13].hp= x303006_BossLftID3_Attack[sceneId][1], x303006_BossLftID3_HP[sceneId][1]
	ta[14].id, ta[14].hp= x303006_BossLftID3_Attack[sceneId][2], x303006_BossLftID3_HP[sceneId][2]
	ta[15].id, ta[15].hp= x303006_BossMidID3_Attack[sceneId][1], x303006_BossMidID3_HP[sceneId][1]
	ta[16].id, ta[16].hp= x303006_BossMidID3_Attack[sceneId][2], x303006_BossMidID3_HP[sceneId][2]
	ta[17].id, ta[17].hp= x303006_BossRhtID3_Attack[sceneId][1], x303006_BossRhtID3_HP[sceneId][1]
	ta[18].id, ta[18].hp= x303006_BossRhtID3_Attack[sceneId][2], x303006_BossRhtID3_HP[sceneId][2]
	ta[19].id, ta[19].hp= x303006_BossLftID4_Attack[sceneId][1], x303006_BossLftID4_HP[sceneId][1]
	ta[20].id, ta[20].hp= x303006_BossLftID4_Attack[sceneId][2], x303006_BossLftID4_HP[sceneId][2]
	ta[21].id, ta[21].hp= x303006_BossMidID4_Attack[sceneId][1], x303006_BossMidID4_HP[sceneId][1]
	ta[22].id, ta[22].hp= x303006_BossMidID4_Attack[sceneId][2], x303006_BossMidID4_HP[sceneId][2]
	ta[23].id, ta[23].hp= x303006_BossMidID4_Attack[sceneId][3], x303006_BossMidID4_HP[sceneId][3]
	ta[24].id, ta[24].hp= x303006_BossMidID4_Attack[sceneId][4], x303006_BossMidID4_HP[sceneId][4]
	ta[25].id, ta[25].hp= x303006_BossRhtID4_Attack[sceneId][1], x303006_BossRhtID4_HP[sceneId][1]
	ta[26].id, ta[26].hp= x303006_BossRhtID4_Attack[sceneId][2], x303006_BossRhtID4_HP[sceneId][2]
	ta[27].id, ta[27].hp= x303006_BossMidID5_Attack[sceneId][1], x303006_BossMidID5_HP[sceneId][1]
	ta[28].id, ta[28].hp= x303006_BossMidID5_Attack[sceneId][2], x303006_BossMidID5_HP[sceneId][2]
	ta[29].id, ta[29].hp= x303006_BossMidID5_Attack[sceneId][3], x303006_BossMidID5_HP[sceneId][3]
	ta[30].id, ta[30].hp= x303006_BossMidID5_Attack[sceneId][4], x303006_BossMidID5_HP[sceneId][4]
	-- 得到大营最新状态
	ta[31].id, ta[31].hp= x303006_BossMidID6[sceneId][1], x303006_BossMidID6_HP[sceneId][1]
	ta[32].id, ta[32].hp= x303006_BossMidID6[sceneId][2], x303006_BossMidID6_HP[sceneId][2]
													
	for i, item in ta do
		if item.id ~= -1 and IsObjValid(sceneId,item.id) ~= 1 then
			item.id = -1
		end
		if item.id ~= -1 and item.hp <= 0 then
			--local hp = GetHp(sceneId,item.id )
			--if hp <= 0 then
				item.id = -1
			--else
			--	item.hp = hp
			--end
		end
		if item.id ~= -1 then
			item.camp = GetMonsterCamp(sceneId,item.id)
			item.x, item.z = GetWorldPos(sceneId, item.id)
			
			--print ("ta:", item.x, item.z)
		end
	end
	
	-- 更新
	local humancount = GetScenePlayerCount(sceneId)
	for	i = 0, humancount - 1 do
		local id = GetScenePlayerObjId(sceneId, i)
		
		if id ~= -1 then
			x303006_UpdateBattleMapToPlayer( sceneId, player[i+1], player, ta )
		end
	end
	
	-- 结束更新
	for	i = 1, 12 do
		player[i].oldid = player[i].id
		player[i].oldhp = player[i].hp
		player[i].oldx, player[i].oldz = player[i].x, player[i].z
	end
	for i, item in ta do
		item.oldid = item.id
		item.oldhp = item.hp
	end
	
	x303006_g_Texiao[sceneId] = x303006_g_Texiao[sceneId]+1
end

x303006_g_UpdateBattleMap_Hide				= 0	-- 0 删除
x303006_g_UpdateBattleMap_Icon				= 1	-- 1 更新图标
x303006_g_UpdateBattleMap_Pos				= 2	-- 2 更新位置
x303006_g_UpdateBattleMap_All				= 3 -- 3 都更新
x303006_g_UpdateBattleMap_No				= 4	-- 4 不变
x303006_g_UpdateBattleMap_Ani				= 5	-- 5 显示被攻击动画

-- 图标
x303006_g_UpdateBattleMap_Pic_Self			= 1	-- 自己的图标
x303006_g_UpdateBattleMap_Pic_Team			= 2	-- 己方的玩家图标
x303006_g_UpdateBattleMap_Pic_OtherTeam		= 3	-- 敌方的玩家图标
x303006_g_UpdateBattleMap_Pic_Ta			= 4	-- 己方的塔图标
x303006_g_UpdateBattleMap_Pic_OtherTa		= 5	-- 敌方的塔图标
x303006_g_UpdateBattleMap_Pic_Daying		= 6	-- 己方的大营图标
x303006_g_UpdateBattleMap_Pic_OtherDaying	= 7	-- 敌方的大营图标

function x303006_UpdateBattleMapToPlayer( sceneId, self, player, ta )
	
	local count = 1
	
	if self.id ~= -1 then
		count = x303006_UpdateBattleMapOtherPlayerInfoToPlayer( sceneId, self, player, ta, count )
		
		count = x303006_UpdateBattleMapTaInfoToPlayer( sceneId, self, ta, count )
	end
end

function x303006_UpdateBattleMapOtherPlayerInfoToPlayer( sceneId, self, player, ta, count )
	local map_size = 256
	local pic, bshow, x, z, xx, zz
	
	for i = 1, 12 do
	
		if player[i].id ~= -1 or player[i].oldid ~= -1 then
			bshow = 0
			if player[i].id ~= -1 and IsHaveSpecificImpact( sceneId, player[i].id, 7978 ) <= 0 then -- 显示
			
				if self.camp == player[i].camp then
					bshow = 1
				else 
					-- 判断是否在人附近
					for j = 1, 12 do
						if player[j].id ~= -1 and player[i].id ~= player[j].id and player[j].camp == self.camp then
							xx = player[i].x - player[j].x
							zz = player[i].z - player[j].z
							if xx*xx + zz*zz <= 25*25 then
								bshow = 1
								break
							end
						end
					end
					-- 判断是否在塔附近
					if bshow ~= 1 then
						for k, item in ta do
							if item.id ~= -1 and IsObjValid(sceneId,item.id) == 1 and item.hp > 0 then
								if self.camp == item.camp or self.camp == item.camp-23 then
									xx = item.x - player[i].x
									zz = item.z - player[i].z
									if xx*xx + zz*zz <= 25*25 then
										bshow = 1
										break
									end
								end
							end
						end
					end
				end
			end	
		
			if bshow == 1 then
				if self.id == player[i].id then
					pic = x303006_g_UpdateBattleMap_Pic_Self
				elseif self.camp == player[i].camp then
					pic = x303006_g_UpdateBattleMap_Pic_Team
				else
					pic = x303006_g_UpdateBattleMap_Pic_OtherTeam
				end
			
				x = player[i].x/map_size
				z = player[i].z/map_size
				if player[i].oldid == -1 then
					SendBattleMapObj(sceneId, self.id, count, x303006_g_UpdateBattleMap_All, pic, x, z)
				else
					if player[i].hp >= player[i].oldhp then
						if mod(x303006_g_Texiao[sceneId], 3) == 1 then
							SendBattleMapObj(sceneId, self.id, count+160, x303006_g_UpdateBattleMap_Pos, 0, x, z)
						else
							SendBattleMapObj(sceneId, self.id, count, x303006_g_UpdateBattleMap_Pos, 0, x, z)
						end
					else
						SendBattleMapObj(sceneId, self.id, count+80, x303006_g_UpdateBattleMap_Pos, 0, x, z)
					end
				end
			else
				SendBattleMapObj(sceneId, self.id, count, x303006_g_UpdateBattleMap_Hide, 0, -1, -1)
			end
		end
		count = count+1
	end
	return count		
end

function x303006_UpdateBattleMapTaInfoToPlayer( sceneId, self, ta, count )
	local map_size = 256
	local pic, x, z
	
	for i, item in ta do
		
		--if item.id ~= -1 or item.oldid ~= -1 then
			if item.id ~= -1 then
				--if item.oldid == -1 then
				
		--print ("joidjsoijdfois::::", item.id, item.oldid, item.camp, item.x, item.z)
					if i < 31 then
						if self.camp == item.camp or self.camp == item.camp-23 then
							pic = x303006_g_UpdateBattleMap_Pic_Ta
						else
							pic = x303006_g_UpdateBattleMap_Pic_OtherTa
						end
					else
						if self.camp == 5 then
							if i == 31 then
								pic = x303006_g_UpdateBattleMap_Pic_Daying
							else
								pic = x303006_g_UpdateBattleMap_Pic_OtherDaying
							end
						else
							if i == 31 then
								pic = x303006_g_UpdateBattleMap_Pic_OtherDaying
							else
								pic = x303006_g_UpdateBattleMap_Pic_Daying
							end
						end
					end

					x = item.x/map_size
					z = item.z/map_size
					
					if item.hp >= item.oldhp then
						if mod(x303006_g_Texiao[sceneId], 3) == 1 then
							SendBattleMapObj(sceneId, self.id, count+160, x303006_g_UpdateBattleMap_All, pic, x, z)
						else
							SendBattleMapObj(sceneId, self.id, count, x303006_g_UpdateBattleMap_All, pic, x, z)
						end
					else
						SendBattleMapObj(sceneId, self.id, count+80, x303006_g_UpdateBattleMap_All, pic, x, z)
					end
				--else
				--	SendBattleMapObj(sceneId, self.id, count, x303006_g_UpdateBattleMap_Pos, 0, x, z)
				--end
			elseif item.oldid ~= -1 then
				SendBattleMapObj(sceneId, self.id, count, x303006_g_UpdateBattleMap_Hide, 0, -1, -1)
			end
		--end
		count = count+1
	end
	
	return count
end