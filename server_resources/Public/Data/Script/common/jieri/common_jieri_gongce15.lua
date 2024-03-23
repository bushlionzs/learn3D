-- 脚本号
x350014_g_ScriptId          = 350014
-- 活动名
x350014_g_Name              = "内测领奖"
-- 提示领取时间
x350014_g_strErrorTime      = "请在9月10日，9月11日，9月12日的20：00—20：30领取"
x350014_g_shuoming 		      = "\t为了让广大玩家在内测期间有充足的银两体验我们的各种精彩玩法，我们将给所有玩家免费发放海量封测“军饷”！人人都有，上线就有！9月10日、9月11日、9月12日每晚20:00至20:30限时发放，赶快上线领取吧，过期不候哟！\n\t\n\t9月10日可获得银卡#R100两#W。\n\t9月11日可获得银卡#R200两#W。\n\t9月12日可获得银卡#R300两#W。"

x350014_g_MD1 =MD_NEICE_LINGJIANG_TIME1
x350014_g_MD2 =MD_NEICE_LINGJIANG_TIME2
x350014_g_MD3 =MD_NEICE_LINGJIANG_TIME3
x350014_g_FeastId	  = 3


function x350014_IsFeastActive()
	
	if x350014_g_FeastId ~= MD_CURRENT_FEAST_ID then
				return 0
	end
	return 1
end

-- 点击NPC回调（点击NPC调用，界面中添加封测送金卡按钮）
function x350014_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
	
	if x350014_IsFeastActive() ~= 1	then
		return  
	end 
	
	local day = GetDayOfYear()
	if day < 252 or day > 254 then
		return
	end
	 
    AddQuestNumText( sceneId, x350014_g_ScriptId, x350014_g_Name, 3, 1)
end

-- 玩家点击NPC对话选项按钮后的回调（点击后，根据x350014_GetMoney( sceneId, selfId)返回的值确定是否进入领奖界面，不为0才能进入）
function x350014_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
	if x350014_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "活动没有开启", 8, 3)
        return
    end

        BeginQuestEvent( sceneId)  --1
            AddQuestText( sceneId, "#Y"..x350014_g_Name)  --2
            AddQuestText( sceneId, x350014_g_shuoming )
--         AddQuestMoneyBonus3( sceneId, money)
        EndQuestEvent() --3固定的格式
        DispatchQuestInfo( sceneId, selfId, NPCId, x350014_g_ScriptId, -1) 
end


-- 玩家点击确定（点击确定给钱，同时记录MD）
function x350014_ProcAcceptCheck( sceneId, selfId, NPCId)
	if x350014_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "活动没有开启", 8, 3)
        return
        end
	CallScriptFunction(888894,"Feast_SetCurrentId",sceneId,selfId,x350014_g_FeastId)

		local money = x350014_GetMoney( sceneId, selfId)

    if money ~= 0 then
        AddMoney( sceneId, selfId, 1, money)
    else
    	return 0
    end

    local y, m, d = GetYearMonthDay()
    if d == 10 then
        SetQuestData( sceneId, selfId, x350014_g_MD1[ 1], x350014_g_MD1[ 2], x350014_g_MD1[ 3], 1)
    elseif d == 11 then
        SetQuestData( sceneId, selfId, x350014_g_MD2[ 1], x350014_g_MD2[ 2], x350014_g_MD2[ 3], 1)
    elseif d ==12 then
    	SetQuestData( sceneId, selfId, x350014_g_MD3[ 1], x350014_g_MD3[ 2], x350014_g_MD3[ 3], 1)
    end

    return 1
end


function x350014_ProcAccept( sceneId, selfId, NPCId)
end


function x350014_GetMoney( sceneId, selfId)
	local y, m, d = GetYearMonthDay()
        local minute = GetMinOfDay()

        if m ~= 9 then
        	Msg2Player( sceneId, selfId, x350014_g_strErrorTime, 8, 3)
       		return 0	
        end

   	if d ~= 10 and d ~= 11 and d ~= 12 then
       		Msg2Player( sceneId, selfId, x350014_g_strErrorTime, 8, 3)
        	return 0
        end

        if minute < 1200 or minute > 1230 then
       		Msg2Player( sceneId, selfId,"只能在20：00—20：30领取银卡奖励", 8, 3)
        	return 0
        end
 

        if d == 10 then
        	if GetQuestData( sceneId, selfId, x350014_g_MD1[ 1], x350014_g_MD1[ 2], x350014_g_MD1[ 3] ) == 1 then
            		Msg2Player( sceneId, selfId, "今天的奖励你已经领取过了", 8, 3)
            	return 0
        else
            return 100000
        end
    end
    if d == 11 then
        if GetQuestData( sceneId, selfId, x350014_g_MD2[ 1], x350014_g_MD2[ 2], x350014_g_MD2[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "今天的奖励你已经领取过了", 8, 3)
            return 0
        else
            return 200000
        end
    end
    if d == 12 then
        if GetQuestData( sceneId, selfId, x350014_g_MD3[ 1], x350014_g_MD3[ 2], x350014_g_MD3[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "今天的奖励你已经领取过了", 8, 3)
            return 0
        else
            return 300000
        end
    end
end





















