--ͻ�������ٻ�ͻ�ʷ���
x413312_g_scriptId  = 413312
x413312_g_Impact1   = -1--Ч��ID�������Ӻ���
x413312_g_MissionId = 710
x413312_g_doing =0
x413312_g_shashe =0
--**********************************
--�¼��������
--**********************************
function x413312_ProcEventEntry( sceneId, selfId, bagIndex )
    local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413312_g_Impact1 )
  		
    if bCplay == 1 then
    	if GetItemCount(sceneId,selfId,13060025) == 0 then
        x413312_g_shashe=CreateMonster(sceneId, 908,86,155,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,85,154,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,85,165,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,86,160,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,85,160,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,84,160,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,86,165,5,1,-1,-1,21,60000)
        x413312_g_shashe=CreateMonster(sceneId, 908,86,150,5,1,-1,-1,21,60000)
        CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 15 )
    	end
    end

    return bCplay


-- ����Ҫ����ӿڣ���Ҫ�����պ���
end


function x413312_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413312_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413312_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413312_OnDeplete( sceneId, selfId )

	return 1
end

function x413312_OnActivateOnce( sceneId, selfId )
end

function x413312_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
