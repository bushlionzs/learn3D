--乌龙辞典玩法说明

--MisDescBegin
x310189_g_ScriptId = 310189
x310189_g_MissionIdPre =-1
--x310189_g_MissionId = 
x310189_g_MissionKind = 8
x310189_g_LevelLess	= 	-1 
x310189_g_MissionIdNext = -1
x310189_g_MissionId1 = 9300
x310189_g_Name	="" 
x310189_g_noDemandItem ={}
x310189_g_ExtTarget={}
x310189_g_NeedNum1= 1
x310189_g_NeedNum2= 1
x310189_g_NeedNum3= 1
x310189_g_MissionHelp =	""
x310189_g_MissionName1="【乌龙辞典大都淘汰赛说明】"
x310189_g_MissionName2="【乌龙辞典大都淘汰赛说明】"
x310189_g_MissionInfo1="\t大都淘汰赛，每人可以参加两轮，可以在大都#G（157，215）（96，222）（66，196）任意一处找到大都一号主持人参加。\n\t每轮比赛要通过#G一号#W至#G二十号主持人的考验#W，在一位主持人处#G回答正确#W，或#G回答错误两次#W，必须前往下一位主持人处回答。\n\t#G每回答错误一次，均会增加15秒总消耗时间。但是，每人有1次使用过关令（一定回答正确）和3次使用黑白令（50%可能回答正确）的机会。\n\t#W我们将会统计#G每轮用时最短的前三十位玩家#W，他们将取得乌龙辞典终极挑战的资格，在下午16：30后前往大元皇宫找到海总管（135，54）接受考验。"  --任务描述
--x310189_g_MissionInfo2="\t#G龙眼石#W是王国加强边防的重要物资。王国大将军派我在这里向所有王国的子民们收集#G龙眼石#W。如果您获得了#G龙眼石#W之后，把它交给我，可以得到珍贵的装备。\n\t龙眼石兑换的装备分为30级，50级，70级三种。30级装备需要#G初级龙眼石#W，50级装备需要#G中级龙眼石#W，70级装备需要#G高级龙眼石#W。\n\t我现在能为您兑换50级和70级装备装备！"  --任务描述
x310189_g_MissionCompleted1=""--完成任务npc说话的话
x310189_g_MissionCompleted2=""--完成任务npc说话的话
x310189_g_ContinueInfo1="\t你将要x310189_g_MissionName5。\n\t将扣除您的龙眼石x310189_g_NeedNum1颗。"
x310189_g_ContinueInfo2=""
x310189_g_ContinueInfo3=""
x310189_g_ErrorInfo1=""
x310189_g_ErrorInfo2=""
x310189_g_BonusMoney1 =0
x310189_g_BonusMoney2 =0
x310189_g_BonusMoney3 =0
x310189_g_BonusItem	=	{}
x310189_g_BonusChoiceItem ={}
x310189_g_ExpBonus = 250
x310189_g_SkillHalfHour = 7510
x310189_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x310189_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件
--local isHaveMission = IsHaveQuestNM(sceneId,selfId,9300);
--if isHaveMission == 1 then
		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310189_g_MissionName1)
			AddQuestText(sceneId,x310189_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310189_g_ScriptId, x310189_g_MissionName1)
	
--end

end



--**********************************

--列举事件

--**********************************

function x310189_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
--local isHaveMission = IsHaveQuestNM(sceneId,selfId,9300);
--if isHaveMission == 1 then
		AddQuestNumText(sceneId, x310189_g_ScriptId, x310189_g_MissionName1,13,1)
--	else 
--			return
--	end
--end
	
end



--**********************************

--检测接受条件

--**********************************

function x310189_ProcAcceptCheck(sceneId, selfId, NPCId)

	return 1
end


--**********************************

--检测查看条件

--**********************************

function x310189_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x310189_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x310189_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x310189_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x310189_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x310189_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x310189_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x310189_ProcTiming(sceneId, selfId )
	 
		
end

function x310189_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x310189_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x310189_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x310189_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x310189_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x310189_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x310189_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x310189_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x310189_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
