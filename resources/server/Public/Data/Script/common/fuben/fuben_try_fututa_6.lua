---------------------------------------------------
-- File: 700213_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700213_CSP_FUBENTYPE				= 	0
x700213_CSP_SCRIPTID				=	1
x700213_CSP_TICKCOUNT				= 	2
x700213_CSP_FROMSCENEID				= 	3
x700213_CSP_ISCLOSING				= 	4
x700213_CSP_LEAVECOUNTDOWN			= 	5
x700213_CSP_TEAMID					=	6
x700213_CSP_BACKSCENEX       		=   7
x700213_CSP_BACKSCENEZ      		=   8
x700213_CSP_FUBENLEVEL			=	9
x700213_CSP_KILLCOUNT				=	20

x700213_CSP_ARRAYID					=   21
x700213_CSP_COUNT					=	22
x700213_CSP_TOTALCOUNT				=	23	
x700213_CSP_TIME_COUNT				=	24
x700213_CSP_TIME_DOWN				=	25
x700213_CSP_TIME_BACKUP				=	26
x700213_CSP_TIME_BISHEN				=	27
x700213_CSP_COUNTDOWN				=	28
x700213_CSP_NPCID					=   29

x700213_CSP_MONSTER_COUNT			=	30
x700213_CSP_MONSTERCONVCOUNT		=	31
x700213_CSP_NKILLMONSTER			=	32
x700213_CSP_MONSTERCOUNT            =   33      --当前组别ID
x700213_CSP_TOTALBIAN				=	34
x700213_CSP_TOTALDISAPEAR			=	35
x700213_CSP_BOSSLOGIC				=	36
x700213_CSP_BONUSLOGIC				=	37
x700213_CSP_BOSSID					=	38
x700213_CSP_GROUP					=	39

x700213_CSP_START					=	40




x700213_CSP_GUID_START              =   248



------------------------Scene System Setting -----------------------------------

x700213_g_ScriptId 					= 700213


--------------------------- special for this fuben ---------------------
--NPC引领时说话的内容
x700213_g_NpcText					=	{
											"冰之灵，多疑之灵，让人失去信念！", 
											"巨之灵，慢之根，自大让人迷失！", 
											"地之灵，痴之源泉，蒙蔽人的慧心！", 
											"聚之灵，是嗔念之灵，一念地狱，一念天堂！", 
											"不要被你的欲望所困！", 
											"炎之灵，是贪欲之火！三大戒之首！", 
											"坚持住，不能倒下！", 
											"战胜最后的心魔，小心了！", 
										}

x700213_g_NeedKillMonster			=  65	

------------------------- list -----------------------------------------

x700213_g_SubmitNPC                 =   { type =25033,guid= 150548,x = 32, z=34, facedir = 0, title = "" }


--创建时间
x700213_g_Timer0                    = 1
x700213_g_Timer1                    = 2
x700213_g_Timer2                    = 3 --boss
x700213_g_Timer3                    = 4
x700213_g_Timer4                    = 4
x700213_g_Timer5                    = 3 --boss
x700213_g_Timer6                    = 4
x700213_g_Timer7                    = 0

--变身时间
x700213_g_Timer0_r                  = 4
x700213_g_Timer1_r                  = 4
x700213_g_Timer2_r                  = 12    --boss
x700213_g_Timer3_r                  = 6
x700213_g_Timer4_r                  = 6
x700213_g_Timer5_r                  = 18    --boss
x700213_g_Timer6_r                  = 6
x700213_g_Timer7_r                  = 12

--每个刷怪点的倒计时计数
x700213_g_CountDown					= 2

--BOSS类型
x700213_g_BossCreate				=	{
                                            {levelmin =40, levelmax=100, name ="虚空总boss",   type= 27781,   x=31, z=31, r=0,  ai=18, aiscript=598, facedir = 0, title = "",bonus=0},  
                                            

										}

x700213_g_MonsterCreate            =    {

                                            --变身前
                                            {levelmin =40, levelmax=100, name ="小怪11",   type= 27773,   x=12, z=16, r=1,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 0,group=0,time=18,bonus=0},
                                           
                                            {levelmin =40, levelmax=100, name ="小怪12",   type= 27775,   x=12, z=16, r=1,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 0,group=1,time=18,bonus=0},
                                           
                                            
                                            {levelmin =40, levelmax=100, name ="小怪13",   type= 27777,   x=12, z=16, r=1,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 0,group=2,time=18,bonus=0},
                                           
                                            
                                            {levelmin =40, levelmax=100, name ="小怪21",   type= 27773,   x=12, z=31, r=3,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 1,group=0,time=17,bonus=0},
                                           
                                                                                                         
                                            {levelmin =40, levelmax=100, name ="小怪22",   type= 27775,   x=12, z=31, r=3,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 1,group=1,time=17,bonus=0},
                                           
                                                                                                         
                                            {levelmin =40, levelmax=100, name ="小怪23",   type= 27777,   x=12, z=31, r=3,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 1,group=2,time=17,bonus=0},
                                            

                                            {levelmin =40, levelmax=100, name ="虚空boss1",   type= 27779,   x=12, z=52, r=0,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 2,group=0,time=16,bonus=0},
                                            

                                            {levelmin =40, levelmax=100, name ="小怪31",   type= 27773,   x=28, z=49, r=2,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 3,group=0,time=15,bonus=0},
                                           
                                                                                                                                                                                                     
                                            {levelmin =40, levelmax=100, name ="小怪32",   type= 27775,   x=28, z=49, r=2,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 3,group=1,time=15,bonus=0},
                                           
                                                                                                                                                                                                   
                                            {levelmin =40, levelmax=100, name ="小怪33",   type= 27777,   x=28, z=49, r=2,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 3,group=2,time=15,bonus=0},
                                            
                                                                                                                                                                                                  
                                            {levelmin =40, levelmax=100, name ="小怪41",   type= 27773,   x=40, z=17, r=4,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 7,group=0,time=14,bonus=0},
                                            
                                                                                                                                                                                                  
                                            {levelmin =40, levelmax=100, name ="小怪42",   type= 27775,   x=40, z=17, r=4,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 7,group=1,time=14,bonus=0},
                                           
                                            {levelmin =40, levelmax=100, name ="小怪43",   type= 27777,   x=40, z=17, r=4,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 7,group=2,time=14,bonus=0},
                                            
                                                                                                                                                                                                   
                                            {levelmin =40, levelmax=100, name ="小怪51",   type= 27773,   x=50, z=14, r=4,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 6,group=0,time=13,bonus=0},
                                            
                                                                                                                                                                                                     
                                            {levelmin =40, levelmax=100, name ="小怪52",   type= 27775,   x=50, z=14, r=4,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 6,group=1,time=13,bonus=0},
                                            
                                                                                                                                                                                                    
                                            {levelmin =40, levelmax=100, name ="小怪53",   type= 27777,   x=50, z=14, r=4,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 6,group=2,time=13,bonus=0},
                                            
                                            {levelmin =40, levelmax=100, name ="虚空boss2",   type= 27780,   x=50, z=33, r=0,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 5,group=0,time=12,bonus=0},
                                            
                                            {levelmin =40, levelmax=100, name ="小怪61",   type= 27773,   x=50, z=50, r=2,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 4,group=0,time=11,bonus=0},
                                                                                                                                                                                     
                                            {levelmin =40, levelmax=100, name ="小怪62",   type= 27775,   x=50, z=50, r=2,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 4,group=1,time=11,bonus=0},
                                                                                                                                                                                                                 
                                            {levelmin =40, levelmax=100, name ="小怪63",   type= 27777,   x=50, z=50, r=2,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 4,group=2,time=11,bonus=0},
                                           

											--奖励怪
                                            {levelmin =40, levelmax=100, name ="小怪2变身",   type= 27774,   x=31, z=17, r=2,  ai=7, aiscript=-1, facedir = 0, title = "", flag=9,group=0,time=-1,bonus=0},
                                          

                                            --变身后
                                            {levelmin =40, levelmax=100, name ="小怪1变身",   type= 27774,   x=17, z=17, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 10,group=0,time=-1,bonus=0},
                                                  
                                            {levelmin =40, levelmax=100, name ="小怪1变身",   type= 27774,   x=17, z=31, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 11,group=0,time=-1,bonus=0},
                                              
                                            {levelmin =40, levelmax=100, name ="小怪1变身",   type= 27774,   x=17, z=45, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 12,group=0,time=-1,bonus=0},
                                                     
                                            {levelmin =40, levelmax=100, name ="小怪1变身",   type= 27774,   x=31, z=45, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 13,group=0,time=-1,bonus=0},
                                           
                                            {levelmin =40, levelmax=100, name ="小怪1变身",   type= 27774,   x=31, z=31, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 17,group=0,time=-1,bonus=0},
                                                   
                                            {levelmin =40, levelmax=100, name ="小怪1变身",   type= 27774,   x=31, z=17, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 16,group=0,time=-1,bonus=0},
                                             
                                            {levelmin =40, levelmax=100, name ="小怪1变身",   type= 27774,   x=46, z=17, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 15,group=0,time=-1,bonus=0},
                                                 
                                            {levelmin =40, levelmax=100, name ="小怪1变身",   type= 27774,   x=46, z=31, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 14,group=0,time=-1,bonus=0},
                                           
                                        }

x700213_g_NPCType					= 	25033

x700213_g_NpcGUID                   =   {
                                            {guid = 150000, name = "指灵禅师"},
                                        }

x700213_g_NpcCreate					=	{
											{	hash=1, type=x700213_g_NPCType,	x=15,	z=15,	ai=3, aiscript=-1,facedir = 0, title = "",objid = 150000,campid = -1 },
										}
	


-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700213_ProcEventEntry(sceneId, selfId, NPCId)
end


-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700213_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	SetFubenData_Param(sceneId, x700213_CSP_ARRAYID, -1);	

	x700213_CreateNPC( sceneId);
		
end



-----------------------------------------------------------
--*********************************************************
--EnterTick  :  副本心跳
--*********************************************************
-----------------------------------------------------------
function x700213_EnterTick(sceneId, nowTickCount)

	if nowTickCount >= 6 then
	    x700213_UpdateMonsterParam( sceneId )
	end
end


---------------------------------------------------------------------------------------------------
--创建BOSS
---------------------------------------------------------------------------------------------------
function x700213_CreateBoss(sceneId)

	local copyscenelevel = GetFubenData_Param(sceneId, x700213_CSP_FUBENLEVEL ) ;

	for i, item in x700213_g_BossCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		    local bossid = 0;
			if item.title~="" then
				bossid = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700213_g_ScriptId, -1, 21, -1, item.facedir, "", item.title)
			else
				bossid = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700213_g_ScriptId, -1, 21, -1, item.facedir)
			end
			SetFubenData_Param( sceneId, x700213_CSP_BOSSID, bossid )
		end
	end
end

function x700213_CreateNPC( sceneId)
	for i, item in x700213_g_NpcCreate do
		local NPCID, NPCGUID;
		
		if item.title~="" then
			NPCID, NPCGUID = CreateMonster( sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, item.objid, -1, -1, item.facedir,  "",item.title);
		else
			NPCID, NPCGUID = CreateMonster( sceneId, item.type, item.x, item.z, item.ai, item.aiscript, -1, item.objid, -1, -1, item.facedir);
		end

		SetFubenData_Param( sceneId, x700213_CSP_NPCID, NPCID);
	end
end



---------------------------------------------------------------------------------------------------
--设置怪物数据
---------------------------------------------------------------------------------------------------
function x700213_SetMonsterParam( sceneId, arrayId)
	local patrolId = arrayId - 1
    if arrayId == 0 then
        SetFubenData_Param(sceneId, x700213_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700213_CSP_COUNT,             1                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700213_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN,         x700213_g_Timer0    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BACKUP,       x700213_g_Timer0    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BISHEN,       x700213_g_Timer0_r  );
		SetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN,         x700213_g_CountDown );

		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     3                   );--总数3
    elseif arrayId == 1 then
        SetFubenData_Param(sceneId, x700213_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700213_CSP_COUNT,             2                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700213_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN,         x700213_g_Timer1    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BACKUP,       x700213_g_Timer1    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BISHEN,       x700213_g_Timer1_r  );
        SetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN,         x700213_g_CountDown );
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     6                   );--总数6
		--npc talk
		local id = GetFubenData_Param( sceneId, x700213_CSP_NPCID);
		NpcTalk( sceneId, id, x700213_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, patrolId);
	elseif arrayId == 2 then
        SetFubenData_Param(sceneId, x700213_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700213_CSP_COUNT,             1                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700213_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN,         x700213_g_Timer2    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BACKUP,       x700213_g_Timer2    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BISHEN,       x700213_g_Timer2_r  );
        SetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN,         x700213_g_CountDown );
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     1                   );--总数1
		--npc talk
		local id = GetFubenData_Param( sceneId, x700213_CSP_NPCID);
		NpcTalk( sceneId, id, x700213_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, patrolId);
	elseif arrayId == 3 then
        SetFubenData_Param(sceneId, x700213_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700213_CSP_COUNT,             4                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700213_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN,         x700213_g_Timer3    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BACKUP,       x700213_g_Timer3    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BISHEN,       x700213_g_Timer3_r  );
        SetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN,         x700213_g_CountDown );
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     12                  );--总数12
		--npc talk
		local id = GetFubenData_Param( sceneId, x700213_CSP_NPCID);
		NpcTalk( sceneId, id, x700213_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, patrolId);
    elseif arrayId == 4 then
        SetFubenData_Param(sceneId, x700213_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700213_CSP_COUNT,             6                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700213_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN,         x700213_g_Timer4    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BACKUP,       x700213_g_Timer4    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BISHEN,       x700213_g_Timer4_r  );
        SetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN,         x700213_g_CountDown );
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     18                  );--总数18
		--npc talk
		local id = GetFubenData_Param( sceneId, x700213_CSP_NPCID);
		NpcTalk( sceneId, id, x700213_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, patrolId);
    elseif arrayId == 5 then
        SetFubenData_Param(sceneId, x700213_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700213_CSP_COUNT,             1                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700213_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN,         x700213_g_Timer5    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BACKUP,       x700213_g_Timer5    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BISHEN,       x700213_g_Timer5_r  );
        SetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN,         x700213_g_CountDown );
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     1                   );--总数1
		--npc talk
		local id = GetFubenData_Param( sceneId, x700213_CSP_NPCID);
		NpcTalk( sceneId, id, x700213_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, patrolId);
    elseif arrayId == 6 then
        SetFubenData_Param(sceneId, x700213_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700213_CSP_COUNT,             8                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700213_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN,         x700213_g_Timer6    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BACKUP,       x700213_g_Timer6    );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BISHEN,       x700213_g_Timer6_r  );
        SetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN,         x700213_g_CountDown );
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     24                  );--总数24
		--npc talk
		local id = GetFubenData_Param( sceneId, x700213_CSP_NPCID);
		NpcTalk( sceneId, id, x700213_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, patrolId);

	elseif arrayId == 8 then
        SetFubenData_Param(sceneId, x700213_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700213_CSP_COUNT,             1                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700213_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN,         0                   );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BACKUP,       0                   );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BISHEN,       0                   );
        SetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN,         x700213_g_CountDown );
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     1                   );--总数24
		--npc talk
		local id = GetFubenData_Param( sceneId, x700213_CSP_NPCID);
		NpcTalk( sceneId, id, x700213_g_NpcText[ arrayId], -1);
		--npc move to target
		SetPatrolId( sceneId, id, 7);
	elseif arrayId == 9 then
        SetFubenData_Param(sceneId, x700213_CSP_ARRAYID,           arrayId             );
        SetFubenData_Param(sceneId, x700213_CSP_COUNT,             2                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT,        0                   );
	    SetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT,        0                   );
		SetFubenData_Param(sceneId, x700213_CSP_GROUP,        		0                   );
        SetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN,         x700213_g_Timer7	);
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BACKUP,       x700213_g_Timer7	);
        SetFubenData_Param(sceneId, x700213_CSP_TIME_BISHEN,       x700213_g_Timer7_r	);
        SetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN,         0					);
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     2                   );--总数24	
	end
end


---------------------------------------------------------------------------------------------------
--添加怪物数据
---------------------------------------------------------------------------------------------------
function x700213_AddMonsterParam( sceneId )

    local arrayId = GetFubenData_Param(sceneId, x700213_CSP_ARRAYID);					    -- 设置离开倒计时次数
    local nCount  = GetFubenData_Param(sceneId, x700213_CSP_COUNT);                        -- 一次创建数量
    local nHaveCount = GetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT);	--显示刷怪倒计时
	local createCountdown = GetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN);
	local group = GetFubenData_Param(sceneId, x700213_CSP_GROUP)
	if createCountdown > 0 then
		local countTime = createCountdown * 5
		local str = countTime.."秒后出现新的敌人！"
		ShowTips( sceneId, str);
		SetFubenData_Param( sceneId, x700213_CSP_COUNTDOWN, createCountdown - 1);
		return
	end

    --判断是否已经到创建怪物的间隔
    local nTimeDown = GetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN ) - 1
    -- 如果当前刷怪点已经创建了至少一只怪才走刷怪批次之间的倒计时，第一次刷怪前不用倒计时
    if nTimeDown > 0 and nHaveCount > 0 then
        SetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN, nTimeDown )
        return
    else
        local nTimeBack = GetFubenData_Param(sceneId, x700213_CSP_TIME_BACKUP )
        SetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN, nTimeBack )
    end

    local nNeedCreate = GetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT)


    --判断创建怪物的总数
    if nHaveCount < nNeedCreate then

        for i = 0,nCount-1 do

            local nTotalCount = GetFubenData_Param( sceneId, x700213_CSP_TOTALCOUNT )

            local pos = x700213_CSP_START + nTotalCount*3

            local objId,nShengWang = x700213_CreateMonster( sceneId,arrayId, group )
            if objId ~= -1 then
                local nBianShen = GetFubenData_Param(sceneId, x700213_CSP_TIME_BISHEN )

                SetFubenData_Param(sceneId, pos + 1, objId ) --设置怪物
                SetFubenData_Param(sceneId, pos + 2, 0     ) --0未变身,1变身,2死亡
                SetFubenData_Param(sceneId, pos + 3, nBianShen    ) --设置变身时间

                SetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT, nTotalCount + 1 );
            end
        end
    end
	
	SetFubenData_Param(sceneId, x700213_CSP_GROUP, group+1)


    -- nHaveCount = GetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT);
    -- local msg = "第"..(arrayId + 1).."拨怪创建,已创建："..nHaveCount.." 总数："..nNeedCreate
    -- ShowTips(sceneId,msg)
end

--
function x700213_BosnusMonsterLogic( sceneId )
	--刷奖励怪
	local TotalBian = GetFubenData_Param( sceneId, x700213_CSP_TOTALBIAN )
	local TotalDisapear = GetFubenData_Param( sceneId, x700213_CSP_TOTALDISAPEAR )
	--print( "TotalBian="..TotalBian.."  , TotalDisapear="..TotalDisapear )
	if TotalBian+TotalDisapear == 0 then
		local str = "虚空南部发生了扭曲！"
		ShowTips( sceneId, str)
		x700213_SetMonsterParam(sceneId,9)
		SetFubenData_Param(sceneId,x700213_CSP_BONUSLOGIC,0)
	end	
end

--
function x700213_FinalBossLogic( sceneId)
	--显示刷怪倒计时
	local createCountdown = GetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN);
	--print("x700213_FinalBossLogic : createCountdown="..createCountdown)
	if createCountdown > 0 then
		local countTime = createCountdown * 5
		local str = countTime.."秒后，将是最严峻的考验！"
		ShowTips( sceneId, str);
		SetFubenData_Param( sceneId, x700213_CSP_COUNTDOWN, createCountdown - 1);
		return
	end
	
	createCountdown = GetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN);
	if createCountdown == 0 then
		SetFubenData_Param( sceneId, x700213_CSP_COUNTDOWN, -1);
		--delete npc
		local id = GetFubenData_Param( sceneId, x700213_CSP_NPCID);
		DeleteMonster( sceneId, id);
		--create boss
		x700213_CreateBoss( sceneId);
		
		SetFubenData_Param(sceneId,x700213_CSP_BOSSLOGIC,0)
		SetFubenData_Param(sceneId,x700213_CSP_BONUSLOGIC,1)
	end
end

function ShowTips( sceneId,msg )

    if msg == nil then
        return
    end

    local humancount = GetFuben_PlayerCount(sceneId);
    for i = 0, humancount - 1 do

        local humanId = GetFuben_PlayerObjId(sceneId, i);	--取得当前场景里人的objId

        BeginQuestEvent(sceneId);
            AddQuestText(sceneId, msg);
        EndQuestEvent();
        DispatchQuestTips(sceneId, humanId);

    end
end



---------------------------------------------------------------------------------------------------
--更新怪物数据
---------------------------------------------------------------------------------------------------
function x700213_UpdateMonsterParam( sceneId )

    --local monstercount = GetFubenData_Param( sceneId,x700213_CSP_MONSTERCONVCOUNT )
    if GetFubenData_Param(sceneId,x700213_CSP_BOSSLOGIC)==1 then
		x700213_FinalBossLogic( sceneId);
        return
    end

	if GetFubenData_Param(sceneId,x700213_CSP_BONUSLOGIC)==1 then
		x700213_BosnusMonsterLogic(sceneId)
		return
	end

    local arrayId = GetFubenData_Param(sceneId, x700213_CSP_ARRAYID);					    -- 设置离开倒计时次数
    local nTotalCount = GetFubenData_Param( sceneId, x700213_CSP_TOTALCOUNT )             -- 取得已创建怪物数量
    local nNeedCreate = GetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT)
	local nKill = 0
	
    for i =0, nTotalCount - 1 do

        local pos = x700213_CSP_START  + i * 3

		--怪物id
        local objId = GetFubenData_Param( sceneId,pos + 1 )
		--怪物状态：0未变身,1变身,2死亡
        local state = GetFubenData_Param( sceneId,pos + 2 )
		--变身计数器
        local tme   = GetFubenData_Param( sceneId,pos + 3 )

        if tme > 0 then
            tme = tme - 1
        end
        SetFubenData_Param( sceneId,pos + 3, tme )

		--提示1
		if tme==6 and state==0 then
			if arrayId==2 or arrayId==5 then
				ShowTips(sceneId,"30秒后敌人将逃离虚空，你也会一无所获！")
			end
		end		
		
		--提示2
		if tme==4 and state==0 then
			if arrayId==2 or arrayId==5 then
				ShowTips(sceneId,"20秒后敌人将逃离虚空，你也会一无所获！")
			end
		end
		
		--提示3
		if tme==2 and state==0 then
			if arrayId==2 or arrayId==5 then
				ShowTips(sceneId,"10秒后敌人将逃离虚空，你也会一无所获！")
			end			
		end		
		
        --只有状态为没变身的才执行变身处理
        if tme == 0 and state == 0  then
			--第2和5刷怪点创建的是Boss，不变身
            if arrayId ~= 2 and arrayId ~= 5 and arrayId~=9 then
				--到时间删除Boss怪物
                local OldObjId = GetFubenData_Param( sceneId,pos + 1)

				if OldObjId>0 then
				
					DeleteMonster( sceneId,OldObjId)

					local x,z = GetMonsterPosition( sceneId,OldObjId)
					
					local NewObjId = x700213_CreateMonster(sceneId,arrayId + 10,0,x,z )

					SetFubenData_Param( sceneId,pos + 1,  NewObjId )
					SetFubenData_Param( sceneId,pos + 2,  1 )   --设置为变身状态
					SetFubenData_Param( sceneId,pos + 3, -1 )   --时间为-1表示已经处理过变身
					
					local TotalBian = GetFubenData_Param( sceneId, x700213_CSP_TOTALBIAN ) + 1
					SetFubenData_Param( sceneId, x700213_CSP_TOTALBIAN, TotalBian )	
				end

            else
                local OldObjId = GetFubenData_Param( sceneId,pos + 1)
                DeleteMonster( sceneId,OldObjId)

                SetFubenData_Param( sceneId,pos + 3, -1 )   --时间为-1表示已经处理过变身	

				local TotalDisapear = GetFubenData_Param( sceneId, x700213_CSP_TOTALDISAPEAR ) + 1
				SetFubenData_Param( sceneId, x700213_CSP_TOTALDISAPEAR, TotalDisapear )	
            end

            local nTimeCount = GetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT)  + 1
            SetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT, nTimeCount)

            local nRefCount = GetFubenData_Param( sceneId,x700213_CSP_MONSTERCONVCOUNT ) + 1
            SetFubenData_Param( sceneId,x700213_CSP_MONSTERCONVCOUNT,nRefCount )		

            -- local msg = "第"..arrayId.."拨怪变身,当前："..nTimeCount.." 总数："..nNeedCreate
            -- ShowTips(sceneId,msg)

            --处理变身总数
        --elseif tme == 0 and state == 2 then
			--如果怪物被杀，立即更新变身计数，不走变身计数器逻辑。这样如果怪物被杀死后下一刷怪点可以立即开始。
		elseif state == 2 then
			--检查是否已经做变身标记，如果做过就跳过
			nKill = nKill + 1
			local isConvert = GetFubenData_Param( sceneId, pos + 3);
			if isConvert ~= -1 then
	            SetFubenData_Param( sceneId, pos + 3, -1 )   --时间为-1表示已经处理过变身

	            local nTimeCount = GetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT)  + 1
	            SetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT, nTimeCount)

	            local nRefCount = GetFubenData_Param( sceneId,x700213_CSP_MONSTERCONVCOUNT ) + 1
	            SetFubenData_Param( sceneId,x700213_CSP_MONSTERCONVCOUNT,nRefCount )

	            -- local msg = "第"..arrayId.."拨怪变身,当前："..nTimeCount.." 总数："..nNeedCreate
	            -- ShowTips(sceneId,msg)
			end
        end
    end

    x700213_AddMonsterParam( sceneId )

    local nTimeCount = GetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT)		--已变身总数
    if nTimeCount>=nNeedCreate or nKill>=nNeedCreate then
        x700213_SetMonsterParam( sceneId,arrayId + 1 )
    end
end

---------------------------------------------------------------------------------------------------
--刷新怪物数据
---------------------------------------------------------------------------------------------------
function x700213_RefreshMonsterParam( sceneId, objId )

    local arrayId = GetFubenData_Param(sceneId, x700213_CSP_ARRAYID);					    -- 设置离开倒计时次数
    local nTotalCount = GetFubenData_Param( sceneId, x700213_CSP_TOTALCOUNT )              -- 取得怪物数量

    for i =0, nTotalCount - 1 do

        local pos = x700213_CSP_START  + i * 3
        local objId_bak = GetFubenData_Param( sceneId,pos + 1 )

        --只有状态为没变身的才执行变身处理
        if objId_bak == objId  then

            SetFubenData_Param( sceneId,pos + 2,  2 )   --设置为变身状态
            return
        end
    end
end

---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700213_CreateMonster(sceneId,index,group,nx,nz)

    local copyscenelevel = GetFubenData_Param(sceneId, x700213_CSP_FUBENLEVEL ) ;

	for i, item in x700213_g_MonsterCreate do

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel and item.group==group then

            if item.flag == index then

 --               for j=0,item.count -1 do

                    local rx = random(-item.r,item.r)
                    local x = item.x + rx
                    local rz = random(-item.r,item.r)
                    local z = item.z + rz

                    if nx ~= nil and nz ~= nil then
                        x = nx
                        z = nz
                    end
                    local objId = 0
					
					if item.title~="" then
						objId = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700213_g_ScriptId, -1, 21, -1, item.facedir, "", item.title)
					else
						objId = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700213_g_ScriptId, -1, 21, -1, item.facedir)
					
					end

                    if item.flag < 10 then
                        local monstercount = GetFubenData_Param( sceneId,x700213_CSP_MONSTERCOUNT) + 1
                        SetFubenData_Param( sceneId,x700213_CSP_MONSTERCOUNT,monstercount)
                    end
                    return objId,item.bonus
--                end

            end
        end
	end

    return -1,0

end

function x700213_GetBonus(nDataID)

	for i,item in x700213_g_MonsterCreate do
		if item.type==nDataID then
			return item.bonus
		end
	end
	
	for i,item in x700213_g_BossCreate do
		if item.type==nDataID then
			return item.bonus
		end
	end
	
	return 0
end

function x700213_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700213_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700213_CSP_KILLCOUNT, nDieCount+1);
	SetFubenData_Param(sceneId, x700213_CSP_NKILLMONSTER, nDieCount+1);
	local bossid = GetFubenData_Param(sceneId, x700213_CSP_BOSSID)
	local arrayId = GetFubenData_Param(sceneId, x700213_CSP_ARRAYID);
	local nShengWang = 0
	
	nDieCount = nDieCount+1;
	
	local nTotalCount = GetFubenData_Param( sceneId, x700213_CSP_TOTALCOUNT )
	for i =0, nTotalCount - 1 do
		local pos = x700213_CSP_START  + i * 3
		local objid = GetFubenData_Param( sceneId,pos + 1 )
		if objid==selfId then
			SetFubenData_Param( sceneId,pos + 2,  2 )   --设置为死亡状态
		end
	end

	-- kill enough，创建BOSS
	local TotalDisapear = GetFubenData_Param( sceneId, x700213_CSP_TOTALDISAPEAR )
	if x700213_g_NeedKillMonster == nDieCount+TotalDisapear then
		x700213_SetMonsterParam( sceneId, 8)
		SetFubenData_Param(sceneId,x700213_CSP_BOSSLOGIC,1)
	end
	
	-- BOSS也被杀死了
	if bossid==selfId then
		x700213_OnAllMonsterDead( sceneId) 

		--//--------------------------- 世界喊话 Start--------------------
--			-- final boss
--			local nowTickCount = GetFubenData_Param(sceneId, x700213_CSP_TICKCOUNT)
--
--			local nowTime = x700213_g_TickTime* nowTickCount;
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
--			--LuaAllScenceM2Wrold (sceneId,"#R哇塞，人品啊！#G"..strPlayerName.."#R和他的队友仅用了#G"..strKillTime.."#R完成了虚空境的考验！", 0, 1)
			
			
			
			--//--------------------------- 世界喊话 end----------------------
	end

	local nDataID = GetMonsterDataID(sceneId,selfId)
	nShengWang = x700213_GetBonus(nDataID)

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		--local str = format("%d", nDieCount);
		--BeginQuestEvent(sceneId);
		--AddQuestText(sceneId, str);
		--EndQuestEvent(sceneId);
		--DispatchQuestTips(sceneId, humanId);
		
		-- 给每个人都加声望
		if nShengWang>0 then
			local nOldValue = GetShengWang( sceneId, humanId )
			SetShengWang( sceneId, humanId, nOldValue+nShengWang )
			Msg2Player(sceneId,humanId,"获得声望"..nShengWang,8,2)
		end		
	end
end

function x700213_ProcQuestObjectKilled(sceneId, selfId, objdataId ,objId, MissionId )
	--PrintStr("x700213_ProcQuestObjectKilled")
end

function x700213_OnAllMonsterDead( sceneId)
	x700213_CreateSubmitNpc( sceneId)
end

function x700213_CreateSubmitNpc( sceneId)

	 if x700213_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700213_g_SubmitNPC.type, x700213_g_SubmitNPC.x, x700213_g_SubmitNPC.z, 3, 0, -1, x700213_g_SubmitNPC.guid, -1, -1, x700213_g_SubmitNPC.facedir, "",x700213_g_SubmitNPC.title )
	 else
		CreateMonster(sceneId, x700213_g_SubmitNPC.type, x700213_g_SubmitNPC.x, x700213_g_SubmitNPC.z, 3, 0, -1, x700213_g_SubmitNPC.guid, -1, -1, x700213_g_SubmitNPC.facedir)
	 end
end



--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
function x700213_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700213_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--//add end





