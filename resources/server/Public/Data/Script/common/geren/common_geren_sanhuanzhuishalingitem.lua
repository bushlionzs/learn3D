
x270356_g_scriptId = 270356

x270356_g_MissionScriptTab 		= 	{ 270350,270351,270352,270353}		--�ĸ����ҵ�����ű���

function x270356_ProcEventEntry( sceneId, selfId, bagIndex )
	print("x270356_ProcEventEntry")
	local nCountryId = GetCurCountry(sceneId,selfId )
	local bCplay =  CallScriptFunction( x270356_g_MissionScriptTab[nCountryId+1], "DenoteMonsterPosition", sceneId, selfId, bagIndex )
end

function x270356_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

 end

function x270356_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
 
end

function x270356_OnConditionCheck( sceneId, selfId )
	return 0
end

function x270356_OnDeplete( sceneId, selfId )
	return 0
end

function x270356_OnActivateOnce( sceneId, selfId )
	print("x270356_OnActivateOnce")
end

function x270356_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
