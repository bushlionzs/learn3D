--梦聊说明

--MisDescBegin
x310371_g_ScriptId = 310371
--x310371_g_MissionIdPre =-1
--x310371_g_MissionId = 
--x310371_g_MissionKind = 8
--x310371_g_LevelLess	= 	-1 
--x310371_g_MissionIdNext = -1
--x310371_g_Name	="" 
--x310371_g_noDemandItem ={}
--x310371_g_ExtTarget={}
--x310371_g_NeedNum1= 1
--x310371_g_NeedNum2= 1
--x310371_g_NeedNum3= 1
--x310371_g_MissionHelp =	""
x310371_g_MissionName1="【天上人间·梦聊说明】"
x310371_g_MissionInfo1="\t天上人间·梦聊是不低于85级玩家周末的大型娱乐场。\n\t天上人间·梦聊每#G周六、日#W的09：00——23：00开放，不低于#G85级#W的玩家可通过花费#G10两#W现银或银卡进入。只有第一次进入收费。\n \n#Y天上人间·梦聊相关玩法#W：\n\t每天首次进入天上人间·梦聊时会得到一个#G梦聊乐透奖券#W，凭借里面记录的数字能参加当天10：30、12：30、14：30、16：30、18：30、20：30、22：30举办的天上人间·梦聊#G乐透大抽奖#W。\n\t周六、日9：00——23：00期间，梦幻聊斋的的财神会#G不断#W的出现在天上人间·梦聊各处，第一个点击财神的玩家将获得大量经验奖励，同时天上人间·梦聊中其他玩家也会获得部分经验奖励。\n\t14:00开始至17：00玩家可参与#G挖宝大作战#W活动。\n\t在开放时间内，可以随时参加天降魔君活动。\n\t在天上人间·梦聊里可以进入#G倩女幽魂#W副本和#G画皮#W副本。\n \n#Y注意事项#W：\n\t1.当天#G第一次#W进入天上人间·梦聊收费及给予乐透奖券。\n\t2.天上人间·梦聊适合不低于85级的玩家进入。"  --任务描述
--x310371_g_MissionInfo2="\t#G龙眼石#W是王国加强边防的重要物资。王国大将军派我在这里向所有王国的子民们收集#G龙眼石#W。如果您获得了#G龙眼石#W之后，把它交给我，可以得到珍贵的装备。\n\t龙眼石兑换的装备分为世传，国传，神传，天传四种。世传装备需要#G初级龙眼石#W，国传装备需要#G中级龙眼石#W，神传装备需要#G高级龙眼石#W。天传装备需要#G天之龙眼石#W。\n\t我现在能为您兑换国传装备、神传装备和天传装备！"  --任务描述
--x310371_g_MissionCompleted1=""--完成任务npc说话的话
--x310371_g_MissionCompleted2=""--完成任务npc说话的话
--x310371_g_ContinueInfo1="\t你将要x310371_g_MissionName5。\n\t将扣除您的龙眼石x310371_g_NeedNum1颗。"
--x310371_g_ContinueInfo2=""
--x310371_g_ContinueInfo3=""
--x310371_g_ErrorInfo1=""
--x310371_g_ErrorInfo2=""
--x310371_g_BonusMoney1 =0
--x310371_g_BonusMoney2 =0
--x310371_g_BonusMoney3 =0
--x310371_g_BonusItem	=	{}
--x310371_g_BonusChoiceItem ={}
--x310371_g_ExpBonus = 250
--x310371_g_SkillHalfHour = 7510
--x310371_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x310371_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310371_g_MissionName1)
			AddQuestText(sceneId,x310371_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310371_g_ScriptId, x310371_g_MissionName1)

end



--**********************************

--列举事件

--**********************************

function x310371_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x310371_g_ScriptId, x310371_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--检测接受条件

--**********************************

function x310371_ProcAcceptCheck(sceneId, selfId, NPCId)
	--081217(齐亮)处于PK模式或PK值大于0不能“领双”
--local pkMode = GetPlayerPKMode( sceneId, selfId)
--local pkValue = GetPKValue( sceneId, selfId)
--if pkMode ~= 0 or pkValue > 0 then
--	BeginQuestEvent( sceneId)
--	AddQuestText( sceneId, "处于PK模式或PK值大于0不能获得双倍经验" )
--	EndQuestEvent()
--	DispatchQuestTips( sceneId, selfId)
--	return 0
--end

		return 1
end


--**********************************

--检测查看条件

--**********************************

function x310371_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x310371_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x310371_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x310371_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x310371_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x310371_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x310371_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x310371_ProcTiming(sceneId, selfId )
	 
		
end

function x310371_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x310371_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x310371_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x310371_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x310371_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x310371_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x310371_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x310371_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x310371_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
