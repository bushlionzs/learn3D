
x303009_g_ScriptId          		= 303009
x303009_g_Leader_Index      		= 5
x303009_g_MissionName       		="离开战场"
x303009_g_LeaveMessageFix      		="\t您真的要现在离开战场吗?"

----------------------------------------------------------------------------------------------
--枚举
----------------------------------------------------------------------------------------------
function x303009_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
  
  --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end
  
	--必须对场景校验
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleSceneType",sceneId) < 0 then
		return
	end
	
	--不是有效的场景
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"IsBattleSceneValid",sceneId) ~= 1 then
		return
	end
	
	--刷新BUF列表
	AddQuestNumText(sceneId,x303009_g_ScriptId,x303009_g_MissionName,3,-1);
	
end

----------------------------------------------------------------------------------------------
--默认事件
----------------------------------------------------------------------------------------------
function x303009_ProcEventEntry( sceneId, selfId, targetId,scriptId,idExt )

	--合服开关
    if GetMergeDBToggle() == 1 then
        return
    end
  
  --升级数据库开关
		local UpdateDBflag = GetUpdateDBBeforeToggle()
		if UpdateDBflag==1 then
			return
		end

	--必须对场景校验
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"GetBattleSceneType",sceneId) < 0 then
		return
	end
	
	--不是有效的场景
	if CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"IsBattleSceneValid",sceneId) ~= 1 then
		return
	end
	
	
	if idExt == -1 then
		--是否真的要离开战场
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x303009_g_LeaveMessageFix);		
			AddQuestNumText(sceneId,x303009_g_ScriptId,"确定...",3,x303009_g_ScriptId);		
	    EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId)
	elseif idExt == x303009_g_ScriptId then
		
		CallScriptFunction(PVP6V6_BATTLE_SCRIPT,"KickPlayer",sceneId,selfId) 
	end
end

----------------------------------------------------------------------------------------------
--检测接受条件
----------------------------------------------------------------------------------------------
function x303009_ProcAcceptCheck( sceneId, selfId, NPCId )
    return 1
end

----------------------------------------------------------------------------------------------
--接受
----------------------------------------------------------------------------------------------
function x303009_ProcAccept( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--放弃
----------------------------------------------------------------------------------------------
function x303009_ProcQuestAbandon( sceneId, selfId, MissionId )
end

----------------------------------------------------------------------------------------------
--继续
----------------------------------------------------------------------------------------------
function x303009_OnContinue( sceneId, selfId, targetId )
end

----------------------------------------------------------------------------------------------
--检测是否可以提交
----------------------------------------------------------------------------------------------
function x303009_CheckSubmit( sceneId, selfId )
end

----------------------------------------------------------------------------------------------
--提交
----------------------------------------------------------------------------------------------
function x303009_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end

----------------------------------------------------------------------------------------------
--杀死怪物或玩家
----------------------------------------------------------------------------------------------
function x303009_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end

----------------------------------------------------------------------------------------------
--进入区域事件
----------------------------------------------------------------------------------------------
function x303009_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

----------------------------------------------------------------------------------------------
--道具改变
----------------------------------------------------------------------------------------------
function x303009_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
