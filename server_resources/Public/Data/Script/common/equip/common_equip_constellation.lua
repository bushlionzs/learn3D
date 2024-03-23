--装备打造脚本

--MisDescBegin
--脚本号
x800117_g_ScriptId = 800117

--上一个任务的ID
--g_MissionIdPre =



--任务文本描述
x800117_g_MissionName="星座铭刻"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x800117_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
--		(这里写弹出打孔界面的脚本接口)
end

--**********************************
--列举事件
--**********************************
function x800117_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800117_g_ScriptId,x800117_g_MissionName,3);
end


--********************
--检测接受条件
--**********************************
function x800117_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x800117_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x800117_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x800117_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x800117_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x800117_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x800117_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x800117_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x800117_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
