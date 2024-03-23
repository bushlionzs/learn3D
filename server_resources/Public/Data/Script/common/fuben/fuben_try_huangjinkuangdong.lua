---------------------------------------------------
-- File: 700212_fuben_huangjinkuangdong_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700212_CSP_FUBENTYPE				= 	0
x700212_CSP_SCRIPTID				=	1
x700212_CSP_TICKCOUNT				= 	2
x700212_CSP_FROMSCENEID				= 	3
x700212_CSP_ISCLOSING				= 	4
x700212_CSP_LEAVECOUNTDOWN			= 	5
x700212_CSP_TEAMID					=	6
x700212_CSP_BACKSCENEX       		=   7
x700212_CSP_BACKSCENEZ      		=   8
x700212_CSP_FUBENLEVEL			=	9
x700212_CSP_KILLCOUNT				=	20
x700212_CSP_FUBEN_SCENE_ID			=	21
x700212_CSP_BOSS1_ID				=	22
x700212_CSP_BOSS2_ID				=	23
x700212_CSP_BOSS2_FULL_HP			=   24
x700212_CSP_BOSS2_LOADMONSTER		=   25

x700212_CSP_NPC_ID					=	26
x700212_CSP_NPC_STATUS				=	27


x700212_CSP_B_GUOYUN_START			=	228
x700212_CSP_B_GATHERED_START		=	234
x700212_CSP_HUMAN_COUNT				=	240
x700212_CSP_OBJID_START				=	241
x700212_CSP_GUID_START              =   248



------------------------Scene System Setting -----------------------------------

x700212_g_ScriptId 					= 700212

----------------------------- special for this Fuben --------------------
x700212_g_RandomBossRate			=   0                       --隐藏boss出现几率
x700212_g_nGrowpointType	=	540                             --boss掉落生长点id

------------------------- list -----------------------------------------

x700212_g_SubmitNPC                 =   { type =25021,guid= 150521,x = 77, z=18, facedir =0, title="" }

--BOSS类型
x700212_g_BossCreate				=	{
											{levelmin =20, levelmax=100, name ="矿工头",   type= 27724,  x=45, z=88,  ai=9, aiscript=553, facedir = 0, title = "",flag=0},
											

                                            {levelmin =20, levelmax=100, name ="半人马头领",   type= 27725,  x=68, z=25,  ai=18, aiscript=554, facedir = 0, title = "",flag=1},
											


										}
-- Random 怪物

x700212_g_Boss_Random_Create		=	{
											{levelmin =20, levelmax=100, name ="隐藏boss2",   type= 25108,   x=71, z=86, r=0,  ai=9, aiscript=637,  facedir = 0, title = "",flag=0},
											


										}

--Monster类型
x700212_g_MonsterCreate				=	{

											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=108.02, z=44.79 , r=0,count = 1, ai=9, aiscript=550, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=115.02, z=45.23 , r=0,count = 1, ai=9, aiscript=551, facedir = 11, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=110.53, z=70.15 , r=0,count = 1, ai=9, aiscript=550, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=110.56, z=65.52 , r=0,count = 1, ai=9, aiscript=551, facedir = 11, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=115.15, z=105.48, r=0,count = 1, ai=9, aiscript=550, facedir = 11, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=108.49, z=105.92, r=0,count = 1, ai=9, aiscript=551, facedir = 7 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=108.77, z=100.65, r=0,count = 1, ai=9, aiscript=550, facedir = 7 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=84.55 , z=98.44 , r=0,count = 1, ai=9, aiscript=551, facedir = 31, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=85.61 , z=107.43, r=0,count = 1, ai=9, aiscript=550, facedir = 4 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=82.66 , z=90.72 , r=0,count = 1, ai=9, aiscript=551, facedir = 4 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=80.11 , z=103.66, r=0,count = 1, ai=9, aiscript=550, facedir = 2 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=79.96 , z=71.20 , r=0,count = 1, ai=9, aiscript=551, facedir = 2 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=82.23 , z=67.37 , r=0,count = 1, ai=9, aiscript=550, facedir = 31, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=70.27 , z=61.06 , r=0,count = 1, ai=9, aiscript=551, facedir = 31, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=57.91 , z=54.67 , r=0,count = 1, ai=9, aiscript=550, facedir = 33, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=38.81 , z=75.00 , r=0,count = 1, ai=9, aiscript=551, facedir = 2 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=56.05 , z=80.57 , r=0,count = 1, ai=9, aiscript=550, facedir = 13, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=50.71 , z=65.00 , r=0,count = 1, ai=9, aiscript=551, facedir = 11, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=41.66 , z=112.66, r=0,count = 1, ai=9, aiscript=550, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=18.38 , z=106.96, r=0,count = 1, ai=9, aiscript=551, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=23.73 , z=102.97, r=0,count = 1, ai=9, aiscript=550, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=15.90 , z=55.41 , r=0,count = 1, ai=9, aiscript=551, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=17.03 , z=75.78 , r=0,count = 1, ai=9, aiscript=550, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=23.55 , z=57.35 , r=0,count = 1, ai=9, aiscript=551, facedir = 27, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=23.02 , z=107.33, r=0,count = 1, ai=9, aiscript=550, facedir = 0 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=20.77 , z=113.87, r=0,count = 1, ai=9, aiscript=551, facedir = 2 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=40.44 , z=108.27, r=0,count = 1, ai=9, aiscript=550, facedir = 6 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=54.05 , z=69.83 , r=0,count = 1, ai=9, aiscript=551, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=44.61 , z=72.18 , r=0,count = 1, ai=9, aiscript=550, facedir = 4 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=86.09 , z=70.94 , r=0,count = 1, ai=9, aiscript=551, facedir = 4 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=77.16 , z=68.76 , r=0,count = 1, ai=9, aiscript=550, facedir = 4 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=79.61 , z=95.84 , r=0,count = 1, ai=9, aiscript=551, facedir = 31, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=84.77 , z=103.06, r=0,count = 1, ai=9, aiscript=550, facedir = 0 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=112.25, z=108.14, r=0,count = 1, ai=9, aiscript=551, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=104.12, z=104.04, r=0,count = 1, ai=9, aiscript=550, facedir = 2 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=112.56, z=47.50 , r=0,count = 1, ai=9, aiscript=551, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=109.54, z=47.48 , r=0,count = 1, ai=9, aiscript=550, facedir = 4 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=114.51, z=70.12 , r=0,count = 1, ai=9, aiscript=551, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=105.90, z=70.38 , r=0,count = 1, ai=9, aiscript=550, facedir = 4 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=52.84 , z=81.55 , r=0,count = 1, ai=9, aiscript=551, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=12.58 , z=69.88 , r=0,count = 1, ai=9, aiscript=550, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=20.58 , z=68.70 , r=0,count = 1, ai=9, aiscript=551, facedir = 9 , title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=45.36 , z=109.38, r=0,count = 1, ai=9, aiscript=550, facedir = 12, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=63.73 , z=57.11 , r=0,count = 1, ai=9, aiscript=551, facedir = 31, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=15.59 , z=102.47, r=0,count = 1, ai=9, aiscript=550, facedir = 31, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=16.90 , z=25.08 , r=0,count = 1, ai=9, aiscript=551, facedir = 27, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工1",   type= 27721,  x=24.42 , z=14.72 , r=0,count = 1, ai=9, aiscript=550, facedir = 27, title = ""},
											{levelmin = 20, levelmax=100, name ="矿工2",   type= 27722,  x=31.82 , z=19.48 , r=0,count = 1, ai=9, aiscript=551, facedir = 27, title = ""},

											

										}

--Monster类型
x700212_g_MonsterCreate_Patrol		=	{
											{levelmin =20, levelmax=100, name ="矿工1",   type= 27721, x=52, z=65, r=8,count = 0, ai=9, aiscript=550, facedir = 0, title = "", patrolid =-1},
											

											{levelmin =20, levelmax=100, name ="矿工2",   type= 27722, x=72, z=98, r=8,count = 0, ai=9, aiscript=551, facedir = 0, title = "", patrolid =-1},
											
										}


x700212_g_Sub_MonsterCreate				= {
                                            {levelmin =20, levelmax=100, name ="半人马小弟",   type= 27723,   r=0, ai=9, aiscript=552, facedir = 0, title = ""},
											

                                            {levelmin =20, levelmax=100, name ="半人马小弟",   type= 27723,   r=0, ai=9, aiscript=552, facedir = 0, title = ""},
											

                                          }
-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700212_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

end


-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700212_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	
	
	local humancount = GetFuben_PlayerCount(sceneId);
	SetFubenData_Param(sceneId, x700212_CSP_HUMAN_COUNT, humancount);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		SetFubenData_Param(sceneId, x700212_CSP_OBJID_START+i, humanId);

		local bGuoyun = CountryIsFortuneTime(sceneId,humanId,2)
		SetFubenData_Param(sceneId, x700212_CSP_B_GUOYUN_START+i, 0); --bGuoyun
	end
	
	x700212_CreateBoss( sceneId )
	x700212_CreateRandomBoss( sceneId )
    x700212_CreateMonster( sceneId )
		
end

-----------------------------------------------------------
--*********************************************************
--EnterTick  :  副本心跳
--*********************************************************
-----------------------------------------------------------
function x700212_EnterTick(sceneId, nowTickCount)

	if nowTickCount >= 2 then
            local nBoss2 = GetFubenData_Param(sceneId, x700212_CSP_BOSS2_ID )
			
			if nBoss2>0 then
				local humancount = GetFuben_PlayerCount(sceneId);
				if humancount>0 then
					local nCurrentHp = GetHp( sceneId, nBoss2 )
					local nFullHp = GetFubenData_Param(sceneId, x700212_CSP_BOSS2_FULL_HP )
					local bCreatedSubMonster = GetFubenData_Param(sceneId, x700212_CSP_BOSS2_LOADMONSTER )
					
					if nCurrentHp/nFullHp <0.3 then
						if bCreatedSubMonster<=0 then
							x700212_CreateSubMonster(sceneId)
						end
					end
				end
			end
        end

	if nowTickCount>=6 then
		local npcStatus = GetFubenData_Param(sceneId, x700212_CSP_NPC_STATUS )

		if npcStatus==1 then
			local npcId = GetFubenData_Param(sceneId, x700212_CSP_NPC_ID )
			NpcTalk(sceneId, npcId, "感谢你们除掉了这金矿洞的恶魔，不过，我们还是赶紧出去吧。",  -1)
			SetFubenData_Param(sceneId, x700212_CSP_NPC_STATUS,  2 )
		end
	end
end


function x700212_CreateBoss(sceneId)


	local copyscenelevel = GetFubenData_Param(sceneId, x700212_CSP_FUBENLEVEL ) ;

	
	

	for i, item in x700212_g_BossCreate do --创建Boss

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
		    local nRet = 0
			
			if item.title~="" then
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700212_g_ScriptId, -1, 21,-1, item.facedir,  "",item.title)
			else
				nRet = CreateMonster(sceneId, item.type, item.x, item.z, item.ai, item.aiscript, x700212_g_ScriptId, -1, 21,-1, item.facedir)
			
			end
			
			if item.flag == 0 then
				SetFubenData_Param(sceneId, x700212_CSP_BOSS1_ID, nRet )
				SetPatrolId(sceneId, nRet, -1)
			elseif item.flag == 1 then
				
				SetFubenData_Param(sceneId, x700212_CSP_BOSS2_ID, nRet )
				local nFullHp = GetHp( sceneId, nRet )
				SetFubenData_Param(sceneId, x700212_CSP_BOSS2_FULL_HP, nFullHp )
				SetFubenData_Param(sceneId, x700212_CSP_BOSS2_LOADMONSTER, 0 )
			end
        end
	end

end

function x700212_CreateRandomBoss(sceneId)


	local rate = random(0,100)/100;
	if rate>= x700212_g_RandomBossRate then
		return 0;
	end

	local nFlag = random(0,0)

	

	local copyscenelevel = GetFubenData_Param(sceneId, x700212_CSP_FUBENLEVEL ) ;


	
	
	for i, item in x700212_g_Boss_Random_Create do --创建随机Boss
		if item.flag == nFlag then
			if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
				if item.title~="" then
					CreateMonster(sceneId, item.type, item.x,item.z, item.ai, item.aiscript, x700212_g_ScriptId, -1, 21,-1,item.facedir,  "",item.title)
				else
					CreateMonster(sceneId, item.type, item.x,item.z, item.ai, item.aiscript, x700212_g_ScriptId, -1, 21,-1,item.facedir)
				
				end
			end
		end
	end

end

function x700212_CreateSubMonster(sceneId)
	local nBoss2 = GetFubenData_Param(sceneId, x700212_CSP_BOSS2_ID )
	local bCreatedSubMonster = GetFubenData_Param(sceneId, x700212_CSP_BOSS2_LOADMONSTER )

	if bCreatedSubMonster>0 then
		return 0;
	end

	local x,z = GetWorldPos(sceneId,nBoss2)
		
	local nStep =0.2 ; 
	local copyscenelevel = GetFubenData_Param(sceneId, x700212_CSP_FUBENLEVEL ) ;

	for i, item in x700212_g_Sub_MonsterCreate do --创建召唤小怪
		if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
			local tx = x + random(-1*(i+1)*nStep, (i+1)*nStep);
			local tz = z + random(-1*(i+1)*nStep, (i+1)*nStep);

			if item.title~="" then
				CreateMonster(sceneId, item.type, tx, tz, item.ai, item.aiscript, x700212_g_ScriptId, -1, 21,-1,item.facedir, "", item.title)
			else
				CreateMonster(sceneId, item.type, tx, tz, item.ai, item.aiscript, x700212_g_ScriptId, -1, 21,-1,item.facedir)
			
			end
		end
	end

	

	SetFubenData_Param(sceneId, x700212_CSP_BOSS2_LOADMONSTER, 1 )

	
end



---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700212_CreateMonster(sceneId)


    local copyscenelevel = GetFubenData_Param(sceneId, x700212_CSP_FUBENLEVEL ) ;

	for i, item in x700212_g_MonsterCreate do --创建普通小怪

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
				if item.title ~="" then
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700212_g_ScriptId, -1, 21,-1,item.facedir, "", item.title)
				else
					CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700212_g_ScriptId, -1, 21,-1,item.facedir)
				
				end
			end
        end
	end


	for i, item in x700212_g_MonsterCreate_Patrol do --创建巡逻小怪

        if item.levelmin <= copyscenelevel and item.levelmax >= copyscenelevel then
            for j=0,item.count -1 do

                local rx = random(-item.r,item.r)
                local x = item.x + rx
                local rz = random(-item.r,item.r)
                local z = item.z + rz
		        local nRet = 0
				if item.title~="" then
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700212_g_ScriptId, -1, 21,-1,item.facedir, "",item.title)
				else
					nRet = CreateMonster(sceneId, item.type, x, z, item.ai, item.aiscript, x700212_g_ScriptId, -1, 21,-1,item.facedir)
				
				end
				SetPatrolId(sceneId, nRet, 1)
            end
        end
	end

end




function x700212_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700212_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700212_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	----------------------------------- 周卡 ----------------------------------

	local buffId1 =9011
	local buffId1_1 = 9013
	local buffId2 =9012

	local humancount = GetFuben_PlayerCount(sceneId);

	--通知玩家
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		local bHaveImpact1 = IsHaveSpecificImpact( sceneId, humanId, buffId1 )
		local bHaveImpact1_1 = IsHaveSpecificImpact( sceneId, humanId, buffId1_1 )
		local bHaveImpact2 = IsHaveSpecificImpact( sceneId, humanId, buffId2 )
			
		local nLevel = GetLevel(sceneId, humanId)
		if bHaveImpact1>0 or bHaveImpact1_1 > 0 then
			local nMoney = nLevel*4
			local strMoney = x700212_GetMoneyName(sceneId,nMoney)
			local str = format("江湖请柬使您额外获得%s的现银",strMoney)
			AddMoney(sceneId, humanId, 0, nMoney)
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId,str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, humanId);
		end

		if bHaveImpact2>0 then
			local nMoney = nLevel*2
			local strMoney = x700212_GetMoneyName(sceneId,nMoney)
			local str = format("你有朝廷请柬，获得%s的银卡",strMoney)
			AddMoney(sceneId, humanId, 1, nMoney)
			BeginQuestEvent(sceneId);
				AddQuestText(sceneId,str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, humanId);
		end
		
	end

	----------------------------------- 周卡end ----------------------------------
	

	
	local objId1 = GetFubenData_Param(sceneId, x700212_CSP_BOSS1_ID)
	local objId2 = GetFubenData_Param(sceneId, x700212_CSP_BOSS2_ID)
	if objId1 == selfId then
		
		
		SetFubenData_Param(sceneId, x700212_CSP_BOSS1_ID, -1)
		
		NpcTalk(sceneId, selfId, "#R这……这不可能……我……还没有使出全力……", -1)
		

		--//--------------------------- 世界喊话 Start--------------------
		--杀死boss1
--		local nowTickCount = GetFubenData_Param(sceneId, x700212_CSP_TICKCOUNT)

--		local nowTime = x700212_g_TickTime* nowTickCount;

--		local nMinute = floor(nowTime/60)
--		local nSec = mod(nowTime,60)

			
--		local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--		local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--		local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件

		
		
--		--LuaAllScenceM2Wrold (sceneId,"#R十分让人吃惊！横扫金矿洞仅用#G"..strKillTime.."#R时间的团队，是以#G"..strPlayerName.."#R为核心的队伍！", 0, 1)
		
		
		--//--------------------------- 世界喊话 end----------------------

	elseif objId2 == selfId then
		SetFubenData_Param(sceneId, x700212_CSP_BOSS2_ID, -1)
		x700212_CreateSubmitNpc( sceneId)

		
		NpcTalk(sceneId, selfId, "#R我会……再回来的……", -1)
	
		for	i = 0, 6 - 1 do
			SetFubenData_Param(sceneId, x700212_CSP_B_GATHERED_START+i,0);
		end

		local x,z =GetWorldPos(sceneId,selfId)
		SetGrowPointPos(sceneId,x700212_g_nGrowpointType,x,z)
		SetGrowPointIntervalContainer(sceneId,x700212_g_nGrowpointType,1)
		x700212_ShowTipsToAll(sceneId, "地上出现了一个奇异的箱子！")
--		--//--------------------------- 世界喊话 Start--------------------
--		--杀死boss2
--		local nowTickCount = GetFubenData_Param(sceneId, x700212_CSP_TICKCOUNT)
--
--		local nowTime = x700212_g_TickTime* nowTickCount;
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
--		----LuaAllScenceM2Wrold (sceneId,"#R金矿内的地穴恐惧魔在一声绝望地哀嚎中倒下，#G"..strPlayerName.."#R所带领的队伍用了#G"..strKillTime.."#R时间就消灭了这个恐怖的魔头，解救了被困的矿工！", 0, 1)
--		
--		
--		--//--------------------------- 世界喊话 end----------------------


	end
end

function x700212_ShowTipsToAll(sceneId, str)

	local humancount = GetFuben_PlayerCount(sceneId);

	--通知玩家
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		BeginQuestEvent(sceneId);
			AddQuestText(sceneId,str);
		EndQuestEvent();
		DispatchQuestTips(sceneId, humanId);
	end
end

function x700212_OnAllMonsterDead( sceneId)
	x700212_CreateSubmitNpc( sceneId)
end

function x700212_CreateSubmitNpc( sceneId)

	local nRet
	if x700212_g_SubmitNPC.title~="" then
		nRet = CreateMonster(sceneId, x700212_g_SubmitNPC.type, x700212_g_SubmitNPC.x, x700212_g_SubmitNPC.z, 3, 0, -1, x700212_g_SubmitNPC.guid, -1,-1,x700212_g_SubmitNPC.facedir,  "",x700212_g_SubmitNPC.title)
	else
		nRet = CreateMonster(sceneId, x700212_g_SubmitNPC.type, x700212_g_SubmitNPC.x, x700212_g_SubmitNPC.z, 3, 0, -1, x700212_g_SubmitNPC.guid, -1,-1,x700212_g_SubmitNPC.facedir)
	
	end

	SetFubenData_Param(sceneId, x700212_CSP_NPC_ID, nRet )
	SetFubenData_Param(sceneId, x700212_CSP_NPC_STATUS, 1 )
end





--------------------------------------------------------------------------------------
-- 生长点脚本
--------------------------------------------------------------------------------------


function x700212_OnCreate(sceneId,growPointType,x,y)
	
	local ItemBoxId = ItemBoxEnterScene(x, y, growPointType, sceneId, 0, -1)

end



function x700212_OnOpen(sceneId,selfId,targetId)
	
	return 0;
	
end

function x700212_OnRecycle(sceneId,selfId,targetId)
	
	return 0;
	--return CallScriptFunction( MISSION_SCRIPT, "OnRecycle", sceneId, selfId, targetId, x700212_g_GrowpointId, x700212_g_ItemIndex )
end



function x700212_OnProcOver(sceneId,selfId,targetId)
	-- 采集完毕
	
	

	
	x700212_OnAnwer(sceneId,selfId)
	

	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end


function x700212_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)

	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


function x700212_OnAnwer(sceneId,selfId)

	local myGuid = GetPlayerGUID( sceneId,selfId )
	myGuid = format("%u", myGuid)

	

	for i=0, 5 do
        local paramidx = x700212_CSP_GUID_START + i
        local nGUID = GetFubenData_Param(sceneId, paramidx  )
		nGUID = format("%u", nGUID)
		
		

        if nGUID == myGuid then

			local bGathered = GetFubenData_Param(sceneId, x700212_CSP_B_GATHERED_START+i);
			
			local str = ""

			if bGathered<=0 then
				SetFubenData_Param(sceneId, x700212_CSP_B_GATHERED_START+i,1);
				
				local bGuoyun =GetFubenData_Param(sceneId, x700212_CSP_B_GUOYUN_START+i);
				local nMoney = x700212_GetMyMoneyBonus(sceneId,selfId,bGuoyun);
				
				
				local strMoney = x700212_GetMoneyName(sceneId,nMoney)
				str = format("获得%s的银卡",strMoney)
				
				AddMoney(sceneId, selfId, 1, nMoney)
			else
				str = "您只能采集一次！"
			end

			BeginQuestEvent(sceneId);
				AddQuestText(sceneId,str);
			EndQuestEvent();
			DispatchQuestTips(sceneId, selfId);
			break;
           
        end
    end
end


function x700212_GetMyMoneyBonus(sceneId,selfId,bGuoyun)

	local nLevel = GetLevel(sceneId,selfId)

	local nCount = nLevel*400


--	if bGuoyun==1 then
--		nCount = nLevel*(80*3+random(-10,10))
--	end

	
	return nCount;
end


function x700212_GetMoneyName(sceneId,nMoney)
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

--//added in 2009-3-17
---------------------------------------------------------------------------------------------------
--进入区域
---------------------------------------------------------------------------------------------------
function x700212_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700212_ProcAreaLeaved( sceneId, selfId, ScriptId, MissionId )
end
--//add end






