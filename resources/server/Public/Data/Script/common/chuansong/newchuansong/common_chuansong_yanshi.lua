--����ʾ����

x550007_g_ScriptId 					= 550007
x550007_g_MissionName				= "��ʾ����"
-------------------------
--***********************
--ProcEnumEvent
--***********************
-------------------------

function x550007_ProcEnumEvent(sceneId, selfId, targetId, MissionId)
	
	AddQuestNumText(sceneId, x550007_g_ScriptId, x550007_g_MissionName);
	
end

-------------------------
--***********************
--ProcEventEntry
--***********************
-------------------------

function x550007_ProcEventEntry(sceneId, selfId, targetId)

		DispatchTransferType(sceneId, selfId, selfId, 8, -1)
end

-------------------------
--***********************
--ProcAcceptCheck
--***********************
-------------------------

function x550007_ProcAcceptCheck(sceneId, selfId, targetId)

end

-------------------------
--***********************
--ProcAccept
--***********************
-------------------------

function x550007_ProcAccept(sceneId, selfId, targetId)

end
function x550007_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��
end
function x550007_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end
function x550007_OnConditionCheck( sceneId, selfId )
	return 1
end
function x550007_OnDeplete( sceneId, selfId )
	DispatchTransferType(sceneId, selfId, selfId, 2, -1)
	return 0
end