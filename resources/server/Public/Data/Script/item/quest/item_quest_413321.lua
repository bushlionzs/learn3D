--��˹��ԭ�ٻ�����أ
x413321_g_scriptId  = 413321
x413321_g_Impact1   = 7520--Ч��ID�������Ӻ���
x413321_g_MissionId = 770
x413321_g_doing =0
x413321_g_xueliewu =0
x413321_g_mengguwushi1= 0
x413321_g_mengguwushi2=	0
x413321_g_mengguwushi3=	0
x413321_g_mengguwushi4=	0
x413321_g_mengguwushi5=	0
--**********************************
--�¼��������
--**********************************
function x413321_ProcEventEntry( sceneId, selfId, bagIndex )
    local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413321_g_Impact1 )
  		
    if bCplay == 1 then
    	if GetItemCount(sceneId,selfId,13060033) == 0 then
        x413321_g_xuliewu=CreateMonster(sceneId, 931,204,219,0,1,-1,-1,24,90000)
        x413321_g_mengguwushi1=CreateMonster(sceneId, 937,205,216,0,1,-1,-1,24,90000)
        x413321_g_mengguwushi2=CreateMonster(sceneId, 937,204,217,0,1,-1,-1,24,90000)
        x413321_g_mengguwushi3=CreateMonster(sceneId, 937,205,218,0,1,-1,-1,24,90000)
        x413321_g_mengguwushi4=CreateMonster(sceneId, 937,205,219,0,1,-1,-1,24,90000)
        x413321_g_mengguwushi5=CreateMonster(sceneId, 937,204,218,0,1,-1,-1,24,90000)
        CallScriptFunction( UTILITY_SCRIPT, "PlayEffect", sceneId, selfId, 19 )
    	end
    end

    return bCplay


-- ����Ҫ����ӿڣ���Ҫ�����պ���
end


function x413321_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413321_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413321_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413321_OnDeplete( sceneId, selfId )

	return 1
end

function x413321_OnActivateOnce( sceneId, selfId )
end

function x413321_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
