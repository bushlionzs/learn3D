
--MisDescBegin
--�ű���
x800089_g_ScriptId = 800089

--�����ı�����
x800089_g_MissionName="װ����¯��ϴ����"

--MisDescEnd

--**********************************
--������ں���
--**********************************
function x800089_ProcEventEntry( sceneId, selfId, targetId )	--����������ִ�д˽ű�
end

--********************
--����������
--**********************************
function x800089_ProcAcceptCheck( sceneId, selfId, NPCId )

		return 1
		
end

function x800089_ProcEnumEvent( sceneId, selfId, targetId, MissionId )

	AddQuestNumText(sceneId,x800089_g_ScriptId,x800089_g_MissionName,3);

end
