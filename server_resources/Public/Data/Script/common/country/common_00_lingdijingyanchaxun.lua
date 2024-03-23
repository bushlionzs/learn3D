x302506_g_ScriptId 		= 302506
x302506_g_MissionKind 	= 	1                       --任务类型
x302506_g_MissionName	= "【国家】图腾经验查询"

-- 玩法开关id
x302506_g_IsEnableId    = 1050
x302506_g_LimitLevel	= 40			--最低级别

-- 图腾所在的地图
x302506_g_LairdMap		= { 6, 9, 13, 18, 21, 24, 27, 31, 34 }
-- 图腾NPC id
x302506_g_LairdNpcId	= { 400600, 400601, 400602, 400603, 400604, 400605, 400606, 400607, 400608 }
-- 每个等级的图腾经验最大值
x302506_g_LairdExpMax	= { 10500, 11667, 12834, 14001 }


-- 使用该函数显示
function x302506_CallbackEnumEvent(sceneId, selfId, targetId, MissionId)
	if GetGameOpenById( x302506_g_IsEnableId) <= 0 then
        return
    end
    
    local index = -1
    local npcGuid = GetMonsterGUID(sceneId,targetId)
    for i, item in x302506_g_LairdNpcId do
    	if npcGuid == item then
    		index = i
    		break
    	end
    end
	if index == -1 then
		return
	end
    
    local country = GetCurCountry(sceneId, selfId)
    local nLairdCountry = GetSceneLairdCountryId(x302506_g_LairdMap[index])
    if nLairdCountry ~= country then
		return
	end
    
	AddQuestNumText(sceneId,x302506_g_ScriptId, x302506_g_MissionName, 3, -1)
end

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x302506_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
end

----------------------------------------------------------------------------------------------
--脚本默认事件
----------------------------------------------------------------------------------------------
function x302506_ProcEventEntry( sceneId ,selfId, targetId, idScript, idExt )

	if GetGameOpenById( x302506_g_IsEnableId) <= 0 then
        return
    end
    
    local index = -1
    local npcGuid = GetMonsterGUID(sceneId,targetId)
    for i, item in x302506_g_LairdNpcId do
    	if npcGuid == item then
    		index = i
    		break
    	end
    end
	if index == -1 then
		return
	end
    
    local country = GetCurCountry(sceneId, selfId)
    local nLairdCountry = GetSceneLairdCountryId(x302506_g_LairdMap[index])
    if nLairdCountry ~= country then
		return
	end
	
	local nGuildID = GetSceneLairdGuildId(x302506_g_LairdMap[index])
	if nGuildID < 0 then
		--帮会无效
		return
	end
	
	local nLairdLevel = GetSceneLairdLevel(x302506_g_LairdMap[index])
	local nCurLairdExp = GetGuildParam(nGuildID,GD_GUILD_LAIRDBATTLE_CURRENT_EXP)
	
	BeginQuestEvent(sceneId)          
	AddQuestText(sceneId, "#Y"..x302506_g_MissionName.."#W")
	
	if nLairdLevel == 5 then
		AddQuestText(sceneId, "#Y".."当前领地等级已达到满级".."#W")
	else
	local percent = nCurLairdExp*100/x302506_g_LairdExpMax[nLairdLevel]-0.05
	if percent < 0 then
		percent = 0
	end
	AddQuestText(sceneId, format("\n\t领地图腾的经验来源于#Y【国家】图腾进贡#W任务。当图腾的经验到达100%%时，图腾将会升级。领地图腾升级后可以为#G占领领地的帮会#W增加领地津贴和领地经验，同时也会提升#G全国玩家#W出国任务的奖励。\n \n当前经验：#R%.1f%%", percent))
	end
	
	EndQuestEvent()
	DispatchQuestInfo(sceneId ,selfId, targetId, x302506_g_ScriptId, -1, 1)
end

function x302506_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x302506_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x302506_ProcQuestAbandon( sceneId, selfId, MissionId )

end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x302506_OnContinue( sceneId, selfId, targetId )

end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x302506_CheckSubmit( sceneId, selfId )

end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x302506_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x302506_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x302506_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x302506_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
