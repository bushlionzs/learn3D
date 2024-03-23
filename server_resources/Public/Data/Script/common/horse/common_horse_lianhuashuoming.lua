--骑乘炼化说明

--MisDescBegin
x920009_g_ScriptId = 920009
--x920009_g_MissionIdPre =-1
--x920009_g_MissionId = 
--x920009_g_MissionKind = 8
--x920009_g_LevelLess	= 	-1 
--x920009_g_MissionIdNext = -1
--x920009_g_Name	="" 
--x920009_g_noDemandItem ={}
--x920009_g_ExtTarget={}
--x920009_g_NeedNum1= 1
--x920009_g_NeedNum2= 1
--x920009_g_NeedNum3= 1
--x920009_g_MissionHelp =	""
x920009_g_MissionName1="【骑乘炼化说明】"
x920009_g_MissionInfo1="\t骑乘炼化可以将两只#G40级以上#R非成年非绑定#W的骑乘，炼化为一只新的骑乘。新骑乘外形、资质、属性点、技能等选取范围取决于炼化的两只骑乘的相关属性。#G每人每天只能进行一次骑乘炼化#W。"  --任务描述
--x920009_g_MissionInfo2="\n\t#Y注意#W：\n\t1.所选骑乘需为非绑定且等级不低于40级的非成年骑乘。\n\t2.炼化后#R副骑乘将失去#W。在炼化后可放弃领取新骑乘，领回用于炼化的原主骑乘。\n\t3.炼化出的骑乘#G等级#W取主骑乘的等级。"  --任务描述
x920009_g_MissionCompleted1="#Y【骑乘外形继承说明】#W\n\t\从所提供的两只骑乘外形之中，随机选取一个作为新骑乘的外形，如果参与炼化的骑乘都为异形骑乘，则有几率炼出#G天龙#W、#G青螭#W等稀有骑乘，这些稀有骑乘可以继续用来下次炼化。"--完成任务npc说话的话
x920009_g_MissionCompleted2="#Y【骑乘属性点和资质继承说明】#W\n\t\根据炼化的两只骑乘的各项资质（原始属性点），炼化后的每项资质（原始属性点）在原有两只骑乘各项资质（原始属性点）的最低和最高之间随机取值。两只炼化的骑乘之中有一只骑乘为变异的，则合出骑乘为变异的（使用道具固本丹和合出稀有骑乘情况例外，有关稀有骑乘请查看“骑乘外形继承说明”）。\n\t#G注：本说明提及的属性点均为骑乘的初始1级时的属性点。"--完成任务npc说话的话
x920009_g_MissionCompleted3="#Y【骑乘技能继承说明】#W\n\t根据炼化的两只骑乘所拥有的技能，随机分配，有可能产生出#R拥有互斥技能的骑乘#W（互斥技能可分别使用高级技能书升级，不会相互影响），当然也有可能#R失去很多原有技能#W。\n \n提示：\n\t1.炼化时副骑乘为异兽时，合出更多技能的几率更高。\n\t2.炼化出骑乘的主动技能个数不会超过主或副骑乘中主动技能格最大开格的数量。"--完成任务npc说话的话
x920009_g_MissionCompleted4="#Y【骑乘等级及携带等级继承说明】#W\n\t根据炼化出骑乘的外形决定新骑乘的携带等级，如炼化出的骑乘为天鹅，则其携带等级为30级。\n\t炼化出的骑乘等级取主骑乘的等级。"--完成任务npc说话的话
x920009_g_ContinueInfo1="#Y【道具固本丹说明】#W\n\t使用了道具#G固本丹#W，炼化出的新骑乘外形、代数、资质和属性点等同于主骑乘的外形、代数、资质和属性点，对骑乘的主动技能和被动技能继承没有影响。\n\t使用道具固本丹，不会影响炼化出稀有骑乘的几率，且使用道具固本丹后，炼出的稀有骑乘各项资质会更加优秀。"
x920009_g_ContinueInfo2="#Y【道具复元丹说明】#W\n\t使用了道具#G回元丹#W，炼化后可选择放弃领取新骑乘，取回原主骑乘。"
x920009_g_ContinueInfo3="#Y【炼化操作说明】#W\n\t1.与王国#G骑乘炼化大师#W或大都#G骑乘炼化大师#W对话。\n\t2.选择#G骑乘炼化#W选项，打开骑乘炼化界面。\n\t3.在骑乘炼化界面左方主骑乘下拉条中选择主骑乘。\n\t4.在骑乘炼化界面右方副骑乘下拉条中选择副骑乘。\n\t5.可以选择放入道具固本丹。\n\t6.点击开始炼化按钮。\n\t7.点击停止炼化按钮。\n\t8.领取新骑乘或原主骑乘。"
--x920009_g_ErrorInfo1=""
--x920009_g_ErrorInfo2=""
--x920009_g_BonusMoney1 =0
--x920009_g_BonusMoney2 =0
--x920009_g_BonusMoney3 =0
--x920009_g_BonusItem	=	{}
--x920009_g_BonusChoiceItem ={}
--x920009_g_ExpBonus = 250
--x920009_g_SkillHalfHour = 7510
--x920009_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x920009_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件
	if extid == 1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x920009_g_MissionName1)
			AddQuestText(sceneId,x920009_g_MissionInfo1)
			AddQuestNumText(sceneId, x920009_g_ScriptId, "骑乘外形继承说明",13,2)
			AddQuestNumText(sceneId, x920009_g_ScriptId, "骑乘等级和携带等级继承说明",13,8)
			AddQuestNumText(sceneId, x920009_g_ScriptId, "骑乘属性点和资质继承说明",13,3)
			AddQuestNumText(sceneId, x920009_g_ScriptId, "骑乘技能继承说明",13,4)
			AddQuestNumText(sceneId, x920009_g_ScriptId, "道具固本丹说明",13,5)
			--AddQuestNumText(sceneId, x920009_g_ScriptId, "道具回元丹说明",13,6)
			AddQuestNumText(sceneId, x920009_g_ScriptId, "炼化操作说明",13,7)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x920009_g_ScriptId, x920009_g_MissionName1)
	elseif extid == 2 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x920009_g_MissionCompleted1)
			AddQuestNumText(sceneId, x920009_g_ScriptId, "返回骑乘炼化说明界面",13,1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x920009_g_ScriptId, x920009_g_MissionName1)
	elseif extid == 3 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x920009_g_MissionCompleted2)
			AddQuestNumText(sceneId, x920009_g_ScriptId, "返回骑乘炼化说明界面",13,1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x920009_g_ScriptId, x920009_g_MissionName1)
	elseif extid == 4 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x920009_g_MissionCompleted3)
			AddQuestNumText(sceneId, x920009_g_ScriptId, "返回骑乘炼化说明界面",13,1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x920009_g_ScriptId, x920009_g_MissionName1)
	elseif extid == 5 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x920009_g_ContinueInfo1)
			AddQuestNumText(sceneId, x920009_g_ScriptId, "返回骑乘炼化说明界面",13,1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x920009_g_ScriptId, x920009_g_MissionName1)
	--elseif extid == 6 then	
	--	BeginQuestEvent(sceneId)
	--		AddQuestText(sceneId,x920009_g_ContinueInfo2)
	--		AddQuestNumText(sceneId, x920009_g_ScriptId, "返回骑乘炼化说明界面",13,1)
	--	EndQuestEvent()
	--	DispatchQuestEventList(sceneId, selfId,targetId,x920009_g_ScriptId, x920009_g_MissionName1)	
	elseif extid == 7 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x920009_g_ContinueInfo3)
			AddQuestNumText(sceneId, x920009_g_ScriptId, "返回骑乘炼化说明界面",13,1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x920009_g_ScriptId, x920009_g_MissionName1)	
	elseif extid == 8 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,x920009_g_MissionCompleted4)
			AddQuestNumText(sceneId, x920009_g_ScriptId, "返回骑乘炼化说明界面",13,1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x920009_g_ScriptId, x920009_g_MissionName1)	
	end	
end



--**********************************

--列举事件

--**********************************

function x920009_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x920009_g_ScriptId, x920009_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--检测接受条件

--**********************************

function x920009_ProcAcceptCheck(sceneId, selfId, NPCId)
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

function x920009_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x920009_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x920009_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x920009_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x920009_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x920009_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x920009_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x920009_ProcTiming(sceneId, selfId )
	 
		
end

function x920009_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x920009_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x920009_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x920009_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x920009_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x920009_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x920009_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x920009_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x920009_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
