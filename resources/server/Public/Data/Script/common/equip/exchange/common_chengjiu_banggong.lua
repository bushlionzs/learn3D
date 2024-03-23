--成就兑换经验

--MisDescBegin
x570041_g_ScriptId = 570041
x570041_g_ExtTarget={}
x570041_g_MissionName1 = "帮贡兑换经验"
--MisDescEnd

-- 等级系数配置表（80级之后每5级比75级的提高30%）
x570041_g_LevelTable    = {
                            { minLevel = 1,  maxLevel = 75,  coff = 48000},
                            { minLevel = 75, maxLevel = 80,  coff = 70000},
                            { minLevel = 80, maxLevel = 85,  coff = 91000 },
							{ minLevel = 85, maxLevel = 90,  coff = 112000},
                            { minLevel = 90, maxLevel = 95,  coff = 133000},
                            { minLevel = 95, maxLevel = 161, coff = 154000},
}

--**********************************

--任务入口函数

--**********************************

function x570041_ProcEventEntry( sceneId, selfId, targetId, scriptid, extid)	--点击该任务后执行此脚本
    local level = GetLevel( sceneId, selfId)
    local xp = 48000
    for i, item in x570041_g_LevelTable do
        if level >= item.minLevel and level < item.maxLevel then
            xp = item.coff * level
        end
    end

	BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y帮贡兑换经验" )
		AddQuestText( sceneId, format( "\n\t你所取得的成就有目共睹！#G帮贡#W正是你对帮会所做贡献的最好证明。您可以在这里用#R2000点#G帮贡#W兑换#R%d点#G经验#W。但每天只可以兑换一次。\n \n\t您现在有#R%d点#G帮贡#W。", xp, GetGuildUserPoint( sceneId, selfId) ) )
        AddQuestText( sceneId, "\n\t你确定要用#G帮贡#W兑换#G经验#W么？" )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x570041_g_ScriptId, -1)
end



--**********************************

--列举事件

--**********************************

function x570041_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x570041_g_ScriptId, x570041_g_MissionName1, 3, 1)
end

function x570041_ProcAcceptCheck( sceneId, selfId, NPCId)
    return 1
end

function x570041_ProcAccept( sceneId, selfId)
    local score = GetGuildUserPoint( sceneId, selfId)
    if score < 2000 then
        Msg2Player( sceneId, selfId, "你的帮贡不足2000点，无法兑换经验", 8, 3)
        return
    end

    local day = GetDayOfYear()
    if day == GetQuestData( sceneId, selfId, MD_CHENGJIOU_BANGGONG[ 1], MD_CHENGJIOU_BANGGONG[ 2], MD_CHENGJIOU_BANGGONG[ 3] ) then
        Msg2Player( sceneId, selfId, "你今天已经兑换过一次了，请明天再来", 8, 3)
        return
    else
        SetQuestData( sceneId, selfId, MD_CHENGJIOU_BANGGONG[ 1], MD_CHENGJIOU_BANGGONG[ 2], MD_CHENGJIOU_BANGGONG[ 3], day)
    end

    local level = GetLevel( sceneId, selfId)
    local xp = 48000
    for i, item in x570041_g_LevelTable do
        if level >= item.minLevel and level < item.maxLevel then
            xp = item.coff * level
        end
    end

    AddExp( sceneId, selfId, xp)
    Msg2Player( sceneId, selfId, format( "获得#R%d#cffcc00点经验", xp), 8, 3)
    Msg2Player( sceneId, selfId, format( "获得#R%d#cffcc00点经验。", xp), 8, 2)
	SubGuildUserPoint( sceneId, selfId, 2000)
end

