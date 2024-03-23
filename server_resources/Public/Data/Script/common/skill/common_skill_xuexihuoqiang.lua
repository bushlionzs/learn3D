--杀怪任务
--金国士兵
--MisDescBegin
--脚本号
x800045_g_ScriptId = 800045

--上一个任务的ID
--g_MissionIdPre =



--任务文本描述
x800045_g_MissionName="火枪技能学习"
x800045_g_MissionStr="你应该找你的老师学习技能才是，我只能教火枪的技能。"
--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x800045_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
	local ZhiYe= GetZhiye( sceneId, selfId)
	if ZhiYe == 3 then
		OpenSkillStudyUI( sceneId, selfId)
	else
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x800045_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	end


end

--**********************************
--列举事件
--**********************************
function x800045_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId,x800045_g_ScriptId,x800045_g_MissionName,3);
end


--********************
--检测接受条件
--**********************************
function x800045_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x800045_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x800045_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x800045_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x800045_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x800045_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x800045_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x800045_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x800045_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
