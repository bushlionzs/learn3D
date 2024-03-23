---------------------------------------------------
-- File: 700092_fuben_dawushi_scene.lua
-- Author: ZP Wang
-- Created: 2008-12-19
-- Version: 0.1

----------------------------------------------------
--********************************
--	#define
--********************************
----------------------------------------------------

x700092_CSP_FUBENTYPE				= 	0
x700092_CSP_SCRIPTID				=	1
x700092_CSP_TICKCOUNT				= 	2
x700092_CSP_FROMSCENEID				= 	3
x700092_CSP_ISCLOSING				= 	4
x700092_CSP_LEAVECOUNTDOWN			= 	5
x700092_CSP_TEAMID					=	6
x700092_CSP_BACKSCENEX       		=   7
x700092_CSP_BACKSCENEZ      		=   8
x700092_CSP_FUBENLEVEL			=	9
x700092_CSP_NPCID					=   10

x700092_CSP_KILLCOUNT				=	20
x700092_CSP_SPECIALMONSTER1			=   21
x700092_CSP_BOSS1					=   22
x700092_CSP_BOSS2					=   23
x700092_CSP_BOSS3					=   24
x700092_CSP_BOSS4					=   25
x700092_CSP_BOSS_COUNT				=   26

x700092_CSP_FUBEN_SCENE_ID			=	27
x700092_CSP_AREA_ID					=	28
x700092_CSP_AREA_FLAG				=	29
x700092_CSP_RANDOM_BOSS_ID			=	233
x700092_RANDOMBOSS_FLAG				=	234

x700092_CSP_XIANJINBOSS				=	239

x700092_CSP_HUMAN_COUNT				=	240
x700092_CSP_OBJID_START				=	241
x700092_CSP_NEXT_SCENE				=   247
x700092_CSP_GUID_START              =   248

x700092_CSP_FUBEN_TYPE				=	254	--试练，普通，英雄，三种类型
x700092_CSP_FUBEN_MODE				=   255 



------------------------Scene System Setting -----------------------------------
x700092_g_MissionId					=   6608
x700092_g_ScriptId 					= 700092                    --脚本号

---------------------------- special for fuben -----------------------------


x700092_g_SubmitNPC                 =   { type =28517,guid= 150561,x = 96, z=11, facedir =180, title="" }
			
x700092_g_TalkNpcID					=   	150556		
x700092_g_NpcTalk = 	{
								"景教堂竟然有个惊天的秘密，他们在用人类做残忍的研究！"		,	
						}
						
x700092_g_BossBuffID 				= 4250  

                       --隐藏boss出现几率
x700092_g_RandomMonsterRate			= 0.1                       --隐藏boss出现几率
x700092_g_RandomMonsterRateZHOUSANFAN			= 67                      --隐藏boss出现几率 百分之几!
-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------


function x700092_ProcEventEntry(sceneId, selfId, NPCId,nScriptId, nFlag)

end

function x700092_ShowTips(sceneId, selfId, str)
	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	DispatchQuestTips(sceneId, selfId);
end

function x700092_ShowTipsToAll(sceneId, str)

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
function x700092_OnFubenSceneCreated( sceneId )
	
	SetFubenData_Param(sceneId, x700092_CSP_BOSS4, 0);
	SetFubenData_Param(sceneId, x700092_CSP_XIANJINBOSS, -1 )
    x700092_CreateMonster( sceneId )
	x700092_CreateBoss( sceneId )
	--x700092_CreateRandomMonster(sceneId)
	
	--x700092_CreateBoss2(sceneId)
end

---------------------------------------------------------------------------------------------------
--区域定时器
---------------------------------------------------------------------------------------------------
function x700092_ProcTiming( sceneId, selfId, ScriptId, MissionId )
	local zoneId = GetFubenData_Param(sceneId, x700092_CSP_AREA_ID )
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700092_CSP_BOSS4 )
		if BossId ~= -1 then
			return --TEST
		end
		local flag = GetFubenData_Param(sceneId, x700092_CSP_AREA_FLAG)
		if flag == 1 then
			return
		end
		SetFubenData_Param(sceneId, x700092_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700092_g_MissionId, x700092_g_ScriptId,1)
		
	else
	 	--CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700092_g_MissionId, x700092_g_ScriptId)
	end
end
--//add end

function x700092_EnterTick(sceneId, nowTickCount)
	--print("nowTickCount",nowTickCount)
	if nowTickCount == 3 then
		local objID = FindMonsterByGUID(sceneId,x700092_g_TalkNpcID)
		NpcTalk( sceneId,objID, x700092_g_NpcTalk[1], -1)
		--print("x700092_EnterTick00000000000000000000",a)
	end
end

function x700092_CreateBoss(sceneId)


	local fubenlevel = GetFubenData_Param(sceneId, x700092_CSP_FUBENLEVEL ) 
	SetFubenData_Param(sceneId, x700092_CSP_BOSS_COUNT, 0 )
	

	local nIndexFrom = GetFubenDataPosByScriptID(x700092_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700092_g_ScriptId )
	local nFubenType = GetFubenData_Param(sceneId, x700092_CSP_FUBEN_TYPE)
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700092_g_ScriptId,nIndexFrom,i)
		if idScript == x700092_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
		    local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700092_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700092_g_ScriptId, -1, 21,-1,facedir)
			end

			if flag == 2 then
				SetFubenData_Param(sceneId, x700092_CSP_SPECIALMONSTER1, nRet )
			elseif flag==0 then
				SetFubenData_Param(sceneId, x700092_CSP_BOSS4, nRet )
			end
        end
	end

end

function x700092_CreateBoss1(sceneId)
	--print("x700092_CreateBoss2")
	local fubenlevel = GetFubenData_Param(sceneId, x700092_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700092_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700092_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700092_g_ScriptId )
	
	for i = 0,nDataCount-1 do

		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700092_g_ScriptId,nIndexFrom,i)
		if idScript == x700092_g_ScriptId and monsterFlag == 2 and levelmin <= fubenlevel and levelmax >= fubenlevel and flag == 0 and nFubenType == flag3 then
		    local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700092_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700092_g_ScriptId, -1, 21,-1,facedir)
			end
			
        end
	end

end
---------------------------------------------------------------------------------------------------
--创建BOSS2
---------------------------------------------------------------------------------------------------
function x700092_CreateBoss2(sceneId)
	--print("x700092_CreateBoss2")
	local fubenlevel = GetFubenData_Param(sceneId, x700092_CSP_FUBENLEVEL )
	local nFubenType = GetFubenData_Param(sceneId, x700092_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700092_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700092_g_ScriptId )
	
--	for i = 0,nDataCount-1 do
--
--		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x1,z1,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700092_g_ScriptId,nIndexFrom,i)
--		if idScript == x700092_g_ScriptId and monsterFlag == 1 and levelmin <= fubenlevel and levelmax >= fubenlevel and flag == 0 and nFubenType == flag3 then
--		    local nRet = 0;
--			if title~="" then
--				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700092_g_ScriptId, -1, 21,-1,facedir,"",title)
--			else
--				nRet = CreateMonster(sceneId, type, x1, z1, ai, aiscript, x700092_g_ScriptId, -1, 21,-1,facedir)
--			end
--			print("x700092_CreateBoss2")
--			SetFubenData_Param(sceneId, x700092_CSP_BOSS4, nRet )
--        end
--	end

end


---------------------------------------------------------------------------------------------------
--创建Monster
---------------------------------------------------------------------------------------------------
function x700092_CreateMonster(sceneId)


    local fubenlevel = GetFubenData_Param(sceneId, x700092_CSP_FUBENLEVEL ) ;
	local nFubenType = GetFubenData_Param(sceneId, x700092_CSP_FUBEN_TYPE)
	local nIndexFrom = GetFubenDataPosByScriptID(x700092_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700092_g_ScriptId )

	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700092_g_ScriptId,nIndexFrom,i)
		if idScript == x700092_g_ScriptId and monsterFlag == 3 and levelmin <= fubenlevel and levelmax >= fubenlevel and nFubenType == flag3 then
            for j=0,count -1 do

                local rx = random(-r,r)
                local x = x + rx
                local rz = random(-r,r)
                local z = z + rz
				if title~="" then
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir, "",title)
				else
					CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21,-1,facedir)
				end
            end
        end
	end

end
function x700092_ProcAreaLeaved( sceneId, selfId, zoneId, MissionId )
	EnterAreaEventListHideNM(sceneId, selfId)
	SetFubenData_Param(sceneId, x700092_CSP_AREA_ID, -1)
end
function x700092_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	SetFubenData_Param(sceneId, x700092_CSP_AREA_ID, zoneId)
	if zoneId == 0 then  --出口
		local BossId = GetFubenData_Param(sceneId, x700092_CSP_BOSS4 )
		if BossId ~= -1 then
			return --TEST
		end
		SetFubenData_Param(sceneId, x700092_CSP_AREA_FLAG,1)
		CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700092_g_MissionId, x700092_g_ScriptId,1)
		
	else
	 	CallScriptFunction(700105,"PopupFubenMenu", sceneId, selfId, zoneId, x700092_g_MissionId, x700092_g_ScriptId)
	end
end



function x700092_CreateRandomMonster(sceneId)
	local nFubenType = GetFubenData_Param(sceneId, x700092_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end

	local rate = random(0,100)/100;
	local nStdRate = x700092_g_RandomMonsterRate
	local nFubenMode = GetFubenData_Param(sceneId, x700092_CSP_FUBEN_MODE)
	if nFubenMode ==1 then
		nStdRate = nStdRate*3
	end
	
	if(nFubenMode ~= 2) then
		if rate>= nStdRate then
			return 0;
		end
	else			
		rate = random(1,100)
		if(rate > x700092_g_RandomMonsterRateZHOUSANFAN) then
			return 0;
		end
	end

	local nFlag = random(0,3)

	

	local fubenlevel = GetFubenData_Param(sceneId, x700092_CSP_FUBENLEVEL ) ;
	local nIndexFrom = GetFubenDataPosByScriptID(x700092_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700092_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700092_g_ScriptId,nIndexFrom,i)
		--if flag == nFlag then
		
		
			if idScript == x700092_g_ScriptId and monsterFlag == 7+nFlag and levelmin <= fubenlevel and levelmax >= fubenlevel  and flag3 == nFubenType then
				local nBossID =0;
				if title~="" then
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700092_g_ScriptId, -1, 21,-1,facedir,  "",title)
				else
					nBossID = CreateMonster(sceneId, type, x,z, ai, aiscript, x700092_g_ScriptId, -1, 21,-1,facedir)
				
				end
				--print("Random BossID",nBossID, title)
				SetFubenData_Param(sceneId, x700092_RANDOMBOSS_FLAG, nFlag)
				SetFubenData_Param(sceneId, x700092_CSP_RANDOM_BOSS_ID, nBossID)
			end
		--end
	end

	x700092_ShowTipsToAll(sceneId, "战神再现！")

end


--function x700092_CreateRandomMonster(sceneId)
--
--	local nFubenType = GetFubenData_Param(sceneId, x700092_CSP_FUBEN_TYPE)
--	if nFubenType ~= 0 then
--		return
--	end
--
--	local rate = random(0,100)/100;
--	if rate>= x700092_g_RandomMonsterRate then
--		return 0;
--	end
--
--
--
--	local fubenlevel = GetFubenData_Param(sceneId, x700092_CSP_FUBENLEVEL ) ;
--
--
--	
--	local bCreated =0;
--	
--	local nIndexFrom = GetFubenDataPosByScriptID(x700092_g_ScriptId)
--	local nDataCount = GetFubenDataCountByScriptID( x700092_g_ScriptId )
--	
--	for i = 0,nDataCount-1 do
--		
--		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700092_g_ScriptId,nIndexFrom,i)
--		if idScript == x700092_g_ScriptId and monsterFlag == 4 and levelmin <= fubenlevel and levelmax >= fubenlevel then
--            for j=0,count -1 do
--
--                local rx = random(-r,r)
--                local x = x + rx
--                local rz = random(-r,r)
--                local z = z + rz
--		        
--				local nRet = 0;
--				if title~="" then
--					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21, -1,facedir, "", title)
--				else
--					nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, -1, -1, 21, -1,facedir)
--				end
--
--				
--				if patrolid>=0 then
--					SetPatrolId(sceneId, nRet, patrolid)
--					
--				end
--            end
--        end
--	end
--
--	
--
--end


function x700092_OnDie(sceneId, selfId, killerId)
	--local nDieCount = GetFubenData_Param(sceneId, x700092_CSP_KILLCOUNT)
	--SetFubenData_Param(sceneId, x700092_CSP_KILLCOUNT, nDieCount+1);

	--nDieCount = nDieCount+1;
	
	--if nDieCount== x700092_NeedKillMonster_Count then
		--x700092_OnAllMonsterDead( sceneId) 
	--end

	local objId1 = GetFubenData_Param(sceneId, x700092_CSP_SPECIALMONSTER1)
	local objId2 = GetFubenData_Param(sceneId, x700092_CSP_BOSS1)
	local objId3 = GetFubenData_Param(sceneId, x700092_CSP_BOSS2)
	local objId4 = GetFubenData_Param(sceneId, x700092_CSP_BOSS3)
	local objId5 = GetFubenData_Param(sceneId, x700092_CSP_BOSS4)

	local xianjinboss = GetFubenData_Param(sceneId, x700092_CSP_XIANJINBOSS)
	if xianjinboss == selfId then
		CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnXianjinBossDie", sceneId)
	end
	
--	--//--------------------------- 世界喊话 Start--------------------
--	
--	local nowTickCount = GetFubenData_Param(sceneId, x700092_CSP_TICKCOUNT)
--
--	local nowTime = x700092_g_TickTime* nowTickCount;
--
--	local nMinute = floor(nowTime/60)
--	local nSec = mod(nowTime,60)
--
--		
--	local strPlayerName = GetName(sceneId, killerId)     -- 杀死怪物的玩家名字
--	-------- if killed by pet -----------------
--	local nKillerType = GetObjType(sceneId, killerId)
--	
--	if nKillerType== 3 then
--		local nOwnerId = GetOwnerID(sceneId, killerId)
--		strPlayerName = GetName(sceneId, nOwnerId)
--	end
--	--------- end -------------------------------
--	
--	local strBossName = GetName(sceneId, selfId)		 -- Boss name	
--	local strKillTime = format("%d分%d秒", nMinute, nSec) -- 杀死关务的事件
--
--	
--	if selfId == objId2 then -- boss flag=0
--		LuaAllScenceM2Wrold (sceneId,"#R“不，我是天命之人，我是神的使者，这不可能！”勃鲁合怎么也没有想到勇士#G"..strPlayerName.."#R带领着队友仅用了#G"..strKillTime.."#R就将自己多年苦心经营的计划全盘毁掉。", 0, 1)
--	end
--
--	if selfId == objId3 then -- boss flag=1
--		LuaAllScenceM2Wrold (sceneId,x700092_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
--	end

--	if selfId == objId4 then -- boss flag=2
--		LuaAllScenceM2Wrold (sceneId,x700092_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
--	end

--	if selfId == objId5 then -- boss flag= 变身后的boss
--		LuaAllScenceM2Wrold (sceneId,x700092_g_FubenName.."玩家"..strPlayerName.."在"..strKillTime.."杀死"..strBossName, 0, 1)
--	end
	
	
	--//--------------------------- 世界喊话 end----------------------

	
	if objId1 == selfId then		
		local x,z = GetWorldPos(sceneId,objId1)
		x700092_CreateBoss1(sceneId)
		--print("boss")
	end
	
	if objId2 == selfId then		
		--print("boss1")
	elseif objId3 == selfId then		
		--print("boss2")
	elseif objId4 == selfId then
		--print("boss3")
	end

	if selfId ==objId5 then
		--print("boss4")
		--x700092_CreateSubmitNpc( sceneId)
		x700092_OnFubenEnd( sceneId)
		SetFubenData_Param(sceneId, x700092_CSP_BOSS4, -1)
		
		
	end

	--// add for random boss event, add in 2009-5-20
	local nRandomBossId = GetFubenData_Param(sceneId, x700092_CSP_RANDOM_BOSS_ID)

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

			local nHorseFlag = GetFubenData_Param(sceneId, x700092_RANDOMBOSS_FLAG)
			local fubenlevel = GetFubenData_Param(sceneId, x700092_CSP_FUBENLEVEL )
			
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



			local strMapName = "大教堂"
			
			LuaAllScenceM2Wrold (sceneId,strCountryName.."的"..strPlayerName.."打败了"..strMapName.."的九旄战神，九旄丢下"..strHorseName.."落荒而逃！", 5, 1)
			
			
			--//--------------------------- 世界喊话 end----------------------
		end
	end
	
end

function x700092_OnAllMonsterDead( sceneId)
	--print("x700092_CreateSubmitNpc")
	--x700092_CreateSubmitNpc( sceneId)
end

function x700092_OnFubenEnd( sceneId)
	--print("x700092_CreateSubmitNpc")
	--x700092_CreateSubmitNpc( sceneId)
	--// add for 现金副本
	x700092_CreateXianJinBoss(sceneId)
	x700092_CreateRandomMonster(sceneId)
	CallScriptFunction(FUBEN_COMMON_SCRIPT_CALL,"OnFubuenCompleted", sceneId)
	local humancount = GetFuben_PlayerCount(sceneId);
	for ii = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, ii);
		CallScriptFunction(UTILITY_SCRIPT,"PlayEffect",sceneId,humanId,61 )
	end	
	x700092_ShowTipsToAll(sceneId, "成功击杀贝拉四世,副本完成，请退出副本。")
end

function x700092_CreateSubmitNpc( sceneId)
	if x700092_g_SubmitNPC.title~="" then
		CreateMonster(sceneId, x700092_g_SubmitNPC.type, x700092_g_SubmitNPC.x, x700092_g_SubmitNPC.z, 3, 0, -1, x700092_g_SubmitNPC.guid, -1,-1,x700092_g_SubmitNPC.facedir,  "", x700092_g_SubmitNPC.title)
	else
		CreateMonster(sceneId, x700092_g_SubmitNPC.type, x700092_g_SubmitNPC.x, x700092_g_SubmitNPC.z, 3, 0, -1, x700092_g_SubmitNPC.guid, -1,-1,x700092_g_SubmitNPC.facedir)
	end

	
	
	--挑战副本任务
	CallScriptFunction( 701110, "OnSceneBossDie", sceneId, 0)
	local humancount = GetFuben_PlayerCount(sceneId);
	for i = 0, humancount - 1 do
		local humanId = GetFuben_PlayerObjId(sceneId, i)
		local haveImpact = IsHaveSpecificImpact( sceneId, humanId, x700092_g_BossBuffID )
		if haveImpact == 1 then
			CallScriptFunction( 701111, "OnSceneBossDie", sceneId, 0)
			return
		end
	end
	 
--	 local nFubenMode = GetFubenData_Param(sceneId, x700092_CSP_FUBEN_MODE)
--	 if nFubenMode==1 then
--	 	SetGrowPointIntervalContainer(sceneId,541,1)
--	 	x700092_ShowTipsToAll(sceneId, "现金宝箱出现！")
--	 end
	 --// add end
	 
end

----------------------------------------------------------
--创建现金boss
----------------------------------------------------------

function x700092_CreateXianJinBoss(sceneId)

	--print("x700092_CreateXianJinBoss")
	local nFubenType = GetFubenData_Param(sceneId, x700092_CSP_FUBEN_TYPE)
	if nFubenType ~= 0 then
		return
	end
	--print("x700092_CreateXianJinBoss1")
	local nFubenMode = GetFubenData_Param(sceneId, x700092_CSP_FUBEN_MODE)
	--print("x700092_CreateXianJinBoss4",nFubenMode)
	if nFubenMode == 0 then
	  return
	end
	--print("x700092_CreateXianJinBoss2")
	local fubenlevel = GetFubenData_Param(sceneId, x700092_CSP_FUBENLEVEL ) ;
	
	local nIndexFrom = GetFubenDataPosByScriptID(x700092_g_ScriptId)
	local nDataCount = GetFubenDataCountByScriptID( x700092_g_ScriptId )
	
	for i = 0,nDataCount-1 do
		--print("x700092_CreateXianJinBoss3", nDataCount)
		local idScript,monsterFlag,indexFlag,levelmin,levelmax,name,title,type,guid,x,z,r,ai,aiscript,flag,flag1,flag2,flag3,count,facedir,patrolid,camp = GetFubenDataByScriptID_Pos_Index(x700092_g_ScriptId,nIndexFrom,i)
		if idScript == x700092_g_ScriptId and monsterFlag == 0 and levelmin <= fubenlevel and levelmax >= fubenlevel then

			local nRet = 0;
			if title~="" then
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700092_g_ScriptId, -1, 21,-1,facedir,"",title)
			else
				nRet = CreateMonster(sceneId, type, x, z, ai, aiscript, x700092_g_ScriptId, -1, 21,-1,facedir)
			end
			SetFubenData_Param(sceneId, x700092_CSP_XIANJINBOSS, nRet )
		end
	end

	x700092_ShowTipsToAll(sceneId, "翻番宝箱出现！")
end

