---------------------------------------------------
-- File: 700024_fuben_HUDI_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700024_CSP_FUBENTYPE				= 	0
x700024_CSP_SCRIPTID				=	1
x700024_CSP_TICKCOUNT				= 	2
x700024_CSP_FROMSCENEID				= 	3
x700024_CSP_ISCLOSING				= 	4
x700024_CSP_LEAVECOUNTDOWN			= 	5
x700024_CSP_TEAMID					=	6
x700024_CSP_BACKSCENEX       		=   7
x700024_CSP_BACKSCENEZ      		=   8
x700024_CSP_FUBENLEVEL			=	9

x700024_CSP_KILLCOUNT				=	20
x700024_CSP_BOSS_ID					=   21
x700024_CSP_BOSS_FULL_HP			=   22
x700024_CSP_FUBEN_SCENE_ID			=	23
x700024_CSP_MONSTER_KILL_COUNT		=	24

x700024_CSP_B_KILL_SHARK			=	25


x700024_CSP_MONSTER_COUNT			=	39
x700024_CSP_MONSTER_ID_START		=	40
x700024_CSP_SHARK_COUNT				=	99
x700024_CSP_SHARK_ID_START			=	100
x700024_CSP_MODEL_COUNT				=	109
x700024_CSP_MODEL_ID_START			=	110

x700024_CSP_XIANJINBOSS				=	239

x700024_CSP_HUMAN_COUNT				=	240
x700024_CSP_OBJID_START				=	241

x700024_CSP_GUID_START              =   248  --空6个
x700024_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型
x700024_CSP_FUBEN_MODE				=   255 



------------------------Scene System Setting -----------------------------------

x700024_g_ScriptId 					= 700024

x700024_g_SubmitNPC                 =   { type =25007,guid= 150507,x = 54, z=71, facedir =0, title="" }


										
x700024_g_Shark_FinalX					=	55
x700024_g_Shark_FinalZ					=	60







-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700024_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)
end



function x700024_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700024_ShowTipsToAll(sceneId, str)

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
function x700024_OnFubenSceneCreated( sceneId )
	-- @Param sceneId:  副本场景id
	SetFubenData_Param(sceneId, x700024_CSP_XIANJINBOSS, -1 )
	SetFubenData_Param(sceneId, x700024_CSP_B_KILL_SHARK, 0 );
	x700024_CreateBoss( sceneId )
    x700024_CreateMonster( sceneId )

end

function x700024_EnterTick(sceneId, nowTickCount)

	local nSharkCount = GetFubenData_Param(sceneId, x700024_CSP_SHARK_COUNT ) ;
	
	for i=0, nSharkCount-1 do
		local nObjMonsterId = GetFubenData_Param(sceneId, x700024_CSP_SHARK_ID_START+i );
		if nObjMonsterId>0 and IsObjValid(sceneId,nObjMonsterId) == 1  then
			local x,z = GetWorldPos(sceneId,nObjMonsterId)
			
			if x==x700024_g_Shark_FinalX and z==x700024_g_Shark_FinalZ then
				
				DeleteMonster( sceneId,nObjMonsterId )
				SetFubenData_Param(sceneId, x700024_CSP_SHARK_ID_START+i, -1)
				x700024_CreateModel(sceneId)
			end
		end
	end


	if mod(nowTickCount,1) ==0 then  --5 秒一次
		local nBossId = GetFubenData_Param(sceneId, x700024_CSP_BOSS_ID ) ;

		if nBossId>=0 then
			local nCurrentBossHp = GetHp( sceneId, nBossId )
			local nFullBossHp = GetFubenData_Param(sceneId, x700024_CSP_BOSS_FULL_HP )
			if nCurrentBossHp/nFullBossHp<0.5 then
				

				local nModelCount = GetFubenData_Param(sceneId, x700024_CSP_MODEL_COUNT );
				
				for i=0, nModelCount-1 do
					local nModelId = GetFubenData_Param(sceneId, x700024_CSP_MODEL_ID_START+i ) ;
					
					if nModelId>0 then
						DeleteMonster( sceneId,nModelId )
						SetFubenData_Param(sceneId, x700024_CSP_MODEL_ID_START+i, -1)

						SetHp(sceneId,nBossId, nFullBossHp*0.2 )
						
						local humancount = GetFuben_PlayerCount(sceneId);
						for	j = 0, humancount - 1 do
							local humanId = GetFuben_PlayerObjId(sceneId, j);
							local str = "巨鲨吃了一条小鲨鱼，为自己补充生命！"
							BeginQuestEvent(sceneId);
							AddQuestText(sceneId, str);
							EndQuestEvent(sceneId);
							DispatchQuestTips(sceneId, humanId);
						end
						break;
					end
				end
			end
			
			
		end
	end
			
            
	
end

function x700024_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL )

	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1,facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1,facedir)
			
			end
			SetFubenData_Param(sceneId, x700024_CSP_BOSS_ID, nRet ) ;
			local nFullHp = GetHp( sceneId, nRet )
			SetFubenData_Param(sceneId, x700024_CSP_BOSS_FULL_HP, nFullHp )
			
        end
	end

end




---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700024_CreateMonster(sceneId) --创建小怪


    local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL ) ;

	local nCount = 0
	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
		        local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1, facedir)
				
				end
				SetFubenData_Param(sceneId, x700024_CSP_MONSTER_ID_START+nCount, nRet ) ;
				nCount = nCount+1
            end
        end
	end

	SetFubenData_Param(sceneId, x700024_CSP_MONSTER_COUNT, nCount ) ;
	SetFubenData_Param(sceneId, x700024_CSP_MONSTER_KILL_COUNT, 0 )

end



function x700024_CreateModel(sceneId)
	local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL ) 
	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	local nCount = GetFubenData_Param(sceneId, x700024_CSP_MODEL_COUNT )

	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
			
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x + rx
				local rz = random(-r,r)
				local z = z + rz
				local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, -1,-1, facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, -1,-1, facedir)
				
				end
				SetFubenData_Param(sceneId, x700024_CSP_MODEL_ID_START+nCount, nRet ) ;
				nCount = nCount+1
			end
			
        end
	end

	local nModelCount =  nCount;
	SetFubenData_Param(sceneId, x700024_CSP_MODEL_COUNT,nModelCount )

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = format("%d只幼鲨受到巨鲨的庇护！",nModelCount);
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
end

function x700024_CreateSharkMonster(sceneId, nCurrentKillCount)
	local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	local nCount = GetFubenData_Param(sceneId, x700024_CSP_SHARK_COUNT )

	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
			
			for j=0,count -1 do

				local rx = random(-r,r)
				local x = x + rx
				local rz = random(-r,r)
				local z = z + rz
				local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1, facedir)
				
				end
				SetPatrolId(sceneId, nRet, 0)
				SetFubenData_Param(sceneId, x700024_CSP_SHARK_ID_START+nCount, nRet ) ;
				nCount = nCount+1
			end
			
        end
	end

	local nSharkCount =  nCount;
	SetFubenData_Param(sceneId, x700024_CSP_SHARK_COUNT,nSharkCount )

	local humancount = GetFuben_PlayerCount(sceneId);
	for	i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i);
		local str = format("杀死小怪%d个, 第%d条幼鲨刷新",nCurrentKillCount,nSharkCount );
		BeginQuestEvent(sceneId);
		AddQuestText(sceneId, str);
		EndQuestEvent(sceneId);
		DispatchQuestTips(sceneId, humanId);
	end
end


function x700024_OnDie(sceneId, selfId, killerId)
	local xianjinboss = GetFubenData_Param(sceneId, x700024_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		local humancount = GetFuben_PlayerCount(sceneId);

	--通知玩家
		for i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
			if GetLevel(sceneId, humanId) >= 80 then
				local refixInhExp = AddInherenceExp(sceneId, humanId, 600)
				local str = format("你获得了%d点天赋值", refixInhExp)
				BeginQuestEvent(sceneId);
					AddQuestText(sceneId,str);
				EndQuestEvent();
				DispatchQuestTips(sceneId, humanId)
			end
		end
	end
	
	local nDieCount = GetFubenData_Param(sceneId, x700024_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700024_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	

	local objId1 = GetFubenData_Param(sceneId, x700024_CSP_BOSS_ID)

	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700024_CSP_BOSS_ID,-1)
		x700024_CreateSubmitNpc( sceneId)

		local humancount = GetFuben_PlayerCount(sceneId);
		for	i = 0, humancount - 1 do
			local humanId = GetFuben_PlayerObjId(sceneId, i);
			local str = "奇异的石头出现！";
			BeginQuestEvent(sceneId);
			AddQuestText(sceneId, str);
			EndQuestEvent(sceneId);
			DispatchQuestTips(sceneId, humanId);

			------------------- 随机获得物品----------
			local nRandom = random(1,100)
			if nRandom<=20 then
				BeginAddItem(sceneId)
				AddItem( sceneId, 11990101, 1 )
				local ret = EndAddItem(sceneId,humanId)
				if ret > 0 then
					AddItemListToPlayer(sceneId,humanId)
					str = "恭喜你获得了和氏璧"
				else
					str = "很遗憾，你的背包已满无法获得和氏璧"
				end

				BeginQuestEvent(sceneId);
				AddQuestText(sceneId, str);
				EndQuestEvent(sceneId);
				DispatchQuestTips(sceneId, humanId);
			end
			------------------ 随机获得物品end-------------
		end

			--//--------------------------- 世界喊话 Start--------------------
			--杀死boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700024_CSP_TICKCOUNT)

--			local nowTime = x700024_g_TickTime* nowTickCount;

--			local nMinute = floor(nowTime/60)
--			local nSec = mod(nowTime,60)

				
--			local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--			-------- if killed by pet -----------------
--			local nKillerType = GetObjType(sceneId, killerId)
--			--PrintStr(nKillerType)
--			if nKillerType== 3 then
--				local nOwnerId = GetOwnerID(sceneId, killerId)
--				strPlayerName = GetName(sceneId, nOwnerId)
--			end
--			--------- end -------------------------------
--			local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--			local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件

			
			
--			LuaAllScenceM2Wrold (sceneId,x700024_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
			
			
			--//--------------------------- 世界喊话 end----------------------
	end

	
	
		
	
	local nMonsterCount = GetFubenData_Param(sceneId, x700024_CSP_MONSTER_COUNT ) ;
	for i=0, nMonsterCount-1 do
		local nObjMonsterId = GetFubenData_Param(sceneId, x700024_CSP_MONSTER_ID_START+i );
		if nObjMonsterId>=0 then
			if nObjMonsterId== selfId then
				SetFubenData_Param(sceneId, x700024_CSP_MONSTER_ID_START+i, -1 );
				local nCurrentKillCount = GetFubenData_Param(sceneId, x700024_CSP_MONSTER_KILL_COUNT )+1 ;

				
				SetFubenData_Param(sceneId, x700024_CSP_MONSTER_KILL_COUNT,nCurrentKillCount ) ;
			
				if mod(nCurrentKillCount, 6) ==0 then
					x700024_CreateSharkMonster(sceneId,nCurrentKillCount)
				end
			end
		end
	end

	local nSharkCount = GetFubenData_Param(sceneId, x700024_CSP_SHARK_COUNT ) ;
	for i=0, nSharkCount-1 do
		local nObjMonsterId = GetFubenData_Param(sceneId, x700024_CSP_SHARK_ID_START+i );
		if nObjMonsterId>=0 then
			if nObjMonsterId== selfId then
				SetFubenData_Param(sceneId, x700024_CSP_SHARK_ID_START+i, -1 );
				
				SetFubenData_Param(sceneId, x700024_CSP_B_KILL_SHARK, 1 );
			end
		end
	end


	local nModelCount = GetFubenData_Param(sceneId, x700024_CSP_MODEL_COUNT );
	for i=0, nModelCount-1 do
		local nObjMonsterId = GetFubenData_Param(sceneId, x700024_CSP_MODEL_ID_START+i );
		if nObjMonsterId>=0 then
			if nObjMonsterId== selfId then
				SetFubenData_Param(sceneId, x700024_CSP_MODEL_ID_START+i, -1 );
				
			end
		end
	end

	

				





end

function x700024_OnAllMonsterDead( sceneId)
	--x700024_CreateSubmitNpc( sceneId)
end

function x700024_CreateSubmitNpc( sceneId)
	if x700024_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700024_g_SubmitNPC.type, x700024_g_SubmitNPC.x, x700024_g_SubmitNPC.z, 3, 0, -1, x700024_g_SubmitNPC.guid, -1,-1,x700024_g_SubmitNPC.facedir,  "",x700024_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700024_g_SubmitNPC.type, x700024_g_SubmitNPC.x, x700024_g_SubmitNPC.z, 3, 0, -1, x700024_g_SubmitNPC.guid, -1,-1,x700024_g_SubmitNPC.facedir)
	
	end

	--// add for 现金副本
	 x700024_CreateXianJinBoss(sceneId)
	 --// add end

	 CallScriptFunction( 701107, "OnSceneBossDie", sceneId, 0)

	 local bKillShark = GetFubenData_Param(sceneId, x700024_CSP_B_KILL_SHARK);

	 if bKillShark<=0 then
		CallScriptFunction( 701108, "OnSceneBossDie", sceneId, 0)
	 end
end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700024_CreateXianJinBoss(sceneId)
	local nFubenType = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700024_CSP_FUBEN_MODE)

	if nFubenMode ==0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700024_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700024_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700024_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700024_g_ScriptId,nIndexFrom,i)
		if idScript == x700024_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700024_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700024_CSP_XIANJINBOSS, nRet )
		end
	end

	x700024_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end

