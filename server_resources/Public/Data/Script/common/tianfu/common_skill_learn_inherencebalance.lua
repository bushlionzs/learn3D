--杀怪任务
--金国士兵
--MisDescBegin
--脚本号
x570060_g_ScriptId = 570060

--上一个任务的ID
--g_MissionIdPre =



--任务文本描述
x570060_g_MissionName="平衡天赋学习"
--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x570060_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
	if GetGameOpenById(1054 ) == 0 then
		return
	end
	local inherenceLevel = GetInherenceLevel( sceneId, selfId )
	if  inherenceLevel < 30 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "您的天赋等级不足30级，还不能学习平衡天赋。");
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
	else
		OpenInherenceBalanceStudyUI(sceneId, selfId)
	end
	return 0
end

--**********************************
--列举事件
--**********************************
function x570060_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	
	if GetGameOpenById(1054 ) == 0 then
		return
	end
	
	AddQuestNumText(sceneId,x570060_g_ScriptId,x570060_g_MissionName,3);
end


--********************
--检测接受条件
--**********************************
function x570060_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x570060_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x570060_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x570060_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x570060_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x570060_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x570060_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x570060_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x570060_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
