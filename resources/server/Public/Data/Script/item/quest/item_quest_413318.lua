--ͻ�������ٻ���������
x413318_g_scriptId  = 413318
x413318_g_Impact1   = -1--Ч��ID�������Ӻ���
x413318_g_MissionId = 705
x413318_g_doing =0
x413318_g_shashe =0
--**********************************
--�¼��������
--**********************************
function x413318_ProcEventEntry( sceneId, selfId, bagIndex )
    local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413318_g_Impact1 )
  		
    if bCplay == 1 then
    	if GetItemCount(sceneId,selfId,13060022) == 0 then
        x413318_g_shashe=CreateMonster(sceneId, 907,210,94,5,1,-1,-1,21,60000)
        CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 19 )
    	end
    end

    return bCplay


-- ����Ҫ����ӿڣ���Ҫ�����պ���
end


function x413318_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413318_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413318_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413318_OnDeplete( sceneId, selfId )

	return 1
end

function x413318_OnActivateOnce( sceneId, selfId )
end

function x413318_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
