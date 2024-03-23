---------------------------------------------------
-- File: 700010_fuben_shizijing_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700010_CSP_FUBENTYPE				= 	0
x700010_CSP_SCRIPTID				=	1
x700010_CSP_TICKCOUNT				= 	2
x700010_CSP_FROMSCENEID				= 	3
x700010_CSP_ISCLOSING				= 	4
x700010_CSP_LEAVECOUNTDOWN			= 	5
x700010_CSP_TEAMID					=	6
x700010_CSP_BACKSCENEX       		=   7
x700010_CSP_BACKSCENEZ      		=   8
x700010_CSP_FUBENLEVEL			=	9

x700010_CSP_KILLCOUNT				=	20
x700010_CSP_FUBEN_SCENE_ID			=	21
x700010_CSP_BOSS1_ID				=	22
x700010_CSP_BOSS2_ID				=	23
x700010_CSP_BOSS3_ID				=   24
x700010_CSP_B_BOSS1_STATUS			=	25
x700010_CSP_BOSS1_TIME_COUNT		=	26
x700010_CSP_BOSS1_FULL_HP			=	27
x700010_CSP_B_BOSS2_STATUS			=	28
x700010_CSP_BOSS2_TIME_COUNT		=	29
x700010_CSP_XJ_BOSS_ID				=	30

x700010_CSP_HUMAN_COUNT				=	240
x700010_CSP_OBJID_START				=	241
x700010_CSP_GUID_START              =   248

x700010_CSP_FUBEN_MODE				=   255 
------------------------Scene System Setting -----------------------------------

x700010_g_ScriptId 					= 700010
----------------------------- special for this Fuben --------------------
x700010_g_Buff1						=	13505                   --防御buff
x700010_g_Buff2						=	13504                   --命中buff
x700010_g_Boss1_Del_Time			=	6                       --会消失怪物的消失时间（进入战斗后）
x700010_g_Boss_Relive_Time			=	1*36                    --有buff的怪物重生时间

x700010_g_nShengWang_Boss1			=	10                      --小头目（命中buff）声望
x700010_g_nShengWang_Boss2			=	10                      --特殊怪（防御buff）声望
x700010_g_nShengWang_Boss3			=	200                     --BOSS声望
x700010_g_nShengWang_Monster		=   5                       --普通小怪声望

x700010_g_SubmitNPC                 =   { type =25023,guid= 150523,x = 49, z=52, facedir =0, title =""}




-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700010_ProcEventEntry(sceneId, selfId, NPCId, nScriptId, nFlag)

end

function x700010_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700010_ShowTipsToAll(sceneId, str)

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
function x700010_OnFubenSceneCreated( sceneId )
	

	x700010_CreateMonster( sceneId )
	x700010_CreateBoss( sceneId, 3 )
   
		
end



function x700010_EnterTick(sceneId,nowTickCount)
	local nBoss1TimeCount = GetFubenData_Param(sceneId, x700010_CSP_BOSS1_TIME_COUNT) + 1;
	SetFubenData_Param(sceneId, x700010_CSP_BOSS1_TIME_COUNT, nBoss1TimeCount);

	local nBoss2TimeCount = GetFubenData_Param(sceneId, x700010_CSP_BOSS2_TIME_COUNT) + 1;
	SetFubenData_Param(sceneId, x700010_CSP_BOSS2_TIME_COUNT, nBoss2TimeCount);

	local nBoss1Status = GetFubenData_Param(sceneId, x700010_CSP_B_BOSS1_STATUS)
	local nBoss2Status = GetFubenData_Param(sceneId, x700010_CSP_B_BOSS2_STATUS)


	
	
	if nBoss1Status==1 then
		local nBoss1Id = GetFubenData_Param(sceneId, x700010_CSP_BOSS1_ID)

		local currentHp = GetHp( sceneId, nBoss1Id )
		local nFullHp = GetFubenData_Param(sceneId, x700010_CSP_BOSS1_FULL_HP)
		
		if currentHp>=nFullHp then
			
			nBoss1TimeCount = nBoss1TimeCount-1
			SetFubenData_Param(sceneId, x700010_CSP_BOSS1_TIME_COUNT, nBoss1TimeCount);
		else
			
			if nBoss1TimeCount==x700010_g_Boss1_Del_Time then
			
				if nBoss1Id>=0 then
					DeleteMonster( sceneId,nBoss1Id )
					SetFubenData_Param(sceneId, x700010_CSP_B_BOSS1_STATUS,2)
					SetFubenData_Param(sceneId, x700010_CSP_BOSS1_ID,-1)
					SetFubenData_Param(sceneId, x700010_CSP_BOSS1_TIME_COUNT,0)
					--x700010_ShowTipsToAll(sceneId, format("怪物消失， %d分钟后重新出现",x700010_g_Boss_Relive_Time/12))
				end
			end
		end

		
	elseif nBoss1Status==2 then
		if nBoss1TimeCount==x700010_g_Boss_Relive_Time then
			x700010_CreateBoss(sceneId, 0)
			
		end
	end

	if nBoss2Status==2 then
		if nBoss2TimeCount==x700010_g_Boss_Relive_Time then
			x700010_CreateBoss(sceneId, 1)
		end
	end
	
end



function x700010_CreateBoss(sceneId, nFlag)


	local fubenlevel = GetFubenData_Param(sceneId, x700010_CSP_FUBENLEVEL ) ;

	
	local nIndexFrom = GetFubenDataPosByScriptID(x700010_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700010_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700010_g_ScriptId,nIndexFrom,i)
		if idScript == x700010_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel then
			if nFlag== flag or nFlag>=3 then
				local nRet = 0
				if title ~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700010_g_ScriptId, -1, 21,-1, facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700010_g_ScriptId, -1, 21,-1, facedir)
				
				end
				if flag == 0 then
					SetFubenData_Param(sceneId, x700010_CSP_BOSS1_ID, nRet )
					SetFubenData_Param(sceneId, x700010_CSP_B_BOSS1_STATUS, 1 )
					SetFubenData_Param(sceneId, x700010_CSP_BOSS1_TIME_COUNT, 0 )

					local nFullHp = GetHp( sceneId, nRet )
					SetFubenData_Param(sceneId, x700010_CSP_BOSS1_FULL_HP,nFullHp )
					
					--SetPatrolId(sceneId, nRet, 0)
				elseif flag == 1 then
					
					SetFubenData_Param(sceneId, x700010_CSP_BOSS2_ID, nRet )
					SetFubenData_Param(sceneId, x700010_CSP_B_BOSS2_STATUS, 1 )
					SetFubenData_Param(sceneId, x700010_CSP_BOSS2_TIME_COUNT, 0 )
				elseif flag == 2 then
					
					SetFubenData_Param(sceneId, x700010_CSP_BOSS3_ID, nRet )
					
				end
			end
		
        end
	end


--	if nFlag<3 then
--
--		local humancount = GetFuben_PlayerCount(sceneId);
--
--			for i = 0, humancount - 1 do
--
--
--				local humanId = GetFuben_PlayerObjId(sceneId, i);	--取得当前场景里人的objId
--				local str = format(" ",nFlag+1);
--				BeginQuestEvent(sceneId);
--				AddQuestText(sceneId, str);
--				EndQuestEvent(sceneId);
--
--				DispatchQuestTips(sceneId, humanId);
--			end
--	end

end




---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700010_CreateMonster(sceneId)


    local fubenlevel = GetFubenData_Param(sceneId, x700010_CSP_FUBENLEVEL ) ;

	local nIndexFrom = GetFubenDataPosByScriptID(x700010_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700010_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700010_g_ScriptId,nIndexFrom,i)
		if idScript == x700010_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x1 + rx
                local rz = random(-r,r)
                local z = z1 + rz

				if title ~= "" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, x700010_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, x700010_g_ScriptId, -1, 21,-1,facedir)
				
				end
			end
        end
	end


	
end




function x700010_OnDie(sceneId, selfId, killerId)
	local nDieCount = GetFubenData_Param(sceneId, x700010_CSP_KILLCOUNT)
	SetFubenData_Param(sceneId, x700010_CSP_KILLCOUNT, nDieCount+1);

	nDieCount = nDieCount+1;
	
	
	
	local objId1 = GetFubenData_Param(sceneId, x700010_CSP_BOSS1_ID)
	local objId2 = GetFubenData_Param(sceneId, x700010_CSP_BOSS2_ID)
	local objId3 = GetFubenData_Param(sceneId, x700010_CSP_BOSS3_ID)
	local nXjBossId = GetFubenData_Param(sceneId, x700010_CSP_XJ_BOSS_ID )

	local nShengWangBonus = 0;
	if objId1 == selfId then
		SetFubenData_Param(sceneId, x700010_CSP_BOSS1_ID, -1)
		SetFubenData_Param(sceneId, x700010_CSP_B_BOSS1_STATUS, 2)
		SetFubenData_Param(sceneId, x700010_CSP_BOSS1_TIME_COUNT, 0)
		nShengWangBonus	= x700010_g_nShengWang_Boss1;
		local humancount = GetFuben_PlayerCount(sceneId);

		for i = 0, humancount - 1 do


			local humanId = GetFuben_PlayerObjId(sceneId, i);	--取得当前场景里人的objId
			SendSpecificImpactToUnit(sceneId, humanId,humanId,humanId, x700010_g_Buff1,0 )
--			local str = "";
--			BeginQuestEvent(sceneId);
--			AddQuestText(sceneId, str);
--			EndQuestEvent(sceneId);
--
--			DispatchQuestTips(sceneId, humanId);
		end
	
		--x700010_ShowTipsToAll(sceneId, format("怪物死亡， %d分钟后重新出现",x700010_g_Boss_Relive_Time/12))
	elseif objId2 == selfId then

		SetFubenData_Param(sceneId, x700010_CSP_BOSS2_ID, -1)
		SetFubenData_Param(sceneId, x700010_CSP_B_BOSS2_STATUS, 2)
		SetFubenData_Param(sceneId, x700010_CSP_BOSS2_TIME_COUNT, 0)
		nShengWangBonus	= x700010_g_nShengWang_Boss2;

		local humancount = GetFuben_PlayerCount(sceneId);

		for i = 0, humancount - 1 do


			local humanId = GetFuben_PlayerObjId(sceneId, i);	--取得当前场景里人的objId
			SendSpecificImpactToUnit(sceneId, humanId,humanId,humanId, x700010_g_Buff2,0 )
--			local str = "";
--			BeginQuestEvent(sceneId);
--			AddQuestText(sceneId, str);
--			EndQuestEvent(sceneId);

--			DispatchQuestTips(sceneId, humanId);
		end
		
		--x700010_ShowTipsToAll(sceneId, format("怪物死亡， %d分钟后重新出现",x700010_g_Boss_Relive_Time/12))
	elseif objId3 == selfId then

		nShengWangBonus	= x700010_g_nShengWang_Boss3;
		SetFubenData_Param(sceneId, x700010_CSP_BOSS3_ID, -1)
		x700010_CreateSubmitNpc( sceneId)
		
--		--//--------------------------- 世界喊话 Start--------------------
--			--杀死boss1
--			local nowTickCount = GetFubenData_Param(sceneId, x700010_CSP_TICKCOUNT)
--
--			local nowTime = x700010_g_TickTime* nowTickCount;
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
--			LuaAllScenceM2Wrold (sceneId,"#R“成吉思汗当年都不能使我屈服，何况你们这些蝼蚁！下一次，我决不会重蹈覆辙！”在#G"..strPlayerName.."#R等人猛烈的攻势下，扎兰丁仅仅支撑了#G"..strKillTime.."#R，就怒吼着又一次进入了沉睡。", 0, 1)
--			
--			
--			--//--------------------------- 世界喊话 end----------------------

	elseif nXjBossId == selfId then
		SetFubenData_Param(sceneId, x700010_CSP_XJ_BOSS_ID, -1 )
		nShengWangBonus = 620*4
	else
		nShengWangBonus	= x700010_g_nShengWang_Monster;
		
	end


	local nShengWangBonus_dup = nShengWangBonus
	
	--朝廷声望
	if nShengWangBonus > 0 then
		local humancount = GetFuben_PlayerCount(sceneId);

		for i = 0, humancount - 1 do


			local humanId = GetFuben_PlayerObjId(sceneId, i);	--取得当前场景里人的objId

			--//add in 2009-3-26
			nShengWangBonus = nShengWangBonus_dup
			local nLevel1 = GetLevel(sceneId, selfId)	--被杀死怪物的level
			local nLevel2 = GetLevel(sceneId, humanId)	--玩家的level
			local fubenlevel = GetFubenData_Param(sceneId, x700010_CSP_FUBENLEVEL ) ; --副本等级
			
			if nLevel2-fubenlevel>10 then
				nShengWangBonus = floor(nShengWangBonus*nLevel1/nLevel2)
			end
			--//add end


			local nShengWang = GetShengWang( sceneId, humanId )
			nShengWang = nShengWang + nShengWangBonus
			SetShengWang( sceneId, humanId, nShengWang )
            
            local str = format("您获得了%d点声望值的奖励。", nShengWangBonus)
			Msg2Player(sceneId,humanId,str,4,2)
			Msg2Player(sceneId,humanId,str,4,3)

		end
		

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

			--//add in 2009-3-26
			nShengWangBonus = nShengWangBonus_dup
			local nLevel1 = GetLevel(sceneId, selfId)	--被杀死怪物的level
			local nLevel2 = GetLevel(sceneId, humanId)	--玩家的level
			local fubenlevel = GetFubenData_Param(sceneId, x700010_CSP_FUBENLEVEL ) ; --副本等级
			
			if nLevel2-fubenlevel>10 then
				nShengWangBonus = floor(nShengWangBonus*nLevel1/nLevel2)
			end
			--//add end
				
			local nLevel = GetLevel(sceneId, humanId)
			if bHaveImpact1>0 or bHaveImpact1_1 > 0 then
				
				local nShengWang = GetShengWang( sceneId, humanId )
				nShengWang = nShengWang + nShengWangBonus*1
				SetShengWang( sceneId, humanId, nShengWang )

				local str = format("江湖请柬帮你获得%d点声望值的奖励",nShengWangBonus*1)
				Msg2Player(sceneId,humanId,str,4,2)
                Msg2Player(sceneId,humanId,str,4,3)
				
				
				BeginQuestEvent(sceneId);
					AddQuestText(sceneId,str);
				EndQuestEvent();
				DispatchQuestTips(sceneId, humanId);

			
				
			end

			if bHaveImpact2>0 then
				
				local nShengWang = GetShengWang( sceneId, humanId )
				nShengWang = nShengWang + nShengWangBonus*2
				SetShengWang( sceneId, humanId, nShengWang )

				local str = format("朝廷请柬帮你获得%d点声望值的奖励",nShengWangBonus*2)
				Msg2Player(sceneId,humanId,str,4,2)
                Msg2Player(sceneId,humanId,str,4,3)
				
				
				BeginQuestEvent(sceneId);
					AddQuestText(sceneId,str);
				EndQuestEvent();
				DispatchQuestTips(sceneId, humanId);
			end
			
		end

	----------------------------------- 周卡end ----------------------------------
	end
end

function x700010_OnAllMonsterDead( sceneId)
	x700010_CreateSubmitNpc( sceneId)
end

function x700010_CreateSubmitNpc( sceneId)
	if x700010_g_SubmitNPC.title ~="" then
		CreateMonster(sceneId, x700010_g_SubmitNPC.type, x700010_g_SubmitNPC.x, x700010_g_SubmitNPC.z, 3, 0, -1, x700010_g_SubmitNPC.guid, -1,-1,x700010_g_SubmitNPC.facedir,  "",x700010_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700010_g_SubmitNPC.type, x700010_g_SubmitNPC.x, x700010_g_SubmitNPC.z, 3, 0, -1, x700010_g_SubmitNPC.guid, -1,-1,x700010_g_SubmitNPC.facedir)
	
	end

	--// add for 现金副本
	 --x700010_CreateXianJinBoss(sceneId)
	 local nFubenMode = GetFubenData_Param(sceneId, x700010_CSP_FUBEN_MODE)
	 if nFubenMode==1 then
	 	SetGrowPointIntervalContainer(sceneId,541,1)
	 	x700010_ShowTipsToAll(sceneId, "现金宝箱出现！")
	 end
	 --// add end
end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700010_CreateXianJinBoss(sceneId)
	local nFubenMode = GetFubenData_Param(sceneId, x700010_CSP_FUBEN_MODE)

	if nFubenMode~=1 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700010_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700010_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700010_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700010_g_ScriptId,nIndexFrom,i)
		if idScript == x700010_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700010_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700010_g_ScriptId, -1, 21,-1,facedir)
			end

			SetFubenData_Param(sceneId, x700010_CSP_XJ_BOSS_ID, nRet )
			
		end
	end

	x700010_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end
