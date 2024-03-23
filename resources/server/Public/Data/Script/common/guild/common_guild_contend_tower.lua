
-------------------------
--***********************
--Const
--***********************
-------------------------

x300616_g_ScriptId 					= 300616
x300616_g_MissionName				= "【世界杯】上缴龙珠"
x300616_g_strDescription            = "\t你要上缴龙珠么？"
x300616_g_Score                     = 50
x300616_g_Score_Crystal             = 1
x300616_g_ItemId                    = 13080024

function x300616_ProcEnumEvent( sceneId, selfId, targetId, MissionId)
    local state = GetWorldCupState( sceneId)
    if state == STATE_GUILD_WORLDCUP_START then
        AddQuestNumText( sceneId, x300616_g_ScriptId, x300616_g_MissionName, 3, 1)
        AddQuestNumText( sceneId, x300616_g_ScriptId, "【世界杯】上缴幽谷玄冰", 3, 2)
    end
    return 1
end

function x300616_ProcEventEntry( sceneId, selfId, targetId, idScript, idExt)
    SetPlayerRuntimeData( sceneId, selfId, RD_GUILDBATTLE_BEKILLED, 0)
    if idExt == 1 then
        if IsHaveSpecificImpact( sceneId, selfId, 7801) == 0 then
            Msg2Player( sceneId, selfId, "你没有夺取龙珠，无法上缴", 8, 3)
            return
        end
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y"..x300616_g_MissionName)
        AddQuestText( sceneId, x300616_g_strDescription)
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, targetId, x300616_g_ScriptId, -1)
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDBATTLE_BEKILLED, idExt)
    elseif idExt == 2 then
        if GetItemCountInBag( sceneId, selfId, x300616_g_ItemId) <= 0 then
            Msg2Player( sceneId, selfId, "你没有夺取幽谷玄冰，无法上缴", 8, 3)
            return
        end
        BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y"..x300616_g_MissionName)
        AddQuestText( sceneId, "\t你要上缴幽谷玄冰么？")
        EndQuestEvent()
        DispatchQuestInfo( sceneId, selfId, targetId, x300616_g_ScriptId, -1)
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDBATTLE_BEKILLED, idExt)
    end
end

function x300616_ProcAcceptCheck( sceneId, selfId, targetId)
    local commitType = GetPlayerRuntimeData( sceneId, selfId, RD_GUILDBATTLE_BEKILLED)
    local nGuildA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD)
    local nGuildB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD)
    local nGuildId = GetGuildID( sceneId, selfId)

    if commitType == 1 then
        if IsHaveSpecificImpact( sceneId, selfId, 7801) == 0 then
            Msg2Player( sceneId, selfId, "你没有夺取龙珠，无法上缴", 8, 3)
            return 0
        end

        local growPointid = GetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID)
        if nGuildA == nGuildId then
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE, GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE) + x300616_g_Score)
        elseif nGuildB == nGuildId then
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE, GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE) + x300616_g_Score)
        end

        CancelSpecificImpact( sceneId, selfId, 7801)
        CancelSpecificImpact( sceneId, selfId, 7802)
        -- 更新个人采集计数
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_ASSIST, GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_ASSIST) + 1)
        -- 更新个人得分
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_SCORE, GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_SCORE) + x300616_g_Score)
        Msg2Player( sceneId, selfId, format( "#G%s#cffcc00上缴一颗龙珠。", GetName( sceneId, selfId) ), 6, 2)
        Msg2Player( sceneId, selfId, "你上缴一颗龙珠。", 8, 2)

        SetGrowPointPos( sceneId, growPointid, 126, 124)
        SetGrowPointIntervalContainer( sceneId, growPointid, 1000)
        SetPlayerRuntimeData( sceneId, selfId, RD_DANCERY_BODYID, 0)
        SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_FLAGOCCUPY, -1)
    elseif commitType == 2 then
        if GetItemCountInBag( sceneId, selfId, x300616_g_ItemId) <= 0 then
            Msg2Player( sceneId, selfId, "你没有夺取幽谷玄冰，无法上缴", 8, 3)
            return 0
        end

        if DelItem( sceneId, selfId, x300616_g_ItemId, 1) <= 0 then
            Msg2Player( sceneId, selfId, "提交幽谷玄冰失败", 8, 3)
            return 0
        end

        if nGuildA == nGuildId then
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE, GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_SOCRE) + x300616_g_Score_Crystal)
        elseif nGuildB == nGuildId then
            SetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE, GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_SOCRE) + x300616_g_Score_Crystal)
        end

        -- 更新个人采集玄冰计数
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_FAMILY, GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_KILL_FAMILY) + 1)
        -- 更新个人得分
        SetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_SCORE, GetPlayerRuntimeData( sceneId, selfId, RD_GUILDCONTEND_SCORE) + 1)

        Msg2Player( sceneId, selfId, format( "#G%s#cffcc00上缴一块@item_%d#cffcc00。", GetName( sceneId, selfId), x300616_g_ItemId), 6, 2)
        Msg2Player( sceneId, selfId, format( "你上缴一块@item_%d#cffcc00。", x300616_g_ItemId), 8, 2)
    end

    SetPlayerRuntimeData( sceneId, selfId, RD_GUILDBATTLE_BEKILLED, 0)

	return 1;
end

function x300616_ProcAccept( sceneId, selfId, targetId)
    -- print( "x300616_OnAccept" )
	-- local str = x300616_DoGuildDelate(sceneId, selfId, targetId)
	-- if str ~= nil then
		-- Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_RIGHTDOWN)
		-- Msg2Player(sceneId,selfId,str,CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
	-- end
end

