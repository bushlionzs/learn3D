





x400217_g_scriptId = 400217 
x400217_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400217_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x400217_g_Impact1 )
			if GetItemCount(sceneId,selfId,13020412) == 0 then
						local talknpc2 =FindMonsterByGUID( sceneId,112006)
						if IsObjValid (sceneId,talknpc2) == 1 then
								NpcTalk(sceneId, talknpc2, "�����㲻Ҫ�����ˣ�", -1)
						end
			end
	

end

function x400217_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400217_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400217_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400217_OnDeplete( sceneId, selfId )

	return 0
end

function x400217_OnActivateOnce( sceneId, selfId )
end

function x400217_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
