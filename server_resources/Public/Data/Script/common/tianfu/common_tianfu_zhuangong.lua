-- �ű���
x300985_g_ScriptId  = 300985
-- Game open id
x300985_g_OpenID    = 1058

--**********************************
--������ں���
--**********************************
function x300985_ProcEventEntry( sceneId, selfId, NPCId)	--����������ִ�д˽ű�
    if GetInherenceLevel( sceneId, selfId) < 50 then
        Msg2Player( sceneId, selfId, "�����츳�ȼ�С��50�������ܽ��д˲���", 8, 3)
        return
    end

    if GetGameOpenById( x300985_g_OpenID) <= 0 then
        return 0
    end

    BeginUICommand( sceneId)
        UICommand_AddInt( sceneId, NPCId)
        DispatchUICommand( sceneId, selfId, 108)
    EndUICommand( sceneId)
end

--**********************************
--�о��¼�
--**********************************
function x300985_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    if GetGameOpenById( x300985_g_OpenID) <= 0 then
        return 0
    end

    AddQuestNumText( sceneId, x300985_g_ScriptId, "ר���츳ר��ѵ��", 3, 1)
end


--**********************************
--����������
--**********************************
function x300985_ProcAcceptCheck( sceneId, selfId, NPCId)
end

--**********************************
--����
--**********************************
function x300985_ProcAccept( sceneId, selfId)
end

