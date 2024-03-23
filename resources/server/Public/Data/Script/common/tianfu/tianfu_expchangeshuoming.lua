--装备鎏金说明

--MisDescBegin
x570049_g_ScriptId = 570049
--x570049_g_MissionIdPre =-1
--x570049_g_MissionId = 
--x570049_g_MissionKind = 8
--x570049_g_LevelLess	= 	-1 
--x570049_g_MissionIdNext = -1
--x570049_g_Name	="" 
--x570049_g_noDemandItem ={}
--x570049_g_ExtTarget={}
--x570049_g_NeedNum1= 1
--x570049_g_NeedNum2= 1
--x570049_g_NeedNum3= 1
--x570049_g_MissionHelp =	""
x570049_g_MissionName1="【天赋修炼说明】"
x570049_g_MissionInfo1="\t#W天赋等级增加，可以提升玩家自身控制技能的命中率，降低对方玩家控制技能的命中率。70级以上的玩家才可以开始修炼天赋！多多修炼提升天赋等级，您才能拥有万夫不当之勇！\n#Y操作说明#W：\n\t1.与大都#G天赋修炼大师#W对话。\n\t2.选择#G天赋修炼#W选项。\n\t3.点击界面下方#G确定#W按钮。\n#Y注意事项#W：\n\t1.天赋等级上限为（玩家等级-69）*4。\n\t2.修炼天赋要消耗一定的经验和金钱。"  --任务描述
--x570049_g_MissionInfo2="\t#G龙眼石#W是王国加强边防的重要物资。王国大将军派我在这里向所有王国的子民们收集#G龙眼石#W。如果您获得了#G龙眼石#W之后，把它交给我，可以得到珍贵的装备。\n\t龙眼石兑换的装备分为世传，国传，神传，天传四种。世传装备需要#G初级龙眼石#W，国传装备需要#G中级龙眼石#W，神传装备需要#G高级龙眼石#W。天传装备需要#G天之龙眼石#W。\n\t我现在能为您兑换国传装备、神传装备和天传装备！"  --任务描述
--x570049_g_MissionCompleted1=""--完成任务npc说话的话
--x570049_g_MissionCompleted2=""--完成任务npc说话的话
--x570049_g_ContinueInfo1="\t你将要x570049_g_MissionName5。\n\t将扣除您的龙眼石x570049_g_NeedNum1颗。"
--x570049_g_ContinueInfo2=""
--x570049_g_ContinueInfo3=""
--x570049_g_ErrorInfo1=""
--x570049_g_ErrorInfo2=""
--x570049_g_BonusMoney1 =0
--x570049_g_BonusMoney2 =0
--x570049_g_BonusMoney3 =0
--x570049_g_BonusItem	=	{}
--x570049_g_BonusChoiceItem ={}
--x570049_g_ExpBonus = 250
--x570049_g_SkillHalfHour = 7510
--x570049_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x570049_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570049_g_MissionName1)
			AddQuestText(sceneId,x570049_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570049_g_ScriptId, x570049_g_MissionName1)

end



--**********************************

--列举事件

--**********************************

function x570049_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x570049_g_ScriptId, x570049_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--检测接受条件

--**********************************

function x570049_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x570049_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x570049_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x570049_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x570049_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x570049_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x570049_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x570049_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570049_ProcTiming(sceneId, selfId )
	 
		
end

function x570049_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x570049_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570049_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570049_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570049_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570049_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570049_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570049_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570049_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
