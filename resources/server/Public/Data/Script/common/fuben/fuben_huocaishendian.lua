---------------------------------------------------
-- File: 700003_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700003_CSP_FUBENTYPE				= 	0
x700003_CSP_SCRIPTID				=	1
x700003_CSP_TICKCOUNT				= 	2
x700003_CSP_FROMSCENEID				= 	3
x700003_CSP_ISCLOSING				= 	4
x700003_CSP_LEAVECOUNTDOWN			= 	5
x700003_CSP_TEAMID					=	6
x700003_CSP_BACKSCENEX       		=   7
x700003_CSP_HOLDTIME      		=   8
x700003_CSP_FUBENLEVEL			=	9

x700003_CSP_KILLCOUNT				=	20
x700003_CSP_BOSS1_ID				=	21
x700003_CSP_BOSS2_ID				=	22
x700003_CSP_NPC_ID					=	23
x700003_CSP_B_PAO_OVER				=	24
x700003_CSP_PAO_STATUS				=	25
x700003_CSP_FUBEN_SCENE_ID			=	26
x700003_CSP_PAO_TICKCOUNT			=	27


x700003_CSP_B_GETBONUS_START		=	230

x700003_CSP_XIANJINBOSS				=	239


x700003_CSP_HUMAN_COUNT				=	240
x700003_CSP_OBJID_START				=	241
x700003_CSP_GUID_START              =   248  --空6个
x700003_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型

x700003_CSP_FUBEN_MODE				=   255 

------------------------Scene System Setting -----------------------------------

x700003_g_ScriptId 					= 700003


x700003_g_LimitTotalHoldTime		= 	720						--副本可以存活的时间（单位：次数）,如果此时间到了，则任务将会失败
x700003_g_PaoTaiHoldTime			=	15*12					-- 炮台时间

x700003_g_SubmitNPC                 =   { type =25072,guid= 150535,x = 35, z=31, facedir =0, title="" }     -- 整齐的npc
x700003_g_SubmitNPC1                =   { type =25072,guid= 150535,x = 35, z=31, facedir =0, title="" }	 -- 破烂的沈万三npc	
x700003_g_NpcGroup                  =   {
                                            {   type = 25034,x=22,z=107,ai=3,aiscript = 0,guid=150534,facedir =0, title=""},
                                        }


										






-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700003_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
	
end



function x700003_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700003_ShowTipsToAll(sceneId, str)

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
function x700003_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	SetFubenData_Param(sceneId, x700003_CSP_XIANJINBOSS, -1 )
	x700003_CreateBoss( sceneId,0 )
    x700003_CreateMonster1( sceneId )
	x700003_CreateNpc(sceneId )

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		 x700003_AddPlayerBuff(sceneId, humanId,1)
	end
		
end

function x700003_OnHuoPaoOver(sceneId, nStatus)
	if nStatus ~= 1 and nStatus~=2  then
		return -1;
	
	end

	local objId1 = GetFubenData_Param(sceneId, x700003_CSP_BOSS1_ID);
	if objId1>=0 then
		DeleteMonster( sceneId, objId1);
	--else
		--return
	end

	SetFubenData_Param(sceneId, x700003_CSP_PAO_STATUS, nStatus )  --// 1:超时, 2: 完成
	SetFubenData_Param(sceneId, x700003_CSP_B_PAO_OVER, 1 ) ;
	
	local nowTick = GetFubenData_Param(sceneId, x700003_CSP_TICKCOUNT);
	SetFubenData_Param(sceneId,x700003_CSP_PAO_TICKCOUNT,nowTick);

	local str="";

	if nStatus==1 then
		str	= "你未能成功阻止火炮攻击！"
		x700003_CreateBoss(sceneId, 1)
	else
		str = "火炮成功的被摧毁了！"
		x700003_CreateMonster2(sceneId)
		x700003_CreateBoss(sceneId, 1)

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



function x700003_AddPlayerBuff(sceneId, selfId, nFlag)
	
end

function x700003_OnStartHuoPaoTime(sceneId)
	
	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		
		
	end
	
end

function x700003_EnterTick(sceneId, nowTickCount)
	if nowTickCount == 2 then
		local nTalkNpcId = GetFubenData_Param(sceneId, x700003_CSP_NPC_ID ) ;
		if nTalkNpcId>0 then
			NpcTalk(sceneId, nTalkNpcId, "那群叛军在山顶架设了火炮，你们快去摧毁它！",  -1)
			x700003_OnStartHuoPaoTime(sceneId);

		end
	end

--        x700003_CheckAllMemberState( sceneId )

	--副本计时器
	local bPaoTimeOver = GetFubenData_Param(sceneId, x700003_CSP_B_PAO_OVER ) ;
	if bPaoTimeOver==0 then
		-- 如果炮台时间到
		if nowTickCount >= x700003_g_PaoTaiHoldTime then
			
			bPaoTimeOver = 1;
			
			x700003_OnHuoPaoOver(sceneId, 1)
		end
	end


	if bPaoTimeOver==0 then	
		SetFubenData_Param(sceneId, x700003_CSP_HOLDTIME, x700003_g_PaoTaiHoldTime);
	else
		SetFubenData_Param(sceneId, x700003_CSP_HOLDTIME, x700003_g_LimitTotalHoldTime);
	end
end

---------------------------------------------------------------------------------------------------
--创建BOSS
---------------------------------------------------------------------------------------------------
function x700003_CreateBoss(sceneId, nFlag)

    local fubenlevel = GetFubenData_Param(sceneId, x700003_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700003_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700003_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700003_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700003_g_ScriptId,nIndexFrom,i)
		if idScript == x700003_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    if flag == nFlag then
				local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700003_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700003_g_ScriptId, -1, 21,-1,facedir)
				
				end

				if flag ==0 then
					SetFubenData_Param(sceneId, x700003_CSP_BOSS1_ID,nRet  )
				elseif flag ==1 then
					SetFubenData_Param(sceneId, x700003_CSP_BOSS2_ID,nRet  )
				end
			end
        end
	end

end

---------------------------------------------------------------------------------------------------
--创建炮台消失之前Monster
---------------------------------------------------------------------------------------------------
function x700003_CreateMonster1(sceneId)

    local fubenlevel = GetFubenData_Param(sceneId, x700003_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700003_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700003_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700003_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700003_g_ScriptId,nIndexFrom,i)
		if idScript == x700003_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x1 = x + rx
                local rz = random(-r,r)
                local z1 = z + rz

				if title~="" then
					CreateMonster(sceneId, type, x1, z1, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					CreateMonster(sceneId, type, x1, z1, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
			end
        end
	end

end

---------------------------------------------------------------------------------------------------
--创建炮台小时之后Monster
---------------------------------------------------------------------------------------------------
function x700003_CreateMonster2(sceneId)

    local fubenlevel = GetFubenData_Param(sceneId, x700003_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700003_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700003_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700003_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700003_g_ScriptId,nIndexFrom,i)
		if idScript == x700003_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x1 = x + rx
                local rz = random(-r,r)
                local z1 = z + rz

				if title~="" then
					CreateMonster(sceneId, type, x1, z1, ai, aiscript, -1, -1, 21,-1,facedir, "",title)
				else
					CreateMonster(sceneId, type, x1, z1, ai, aiscript, -1, -1, 21,-1,facedir)
					
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
function x700003_CreateNpc(sceneId )

    for i, item in x700003_g_NpcGroup do
        local nRet = 0
		if item.title~="" then
			nRet = CreateMonster( sceneId,item.type,item.x,item.z,item.ai,item.aiscript,-1,item.guid,-1,-1,item.facedir, "",item.title)
		else
			nRet = CreateMonster( sceneId,item.type,item.x,item.z,item.ai,item.aiscript,-1,item.guid,-1,-1,item.facedir)
		
		end
		SetFubenData_Param(sceneId, x700003_CSP_NPC_ID,nRet ) ;
    end
end


function x700003_OnDie(sceneId, selfId, killerId)

	local xianjinboss = GetFubenData_Param(sceneId, x700003_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	
	
	local nDieCount = GetFubenData_Param(sceneId, x700003_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700003_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	


	local objId1 = GetFubenData_Param(sceneId, x700003_CSP_BOSS1_ID);
	local objId2 = GetFubenData_Param(sceneId, x700003_CSP_BOSS2_ID);

	
	local name_t = GetName(sceneId, selfId)
	
	if name_t == "将军哈达鲁" then
		local msg_t = "x700003_OnDie 将军哈达鲁: objId="..objId2..",selfId="..selfId
		WriteLog(1,msg_t)
	end

	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700003_CSP_BOSS1_ID, -1);

		x700003_OnHuoPaoOver(sceneId,2)
		return
	end

	if objId2>0 then
		if objId2 == selfId then
			SetFubenData_Param(sceneId, x700003_CSP_BOSS2_ID, -1);
			
			x700003_CreateSubmitNpc( sceneId)
			x700003_ShowTipsToAll(sceneId, "副本完成")

			--//--------------------------- 世界喊话 Start--------------------
			--杀死boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700003_CSP_TICKCOUNT)
--
--			local nowTime = x700003_g_TickTime* nowTickCount;
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
--			LuaAllScenceM2Wrold (sceneId,"#R玩家#G"..strPlayerName.."#R和他的队友用时#G"..strKillTime.."#R杀死了"..strBossName, 0, 1)
			
			
			
			--//--------------------------- 世界喊话 end----------------------

		end
	end
end


function x700003_OnAllMonsterDead( sceneId)
	
end

function x700003_CreateSubmitNpc( sceneId)

	 local nStatus = GetFubenData_Param(sceneId, x700003_CSP_PAO_STATUS )
	 if nStatus== 1 then
		if x700003_g_SubmitNPC1.title~="" then
			CreateMonster(sceneId, x700003_g_SubmitNPC1.type, x700003_g_SubmitNPC1.x, x700003_g_SubmitNPC1.z, 3, 0, -1, x700003_g_SubmitNPC1.guid, -1,-1,x700003_g_SubmitNPC1.facedir,  "",x700003_g_SubmitNPC1.title)
		else
			CreateMonster(sceneId, x700003_g_SubmitNPC1.type, x700003_g_SubmitNPC1.x, x700003_g_SubmitNPC1.z, 3, 0, -1, x700003_g_SubmitNPC1.guid, -1,-1,x700003_g_SubmitNPC1.facedir)
		
		end
	 elseif nStatus==2 then
		if x700003_g_SubmitNPC.title~="" then
			CreateMonster(sceneId, x700003_g_SubmitNPC.type, x700003_g_SubmitNPC.x, x700003_g_SubmitNPC.z, 3, 0, -1, x700003_g_SubmitNPC.guid, -1,-1,x700003_g_SubmitNPC.facedir,  "",x700003_g_SubmitNPC.title)
		else
			CreateMonster(sceneId, x700003_g_SubmitNPC.type, x700003_g_SubmitNPC.x, x700003_g_SubmitNPC.z, 3, 0, -1, x700003_g_SubmitNPC.guid, -1,-1,x700003_g_SubmitNPC.facedir)
		
		end
	 end

	 --// add for 现金副本
	 x700003_CreateXianJinBoss(sceneId)
	 --// add end

	 CallScriptFunction( 701113, "OnSceneBossDie", sceneId, 0)
	 CallScriptFunction( 701114, "OnSceneBossDie", sceneId, 0)
end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700003_CreateXianJinBoss(sceneId)

	local nFubenType = GetFubenData_Param(sceneId, x700003_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	
	local nFubenMode = GetFubenData_Param(sceneId, x700003_CSP_FUBEN_MODE)

	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700003_CSP_FUBENLEVEL )
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700003_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700003_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700003_g_ScriptId,nIndexFrom,i)
		if idScript == x700003_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700003_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700003_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700003_CSP_XIANJINBOSS, nRet )
		end
	end

	x700003_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end





