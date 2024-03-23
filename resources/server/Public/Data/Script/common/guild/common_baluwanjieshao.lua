
x300749_g_ScriptId = 300749

--任务文本描述
x300749_g_MissionName="八鲁湾之战"

--MisDescEnd
--**********************************
--任务入口函数
--**********************************
function x300749_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本
		BeginQuestEvent(sceneId);
		local localexp = (GetLevel( sceneId, selfId )) *1000*0.8*5	

		local Readme_1 = "#Y八鲁湾之战#r#W"
		
		local Readme_2 = "\t制作中，敬请期待#r"
		
		local Readme = Readme_1..Readme_2
		
		AddQuestText(sceneId, Readme);EndQuestEvent(sceneId);DispatchQuestEventList(sceneId,selfId,targetId);DispatchQuestInfoNM( sceneId, selfId, targetId, -1, -1,2 );
	
end

--**********************************
--列举事件
--**********************************
function x300749_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	--AddQuestNumText(sceneId,x300749_g_ScriptId,x300749_g_MissionName);
end


--********************
--检测接受条件
--**********************************
function x300749_ProcAcceptCheck( sceneId, selfId, NPCId )
		return 1
end

--**********************************
--接受
--**********************************
function x300749_ProcAccept( sceneId, selfId )

	
end

--**********************************
--放弃
--**********************************
function x300749_ProcQuestAbandon( sceneId, selfId, MissionId )

end

--**********************************
--继续
--**********************************
function x300749_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x300749_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x300749_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x300749_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x300749_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x300749_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
