--成就兑换经验

--MisDescBegin
x570040_g_ScriptId = 570040
x570040_g_ExtTarget={}
x570040_g_MissionName1 = "荣誉兑换经验"
--MisDescEnd

-- 等级系数配置表（80级之后每5级比75级的提高30%）
x570040_g_LevelTable    = {
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

function x570040_ProcEventEntry( sceneId, selfId, targetId, scriptid, extid)	--点击该任务后执行此脚本
    local level = GetLevel( sceneId, selfId)
    local xp = 48000
    for i, item in x570040_g_LevelTable do
        if level >= item.minLevel and level < item.maxLevel then
            xp = item.coff * level
        end
    end

	BeginQuestEvent( sceneId)
	    AddQuestText( sceneId, "#Y荣誉兑换经验" )
        AddQuestText( sceneId, format( "\n\t你所取得的成就有目共睹！#G荣誉#W正是你对国家所做贡献的最好证明。您可以在这里用#R5000点#G荣誉#W兑换#R%d点#G经验#W。但每天只可以兑换一次。\n \n\t您现在有#R%d点#G荣誉#W。", xp, GetHonor( sceneId, selfId) ) )
        AddQuestText( sceneId, "\n\t你确定要用#G荣誉#W兑换#G经验#W么？" )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, targetId, x570040_g_ScriptId, -1)
end



--**********************************

--列举事件

--**********************************

function x570040_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
    AddQuestNumText( sceneId, x570040_g_ScriptId, x570040_g_MissionName1, 3, 1)
end

function x570040_ProcAcceptCheck( sceneId, selfId, NPCId)
    return 1
end

function x570040_ProcAccept( sceneId, selfId)
    local score = GetHonor( sceneId, selfId)
    if score < 5000 then
        Msg2Player( sceneId, selfId, "你的荣誉不足5000点，无法兑换经验", 8, 3)
        return
    end

    local day = GetDayOfYear()
    if day == GetQuestData( sceneId, selfId, MD_CHENGJIOU_RONGYU[ 1], MD_CHENGJIOU_RONGYU[ 2], MD_CHENGJIOU_RONGYU[ 3] ) then
        Msg2Player( sceneId, selfId, "你今天已经兑换过一次了，请明天再来", 8, 3)
        return
    else
        SetQuestData( sceneId, selfId, MD_CHENGJIOU_RONGYU[ 1], MD_CHENGJIOU_RONGYU[ 2], MD_CHENGJIOU_RONGYU[ 3], day)
    end

    local level = GetLevel( sceneId, selfId)
    local xp = 48000
    for i, item in x570040_g_LevelTable do
        if level >= item.minLevel and level < item.maxLevel then
            xp = item.coff * level
        end
    end

    AddExp( sceneId, selfId, xp)
    Msg2Player( sceneId, selfId, format( "获得#R%d#cffcc00点经验", xp), 8, 3)
    Msg2Player( sceneId, selfId, format( "获得#R%d#cffcc00点经验。", xp), 8, 2)
	SubHonor( sceneId, selfId, 5000)
end

