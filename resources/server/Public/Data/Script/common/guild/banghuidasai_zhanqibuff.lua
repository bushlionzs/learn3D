
--帮战战旗BUFF

--MisDescBegin
x300682_g_ScriptId          	= 300682
x300682_g_MissionName          	= "【帮会】战神祝福"
x300682_g_Leader_Index      	= 5
x300682_g_NpcIDA      			= 150015
x300682_g_NpcIDB     			= 150014

x300682_g_FlagImpactID    		= 8860   --战旗BUFF

--帮会战中双方阵营
x300682_g_Guild_Camp_A          = 5
x300682_g_Guild_Camp_B          = 6

--每次加BUFF所消耗的资源点数
x300682_g_Guild_BufResPoint     = 20  



--小贩ID    x坐标        y坐标
--150014    22.77097     121.0536
--150015    233.1756     127.5841



--帮会战中双方阵营
x300682_g_Guild_Camp_A          = 5
x300682_g_Guild_Camp_B          = 6

x300682_g_SubMenuDesc     		= "#Y【帮会】战神祝福#r#W\t每位帮主，可以通过消耗20点帮会的战场资源，使用战神祝福给本方战旗恢复10%的生命。#r \t帮会的战场资源主要来源于对帮会战场内的粮车的控制，成功占领一个粮车后，会每10秒增加1点本帮会的战场资源。如果同时占领了本方的两辆粮车或敌方的两辆粮车，则每10秒增加4点战场资源。#r \t战场内有时会随机出现战神宝箱，每成功开启一个宝箱，会给本帮会增加10点战场资源。您确定要使用战神祝福吗？"

x300682_g_PointNotEnough    	= "战场资源不足"
x300682_g_GuildNotify    		= "本方战旗获得了战神祝福，血量恢复10%"
x300682_g_MapNotify    			= "获得了战神祝福"

function x300682_GetNPCCamp(sceneId, selfId, NPCId)
	if NPCId == x300682_g_NpcIDA then
		return x300682_g_Guild_Camp_A
	elseif NPCId == x300682_g_NpcIDB then
		return x300682_g_Guild_Camp_B
	end 
	return -1
end

function x300682_ProcEnumEvent(sceneId, selfId, NPCId)
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
	
	
	-- local pos = GetGuildOfficial(sceneId, selfId)
    -- if pos ~= x300682_g_Leader_Index then
        -- BeginQuestEvent(sceneId)
        -- AddQuestText(sceneId, "您不是帮主。");
        -- EndQuestEvent(sceneId)
        -- DispatchQuestEventList(sceneId,selfId,NPCId)
        -- return
    -- end
        
	AddQuestNumText(sceneId,x300682_g_ScriptId,x300682_g_MissionName,3,100)
end


function x300682_ProcEventEntry(sceneId, selfId, NPCId, scriptid, index)	--点击该任务后执行此脚本
	BeginQuestEvent(sceneId)
		AddQuestText(sceneId,x300682_g_SubMenuDesc)
   	EndQuestEvent()
	DispatchQuestInfo(sceneId, selfId, NPCId, x300682_g_ScriptId, -1)
	--DispatchQuestEventList(sceneId,selfId,NPCId)
end

function x300682_ProcAccept( sceneId, selfId, NPCId, MissionId, index )
	local pos = GetGuildOfficial(sceneId, selfId)
    if pos ~= x300682_g_Leader_Index then
       Msg2Player( sceneId, selfId, "您不是帮主", 8, 3)
	   Msg2Player(sceneId,selfId,"很抱歉，只有帮主才有权领取战神祝福。",8,2)
        return
    end
	local nCampID = GetCurCamp(sceneId,selfId)
	
	local resPoint = CallScriptFunction(300643,"GetScoreInterval",sceneId,nCampID)
	if resPoint < x300682_g_Guild_BufResPoint then
	
		Msg2Player( sceneId, selfId, x300682_g_PointNotEnough, 8, 3)
--		BeginQuestEvent(sceneId)
--        AddQuestText(sceneId, x300682_g_PointNotEnough);
--        EndQuestEvent(sceneId)
--        DispatchQuestEventList(sceneId,selfId,NPCId)
		return 
	end
	
	local battleFlagAID =  GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_A_ID)
	local battleFlagBID =  GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_FLAG_B_ID)

	if nCampID == x300682_g_Guild_Camp_A then
	
		if IsObjValid(sceneId,battleFlagAID) == 1 and GetHp(sceneId,battleFlagAID) > 0 then
			
			local nAdd = floor(GetMaxHp(sceneId,battleFlagAID)* 0.1)
			if nAdd > 0 then
				SetHp(sceneId,battleFlagAID,nAdd)
			end
			
			--SendSpecificImpactToUnit(sceneId, selfId,selfId,battleFlagAID,x300682_g_FlagImpactID,0)
		end
		
		local GuildIdA = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_A_GUILD)
		LuaThisScenceM2Guild(sceneId,x300682_g_GuildNotify,GuildIdA,2,1)
		local msg = "蓝方战旗获得了战神祝福"
		LuaThisScenceM2Wrold(sceneId,msg,2,1)
        LuaThisScenceM2Wrold(sceneId,msg,3,1)	
		
		

	elseif nCampID == x300682_g_Guild_Camp_B then
		
		if IsObjValid(sceneId,battleFlagBID) == 1 and GetHp(sceneId,battleFlagBID) > 0 then
			local nAdd = floor(GetMaxHp(sceneId,battleFlagBID)* 0.1)
			if nAdd > 0 then
				SetHp(sceneId,battleFlagBID,nAdd)
			end
			--SendSpecificImpactToUnit(sceneId, selfId,selfId,battleFlagBID,x300682_g_FlagImpactID,0)
		end
		
		local GuildIdB = GetGuildBattleSceneData_Param(sceneId,LD_GUILD_BATTLE_B_GUILD)
		LuaThisScenceM2Guild(sceneId,x300682_g_GuildNotify,GuildIdB,2,1)
		local msg = "红方战旗获得了战神祝福"
		LuaThisScenceM2Wrold(sceneId,msg,2,1)
        LuaThisScenceM2Wrold(sceneId,msg,3,1)	
	end
	
	CallScriptFunction(300643,"SetScoreIntervalInc",sceneId,nCampID,-x300682_g_Guild_BufResPoint)  --减掉资源点
	
	--LuaThisScenceM2Wrold(sceneId,x300682_g_MapNotify,2,1)

end

function x300682_ProcAcceptCheck( sceneId, selfId, targetId, MissionId, index )
    return 1
end
function x300682_ProcQuestAccept( sceneId, selfId, targetId, MissionId, index )
    
end

	