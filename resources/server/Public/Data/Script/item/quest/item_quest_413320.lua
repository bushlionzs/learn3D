--��˹��ԭ�ٻ�����
x413320_g_scriptId  = 413320
x413320_g_Impact1   = -1--Ч��ID�������Ӻ���
x413320_g_MissionId = 765
x413320_g_doing =0
x413320_g_jianling =0
--**********************************
--�¼��������
--**********************************
function x413320_ProcEventEntry( sceneId, selfId, bagIndex )
    local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413320_g_Impact1 )
  		
    if bCplay == 1 then
    	if GetItemCount(sceneId,selfId,13060032) == 0 then
        x413320_g_jianling=CreateMonster(sceneId, 930,119,224,5,1,-1,-1,21,60000)
        CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 19 )
    	end
    end

    return bCplay


-- ����Ҫ����ӿڣ���Ҫ�����պ���
end


function x413320_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413320_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413320_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413320_OnDeplete( sceneId, selfId )

	return 1
end

function x413320_OnActivateOnce( sceneId, selfId )
end

function x413320_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
