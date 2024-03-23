--麻将铭刻说明

--MisDescBegin
x800093_g_ScriptId = 800093
--x800093_g_MissionIdPre =-1
--x800093_g_MissionId = 
--x800093_g_MissionKind = 8
--x800093_g_LevelLess	= 	-1 
--x800093_g_MissionIdNext = -1
--x800093_g_Name	="" 
--x800093_g_noDemandItem ={}
--x800093_g_ExtTarget={}
--x800093_g_NeedNum1= 1
--x800093_g_NeedNum2= 1
--x800093_g_NeedNum3= 1
--x800093_g_MissionHelp =	""
x800093_g_MissionName1="【职业转换说明】"
x800093_g_MissionInfo1="\t在成吉思汗2中新增了6个职业，我可以帮你转职为对应的新职业。\n\t在转换职业时，你需要一个#G职业转换符#W和一定数量的金钱。\n\t具体职业转换对应为：\n\t#G突厥武士#W可转职为#G地中海十字军#W\n\t#G江南剑侠#W可转职为#G西域圣火使#W\n\t#G蒙古骑射手#W可转职为#G西夏刺客#W\n\t#G中原火枪手#W可转职为#G蒙古近卫军#W\n\t#G波斯先知#W可转职为#G斯拉夫隐修士#W\n\t#G雪山萨满#W可转职为#G高原僧侣#W\n#Y注意事项#W：\n\t在转职之后，你的原有技能也会随之转换，但装备不会发生变化，您还需要进行装备转换来获取新职业的装备。"  --任务描述
--x800093_g_MissionInfo2="\t#G龙眼石#W是王国加强边防的重要物资。王国大将军派我在这里向所有王国的子民们收集#G龙眼石#W。如果您获得了#G龙眼石#W之后，把它交给我，可以得到珍贵的装备。\n\t龙眼石兑换的装备分为世传，国传，神传，天传四种。世传装备需要#G初级龙眼石#W，国传装备需要#G中级龙眼石#W，神传装备需要#G高级龙眼石#W。天传装备需要#G天之龙眼石#W。\n\t我现在能为您兑换国传装备、神传装备和天传装备！"  --任务描述
--x800093_g_MissionCompleted1=""--完成任务npc说话的话
--x800093_g_MissionCompleted2=""--完成任务npc说话的话
--x800093_g_ContinueInfo1="\t你将要x800093_g_MissionName5。\n\t将扣除您的龙眼石x800093_g_NeedNum1颗。"
--x800093_g_ContinueInfo2=""
--x800093_g_ContinueInfo3=""
--x800093_g_ErrorInfo1=""
--x800093_g_ErrorInfo2=""
--x800093_g_BonusMoney1 =0
--x800093_g_BonusMoney2 =0
--x800093_g_BonusMoney3 =0
--x800093_g_BonusItem	=	{}
--x800093_g_BonusChoiceItem ={}
--x800093_g_ExpBonus = 250
--x800093_g_SkillHalfHour = 7510
--x800093_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x800093_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800093_g_MissionName1)
			AddQuestText(sceneId,x800093_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800093_g_ScriptId, x800093_g_MissionName1)

end



--**********************************

--列举事件

--**********************************

function x800093_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800093_g_ScriptId, x800093_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--检测接受条件

--**********************************

function x800093_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800093_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x800093_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x800093_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x800093_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x800093_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x800093_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x800093_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800093_ProcTiming(sceneId, selfId )
	 
		
end

function x800093_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x800093_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800093_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800093_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800093_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800093_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800093_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800093_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800093_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
