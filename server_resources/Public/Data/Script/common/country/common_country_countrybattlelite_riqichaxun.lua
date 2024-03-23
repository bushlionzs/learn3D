--点击（NPC）
x310158_g_ScriptId 					= 	310158   
-- 屠城战玩法开关ID
x310158_g_GameOpenId                = 1026
								  							   
function x310158_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
    if GetGameOpenById(x310158_g_GameOpenId) <= 0 then
		return
	end
	AddQuestNumText(sceneId,310158,"【国家】查询屠城战日期",3)	
end



--点击（按钮）点击该任务后执行此脚本
function x310158_ProcEventEntry( sceneId, selfId, targetId)		
		--local MissionName = x300767_g_MissionName;
		BeginQuestEvent(sceneId)
			local Readme_1 = "#Y【国家】查询屠城战日期#r#W #r"			
			
			local Readme_2 = "\t屠城战每#G两周#W开启一次，开启日期为#G当周的周六晚上（20：00-21：00）#W，您可以在我这里查询#G本周#W屠城战是否开启。 #r#r"
			
			local Readme_3 = "#r #r屠城战开启时间为:#R#r"
			
			
			local Readme = Readme_1..Readme_2..Readme_3	
			
			
			local y,m,d = CountryBattleLite_GetNextStartDate()
			local str   ="(20:00-21:00)"
			local msg = format("%s%d-%02d-%02d%s",Readme,y,m,d,str)
			
		AddQuestText( sceneId,msg)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,targetId);
		
end



--点击（确定）
function x310158_ProcAcceptCheck( sceneId, selfId, NPCId )

end



--**********************************
--接受
--**********************************
function x310158_ProcAccept( sceneId, selfId )
end
--**********************************
--放弃
--**********************************
function x310158_ProcQuestAbandon( sceneId, selfId, MissionId )
end
--**********************************
--继续
--**********************************
function x310158_OnContinue( sceneId, selfId, targetId )
end
--**********************************
--检测是否可以提交
--**********************************
function x310158_CheckSubmit( sceneId, selfId )
end
--**********************************
--提交
--**********************************
function x310158_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )
end
--**********************************
--杀死怪物或玩家
--**********************************
function x310158_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )
end
--**********************************
--进入区域事件
--**********************************
function x310158_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end
--**********************************
--道具改变
--**********************************
function x310158_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end