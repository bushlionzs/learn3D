x800119_g_ScriptId = 800119


--任务文本描述
x800119_g_MissionName="星辰淬炼"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x800119_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
end

--**********************************
--列举事件
--**********************************
function x800119_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800119_g_ScriptId,x800119_g_MissionName,3);
end


--********************
--检测接受条件
--**********************************
function x800119_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x800119_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x800119_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x800119_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x800119_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x800119_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x800119_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x800119_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x800119_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
