
x561110_g_ScriptId = 561110
x561110_g_GameId = 1036
x561110_g_MissionName = "��ȡcd-key���"

--�����NPC��
function x561110_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x561110_g_ScriptId,x561110_g_MissionName,3,-1)
	
end


--�������ť������������ִ�д˽ű�
function x561110_ProcEventEntry( sceneId, selfId, targetId,state,index )	

	if GetGameOpenById( x561110_g_GameId) <= 0 then
        x561110_ShowTips(sceneId, selfId, targetId, "�˻�ѹر�")
		return 0
    end
    
	--��¼��ǰ�콱NPCID���Ա��ڷ��ض�λ
	SetPlayerRuntimeData( sceneId, selfId, RD_HUMAN_CURR_AWARD_NPCID,targetId  )
	
	--֪ͨ�ͻ��˴򿪶Ի���
	OpenAwardBox( sceneId, selfId )

end


function x561110_ShowTips(sceneId, selfId,targetId, str)

	BeginQuestEvent(sceneId);
		AddQuestText(sceneId,str);
	EndQuestEvent();
	
	DispatchQuestEventList(sceneId,selfId,targetId)
	DispatchQuestInfo(sceneId, selfId, targetId, x561110_g_ScriptId, -1);
	
end

function x561110_ProcAccept( sceneId, selfId )
	return 0
end

function x561110_ProcAcceptCheck( sceneId, selfId, NPCId )
	return 0
end

function x561103_ProcQuestAccept( sceneId, selfId, NPCId )
end