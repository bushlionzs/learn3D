--图腾进贡
x300959_g_ScriptId              			= 300959
x300959_g_MissionName          			="【国家】图腾进贡"

x300959_g_MissionId						= {7760, 7761, 7762, 7763, 7764, 7765, 7766, 7767, 7768}
x300959_g_Laird							= {6, 9, 13, 18, 21, 24, 27, 31, 34}

---------------------------------------------------------------------------------------------------
--列举事件
---------------------------------------------------------------------------------------------------
function x300959_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	local state = 8
	for i, item in x300959_g_MissionId do
		local state = GetQuestStateNM(sceneId, selfId, targetId, item)
		if state == 7 then
			break
		end
	end
	if state == 8 then
		local ret = 1
		local country = GetCurCountry(sceneId, selfId)
		for i, item in x300959_g_Laird do
			local nLairdCountry = GetSceneLairdCountryId(item)
			if nLairdCountry == country then
				ret = 0
				break
			end
		end
		if ret == 1 then
			return
		end
	end
	AddQuestNumText(sceneId,x300959_g_ScriptId,x300959_g_MissionName,state,x300959_g_ScriptId)
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x300959_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )
	
	BeginQuestEvent(sceneId)
	
		AddQuestText( sceneId, "\t领地图腾最高等级为#G5级#W，达到#G40级#W的玩家，可为领地图腾进贡从而升级图腾等级。进贡后可获得#G经验#W、#G天赋值#W奖励。请选择#G本国占领的图腾#W进行进贡！请注意只有在每日的#R9点-23点#W才可接受和完成任务！" )
		CallScriptFunction(300950,"CallbackEnumEvent", sceneId, selfId, targetId, 1)
		CallScriptFunction(300951,"CallbackEnumEvent", sceneId, selfId, targetId, 2)
		CallScriptFunction(300952,"CallbackEnumEvent", sceneId, selfId, targetId, 3)
		CallScriptFunction(300953,"CallbackEnumEvent", sceneId, selfId, targetId, 4)
		CallScriptFunction(300954,"CallbackEnumEvent", sceneId, selfId, targetId, 5)
		CallScriptFunction(300955,"CallbackEnumEvent", sceneId, selfId, targetId, 6)
		CallScriptFunction(300956,"CallbackEnumEvent", sceneId, selfId, targetId, 7)
		CallScriptFunction(300957,"CallbackEnumEvent", sceneId, selfId, targetId, 8)
		CallScriptFunction(300958,"CallbackEnumEvent", sceneId, selfId, targetId, 9)
    
    EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)	

    return 1

end

----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x300959_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x300959_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x300959_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x300959_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x300959_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x300959_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x300959_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x300959_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x300959_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end