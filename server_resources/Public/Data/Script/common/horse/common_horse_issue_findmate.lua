--杀怪任务
--金国士兵
--MisDescBegin
--脚本号
x800029_g_ScriptId = 800029

--上一个任务的ID
--g_MissionIdPre =



--任务文本描述
x800029_g_MissionName="发布骑乘征友"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x800029_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
	OpenFindHorseMating(sceneId, selfId, 0) --0: 发布
end

--**********************************
--列举事件
--**********************************
function x800029_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800029_g_ScriptId,x800029_g_MissionName);
end


--********************
--检测接受条件
--**********************************
function x800029_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x800029_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x800029_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x800029_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x800029_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x800029_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x800029_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x800029_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x800029_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
