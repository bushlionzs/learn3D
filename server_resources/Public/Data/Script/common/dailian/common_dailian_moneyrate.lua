--代练之金钱消耗

--MisDescBegin
--脚本号
x800026_g_ScriptId = 800026
--MisDescEnd




function x800026_SubTrainMoneyRate( sceneId, level, attack, mode, constant )	--点击该任务后执行此脚本
	local mode = mode/10
	local Money
	if level < 10 then
		Money = ceil(level*attack*mode)
	else
		Money = ceil(level*level*attack*mode/10)
	end
	
	if Money > 0 then
		return Money
	else
		return 0
	end
end




--**********************************
--任务入口函数
--**********************************
function x800026_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
--		(这里写弹出打孔界面的脚本接口)
end

--**********************************
--列举事件
--**********************************
function x800026_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800026_g_ScriptId,"代练");
end


--********************
--检测接受条件
--**********************************
function x800026_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x800026_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x800026_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x800026_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x800026_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x800026_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x800026_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x800026_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x800026_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
