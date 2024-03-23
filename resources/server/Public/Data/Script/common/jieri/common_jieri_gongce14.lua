-- 脚本号
x350013_g_ScriptId          = 350013
-- 活动名
x350013_g_Name              = "封测领奖"
-- 提示领取时间
x350013_g_strErrorTime      = "请在8月10日和8月11日的20：00—20：30领取"
x350013_g_shuoming 		      = "\t为了让广大玩家在封测期间有充足的银两体验我们的各种精彩玩法，我们将给所有玩家免费发放海量封测“军饷”！人人都有，上线就有！8月10日、8月11日每晚20:00至20:30限时发放，赶快上线领取吧，过期不候哟！\n\t\n\t8月10日可获得金卡#R50两#W。\n\t8月11日可获得金卡#R100两#W。"

x350013_g_MD1 =MD_LINGJIANG_TIME1
x350013_g_MD2 =MD_LINGJIANG_TIME2
x350013_g_FeastId	  = 2


function x350013_IsFeastActive()
	
	if x350013_g_FeastId ~= MD_CURRENT_FEAST_ID then
				return 0
	end
	return 1
end

-- 点击NPC回调（点击NPC调用，界面中添加封测送金卡按钮）
function x350013_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
	
	if x350013_IsFeastActive() ~= 1	then
		return  
	end 
	
	local day = GetDayOfYear()
	if day < 221 or day > 222 then
		return
	end
	 
    AddQuestNumText( sceneId, x350013_g_ScriptId, x350013_g_Name, 3, 1)
end

-- 玩家点击NPC对话选项按钮后的回调（点击后，根据x350013_GetMoney( sceneId, selfId)返回的值确定是否进入领奖界面，不为0才能进入）
function x350013_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
	if x350013_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "活动没有开启", 8, 3)
        return
    end

        BeginQuestEvent( sceneId)  --1
            AddQuestText( sceneId, "#Y"..x350013_g_Name)  --2
            AddQuestText( sceneId, x350013_g_shuoming )
--         AddQuestMoneyBonus3( sceneId, money)
        EndQuestEvent() --3固定的格式
        DispatchQuestInfo( sceneId, selfId, NPCId, x350013_g_ScriptId, -1) 
end


-- 玩家点击确定（点击确定给钱，同时记录MD）
function x350013_ProcAcceptCheck( sceneId, selfId, NPCId)
	if x350013_IsFeastActive() ~= 1 then
        Msg2Player( sceneId, selfId, "活动没有开启", 8, 3)
        return
        end
	CallScriptFunction(888894,"Feast_SetCurrentId",sceneId,selfId,x350013_g_FeastId)

		local money = x350013_GetMoney( sceneId, selfId)

    if money ~= 0 then
        AddMoney( sceneId, selfId, 3, money)
    else
    	return 0
    end

    local y, m, d = GetYearMonthDay()
    if d == 10 then
        SetQuestData( sceneId, selfId, x350013_g_MD1[ 1], x350013_g_MD1[ 2], x350013_g_MD1[ 3], 1)
    else
        SetQuestData( sceneId, selfId, x350013_g_MD2[ 1], x350013_g_MD2[ 2], x350013_g_MD2[ 3], 1)
    end

    return 1
end


function x350013_ProcAccept( sceneId, selfId, NPCId)
end


function x350013_GetMoney( sceneId, selfId)
	local y, m, d = GetYearMonthDay()
        local minute = GetMinOfDay()

        if m ~= 8 then
        	Msg2Player( sceneId, selfId, x350013_g_strErrorTime, 8, 3)
       		return 0	
        end

   	if d ~= 10 and d ~= 11 then
       		Msg2Player( sceneId, selfId, x350013_g_strErrorTime, 8, 3)
        	return 0
        end

        if minute < 1200 or minute > 1230 then
       		Msg2Player( sceneId, selfId,"只能在20：00—20：30领取金卡奖励", 8, 3)
        	return 0
        end
 

        if d == 10 then
        	if GetQuestData( sceneId, selfId, x350013_g_MD1[ 1], x350013_g_MD1[ 2], x350013_g_MD1[ 3] ) == 1 then
            		Msg2Player( sceneId, selfId, "今天的奖励你已经领取过了", 8, 3)
            	return 0
        else
            return 50000
        end
    end
    if d == 11 then
        if GetQuestData( sceneId, selfId, x350013_g_MD2[ 1], x350013_g_MD2[ 2], x350013_g_MD2[ 3] ) == 1 then
            Msg2Player( sceneId, selfId, "今天的奖励你已经领取过了", 8, 3)
            return 0
        else
            return 100000
        end
    end

end





















