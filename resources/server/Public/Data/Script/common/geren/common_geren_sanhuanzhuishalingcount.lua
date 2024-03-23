x270355_g_ScriptId 	  = 270355

function x270355_CountCheck( sceneId, selfId)
    -- 检查本周副本计次
    --print("x270355_CountCheck")
    local week = GetWeekIndex()
    local today = GetDayOfYear()
    --print( week, GetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_DATE[1], MD_FUBEN_QIULONGDAO_DATE[2], MD_FUBEN_QIULONGDAO_DATE[3] ) )
    if week == GetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_DATE[1], MD_FUBEN_QIULONGDAO_DATE[2], MD_FUBEN_QIULONGDAO_DATE[3] ) then
        if GetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1], MD_FUBEN_QIULONGDAO_DAYCOUNT[2], MD_FUBEN_QIULONGDAO_DAYCOUNT[3] ) >= 21 then
            return 0, "你本周已经不能再领取此任务了"
        end
    else
        SetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_DATE[1], MD_FUBEN_QIULONGDAO_DATE[2], MD_FUBEN_QIULONGDAO_DATE[3], week)
        SetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAY[1], MD_FUBEN_QIULONGDAO_TODAY[2], MD_FUBEN_QIULONGDAO_TODAY[3], today)
        SetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1], MD_FUBEN_QIULONGDAO_DAYCOUNT[2], MD_FUBEN_QIULONGDAO_DAYCOUNT[3], 0)
        SetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3], 0)
        x270355_SetTimes( sceneId, selfId, 0)
    end

    -- 检查今天副本是否已经做了6次
    if today == GetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAY[1], MD_FUBEN_QIULONGDAO_TODAY[2], MD_FUBEN_QIULONGDAO_TODAY[3] ) then
    	local daycount = GetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3] )
    	
    	local Times = x270355_GetTimes( sceneId, selfId)
    	--print("daycount",daycount,Times)
    	if (daycount == 6 and Times == 0 ) or (daycount >= 6 and Times >= 10 ) or (daycount > 6) then
	        return 0, "你今天已经不能再领取此任务了"
	    end
    else
        SetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAY[1], MD_FUBEN_QIULONGDAO_TODAY[2], MD_FUBEN_QIULONGDAO_TODAY[3], today)
        SetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3], 0)
    end

    return 1
end

function x270355_UpdateCount( sceneId, selfId, circle)
    local weekCount = GetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1], MD_FUBEN_QIULONGDAO_DAYCOUNT[2], MD_FUBEN_QIULONGDAO_DAYCOUNT[3] )
    local dayCount = GetQuestData(sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3] )
    -- 更新环数
    if x270355_GetTimes( sceneId, selfId) >= 10 then
        x270355_SetTimes( sceneId, selfId, 0)
    end
    
    
    
    if x270355_GetTimes( sceneId, selfId) == 0 then
        SetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1], MD_FUBEN_QIULONGDAO_DAYCOUNT[2], MD_FUBEN_QIULONGDAO_DAYCOUNT[3], weekCount + 1)
        SetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3], dayCount + 1)
    end
    
    
    if x270355_GetTimes( sceneId, selfId) + circle > 10 then
        if weekCount < 21 then
        	SetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1], MD_FUBEN_QIULONGDAO_DAYCOUNT[2], MD_FUBEN_QIULONGDAO_DAYCOUNT[3], weekCount + 1)
        end
        if dayCount < 6 then
        	SetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3], dayCount + 1)
        end
        x270355_SetTimes( sceneId, selfId, x270355_GetTimes( sceneId, selfId) + circle - 10)
    else
--    	if x270355_GetTimes( sceneId, selfId) == 9 then
--            if GetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1], MD_FUBEN_QIULONGDAO_DAYCOUNT[2], MD_FUBEN_QIULONGDAO_DAYCOUNT[3] ) == 21 then
--                SetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_DAYCOUNT[1], MD_FUBEN_QIULONGDAO_DAYCOUNT[2], MD_FUBEN_QIULONGDAO_DAYCOUNT[3], weekCount + 1)
--            end
--            if GetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3] ) == 6 then
--                SetQuestData( sceneId, selfId, MD_FUBEN_QIULONGDAO_TODAYCOUNT[1], MD_FUBEN_QIULONGDAO_TODAYCOUNT[2], MD_FUBEN_QIULONGDAO_TODAYCOUNT[3], dayCount + 1)
--            end
--        end
        x270355_SetTimes( sceneId, selfId, x270355_GetTimes( sceneId, selfId) + circle)
    end
end

function x270355_GetTimes( sceneId, selfId)
    return GetQuestData( sceneId, selfId, MD_ZHUISHA_CIRCLE[ 1], MD_ZHUISHA_CIRCLE[ 2], MD_ZHUISHA_CIRCLE[ 3] )
end

function x270355_SetTimes( sceneId, selfId, value)
    SetQuestData( sceneId, selfId, MD_ZHUISHA_CIRCLE[ 1], MD_ZHUISHA_CIRCLE[ 2], MD_ZHUISHA_CIRCLE[ 3], value)
end

