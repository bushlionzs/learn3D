x413303_g_scriptId  = 413303--�ٻ�ɳ�߽ű�
x413303_g_Impact1   = -1--Ч��ID�������Ӻ���
x413303_g_MissionId = 474
x413303_g_doing =0
x413303_g_shashe =0
--**********************************
--�¼��������
--**********************************
function x413303_ProcEventEntry( sceneId, selfId, bagIndex )
    local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413303_g_Impact1 )
  
    if bCplay == 1 then
        x413303_g_shashe=CreateMonster(sceneId, 816,186,200,5,1,-1,-1,21,120000)
        x413303_g_shashe=CreateMonster(sceneId, 816,184,213,5,1,-1,-1,21,120000)
    end

    return bCplay


-- ����Ҫ����ӿڣ���Ҫ�����պ���
end


function x413303_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413303_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413303_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413303_OnDeplete( sceneId, selfId )

	return 1
end

function x413303_OnActivateOnce( sceneId, selfId )
end

function x413303_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
