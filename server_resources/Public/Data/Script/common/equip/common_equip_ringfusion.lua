x800065_g_ScriptId = 800065


--任务文本描述
x800065_g_MissionName="皇家秘银熔炼"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x800065_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
end

--**********************************
--列举事件
--**********************************
function x800065_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800065_g_ScriptId,x800065_g_MissionName,3);
end


--********************
--检测接受条件
--**********************************
function x800065_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x800065_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x800065_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x800065_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x800065_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x800065_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x800065_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x800065_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x800065_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
