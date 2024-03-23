---------------------------------------------------

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700091_CSP_FUBENTYPE				= 	0
x700091_CSP_SCRIPTID				=	1
x700091_CSP_TICKCOUNT				= 	2
x700091_CSP_FROMSCENEID				= 	3
x700091_CSP_ISCLOSING				= 	4
x700091_CSP_LEAVECOUNTDOWN			= 	5
x700091_CSP_TEAMID					=	6
x700091_CSP_BACKSCENEX       		=   7
x700091_CSP_BACKSCENEZ      		=   8
x700091_CSP_FUBENLEVEL				=	9
x700091_CSP_NPCID					=   10
x700091_CSP_KILLCOUNT				=	20
x700091_CSP_FUBEN_SCENE_ID			=	21


x700091_CSP_BOSS_ID					=	22

x700091_CSP_FINALBOSS_ID			=	25
x700091_CSP_FINALBOSS_FULL_HP		=   26
x700091_CSP_AREA_ID					=	27
x700091_CSP_AREA_FLAG				=	28
x700091_CSP_ADDHP_MONSTER_ID1		=	31		--对应怪物C
x700091_CSP_ADDHP_MONSTER_ID2		=	32		--对应怪物C
x700091_CSP_ADDHP_MONSTER_ID3		=	33		--对应怪物C
x700091_CSP_ADDHP_MONSTER_ID4		=	34		--对应怪物C



--Boss2和Boss3血量每减少10%都会有1%的概率触发刷新怪物C
x700091_CSP_BOSS_ID2_HPINDEX		=   40  
x700091_CSP_BOSS_ID3_HPINDEX		=   41

x700091_CSP_SELFEXPLODE_MONSER_NUM		=   30  --自爆怪个数
x700091_CSP_SELFEXPLODE_MONSER_STARTID	=   51  --自爆怪ID  --预留30个！！
x700091_CSP_SELFEXPLODE_MONSER_ENDID	=   80  --自爆怪ID  
	
x700091_CSP_RANDOM_BOSS_ID			=	233
x700091_RANDOMBOSS_FLAG				=	234

x700091_CSP_XIANJINBOSS				=	239

x700091_CSP_HUMAN_COUNT				=	240
x700091_CSP_PLAYER_ENTER_START		=	241

x700091_CSP_OBJID_START				=	247
x700091_CSP_GUID_START              =   248

x700091_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型
x700091_CSP_FUBEN_MODE				=   255 


x700091_g_RandomMonsterRate			= 0.1                       --隐藏boss出现几率
x700091_g_RandomMonsterRateZHOUSANFAN			= 67                      --隐藏boss出现几率 百分之几!

------------------------Scene System Setting -----------------------------------
x700091_g_GutMonsterArea       =   { x1 =40,z1= 60,x2 = 60, z2= 90 }

x700091_g_ScriptId 					= 700091
x700091_g_MissionId					= 6608

x700091_g_SubmitNPC       =   { type =28516,guid= 150560,x = 106, z=39, facedir =0, title = "" }

x700091_g_TalkNpcID  = 150558
x700091_g_NpcTalk = 	{
												"不死战神在等待着你们！"		,	
												"谁也别想抢走我的功劳，我得不到的你们也别想得到！"			,
												"接受我不死的诅咒吧"			,
												"我的主人，别担心，只要我在就没人可以伤害到你！"		,	
												"我的守卫呢？难道都已经…我要为他们报仇！！！！！"		,	
						}
											
x700091_g_ExitPos					= { sceneId = {50,50,50,50}, x=100, z=100, scriptId=x700091_g_ScriptId }					  
x700091_g_NextFuben					= 49

------------------------------------------挑战副本任务
x700091_g_AddHPDeadFirst			=  0  --第一个加血怪死的时间
x700091_g_AddHPDeadFinal			=  0  --最后一个加血怪死的时间
x700091_g_EnterTick					=  0  --最后一个加血怪死的时间
-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------



function x700091_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
	--print("x700091_ProcEventEntry",selfId)
	-- SetFubenData_Param(sceneId, x700091_CSP_GUT_BOSS_ID )

end




function x700091_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700091_ShowTipsToAll(sceneId, str)

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

-----------------------------------------------------------
--*********************************************************
--OnFubenSceneCreated  :  当副本创建成功时， 开始刷怪和npc
--*********************************************************
-----------------------------------------------------------
function x700091_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	--print("x700091_OnFubenSceneCreated")
	SetFubenData_Param(sceneId, x700091_CSP_XIANJINBOSS, -1 )
	

	local humancount = GetFuben_PlayerCount(sceneId)
	SetFubenData_Param(sceneId, x700091_CSP_HUMAN_COUNT, humancount)
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		SetFubenData_Param(sceneId, x700091_CSP_PLAYER_ENTER_START+i, humanId)
	end
	
	for i = x700091_CSP_SELFEXPLODE_MONSER_STARTID, x700091_CSP_SELFEXPLODE_MONSER_STARTID+x700091_CSP_SELFEXPLODE_MONSER_NUM do
		SetFubenData_Param(sceneId, i, 0)
	end
	
	SetFubenData_Param(sceneId, x700091_CSP_BOSS_ID2_HPINDEX, 9)
	SetFubenData_Param(sceneId, x700091_CSP_BOSS_ID3_HPINDEX, 9)
	SetFubenData_Param(sceneId, x700091_CSP_BOSS_ID, 0)	
	--SetFubenData_Param(sceneId, x700091_CSP_BOSS_FULL_HP, 0)	
	SetFubenData_Param(sceneId, x700091_CSP_FINALBOSS_ID, -1)	
	SetFubenData_Param(sceneId, x700091_CSP_FINALBOSS_FULL_HP, 0)	
	
	--SetFubenData_Param(sceneId, x700091_CSP_GUT_BOSS_ID, 0)	
	SetFubenData_Param(sceneId, x700091_CSP_SELFEXPLODE_MONSER_NUM, 0)

	
	SetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID1, 0)
	SetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID2, 0)
	SetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID3, 0)
	SetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID4, 0)	
		
	
	x700091_CreateMonster( sceneId )
	x700091_CreateAddHPMonster(sceneId)
	x700091_CreateBoss( sceneId )
	x700091_CreateFinalBoss( sceneId )

	
		
end


function x700091_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	--print("x700091_ProcAreaEntered",selfId,zoneId,MissionId)

	--@param sceneId: 场景Id
	--@param selfId: 玩家ObjId (宠物进入EnterArea也会触发这个时间)
	--@param zoneId: 区域Id
	--@param MissionId: 任务id\
	
	SetFubenData_Param(sceneId, x700091_CSP_AREA_ID, zoneId)
	local countryId = GetCurCountry( sceneId, selfId )
	
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700091_CSP_FINALBOSS_ID )
		if BossId ~= -2 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700091_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700091_g_MissionId, x700091_g_ScriptId)
		
	else
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700091_g_MissionId, x700091_g_ScriptId)
	end

end

---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700091_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	SetFubenData_Param(sceneId, x700091_CSP_AREA_ID, -1)
--@param sceneId: 场景Id
--@param selfId: 玩家ObjId (宠物进入EnterArea也会触发这个时间)
--@param zoneId: 区域Id
--@param MissionId: 任务id

	--print("x700091_ProcAreaLeaved"..zoneId.." "..MissionId)
	--local fubenArea = GetFubenData_Param(sceneId, x700091_CSP_FUBENAREA )
	--if zoneId == fubenArea then
	--	SetFubenData_Param(sceneId, x700091_CSP_FUBENAREA,0)
	--end
		
	

end
---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
function x700091_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	local zoneId = GetFubenData_Param(sceneId, x700091_CSP_AREA_ID )
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700091_CSP_FINALBOSS_ID )
		if BossId ~= -2 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700091_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700091_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700091_g_MissionId, x700091_g_ScriptId)
		
	else
	 	--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700091_g_MissionId, x700091_g_ScriptId)
	end
end
--//add end

function x700091_EnterTick(sceneId, nowTickCount)
	x700091_g_EnterTick = nowTickCount
	if nowTickCount == 3 then
		local objID = FindMonsterByGUID(sceneId,x700091_g_TalkNpcID)
		NpcTalk( sceneId,objID, x700091_g_NpcTalk[1], -1)
		--print("x700091_EnterTick00000000000000000000",a)
	end
	if mod(nowTickCount,5) == 0 then
	end
		
	if nowTickCount == 5 then
		local id = GetFubenData_Param( sceneId, x700091_CSP_NPCID)
		NpcTalk( sceneId, id, x700091_g_NpcTalk[1], -1)
		--print("x700091_EnterTick00000000000000000000", nowTickCount, id)
	end
	
	local BossID = GetFubenData_Param(sceneId, x700091_CSP_BOSS_ID)
	local FinalBossID = GetFubenData_Param(sceneId, x700091_CSP_FINALBOSS_ID)
	
	local addHPMonID1 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID1)
	local addHPMonID2 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID2)
	local addHPMonID3 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID3)
	local addHPMonID4 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID4)


	if addHPMonID1 == 1 and addHPMonID2 == 1 and addHPMonID3 == 1 and addHPMonID4 == 1 and FinalBossID >= 0 and NpcIsTalk == 0  then
		SetFubenData_Param( sceneId, x700091_CSP_NPC_IS_TALK, 1)
		NpcTalk( sceneId, FinalBossID, x700091_g_NpcTalk[5], -1)
	elseif (addHPMonID1 ~= 0 or addHPMonID2 ~= 0 or addHPMonID3 ~= 0 or addHPMonID4 ~= 0 ) and FinalBossID >= 0 then   --BOSS没死
		
		local nCurrentHp = GetHp( sceneId, FinalBossID )
		local nFullHp = GetFubenData_Param(sceneId, x700091_CSP_FINALBOSS_FULL_HP )
		
		if nCurrentHp/nFullHp <= 0.9 then
			SetHp(sceneId, FinalBossID, nFullHp)
			if addHPMonID1 ~= 0 then
				NpcTalk( sceneId, addHPMonID1, x700091_g_NpcTalk[4], -1)
			elseif addHPMonID2 ~= 0 then
				NpcTalk( sceneId, addHPMonID2, x700091_g_NpcTalk[4], -1)
			elseif addHPMonID3 ~= 0 then
				NpcTalk( sceneId, addHPMonID3, x700091_g_NpcTalk[4], -1)
			elseif addHPMonID4 ~= 0 then
				NpcTalk( sceneId, addHPMonID4, x700091_g_NpcTalk[4], -1)
			end
		
		end
	end
	
	

	
end	
	

function x700091_CreateFinalBoss(sceneId)  
	local nFubenType = GetFubenData_Param(sceneId, x700091_CSP_FUBEN_TYPE)
	local fubenlevel = GetFubenData_Param(sceneId, x700091_CSP_FUBENLEVEL ) 
	local nIndexFrom = GetFubenDataPosByScriptID(x700091_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700091_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700091_g_ScriptId,nIndexFrom,i)
		if idScript == x700091_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel  and flag3 == nFubenType then
		  	local nRet = 0
		  	--print("title",title)
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700091_g_ScriptId, -1, 21,-1, facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700091_g_ScriptId, -1, 21,-1, facedir)
			end
				
			
			SetFubenData_Param(sceneId, x700091_CSP_FINALBOSS_ID, nRet )
			local nFullHp = GetHp( sceneId, nRet )
			SetFubenData_Param(sceneId, x700091_CSP_FINALBOSS_FULL_HP, nFullHp )
			
			--NpcTalk( sceneId, nRet, x700091_g_NpcTalk[7], -1)
			
			
    	end
	end
end

function x700091_CreateBoss(sceneId)

	local nFubenType = GetFubenData_Param(sceneId, x700091_CSP_FUBEN_TYPE)
	local fubenlevel = GetFubenData_Param(sceneId, x700091_CSP_FUBENLEVEL ) 

	
	local nIndexFrom = GetFubenDataPosByScriptID(x700091_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700091_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700091_g_ScriptId,nIndexFrom,i)
		if idScript == x700091_g_ScriptId and levelmin <= fubenlevel and levelmax >= fubenlevel and flag3 == nFubenType then
			if monsterFlag == 3 then
			  	local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700091_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700091_g_ScriptId, -1, 21,-1, facedir)
				end
				
--				if monsterFlag == 4 then
--					SetFubenData_Param(sceneId, x700091_CSP_BOSS_ID2, nRet )
--					local nFullHp = GetHp( sceneId, nRet )
--					SetFubenData_Param(sceneId, x700091_CSP_BOSS_FULL_HP2, nFullHp )
--				elseif monsterFlag == 5 then
--					SetFubenData_Param(sceneId, x700091_CSP_BOSS_ID3, nRet )
--					local nFullHp = GetHp( sceneId, nRet )
--					SetFubenData_Param(sceneId, x700091_CSP_BOSS_FULL_HP3, nFullHp )
--				end
	
		
				
			end
		end
    end
end

function x700091_CreateAddHPMonster(sceneId)
	local fubenlevel = GetFubenData_Param(sceneId, x700091_CSP_FUBENLEVEL ) 
	local nFubenType = GetFubenData_Param(sceneId, x700091_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700091_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700091_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700091_g_ScriptId,nIndexFrom,i)
		if idScript == x700091_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel  and flag3 == nFubenType then
			 for j=0,count -1 do

                local rx = random(-r,r)
                local x = x1 + rx
                local rz = random(-r,r)
                local z = z1 + rz
		        local MonId = 0
				if title~="" then
					MonId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700091_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					MonId = CreateMonster(sceneId, type, x, z, ai, aiscript, x700091_g_ScriptId, -1, 21,-1,facedir)
				--print("Gut",title)
				end
				
				local addHPMonID1 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID1)
				local addHPMonID2 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID2)
				local addHPMonID3 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID3)
				local addHPMonID4 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID4)
				if addHPMonID1 == 0 then
					SetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID1,  MonId) 
				elseif addHPMonID2 == 0 then
					SetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID2,  MonId) 
				elseif addHPMonID3 == 0 then
					SetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID3,  MonId) 
				elseif addHPMonID4 == 0 then
					SetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID4,  MonId) 		
				end
				
            end
        end
	end
end




---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700091_CreateMonster(sceneId)

	--print("x700091_CreateMonster")
    local fubenlevel = GetFubenData_Param(sceneId, x700091_CSP_FUBENLEVEL ) 
    local nFubenType = GetFubenData_Param(sceneId, x700091_CSP_FUBEN_TYPE)

	local nIndexFrom = GetFubenDataPosByScriptID(x700091_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700091_g_ScriptId )
	--print("x700091_CreateMonster=nDataCount="..nDataCount)
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700091_g_ScriptId,nIndexFrom,i)
		--print("x700091_CreateMonster="..levelmin.." "..levelmax)
		if idScript == x700091_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel  and flag3 == nFubenType then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x1 + rx
                local rz = random(-r,r)
                local z = z1 + rz
				if title~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, x700091_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, x700091_g_ScriptId, -1, 21,-1,facedir)
				
				end
				--print("Monster0")
			end
        end
        if idScript == x700091_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel  and flag3 == nFubenType then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x1 + rx
                local rz = random(-r,r)
                local z = z1 + rz
                local selfExplodeID = 0
				if title~="" then
					selfExplodeID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700091_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					selfExplodeID = CreateMonster(sceneId, type, x, z, ai, aiscript, x700091_g_ScriptId, -1, 21,-1,facedir)
				
				end
				
				local num = GetFubenData_Param(sceneId, x700091_CSP_SELFEXPLODE_MONSER_NUM )
				SetFubenData_Param(sceneId, x700091_CSP_SELFEXPLODE_MONSER_STARTID+num, selfExplodeID)
				SetFubenData_Param(sceneId, x700091_CSP_SELFEXPLODE_MONSER_NUM, num + 1)
				--print("Monster1")
			end
        end
	end

end

function x700091_IsMonsterB(sceneId, monsterId)
	for i = x700091_CSP_SELFEXPLODE_MONSER_STARTID, x700091_CSP_SELFEXPLODE_MONSER_STARTID+x700091_CSP_SELFEXPLODE_MONSER_NUM do
		local id = GetFubenData_Param(sceneId, i)
		if id ~= -1 and id == monsterId then
			return i
		end
	end
	
	return -1
end

function x700091_SetAddHPMonDieTime(sceneId, selfId)
	local addHPMonID1 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID1)	
	local addHPMonID2 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID2)	
	local addHPMonID3 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID3)	
	local addHPMonID4 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID4)	
	
	if x700091_g_AddHPDeadFirst == 0 then
		x700091_g_AddHPDeadFirst = x700091_g_EnterTick
	end
	if 	addHPMonID1 == 0 and addHPMonID2 == 0 and addHPMonID3 == 0 and addHPMonID4 == 0 then
		x700091_g_AddHPDeadFinal = x700091_g_EnterTick
	end	
end

function x700091_OnDie(sceneId, selfId, killerId)
		
	local PlayerID = GetFubenData_Param(sceneId, x700091_CSP_PLAYER_ENTER_START)
	
	local BossID = GetFubenData_Param(sceneId, x700091_CSP_BOSS_ID)	
	local FinalBossID = GetFubenData_Param(sceneId, x700091_CSP_FINALBOSS_ID)	

	local addHPMonID1 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID1)	
	local addHPMonID2 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID2)	
	local addHPMonID3 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID3)	
	local addHPMonID4 = GetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID4)	

	local xianjinboss = GetFubenData_Param(sceneId, x700091_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	
	local index = x700091_IsMonsterB(sceneId, selfId)
	if index ~= -1 then
--		local ran = random(1, 5)
--		if ran == 1 then
--			local Num =  GetNearObjCount(sceneId, PlayerID, 10, 0, selfId)
--			for i = 0, Num-1 do
--				local ObjId = GetNearMonster(sceneId, PlayerID,i)
--				local CurHp = GetHp( sceneId, ObjId )
--			
--				SetHp( sceneId, ObjId, - (CurHp - 1) )
--			end	
--		end
--		SetFubenData_Param(sceneId, index, 0)	
		
	elseif BossID == selfId then
		SetFubenData_Param(sceneId, x700091_CSP_BOSS_ID, 0)
	elseif FinalBossID == selfId then
		SetFubenData_Param(sceneId, x700091_CSP_FINALBOSS_ID, -2)
		x700091_OnFubenEnd( sceneId)
		x700091_ShowTipsToAll(sceneId, "成功击杀圣路易，副本完成。")
	elseif addHPMonID1 == selfId then
		SetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID1, 0)
		x700091_SetAddHPMonDieTime(sceneId, selfId)
	elseif addHPMonID2 == selfId then
		SetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID2, 0)
		x700091_SetAddHPMonDieTime(sceneId, selfId)
	elseif addHPMonID3 == selfId then
		SetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID3, 0)
		x700091_SetAddHPMonDieTime(sceneId, selfId)
	elseif addHPMonID4 == selfId then
		SetFubenData_Param(sceneId, x700091_CSP_ADDHP_MONSTER_ID4, 0)		
		x700091_SetAddHPMonDieTime(sceneId, selfId)
	end
	
	
	--// add for random boss event, add in 2009-5-20
	local nRandomBossId = GetFubenData_Param(sceneId, x700091_CSP_RANDOM_BOSS_ID)

	if nRandomBossId ~= 0 then
		if nRandomBossId==selfId then
			--//--------------------------- 世界喊话 Start--------------------
			--杀死Random boss
			
			
			-------- if killed by pet -----------------
			local nKillerType = GetObjType(sceneId, killerId)
			local nOwnerId = killerId
			if nKillerType== 3 then
				nOwnerId = GetOwnerID(sceneId, killerId)
				
			end
			--------- end -------------------------------
			local strPlayerName = GetName(sceneId, nOwnerId)
			
			local nCountry = GetCurCountry( sceneId, nOwnerId )
			local strCountryName = "";
			if nCountry==0 then
				strCountryName = "楼兰"
			elseif nCountry==1 then
				strCountryName = "天山"
			elseif nCountry==2 then
				strCountryName = "昆仑"
			elseif nCountry==3 then
				strCountryName = "敦煌"
			end

			local strHorseName = ""

			local nHorseFlag = GetFubenData_Param(sceneId, x700091_RANDOMBOSS_FLAG);
			local fubenlevel = GetFubenData_Param(sceneId, x700091_CSP_FUBENLEVEL )
			
			if fubenlevel < 50 then
				if nHorseFlag==0 then
					strHorseName = "凶豹"
				elseif nHorseFlag==1 then
					strHorseName = "奔羚"
				elseif nHorseFlag==2 then
					strHorseName = "天鹅"
				elseif nHorseFlag==3 then
					strHorseName = "河马"
				end
			elseif fubenlevel < 70 then
				if nHorseFlag==0 then
					strHorseName = "烈狮"
				elseif nHorseFlag==1 then
					strHorseName = "驯鹿"
				elseif nHorseFlag==2 then
					strHorseName = "瑞鹤"
				elseif nHorseFlag==3 then
					strHorseName = "铁犀"
				end
			elseif fubenlevel < 80 then
				if nHorseFlag==0 then
					strHorseName = "剑齿虎"
				elseif nHorseFlag==1 then
					strHorseName = "蛮牛"
				elseif nHorseFlag==2 then
					strHorseName = "凤凰"
				elseif nHorseFlag==3 then
					strHorseName = "猛犸"
				end
			elseif fubenlevel < 110 then
				if nHorseFlag==0 then
					strHorseName = "虬龙"
				elseif nHorseFlag==1 then
					strHorseName = "应龙"
				elseif nHorseFlag==2 then
					strHorseName = "暴龙"
				elseif nHorseFlag==3 then
				strHorseName = "奎龙"
				end
			elseif fubenlevel < 130 then
				if nHorseFlag==0 then
					strHorseName = "虬龙"
				elseif nHorseFlag==1 then
					strHorseName = "应龙"
				elseif nHorseFlag==2 then
					strHorseName = "暴龙"
				elseif nHorseFlag==3 then
					strHorseName = "奎龙"
				end
			else
				if nHorseFlag==0 then
					strHorseName = "虬龙"
				elseif nHorseFlag==1 then
					strHorseName = "应龙"
				elseif nHorseFlag==2 then
					strHorseName = "暴龙"
				elseif nHorseFlag==3 then
					strHorseName = "奎龙"
				end
			end



			local strMapName = "景教堂"
			
			LuaAllScenceM2Wrold (sceneId,strCountryName.."的"..strPlayerName.."打败了"..strMapName.."的九旄战神，九旄丢下"..strHorseName.."落荒而逃！", 5, 1)
			
			
			--//--------------------------- 世界喊话 end----------------------
		end
	end
end

function x700091_OnFubenEnd( sceneId)
	--x700091_CreateSubmitNpc(sceneId)
	x700091_CreateXianJinBoss(sceneId)
	--x700091_CreateRandomMonster(sceneId)
	local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,60 )
	end	
end

function x700091_CreateSubmitNpc( sceneId)
	if x700091_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700091_g_SubmitNPC.type, x700091_g_SubmitNPC.x, x700091_g_SubmitNPC.z, 3, 0, -1, x700091_g_SubmitNPC.guid, -1,-1,x700091_g_SubmitNPC.facedir,  "",x700091_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700091_g_SubmitNPC.type, x700091_g_SubmitNPC.x, x700091_g_SubmitNPC.z, 3, 0, -1, x700091_g_SubmitNPC.guid, -1,-1,x700091_g_SubmitNPC.facedir)
	
	end

	CallScriptFunction( 701110, "OnSceneBossDie", sceneId, 2)
	
	if x700091_g_AddHPDeadFinal - x700091_g_AddHPDeadFirst <= 10 then --10秒内
		CallScriptFunction( 701111, "OnSceneBossDie", sceneId, 2)
	end
	
	CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)
	

end
----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700091_CreateXianJinBoss(sceneId)
	local nFubenType = GetFubenData_Param(sceneId, x700091_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700091_CSP_FUBEN_MODE)

	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700091_CSP_FUBENLEVEL ) 
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700091_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700091_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700091_g_ScriptId,nIndexFrom,i)
		if idScript == x700091_g_ScriptId and monsterFlag == 6 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700091_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700091_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700091_CSP_XIANJINBOSS, nRet )
			--print("x700091_CreateXianJinBoss",x,z)
		end
	end

	x700091_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end




