
--帮战BUFF

--MisDescBegin
x300681_g_ScriptId         		= 300681
x300681_g_MissionName          	= "【帮会】战神之力"
x300681_g_BuffCriName          	= "【帮会】增加战神之怒"
x300681_g_BuffTenName          	= "【帮会】增加战神之护"
x300681_g_Leader_Index      	= 5

--帮会战中双方阵营
x300681_g_Guild_Camp_A          = 5
x300681_g_Guild_Camp_B          = 6


x300681_g_NpcIDA      			= 150015
x300681_g_NpcIDB     			= 150014
x300681_g_BuffCriImpactID     	= 8862
x300681_g_BuffTenImpactID     	= 8861

x300681_g_GuildNotify    		= "帮会获得了战神之力"
--x300681_g_MapNotify    			= "获得了战神之力"
x300681_g_PointNotEnough    	= "战场资源不足"

--每次加BUFF所消耗的资源点数
x300681_g_Guild_BufResPoint     = 60  

function x300681_GetNPCCamp(sceneId, selfId, NPCId)
	if NPCId == x300681_g_NpcIDA then
		return x300681_g_Guild_Camp_A
	elseif NPCId == x300681_g_NpcIDB then
		return x300681_g_Guild_Camp_B
	end 
	return -1
end

function x300681_ProcEnumEvent(sceneId, selfId, NPCId)

	local nCampID = GetCurCamp(sceneId,selfId)
	local npcGuid = GetMonsterGUID(sceneId, NPCId)
	local NPCcamp = x300681_GetNPCCamp(sceneId, selfId, npcGuid)
	if nCampID ~= NPCcamp then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId, "不是同一阵营。");
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
		return
	end
	
	
        
	AddQuestNumText(sceneId,x300681_g_ScriptId,x300681_g_MissionName,3,1)
end



function x300681_ProcEventEntry(sceneId, selfId, NPCId, scriptid, index)	--点击该任务后执行此脚本
	
	if index < 100 then
		
		BeginQuestEvent(sceneId)
		
			local Readme_1 = "#Y【帮会】战神之力#r#W"
			local Readme_2 = "\t每位帮主，可以通过消耗60点帮会的战场资源，给所有的帮会成员增加战神之力，提升所有帮会成员的战斗力。#r"
			local Readme_3 = "\t帮会的战场资源主要来源于对帮会战场内的粮车的控制，成功占领一个粮车后，会每10秒增加1点本帮会的战场资源。如果同时占领了本方的两辆粮车或敌方的两辆粮车，则每10秒增加4点战场资源。#r"
			local Readme_4 = "\t战场内有时会随机出现战神宝箱，每成功开启一个宝箱，会给本帮会增加10点战场资源。"
			local Readme_5 = "注意：战场资源只有在帮会战场中才能由帮主使用，并且在帮会战场结束后会清空。"
			local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
			
			AddQuestText(sceneId, Readme);
			AddQuestNumText(sceneId,x300681_g_ScriptId,x300681_g_BuffCriName,3,1+100)
			AddQuestNumText(sceneId,x300681_g_ScriptId,x300681_g_BuffTenName,3,2+100)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,NPCId)
		
	else
	
		index = index - 100
		x300681_ClickBuffMenu(sceneId, selfId, NPCId, index)
		
	end
	
end

function x300681_ProcAccept( sceneId, selfId, NPCId, MissionId, index )
   local pos = GetGuildOfficial(sceneId, selfId)
    if pos ~= x300681_g_Leader_Index then
       BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，只有帮主才有权领取战旗祝福。");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)	
	   Msg2Player(sceneId,selfId,"很抱歉，只有帮主才有权领取战旗祝福。",8,2)
        return
    end

end

function x300681_ClickBuffMenu(sceneId, selfId, NPCId, index)

	local pos = GetGuildOfficial(sceneId, selfId)
    if pos ~= x300681_g_Leader_Index then
       BeginQuestEvent(sceneId)
        AddQuestText(sceneId, "很遗憾，您不是帮主，没有权利领取战神祝福。");
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
		return
    end
    
	local nCampID = GetCurCamp(sceneId,selfId)
	local resPoint = CallScriptFunction(300643,"GetScoreInterval",sceneId,nCampID)
	if resPoint < x300681_g_Guild_BufResPoint then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId, x300681_g_PointNotEnough);
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
		return 
	end
	
	if nCampID == x300681_g_Guild_Camp_A then
		if index == 1 then
			x300681_AddImpactToAllUser(sceneId, selfId, NPCId, x300681_g_BuffCriImpactID)  --暴击
		elseif index == 2 then
			x300681_AddImpactToAllUser(sceneId, selfId, NPCId, x300681_g_BuffTenImpactID)  --韧性
		end

		local GuildIdA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD)
		local GuildTitle = GetGuildTitle(sceneId,selfId)
		local msg = "蓝方获得了战神之力"
		LuaThisScenceM2Wrold(sceneId,msg,2,1)
        LuaThisScenceM2Wrold(sceneId,msg,3,1)	

	elseif nCampID == x300681_g_Guild_Camp_B then
		if index == 1 then
			x300681_AddImpactToAllUser(sceneId, selfId, NPCId, x300681_g_BuffCriImpactID)  --暴击
		elseif index == 2 then
			x300681_AddImpactToAllUser(sceneId, selfId, NPCId, x300681_g_BuffTenImpactID)  --韧性
		end
	
		
		local GuildIdB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD)
		local GuildTitle = GetGuildTitle(sceneId,selfId)
		local msg = "红方获得了战神之力"
		LuaThisScenceM2Wrold(sceneId,msg,2,1)
        LuaThisScenceM2Wrold(sceneId,msg,3,1)	
	end
	
	CallScriptFunction(300643,"SetScoreIntervalInc",sceneId,nCampID,-x300681_g_Guild_BufResPoint)  --减掉资源点
	
	--LuaThisScenceM2Wrold(sceneId,x300681_g_MapNotify,2,1)
	
end

function x300681_AddImpactToAllUser( sceneId, selfId, targetId, impactId )
	
	local nCampID = GetCurCamp(sceneId,selfId)
	local nHumanCount = GetScenePlayerCount( sceneId )
	for i = 0,nHumanCount-1 do
	    local objId = GetScenePlayerObjId( sceneId,i)
	    if objId >= 0 then
	        local nCampIDOther = GetCurCamp(sceneId,objId)
	        if nCampID == nCampIDOther then
	        	SendSpecificImpactToUnit(sceneId, selfId,objId,objId,impactId,0)
	        end
	    end
	end
end

function x300681_ProcAccept( sceneId, selfId, targetId, MissionId, index )
	local nCampID = GetCurCamp(sceneId,selfId)
	
	local resPoint = CallScriptFunction(300643,"GetScoreInterval",sceneId,nCampID)
	if resPoint < x300681_g_Guild_BufResPoint then
		BeginQuestEvent(sceneId)
        AddQuestText(sceneId, x300681_g_PointNotEnough);
        EndQuestEvent(sceneId)
        DispatchQuestEventList(sceneId,selfId,NPCId)
		return 
	end
	
	
	if nCampID == x300681_g_Guild_Camp_A then
		if index == 1 then
			x300681_AddImpactToAllUser(sceneId, selfId, targetId, x300681_g_BuffCriImpactID)  --暴击
		elseif index == 2 then
			x300681_AddImpactToAllUser(sceneId, selfId, targetId, x300681_g_BuffTenImpactID)  --韧性
		end
	
		
		local GuildIdA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD)
		LuaThisScenceM2Guild(sceneId,x300681_g_GuildNotify,GuildIdA,2,1)

	elseif nCampID == x300681_g_Guild_Camp_B then
		if index == 1 then
			x300681_AddImpactToAllUser(sceneId, selfId, targetId, x300681_g_BuffCriImpactID)  --暴击
		elseif index == 2 then
			x300681_AddImpactToAllUser(sceneId, selfId, targetId, x300681_g_BuffTenImpactID)  --韧性
		end
	
		
		local GuildIdB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD)
		LuaThisScenceM2Guild(sceneId,x300681_g_GuildNotify,GuildIdB,2,1)	
	end
	
	CallScriptFunction(300643,"SetScoreIntervalInc",sceneId,nCampID,-x300681_g_Guild_BufResPoint)  --减掉资源点
	--LuaThisScenceM2Wrold(sceneId,x300681_g_MapNotify,2,1)
end

function x300681_ProcAcceptCheck( sceneId, selfId, targetId, MissionId, index )
    return 1
end

function x300681_ProcQuestAccept( sceneId, selfId, targetId, MissionId, index )
    
end

	