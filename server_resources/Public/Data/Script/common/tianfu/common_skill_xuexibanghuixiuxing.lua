--杀怪任务
--金国士兵
--MisDescBegin
--脚本号
x570052_g_ScriptId = 570052

--上一个任务的ID
--g_MissionIdPre =



--任务文本描述
x570052_g_MissionName="属性天赋研究"
x570052_g_MissionStr="你还未加入任何帮会。"
x570052_g_Leader_Index=5
--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x570052_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
	if GetGameOpenById(1052 ) == 0 then
		return
	end

	local nGuildID= GetGuildID( sceneId, selfId)
	if nGuildID == -1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId, x570052_g_MissionStr)
		EndQuestEvent()
		DispatchQuestEventList(sceneId,selfId,targetId)
	else
		local pos = GetGuildOfficial(sceneId, selfId)
		if pos ~= x570052_g_Leader_Index then			--不是帮主
			BeginQuestEvent(sceneId)
			AddQuestText(sceneId, "抱歉，您不是帮主，没有权利升级帮会属性天赋！");
			EndQuestEvent(sceneId)
			DispatchQuestTips(sceneId,selfId)
		else
			OpenGuildSkillStudyUI_Guild( sceneId, selfId)
		end

	
 	end

	return 0
end

--**********************************
--列举事件
--**********************************
function x570052_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if GetGameOpenById(1052 ) == 0 then
		return
	end

	AddQuestNumText(sceneId,x570052_g_ScriptId,x570052_g_MissionName,3);
end


--********************
--检测接受条件
--**********************************
function x570052_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x570052_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x570052_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x570052_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x570052_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x570052_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x570052_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x570052_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x570052_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
