--装备锻造说明

--MisDescBegin
x800120_g_ScriptId = 800120
--x800120_g_MissionIdPre =-1
--x800120_g_MissionId = 
--x800120_g_MissionKind = 8
--x800120_g_LevelLess	= 	-1 
--x800120_g_MissionIdNext = -1
--x800120_g_Name	="" 
--x800120_g_noDemandItem ={}
--x800120_g_ExtTarget={}
--x800120_g_NeedNum1= 1
--x800120_g_NeedNum2= 1
--x800120_g_NeedNum3= 1
--x800120_g_MissionHelp =	""
x800120_g_MissionName1="【战功铭刻说明】"
x800120_g_MissionInfo1="\t装备进行战功铭刻会提高其基础属性，最高可以升到9级，战功铭刻消耗银币和战场获得的奖章。目前只开放到3级战功铭刻。\n#Y操作说明：\n\t#W1.与王国#G装备铭刻大师#W或大都#G装备铭刻大师#W对话。\n\t2.选择#G战功铭刻#W选项。\n\t3.将装备放入到战功铭刻界面左上方格子内。\n\t4.在选择铭刻道具列表内，选择铭刻使用的奖章。\n\t5.点击界面下方铭刻按钮给装备战功铭刻。\n\t6.如果需要使用自动铭刻的功能，则可以在选择自动铭刻等级的下拉条内，选择自动铭刻等级，点击自动铭刻按钮即可，当银币或奖章不足，或装备已升级至选择的等级，自动铭刻将会自动停止。\n#Y注意事项：\n\t#W1.战功铭刻强化的基础属性不受打星影响。\n\t2.铭刻过程有几率失败，失败后会退一级铭刻等级，0升1级、3升4级、6升7级铭刻失败后不退等级。"  --任务描述
--x800120_g_MissionInfo2="\t#G龙眼石#W是王国加强边防的重要物资。王国大将军派我在这里向所有王国的子民们收集#G龙眼石#W。如果您获得了#G龙眼石#W之后，把它交给我，可以得到珍贵的装备。\n\t龙眼石兑换的装备分为世传，国传，神传，天传四种。世传装备需要#G初级龙眼石#W，国传装备需要#G中级龙眼石#W，神传装备需要#G高级龙眼石#W。天传装备需要#G天之龙眼石#W。\n\t我现在能为您兑换国传装备、神传装备和天传装备！"  --任务描述
--x800120_g_MissionCompleted1=""--完成任务npc说话的话
--x800120_g_MissionCompleted2=""--完成任务npc说话的话
--x800120_g_ContinueInfo1="\t你将要x800120_g_MissionName5。\n\t将扣除您的龙眼石x800120_g_NeedNum1颗。"
--x800120_g_ContinueInfo2=""
--x800120_g_ContinueInfo3=""
--x800120_g_ErrorInfo1=""
--x800120_g_ErrorInfo2=""
--x800120_g_BonusMoney1 =0
--x800120_g_BonusMoney2 =0
--x800120_g_BonusMoney3 =0
--x800120_g_BonusItem	=	{}
--x800120_g_BonusChoiceItem ={}
--x800120_g_ExpBonus = 250
--x800120_g_SkillHalfHour = 7510
--x800120_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x800120_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800120_g_MissionName1)
			AddQuestText(sceneId,x800120_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800120_g_ScriptId, x800120_g_MissionName1)

end



--**********************************

--列举事件

--**********************************

function x800120_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800120_g_ScriptId, x800120_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--检测接受条件

--**********************************

function x800120_ProcAcceptCheck(sceneId, selfId, NPCId)
		return 1
end


--**********************************

--检测查看条件

--**********************************

function x800120_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x800120_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x800120_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x800120_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x800120_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x800120_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x800120_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800120_ProcTiming(sceneId, selfId )
	 
		
end

function x800120_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x800120_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800120_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800120_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800120_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800120_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800120_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800120_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800120_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
