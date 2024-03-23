--装备鎏金说明

--MisDescBegin
x800090_g_ScriptId = 800090
--x800090_g_MissionIdPre =-1
--x800090_g_MissionId = 
--x800090_g_MissionKind = 8
--x800090_g_LevelLess	= 	-1 
--x800090_g_MissionIdNext = -1
--x800090_g_Name	="" 
--x800090_g_noDemandItem ={}
--x800090_g_ExtTarget={}
--x800090_g_NeedNum1= 1
--x800090_g_NeedNum2= 1
--x800090_g_NeedNum3= 1
--x800090_g_MissionHelp =	""
x800090_g_MissionName1="【装备鎏金（洗蓝）说明】"
x800090_g_MissionInfo1="\t装备鎏金（洗蓝）会对装备已有的蓝属性进行随机强化。鎏金后该装备某些蓝属性的数值将得到提升。\n\t装备鎏金（洗蓝）所需的道具为：海蓝精金（战场积分商店出售），炫彩精金（天上人间·梦聊中天降魔君玩法产出），晕光精金（天上人间·梦聊中挖宝大作战玩法产出），水火精金（威望商店出售），每次鎏金时，所有洗蓝强化值会重新分配。鎏金次数越多蓝属性能够得到的提升越高。每件装备最多可以鎏金9次。玩家等级与装备等级的差值决定目前玩家可以对该装备鎏金的次数。\n\t#R注意：#G命中、闪避、暴击、韧性、暴击伤害#R属性每鎏金三次才能上升1点。\n#Y操作说明#W：\n\t1.与王国#G装备鎏金大师#W或大都#G装备鎏金大师#W对话。\n\t2.选择#G装备鎏金（洗蓝）#W选项。\n\t3.将黄色或紫色装备放入到装备鎏金（洗蓝）界面左上方格子内。\n\t4.点击界面下方鎏金按钮。"  --任务描述
x800090_g_MissionInfo2="#Y注意事项#W：\n\t1.只能强化#G力量、敏捷、智力、体质、全属性、攻击、防御、生命上限、命中、闪避、暴击、韧性、暴击伤害#W属性;#G命中、闪避、暴击、韧性、暴击伤害#W属性每鎏金三次才能上升1点。\n\t2.只有#G3孔以上等级不低于80级的装备#W才能使用此功能。\n\t3.只有#G黄色装备#W和#G紫色装备#W才能使用此功能。\n\t4.#G已绑定#W的装备才能进行装备鎏金。\n\t5.装备80～99级，每2级鎏金1次；\n\t  装备100～160级，无需等级提升即可鎏金。"  --任务描述
--x800090_g_MissionCompleted1=""--完成任务npc说话的话
--x800090_g_MissionCompleted2=""--完成任务npc说话的话
--x800090_g_ContinueInfo1="\t你将要x800090_g_MissionName5。\n\t将扣除您的龙眼石x800090_g_NeedNum1颗。"
--x800090_g_ContinueInfo2=""
--x800090_g_ContinueInfo3=""
--x800090_g_ErrorInfo1=""
--x800090_g_ErrorInfo2=""
--x800090_g_BonusMoney1 =0
--x800090_g_BonusMoney2 =0
--x800090_g_BonusMoney3 =0
--x800090_g_BonusItem	=	{}
--x800090_g_BonusChoiceItem ={}
--x800090_g_ExpBonus = 250
--x800090_g_SkillHalfHour = 7510
--x800090_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x800090_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800090_g_MissionName1)
			AddQuestText(sceneId,x800090_g_MissionInfo1)
			AddQuestText(sceneId,x800090_g_MissionInfo2)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800090_g_ScriptId, x800090_g_MissionName1)

end



--**********************************

--列举事件

--**********************************

function x800090_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800090_g_ScriptId, x800090_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--检测接受条件

--**********************************

function x800090_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x800090_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x800090_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x800090_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x800090_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x800090_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x800090_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x800090_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800090_ProcTiming(sceneId, selfId )
	 
		
end

function x800090_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x800090_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800090_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800090_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800090_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800090_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800090_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800090_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800090_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
