--装备锻造说明

--MisDescBegin
x800118_g_ScriptId = 800118
--x800118_g_MissionIdPre =-1
--x800118_g_MissionId = 
--x800118_g_MissionKind = 8
--x800118_g_LevelLess	= 	-1 
--x800118_g_MissionIdNext = -1
--x800118_g_Name	="" 
--x800118_g_noDemandItem ={}
--x800118_g_ExtTarget={}
--x800118_g_NeedNum1= 1
--x800118_g_NeedNum2= 1
--x800118_g_NeedNum3= 1
--x800118_g_MissionHelp =	""
x800118_g_MissionName1="【星座铭刻说明】"
x800118_g_MissionInfo1="\t1.为10星以上有铭刻的黄装或紫装进行星座铭刻。\n\t2.星座铭刻会随机给装备分配一个或两个星座。每个星座会有一个基础属性，并还有一个星座附属性可被激活。\n\t3.每个星座的激活属性需要的特定星座：金牛或双鱼激活白羊，双子或白羊激活金牛，巨蟹或金牛激活双子，狮子或双子激活巨蟹，处女或巨蟹激活狮子，天枰或狮子激活处女，天蝎或处女激活天枰，射手或天枰激活天蝎，魔羯或天蝎激活射手，水瓶或射手激活魔羯，双鱼或魔羯激活水瓶，白羊或水瓶激活双鱼。\n\t3.星座链的装备激活顺序为：头盔激活主手，衣服激活头盔，手镯（上）激活衣服，手镯（下）激活手镯（上），腰带激活手镯（下），披风激活腰带，徽章激活披风，鞋子激活徽章，戒指（下）激活鞋子，戒指（上）激活戒指（下），护手激活戒指（上），项链激活护手，副手激活项链，主手激活副手。\n#Y操作说明#W：\n\t1.与大都#G铭刻大师#W对话。\n\t2.选择#G星座铭刻#W选项，打开#G星座铭刻#W界面。\n\t3.将需要铭刻的装备放入装备栏中并显示装备星座属性。\n\t4.放入星座铭刻道具。\n\t5.点击#G铭刻#W按钮。\n#Y注意事项#W：\n\t1.10星以上有铭刻的黄装或紫装方可进行星座铭刻。\n\t2.星座附属性需要激活后方可生效。"  --任务描述
--x800118_g_MissionInfo2="\t#G龙眼石#W是王国加强边防的重要物资。王国大将军派我在这里向所有王国的子民们收集#G龙眼石#W。如果您获得了#G龙眼石#W之后，把它交给我，可以得到珍贵的装备。\n\t龙眼石兑换的装备分为世传，国传，神传，天传四种。世传装备需要#G初级龙眼石#W，国传装备需要#G中级龙眼石#W，神传装备需要#G高级龙眼石#W。天传装备需要#G天之龙眼石#W。\n\t我现在能为您兑换国传装备、神传装备和天传装备！"  --任务描述
--x800118_g_MissionCompleted1=""--完成任务npc说话的话
--x800118_g_MissionCompleted2=""--完成任务npc说话的话
--x800118_g_ContinueInfo1="\t你将要x800118_g_MissionName5。\n\t将扣除您的龙眼石x800118_g_NeedNum1颗。"
--x800118_g_ContinueInfo2=""
--x800118_g_ContinueInfo3=""
--x800118_g_ErrorInfo1=""
--x800118_g_ErrorInfo2=""
--x800118_g_BonusMoney1 =0
--x800118_g_BonusMoney2 =0
--x800118_g_BonusMoney3 =0
--x800118_g_BonusItem	=	{}
--x800118_g_BonusChoiceItem ={}
--x800118_g_ExpBonus = 250
--x800118_g_SkillHalfHour = 7510
--x800118_g_SkillOneHour = 7511
--MisDescEnd

--**********************************

--任务入口函数

--**********************************

function x800118_ProcEventEntry(sceneId, selfId, targetId,scriptid,extid)	--点击该任务后执行此脚本
	--检测列出条件

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x800118_g_MissionName1)
			AddQuestText(sceneId,x800118_g_MissionInfo1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x800118_g_ScriptId, x800118_g_MissionName1)

end



--**********************************

--列举事件

--**********************************

function x800118_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)

--	local country = GetCurCountry(sceneId, selfId)
--	local nDefaultCamp = GetSceneCamp( sceneId )-16
--
--	if country == nDefaultCamp then 
		AddQuestNumText(sceneId, x800118_g_ScriptId, x800118_g_MissionName1,13,1)
--	else 
--			return
--	end
	
end



--**********************************

--检测接受条件

--**********************************

function x800118_ProcAcceptCheck(sceneId, selfId, NPCId)
		return 1
end


--**********************************

--检测查看条件

--**********************************

function x800118_CheckPushList(sceneId, selfId, NPCId)
	
end

--**********************************

--接受

--**********************************

function x800118_ProcAccept( sceneId, selfId )
	
end



--**********************************

--放弃

--**********************************

function x800118_ProcQuestAbandon(sceneId, selfId, MissionId)

end



--**********************************

--检测是否可以提交

--**********************************

function x800118_CheckSubmit( sceneId, selfId, NPCId)


end



--**********************************

--提交

--**********************************

function x800118_ProcQuestSubmit(sceneId, selfId, NPCId, selectRadioId, MissionId)

end



--**********************************

--杀死怪物或玩家

--**********************************

function x800118_ProcQuestObjectKilled(sceneId, selfId, objdataId, objId, MissionId)

end



--**********************************

--进入区域事件

--**********************************

function x800118_ProcAreaEntered(sceneId, selfId, zoneId, MissionId)
	

end

function x800118_ProcTiming(sceneId, selfId )
	 
		
end

function x800118_ProcAreaLeaved(sceneId, selfId, ScriptId, MissionId )
	
end



--**********************************

--道具改变

--**********************************

function x800118_ProcQuestItemChanged(sceneId, selfId, itemdataId, MissionId)
	
end
function x800118_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId )
	    CallScriptFunction( MISSION_SCRIPT, "ProcQuestAttach",sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

function x800118_MissionComplate( sceneId, selfId, targetId, selectId, MissionId )
	return CallScriptFunction( MISSION_SCRIPT, "MissionComplate", sceneId, selfId, targetId, selectId, MissionId  )
end

function x800118_PositionUseItem( sceneId, selfId, BagIndex, impactId )
	return  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem",sceneId, selfId, BagIndex, impactId)
end

function x800118_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnOpenItemBox",sceneId, selfId, targetId, gpType, needItemID)
end

function x800118_OnRecycle( sceneId, selfId, targetId, gpType, needItemID )
	return CallScriptFunction( MISSION_SCRIPT, "OnRecycle",sceneId, selfId, targetId, gpType, needItemID)
end

function x800118_OnProcOver( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OnProcOver",sceneId, selfId, targetId)
end

function x800118_OpenCheck( sceneId, selfId, targetId )
	CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
