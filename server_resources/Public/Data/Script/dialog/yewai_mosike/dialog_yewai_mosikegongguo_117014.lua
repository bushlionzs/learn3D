 --密探
x203326_g_ScriptId	= 203326
x203326_g_MissionId	=	806
--**********************************
--事件交互入口
--**********************************
function x203326_ProcEventEntry( sceneId, selfId,targetId ) 
local misIndex = GetQuestIndexByID(sceneId, selfId,x203326_g_MissionId) 
  if GetQuestParam(sceneId, selfId,misIndex,7,1)  < 1 then
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"\t你是什么人？找我有事么？没事别挡着大爷在这里欣赏风景！")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	ShowNpcQuestEventList(sceneId,selfId,targetId)
	end
	if GetQuestParam(sceneId, selfId,misIndex,7,1) == 1 then
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"\t英雄！别再打我了，我也只是为了讨生活才替那些老爷们做事！")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	ShowNpcQuestEventList(sceneId,selfId,targetId)
	end
end

function x203326_OnDie(sceneId, selfId, killerId)
	SetMonsterCamp(sceneId,selfId,20)
end