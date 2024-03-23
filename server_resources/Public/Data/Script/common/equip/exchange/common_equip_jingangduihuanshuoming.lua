--兑换金刚说明

--MisDescBegin
x570037_g_ScriptId = 570037
x570037_g_MissionIdPre =-1
--x570037_g_MissionId = 
x570037_g_MissionKind = 8
x570037_g_LevelLess	= 	-1 
x570037_g_MissionIdNext = -1
x570037_g_Name	="" 
x570037_g_noDemandItem ={}
x570037_g_ExtTarget={}
x570037_g_NeedNum1= 1
x570037_g_NeedNum2= 1
x570037_g_NeedNum3= 1
x570037_g_MissionHelp =	""
x570037_g_MissionName1="金刚兑换说明"
x570037_g_MissionInfo1="\n\t#G钻石#W、#G金刚#W是打造极品星装，提升属性的必要物资。我可以将#G钻石#W兑换成#G金刚#W。金刚可用于不低于75级的装备从9星升到10星，升星失败后装备星级不会下降。\n\t金刚的兑换方式很简单，只要你给我一颗#G钻石#W和一定数量的材料，比如#G夜明珠#W等，我就可以给你兑换成相应的#G金刚#W。\n\t还没有明白？举个例子吧，如果你给我一颗#G海蓝钻石#W和#G夜明珠#W，就可以从我这里兑换到一颗#G海蓝金刚#W，如果你给我一颗#G水火钻石#W和#G夜明珠#W，我就可以给你兑换成一颗#G水火金刚#W，以此类推。"  --任务描述
--x570037_g_MissionInfo2="\t#G龙眼石#W是王国加强边防的重要物资。王国大将军派我在这里向所有王国的子民们收集#G龙眼石#W。如果您获得了#G龙眼石#W之后，把它交给我，可以得到珍贵的装备。\n\t龙眼石兑换的装备分为世传，国传，神传，天传四种。世传装备需要#G初级龙眼石#W，国传装备需要#G中级龙眼石#W，神传装备需要#G高级龙眼石#W。天传装备需要#G天之龙眼石#W。\n\t我现在能为您兑换国传装备、神传装备和天传装备！"  --任务描述
x570037_g_MissionCompleted1=""--完成任务npc说话的话
x570037_g_MissionCompleted2=""--完成任务npc说话的话
x570037_g_ContinueInfo1="\t你将要x570037_g_MissionName5。\n\t将扣除您的龙眼石x570037_g_NeedNum1颗。"
x570037_g_ContinueInfo2=""
x570037_g_ContinueInfo3=""
x570037_g_ErrorInfo1=""
x570037_g_ErrorInfo2=""
x570037_g_BonusMoney1 =0
x570037_g_BonusMoney2 =0
x570037_g_BonusMoney3 =0
x570037_g_BonusItem	=	{}
x570037_g_BonusChoiceItem ={}
x570037_g_ExpBonus = 250
x570037_g_SkillHalfHour = 7510
x570037_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x570037_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件
	if sceneId ==0 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x570037_g_MissionName1)
			AddQuestText(sceneId,x570037_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x570037_g_ScriptId, x570037_g_MissionName1)
	--else  	
	--	BeginQuestEvent(sceneId)
	--		AddQuestText(sceneId,"#Y"..x570037_g_MissionName1)
	--		AddQuestText(sceneId,x570037_g_MissionInfo1)
	--	EndQuestEvent()
	--	DispatchQuestEventList(sceneId, selfId,targetId,x570037_g_ScriptId, x570037_g_MissionName1)
	end

end



--**********************************

--列举事件

--**********************************

function x570037_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x570037_g_ScriptId, x570037_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--检测接受条件

--**********************************

function x570037_ProcAcceptCheck(sceneId, selfId, NPCId)
	--081217(齐亮)处于PK模式或PK值大于0不能“领双”
	local pkMode = GetPlayerPKMode( sceneId, selfId)
	local pkValue = GetPKValue( sceneId, selfId)
	if pkMode ~= 0 or pkValue > 0 then
		BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "处于PK模式或PK值大于0不能获得双倍经验" )
		EndQuestEvent()
		DispatchQuestTips( sceneId, selfId)
		return 0
	end

	return 1
end


--**********************************

--检测查看条件

--**********************************

function x570037_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x570037_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x570037_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x570037_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x570037_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x570037_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x570037_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x570037_ProcTiming(sceneId, selfId )
	 
		
end

function x570037_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x570037_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x570037_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x570037_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x570037_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x570037_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x570037_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x570037_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x570037_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
