 --��ľ�������Ի�

--**********************************
--�¼��������
--**********************************
function x101001_ProcEventEntry( sceneId, selfId,targetId )
	BeginQuestEvent(sceneId)
	AddQuestText(sceneId,"\t�����ӷ𣬷��ž�����ʩ����Ҫ�������ߡ�")
	EndQuestEvent(sceneId)
	if IsHaveQuest(sceneId,selfId, 3574) > 0 then
				AddQuestNumText(sceneId, 3574, "ɫ���ǿ�",0, 2)
	end
	DispatchQuestEventList(sceneId,selfId,targetId)
	ShowNpcQuestEventList(sceneId,selfId,targetId)
end

function x101001_OnDie(sceneId, selfId, killerId)
	SetMonsterCamp(sceneId,selfId,20)
end