
x300632_g_ScriptId = 300632

--上一个任务的ID
--g_MissionIdPre =

--后续任务ID
x300632_g_MessionIdAfter1	= 300634
x300632_g_MessionIdAfter2	= 300633


--任务文本描述
x300632_g_MissionName1="【帮会】帮会建设"
x300632_g_MissionName2="【帮会】帮会募集"
x300632_g_MissionName3="【帮会】帮贡建设"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x300632_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本

	local Readme_1 = "#Y【帮会】帮会建设#W#r"
	
	local Readme_2 = "\t帮会经验是升级帮会，开启帮贡商店的必需品。#r"
	
	local Readme_3 = "\t帮会成员除了日常帮会任务外还可以通过".."#G".."帮会募集".."#W".."或".."#G".."帮贡建设".."#W".."提升帮会经验，同时建设者也将获得#G高额奖励。#r"
	
	local Readme_4 = "\t#W帮会募集:帮会成员每人每日可以建设1次。#r"
	
	local Readme_5 = "\t#W帮贡建设:每个帮会每日根据本帮会的等级进行建设。1级帮会可以建设25次，2级帮会可以建设50次，3级帮会可以建设75次，4级帮会可以建设100次，5级帮会可以建设125次，6级帮会可以建设150次,7级帮会可以建设175次。"
	
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4..Readme_5
	
	BeginQuestEvent(sceneId);AddQuestText(sceneId,Readme)
	
	AddQuestNumText(sceneId,x300632_g_MessionIdAfter1,x300632_g_MissionName2,3)
	
	AddQuestNumText(sceneId,x300632_g_MessionIdAfter2,x300632_g_MissionName3,3)
	
	EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId)
	
end

--**********************************
--列举事件
--**********************************
function x300632_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	local pos = GetGuildOfficial(sceneId, selfId)--判断是否加入帮会
	if pos == -1 then
		return
	end
	AddQuestNumText(sceneId,x300632_g_ScriptId,x300632_g_MissionName1,3);
end


--********************
--检测接受条件
--**********************************
function x300632_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300632_ProcAccept( sceneId, selfId )

end

--**********************************
--放弃
--**********************************
function x300632_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300632_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300632_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300632_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300632_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300632_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300632_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
