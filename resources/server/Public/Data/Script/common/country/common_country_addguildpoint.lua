--�ﹱ������
--��Ӱﹱ

--************************************************************************
--MisDescBegin

--�ű���
x300306_g_ScriptId = 300306


--�����ı�����
x300306_g_MissionName="�񰡣�����Ұﹱ�ɣ�"
x300306_g_MissionInfo="��������100�ﹱ�ɣ�"

function x300306_ProcEventEntry( sceneId, selfId, targetId )
--AddGuildUserPoint(sceneId,selfId,100)
	BeginQuestEvent(sceneId)
		
		AddQuestText(sceneId,x300306_g_MissionInfo)
	
	EndQuestEvent(sceneId)
	DispatchQuestInfo(sceneId,selfId,targetId,x300306_g_ScriptId,-1)
	
end

--**********************************
function x300306_ProcAcceptCheck( sceneId, selfId, NPCId )

	return	1

end

--**********************************
function x300306_ProcAccept( sceneId, selfId )

	AddGuildUserPoint(sceneId,selfId,100)

end

--**********************************

function x300306_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
--	AddGuildUserPoint(sceneId,selfId,100)
	AddQuestNumText(sceneId, x300306_g_ScriptId, x300306_g_MissionName)
end