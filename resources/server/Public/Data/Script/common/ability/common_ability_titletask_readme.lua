--大师专属制造说明

--MisDescBegin
x310707_g_ScriptId = 310707
--x310707_g_MissionIdPre =-1
--x310707_g_MissionId = 
--x310707_g_MissionKind = 8
--x310707_g_LevelLess	= 	-1 
--x310707_g_MissionIdNext = -1
--x310707_g_Name	="" 
--x310707_g_noDemandItem ={}
--x310707_g_ExtTarget={}
--x310707_g_NeedNum1= 1
--x310707_g_NeedNum2= 1
--x310707_g_NeedNum3= 1
--x310707_g_MissionHelp =	""
x310707_g_MissionName1="【大师专属制造说明】"
x310707_g_MissionInfo1="\t大师专属制造可以通过本门手艺的高超技巧制作出各种珍贵物品。\n#Y详细说明#W：\n#G草药大师#W可以制作：\n\t百花玉露丹（5个/次）\n\t五行神力丸（3个/次）\n\t五行仙火丸（3个/次）\n\t五行魔道丸（3个/次）\n#G珠宝大师#W可以制作：\n\t大师级红龙晶（1个/次）\n\t大师级绿龙晶（1个/次）\n\t大师级黄龙晶（1个/次）\n\t大师级蓝龙晶（1个/次）\n\t大师级金光石（1个/次）\n\t宗师级洗石剂（1个/次）\n\t炼银钻（1个/次）\n#G驯马大师#W可以制作：\n\t骑术强化符：一级健体（3个/次）\n\t骑术强化符：一级蛮力（3个/次）\n\t骑术强化符：一级聪慧（3个/次）\n\t骑术强化符：一级追影（3个/次）\n\t骑术强化符：一级全能（3个/次）\n#G锻造大师#W可以制作：\n\t暴击神水（3个/次）\n\t血银钻（1个/次）\n#G铸甲大师#W可以制作：\n\t一级碎甲丸（3个/次）\n\t一级穿甲丸（3个/次）\n\t一级熔甲丸（3个/次）\n\t淬银钻（1个/次）\n#G工艺大师#W可以制作：\n\t乱士符（5个/次）\n\t优质符文布（10个/次）\n\t玄银钻（1个/次）"  --任务描述
x310707_g_MissionInfo2="#Y注意事项#W：\n\t#R大师级专属制造的物品共用冷却时间——24小时。#W即：在制作了以上任意物品一次之后，24小时内不能再制作大师专属制造的物品。"  --任务描述
--x310707_g_MissionCompleted1=""--完成任务npc说话的话
--x310707_g_MissionCompleted2=""--完成任务npc说话的话
--x310707_g_ContinueInfo1="\t你将要x310707_g_MissionName5。\n\t将扣除您的龙眼石x310707_g_NeedNum1颗。"
--x310707_g_ContinueInfo2=""
--x310707_g_ContinueInfo3=""
--x310707_g_ErrorInfo1=""
--x310707_g_ErrorInfo2=""
--x310707_g_BonusMoney1 =0
--x310707_g_BonusMoney2 =0
--x310707_g_BonusMoney3 =0
--x310707_g_BonusItem	=	{}
--x310707_g_BonusChoiceItem ={}
--x310707_g_ExpBonus = 250
--x310707_g_SkillHalfHour = 7510
--x310707_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x310707_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310707_g_MissionName1)
			AddQuestText(sceneId,x310707_g_MissionInfo1)
            AddQuestText(sceneId,x310707_g_MissionInfo2)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310707_g_ScriptId, x310707_g_MissionName1)

end



--**********************************

--列举事件

--**********************************

function x310707_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x310707_g_ScriptId, x310707_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--检测接受条件

--**********************************

function x310707_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x310707_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x310707_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x310707_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x310707_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x310707_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x310707_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x310707_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x310707_ProcTiming(sceneId, selfId )
	 
		
end

function x310707_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x310707_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x310707_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x310707_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x310707_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x310707_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x310707_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x310707_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x310707_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
