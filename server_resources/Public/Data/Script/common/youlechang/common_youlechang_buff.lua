
x310329_g_ScriptId = 310329
x310329_g_BuffId = 8400
x310329_g_Pos              = {x = 127, z = 79}

--�������ʱ����
function x310329_OnIntervalOverEvent( sceneId, selfId)
end

--��Чʱ����
function x310329_OnActiveEvent( sceneId, selfId )
end

--Ч����ɢʱ����
function x310329_OnFadeOutEvent( sceneId, selfId )
    if sceneId == 39 or sceneId == 40 then
        NewWorld( sceneId, selfId, 36, x310329_g_Pos.x, x310329_g_Pos.z, 310320)
    end

end

--**********************************
--�¼��������
--**********************************
function x310329_ProcEventEntry( sceneId, selfId, bagIndex)
end


