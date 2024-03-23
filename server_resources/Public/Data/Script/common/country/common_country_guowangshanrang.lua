
x310201_g_ScriptId = 310201


--任务文本描述
x310201_g_MissionName="【国家】国王禅让"


--**********************************
--任务入口函数
--**********************************
function x310201_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if CountryGetOfficial(sceneId,selfId)~=8 then
		return
	end
	AddQuestNumText(sceneId,x310201_g_ScriptId,x310201_g_MissionName,3)	
end

function x310201_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本	
      
        
	local Readme_1 = "#Y【国家】国王禅让#W#r #r"	
	local Readme_2 = "\t尊敬的国王陛下，您真的愿意将您所在的尊崇无比的国王位置禅让给您的副帮主吗？#r"
	local Readme_3 = "\t如果你因为一时不快不再想担任国王了，那么我建议你冷静下来再做决定，如果你已经经过了#G深思熟虑#W，那么我可以帮你办理禅让国王的手续。#r"
	local Readme_4 = "\t每周#G除周二和周日以外#W的任何时间，您都可以在我这里进行禅让，但是#G每天#W只能禅让#G一次#W，您需要将您的国王位置和国家大权#G交给#W您的#G副帮主#W吗？#r"
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4		
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo( sceneId, selfId, targetId, x310201_g_ScriptId, -1 )
	
end

--**********************************
--列举事件
--**********************************



--********************
--检测接受条件
--**********************************
function x310201_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

--**********************************
--接受
--**********************************
function x310201_ProcAccept( sceneId, selfId )
	if CountryGetOfficial(sceneId,selfId)~=8 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，您不是国王，没有禅让王位的权利。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，您不是国王，没有禅让王位的权利。",8,2)	
		return
	end
	
	if GetWeek() == 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，周日不能进行国王禅让。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，周日不能进行国王禅让。",8,2)
		return
	end		
	
	if GetWeek() == 2 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, "很抱歉，周二不能进行国王禅让。")
		DispatchQuestTips(sceneId, selfId)
		EndQuestEvent(sceneId)
		Msg2Player(sceneId,selfId,"很抱歉，周二不能进行国王禅让。",8,2)
		return
	end
		CountryGuildDemise(sceneId, selfId)
		
end

--**********************************
--放弃
--**********************************
function x310201_ProcQuestAbandon( sceneId, selfId, MissionId )	
end

--**********************************
--继续
--**********************************
function x310201_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x310201_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x310201_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x310201_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x310201_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x310201_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
