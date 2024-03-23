--MisDescBegin 
x300837_g_ScriptId 					= 	300837
--MisDescEnd

-- x300837_g_BroadCastTable            = {
                                        -- { minute = 1020, clocktime = 1700, message = "���籭ս������17��30������������������׼����" }, 
                                        -- { minute = 1045, clocktime = 1725, message = "���籭ս������5���Ӻ�ʼ��" }, 
                                        -- { minute = 1050, clocktime = 1730, message = "���籭ս�����Ƚ�����" }, 
                                        -- { minute = 1065, clocktime = 1745, message = "���籭ս�����Ƚ�����" }, 
                                        -- { minute = 1075, clocktime = 1755, message = "���籭ս�����籭ս����������5���ӣ�" }, 
                                        -- { minute = 1080, clocktime = 1800, message = "���籭ս�����籭ս���Ѿ�������" }, 
-- }
x300837_g_BroadCastTable            = {
                                        { minute = 930, clocktime = 1530, message = "���籭ս������16��00������������������׼����" }, 
                                        { minute = 955, clocktime = 1555, message = "���籭ս������5���Ӻ�ʼ��" }, 
                                        { minute = 960, clocktime = 1600, message = "���籭ս�����Ƚ�����" }, 
                                        { minute = 975, clocktime = 1615, message = "���籭ս�����Ƚ�����" }, 
                                        { minute = 985, clocktime = 1625, message = "���籭ս����������5���ӣ�" }, 
                                        { minute = 990, clocktime = 1630, message = "���籭ս���Ѿ�������" }, 
}

function x300837_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
    -- ���ĵ����ղŹ㲥����Ϣ
    local week, YearIndex = GetWeek()
    if week ~= 0 then
        return
    end

    -- ������ڽ�ֹ�����׶μ�ʹɱ��ʮ��ħ��Ҳ���㲥��Ϣ
    local state = GetWorldCupState( sceneId)
    if state == STATE_GUILD_WORLDCUP_DISABLESIGNUP then
        return
    end

    local switch = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_SWITCH)
    -- �����������������Timer
    if switch == 1 then
        SetSystemTimerTick( sceneId, 300837, "BroadCast", actId, 60000)
    end
end

function x300837_BroadCast( sceneId, actId, uTime)
    local curTime = GetMinOfDay()

    local broadcast = 0
    for i, item in x300837_g_BroadCastTable do
        if curTime == item.minute then
            broadcast = i
            break
        end
    end

    if broadcast ~= 0 then
        LuaAllScenceM2Wrold( sceneId, x300837_g_BroadCastTable[ broadcast].message, CHAT_PLANE_SCROLL, 1)
        LuaAllScenceM2Wrold( sceneId, x300837_g_BroadCastTable[ broadcast].message, CHAT_LEFTDOWN, 1)
        if broadcast == getn( x300837_g_BroadCastTable) then
            -- ���һ�δ���Timer�������ö�ʱ��
            return
        end
    end
    SetSystemTimerTick( sceneId, 300837, "BroadCast", actId, 60000)
end

