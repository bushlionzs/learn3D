--�����г���

x550005_g_ScriptId 					= 550005
x550005_g_MissionName				= "���г���"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x550005_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	AddQuestNumText(sceneId, x550005_g_ScriptId, x550005_g_MissionName);
	
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x550005_ProcEventEntry(sceneId, selfId, targetId)

		DispatchTransferType(sceneId, selfId, selfId, 2, -1)
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x550005_ProcAcceptCheck(sceneId, selfId, targetId)

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x550005_ProcAccept(sceneId, selfId, targetId)

end
function x550005_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��
end
function x550005_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end
function x550005_OnConditionCheck( sceneId, selfId )
	return 1
end
function x550005_OnDeplete( sceneId, selfId )
	DispatchTransferType(sceneId, selfId, selfId, 2, -1)
	return 0
end