x413306_g_scriptId  = 413306 --�ٻ�������
x413306_g_Impact1   = -1--Ч��ID�������Ӻ���
x413306_g_MissionId = 672
x413306_g_doing =0
x413306_g_bailuotuo =0
x413306_g_luotuo1 =0
x413306_g_luotuo2 =0
x413306_g_tujueqibing =0
--**********************************
--�¼��������
--**********************************
function x413306_ProcEventEntry( sceneId, selfId, bagIndex )
    local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413306_g_Impact1 )
  
    if bCplay == 1 then
    
        x413306_g_bailuotuo=CreateMonster(sceneId, 849,161,113,1,1,-1,-1,20,9000)
        x413306_g_luotuo1=CreateMonster(sceneId, 861,157,111,1,1,-1,-1,20,9000)
        x413306_g_luotuo2=CreateMonster(sceneId, 861,163,115,1,1,-1,-1,20,9000)
        x413306_g_tujueqibing=CreateMonster(sceneId, 841,159,119,1,1,-1,-1,20,2000)
        SetPatrolId(sceneId, x413306_g_bailuotuo, 3)
        SetPatrolId(sceneId, x413306_g_luotuo1, 4)
        SetPatrolId(sceneId, x413306_g_luotuo2, 5)
        NpcTalk(sceneId, x413306_g_tujueqibing, "�����쿴�������գ����ʹ�߳����ˣ�", -1)
    end

    return bCplay


-- ����Ҫ����ӿڣ���Ҫ�����պ���
end


function x413306_IsSkillLikeScript( sceneId, selfId)
 
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x413306_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413306_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413306_OnDeplete( sceneId, selfId )

	return 1
end

function x413306_OnActivateOnce( sceneId, selfId )
end

function x413306_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
