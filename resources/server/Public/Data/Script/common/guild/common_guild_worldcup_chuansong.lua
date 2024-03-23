--MisDescBegin 
x300835_g_ScriptId 					= 	300835
x300835_g_MissionName				= 	"世界杯战场规则"
x300835_g_MissionInfo				= 	"巡按任务信息"
--MisDescEnd

-- 传送点坐标
x300835_g_UpRedX                    = 202
x300835_g_UpRedZ                    = 79
x300835_g_UpBlueX                   = 64
x300835_g_UpBlueZ                   = 88
x300835_g_DownRedX                  = 202
x300835_g_DownRedZ                  = 169
x300835_g_DownBlueX                 = 64
x300835_g_DownBlueZ                 = 175
x300835_g_CenterRedX                = 215
x300835_g_CenterRedZ                = 108
x300835_g_CenterBlueX               = 35
x300835_g_CenterBlueZ               = 111
-- 战场传送NPC
x300835_g_RedNPCUp                  = 129734
x300835_g_RedNPCDown                = 129733
x300835_g_RedNPCCenter              = 129732
x300835_g_BlueNPCUp                 = 129735
x300835_g_BlueNPCDown               = 129736
x300835_g_BlueNPCCenter             = 129739
x300835_g_RedNPCLeave               = 129730
x300835_g_BlueNPCLeave              = 129737

function x300835_ProcEnumEvent( sceneId, selfId, targetId)
    local guid = GetMonsterGUID( sceneId, targetId)

    if guid == x300835_g_RedNPCCenter then
        AddQuestNumText( sceneId, x300835_g_ScriptId, "【右卫军】传送", 13, 1)
        AddQuestNumText( sceneId, x300835_g_ScriptId, "【左卫军】传送", 13, 2)
    elseif guid == x300835_g_BlueNPCCenter then
        AddQuestNumText( sceneId, x300835_g_ScriptId, "【左翼军】传送", 13, 7)
        AddQuestNumText( sceneId, x300835_g_ScriptId, "【右翼军】传送", 13, 8)
    elseif guid == x300835_g_RedNPCUp then
        AddQuestNumText( sceneId, x300835_g_ScriptId, "【本阵】传送", 13, 3)
        AddQuestNumText( sceneId, x300835_g_ScriptId, "【左卫军】传送", 13, 4)
    elseif guid == x300835_g_BlueNPCUp then
        AddQuestNumText( sceneId, x300835_g_ScriptId, "【本阵】传送", 13, 9)
        AddQuestNumText( sceneId, x300835_g_ScriptId, "【右翼军】传送", 13, 10)
    elseif guid == x300835_g_RedNPCDown then
        AddQuestNumText( sceneId, x300835_g_ScriptId, "【右卫军】传送", 13, 5)
        AddQuestNumText( sceneId, x300835_g_ScriptId, "【本阵】传送", 13, 6)
    elseif guid == x300835_g_BlueNPCDown then
        AddQuestNumText( sceneId, x300835_g_ScriptId, "【左翼军】传送", 13, 11)
        AddQuestNumText( sceneId, x300835_g_ScriptId, "【本阵】传送", 13, 12)
    elseif guid == x300835_g_RedNPCLeave or guid == x300835_g_BlueNPCLeave then
        AddQuestNumText( sceneId, x300835_g_ScriptId, "离开战场", 13, 13)
    end
end

function x300835_ProcEventEntry( sceneId, selfId, targetId, MissionId, indexId)
    local nGuildA = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_A_GUILD)
    local nGuildB = GetWorldCupSceneData_Param( sceneId, LD_GUILD_WORLDCUP_B_GUILD)
    local nGuildId = GetGuildID( sceneId, selfId)
    local rx = random( 2, 5)
    local rz = random( 2, 5)

    if indexId == 13 then
        CallScriptFunction( 300615,"OnPlayerAskLeave", sceneId, selfId)
        return
    end

    local state = GetWorldCupState( sceneId)
    if state ~= STATE_GUILD_WORLDCUP_START then
        Msg2Player( sceneId, selfId, "比赛尚未开始，无法传送", 8, 3)
        return
    end

    if indexId == 1 then
        SetPos( sceneId, selfId, x300835_g_UpRedX + rx, x300835_g_UpRedZ + rz)
    elseif indexId == 2 then
        SetPos( sceneId, selfId, x300835_g_DownRedX + rx, x300835_g_DownRedZ + rz)
    elseif indexId == 3 then
        SetPos( sceneId, selfId, x300835_g_CenterRedX + rx, x300835_g_CenterRedZ + rz)
    elseif indexId == 4 then
        SetPos( sceneId, selfId, x300835_g_DownRedX + rx, x300835_g_DownRedZ + rz)
    elseif indexId == 5 then
        SetPos( sceneId, selfId, x300835_g_UpRedX + rx, x300835_g_UpRedZ + rz)
    elseif indexId == 6 then
        SetPos( sceneId, selfId, x300835_g_CenterRedX + rx, x300835_g_CenterRedZ + rz)
    elseif indexId == 7 then
        SetPos( sceneId, selfId, x300835_g_UpBlueX + rx, x300835_g_UpBlueZ + rz)
    elseif indexId == 8 then
        SetPos( sceneId, selfId, x300835_g_DownBlueX + rx, x300835_g_DownBlueZ + rz)
    elseif indexId == 9 then
        SetPos( sceneId, selfId, x300835_g_CenterBlueX + rx, x300835_g_CenterBlueZ + rz)
    elseif indexId == 10 then
        SetPos( sceneId, selfId, x300835_g_DownBlueX + rx, x300835_g_DownBlueZ + rz)
    elseif indexId == 11 then
        SetPos( sceneId, selfId, x300835_g_UpBlueX + rx, x300835_g_UpBlueZ + rz)
    elseif indexId == 12 then
        SetPos( sceneId, selfId, x300835_g_CenterBlueX + rx, x300835_g_CenterBlueZ + rz)
    end
end

function x300835_ProcAcceptCheck( sceneId, selfId, targetId)

end

function x300835_OnDie( sceneId, selfId, killerId)
end

function x300835_ProcQuestLogRefresh( sceneId, selfId, MissionId)
end

function x300835_ProcQuestAttach( sceneId, selfId, npcId, npcGuid, misIndex, MissionId)
end

--**********************************
--接受
--**********************************
function x300835_ProcAccept( sceneId, selfId)
end
--**********************************
--放弃
--**********************************
function x300835_ProcQuestAbandon( sceneId, selfId, MissionId)
end
--**********************************
--继续
--**********************************
function x300835_OnContinue( sceneId, selfId, targetId)
end
--**********************************
--检测是否可以提交
--**********************************
function x300835_CheckSubmit( sceneId, selfId)
end
--**********************************
--提交
--**********************************
function x300835_ProcQuestSubmit( sceneId, selfId, targetId,selectRadioId, MissionId)
end
--**********************************
--杀死怪物或玩家
--**********************************
function x300835_ProcQuestObjectKilled( sceneId, selfId, objdataId, objId, MissionId)
end
--**********************************
--进入区域事件
--**********************************
function x300835_ProcAreaEntered( sceneId, selfId, zoneId, MissionId)
end
--**********************************
--道具改变
--**********************************
function x300835_ProcQuestItemChanged( sceneId, selfId, itemdataId, MissionId)
end