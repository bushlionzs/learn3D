--杀怪任务
--金国士兵
--MisDescBegin
--脚本号
x800034_g_ScriptId = 800034

--上一个任务的ID
--g_MissionIdPre =



--任务文本描述
x800034_g_MissionName="骑乘技能"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x800034_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
--		(这里写弹出骑乘技能学习界面的脚本接口)
end

--**********************************
--列举事件
--**********************************
function x800034_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800034_g_ScriptId,x800034_g_MissionName);
end


--********************
--检测接受条件
--**********************************
function x800034_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x800034_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x800034_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x800034_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x800034_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x800034_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x800034_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x800034_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x800034_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
