





x400216_g_scriptId = 400216 
x400216_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400216_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x400216_g_Impact1 )
			if GetItemCount(sceneId,selfId,13020412) == 0 then
						local talknpc =FindMonsterByGUID( sceneId,112027)
						if IsObjValid (sceneId,talknpc) == 1 then
								NpcTalk(sceneId, talknpc, "���꣡���ɼ�˼�����꣡", -1)
						end
						local talknpc2 =FindMonsterByGUID( sceneId,112028)
						if IsObjValid (sceneId,talknpc2) == 1 then
								NpcTalk(sceneId, talknpc2, "����֮���ɼ�˼�����꣡", -1)
						end
			end
	

end

function x400216_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400216_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400216_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400216_OnDeplete( sceneId, selfId )

	return 0
end

function x400216_OnActivateOnce( sceneId, selfId )
end

function x400216_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
