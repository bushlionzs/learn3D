--收集神石介绍
--ScriptID = 310017


x310017_g_ScriptId 					= 310017


x310017_g_MissionName				= "【收集神石】活动介绍"

x310017_g_Readme1						=	"\n#Y一、活动介绍\n#W1、在近来出现了五种写有#Y“成”“吉”“思”“汗”“China Joy”#W的神石，凡是收集齐五块神石的人，当你是第888给阿依娜石头的人，就有机会成为免费参加上海China Joy的活动的幸运儿。活动时间为每天#Y12：30~13：00#W和#G19：30~20：00#W，在接受过#Y【天降宝箱】#W任务后，可以在#Y天赐宝箱#W中随机获得五种神石中的一种，#R每天可以完成1次#W。"

--**********************************
--点击NPC
--**********************************
function x310017_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x310017_g_ScriptId,x310017_g_MissionName,0,1)
	
end
--**********************************
--执行默认事件
--**********************************
function x310017_ProcEventEntry( sceneId, selfId, targetId,state,index)

		BeginQuestEvent(sceneId)
			AddQuestText(sceneId,"#Y"..x310017_g_MissionName)
			AddQuestText(sceneId,x310017_g_Readme1)
		EndQuestEvent()
		DispatchQuestEventList(sceneId, selfId,targetId,x310017_g_ScriptId, x310017_g_MissionName)
		
end
--**********************************
--检测
--**********************************
function x310017_ProcAcceptCheck( sceneId, selfId, NPCId )

end

--**********************************
--接受
--**********************************
function x310017_ProcAccept( sceneId, selfId )
end

--**********************************
--放弃
--**********************************
function x310017_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x310017_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x310017_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x310017_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x310017_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x310017_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x310017_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end



