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
x700213_CSP_MONSTERCOUNT            =   33      --��ǰ���ID
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
--NPC����ʱ˵��������
x700213_g_NpcText					=	{
											"��֮�飬����֮�飬����ʧȥ���", 
											"��֮�飬��֮�����Դ�������ʧ��", 
											"��֮�飬��֮ԴȪ���ɱ��˵Ļ��ģ�", 
											"��֮�飬������֮�飬һ�������һ�����ã�", 
											"��Ҫ���������������", 
											"��֮�飬��̰��֮�������֮�ף�", 
											"���ס�����ܵ��£�", 
											"սʤ������ħ��С���ˣ�", 
										}

x700213_g_NeedKillMonster			=  65	

------------------------- list -----------------------------------------

x700213_g_SubmitNPC                 =   { type =25033,guid= 150548,x = 32, z=34, facedir = 0, title = "" }


--����ʱ��
x700213_g_Timer0                    = 1
x700213_g_Timer1                    = 2
x700213_g_Timer2                    = 3 --boss
x700213_g_Timer3                    = 4
x700213_g_Timer4                    = 4
x700213_g_Timer5                    = 3 --boss
x700213_g_Timer6                    = 4
x700213_g_Timer7                    = 0

--����ʱ��
x700213_g_Timer0_r                  = 4
x700213_g_Timer1_r                  = 4
x700213_g_Timer2_r                  = 12    --boss
x700213_g_Timer3_r                  = 6
x700213_g_Timer4_r                  = 6
x700213_g_Timer5_r                  = 18    --boss
x700213_g_Timer6_r                  = 6
x700213_g_Timer7_r                  = 12

--ÿ��ˢ�ֵ�ĵ���ʱ����
x700213_g_CountDown					= 2

--BOSS����
x700213_g_BossCreate				=	{
                                            {levelmin =40, levelmax=100, name ="�����boss",   type= 27781,   x=31, z=31, r=0,  ai=18, aiscript=598, facedir = 0, title = "",bonus=0},  
                                            

										}

x700213_g_MonsterCreate            =    {

                                            --����ǰ
                                            {levelmin =40, levelmax=100, name ="С��11",   type= 27773,   x=12, z=16, r=1,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 0,group=0,time=18,bonus=0},
                                           
                                            {levelmin =40, levelmax=100, name ="С��12",   type= 27775,   x=12, z=16, r=1,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 0,group=1,time=18,bonus=0},
                                           
                                            
                                            {levelmin =40, levelmax=100, name ="С��13",   type= 27777,   x=12, z=16, r=1,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 0,group=2,time=18,bonus=0},
                                           
                                            
                                            {levelmin =40, levelmax=100, name ="С��21",   type= 27773,   x=12, z=31, r=3,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 1,group=0,time=17,bonus=0},
                                           
                                                                                                         
                                            {levelmin =40, levelmax=100, name ="С��22",   type= 27775,   x=12, z=31, r=3,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 1,group=1,time=17,bonus=0},
                                           
                                                                                                         
                                            {levelmin =40, levelmax=100, name ="С��23",   type= 27777,   x=12, z=31, r=3,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 1,group=2,time=17,bonus=0},
                                            

                                            {levelmin =40, levelmax=100, name ="���boss1",   type= 27779,   x=12, z=52, r=0,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 2,group=0,time=16,bonus=0},
                                            

                                            {levelmin =40, levelmax=100, name ="С��31",   type= 27773,   x=28, z=49, r=2,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 3,group=0,time=15,bonus=0},
                                           
                                                                                                                                                                                                     
                                            {levelmin =40, levelmax=100, name ="С��32",   type= 27775,   x=28, z=49, r=2,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 3,group=1,time=15,bonus=0},
                                           
                                                                                                                                                                                                   
                                            {levelmin =40, levelmax=100, name ="С��33",   type= 27777,   x=28, z=49, r=2,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 3,group=2,time=15,bonus=0},
                                            
                                                                                                                                                                                                  
                                            {levelmin =40, levelmax=100, name ="С��41",   type= 27773,   x=40, z=17, r=4,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 7,group=0,time=14,bonus=0},
                                            
                                                                                                                                                                                                  
                                            {levelmin =40, levelmax=100, name ="С��42",   type= 27775,   x=40, z=17, r=4,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 7,group=1,time=14,bonus=0},
                                           
                                            {levelmin =40, levelmax=100, name ="С��43",   type= 27777,   x=40, z=17, r=4,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 7,group=2,time=14,bonus=0},
                                            
                                                                                                                                                                                                   
                                            {levelmin =40, levelmax=100, name ="С��51",   type= 27773,   x=50, z=14, r=4,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 6,group=0,time=13,bonus=0},
                                            
                                                                                                                                                                                                     
                                            {levelmin =40, levelmax=100, name ="С��52",   type= 27775,   x=50, z=14, r=4,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 6,group=1,time=13,bonus=0},
                                            
                                                                                                                                                                                                    
                                            {levelmin =40, levelmax=100, name ="С��53",   type= 27777,   x=50, z=14, r=4,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 6,group=2,time=13,bonus=0},
                                            
                                            {levelmin =40, levelmax=100, name ="���boss2",   type= 27780,   x=50, z=33, r=0,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 5,group=0,time=12,bonus=0},
                                            
                                            {levelmin =40, levelmax=100, name ="С��61",   type= 27773,   x=50, z=50, r=2,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 4,group=0,time=11,bonus=0},
                                                                                                                                                                                     
                                            {levelmin =40, levelmax=100, name ="С��62",   type= 27775,   x=50, z=50, r=2,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 4,group=1,time=11,bonus=0},
                                                                                                                                                                                                                 
                                            {levelmin =40, levelmax=100, name ="С��63",   type= 27777,   x=50, z=50, r=2,  ai=7, aiscript=-1, facedir = 0, title = "",flag = 4,group=2,time=11,bonus=0},
                                           

											--������
                                            {levelmin =40, levelmax=100, name ="С��2����",   type= 27774,   x=31, z=17, r=2,  ai=7, aiscript=-1, facedir = 0, title = "", flag=9,group=0,time=-1,bonus=0},
                                          

                                            --�����
                                            {levelmin =40, levelmax=100, name ="С��1����",   type= 27774,   x=17, z=17, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 10,group=0,time=-1,bonus=0},
                                                  
                                            {levelmin =40, levelmax=100, name ="С��1����",   type= 27774,   x=17, z=31, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 11,group=0,time=-1,bonus=0},
                                              
                                            {levelmin =40, levelmax=100, name ="С��1����",   type= 27774,   x=17, z=45, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 12,group=0,time=-1,bonus=0},
                                                     
                                            {levelmin =40, levelmax=100, name ="С��1����",   type= 27774,   x=31, z=45, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 13,group=0,time=-1,bonus=0},
                                           
                                            {levelmin =40, levelmax=100, name ="С��1����",   type= 27774,   x=31, z=31, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 17,group=0,time=-1,bonus=0},
                                                   
                                            {levelmin =40, levelmax=100, name ="С��1����",   type= 27774,   x=31, z=17, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 16,group=0,time=-1,bonus=0},
                                             
                                            {levelmin =40, levelmax=100, name ="С��1����",   type= 27774,   x=46, z=17, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 15,group=0,time=-1,bonus=0},
                                                 
                                            {levelmin =40, levelmax=100, name ="С��1����",   type= 27774,   x=46, z=31, r=6,  ai=9, aiscript=-1, facedir = 0, title = "",flag = 14,group=0,time=-1,bonus=0},
                                           
                                        }

x700213_g_NPCType					= 	25033

x700213_g_NpcGUID                   =   {
                                            {guid = 150000, name = "ָ����ʦ"},
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
--OnFubenSceneCreated  :  �����������ɹ�ʱ�� ��ʼˢ�ֺ�npc
--*********************************************************
-----------------------------------------------------------
function x700213_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  ��������id
	SetFubenData_Param(sceneId, x700213_CSP_ARRAYID, -1);	

	x700213_CreateNPC( sceneId);
		
end



-----------------------------------------------------------
--*********************************************************
--EnterTick  :  ��������
--*********************************************************
-----------------------------------------------------------
function x700213_EnterTick(sceneId, nowTickCount)

	if nowTickCount >= 6 then
	    x700213_UpdateMonsterParam( sceneId )
	end
end


---------------------------------------------------------------------------------------------------
--����BOSS
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
--���ù�������
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

		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     3                   );--����3
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
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     6                   );--����6
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
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     1                   );--����1
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
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     12                  );--����12
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
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     18                  );--����18
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
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     1                   );--����1
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
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     24                  );--����24
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
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     1                   );--����24
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
		SetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT,     2                   );--����24	
	end
end


---------------------------------------------------------------------------------------------------
--��ӹ�������
---------------------------------------------------------------------------------------------------
function x700213_AddMonsterParam( sceneId )

    local arrayId = GetFubenData_Param(sceneId, x700213_CSP_ARRAYID);					    -- �����뿪����ʱ����
    local nCount  = GetFubenData_Param(sceneId, x700213_CSP_COUNT);                        -- һ�δ�������
    local nHaveCount = GetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT);	--��ʾˢ�ֵ���ʱ
	local createCountdown = GetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN);
	local group = GetFubenData_Param(sceneId, x700213_CSP_GROUP)
	if createCountdown > 0 then
		local countTime = createCountdown * 5
		local str = countTime.."�������µĵ��ˣ�"
		ShowTips( sceneId, str);
		SetFubenData_Param( sceneId, x700213_CSP_COUNTDOWN, createCountdown - 1);
		return
	end

    --�ж��Ƿ��Ѿ�����������ļ��
    local nTimeDown = GetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN ) - 1
    -- �����ǰˢ�ֵ��Ѿ�����������һֻ�ֲ���ˢ������֮��ĵ���ʱ����һ��ˢ��ǰ���õ���ʱ
    if nTimeDown > 0 and nHaveCount > 0 then
        SetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN, nTimeDown )
        return
    else
        local nTimeBack = GetFubenData_Param(sceneId, x700213_CSP_TIME_BACKUP )
        SetFubenData_Param(sceneId, x700213_CSP_TIME_DOWN, nTimeBack )
    end

    local nNeedCreate = GetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT)


    --�жϴ������������
    if nHaveCount < nNeedCreate then

        for i = 0,nCount-1 do

            local nTotalCount = GetFubenData_Param( sceneId, x700213_CSP_TOTALCOUNT )

            local pos = x700213_CSP_START + nTotalCount*3

            local objId,nShengWang = x700213_CreateMonster( sceneId,arrayId, group )
            if objId ~= -1 then
                local nBianShen = GetFubenData_Param(sceneId, x700213_CSP_TIME_BISHEN )

                SetFubenData_Param(sceneId, pos + 1, objId ) --���ù���
                SetFubenData_Param(sceneId, pos + 2, 0     ) --0δ����,1����,2����
                SetFubenData_Param(sceneId, pos + 3, nBianShen    ) --���ñ���ʱ��

                SetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT, nTotalCount + 1 );
            end
        end
    end
	
	SetFubenData_Param(sceneId, x700213_CSP_GROUP, group+1)


    -- nHaveCount = GetFubenData_Param(sceneId, x700213_CSP_TOTALCOUNT);
    -- local msg = "��"..(arrayId + 1).."���ִ���,�Ѵ�����"..nHaveCount.." ������"..nNeedCreate
    -- ShowTips(sceneId,msg)
end

--
function x700213_BosnusMonsterLogic( sceneId )
	--ˢ������
	local TotalBian = GetFubenData_Param( sceneId, x700213_CSP_TOTALBIAN )
	local TotalDisapear = GetFubenData_Param( sceneId, x700213_CSP_TOTALDISAPEAR )
	--print( "TotalBian="..TotalBian.."  , TotalDisapear="..TotalDisapear )
	if TotalBian+TotalDisapear == 0 then
		local str = "����ϲ�������Ť����"
		ShowTips( sceneId, str)
		x700213_SetMonsterParam(sceneId,9)
		SetFubenData_Param(sceneId,x700213_CSP_BONUSLOGIC,0)
	end	
end

--
function x700213_FinalBossLogic( sceneId)
	--��ʾˢ�ֵ���ʱ
	local createCountdown = GetFubenData_Param(sceneId, x700213_CSP_COUNTDOWN);
	--print("x700213_FinalBossLogic : createCountdown="..createCountdown)
	if createCountdown > 0 then
		local countTime = createCountdown * 5
		local str = countTime.."��󣬽������Ͼ��Ŀ��飡"
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

        local humanId = GetFuben_PlayerObjId(sceneId, i);	--ȡ�õ�ǰ�������˵�objId

        BeginQuestEvent(sceneId);
            AddQuestText(sceneId, msg);
        EndQuestEvent();
        DispatchQuestTips(sceneId, humanId);

    end
end



---------------------------------------------------------------------------------------------------
--���¹�������
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

    local arrayId = GetFubenData_Param(sceneId, x700213_CSP_ARRAYID);					    -- �����뿪����ʱ����
    local nTotalCount = GetFubenData_Param( sceneId, x700213_CSP_TOTALCOUNT )             -- ȡ���Ѵ�����������
    local nNeedCreate = GetFubenData_Param(sceneId, x700213_CSP_MONSTER_COUNT)
	local nKill = 0
	
    for i =0, nTotalCount - 1 do

        local pos = x700213_CSP_START  + i * 3

		--����id
        local objId = GetFubenData_Param( sceneId,pos + 1 )
		--����״̬��0δ����,1����,2����
        local state = GetFubenData_Param( sceneId,pos + 2 )
		--���������
        local tme   = GetFubenData_Param( sceneId,pos + 3 )

        if tme > 0 then
            tme = tme - 1
        end
        SetFubenData_Param( sceneId,pos + 3, tme )

		--��ʾ1
		if tme==6 and state==0 then
			if arrayId==2 or arrayId==5 then
				ShowTips(sceneId,"30�����˽�������գ���Ҳ��һ������")
			end
		end		
		
		--��ʾ2
		if tme==4 and state==0 then
			if arrayId==2 or arrayId==5 then
				ShowTips(sceneId,"20�����˽�������գ���Ҳ��һ������")
			end
		end
		
		--��ʾ3
		if tme==2 and state==0 then
			if arrayId==2 or arrayId==5 then
				ShowTips(sceneId,"10�����˽�������գ���Ҳ��һ������")
			end			
		end		
		
        --ֻ��״̬Ϊû����Ĳ�ִ�б�����
        if tme == 0 and state == 0  then
			--��2��5ˢ�ֵ㴴������Boss��������
            if arrayId ~= 2 and arrayId ~= 5 and arrayId~=9 then
				--��ʱ��ɾ��Boss����
                local OldObjId = GetFubenData_Param( sceneId,pos + 1)

				if OldObjId>0 then
				
					DeleteMonster( sceneId,OldObjId)

					local x,z = GetMonsterPosition( sceneId,OldObjId)
					
					local NewObjId = x700213_CreateMonster(sceneId,arrayId + 10,0,x,z )

					SetFubenData_Param( sceneId,pos + 1,  NewObjId )
					SetFubenData_Param( sceneId,pos + 2,  1 )   --����Ϊ����״̬
					SetFubenData_Param( sceneId,pos + 3, -1 )   --ʱ��Ϊ-1��ʾ�Ѿ����������
					
					local TotalBian = GetFubenData_Param( sceneId, x700213_CSP_TOTALBIAN ) + 1
					SetFubenData_Param( sceneId, x700213_CSP_TOTALBIAN, TotalBian )	
				end

            else
                local OldObjId = GetFubenData_Param( sceneId,pos + 1)
                DeleteMonster( sceneId,OldObjId)

                SetFubenData_Param( sceneId,pos + 3, -1 )   --ʱ��Ϊ-1��ʾ�Ѿ����������	

				local TotalDisapear = GetFubenData_Param( sceneId, x700213_CSP_TOTALDISAPEAR ) + 1
				SetFubenData_Param( sceneId, x700213_CSP_TOTALDISAPEAR, TotalDisapear )	
            end

            local nTimeCount = GetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT)  + 1
            SetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT, nTimeCount)

            local nRefCount = GetFubenData_Param( sceneId,x700213_CSP_MONSTERCONVCOUNT ) + 1
            SetFubenData_Param( sceneId,x700213_CSP_MONSTERCONVCOUNT,nRefCount )		

            -- local msg = "��"..arrayId.."���ֱ���,��ǰ��"..nTimeCount.." ������"..nNeedCreate
            -- ShowTips(sceneId,msg)

            --�����������
        --elseif tme == 0 and state == 2 then
			--������ﱻɱ���������±�����������߱���������߼�������������ﱻɱ������һˢ�ֵ����������ʼ��
		elseif state == 2 then
			--����Ƿ��Ѿ��������ǣ��������������
			nKill = nKill + 1
			local isConvert = GetFubenData_Param( sceneId, pos + 3);
			if isConvert ~= -1 then
	            SetFubenData_Param( sceneId, pos + 3, -1 )   --ʱ��Ϊ-1��ʾ�Ѿ����������

	            local nTimeCount = GetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT)  + 1
	            SetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT, nTimeCount)

	            local nRefCount = GetFubenData_Param( sceneId,x700213_CSP_MONSTERCONVCOUNT ) + 1
	            SetFubenData_Param( sceneId,x700213_CSP_MONSTERCONVCOUNT,nRefCount )

	            -- local msg = "��"..arrayId.."���ֱ���,��ǰ��"..nTimeCount.." ������"..nNeedCreate
	            -- ShowTips(sceneId,msg)
			end
        end
    end

    x700213_AddMonsterParam( sceneId )

    local nTimeCount = GetFubenData_Param(sceneId, x700213_CSP_TIME_COUNT)		--�ѱ�������
    if nTimeCount>=nNeedCreate or nKill>=nNeedCreate then
        x700213_SetMonsterParam( sceneId,arrayId + 1 )
    end
end

---------------------------------------------------------------------------------------------------
--ˢ�¹�������
---------------------------------------------------------------------------------------------------
function x700213_RefreshMonsterParam( sceneId, objId )

    local arrayId = GetFubenData_Param(sceneId, x700213_CSP_ARRAYID);					    -- �����뿪����ʱ����
    local nTotalCount = GetFubenData_Param( sceneId, x700213_CSP_TOTALCOUNT )              -- ȡ�ù�������

    for i =0, nTotalCount - 1 do

        local pos = x700213_CSP_START  + i * 3
        local objId_bak = GetFubenData_Param( sceneId,pos + 1 )

        --ֻ��״̬Ϊû����Ĳ�ִ�б�����
        if objId_bak == objId  then

            SetFubenData_Param( sceneId,pos + 2,  2 )   --����Ϊ����״̬
            return
        end
    end
end

---------------------------------------------------------------------------------------------------
--����Monster
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
			SetFubenData_Param( sceneId,pos + 2,  2 )   --����Ϊ����״̬
		end
	end

	-- kill enough������BOSS
	local TotalDisapear = GetFubenData_Param( sceneId, x700213_CSP_TOTALDISAPEAR )
	if x700213_g_NeedKillMonster == nDieCount+TotalDisapear then
		x700213_SetMonsterParam( sceneId, 8)
		SetFubenData_Param(sceneId,x700213_CSP_BOSSLOGIC,1)
	end
	
	-- BOSSҲ��ɱ����
	if bossid==selfId then
		x700213_OnAllMonsterDead( sceneId) 

		--//--------------------------- ���纰�� Start--------------------
--			-- final boss
--			local nowTickCount = GetFubenData_Param(sceneId, x700213_CSP_TICKCOUNT)
--
--			local nowTime = x700213_g_TickTime* nowTickCount;
--
--			local nMinute = floor(nowTime/60)
--			local nSec = mod(nowTime,60)
--
--				
--			local strPlayerName = GetName(sceneId, killerId)     -- ɱ��������������
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
--			local strKillTime = format("%d��%d��", nMinute, nSec) -- ɱ��������¼�
--
--			
--			
--			--LuaAllScenceM2Wrold (sceneId,"#R��������Ʒ����#G"..strPlayerName.."#R�����Ķ��ѽ�����#G"..strKillTime.."#R�������վ��Ŀ��飡", 0, 1)
			
			
			
			--//--------------------------- ���纰�� end----------------------
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
		
		-- ��ÿ���˶�������
		if nShengWang>0 then
			local nOldValue = GetShengWang( sceneId, humanId )
			SetShengWang( sceneId, humanId, nOldValue+nShengWang )
			Msg2Player(sceneId,humanId,"�������"..nShengWang,8,2)
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
--��������
---------------------------------------------------------------------------------------------------
function x700213_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--�뿪����
---------------------------------------------------------------------------------------------------
function x700213_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--//add end





