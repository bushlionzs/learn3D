-- 物品列表
x430009_g_ItemTable         = {
                                { name = "神传龙吟戒指（武士）", itemid = 10284003 }, 
                                { name = "神传碎玉戒指（剑侠）", itemid = 10284013 }, 
                                { name = "神传逐日戒指（骑射）", itemid = 10284023 }, 
                                { name = "神传虎跃戒指（火枪）", itemid = 10284033 }, 
                                { name = "神传白虎戒指（先知）", itemid = 10284043 }, 
                                { name = "神传师君戒指（萨满）", itemid = 10284053 }, 
                                { name = "神传龙吟手镯（武士）", itemid = 10294003 }, 
                                { name = "神传碎玉手镯（剑侠）", itemid = 10294013 }, 
                                { name = "神传逐日手镯（骑射）", itemid = 10294023 }, 
                                { name = "神传虎跃手镯（火枪）", itemid = 10294033 }, 
                                { name = "神传白虎手镯（先知）", itemid = 10294043 }, 
                                { name = "神传师君手镯（萨满）", itemid = 10294053 }, 
}

x430009_g_MissionId         = 9339
x430009_g_scriptId          = 430009
-- VIP首饰盒
x430009_g_VIPItem           = 12030385

function x430009_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
	BeginQuestEvent( sceneId)
		AddQuestText( sceneId, "\t这只神秘的盒子中珍藏着各种神传首饰，您只能选择其中的一只。\n\t请珍惜这次机会，因为选择了这只首饰，这个首饰盒将立刻消失。" )
        for i, item in x430009_g_ItemTable do
            AddQuestNumText( sceneId, x430009_g_MissionId, item.name, 3, i)
        end
	EndQuestEvent()                                                
    DispatchQuestEventList( sceneId, selfId, selfId)
end

function x430009_ProcEventEntry( sceneId, selfId, targetId, scriptid, extid)
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, format( "\t您确认要选择#Y%s#W吗？\n\t您确认后将永久的获得，请谨慎挑选！", x430009_g_ItemTable[ extid].name) )
        AddQuestRadioItemBonus( sceneId, x430009_g_ItemTable[ extid].itemid, 1)
        SetPlayerRuntimeData( sceneId, selfId, RD_VIP_BOX, extid)
    EndQuestEvent()
	DispatchQuestInfoNM( sceneId, selfId, selfId, x430009_g_scriptId, x430009_g_MissionId)
end

function x430009_ProcQuestAccept( sceneId, selfId, targetId, missionId)
    -- 检查背包空间
    local index = GetPlayerRuntimeData( sceneId, selfId, RD_VIP_BOX)
    BeginAddItem( sceneId)
    AddItem( sceneId, x430009_g_ItemTable[ index].itemid, 1)
    if EndAddItem( sceneId, selfId) <= 0 then
        Msg2Player( sceneId, selfId, "无法得到物品，请整理背包", 8, 3)
        return
    end
    -- 删除VIP首饰盒
    if DelItem( sceneId, selfId, x430009_g_VIPItem, 1) == 0 then
        Msg2Player( sceneId, selfId, "神传首饰盒删除失败。", 8, 2)
        Msg2Player( sceneId, selfId, "神传首饰盒删除失败。", 8, 3)
        return 0
    end
    -- 添加物品
    AddItemListToPlayer( sceneId, selfId)
end

