 --��ľ�������Ի�

--**********************************
--�¼��������
--**********************************
function x101000_ProcEventEntry( sceneId, selfId,targetId )
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"\t����ʲô�ˣ����Ŵ�ү�ĺ��¡�")
	EndQuestEvent(sceneId)
	if IsHaveQuest(sceneId,selfId, 3568) > 0 then
		if GetItemCount(sceneId,selfId,13020312) < 1 then
				AddQuestNumText(sceneId, 3568, "����������ɵ�Ů������",0, 1)
		end
	end
	DispatchQuestEventList(sceneId,selfId,targetId)
	ShowNpcQuestEventList(sceneId,selfId,targetId)
end

function x101000_OnDie(sceneId, selfId, killerId)
	SetMonsterCamp(sceneId,selfId,20)
end