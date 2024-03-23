--�ű���
x300986_g_ScriptId  = 300986
-- Game open id
x300986_g_OpenID    = 1059

--**********************************
--������ں���
--**********************************
function x300986_ProcEventEntry( sceneId, selfId, NPCId)	--����������ִ�д˽ű�
    if GetInherenceLevel( sceneId, selfId) < 50 then
        Msg2Player( sceneId, selfId, "�����츳�ȼ�С��50�������ܽ��д˲���", 8, 3)
        return
    end

    if GetGameOpenById( x300986_g_OpenID) <= 0 then
        return 0
    end

    BeginUICommand( sceneId)
        UICommand_AddInt( sceneId, NPCId)
        DispatchUICommand( sceneId, selfId, 109)
    EndUICommand( sceneId)
end

--**********************************
--�о��¼�
--**********************************
function x300986_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    if GetGameOpenById( x300986_g_OpenID) <= 0 then
        return 0
    end

    AddQuestNumText( sceneId, x300986_g_ScriptId, "ר���츳ר��ѵ��", 3, 1)
end


--**********************************
--����������
--**********************************
function x300986_ProcAcceptCheck( sceneId, selfId, NPCId)
end

--**********************************
--����
--**********************************
function x300986_ProcAccept( sceneId, selfId)
end

