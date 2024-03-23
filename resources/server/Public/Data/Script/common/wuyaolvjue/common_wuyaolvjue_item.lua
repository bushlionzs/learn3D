x310021_g_scriptId = 310021 
x310021_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x310021_ProcEventEntry( sceneId, selfId, BagIndex )
	local ItemID = GetItemTableIndexByIndex( sceneId, selfId, BagIndex ) --�õ���ƷID
	local MissionId = GetQuestIDByItemIDNM( sceneId, selfId, ItemID )

	if MissionId == -1 then 	--û���ҵ��������
		return 0
	end

	if IsHaveQuestNM( sceneId, selfId, MissionId ) == 0 then	-- ���û�������ֱ���˳�
		return 0
	end

	local misIndex = GetQuestIndexByID( sceneId, selfId, MissionId )
	local level = GetQuestParam( sceneId, selfId, misIndex, 2 ) 

	if MissionId>= 8000 and MissionId<=8004 then
		CallScriptFunction( 310020, "PositionUseItem", sceneId, selfId, BagIndex, x310021_g_Impact1 )
	elseif MissionId>=8005 and MissionId<=8009 then
		CallScriptFunction( 310022, "PositionUseItem", sceneId, selfId, BagIndex, x310021_g_Impact1 )
	end

end

function x310021_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x310021_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x310021_OnConditionCheck( sceneId, selfId )
	return 0
end

function x310021_OnDeplete( sceneId, selfId )

	return 0
end

function x310021_OnActivateOnce( sceneId, selfId )
end

function x310021_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
