--骑乘炼化
--骑乘炼化
--MisDescBegin
--脚本号
x800031_g_ScriptId = 800031

--上一个任务的ID
--g_MissionIdPre =
x800031_g_GameId = 1055


--任务文本描述
x800031_g_MissionName="骑乘炼化"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x800031_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
--		(这里写弹出骑乘技能学习界面的脚本接口)
end

--**********************************
--列举事件
--**********************************
function x800031_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(x800031_g_GameId) ~= 1 then
		return
	end
	

	if CallScriptFunction(888888,"IsCanHorseCompose",sceneId,selfId) == 0 then --当天已经炼化过。
		AddQuestNumText(sceneId,x800031_g_ScriptId,x800031_g_MissionName,3,3);
	else
		AddQuestNumText(sceneId,x800031_g_ScriptId,x800031_g_MissionName,3,2);
	end
end


--********************
--检测接受条件
--**********************************
function x800031_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x800031_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x800031_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x800031_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x800031_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x800031_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x800031_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x800031_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x800031_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
