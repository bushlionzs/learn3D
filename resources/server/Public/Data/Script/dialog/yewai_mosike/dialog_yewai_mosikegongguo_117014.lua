 --��̽
x203326_g_ScriptId	= 203326
x203326_g_MissionId	=	806
--**********************************
--�¼��������
--**********************************
function x203326_ProcEventEntry( sceneId, selfId,targetId ) 
local misIndex = GetQuestIndexByID(sceneId, selfId,x203326_g_MissionId) 
  if GetQuestParam(sceneId, selfId,misIndex,7,1)  < 1 then
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"\t����ʲô�ˣ���������ô��û�±��Ŵ�ү���������ͷ羰��")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	ShowNpcQuestEventList(sceneId,selfId,targetId)
	end
	if GetQuestParam(sceneId, selfId,misIndex,7,1) == 1 then
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"\tӢ�ۣ����ٴ����ˣ���Ҳֻ��Ϊ�������������Щ��ү�����£�")
	EndQuestEvent(sceneId)
	DispatchQuestEventList(sceneId,selfId,targetId)
	ShowNpcQuestEventList(sceneId,selfId,targetId)
	end
end

function x203326_OnDie(sceneId, selfId, killerId)
	SetMonsterCamp(sceneId,selfId,20)
end