-- �������޻

-- �ű���
x310801_g_ScriptId = 310801						

function x310801_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
    --SetSystemTimerTick( sceneId, 310801, "BroadCast", actId, 10 * 1000)
    if sceneId ~= 88 and sceneId ~= 188 and sceneId ~= 288 and sceneId ~= 388 then
        return
    end

    local day = GetDayOfYear()
    local rx = random( 3, 5)
    local rz = random( 3, 5)
    -- 2010��2��14����2��22��(branch)
    if day >= 44 and day <= 52  then
        CreateMonster( sceneId, 9752, 84 + rx, 164 + rz, 1, 1006, x310801_g_ScriptId, -1, 21, 3600000, 0)
        LuaAllScenceM2Wrold( sceneId, "���ꡱͻȻ���������������������Ӷ�Ǯ��ƻ�����ϲ�졣��������ʿ����ǰ��������԰�����������޿ɻ�ô�������Ŷ����", CHAT_PLANE_SCROLL, 1)
    end
end

function x310801_OnDie( sceneId, selfId, killerId)
    LuaAllScenceM2Wrold( sceneId, "����������ʿ�ķ��µֿ������ꡱ�ѱ�����", CHAT_PLANE_SCROLL, 1)
end

