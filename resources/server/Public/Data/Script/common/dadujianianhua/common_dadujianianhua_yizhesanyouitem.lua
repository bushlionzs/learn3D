x310166_g_ScriptId = 310166
x310166_g_ScriptName = "提交高丽贡书"	

x310166_g_ScripText = "\t和贡品一起丢失的还有三册贡书，里面记载着贡品的名称和数量。\n\t#Y@myname#W，请帮我把三册贡书找回来好吗？\n \n#G(完成大都NPC[益者三友]全美丽#G的任务过程中有几率得到高丽贡书。)"

x310166_g_Item = {12030080, 12030081, 12030082}

-- 玩法开放时间(从0点起的第x分钟)
x310166_g_OpenTime                  = 1170
-- 玩法关闭时间(从0点起的第x分钟)
x310166_g_EndTime                   = 1440

function x310166_ProcEnumEvent( sceneId, selfId, targetId, MissionId )
	AddQuestNumText(sceneId, x310166_g_ScriptId, x310166_g_ScriptName,3)
end

function x310166_ProcEventEntry( sceneId, selfId, targetId, MissionId )
	local exp = GetLevel( sceneId, selfId)*7000
	BeginQuestEvent( sceneId)
    AddQuestText( sceneId, "#Y"..x310166_g_ScriptName)
    AddQuestText(sceneId, x310166_g_ScripText)
    AddQuestText( sceneId, "\n#Y奖励内容：#W")
    AddQuestText( sceneId, "经验值:"..exp )
    
    DispatchQuestInfo(sceneId, selfId, targetId, x310166_g_ScriptId, -1)
end


function x310166_CheckItem( sceneId, selfId)

	for i, item in x310166_g_Item do
		if HaveItemInBag( sceneId, selfId, item ) <= 0 then
			return 0
		end
	end
	return 1
end

function x310166_ProcAcceptCheck( sceneId, selfId, targetId)

	local nowTime = GetMinOfDay()
    if nowTime < x310166_g_OpenTime or nowTime >= x310166_g_EndTime then
		local msg = "只有在每日的#G19：30--24：00#cffcf00内才可提交高丽贡书。"
        Msg2Player( sceneId, selfId, msg, 8, 2)
        Msg2Player( sceneId, selfId, msg, 8, 3)
		return
    end

	local lastDay = GetQuestData(sceneId, selfId, MD_YIZHESANYOU_ITEM_DAY[1], MD_YIZHESANYOU_ITEM_DAY[2], MD_YIZHESANYOU_ITEM_DAY[3])

	local today = GetDayOfYear()
	if today == lastDay then 
		local msg = "您今天已经提交过高丽贡书了，请明天再来。"
        Msg2Player( sceneId, selfId, msg, 8, 2)
        Msg2Player( sceneId, selfId, msg, 8, 3)
        return
	end
		

    if x310166_CheckItem( sceneId, selfId) == 1 then
		for i, item in x310166_g_Item do
			DelItem( sceneId, selfId, item, 1 )
		end
		
		SetQuestData(sceneId, selfId, MD_YIZHESANYOU_ITEM_DAY[1], MD_YIZHESANYOU_ITEM_DAY[2], MD_YIZHESANYOU_ITEM_DAY[3], today)
		
		local exp = GetLevel( sceneId, selfId)*7000
		AddExp( sceneId, selfId, exp)
        Msg2Player( sceneId, selfId, format( "获得#R经验%d点#cffcf00的奖励", exp).."。", 8, 2)
        Msg2Player( sceneId, selfId, format( "获得#R经验%d点#cffcf00的奖励", exp), 8, 3)
    else
        Msg2Player( sceneId, selfId, "您身上没有全套的高丽贡书，提交失败", 8, 2)
        Msg2Player( sceneId, selfId, "您身上没有全套的高丽贡书，提交失败", 8, 3)
	end
end