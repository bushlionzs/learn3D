--装备锻造说明

--MisDescBegin
x310345_g_ScriptId = 310345
--x310345_g_MissionIdPre =-1
--x310345_g_MissionId = 
--x310345_g_MissionKind = 8
--x310345_g_LevelLess	= 	-1 
--x310345_g_MissionIdNext = -1
--x310345_g_Name	="" 
--x310345_g_noDemandItem ={}
--x310345_g_ExtTarget={}
--x310345_g_NeedNum1= 1
--x310345_g_NeedNum2= 1
--x310345_g_NeedNum3= 1
--x310345_g_MissionHelp =	""
x310345_g_MissionName1="【水晶球总动员说明】"
x310345_g_MissionInfo1="\t如果魔女的水晶球跑掉了，那她还算魔女吗？我不知道，不过这水晶球对我很重要，是从小把我带大的嬷嬷送给我的，这次它又很顽皮的藏了起来。找到它，它就会回到我身边。当然，你，以及这天上人间·麒麟内的所有人都会获得无限的惊喜！\n \n#Y活动规则#W：\n\t1.周六、日9：00——23：00，水晶球会#G不断#W的出现在天上人间·麒麟各处。\n\t2.搜寻到水晶球的玩家获得大量经验奖励，同时天上人间·麒麟中其他玩家获得部分经验奖励。\n\t3.水晶球并不会进入玩家背包，搜寻结束后它会回到魔女身边，不过顽皮的它随时会在其他地方再次出现。"  --任务描述
--x310345_g_MissionInfo2="\t#G龙眼石#W是王国加强边防的重要物资。王国大将军派我在这里向所有王国的子民们收集#G龙眼石#W。如果您获得了#G龙眼石#W之后，把她交给我，可以得到珍贵的装备。\n\t龙眼石兑换的装备分为世传，国传，神传，天传四种。世传装备需要#G初级龙眼石#W，国传装备需要#G中级龙眼石#W，神传装备需要#G高级龙眼石#W。天传装备需要#G天之龙眼石#W。\n\t我现在能为您兑换国传装备、神传装备和天传装备！"  --任务描述
--x310345_g_MissionCompleted1=""--完成任务npc说话的话
--x310345_g_MissionCompleted2=""--完成任务npc说话的话
--x310345_g_ContinueInfo1="\t你将要x310345_g_MissionName5。\n\t将扣除您的龙眼石x310345_g_NeedNum1颗。"
--x310345_g_ContinueInfo2=""
--x310345_g_ContinueInfo3=""
--x310345_g_ErrorInfo1=""
--x310345_g_ErrorInfo2=""
--x310345_g_BonusMoney1 =0
--x310345_g_BonusMoney2 =0
--x310345_g_BonusMoney3 =0
--x310345_g_BonusItem	=	{}
--x310345_g_BonusChoiceItem ={}
--x310345_g_ExpBonus = 250
--x310345_g_SkillHalfHour = 7510
--x310345_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x310345_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310345_g_MissionName1)
			AddQuestText(sceneId,x310345_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310345_g_ScriptId, x310345_g_MissionName1)

end



--**********************************

--列举事件

--**********************************

function x310345_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x310345_g_ScriptId, x310345_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--检测接受条件

--**********************************

function x310345_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x310345_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x310345_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x310345_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x310345_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x310345_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x310345_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x310345_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x310345_ProcTiming(sceneId, selfId )
	 
		
end

function x310345_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x310345_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x310345_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x310345_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x310345_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x310345_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x310345_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x310345_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x310345_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
