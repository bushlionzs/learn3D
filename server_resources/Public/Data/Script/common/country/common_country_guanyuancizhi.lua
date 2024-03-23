
x310200_g_ScriptId = 310200


--任务文本描述
x310200_g_MissionName="【国家】官员辞职"


--**********************************
--任务入口函数
--**********************************
function x310200_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	if  CountryGetOfficial(sceneId,selfId)~=6 
	and CountryGetOfficial(sceneId,selfId)~=5
	and CountryGetOfficial(sceneId,selfId)~=4
	and CountryGetOfficial(sceneId,selfId)~=3
	and CountryGetOfficial(sceneId,selfId)~=2	then
		return
	end
	AddQuestNumText(sceneId,x310200_g_ScriptId,x310200_g_MissionName,3)
end
function x310200_ProcEventEntry( sceneId, selfId, targetId )	--点击该任务后执行此脚本	

	local Readme_1 = "#Y【国家】官员辞职#W#r #r"	
	local Readme_2 = "\t作为一名国家官员，不仅仅是荣誉，也是一种#G责任#W。 #r"
	local Readme_3 = "\t如果你因为一时不快不再想担任你目前的国家职务，那么我建议你冷静下来再做决定，如果你已经经过了#G深思熟虑#W，那么我可以帮你办理辞去国家职务的手续。#r"
	local Readme_4 = "\t不过国王和王后是不可以辞职的，只有大将军、左丞、右相、金牌左捕、金牌右捕可以辞职。#r"
	local Readme = Readme_1..Readme_2..Readme_3..Readme_4		
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId, Readme)
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo( sceneId, selfId, targetId, x310200_g_ScriptId, -1 )
	
end

--**********************************
--列举事件
--**********************************



--********************
--检测接受条件
--**********************************
function x310200_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 1
end

--**********************************
--接受
--**********************************
function x310200_ProcAccept( sceneId, selfId )
	if  CountryGetOfficial(sceneId,selfId)~=6 
	and CountryGetOfficial(sceneId,selfId)~=5
	and CountryGetOfficial(sceneId,selfId)~=4
	and CountryGetOfficial(sceneId,selfId)~=3
	and CountryGetOfficial(sceneId,selfId)~=2	then
		return
	end
		DismissCountryOfficial_Self(sceneId, selfId)
		Msg2Player( sceneId,selfId, "恭喜您，辞职成功。", 8, 2 )	
end

--**********************************
--放弃
--**********************************
function x310200_ProcQuestAbandon( sceneId, selfId, MissionId )	
end

--**********************************
--继续
--**********************************
function x310200_OnContinue( sceneId, selfId, targetId )

end

--**********************************
--检测是否可以提交
--**********************************
function x310200_CheckSubmit( sceneId, selfId )

end

--**********************************
--提交
--**********************************
function x310200_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId )

end

--**********************************
--杀死怪物或玩家
--**********************************
function x310200_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId )

end

--**********************************
--进入区域事件
--**********************************
function x310200_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
end

--**********************************
--道具改变
--**********************************
function x310200_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId )
end
