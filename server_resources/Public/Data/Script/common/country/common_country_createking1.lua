--功能脚本
--国王募集
--MisDescBegin
--脚本号
x300307_g_ScriptId = 300307

--上一个任务的ID
--g_MissionIdPre =



--任务文本描述
x300307_g_MissionName="国王募集"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x300307_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本

end

--**********************************
--列举事件
--**********************************
function x300307_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x300307_g_ScriptId,x300307_g_MissionName);
end


--********************
--检测接受条件
--**********************************
function x300307_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300307_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x300307_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300307_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300307_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300307_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300307_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300307_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300307_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
