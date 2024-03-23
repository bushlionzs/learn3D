x302512_g_scriptId 		= 302512
x302512_g_Name          = "【活动】粉丝先锋团兑换#r"
-- 兑换物品列表
x302512_g_ItemTable     = {
                            { id = 11000300, sid = 11010020, count = 180, name = "灵魂印" }, 
                            { id = 12030031, sid = 11010020, count = 20,  name = "神行符" }, 
                            { id = 11000501, sid = 11010020, count = 8,  name = "紫檀木炭" }, 
                            { id = 12030258, sid = 11010020, count = 6,  name = "全福月饼" }, 
                            { id = 12030016, sid = 11010020, count = 8,  name = "队伍召集令" }, 
                            { id = 12030241, sid = 11010020, count = 180,  name = "清一色(30天)礼包" }, 
                            { id = 12030240, sid = 11010020, count = 80,  name = "节日时装(14天)礼包" }, 

}

function x302512_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x302512_g_scriptId, "【活动】粉丝先锋团兑换", 3, 99)
end

function x302512_ProcEventEntry( sceneId, selfId, NPCId, MissionId, nExtIdx)
    if nExtIdx == 99 then
		BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x302512_g_Name)
			AddQuestNumText( sceneId, x302512_g_scriptId, "先锋徽章兑换", 3, 100)
			AddQuestNumText( sceneId, x302512_g_scriptId, "黄金先锋徽章兑换", 3, 101)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif nExtIdx == 100 then
		BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y"..x302512_g_Name)
        for i, iter in x302512_g_ItemTable do
            AddQuestNumText( sceneId, x302512_g_scriptId, format( "兑换%s", iter.name), 3, i)
        end
        AddQuestNumText( sceneId, x302512_g_scriptId, "兑换经验", 3, getn( x302512_g_ItemTable) + 1)
        EndQuestEvent()
        DispatchQuestEventList( sceneId, selfId, NPCId)
    elseif nExtIdx == 101 then
		BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x302512_g_Name)
            local count = GetItemCountInBag( sceneId, selfId, 11010021)
            AddQuestText( sceneId, format( "\t你一共有%d个黄金先锋徽章，可兑换#{_MONEY%d}金卡，你确认要兑换么？", count, count * 250) )
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, NPCId, x302512_g_scriptId, -1)
		SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_LEADER, nExtIdx)
    else
        BeginQuestEvent( sceneId)
            AddQuestText( sceneId, "#Y"..x302512_g_Name)
        if nExtIdx <= getn( x302512_g_ItemTable) then
            AddQuestText( sceneId, format( "\t兑换#G%s#W需要#G%s#W个先锋徽章，你确认要兑换么？", x302512_g_ItemTable[ nExtIdx].name, x302512_g_ItemTable[ nExtIdx].count) )
        elseif nExtIdx == getn( x302512_g_ItemTable) + 1 then
            local count = GetItemCountInBag( sceneId, selfId, 11010020)
            AddQuestText( sceneId, format( "\t你一共有%d个先锋徽章，可兑换%d经验，你确认要兑换么？", count, count * 180000) )
        end
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, NPCId, x302512_g_scriptId, -1)
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_LEADER, nExtIdx)
    end
end

function x302512_ProcAcceptCheck( sceneId, selfId, NPCId)

    local index = GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_LEADER)
    
	if index == 101 then
		local count = GetItemCountInBag( sceneId, selfId, 11010021)
		if count > 0 then
			AddMoney( sceneId, selfId, 3, count * 250 )
			-- 删除源物品
			DelItem( sceneId, selfId, 11010021, count)
		end
		return
	end
	
    if index <= getn( x302512_g_ItemTable) then
		-- 检查背包里有没有足够的兑换物品
		local count = GetItemCountInBag( sceneId, selfId, x302512_g_ItemTable[ index].sid)
		if count < x302512_g_ItemTable[ index].count then
			Msg2Player( sceneId, selfId,  "#Y你的#G先锋徽章#Y数量不足，无法兑换", 8, 3)
			Msg2Player( sceneId, selfId,  "#Y你的#G先锋徽章#Y数量不足，无法兑换", 8, 2)
			return 0
		end

		BeginAddItem( sceneId)
		AddBindItem( sceneId, x302512_g_ItemTable[ index].id, 1)
		local b = EndAddItem( sceneId, selfId)
		if b == 0 then
			Msg2Player( sceneId, selfId, "背包空间不足，无法兑换", 8, 3)
			return 0
		end
		-- 添加要送物品
		AddItemListToPlayer( sceneId, selfId)
		-- 删除源物品
		DelItem( sceneId, selfId, x302512_g_ItemTable[ index].sid, x302512_g_ItemTable[ index].count)
    elseif index == getn( x302512_g_ItemTable) + 1 then
        local count = GetItemCountInBag( sceneId, selfId, 11010020)
        if count > 0 then
			AddExp( sceneId, selfId, count * 180000)
			-- 删除源物品
			DelItem( sceneId, selfId, 11010020, count)
		end
    end
end


