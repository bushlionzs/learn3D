---------------------------------------------------
-- File: 
-- Author: Peng Lin
-- Created: 2010-03-18
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700109_CSP_FUBENTYPE				= 	0
x700109_CSP_SCRIPTID				=	1
x700109_CSP_TICKCOUNT				= 	2
x700109_CSP_FROMSCENEID				= 	3
x700109_CSP_ISCLOSING				= 	4
x700109_CSP_LEAVECOUNTDOWN			= 	5
x700109_CSP_TEAMID					=	6
x700109_CSP_TICKTIME				=	7
x700109_CSP_HOLDTIME				=	8
x700109_CSP_FUBENLEVEL				=	9

x700109_CSP_AREA_ID					=	20
x700109_CSP_AREA_FLAG				=	21
x700109_B_CREATE_RANDOMBOSS			=	230
x700109_CSP_RANDOM_BOSS_ID			=	231
x700109_RANDOMBOSS_FLAG				=	232

x700109_CSP_BOSS_ID					=   233

x700109_RANDOM_BOSS_ID				=	235
x700109_RANDOMBOSS_FLAG				=	236

x700109_CSP_XIANJINBOSS				=	239
x700109_CSP_HUMAN_COUNT				=	240
x700109_CSP_PLAYER_ENTER_START		=	241

x700109_CSP_LAST_TICKOUNT			=	247
x700109_CSP_GUID_START				=   248
x700109_CSP_FUBEN_TYPE				=	254	--三种类型 0:普通(队伍),1:试练,2:英雄
x700109_CSP_FUBEN_MODE				=   255
------------------------Scene System Setting -----------------------------------

x700109_g_ScriptId 					= 700109
x700109_g_MissionId					= 6608
-------------------------fuben data begin-----------------------

  
x700109_g_RandomMonsterRate						= 0.1                       --隐藏boss出现几率
x700109_g_RandomMonsterRateZHOUSANFAN			= 67                      --隐藏boss出现几率 百分之几!
                  
-------------------------fuben data end-----------------------

----------------------------------------------------------
--处理点击对话npc的事件
----------------------------------------------------------
function x700109_ProcEventEntry(sceneId,selfId,targetId)

end

-------------------------------------------------------------------------------
--当副本创建成功时， 开始刷怪和npc
-------------------------------------------------------------------------------
function x700109_OnFubenSceneCreated( sceneId )
	 
	for i = 20,239 do
		SetFubenData_Param(sceneId, i,-1)
	end
	SetFubenData_Param(sceneId, x700109_CSP_AREA_FLAG,0)
	x700109_CreateMonster(sceneId)
	x700109_CreateBoss(sceneId)

end

---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700109_CreateMonster(sceneId)

    local fubenlevel = GetFubenData_Param(sceneId, x700109_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700109_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700109_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700109_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700109_g_ScriptId,nIndexFrom,i)
		if idScript == x700109_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do
            	local nRet = 0
				if title~="" then
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir,  "",title)
				else
					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				
				end
				
				SetPatrolId(sceneId, nRet, patrolid)
			end
        end
	end


end

function x700109_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700109_CSP_FUBENLEVEL ) ;

	local nFubenType = GetFubenData_Param(sceneId, x700109_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700109_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700109_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700109_g_ScriptId,nIndexFrom,i)
		if idScript == x700109_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700109_g_ScriptId, -1, 21,-1, facedir,  "",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700109_g_ScriptId, -1, 21,-1, facedir)
			
			end

			SetFubenData_Param(sceneId, x700109_CSP_BOSS_ID, nRet )
			SetPatrolId(sceneId, nRet, patrolid)
			
        end
	end

end


function x700109_OnDie(sceneId, selfId, killerId)

	local xianjinboss = GetFubenData_Param(sceneId, x700109_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
	
	
	local bossid = GetFubenData_Param(sceneId, x700109_CSP_BOSS_ID)
	
	if bossid == selfId then
		SetFubenData_Param(sceneId, x700109_CSP_BOSS_ID, -1)
		x700109_OnFubenEnd( sceneId)
		x700109_ShowTipsToAll(sceneId, "成功击杀北条时宗，副本完成，请退出副本。")
	end
	
	local nRandomBossId = GetFubenData_Param(sceneId, x700109_RANDOM_BOSS_ID)

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

			local nHorseFlag = GetFubenData_Param(sceneId, x700109_RANDOMBOSS_FLAG);
			local fubenlevel = GetFubenData_Param(sceneId, x700109_CSP_FUBENLEVEL )
			
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
			elseif fubenlevel < 95 then
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
					strHorseName = "狻猊"
				elseif nHorseFlag==1 then
					strHorseName = "毕方"
				elseif nHorseFlag==2 then
					strHorseName = "梼杌"
				elseif nHorseFlag==3 then
					strHorseName = "饕餮"
				end
			else
				if nHorseFlag==0 then
					strHorseName = "狻猊"
				elseif nHorseFlag==1 then
					strHorseName = "毕方"
				elseif nHorseFlag==2 then
					strHorseName = "梼杌"
				elseif nHorseFlag==3 then
					strHorseName = "饕餮"
				end
			end



			local strMapName = "赤血号"
			
			LuaAllScenceM2Wrold (sceneId,strCountryName.."的"..strPlayerName.."打败了"..strMapName.."的九旄战神，九旄丢下"..strHorseName.."落荒而逃！", 5, 1)
			
			
			--//--------------------------- 世界喊话 end----------------------
		end
	end
end

function x700109_OnFubenEnd( sceneId)
	x700109_CreateXianJinBoss(sceneId)
	x700109_CreateRandomMonster(sceneId)
	CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)
	local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,64 )
	end	
	--x700109_ShowTipsToAll(sceneId, "副本完成，请退出副本。")
end
----------------------------------------------------------
--创建现金boss
----------------------------------------------------------
function x700109_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	local zoneId = GetFubenData_Param(sceneId, x700109_CSP_AREA_ID )
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700109_CSP_BOSS_ID)
		if BossId ~= -1 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700109_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700109_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700109_g_MissionId, x700109_g_ScriptId,1)
		
	else
	 --	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700109_g_MissionId, x700109_g_ScriptId)
	end
end

--//add end
function x700109_EnterTick(sceneId, nowTickCount)
end

function x700109_CreateXianJinBoss(sceneId)
	
	local nFubenType = GetFubenData_Param(sceneId, x700109_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	
	local nFubenMode = GetFubenData_Param(sceneId, x700109_CSP_FUBEN_MODE)
	if nFubenMode == 0 then
	  return
	end

	local fubenlevel = GetFubenData_Param(sceneId, x700109_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700109_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700109_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700109_g_ScriptId,nIndexFrom,i)
		if idScript == x700109_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700109_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700109_g_ScriptId, -1, 21,-1,facedir)
			end
			--SetPatrolId(sceneId, nRet, -1)
			SetFubenData_Param(sceneId, x700109_CSP_XIANJINBOSS, nRet )
		end
	end

	x700109_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end


function x700109_CreateRandomMonster(sceneId)
	local nFubenType = GetFubenData_Param(sceneId, x700109_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end

	local rate = random(0,100)/100;
	local nStdRate = x700109_g_RandomMonsterRate
	local nFubenMode = GetFubenData_Param(sceneId, x700109_CSP_FUBEN_MODE)
	if nFubenMode ==1 then
		nStdRate = nStdRate*3
	end
	
	if(nFubenMode ~= 2) then
		if rate>= nStdRate then
			return 0;
		end
	else			--ZHOUSANFAN --Jerry Huang
		rate = random(1,100)
		if(rate > x700109_g_RandomMonsterRateZHOUSANFAN) then
			return 0;
		end
	end

	local nFlag = random(0,3)

	

	local fubenlevel = GetFubenData_Param(sceneId, x700109_CSP_FUBENLEVEL ) ;
	local nIndexFrom = GetFubenDataPosByScriptID(x700109_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700109_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700109_g_ScriptId,nIndexFrom,i)
		--if flag == nFlag then
		
		
			if idScript == x700109_g_ScriptId and monsterFlag == 8+nFlag and levelmin <= fubenlevel and levelmax >= fubenlevel  and flag3 == nFubenType then
				local nBossID =0;
				if title~="" then
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700109_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700109_g_ScriptId, -1, 21,-1,facedir)
				
				end
				--print("Random BossID",nBossID, title)
				SetFubenData_Param(sceneId, x700109_RANDOMBOSS_FLAG, nFlag)
				SetFubenData_Param(sceneId, x700109_RANDOM_BOSS_ID, nBossID)
			end
		--end
	end

	x700109_ShowTipsToAll(sceneId, "战神再现！")

end
function x700109_ShowTipsToAll(sceneId, str)

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
function x700109_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	SetFubenData_Param(sceneId, x700109_CSP_AREA_ID, zoneId)
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700109_CSP_BOSS_ID)
		if BossId ~= -1 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700109_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700109_g_MissionId, x700109_g_ScriptId,1)
		
	else
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700109_g_MissionId, x700109_g_ScriptId)
	end
end	
---------------------------------------------------------------------------------------------------
--离开区域
---------------------------------------------------------------------------------------------------
function x700109_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	SetFubenData_Param(sceneId, x700109_CSP_AREA_ID, -1)
end